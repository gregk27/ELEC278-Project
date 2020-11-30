/**
 * game.cpp/h
 * These files contain constants used for game behaviour and the Event class
 */

#include <string>
#include <sstream>
#include <iomanip>
#include "game.h"
#include "robot.h"

const int HIGH_POINTS = 5;
const int LOW_POINTS = 2;

const int CROSS_POINTS = 5;
const int BASE_POINTS = CROSS_POINTS*2;

using namespace std;

string Event::toString(){
    stringstream s, msg;
    // s.precision(3);
    // Add time info
    s << setw(5) << (int) time
        // Add team number
        << setw(7) << r->team
        // Add location 
        << " @" << setw(3) << location->index 
        // Add space for message
        << ":\t" << left << setw(50);
    // Create event description depending on tepy
    switch(type){
        case Type::SCORE_LOW:
            msg << "Score ball in low goal for " << points << " points";
            break;
        case Type::SCORE_HIGH:
            msg << "Score ball in high goal for " << points << " points";
            break;
        case Type::CROSS:
            msg << "Cross defense for  " << points << " points";
            break;
        case Type::INTAKE:
            msg << "Intake ball";
            break;
        default:
            msg << "Drive through node " << location->index;
    }
    // Add description to string
    s << msg.str() << "\n";
    return s.str();
}