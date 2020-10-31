#include <stdio.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include "robot.h"
#include "utils/utils.h"
#include "field/field.h"
#include "field/Fieldpoint.h"

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
}

void Robot::initGraph(){
    // Initialise warning
    std::stringstream warning;
    // If the shot range is greated than the distance to defenses, there is something wrong. Warn the user and cap it
    if(shotRange > DEFENSE_EDGE_OFFSET-TOWER_OFFSET){
        warning << "\tShot range of " << (int)shotRange << "\" is larger than the " << DEFENSE_EDGE_OFFSET-TOWER_OFFSET << "\" distance to the defenses. This will be capped to prevent issues.\n";
        shotRange = DEFENSE_EDGE_OFFSET-TOWER_OFFSET;
    }
    
    // Initialise the graph with field nodes
    graph = Field::initGraph();
    Shotpoint *s;
    if(centreShotTime > 0){
        // Middle centre
        s = getShotZone(shotRange, 0);
        s->time = centreShotTime;
        graph->addNode(s);
        // Connected to central courtyard and central 2 defenses
        graph->addEdge(s, &Field::redCourtyard[1]);
        graph->addEdge(s, &Field::redDefenses[2]);
        graph->addEdge(s, &Field::redDefenses[3]);
        // Add angled nodes if applicable
        if(centreAngle > 0){
            // Top centre
            s = getShotZone(shotRange, -centreAngle);
            s->time = centreShotTime;
            graph->addNode(s);
            // Connected to upper/central courtyard and upper 2 defenses
            graph->addEdge(s, &Field::redCourtyard[2]);
            graph->addEdge(s, &Field::redCourtyard[1]);
            graph->addEdge(s, &Field::redDefenses[3]);
            graph->addEdge(s, &Field::redDefenses[4]);

            // Bottom centre
            s = getShotZone(shotRange, centreAngle);
            s->time = centreShotTime;
            graph->addNode(s);
            // Connected to lower courtyard and central 2 defenses
            graph->addEdge(s, &Field::redCourtyard[0]);
            graph->addEdge(s, &Field::redCourtyard[1]);
            graph->addEdge(s, &Field::redDefenses[0]);
            graph->addEdge(s, &Field::redDefenses[1]);
            graph->addEdge(s, &Field::redDefenses[2]);

            // If the centre angle is higher than 40° soft limit
            if(centreAngle > 40){
                warning << "\tCentre angle of " << (int)centreAngle << "° exceeds recommended limit of 40°\n";
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
        s->time = sideShotTime;
        graph->addNode(s);
        // Connect to upper courtyard and upper 2 defenses
        graph->addEdge(s, &Field::redCourtyard[2]);
        graph->addEdge(s, &Field::redDefenses[3]);
        graph->addEdge(s, &Field::redDefenses[4]);

        // Lower side
        s = getShotZone(shotRange, 90-sideAngle);
        s->time = sideShotTime;
        graph->addNode(s);
        // Connect to lower courtyard and lower 2 defenses
        graph->addEdge(s, &Field::redCourtyard[0]);
        graph->addEdge(s, &Field::redDefenses[0]);
        graph->addEdge(s, &Field::redDefenses[1]);

        // If the side angle is higher than 40° soft limit
        if(sideAngle > 40){
            warning << "\tSide angle of " << (int)sideAngle << "° exceeds recommended limit of 40°\n";
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

    goalNode = new Fieldpoint(Field::redTower.x+10, Field::redTower.y, Alliance::RED);
    // Connect tower and shotpoints to goal node with 0 distance
    graph->addNode(goalNode);
    graph->addEdge(goalNode, &Field::redTower, 0);
    shotpoints.forEach([this](Shotpoint *s, int i){
        this->graph->addEdge(goalNode, s, 0);
    });

    graph->printAdj();
}

Shotpoint *Robot::getShotZone(int range, int angle){
    int x, y;
    float angleRad = angle*(M_PI/180);
    if(alliance == Alliance::RED){
        x = Field::redTower.x + range*cos(angleRad);
        y = Field::redTower.y + range*sin(angleRad);
    } else if(alliance == Alliance::BLUE){
        x = Field::blueTower.x - range*cos(angleRad);
        y = Field::blueTower.y + range*sin(angleRad);
    } else {
        x = 0;
        y = 0;
    }

    return new Shotpoint(x, y, Alliance::NEUTRAL, Fieldpoint::Type::SHOTNODE);
}


int Robot::crossTime(Defense *d){
    // If it's the low bar, then it is impossible or 1 second
    if(d->defType == Defense::LOW_BAR){
        return canLowbar;
    }
    //Shift the current defense into lower 4 bits, then mask
    return (defenses >> (d->defType*4)) & 0xF;
}

Event Robot::getEvent(){
    Event e;
    e.location = location;
    e.r = this;
    e.time = wakeTime;
    switch(location->type){
        case Fieldpoint::Type::TOWER:
            e.type = Event::Type::SCORE_LOW;
            e.points = LOW_POINTS;
            break;
        case Fieldpoint::Type::SHOTNODE:
            e.type = Event::Type::SCORE_HIGH;
            e.points = HIGH_POINTS;
            break;
        case Fieldpoint::Type::DEFENSE:
            e.type = Event::Type::CROSS;
            e.points = ((Defense *) location)->value;
            break;
    }
    return e;
}

void Robot::navUpdate(LinkedList<Event> *events){
    events->push(getEvent());
}

// bool can_cross(Robot *r, Defenses d){
//     // Mask the defenses to check
//     return (r->defenses >> (int)d*4 & 0xF) != 0;
// }

/*
 * Parse a csv file containing robot information
 * Returns a pointer to the found robot
*/
Robot *Robot::parseCSV(std::string filename){
    // Open the file
    FILE *f = fopen(filename.c_str(), "r"); 
    if(f == NULL){
        std::stringstream s;
        s << "Could not open file " << filename;
        throw file_open_exception(s.str());
    }

    // Buffer for read lines. No line following the correct format will exceed 64 characters
    char line[BUFF_SIZE];

    Robot *bot = new Robot();

    // Remove header line
    fgets (line, BUFF_SIZE, f);
    // Read robot line
    fgets (line, BUFF_SIZE, f);
    // Data order: team,can_low,shot_range,centre_shot_time,side_shot_time,centre_angle,side_angle,low_time,defenses,speed
    int result = sscanf(line, "%d,%d,%d,%d,%d,%d,%d,%d,%lx,%d", 
        &(bot->team),
        &(bot->canLowbar),
        &(bot->shotRange),
        &(bot->centreShotTime),
        &(bot->sideShotTime),
        &(bot->centreAngle),
        &(bot->sideAngle),
        &(bot->lowTime),
        &(bot->defenses),
        &(bot->speed));
    
    // Validate input
    // If less values are read than expected, something went wrong
    if(result != 10){
        std::stringstream s;
        s << "Error while parsing robot " << bot->team << ". Read " << result << " values.";
        throw csv_parsing_exception(s.str());
    }
    // If the bot's speed is 0, then it can't go anywhere and there is no point in simulating
    if(!bot->speed) throw invalid_parameter_exception("Robot's speed is zero, this would prevent any motion. Speed must be at least 1.");
    // If the bot cannot cross any defenses, then there is no point in simulating
    if(!bot->defenses && !bot->canLowbar) throw invalid_parameter_exception("Robot cannot cross any defenses, this would prevent any gameplay. Robot must be able to cross at least one defense");
    // If the bot can't score, then tehre is no point in simulating
    if(!bot->centreShotTime && !bot->sideShotTime && !bot->lowTime) throw invalid_parameter_exception("Robot cannot score, this prevents any gameplay. One scoring time must be nonzero");
    
    // Finish setup
    // Convert from the fpm input to ips for internal use
    bot->speed *= 12/60.0;
    // Set the bot's alliance. Currently this is hardcoded to red but may change in the future
    bot->alliance = Alliance::RED;
    // Set the bot's id. Currently hardcoded but this may change in the future
    bot->id = 0;
    // Initialise the bot's internal field graph
    bot->initGraph();

    return bot;
}