#ifndef FIELDPOINT_H
#define FIELDPOINT_H
#include "../game.h"

// Forward-declaration of alliance from ../game.h
enum class Alliance;

extern const int CROSS_POINTS;
extern const int BASE_POINTS;

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
    protected:
        Fieldpoint();

    public:
        // Type of point
        enum class Type {
            // Generic travel node
            NODE, 
            DEFENSE, 
            TOWER, 
            RESTRICTED,
            SHOTNODE
        };

        // X location, inches from top-left
        int x;
        // Y location, inches from top-left
        int y;
        // Type of node
        Type type;
        // Alliance node belongs to, NULL if neutral
        Alliance alliance;
        // Index of the node in node list and matrix
        int index;

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
class Defense: public Fieldpoint {
    private: 
        // Value lost on cross
        static const int CROSS_VALUE = 5;
        // Maximum value of the defense
        static const int MAX_VALUE = CROSS_VALUE*2;

        Defense();
    public:
        /* 
        * Bitmask positions for each defense
        * To get the speed for a particular defense, do
        * mask >> DEF*4 & 0xF
        */
        typedef enum {
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
            ROUGH_TERRAIN   = 7,
            // Low Bar
            LOW_BAR         =-1 // Low bar isn't in defense mask
        } Defenses;

        /**
         * Called when crossing the defense, subtracts from value
         * Returns points earned
         */
        int cross();
        // Current value of the defense
        int value = BASE_POINTS;
        // Type of defense
        Defenses defType;

        using Fieldpoint::Fieldpoint;
};

class Shotpoint: public Fieldpoint {
    public:
        int time;
        using Fieldpoint::Fieldpoint;
};

#endif // !FIELDPOINT_H