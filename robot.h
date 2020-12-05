/**
 * robot.ccp/h
 * These files contain the code for managing robots
 * This includes the bot's abilities (defense crossing, shot locations) and navigation (graph, location, dijkstra algorithm)
 */

#ifndef ROBOT_H
#define ROBOT_H
#include <stdbool.h>
#include <string>
#include "utils/Graph.h"
#include "game.h"
#include "utils/utils.h"

typedef unsigned char byte;

/**
 * Class describing a robot
 */
class Robot {
    private:
        /**
         * Get a ShotNode with a specific range and angle relative to the tower
         * - range: The distance from the tower
         * - angle: The angle relative to the horizontal, in degrees
         * Returns: A shotnode at the specified location 
         */
        Shotnode *getShotZone(int range, int angle);
        /**
         * Get the event representing the robot's last action
         * Returns: Event representing robot's last action
         */
        Event getEvent();
        /**
         * Apply Dijkstra's algorithm at a node
         *  - target: Pointer to the target node
         * Returns: The DijkstraNode at the end of the found path
         */
        Graph::DijkstraNode *getPath(Fieldnode *target);

        // Calculated data about an edge for dijkstra's algorthim
        struct EdgeData {
            // The weight of the edge, rougly time - points
            float weight;
            // Time taken to travel to the node, will not have reduction from points
            float time;
        };

        /**
         * Get the weight and time data for a particular edge
         * This will calulate based on a variety of factors, notable time taken and points earned
         * - n: The node being visited
         * - e: The edge being calculated
         * Returns: EdgeData with weight and time
        */
        EdgeData getWeight(Graph::DijkstraNode *n, Graph::Edge e);

        /**
         * Temp for storing planned path to be passed to event
         */
        Graph::DijkstraNode *path;
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

        // List containing the created shotnodes
        LinkedList<Shotnode *> shotnodes;
        
        // Create an empty robot
        Robot();
        
        /**
         * Initialise the local graph instace
         * This will create a graph with Field::initGraph(), then add robot-specific elements such as shotnodes and the goal node
         */
        void initGraph();
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
        static LinkedList<Robot *> parseCSV(std::string filename);

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
        
        // Navigation

        // Fieldnode with 0 length with all scoring positions, used as target for dijkstra
        Fieldnode *goalNode;
        // Fieldnode where robot will intake balls
        Fieldnode *intakeNode;
        // Current location on the field
        Fieldnode *location;
        // Time at which the robot will have arrived
        float wakeTime = 0;
        // Flag indicating if the robot has a ball, defaults to true
        bool hasBall = true;

        // Value of each point gained in seconds taken, used to determine which defense or scoring method is best
        float pointValue;

        // Number of cycles completed. A cycle is counted when a goal is scored
        int cyclesCompleted = 0;

        /**
         * Have the bot navigate the next leg
         *  - events: The event queue to log to
         */
        void navUpdate(LinkedList<Event> *events);
};




#endif // !ROBOT_H
