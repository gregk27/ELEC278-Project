#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include "robot.h"
// #include "field/Fieldpoint.h"
#include "field/field.h"
#include "utils/LinkedList.h"
#include "utils/Graph.h"
#include "game.h"

int main(){

    printf("Hello World\n");

    Robot *r;
    r = Robot::parseCSV("./robots.csv");
    // Event queue to be populated by simulation
    LinkedList<Event> events;

    Defense *d = new Defense(0,0);
    for(int i=0;i<8;i++){
        d->defType = (Defense::Defenses) i;
        printf("%d\n", r->crossTime(d));
    }

    Field::print(r->graph, false);
    Field::toGraphML(r->graph, "out.graphml");

    // // print_bin(r.defenses, 16);

    // // printf("%d, %d, %d, %d\n",
    // // r.defenses,
    // // can_cross(&r, PORTCULLIS),
    // // can_cross(&r, SALLY_PORT), 
    // // can_cross(&r, ROCK_WALL));
    // print_field(true);

    // std::cout << "/* message */" << std::endl;
    return 0;
}