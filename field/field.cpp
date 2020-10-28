#include "field.h"
#include <stdio.h>
#include <stdbool.h>
#include <vector>
#include <math.h>
#include "../robot.h"
#include "../utils/LinkedList.h"


namespace Field {
    LinkedList<Fieldpoint *> nodes;
    LinkedList<LinkedList<Edge>*> adjacency;

    Fieldpoint redTower = Fieldpoint(
        TOWER_OFFSET, 
        FIELD_WIDTH/2-TOWER_OFFSET,  // Red tower is above the line
        Alliance::RED, 
        Fieldpoint::Type::TOWER
    );

    Defense redDefenses[DEFENSE_COUNT] = {
        Defense(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(0*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(1*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(2*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(3*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(4*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        )
    };

    Fieldpoint redPassage[PASSAGE_COUNT] = {
        Fieldpoint(
            FIELD_LENGTH-0*SECRET_PASSAGE_LENGTH/3,
            FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
            Alliance::RED,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            FIELD_LENGTH-SECRET_PASSAGE_LENGTH/3,
            FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
            Alliance::RED,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            FIELD_LENGTH-2*SECRET_PASSAGE_LENGTH/3,
            FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
            Alliance::RED,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            FIELD_LENGTH-3*SECRET_PASSAGE_LENGTH/3,
            FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
            Alliance::RED,
            Fieldpoint::Type::RESTRICTED
        )
    };

    Fieldpoint redCourtyard[COURTYARD_COUNT] = {
        Fieldpoint(
            COURTYARD_OFFSET,
            redDefenses[1].y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            COURTYARD_OFFSET*1.5,
            redTower.y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            COURTYARD_OFFSET,
            redDefenses[4].y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        )
    };

    Fieldpoint blueTower = Fieldpoint(
        FIELD_LENGTH-TOWER_OFFSET, // Place a far end
        FIELD_WIDTH/2 + TOWER_OFFSET, // Blue tower is below the line
        Alliance::BLUE,
        Fieldpoint::Type::TOWER
    );

    Defense blueDefenses[DEFENSE_COUNT] = {
        Defense(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (0*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (1*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (2*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (3*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Defense(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (4*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
    };

    Fieldpoint bluePassage[PASSAGE_COUNT] = {
        Fieldpoint(
            0*SECRET_PASSAGE_LENGTH/3,
            SECRET_PASSAGE_WIDTH/2,
            Alliance::BLUE,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            SECRET_PASSAGE_LENGTH/3,
            SECRET_PASSAGE_WIDTH/2,
            Alliance::BLUE,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            2*SECRET_PASSAGE_LENGTH/3,
            SECRET_PASSAGE_WIDTH/2,
            Alliance::BLUE,
            Fieldpoint::Type::RESTRICTED
        ),
        Fieldpoint(
            3*SECRET_PASSAGE_LENGTH/3,
            SECRET_PASSAGE_WIDTH/2,
            Alliance::BLUE,
            Fieldpoint::Type::RESTRICTED
        )
    };

    Fieldpoint blueCourtyard[COURTYARD_COUNT] = {
        Fieldpoint(
            FIELD_LENGTH-COURTYARD_OFFSET,
            blueDefenses[1].y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH-COURTYARD_OFFSET*1.5,
            blueTower.y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH-COURTYARD_OFFSET,
            blueDefenses[4].y,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        )
    };

    Fieldpoint centreBalls[CENTRE_BALL_COUNT] = {
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*1,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*2,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*3,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*4,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*5,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        ),
        Fieldpoint(
            FIELD_LENGTH/2,
            FIELD_WIDTH/7*6,
            Alliance::NEUTRAL,
            Fieldpoint::Type::NODE
        )
    };

    void addNode(Fieldpoint *f){
        f->index = nodes.push(f);
    }

    void addNodes(Fieldpoint f[], int count){
        for(int i=0; i<count; i++){
            addNode(&f[i]);
        }
    }
    
    void addNodes(Defense f[], int count){
        for(int i=0; i<count; i++){
            addNode(&f[i]);
        }
    }

    void addEdge(Fieldpoint a, Fieldpoint b){
        Edge e;
        e.end = &b;
        e.distance = sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
        adjacency[a.index]->push(e);
        e.end = &a;
        adjacency[b.index]->push(e);
    }

    void printAdj(){
        adjacency.forEach([](LinkedList<Edge> *l, int i)->void {
            printf("%d->", i);
            l->forEach([](Edge e, int i)->void {
                printf("%d:%d,", e.end->index, e.distance);
            });
            printf("\n");
        });
    }

    void init(){
        addNode(&redTower);
        addNodes(redDefenses, DEFENSE_COUNT);
        addNodes(redPassage, PASSAGE_COUNT);
        addNodes(redCourtyard, COURTYARD_COUNT);

        addNode(&blueTower);
        addNodes(blueDefenses, DEFENSE_COUNT);
        addNodes(bluePassage, PASSAGE_COUNT);
        addNodes(blueCourtyard, COURTYARD_COUNT);

        addNodes(centreBalls, CENTRE_BALL_COUNT);
        // Build up the list
        nodes.forEach([](Fieldpoint *f, int i)->void {
            adjacency.push(new LinkedList<Edge>);
        });

        /**
         * RED NODES
         */
        // Add edges for red courtyard nodes
        addEdge(redCourtyard[0], redTower);
        addEdge(redCourtyard[0], redDefenses[0]);
        addEdge(redCourtyard[0], redCourtyard[1]);
        addEdge(redCourtyard[0], redCourtyard[2]);
        addEdge(redCourtyard[1], redDefenses[0]);
        addEdge(redCourtyard[1], redDefenses[1]);
        addEdge(redCourtyard[1], redDefenses[2]);
        addEdge(redCourtyard[1], redDefenses[3]);
        addEdge(redCourtyard[1], redDefenses[4]);
        addEdge(redCourtyard[2], redTower);
        addEdge(redCourtyard[2], redDefenses[3]);
        addEdge(redCourtyard[2], redDefenses[4]);
        addEdge(redCourtyard[1], redCourtyard[0]);
        addEdge(redCourtyard[1], redCourtyard[2]);

        // Add edges for red defenses and centre field
        addEdge(redDefenses[0], centreBalls[5]);
        addEdge(redDefenses[1], centreBalls[5]);
        addEdge(redDefenses[1], centreBalls[4]);
        addEdge(redDefenses[1], centreBalls[3]);
        addEdge(redDefenses[2], centreBalls[3]);
        addEdge(redDefenses[2], centreBalls[2]);
        addEdge(redDefenses[3], centreBalls[2]);
        addEdge(redDefenses[3], centreBalls[1]);
        addEdge(redDefenses[4], centreBalls[1]);
        addEdge(redDefenses[4], centreBalls[0]);

        // Add edges for red secret passage
        addEdge(redPassage[0], redPassage[1]);
        addEdge(redPassage[1], redPassage[2]);
        addEdge(redPassage[2], redPassage[3]);
        addEdge(redPassage[3], centreBalls[5]);
        addEdge(redPassage[3], centreBalls[4]);
        addEdge(redPassage[3], centreBalls[3]);


        /**
         * BLUE NODES
         * CentreBalls are flipped, so indices are 5-redVal
         */
        // Add edges for blue courtyard nodes
        addEdge(blueCourtyard[0], blueTower);
        addEdge(blueCourtyard[0], blueDefenses[0]);
        addEdge(blueCourtyard[0], blueCourtyard[1]);
        addEdge(blueCourtyard[0], blueCourtyard[2]);
        addEdge(blueCourtyard[1], blueDefenses[0]);
        addEdge(blueCourtyard[1], blueDefenses[1]);
        addEdge(blueCourtyard[1], blueDefenses[2]);
        addEdge(blueCourtyard[1], blueDefenses[3]);
        addEdge(blueCourtyard[1], blueDefenses[4]);
        addEdge(blueCourtyard[2], blueTower);
        addEdge(blueCourtyard[2], blueDefenses[3]);
        addEdge(blueCourtyard[2], blueDefenses[4]);
        addEdge(blueCourtyard[1], blueCourtyard[0]);
        addEdge(blueCourtyard[1], blueCourtyard[2]);

        // Add edges for blue defenses and centre field
        addEdge(blueDefenses[0], centreBalls[5-5]);
        addEdge(blueDefenses[1], centreBalls[5-5]);
        addEdge(blueDefenses[1], centreBalls[5-4]);
        addEdge(blueDefenses[1], centreBalls[5-3]);
        addEdge(blueDefenses[2], centreBalls[5-3]);
        addEdge(blueDefenses[2], centreBalls[5-2]);
        addEdge(blueDefenses[3], centreBalls[5-2]);
        addEdge(blueDefenses[3], centreBalls[5-1]);
        addEdge(blueDefenses[4], centreBalls[5-1]);
        addEdge(blueDefenses[4], centreBalls[5-0]);

        // Add edges for blue secret passage
        addEdge(bluePassage[0], bluePassage[1]);
        addEdge(bluePassage[1], bluePassage[2]);
        addEdge(bluePassage[2], bluePassage[3]);
        addEdge(bluePassage[3], centreBalls[5-5]);
        addEdge(bluePassage[3], centreBalls[5-4]);
        addEdge(bluePassage[3], centreBalls[5-3]);


        /**
         * NEUTRAL
         */
        // Connect centreBalls to eachother
        addEdge(centreBalls[0], centreBalls[1]);
        addEdge(centreBalls[1], centreBalls[2]);
        addEdge(centreBalls[2], centreBalls[3]);
        addEdge(centreBalls[3], centreBalls[4]);
        addEdge(centreBalls[4], centreBalls[5]);

        printAdj();
    }
}

void print_field(bool showdots){
    char out[FIELD_LENGTH/10][FIELD_WIDTH/10][3];
    for(int i=0; i<FIELD_WIDTH/10; i++){
        for(int j=0; j<FIELD_LENGTH/10; j++){
            out[j][i][0]=showdots ? '.' : ' ';
            out[j][i][1]=' ';
            out[j][i][2]=' ';
        }
    }

    int x,y;
    for(int i = 0; i<Field::nodes.size(); i++){
        x = Field::nodes[i]->x/10;
        y = Field::nodes[i]->y/10;

        // Set alliance letter
        switch(Field::nodes[i]->alliance){
            case Alliance::RED:
                out[x][y][0] = 'R';
                break;
            case Alliance::BLUE:
                out[x][y][0] = 'B';
                break;
            default:
                out[x][y][0] = ' ';
                break;
        }

        // Set type letters
        switch(Field::nodes[i]->type){
            case Fieldpoint::Type::TOWER:
                out[x][y][1]='T';
                out[x][y][2]='W';
                break;
            case Fieldpoint::Type::DEFENSE:
                out[x][y][1]='D';
                out[x][y][2]='F';
                break;
            case Fieldpoint::Type::RESTRICTED:
                out[x][y][1]='N';
                out[x][y][2]='R';
                break;
            default:
                out[x][y][1]='N';
                out[x][y][2]=' ';
                break;
        }
    }

    for(int i=0; i<FIELD_WIDTH/10; i++){
        printf("%03d|",i*10);
        for(int j=0; j<FIELD_LENGTH/10; j++){
            printf("%c%c%c",out[j][i][0],out[j][i][1],out[j][i][2]);
        }
        printf("|\n");
    }
}