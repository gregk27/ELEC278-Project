#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "Console.h"
#include "../game.h"

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
    printf("  Time   Robot @Node    Desc\t\t\t\tPress ESC to exit\n");
    
    // Print events
    for(auto i : (*events)){
        // Check that it should be on screen
        // If it's less than the selected value (+ offset) and it's not low enough for bottom, don't render
        if(i.index < selected-2 && i.index < events->size()-LINES-1){
            continue;
        // If it's too low, stop here
        } else if (i.index > (selected-2 + LINES)){
            break;
        }
        // Get data string
        std::string out = i.data.toString();
        // If it's selected, print indicator and colour
        if(i.index == selected){
            SetConsoleTextAttribute(handle, 0x0B);
            printf(" >%s", out.c_str());
            SetConsoleTextAttribute(handle, 0x0F);
        } else {
            printf("  %s", out.c_str());
        }
    }
}

void Console::begin(){
    printf("Hello World\n");
    printf("Printed a thing!\n");

    int selected = 0;
    handle = GetStdHandle (STD_OUTPUT_HANDLE);

    system(CLEAR_COMMAND);
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
        redraw(selected);
    }
}