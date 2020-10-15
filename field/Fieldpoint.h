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

// Class representing the defenses
class Defense:Fieldpoint {
    private: 
        // Value lost on cross
        static const int CROSS_VALUE = 5;
        // Maximum value of the defense
        static const int MAX_VALUE = CROSS_VALUE*2;
    public:
        /**
         * Called when crossing the defense, subtracts from value
         * Returns points earned
         */
        int cross();
        // Current value of the defense
        int value;
        // Type of defense
        int defType;
};

#endif // !FIELDPOINT_H