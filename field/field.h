/**
 * field.cpp/h
 * These files contains the the code used to generate the field graph
 * Pointers to these variables used throughout code for navigation
 * 
 * Constant values defined in header are derived from official field drawings, with small tweaks to improve positioning in GUI
 * All values are in inches, as those are the provided units
 * 
 * The following drawing was used in addition to the Game Manual
 * https://i.imgur.com/1d51oAV.png
 * https://firstfrc.blob.core.windows.net/frc2016manuals/GameManual/FRC-2016-game-manual-02.pdf 
 */

#ifndef FIELD_H
#define FIELD_H
#include <stdbool.h>
#include <vector>
#include "Fieldpoint.h"
#include "../game.h"
#include "../utils/LinkedList.h"
#include "../utils/Graph.h"

// Overall width of the field (y axis)
#define FIELD_WIDTH 320
// Overall legth of the field (x axis)
#define FIELD_LENGTH 650

// X Offset from outer wall to tower centre, and centre to nodes
#define TOWER_OFFSET_X 6
// Y Offset used betwen tower centre and nodes. 2x Y offset from centreline
#define TOWER_OFFSET_Y 24

// X position of centre of red tower
#define RED_TOWER_X TOWER_OFFSET_X
// Y position of centre of red tower, slightly above middle
#define RED_TOWER_Y FIELD_WIDTH/2-TOWER_OFFSET_Y/2
// X position of centre of blue tower
#define BLUE_TOWER_X FIELD_LENGTH-TOWER_OFFSET_X
// Y position of centre of blue tower, slightly below middle
#define BLUE_TOWER_Y FIELD_WIDTH/2+TOWER_OFFSET_Y/2

// Distance from the wall to the edge of the defense, +10" to better line up on GUI
#define DEFENSE_EDGE_OFFSET 202 
// Width of a defense on the field (y axis)
#define DEFENSE_WIDTH 54
// Length of a defense on the field (x axis)
#define DEFENSE_LENGTH 24

// Distance from driver station to end of passage, technically 287, but rounded down for simplicity + padding
#define SECRET_PASSAGE_LENGTH 240 
// Width of secret passage
#define SECRET_PASSAGE_WIDTH 54 

// Distance from the wall for courtyard nav points
#define COURTYARD_OFFSET 72 

// Number of nodes in defense array
#define DEFENSE_COUNT 5 
// Number of nodes in passage array
#define PASSAGE_COUNT 4 
// Number of nodes in courtyard array
#define COURTYARD_COUNT 3 
// NUmber of nodes in the centre ball array
#define CENTRE_BALL_COUNT 6 

/**
 * Namespace with variables representing field elements
 * Also contains graph intialisation and output functions
 */
namespace Field {
    /**
     * Structre representing edge between nodes
    */
    typedef struct {
        /**
         * Fieldpoint at the end of the edge
         */
        Fieldpoint *end;
        /**
         * Distance between the nodes 
         */
        int distance;
    } Edge;

    // Top goal of the red tower
    extern Fieldpoint redTowerTop;
    // Bottom goal of the red tower
    extern Fieldpoint redTowerBottom;
    // Defenses crossed by red alliance
    extern Defense redDefenses[DEFENSE_COUNT];
    // Passage used by red alliance
    extern Fieldpoint redPassage[PASSAGE_COUNT];
    // Courtyard used by red alliance
    extern Fieldpoint redCourtyard[COURTYARD_COUNT];

    // Top goal of the blue tower
    extern Fieldpoint blueTowerTop;
    // Bottom goal of the blue tower
    extern Fieldpoint blueTowerBottom;
    // Defenses crossed by blue alliance
    extern Defense blueDefenses[DEFENSE_COUNT];
    // Passage used by blue alliance
    extern Fieldpoint bluePassage[PASSAGE_COUNT];
    // Cortyard used by blue alliance
    extern Fieldpoint blueCourtyard[COURTYARD_COUNT];

    // Nodes at the centre of the map, placed over the pre-populated balls
    extern Fieldpoint centreBalls[CENTRE_BALL_COUNT];

    /**
     * Create a new Graph instance from field data
     * Returns: A Graph pointer built from field data
    */
    Graph *initGraph();
    
    /**
     * Export graph to GraphML file formatted for use with https://yworks.com/yed-live
     * - g:         Graph to export
     * - filename:  Name of output file, needs extension
     */
    void toGraphML(Graph *g, const char* filename);
    
    /**
     * Print graph to console
     * - g:         Graph to print 
     * - showDots:  If true, will fill empty space with dots
     * 
     * Deprecated, use toGraphML instead.
     */
    void print(Graph *g, bool showdots);
};

#endif // !FIELD_H