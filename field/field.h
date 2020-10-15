#ifndef FIELD_H
#define FIELD_H
#include <stdbool.h>
#include "Fieldpoint.h"
#include "../game.h"

// Dimensions from this drawing: https://i.imgur.com/1d51oAV.png and game manual https://firstfrc.blob.core.windows.net/frc2016manuals/GameManual/FRC-2016-game-manual-02.pdf 
#define FIELD_WIDTH 320
#define FIELD_LENGTH 650

#define TOWER_OFFSET 12 // Edge of 2ft tower is on centerline

#define DEFENSE_EDGE_OFFSET 192 // Distance from the wall to the edge of the defense
#define DEFENSE_WIDTH 54
#define DEFENSE_LENGTH 24

#define SECRET_PASSAGE_LENGTH 280 // Distance from driver station to end of passage, technically 287, but rounded down for simplicity + padding
#define SECRET_PASSAGE_WIDTH 54 // Width of secret passage

void print_field(bool showdots);
#endif // !FIELD_H