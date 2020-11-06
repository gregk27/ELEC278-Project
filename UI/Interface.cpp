#include <string>
#include <stdbool.h>
#include "interface.h"
#include "../SDL2/SDL.h"
#include "../SDL2/SDL_render.h"
#include "../field/field.h"

using namespace Interface;

SDL_Window *fieldWindow;
SDL_Renderer *fieldRenderer;
SDL_Texture *fieldImage;

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
    fieldRenderer = SDL_CreateRenderer(fieldWindow, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *imgSurf = SDL_LoadBMP("field.bmp");
    fieldImage = SDL_CreateTextureFromSurface(fieldRenderer, imgSurf);

    if(fieldWindow == NULL){
        throw window_creation_exception(std::string("Could not create fieldWindow"));
    }
    
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = imgSurf->w;
    dest.h = imgSurf->h;

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

        SDL_RenderClear(fieldRenderer);
        SDL_RenderCopy(fieldRenderer, fieldImage, NULL, &dest);
        SDL_RenderPresent(fieldRenderer);
    }
    SDL_DestroyWindow(fieldWindow);
}

