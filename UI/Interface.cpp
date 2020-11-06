#include <string>
#include <stdbool.h>
#include "interface.h"
#include "../SDL2/SDL.h"
#include "../field/field.h"

using namespace Interface;

SDL_Window *fieldWindow; 

void Interface::init(){
    SDL_Init(SDL_INIT_VIDEO);
    fieldWindow = SDL_CreateWindow(
        "Simulation Field",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        650*2,
        320*2,
        SDL_WINDOW_OPENGL
    );

    if(fieldWindow == NULL){
        throw window_creation_exception(std::string("Could not create fieldWindow"));
    }
    
    bool running = true;
    while(running){
        SDL_Event event;
        // Poll over events
        while(SDL_PollEvent(&event)) {
            // Handle quit event
            if (event.type == SDL_QUIT ||
                    (event.type == SDL_WINDOWEVENT &&
                    event.window.event == SDL_WINDOWEVENT_CLOSE)) {
                        running = false;
            }
        }
    }
    SDL_DestroyWindow(fieldWindow);
}

