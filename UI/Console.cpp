#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "Console.h"
#include "../game.h"

#include <windows.h>

#define CLEAR_COMMAND "cls"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

LinkedList<Event> *events;


void setCursor(short x, short y){
    SetConsoleCursorPosition( GetStdHandle (STD_OUTPUT_HANDLE), {x,y});
}

void Console::setEvents(LinkedList<Event> *e){
    events = e;
}

void Console::begin(){
    printf("Hello World\n");
    printf("Printed a thing!\n");

    system(CLEAR_COMMAND);
    for(auto i : (*events)){
        std::string out = i.data.toString(); 
        printf("  %s", out.c_str());
    }
    setCursor(0,0);
    printf(">");
    int c = 0;
    int y = 0;
    while((c=getch()) != 27){
        setCursor(0,y);
        printf(" ");
        switch (c) {
            case KEY_UP:
                y --;
                break;
            case KEY_DOWN:
                y ++;
                break;
        }
        if(y < 0) y=0;
        if(y >= events->size()) y = events->size()-1;
        setCursor(0,y);
        printf(">");
    }
}