#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "robot.h"
#include "utils.h"

#define BUFF_SIZE 256

Robot::Robot(){
    this->id = -1;
    this->team = 0000;
    this->speed = 0;
    this->alliance = Alliance::NEUTRAL;
    this->canLowbar = false;
    this->defenses = 0;
    this->shotRange = 0;
    this->centreShotTime = 0;
    this->sideShotTime = 0;
    this->centreAngle = 0;
    this->sideAngle = 0;
    this->lowTime = 0;
}

// bool can_cross(Robot *r, Defenses d){
//     // Mask the defenses to check
//     return (r->defenses >> (int)d*4 & 0xF) != 0;
// }

/*
 * Parse a csv file containing robot information
 * Returns a pointer to the found robot
*/
Robot *Robot::parseCSV(std::string filename){
    // Open the file
    FILE *f = fopen(filename.c_str(), "r"); 
    if(f == NULL) return NULL;

    // Buffer for read lines. No line following the correct format will exceed 64 characters
    char line[BUFF_SIZE];

    Robot *bot = new Robot();

    // Remove header line
    fgets (line, BUFF_SIZE, f);
    // Read robot line
    fgets (line, BUFF_SIZE, f);
    // Data order: team,can_low,shot_range,centre_shot_time,side_shot_time,centre_angle,side_angle,low_time,defenses,speed
    sscanf(line, "%d,%d,%d,%d,%d,%d,%d,%d,%lx,%d", 
        &(bot->team),
        &(bot->canLowbar),
        &(bot->shotRange),
        &(bot->centreShotTime),
        &(bot->sideShotTime),
        &(bot->centreAngle),
        &(bot->sideAngle),
        &(bot->lowTime),
        &(bot->defenses),
        &(bot->speed));
    bot->alliance = Alliance::RED;
    bot->id = 0;
    return bot;
}