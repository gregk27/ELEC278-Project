#ifndef FIELD_H
#define FIELD_H
#include <stdbool.h>
#include "Fieldpoint.h"
#include "../robot.h"

// Dimensions from this drawing: https://i.imgur.com/1d51oAV.png and game manual https://firstfrc.blob.core.windows.net/frc2016manuals/GameManual/FRC-2016-game-manual-02.pdf 
#define FIELD_WIDTH 320
#define FIELD_LENGTH 650

#define TOWER_OFFSET 12 // Edge of 2ft tower is on centerline

#define DEFENSE_EDGE_OFFSET 192 // Distance from the wall to the edge of the defense
#define DEFENSE_WIDTH 54
#define DEFENSE_LENGTH 24

#define SECRET_PASSAGE_LENGTH 280 // Distance from driver station to end of passage, technically 287, but rounded down for simplicity + padding
#define SECRET_PASSAGE_WIDTH 54 // Width of secret passage

namespace Field {
    // All locations in inches from top-left. Field dimensions take from game manual.
    Fieldpoint RED_TOWER = Fieldpoint(
        TOWER_OFFSET, 
        FIELD_WIDTH/2-TOWER_OFFSET,  // Red tower is above the line
        RED_ALLIANCE, 
        Fieldpoint::Type::TOWER
    );

    Fieldpoint BLUE_TOWER = Fieldpoint(
        FIELD_LENGTH-TOWER_OFFSET, // Place a far end
        FIELD_WIDTH/2 + TOWER_OFFSET, // Blue tower is below the line
        BLUE_ALLIANCE,
        Fieldpoint::Type::TOWER
    );

    Fieldpoint RED_DEFENSES[5] = {
        Fieldpoint(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(0*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            RED_ALLIANCE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(1*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            RED_ALLIANCE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(2*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            RED_ALLIANCE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(3*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            RED_ALLIANCE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            DEFENSE_EDGE_OFFSET+DEFENSE_LENGTH/2,
            FIELD_WIDTH-(4*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            RED_ALLIANCE,
            Fieldpoint::Type::DEFENSE
        )
    };

    Fieldpoint bluePassage0 = Fieldpoint(
        0*SECRET_PASSAGE_LENGTH/3,
        SECRET_PASSAGE_WIDTH/2,
        BLUE_ALLIANCE,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint bluePassage1 = Fieldpoint(
        SECRET_PASSAGE_LENGTH/3,
        SECRET_PASSAGE_WIDTH/2,
        BLUE_ALLIANCE,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint bluePassage2 = Fieldpoint(
        2*SECRET_PASSAGE_LENGTH/3,
        SECRET_PASSAGE_WIDTH/2,
        BLUE_ALLIANCE,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint bluePassage3 = Fieldpoint(
        3*SECRET_PASSAGE_LENGTH/3,
        SECRET_PASSAGE_WIDTH/2,
        BLUE_ALLIANCE,
        Fieldpoint::Type::RESTRICTED
    );

    Fieldpoint BLUE_DEFENSES[5] = {
        Fieldpoint(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (0*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            BLUE_ALLIANCE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (1*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            BLUE_ALLIANCE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (2*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            BLUE_ALLIANCE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (3*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            BLUE_ALLIANCE,
            Fieldpoint::Type::DEFENSE
        ),
        Fieldpoint(
            FIELD_LENGTH-DEFENSE_EDGE_OFFSET-DEFENSE_LENGTH/2,
            (4*DEFENSE_WIDTH+DEFENSE_WIDTH/2),
            BLUE_ALLIANCE,
            Fieldpoint::Type::DEFENSE
        ),
    };

    Fieldpoint redPassage0 = Fieldpoint(
        FIELD_LENGTH-0*SECRET_PASSAGE_LENGTH/3,
        FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
        RED_ALLIANCE,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint redPassage1 = Fieldpoint(
        FIELD_LENGTH-SECRET_PASSAGE_LENGTH/3,
        FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
        RED_ALLIANCE,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint redPassage2 = Fieldpoint(
        FIELD_LENGTH-2*SECRET_PASSAGE_LENGTH/3,
        FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
        RED_ALLIANCE,
        Fieldpoint::Type::RESTRICTED
    );
    Fieldpoint redPassage3 = Fieldpoint(
        FIELD_LENGTH-3*SECRET_PASSAGE_LENGTH/3,
        FIELD_WIDTH-SECRET_PASSAGE_WIDTH/2,
        RED_ALLIANCE,
        Fieldpoint::Type::RESTRICTED
    );
}

void print_field(bool showdots);
#endif // !FIELD_H