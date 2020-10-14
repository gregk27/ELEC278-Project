#include "Fieldpoint.h"
#include "../robot.h"

Fieldpoint::Fieldpoint(){
    this->x = -1;
    this->y = -1;
    this->alliance = NO_ALLIANCE;
    this->type = Type::NODE;
}

Fieldpoint::Fieldpoint(int x, int y){
    this->x = x;
    this->y = y;
    this->alliance = NO_ALLIANCE;
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

int Defense::cross(){
    if(this->value > 0){
        this->value -= CROSS_VALUE;
        return CROSS_VALUE;
    }
    return 0;
}