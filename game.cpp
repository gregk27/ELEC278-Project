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
    s << setw(5) << (int) time 
        << setw(7) << r->team 
        << " @" << setw(3) << location->index 
        << ":\t" << left << setw(50);
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
    s << msg.str() << "\n";
    return s.str();
}