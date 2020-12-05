/**
 * Console.cpp/h
 * These files contain the code used for displaying the events in the console
 */

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

// This include was causing issues with others, so it was moved below
#include <windows.h>

// Console command to clear the screen
#define CLEAR_COMMAND "cls"
// Key code for the up arrow key
#define KEY_UP 72
// Key code for the down arrow key
#define KEY_DOWN 80
// Key code for the escape key
#define KEY_ESC 27
// Key code for the first event key (F)
#define KEY_FIRST 102
// Key code for the last event key  (L)
#define KEY_LAST 108
// Key code for the show graph key  (G)
#define KEY_GRAPH 103

// Height of the console, in lines
#define HEIGHT 30
// Number of lines used for events
#define LINES 25

// Event list to be used
LinkedList<Event> *events;

// STD Handle used for windows console functions
HANDLE handle;

// Structs tracking stats for defenses
Console::DefenseStat defenses[5];

/** 
 * Names of defenses
 * To get correct name, access Defenses value +1
*/
const std::string DEFENSE_NAMES[] = {"Low Bar", "Portcullis", "Cheval de Frise", "Moat", "Ramparts", "Drawbridge", "Sally Port", "Rock Wall", "Rough Terrain"};

/**
 * Set the cursor location in the console window
 * - x: X position
 * - y: Y position
 */
void setCursor(short x, short y){
    SetConsoleCursorPosition(handle, {x,y});
}

void Console::setEvents(LinkedList<Event> *e){
    events = e;
}

/**
 * Update score and defense stats with an event
 * - i:         Event list listItem to use 
 * - socreVar:  Pointer to the variable holding the score
*/
void updateScores(LinkedList<Event>::Iterator::ListItem i, int *scoreVar){
    *scoreVar += i.data.points;
    // If it was crossing a defense, then remove the points
    if(i.data.location->type == Fieldnode::Type::DEFENSE){
        for(int j=0; j<5; j++){
            if(defenses[j].index == i.data.location->index){
                defenses[j].value -= i.data.points;
            }
        }
    }
}

/**
 * Redraw the console
 * - selected: The index of the currently selected event
 */
void redraw(int selected){
    // Reset to top
    setCursor(0,0);
    // Print header
    printf("  Time   Robot @Node    Desc\n");
    
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

    // Print controls
    setCursor(0, HEIGHT-2);
    printf("\tUse Arrows to navigate\tF/L to jump to First/Last\tG to change graph visibility\tPress ESC to exit");

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
    // Initialise defenses
    for(int i=0; i<5; i++){
        defenses[i].index = Field::redDefenses[i].index;
        defenses[i].type = Field::redDefenses[i].defType;
        defenses[i].value = Defense::MAX_VALUE;
    }

    int selected = 0;
    int score = 0;
    handle = GetStdHandle (STD_OUTPUT_HANDLE);

    // Clear simulation output
    system(CLEAR_COMMAND);
    // Set the GUI's event list
    Interface::setEventList(events);
    
    Node<Event> *e;
    e = events->getNode(selected);
    Interface::setEvent(e);
    redraw(selected);
    
    int c = 0;
    // Loop until escape pressed
    while((c=getch()) != KEY_ESC){
        switch (c) {
            case KEY_UP:
                selected --;
                break;
            case KEY_DOWN:
                selected ++;
                break;
            case KEY_FIRST:
                selected = 0;
                break;
            case KEY_LAST:
                selected = events->size()-1;
                break;
            case KEY_GRAPH:
                Interface::toggleGraph();
                break;
            default:
                continue;
        }
        // Make sure list not exceeded
        if(selected < 0) selected=0;
        if(selected >= events->size()) selected = events->size()-1;
        // Get the new event and redraw
        e = events->getNode(selected);
        Interface::setEvent(e);
        redraw(selected);
        // Delay 100ms between keypresses
        Sleep(100);
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    }

    system(CLEAR_COMMAND);
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