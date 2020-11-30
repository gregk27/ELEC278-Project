/**
 * game.cpp/h
 * These files contain constants used for game behaviour and the Event class
 */

#ifndef GAME_H
#define GAME_H
#include <string>
#include "utils/Graph.h"
#include "Field/Fieldnode.h"

// Forward declare classes as they are only used for pointers
class Robot;
class Fieldnode;

// Points earned for high goal
extern const int HIGH_POINTS;
// Points earned for low goa;
extern const int LOW_POINTS;

// Points earned for crossing a defense
extern const int CROSS_POINTS;
// Initial points available from the defense
extern const int BASE_POINTS;

// Enum representing alliance affiliation
enum class Alliance {
    // Affiliated with red alliance
    RED, 
    // Affiliated with blue alliance
    BLUE, 
    // Affiliated with neither alliance
    NEUTRAL
};

// Structure represnting a simulation event
class Event {
    public:
        // Types of events that can be logged
        enum class Type {
            // Robot passed through a node
            PASSTHROUGH,
            // Robot crossed a defense
            CROSS,
            // Robot intaked a ball
            INTAKE,
            // Robot scored a high goal
            SCORE_HIGH,
            // Robot scored a low goal
            SCORE_LOW
        };


        // Robot that made the event
        Robot *r;
        // Location of the event
        Fieldnode *location;
        // Type of the event
        Type type;
        // Point change from the event
        int points;
        // Timestamp of the event, in seconds
        float time;

        // Last DijsktraNode in the planned following the event
        Graph::DijkstraNode *path;

        /**
         * Get a string representation of the event
         * The format is designed for use with the console event list.
         * 
         * Returns: String representation of event
         */
        std::string toString();
};

#endif // !GAME_H`