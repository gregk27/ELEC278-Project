#include "robot.h"
#include "utils.h"

bool can_cross(Robot *r, Defence d){
    // Mask the defenses to check
    return (r->defenses & d) != 0;
}