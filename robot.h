#ifndef ROBOT_H
#define ROBOT_H
#include <stdbool.h>
#include <string>
#include "utils/Graph.h"
#include "game.h"
#include "utils.h"

typedef unsigned char byte;

/**
 * Class describing a robot
 */
class Robot {
    private:
        void initGraph();
        Shotpoint *getShotZone(int range, int angle);
    public:
        // Robot's unique ID (0-6)
        byte id;
        // Robot's team number
        int team;
        // Robot's speed (ips)
        float speed;
        // Robot's alliance
        Alliance alliance;

        // Boolean flag if the robot can go under the low bar
        bool canLowbar;
        
        // Description of defenses that can be crossed
        long defenses;

        // Maximum range for high goal shot, in feet
        byte shotRange;
        // Time in seconds needed for shot at centre goal. 0 indicates unable
        byte centreShotTime;
        // Time in seconds needed for shot at side goal. 0 indicates unable
        byte sideShotTime;
        // Max angle in degrees for shot at centre goal
        byte centreAngle;
        // Angle in degrees for shot at side goal
        byte sideAngle;
        // Time in seconds needed to score in low goal. 0 indicates unable
        byte lowTime;
        
        // The graph used by this robot, will have different shooting points than others, otherwise identical
        Graph *graph;

        LinkedList<Shotpoint *> shotpoints;
        
        // Create an empty robot, 
        Robot();
        
        /**
         *  Get the time which the robot tales to cross the defense
         *  - d: Pointer to the defense
         *  Returns: The time in seconds, from 1-15. If the robot cannot cross 0 is returned.
         */
        int crossTime(Defense *d);
        
        /*
        * Parse a csv file containing robot information
        * Returns a pointer to the found robot
        */
        static Robot *parseCSV(std::string filename);

        // Exception thrown when CSV file not found
        struct file_open_exception : public ExceptionBase {
            using ExceptionBase::ExceptionBase;
        };

        // Exception thrown when CSV input is shorter than expected
        struct csv_parsing_exception : public ExceptionBase {
            using ExceptionBase::ExceptionBase;
        };

        // Exception thrown for input parameters which will cause severe issues
        struct invalid_parameter_exception : public ExceptionBase {
            using ExceptionBase::ExceptionBase;
        };
};




#endif // !ROBOT_H
