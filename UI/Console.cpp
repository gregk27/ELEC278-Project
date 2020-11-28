#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "Console.h"
#include "../game.h"
#include "Interface.h"

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

void setCursor(short x, short y){
    SetConsoleCursorPosition(handle, {x,y});
}

void Console::setEvents(LinkedList<Event> *e){
    events = e;
}

void redraw(int selected){
    // Reset to top
    setCursor(0,0);
    // Print header
    printf("  Time   Robot @Node    Desc\t\t\tPress ESC to exit\n");
    
    int score = 0;

    // Print events
    for(auto i : (*events)){
        // Check that it should be on screen
        // If it's less than the selected value (+ offset) and it's not low enough for bottom, don't render
        if(i.index < selected-2 && i.index < events->size()-LINES-1){
            // Count the score as it's a passed event
            score += i.data.points;
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
            score += i.data.points;
            SetConsoleTextAttribute(handle, 0x0B);
            printf(" >%s", out.c_str());
            SetConsoleTextAttribute(handle, 0x0F);
        } else {
            if(i.index < selected){
                // Count the score as it's a passed event
                score += i.data.points;
            }
            printf("  %s", out.c_str());
        }
    }

    // Print overview
    setCursor(80, 5);
    printf("Time: %.2f    ", (*events)[selected].time);
    setCursor(80, 6);
    printf("Total score: %d ", score);

    // Return cursor to origin
    setCursor(0,0);
}

void Console::begin(){
    printf("Hello World\n");
    printf("Printed a thing!\n");

    int selected = 0;
    int score = 0;
    handle = GetStdHandle (STD_OUTPUT_HANDLE);

    system(CLEAR_COMMAND);
    Event e;
    events->get(selected, &e);
    Interface::setEvent(&e);
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
        events->get(selected, &e);
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