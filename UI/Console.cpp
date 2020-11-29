#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string>

#include "Console.h"
#include "../game.h"
#include "Interface.h"
#include "../utils/LinkedList.h"
#include "../field/field.h"

#include <windows.h>

#define CLEAR_COMMAND "cls"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

#define HEIGHT 30
#define LINES 25

LinkedList<Event> *events;

HANDLE handle;

Console::DefenseStat defenses[5];

/** 
 * Names of defenses
 * To get correct name, access Defenses value +1
*/
const std::string DEFENSE_NAMES[] = {"Low Bar", "Portcullis", "Cheval de Frise", "Moat", "Ramparts", "Drawbridge", "Sally Port", "Rock Wall", "Rough Terrain"};


void setCursor(short x, short y){
    SetConsoleCursorPosition(handle, {x,y});
}

void Console::setEvents(LinkedList<Event> *e){
    events = e;
}

void updateScores(LinkedList<Event>::Iterator::ListItem i, int *scoreVar){
    *scoreVar += i.data.points;
    // If it was crossing a defense, then remove the points
    if(i.data.location->type == Fieldpoint::Type::DEFENSE){
        for(int j=0; j<5; j++){
            if(defenses[j].index == i.data.location->index){
                defenses[j].value -= i.data.points;
            }
        }
    }
}

void redraw(int selected){
    // Reset to top
    setCursor(0,0);
    // Print header
    printf("  Time   Robot @Node    Desc\t\t\tPress ESC to exit\n");
    
    int score = 0;
    // Initialise defenses
    for(int i=0; i<5; i++){
        defenses[i].value = Defense::MAX_VALUE;
    }

    // Print events
    for(auto i : (*events)){
        // Check that it should be on screen
        // If it's less than the selected value (+ offset) and it's not low enough for bottom, don't render
        if(i.index < selected-2 && i.index < events->size()-LINES-1){
            // Count the score as it's a passed event
            updateScores(i, &score);
            continue;
        // If it's too low, stop here
        } else if (i.index > (selected-2 + LINES)){
            break;
        }
        // Get data string
        std::string out = i.data.toString();
        // If it's selected, print indicator and colour
        if(i.index == selected){
            // Count the score as it's the event
            updateScores(i, &score);
            SetConsoleTextAttribute(handle, 0x0B);
            printf(" >%s", out.c_str());
            SetConsoleTextAttribute(handle, 0x0F);
        } else {
            if(i.index < selected){
                // Count the score as it's a passed event
                updateScores(i, &score);
            }
            printf("  %s", out.c_str());
        }
    }

    // Print overview
    setCursor(80, 5);
    printf("Time: %.2f    ", (*events)[selected].time);
    setCursor(80, 6);
    printf("Total score: %d ", score);
    
    // Print defense information. Print in reverse order to match positions on field
    setCursor(80,9);
    printf("Defenses:");
    setCursor(80,10);
    printf("ID  Value Type");
    for(int i=4; i>=0; i--){
        setCursor(80, 11+i);
        fflush(stdout);
        printf("R%d: %2d %-16s", i, defenses[i].value, DEFENSE_NAMES[defenses[i].type+1].c_str());
    }

    // Return cursor to origin
    setCursor(0,0);
}

void Console::begin(){
    printf("Hello World\n");
    printf("Printed a thing!\n");

    // Initialise defenses
    for(int i=0; i<5; i++){
        defenses[i].index = Field::redDefenses[i].index;
        defenses[i].type = Field::redDefenses[i].defType;
        defenses[i].value = Defense::MAX_VALUE;
    }

    int selected = 0;
    int score = 0;
    handle = GetStdHandle (STD_OUTPUT_HANDLE);

    system(CLEAR_COMMAND);
    Interface::setEventList(events);
    Node<Event> *e;
    e = events->getNode(selected);
    Interface::setEvent(e);
    redraw(selected);
    // setCursor(0,0);
    // printf(">");
    int c = 0;
    // int y = 0;
    while((c=getch()) != 27){
        printf(" ");
        switch (c) {
            case KEY_UP:
                selected --;
                break;
            case KEY_DOWN:
                selected ++;
                break;
        }
        if(selected < 0) selected=0;
        if(selected >= events->size()) selected = events->size()-1;
        e = events->getNode(selected);
        Interface::setEvent(e);
        redraw(selected);
        // Delay 100ms between keypresses
        Sleep(100);
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    }
}


bool Console::confirm(std::string message, bool def) {
    // If input is on new line, indent it
    if(message.back() == '\n')
        message += "\t";
    // Print prompt
    if(def){
        printf("%s (y/n) [Y]: ", message.c_str());
    } else {
        printf("%s (y/n) [N]: ", message.c_str());
    }
    // Get input
    char buf[8];
    fgets(buf, 9, stdin);
    if(buf[0] == '\n')
        return def;
    return buf[0] == 'Y' || buf[0] == 'y';
}