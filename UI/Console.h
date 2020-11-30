/**
 * Console.cpp/h
 * These files contain the code used for displaying the events in the console
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include "../utils/LinkedList.h"
#include "../game.h"
#include "../field/Fieldnode.h"

// Namespace containing functions for the console event list
namespace Console {
    /**
     * Set the events in the console
     * - events: Pointer to linkedlist containing events
    */
    void setEvents(LinkedList<Event> *events);
    /**
     * Run the console interface
     * THIS WILL BLOCK THE THREAD
     * THIS WILL CLEAR THE CONSOLE 
     */
    void begin();

    /**
     * Request user for Y/N confirmation
     *  - message:  Message to prompt with
     *  - def:      Default value on empty response
     * Returns: True if user enters Y/y, def on empty input, otherwise false
     */
    bool confirm(std::string message, bool def);

    // Struct to hold information about a defense
    struct DefenseStat {
        // The index of the node
        int index;
        // The type of the defense
        Defense::Defenses type;
        // The current point value of the defense
        int value;
    };
}


#endif // !CONSOLE_H
