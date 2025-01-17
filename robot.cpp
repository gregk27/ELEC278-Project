#include <stdio.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <sstream>
#include "robot.h"
#include "utils/utils.h"
#include "field/field.h"
#include "field/Fieldnode.h"
#include "utils/Heap.h"

#define BUFF_SIZE 256
// Some compilers may be missing M_PI, this serves as a safety check https://stackoverflow.com/questions/14920675/is-there-a-function-in-c-language-to-calculate-degrees-radians
#ifndef M_PI
#define M_PI 3.1415926535
#endif

Robot::Robot(){
    this->id = -1;
    this->team = 0000;
    this->speed = 0;
    this->alliance = Alliance::NEUTRAL;
    this->canLowbar = false;
    this->defenses = 0;
    this->shotRange = 0;
    this->centreShotTime = 0;
    this->sideShotTime = 0;
    this->centreAngle = 0;
    this->sideAngle = 0;
    this->lowTime = 0;
    this->path = NULL;
}

void Robot::initGraph(){
    // Initialise warning
    std::stringstream warning;
    // If the shot range is greated than the distance to defenses, there is something wrong. Warn the user and cap it
    if(shotRange > DEFENSE_EDGE_OFFSET-TOWER_OFFSET_X){
        warning << "\tShot range of " << (int)shotRange << "\" is larger than the " << DEFENSE_EDGE_OFFSET-TOWER_OFFSET_X << "\" distance to the defenses. This will be capped to prevent issues.\n";
        shotRange = DEFENSE_EDGE_OFFSET-TOWER_OFFSET_X;
    }

    // Create goal node at the centre of the tower
    goalNode = new Fieldnode(RED_TOWER_X, RED_TOWER_Y, Alliance::RED);
    
    // Initialise the graph with field nodes
    graph = Field::initGraph();
    Shotnode *s;
    if(centreShotTime > 0){
        // Middle centre
        s = getShotZone(shotRange, 0);
        s->time = centreShotTime;
        graph->addNode(s);
        shotnodes.push(s);
        // Connected to central courtyard and central 2 defenses
        graph->addEdge(s, &Field::redCourtyard[1]);
        graph->addDefenseEdge(s, &Field::redDefenses[2], false);
        graph->addDefenseEdge(s, &Field::redDefenses[3], false);
        // Add angled nodes if applicable
        if(centreAngle > 0){
            // Top centre
            s = getShotZone(shotRange, -centreAngle);
            shotnodes.push(s);
            s->time = centreShotTime;
            graph->addNode(s);
            // Connected to upper/central courtyard and upper 2 defenses
            graph->addEdge(s, &Field::redCourtyard[2]);
            graph->addEdge(s, &Field::redCourtyard[1]);
            graph->addDefenseEdge(s, &Field::redDefenses[3], false);
            graph->addDefenseEdge(s, &Field::redDefenses[4], false);

            // Bottom centre
            s = getShotZone(shotRange, centreAngle);
            shotnodes.push(s);
            s->time = centreShotTime;
            graph->addNode(s);
            // Connected to lower courtyard and central 2 defenses
            graph->addEdge(s, &Field::redCourtyard[0]);
            graph->addEdge(s, &Field::redCourtyard[1]);
            graph->addDefenseEdge(s, &Field::redDefenses[0], false);
            graph->addDefenseEdge(s, &Field::redDefenses[1], false);
            graph->addDefenseEdge(s, &Field::redDefenses[2], false);

            // If the centre angle is higher than 40deg soft limit
            if(centreAngle > 40){
                warning << "\tCentre angle of " << (int)centreAngle << "deg exceeds recommended limit of 40deg\n";
            }
        }
        // If the cetre shot time is more than 20 seconds, there may be input issues
        if(centreShotTime > 20){
            warning << "\tCentre shot time of " << (int)centreShotTime << "s is quite high, there may be broken input\n";
        }
    }
    if(sideShotTime > 0){
        // Upper side
        s = getShotZone(shotRange, -(90-sideAngle));
        shotnodes.push(s);
        s->time = sideShotTime;
        graph->addNode(s);
        // Connect to upper courtyard and upper 2 defenses
        graph->addEdge(s, &Field::redCourtyard[2]);
        graph->addDefenseEdge(s, &Field::redDefenses[3], false);
        graph->addDefenseEdge(s, &Field::redDefenses[4], false);

        // Lower side
        s = getShotZone(shotRange, 90-sideAngle);
        shotnodes.push(s);
        s->time = sideShotTime;
        graph->addNode(s);
        // Connect to lower courtyard and lower 2 defenses
        graph->addEdge(s, &Field::redCourtyard[0]);
        graph->addDefenseEdge(s, &Field::redDefenses[0], false);
        graph->addDefenseEdge(s, &Field::redDefenses[1], false);

        // If the side angle is higher than 40deg soft limit
        if(sideAngle > 40){
            warning << "\tSide angle of " << (int)sideAngle << "deg exceeds recommended limit of 40deg\n";
        }
        // If the side shot time is more than 20 seconds, there may be input issues
        if(sideShotTime > 20){
            warning << "\tSide shot time of " << (int)sideShotTime << "s is quite high, there may be broken input\n";
        }
    }

    // If the warning string has content, then there are warnings to report
    if(warning.str().length() > 0){
        printf("The following shot parameters exceed recommended tolerance:\n");
        printf(warning.str().c_str());
        // Allow the user to continue, as these warnings don't stop functionality
        printf("Do you wish to continue with the simulation? [y/n] ");
        char c;
        scanf("%c", &c);
        if(c != 'Y' && c != 'y'){
            throw(invalid_parameter_exception("Shot configuration warnings not accepted"));
        }
    }

    // Connect tower and shotnodes to goal node with 0 distance
    graph->addNode(goalNode);
    // If the low time is 0 then the bot can't score there
    if(lowTime != 0){
        graph->addDirectedEdge(&Field::redTowerTop, goalNode, 0);
        graph->addDirectedEdge(&Field::redTowerBottom, goalNode, 0);
    }
    for(auto i : shotnodes) {
        this->graph->addDirectedEdge(i.data, goalNode, 0);
    }

    // graph->printAdj();
}

Shotnode *Robot::getShotZone(int range, int angle){
    int x, y;
    float angleRad = angle*(M_PI/180);
    if(alliance == Alliance::RED){
        x = goalNode->x + range*cos(angleRad);
        y = goalNode->y + range*sin(angleRad);
    } else if(alliance == Alliance::BLUE){
        x = goalNode->x - range*cos(angleRad);
        y = goalNode->y + range*sin(angleRad);
    } else {
        x = 0;
        y = 0;
    }

    return new Shotnode(x, y, Alliance::NEUTRAL, Fieldnode::Type::SHOTNODE);
}


int Robot::crossTime(int id){
    // If it's the low bar, then it is impossible or 1 second
    if(id == Defense::LOW_BAR){
        return canLowbar;
    }
    //Shift the current defense into lower 4 bits, then mask
    return (defenses >> (id*4)) & 0xF;
}


int Robot::crossTime(Defense *d){
    return crossTime(d->defType);
}

Event Robot::getEvent(){
    Event e;
    e.location = location;
    e.path = path;
    e.r = this;
    e.time = wakeTime;
    switch(location->type){
        case Fieldnode::Type::TOWER:
            e.type = Event::Type::SCORE_LOW;
            e.points = LOW_POINTS;
            break;
        case Fieldnode::Type::SHOTNODE:
            e.type = Event::Type::SCORE_HIGH;
            e.points = HIGH_POINTS;
            break;
        case Fieldnode::Type::DEFENSE:
            e.type = Event::Type::CROSS;
            e.points = ((Defense *) location)->cross();
            break;
        default:
            e.type = Event::Type::PASSTHROUGH;
            e.points = 0;
            break;
    }
    if(e.location == intakeNode){
        e.type == Event::Type::INTAKE;
    }
    return e;
}

void Robot::navUpdate(LinkedList<Event> *events){
    // Add completed event to queue
    events->push(getEvent());

    // If the robot has scored a ball, it now needs to get another
    if(location->type == Fieldnode::Type::TOWER || location->type == Fieldnode::Type::SHOTNODE){
        hasBall = false;
        cyclesCompleted ++;
    } else if(location == intakeNode){
        hasBall = true;
    }

    Graph::DijkstraNode *n;
    // If the robot has the ball, go to the tower, otherwise go back to pickup node
    if(hasBall){
        n = getPath(goalNode);
    } else {
        n = getPath(&Field::redPassage[0]);
    }

    path = n;

    // Cycle back to find next node
    while(n->prev != NULL && n->prev->node!=location){
        n = n->prev;
    }
    // Move the robot to the next node
    location = n->node;
    // Update the wake time, because point value is deducted from time, re-add it
    wakeTime += n->time;
}

Graph::DijkstraNode *Robot::getPath(Fieldnode *target){
    Heap<Graph::DijkstraNode*> todo = Heap<Graph::DijkstraNode*>([](Graph::DijkstraNode *n1, Graph::DijkstraNode *n2)->bool{return n1->weight < n2->weight;}, [](Graph::DijkstraNode *d)->const char*{
        if(d == NULL) return "N,N";
        std::stringstream s;
        s << d->weight << "," << d->node->index;
        return s.str().c_str();
    });
    LinkedList<Graph::DijkstraNode*> completed;

    // Initialise the TODO array with inifinty
    // TODO: Don't add nodes which shouldn't be visited (eg other alliance, uncrossable defense)
    for(auto i : graph->nodes){
        Graph::DijkstraNode *n = new Graph::DijkstraNode();
        n->node = i.data;
        n->prev = NULL;
        n->weight = (i.data == location ? 0 : INT_MAX);
        n->time = 0;
        todo.push(n);
    }

    Graph::DijkstraNode *n;
    LinkedList<Graph::Edge> *adj;
    while(todo.pop(&n, 0)){  
        
        //Get the adjacency matrix for this node and iterate over it
        adj = graph->adjacency[n->node->index];
        for(auto i : *adj){
            Graph::Edge e = i.data;

            // If it's not in the list, then it has already been visited
            int todoIdx = todo.indexOf([e](Graph::DijkstraNode *n)->bool{return e.end == n->node;});
            if(todoIdx == -1) continue;

            // Get weight of the edge
            Robot::EdgeData edgeData = getWeight(n, e);
            float weight = n->weight + edgeData.weight;
            float time = n->time + edgeData.time;
            if(edgeData.weight == INT_MAX){
                weight = INT_MAX;
            }

            // If we have a new shorter path, update it
            if((*todo.peek(todoIdx))->weight > weight){
                Graph::DijkstraNode *n2;
                // Get the node and remove it
                todo.pop(&n2, todoIdx);
                
                // Update the node
                n2->prev = n;
                n2->weight = weight;
                n2->time += time;
                // Reinsert it
                todo.push(n2); 

            }
            // If we've reached the target
            if(e.end == target){
                printf("DONE!\n");
                Graph::DijkstraNode *returnNode = new Graph::DijkstraNode();
                returnNode->node = e.end;
                returnNode->prev = n;
                returnNode->weight = weight;
                returnNode->time = time;
                return returnNode;
            }
        }
        // Add n to the completed list. This is done first so we can pop off the target node once reached
        printf("Completed %d\n", n->node->index);
        completed.push_front(n); 
    }
    return NULL;
}

Robot::EdgeData Robot::getWeight(Graph::DijkstraNode *n, Graph::Edge e){
    Robot::EdgeData out;
    // Base weight is time in seconds, measure by previous plus d*v
    out.weight = e.distance/speed;
    out.time = out.weight;
    // Don't go to nodes which are for the other alliance
    if(e.end->alliance != alliance && e.end->alliance != Alliance::NEUTRAL){
        out.weight = INT_MAX;
        return out;
    }
    // Don't pathfind through shotnodes
    if(n->node->type == Fieldnode::Type::SHOTNODE && location != n->node){
        out.weight = INT_MAX;
        return out;
    }
    if(e.end->type == Fieldnode::Type::DEFENSE){
        int cTime = crossTime((Defense *) e.end);
        if(cTime != 0){
            // Add cross time, subtract points for crossing
            out.weight += cTime - ((Defense *) e.end)->value*pointValue;
            out.time += cTime;
        } else {
            out.weight = INT_MAX;
            return out;
        }
    } else if (e.end->type == Fieldnode::Type::SHOTNODE && hasBall){ // Add time taken to shoot ball
        out.weight += ((Shotnode *) e.end)->time - HIGH_POINTS*pointValue;
        out.time += ((Shotnode *) e.end)->time;;
    } else if (e.end->type == Fieldnode::Type::TOWER && hasBall){
        out.weight += lowTime - LOW_POINTS*pointValue;
        out.time += lowTime;
    }
    return out;
}

LinkedList<Robot *> Robot::parseCSV(std::string filename){
    LinkedList<Robot *> bots;
    // Open the file
    FILE *f = fopen(filename.c_str(), "r"); 
    if(f == NULL){
        std::stringstream s;
        s << "Could not open file " << filename;
        throw file_open_exception(s.str());
    }

    // Buffer for read lines. No line following the correct format will exceed 64 characters
    char line[BUFF_SIZE];


    // Remove header line
    fgets (line, BUFF_SIZE, f);

    // Read all robots in file
    while(fgets (line, BUFF_SIZE, f) != NULL){
        Robot *bot = new Robot();
        // Read robot line
        // Data order: team,can_low,shot_range,centre_shot_time,side_shot_time,centre_angle,side_angle,low_time,defenses,speed
        int result = sscanf(line, "%d,%d,%d,%d,%d,%d,%d,%d,%lx,%f,%f", 
            &(bot->team),
            &(bot->canLowbar),
            &(bot->shotRange),
            &(bot->centreShotTime),
            &(bot->sideShotTime),
            &(bot->centreAngle),
            &(bot->sideAngle),
            &(bot->lowTime),
            &(bot->defenses),
            &(bot->speed), 
            &(bot->pointValue));
        
        // Validate input
        // If less values are read than expected, something went wrong
        if(result != 11){
            std::stringstream s;
            s << "Error while parsing robot " << bot->team << ". Read " << result << " values of 11.";
            throw csv_parsing_exception(s.str());
        }

        // Check that team number is unique
        for(auto r : bots){
            if(r.data->team == bot->team){
                std::stringstream s;
                s << "Duplicate team number " << bot->team << ". Please change one.";
                throw invalid_parameter_exception(s.str());
            }
        }

        // If the bot's speed is 0, then it can't go anywhere and there is no point in simulating
        if(bot->speed <= 0) throw invalid_parameter_exception("Robot's speed is negative or zero, this would prevent any motion. Speed must be a positive nonzero number.");
        // If the bot cannot cross any defenses, then there is no point in simulating
        if(!bot->defenses && !bot->canLowbar) throw invalid_parameter_exception("Robot cannot cross any defenses, this would prevent any gameplay. Robot must be able to cross at least one defense");
        // If the bot can't score, then tehre is no point in simulating
        if(!bot->centreShotTime && !bot->sideShotTime && !bot->lowTime) throw invalid_parameter_exception("Robot cannot score, this prevents any gameplay. One scoring time must be nonzero");
        
        // Finish setup
        // Convert from the fps input to ips for internal use
        bot->speed *= 12;
        // Set the bot's alliance. Currently this is hardcoded to red but may change in the future
        bot->alliance = Alliance::RED;
        // Set the bot's id. Currently hardcoded but this may change in the future
        bot->id = 0;
        bots.push(bot);
    }

    return bots;
}