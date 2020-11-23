#ifndef GAME_H
#define GAME_H
#include <string>
#include "Field/Fieldpoint.h"

// Forward declare classes as they are only used for pointers
class Robot;
class Fieldpoint;

const int HIGH_POINTS = 5;
const int LOW_POINTS = 2;

const int CROSS_POINTS = 5;
const int BASE_POINTS = CROSS_POINTS*2;

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

        std::string toString();
};

#endif // !GAME_H`