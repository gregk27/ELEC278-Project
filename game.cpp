#include <string>
#include <sstream>
#include "game.h"
#include "robot.h"

std::string Event::toString(){
    std::stringstream s;
    s.precision(4);
    s << r->team << "\t@" << time << "\t#" << location->index << ":\t";
    switch(type){
        case Type::SCORE_LOW:
            s << "Score ball in low goal for " << points << " points";
            break;
        case Type::SCORE_HIGH:
            s << "Score ball in high goal for " << points << " points";
            break;
        case Type::CROSS:
            s << "Cross defense for  " << points << " points";
            break;
        case Type::INTAKE:
            s << "Intake ball";
            break;
        default:
            s << "Drive through node " << location->index;
    }
    s << ".\n";
    return s.str();
}