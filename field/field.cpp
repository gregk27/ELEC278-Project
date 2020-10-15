#include "field.h"
#include <stdio.h>
#include <stdbool.h>
#include "../robot.h"

namespace Field {
    // All locations in inches from top-left. Field dimensions take from game manual.
    Fieldpoint RED_TOWER = Fieldpoint(
        TOWER_OFFSET, 
        FIELD_WIDTH/2-TOWER_OFFSET,  // Red tower is above the line
        Alliance::RED, 
        Fieldpoint::Type::TOWER
    );

    Fieldpoint BLUE_TOWER = Fieldpoint(
        FIELD_LENGTH-TOWER_OFFSET, // Place a far end
        FIELD_WIDTH/2 + TOWER_OFFSET, // Blue tower is below the line
        Alliance::BLUE,
        Fieldpoint::Type::TOWER
    );

    Fieldpoint RED_DEFENSES[5] = {
        Fieldpoint(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(0*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(1*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(2*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(3*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(4*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::RED,
            Fieldpoint::Type::DEFENSE
        )
    };

    Fieldpoint bluePassage0 = Fieldpoint(
        0*SECRET_PASSAGE_LENGTH/3,
        SECRET_PASSAGE_WIDTH/2,
        Alliance::BLUE,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint bluePassage1 = Fieldpoint(
        SECRET_PASSAGE_LENGTH/3,
        SECRET_PASSAGE_WIDTH/2,
        Alliance::BLUE,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint bluePassage2 = Fieldpoint(
        2*SECRET_PASSAGE_LENGTH/3,
        SECRET_PASSAGE_WIDTH/2,
        Alliance::BLUE,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint bluePassage3 = Fieldpoint(
        3*SECRET_PASSAGE_LENGTH/3,
        SECRET_PASSAGE_WIDTH/2,
        Alliance::BLUE,
        Fieldpoint::Type::RESTRICTED
    );

    Fieldpoint BLUE_DEFENSES[5] = {
        Fieldpoint(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (0*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (1*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (2*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (3*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (4*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            Alliance::BLUE,
            Fieldpoint::Type::DEFENSE
        ),
    };

    Fieldpoint redPassage0 = Fieldpoint(
        FIELD_LENGTH-0*SECRET_PASSAGE_LENGTH/3,
        FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
        Alliance::RED,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint redPassage1 = Fieldpoint(
        FIELD_LENGTH-SECRET_PASSAGE_LENGTH/3,
        FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
        Alliance::RED,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint redPassage2 = Fieldpoint(
        FIELD_LENGTH-2*SECRET_PASSAGE_LENGTH/3,
        FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
        Alliance::RED,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint redPassage3 = Fieldpoint(
        FIELD_LENGTH-3*SECRET_PASSAGE_LENGTH/3,
        FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
        Alliance::RED,
        Fieldpoint::Type::RESTRICTED
    );
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

    out[Field::RED_TOWER.x/10][Field::RED_TOWER.y/10][0]='T';
    out[Field::RED_TOWER.x/10][Field::RED_TOWER.y/10][1]='R';
    out[Field::RED_TOWER.x/10][Field::RED_TOWER.y/10][2]='R';
    
    out[Field::BLUE_TOWER.x/10][Field::BLUE_TOWER.y/10][0]='T';
    out[Field::BLUE_TOWER.x/10][Field::BLUE_TOWER.y/10][1]='R';
    out[Field::BLUE_TOWER.x/10][Field::BLUE_TOWER.y/10][2]='B';

    out[Field::bluePassage0.x/10][Field::bluePassage0.y/10][0]='B';
    out[Field::bluePassage0.x/10][Field::bluePassage0.y/10][1]='P';
    out[Field::bluePassage0.x/10][Field::bluePassage0.y/10][2]='S';

    out[Field::bluePassage1.x/10][Field::bluePassage1.y/10][0]='B';
    out[Field::bluePassage1.x/10][Field::bluePassage1.y/10][1]='P';
    out[Field::bluePassage1.x/10][Field::bluePassage1.y/10][2]='S';
    
    out[Field::bluePassage2.x/10][Field::bluePassage2.y/10][0]='B';
    out[Field::bluePassage2.x/10][Field::bluePassage2.y/10][1]='P';
    out[Field::bluePassage2.x/10][Field::bluePassage2.y/10][2]='S';
    
    out[Field::bluePassage3.x/10][Field::bluePassage3.y/10][0]='B';
    out[Field::bluePassage3.x/10][Field::bluePassage3.y/10][1]='P';
    out[Field::bluePassage3.x/10][Field::bluePassage3.y/10][2]='S';

    for(int i=0; i<5; i++){
        int x = Field::RED_DEFENSES[i].x/10;
        int y = Field::RED_DEFENSES[i].y/10;
        out[x][y][0]='D';
        out[x][y][1]='R';
        out[x][y][2]=i+'0';
    }


    out[Field::redPassage0.x/10][Field::redPassage0.y/10][0]='B';
    out[Field::redPassage0.x/10][Field::redPassage0.y/10][1]='P';
    out[Field::redPassage0.x/10][Field::redPassage0.y/10][2]='S';

    out[Field::redPassage1.x/10][Field::redPassage1.y/10][0]='B';
    out[Field::redPassage1.x/10][Field::redPassage1.y/10][1]='P';
    out[Field::redPassage1.x/10][Field::redPassage1.y/10][2]='S';
    
    out[Field::redPassage2.x/10][Field::redPassage2.y/10][0]='B';
    out[Field::redPassage2.x/10][Field::redPassage2.y/10][1]='P';
    out[Field::redPassage2.x/10][Field::redPassage2.y/10][2]='S';
    
    out[Field::redPassage3.x/10][Field::redPassage3.y/10][0]='B';
    out[Field::redPassage3.x/10][Field::redPassage3.y/10][1]='P';
    out[Field::redPassage3.x/10][Field::redPassage3.y/10][2]='S';

    for(int i=0; i<5; i++){
        int x = Field::BLUE_DEFENSES[i].x/10;
        int y = Field::BLUE_DEFENSES[i].y/10;
        out[x][y][0]='D';
        out[x][y][1]='R';
        out[x][y][2]=i+'0';
    }


    for(int i=0; i<FIELD_WIDTH/10; i++){
        printf("%03d|",i*10);
        for(int j=0; j<FIELD_LENGTH/10; j++){
            printf("%c%c%c",out[j][i][0],out[j][i][1],out[j][i][2]);
        }
        printf("|\n");
    }
}