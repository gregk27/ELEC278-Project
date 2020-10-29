#ifndef ROBOT_H
#define ROBOT_H
#include <stdbool.h>
#include <string>
#include "game.h"

/**
 * Class describing a robot
 */
class Robot {
    public:
        // Robot's unique ID (0-6)
        int id;
        // Robot's team number
        int team;
        // Robot's speed (fpm)
        int speed;
        // Robot's alliance
        Alliance alliance;

        // Boolean flag if the robot can go under the low bar
        bool canLowbar;
        
        // Description of defenses that can be crossed
        long defenses;

        // Maximum range for high goal shot, in feet
        int shotRange;
        // Time in seconds needed for shot at centre goal. 0 indicates unable
        int centreShotTime;
        // Time in seconds needed for shot at side goal. 0 indicates unable
        int sideShotTime;
        // Max angle in degrees for shot at centre goal
        int centreAngle;
        // Angle in degrees for shot at side goal
        int sideAngle;
        // Time in seconds needed to score in low goal. 0 indicates unable
        int lowTime;

        
        // Create an empty robot, 
        Robot();
        
        /*
        * Parse a csv file containing robot information
        * Returns a pointer to the found robot
        */
        static Robot *parseCSV(std::string filename);
};




#endif // !ROBOT_H
