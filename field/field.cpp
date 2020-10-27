#include "field.h"
#include <stdio.h>
#include <stdbool.h>
#include <vector>
#include "../robot.h"


namespace Field {
    std::vector<Fieldpoint *> nodes;

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

    void addNode(Fieldpoint *f){
        nodes.push_back(f);
        f->index = nodes.size()-1;
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

    void init(){
        addNode(&redTower);
        addNodes(redDefenses, DEFENSE_COUNT);
        addNodes(redPassage, PASSAGE_COUNT);

        addNode(&blueTower);
        addNodes(blueDefenses, DEFENSE_COUNT);
        addNodes(bluePassage, PASSAGE_COUNT);

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