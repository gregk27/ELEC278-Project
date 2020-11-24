#ifndef CONSOLE_H
#define CONSOLE_H

#include "../utils/LinkedList.h"
#include "../game.h"

namespace Console {
    void setEvents(LinkedList<Event> *events);
    void begin();
}


#endif // !CONSOLE_H
