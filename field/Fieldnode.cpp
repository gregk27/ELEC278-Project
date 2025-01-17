#include "Fieldnode.h"
#include "../robot.h"

Fieldnode::Fieldnode(){
    this->x = -1;
    this->y = -1;
    this->alliance = Alliance::NEUTRAL;
    this->type = Type::NODE;
}

Fieldnode::Fieldnode(int x, int y){
    this->x = x;
    this->y = y;
    this->alliance = Alliance::NEUTRAL;
    this->type = Type::NODE;
}

Fieldnode::Fieldnode(int x, int y, Alliance a){
    this->x = x;
    this->y = y;
    this->alliance = a;
    this->type = Type::NODE;
}

Fieldnode::Fieldnode(int x, int y, Alliance a, Type t){
    this->x = x;
    this->y = y;
    this->alliance = a;
    this->type = t;
}

Defense::Defense():Fieldnode(){
    this->defType = LOW_BAR;
    this->value = MAX_VALUE;
}

int Defense::cross(){
    if(this->value > 0){
        this->value -= CROSS_VALUE;
        return CROSS_VALUE;
    }
    return 0;
}
