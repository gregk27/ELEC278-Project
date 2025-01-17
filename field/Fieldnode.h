/**
 * Fieldnode.cpp/h
 * These files contains the the code used represent field nodes
 * 
 * Includes subclasses for Defenses and Shotnodes
 */

#ifndef FIELDNODE_H
#define FIELDNODE_H

// Forward-declarations from ../game.h, prevents circular dependancy
enum class Alliance;
extern const int CROSS_POINTS;
extern const int BASE_POINTS;

// Class representing a node on the graph
class Fieldnode {
    protected:
        Fieldnode();

    public:
        // Type of point
        enum class Type {
            // Generic travel node
            NODE, 
            // Node representing a defense, points awarded for crossing
            DEFENSE, 
            // Node representing the centre of the tower
            TOWER, 
            // Node restricted to the owning alliance
            RESTRICTED,
            // Node created by robot as location to shoot high goals
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
         * Create a new Fieldnode, which is automatically a neutral node
         * - x: X location, inches from top-left
         * - y: Y location, inches from top-left
         */
        Fieldnode(int x, int y);

        /**
         * Create a new Fieldnode, which is automatically a node
         * - x: X location, inches from top-left
         * - y: Y location, inches from top-left
         * - a: The alliance the node belongs to
         */
        Fieldnode(int x, int y, Alliance a);

        /**
         * Create a new Fieldnode
         * - x: X location, inches from top-left
         * - y: Y location, inches from top-left
         * - a: The alliance the node belongs to
         * - t: The type of the point
         */
        Fieldnode(int x, int y, Alliance a, Type t);
};

/* 
 * Class representing the defenses
 * This also holds utility functions for determining defenses
*/
class Defense: public Fieldnode {
    private: 
        // Value lost on cross
        static const int CROSS_VALUE = 5;

        Defense();
    public:
        // Maximum value of the defense
        static const int MAX_VALUE = CROSS_VALUE*2;
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

        using Fieldnode::Fieldnode;
};

/**
 * Class representing a node used for shooting high goals
 * These are added by robots to their member graphs
 */
class Shotnode: public Fieldnode {
    public:
        // Time taken for the shot
        int time;
        using Fieldnode::Fieldnode;
};

#endif // !FIELDNODE_H