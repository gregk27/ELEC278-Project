#ifndef FIELD_H
#define FIELD_H
#include <stdbool.h>
#include "Fieldpoint.h"
#include "../robot.h"

namespace Field {
    // All locations in inches from top-left. Field dimensions take from game manual.
    Fieldpoint RED_TOWER;
    Fieldpoint RED_DEFENSES[5];

    Fieldpoint BLUE_TOWER;
    Fieldpoint BLUE_DEFENSES[5];
}

void print_field(bool showdots);
#endif // !FIELD_H