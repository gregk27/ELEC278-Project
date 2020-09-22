#ifndef FIELD_H
#define FIELD_H
#include <stdbool.h>
#include "robot.h"

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

typedef struct _fieldpoint {
    // X location, inches from top-left
    int x;
    // Y location, inches from top-left
    int y;
    // Type of node
    Fieldtype type;
    // Alliance node belongs to, NULL if neutral
    Alliance alliance;
    // Data associated with the node, varies by type
    long data;
} Fieldpoint;

// All locations in inches from top-left. Field dimensions take from game manual.
Fieldpoint RED_TOWER;
Fieldpoint RED_DEFENSES[5];

Fieldpoint BLUE_TOWER;
Fieldpoint BLUE_DEFENSES[5];


void print_field(bool showdots);
#endif // !FIELD_H