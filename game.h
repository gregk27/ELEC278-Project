#ifndef GAME_H
#define GAME_H
#include <string>
#include "utils/Graph.h"
#include "Field/Fieldpoint.h"

// Forward declare classes as they are only used for pointers
class Robot;
class Fieldpoint;

extern const int HIGH_POINTS;
extern const int LOW_POINTS;

extern const int CROSS_POINTS;
extern const int BASE_POINTS;

enum class Alliance {
    RED, BLUE, NEUTRAL
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
        Fieldpoint *location;
        // Type of the event
        Type type;
        // Point change from the event
        int points;
        // Timestamp of the event, in seconds
        float time;

        Graph::DijkstraNode *n;

        std::string toString();
};

#endif // !GAME_H`