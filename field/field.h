#ifndef FIELD_H
#define FIELD_H
#include <stdbool.h>
#include <vector>
#include "Fieldpoint.h"
#include "../game.h"

// Dimensions from this drawing: https://i.imgur.com/1d51oAV.png and game manual https://firstfrc.blob.core.windows.net/frc2016manuals/GameManual/FRC-2016-game-manual-02.pdf 
#define FIELD_WIDTH 320
#define FIELD_LENGTH 650

#define TOWER_OFFSET 12 // Edge of 2ft tower is on centerline

#define DEFENSE_EDGE_OFFSET 192 // Distance from the wall to the edge of the defense
#define DEFENSE_WIDTH 54
#define DEFENSE_LENGTH 24

#define SECRET_PASSAGE_LENGTH 240 // Distance from driver station to end of passage, technically 287, but rounded down for simplicity + padding
#define SECRET_PASSAGE_WIDTH 54 // Width of secret passage

#define DEFENSE_COUNT 5 // Number of nodes in defense array
#define PASSAGE_COUNT 4 // Number of nodes in passage array

void print_field(bool showdots);

// All locations in inches from top-left. Field dimensions take from game manual.
// Namespace with field graph and functions
namespace Field {
    // Vector with all nodes
    extern std::vector<Fieldpoint *> nodes;
    
    extern Fieldpoint redTower;
    extern Defense redDefenses[DEFENSE_COUNT];
    extern Fieldpoint redPassage[PASSAGE_COUNT];

    extern Fieldpoint blueTower;
    extern Defense blueDefenses[DEFENSE_COUNT];
    extern Fieldpoint bluePassage[PASSAGE_COUNT];

    void init();
}

#endif // !FIELD_H