#include <stdio.h>
#include <stdbool.h>
#include <vector>
#include "../robot.h"
#include "../utils/LinkedList.h"
#include "../utils/Graph.h"
#include "field.h"

namespace Field {

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

    /**
     * Initialise a graph of the field
     * This will automatically build the graph from the various predefined fieldpoints
     * 
     */
    Graph *initGraph(){
        Graph *g = new Graph();
        g->addNode(&redTower);
        g->addNodes(redDefenses, DEFENSE_COUNT);
        g->addNodes(redPassage, PASSAGE_COUNT);
        g->addNodes(redCourtyard, COURTYARD_COUNT);

        g->addNode(&blueTower);
        g->addNodes(blueDefenses, DEFENSE_COUNT);
        g->addNodes(bluePassage, PASSAGE_COUNT);
        g->addNodes(blueCourtyard, COURTYARD_COUNT);

        g->addNodes(centreBalls, CENTRE_BALL_COUNT);

        /**
         * RED NODES
         */
        {
            // Add edges for red courtyard nodes
            g->addEdge(&redCourtyard[0], &redTower);
            g->addEdge(&redCourtyard[0], &redDefenses[0]);
            g->addEdge(&redCourtyard[0], &redCourtyard[1]);
            g->addEdge(&redCourtyard[0], &redCourtyard[2]);
            g->addEdge(&redCourtyard[1], &redDefenses[0]);
            g->addEdge(&redCourtyard[1], &redDefenses[1]);
            g->addEdge(&redCourtyard[1], &redDefenses[2]);
            g->addEdge(&redCourtyard[1], &redDefenses[3]);
            g->addEdge(&redCourtyard[1], &redDefenses[4]);
            g->addEdge(&redCourtyard[2], &redTower);
            g->addEdge(&redCourtyard[2], &redDefenses[3]);
            g->addEdge(&redCourtyard[2], &redDefenses[4]);
            g->addEdge(&redCourtyard[1], &redCourtyard[0]);
            g->addEdge(&redCourtyard[1], &redCourtyard[2]);

            // Add edges for red defenses and centre field
            g->addEdge(&redDefenses[0], &centreBalls[5]);
            g->addEdge(&redDefenses[1], &centreBalls[5]);
            g->addEdge(&redDefenses[1], &centreBalls[4]);
            g->addEdge(&redDefenses[1], &centreBalls[3]);
            g->addEdge(&redDefenses[2], &centreBalls[3]);
            g->addEdge(&redDefenses[2], &centreBalls[2]);
            g->addEdge(&redDefenses[3], &centreBalls[2]);
            g->addEdge(&redDefenses[3], &centreBalls[1]);
            g->addEdge(&redDefenses[4], &centreBalls[1]);
            g->addEdge(&redDefenses[4], &centreBalls[0]);

            // Add edges for red secret passage
            g->addEdge(&redPassage[0], &redPassage[1]);
            g->addEdge(&redPassage[1], &redPassage[2]);
            g->addEdge(&redPassage[2], &redPassage[3]);
            g->addEdge(&redPassage[3], &centreBalls[5]);
            g->addEdge(&redPassage[3], &centreBalls[4]);
            g->addEdge(&redPassage[3], &centreBalls[3]);
        }

        /**
         * BLUE NODES
         * CentreBalls are flipped, so indices are 5-redVal
         */
        {
            // Add edges for blue courtyard nodes
            g->addEdge(&blueCourtyard[0], &blueTower);
            g->addEdge(&blueCourtyard[0], &blueDefenses[0]);
            g->addEdge(&blueCourtyard[0], &blueCourtyard[1]);
            g->addEdge(&blueCourtyard[0], &blueCourtyard[2]);
            g->addEdge(&blueCourtyard[1], &blueDefenses[0]);
            g->addEdge(&blueCourtyard[1], &blueDefenses[1]);
            g->addEdge(&blueCourtyard[1], &blueDefenses[2]);
            g->addEdge(&blueCourtyard[1], &blueDefenses[3]);
            g->addEdge(&blueCourtyard[1], &blueDefenses[4]);
            g->addEdge(&blueCourtyard[2], &blueTower);
            g->addEdge(&blueCourtyard[2], &blueDefenses[3]);
            g->addEdge(&blueCourtyard[2], &blueDefenses[4]);
            g->addEdge(&blueCourtyard[1], &blueCourtyard[0]);
            g->addEdge(&blueCourtyard[1], &blueCourtyard[2]);

            // Add edges for blue defenses and centre field
            g->addEdge(&blueDefenses[0], &centreBalls[5-5]);
            g->addEdge(&blueDefenses[1], &centreBalls[5-5]);
            g->addEdge(&blueDefenses[1], &centreBalls[5-4]);
            g->addEdge(&blueDefenses[1], &centreBalls[5-3]);
            g->addEdge(&blueDefenses[2], &centreBalls[5-3]);
            g->addEdge(&blueDefenses[2], &centreBalls[5-2]);
            g->addEdge(&blueDefenses[3], &centreBalls[5-2]);
            g->addEdge(&blueDefenses[3], &centreBalls[5-1]);
            g->addEdge(&blueDefenses[4], &centreBalls[5-1]);
            g->addEdge(&blueDefenses[4], &centreBalls[5-0]);

            // Add edges for blue secret passage
            g->addEdge(&bluePassage[0], &bluePassage[1]);
            g->addEdge(&bluePassage[1], &bluePassage[2]);
            g->addEdge(&bluePassage[2], &bluePassage[3]);
            g->addEdge(&bluePassage[3], &centreBalls[5-5]);
            g->addEdge(&bluePassage[3], &centreBalls[5-4]);
            g->addEdge(&bluePassage[3], &centreBalls[5-3]);
        }

        /**
         * NEUTRAL
         */
        {
            // Connect centreBalls to eachother
            g->addEdge(&centreBalls[0], &centreBalls[1]);
            g->addEdge(&centreBalls[1], &centreBalls[2]);
            g->addEdge(&centreBalls[2], &centreBalls[3]);
            g->addEdge(&centreBalls[3], &centreBalls[4]);
            g->addEdge(&centreBalls[4], &centreBalls[5]);
        }
        
        g->printAdj();
        return g;
    }

    void print(Graph *g, bool showdots){
        char out[FIELD_LENGTH/10][FIELD_WIDTH/10][3];
        for(int i=0; i<FIELD_WIDTH/10; i++){
            for(int j=0; j<FIELD_LENGTH/10; j++){
                out[j][i][0]=showdots ? '.' : ' ';
                out[j][i][1]=' ';
                out[j][i][2]=' ';
            }
        }

        int x,y;
        for(int i = 0; i<g->nodes.size(); i++){
            x = g->nodes[i]->x/10;
            y = g->nodes[i]->y/10;

            // Set alliance letter
            switch(g->nodes[i]->alliance){
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
            switch(g->nodes[i]->type){
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
                case Fieldpoint::Type::SHOTNODE:
                    out[x][y][1]='S';
                    out[x][y][2]='N';
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
}