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
#include "ui/Console.h"
#include "ui/Interface.h"

int main(int argc, char *argv[]){

    printf("Hello World\n");

    // std::thread renderThread(Interface::init);

    // Initialise defenses
    printf("Enter defense configuration for positions 2-5, enter the IDs with spaces between.\n");
    // Get input from user
    int d1, d2, d3, d4;
    while(1){
        // Get input
        printf("[0 2 4 6]: ");
        char buf[16];
        fgets(buf, 16, stdin);
        int r = sscanf(buf, " %d %d %d %d", &d1, &d2, &d3, &d4);
        // If no values read, apply defaults 
        if(r == -1){
            d1 = 0;
            d2 = 2;
            d3 = 4;
            d4 = 6;
        } else if (r != 4){ // If not 0, but still wrong number then go again
            printf("Improper number of parameters, enter either 0 for default or exactly 4.\n");
            continue;
        }

        // Divide each by 2 to get 1,2,3,4 for categories.
        // If all different categories, average will be (1+2+3+4)/4 = 2.5\
        // If there are duplicates/same category, prompt before proceeding
        if((d1/2+d2/2+d3/2+d4/2)/4.0 != 2.5 || Console::confirm("You have selected multiple defenses from the same category, do you wish to proceed?\n", false))
            break;
    }

    // Assign defenses based on input
    // Position 1 is always low bar
    Field::redDefenses[0].defType = Defense::LOW_BAR;
    Field::redDefenses[1].defType = static_cast<Defense::Defenses>(d1);
    Field::redDefenses[2].defType = static_cast<Defense::Defenses>(d2);
    Field::redDefenses[3].defType = static_cast<Defense::Defenses>(d3);
    Field::redDefenses[4].defType = static_cast<Defense::Defenses>(d4);

    Robot *r;
    r = Robot::parseCSV("./robots.csv");
    r->alliance = Alliance::RED;
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

    while(r->wakeTime < 150){
        r->navUpdate(&events);
    }

    int totalScore = 0;
    for(auto i :events){
        std::string out = i.data.toString(); 
        printf(out.c_str());
        totalScore += i.data.points;
    }

    printf("Final score: %d points", totalScore);

    Console::setEvents(&events);
    Console::begin();
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