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

enum class Alliance {
    RED, BLUE, NEUTRAL
};

// Types of events that can be logged
enum class EventType {
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

// Structure represnting a simulation event
struct Event {
    // Robot that made the event
    Robot *r;
    // Location of the event
    Fieldpoint *location;
    // Type of the event
    EventType type;
    // Point change from the event
    int points;
    // Timestamp of the event, in seconds
    int time;
};

#endif // !GAME_H`