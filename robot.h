#ifndef ROBOT_H
#define ROBOT_H
#include <stdbool.h>
#include "game.h"

typedef enum _alliance 
{
    RED_ALLIANCE, BLUE_ALLIANCE
} Alliance;

typedef struct _robot
{
    // Robot's unique ID (0-6)
    int id;
    // Robot's team number
    int team;
    // Robot's speed (fpm)
    int speed;
    // Robot's alliance
    Alliance alliance;

    // Boolean flag if the robot can go under the low bar
    bool can_lowbar;
    
    // Description of defenses that can be crossed
    unsigned int defenses;

} Robot;

bool can_cross(Robot *r, Defence d);
/*
Parse a csv file containing robot information
Returns the number of robots found
*/
int parse_csv(char* filename, Robot *bots, int botCount);



#endif // !ROBOT_H
