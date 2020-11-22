// FLAGS: -ISDL2 -LSDL2 -lmingw32 -lSDL2main -lSDL2
#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <iostream>
#include <thread>
#include "robot.h"
// #include "field/Fieldpoint.h"
#include "field/field.h"
#include "utils/LinkedList.h"
#include "utils/Graph.h"
#include "game.h"
#include "ui/Interface.h"

int main(int argc, char *argv[]){

    printf("Hello World\n");

    // std::thread renderThread(Interface::init);

    Robot *r;
    r = Robot::parseCSV("./robots.csv");
    r->intakeNode = &Field::redPassage[0];
    r->location = &Field::centreBalls[0];
    // Event queue to be populated by simulation
    LinkedList<Event> events;

    // Defense *d = new Defense(0,0);
    // for(int i=0;i<8;i++){
    //     d->defType = (Defense::Defenses) i;
    //     printf("%d\n", r->crossTime(d));
    // }

    // Field::print(r->graph, false);
    Field::toGraphML(r->graph, "out.graphml");
    Interface::setGraph(r->graph);
    // Interface::drawGraph(r->graph);

    while(r->cyclesCompleted < 3){
        r->navUpdate(&events);
    }
    r->navUpdate(&events);

    for(auto i :events){
        std::string out = i.data.toString(); 
        printf(out.c_str());
    }

    // // printf("%d, %d, %d, %d\n",
    // // r.defenses,
    // // can_cross(&r, PORTCULLIS),
    // // can_cross(&r, SALLY_PORT), 
    // // can_cross(&r, ROCK_WALL));
    // print_field(true);

    // std::cout << "/* message */" << std::endl;
    
    // renderThread.join();
    return 0;
}