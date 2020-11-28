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

    std::thread renderThread(Interface::init);

    // Get robot file from user
    std::string robotPath;
    printf("Path to robot file [./robots.csv]: ");
    std::getline(std::cin,robotPath);
    if(robotPath == "")
        robotPath = "./robots.csv";

    // Initialise the robot from
    Robot *r;
    r = Robot::parseCSV(robotPath);
    // Initialise the robot on red alliance
    r->alliance = Alliance::RED;
    // Balls are entered into play at the end of the passage
    r->intakeNode = &Field::redPassage[0];
    // The robot should start at the top-centre    
    r->location = &Field::centreBalls[1];

    // Initialise defenses
    printf("Enter defense configuration for positions 2-5, enter the IDs with spaces between.\n");
    // Get input from user
    int d1, d2, d3, d4;
    while(1){
        // Get input
        printf("[0 2 4 6]: ");
        char buf[16];
        fgets(buf, 16, stdin);
        int in = sscanf(buf, " %d %d %d %d", &d1, &d2, &d3, &d4);
        // If no values read, apply defaults 
        if(in == -1){
            d1 = 0;
            d2 = 2;
            d3 = 4;
            d4 = 6;
        } else if (in != 4){ // If not 0, but still wrong number then go again
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

    printf("Simulation length (seconds) [150]: ");
    int duration;
    char buf[16];
    fgets(buf, 16, stdin);
    int in = sscanf(buf, " %d", &duration);
    if(in == -1){
        duration = 150;
    }


    // Event queue to be populated by simulation
    LinkedList<Event> events;

    Field::toGraphML(r->graph, "out.graphml");
    Interface::setGraph(r->graph);

    while(r->wakeTime < duration){
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
    
    Interface::close();
    renderThread.join();
    return 0;
}