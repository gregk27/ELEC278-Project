#ifndef INTERFACE_H
#define INTERFACE_H
#include "../SDL2/SDL.h"
#include "../utils/utils.h"
#include "../utils/Graph.h"

namespace Interface {
    void init();

    void setGraph(Graph *g);
    void setEvent(Event *e);
    void close();

    // Exception thrown when window 
    struct window_creation_exception: public ExceptionBase{
        using ExceptionBase::ExceptionBase;
    };
}

#endif // !INTERFACE_H
