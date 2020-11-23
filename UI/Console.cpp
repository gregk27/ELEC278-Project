#include <stdio.h>
#include <stdlib.h>

#include "Console.h"
#include "../game.h"

#include <windows.h>

#define CLEAR_COMMAND "cls"
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
    printf("Cleared screen");
    setCursor(2,0);
    printf("TEST");
    setCursor(0,1);
    printf("\n");
    system("pause");
}