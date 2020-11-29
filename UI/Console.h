#ifndef CONSOLE_H
#define CONSOLE_H

#include "../utils/LinkedList.h"
#include "../game.h"
#include "../field/Fieldpoint.h"

namespace Console {
    void setEvents(LinkedList<Event> *events);
    void begin();

    /**
     * Request user for Y/N confirmation
     *  - message:  Message to prompt with
     *  - def:      Default value on empty response
     * Returns: True if user enters Y/y, def on empty input, otherwise false
     */
    bool confirm(std::string message, bool def);

    struct DefenseStat {
        int index;
        Defense::Defenses type;
        int value;
    };
}


#endif // !CONSOLE_H
