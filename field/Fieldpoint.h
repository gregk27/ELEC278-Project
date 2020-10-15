#ifndef FIELDPOINT_H
#define FIELDPOINT_H
#include "../game.h"

typedef enum _fieldtype {
    // Generic travel node
    NODE,
    // Node representing a defense, points awarded for crossing
    DEFENSE,
    // Node representing the centre of the tower
    TOWER,
    // Node restricted to the owning alliance
    RESTRICTED
} Fieldtype;

// Class representing a point on the graph
class Fieldpoint {
    private:
        Fieldpoint();

    public:
        // Type of point
        enum class Type {
            // Generic travel node
            NODE, 
            DEFENSE, 
            TOWER, 
            RESTRICTED
        };

        // X location, inches from top-left
        int x;
        // Y location, inches from top-left
        int y;
        // Type of node
        Type type;
        // Alliance node belongs to, NULL if neutral
        Alliance alliance;

        /**
         * Create a new Fieldpoint, which is automatically a neutral node
         * - x: X location, inches from top-left
         * - y: Y location, inches from top-left
         */
        Fieldpoint(int x, int y);

        /**
         * Create a new Fieldpoint, which is automatically a node
         * - x: X location, inches from top-left
         * - y: Y location, inches from top-left
         * - a: The alliance the node belongs to
         */
        Fieldpoint(int x, int y, Alliance a);

        /**
         * Create a new Fieldpoint
         * - x: X location, inches from top-left
         * - y: Y location, inches from top-left
         * - a: The alliance the node belongs to
         * - t: The type of the point
         */
        Fieldpoint(int x, int y, Alliance a, Type t);
};

/* 
 * Class representing the defenses
 * This also holds utility functions for determining defenses
*/
class Defense:Fieldpoint {
    private: 
        // Value lost on cross
        static const int CROSS_VALUE = 5;
        // Maximum value of the defense
        static const int MAX_VALUE = CROSS_VALUE*2;
    public:
        /* 
        * Bitmask positions for each defense
        * To get the speed for a particular defense, do
        * mask >> DEF*4 & 0xF
        */
        enum _defenses{
            // Category A
            PORTCULLIS      = 0, // Portcullis in first 1/2 byte
            CHEVAL_DE_FRISE = 1, // Cheval de frise in second 1/2 byte
            // Category B
            MOAT            = 2, // Moat in thrid 1/2 byte
            RAMPARTS        = 3,
            // Category C
            DRAWBRIDGE      = 4,
            SALLY_PORT      = 5,
            // Category D
            ROCK_WALL       = 6,
            ROUGH_TERRAIN   = 7
        };

        /**
         * Called when crossing the defense, subtracts from value
         * Returns points earned
         */
        int cross();
        // Current value of the defense
        int value;
        // Type of defense
        enum _defenses defType;
};

#endif // !FIELDPOINT_H