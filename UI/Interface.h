#ifndef INTERFACE_H
#define INTERFACE_H
#include "../SDL2/SDL.h"
#include "../utils/utils.h"

namespace Interface {
    void init();

    // Exception thrown when window 
    struct window_creation_exception: public ExceptionBase{
        using ExceptionBase::ExceptionBase;
    };
}

#endif // !INTERFACE_H
