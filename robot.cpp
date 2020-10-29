#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "robot.h"
#include "utils.h"
#include "field/field.h"
#include "field/Fieldpoint.h"

#define BUFF_SIZE 256
// Some compilers may be missing M_PI, this serves as a safety check https://stackoverflow.com/questions/14920675/is-there-a-function-in-c-language-to-calculate-degrees-radians
#ifndef M_PI
#define M_PI 3.1415926535
#endif

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

void Robot::initGraph(){
    graph = Field::initGraph();
    graph->addNode(getShotZone(shotRange, centreAngle, centreShotTime));
    graph->addNode(getShotZone(shotRange, 0, centreShotTime));
    graph->addNode(getShotZone(shotRange, -centreAngle, centreShotTime));

    graph->addNode(getShotZone(shotRange, 90-sideAngle, sideShotTime));
    graph->addNode(getShotZone(shotRange, -(90-sideAngle), sideShotTime));

}

Shotpoint *Robot::getShotZone(int range, int angle, int time){
    int x, y;
    float angleRad = angle*(M_PI/180);
    if(alliance == Alliance::RED){
        x = Field::redTower.x + range*cos(angleRad);
        y = Field::redTower.y + range*sin(angleRad);
    } else if(alliance == Alliance::BLUE){
        x = Field::blueTower.x - range*cos(angleRad);
        y = Field::blueTower.y + range*sin(angleRad);
    } else {
        x = 0;
        y = 0;
    }

    return new Shotpoint(x, y, Alliance::NEUTRAL, Fieldpoint::Type::SHOTNODE);
}


int Robot::crossTime(Defense *d){
    // If it's the low bar, then it is impossible or 1 second
    if(d->defType == Defense::LOW_BAR){
        return canLowbar;
    }
    //Shift the current defense into lower 4 bits, then mask
    return (defenses >> (d->defType*4)) & 0xF;
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
    bot->initGraph();
    return bot;
}