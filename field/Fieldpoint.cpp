#include "Fieldpoint.h"
#include "../robot.h"

Fieldpoint::Fieldpoint(){
    this->x = -1;
    this->y = -1;
    this->alliance = Alliance::NEUTRAL;
    this->type = Type::NODE;
}

Fieldpoint::Fieldpoint(int x, int y){
    this->x = x;
    this->y = y;
    this->alliance = Alliance::NEUTRAL;
    this->type = Type::NODE;
}

Fieldpoint::Fieldpoint(int x, int y, Alliance a){
    this->x = x;
    this->y = y;
    this->alliance = a;
    this->type = Type::NODE;
}

Fieldpoint::Fieldpoint(int x, int y, Alliance a, Type t){
    this->x = x;
    this->y = y;
    this->alliance = a;
    this->type = t;
}

Defense::Defense():Fieldpoint(){
    this->defType = LOW_BAR;
    this->value = MAX_VALUE;
}

int Defense::crossTime(Robot *r){
    // If it's the low bar, then it is impossible or 1 second
    if(this->defType == LOW_BAR){
        return r->canLowbar;
    }
    //Shift the current defense into lower 4 bits, then mask
    return (r->defenses >> (this->defType*4)) & 0xF;
}

int Defense::cross(){
    if(this->value > 0){
        this->value -= CROSS_VALUE;
        return CROSS_VALUE;
    }
    return 0;
}