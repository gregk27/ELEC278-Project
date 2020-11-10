#include <string>
#include <stdbool.h>
#include "interface.h"
#include "../SDL2/SDL.h"
#include "../SDL2/SDL_render.h"
#include "../SDL2/SDL_rect.h"
#include "../field/field.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"

using namespace Interface;

SDL_Window *fieldWindow;
SDL_Renderer *fieldRenderer;
SDL_Texture *fieldImage;
Graph *activeGraph;

void drawGraph(Graph *g){
    SDL_Rect r;
    r.h=20;
    r.w=20;

    SDL_SetRenderDrawColor(fieldRenderer, 255,255,255,SDL_ALPHA_OPAQUE);
    g->adjacency.forEach([g](LinkedList<Graph::Edge>* l, int i){
        l->forEach([i,l,g](Graph::Edge e, int j){
            SDL_RenderDrawLine(fieldRenderer, g->nodes[i]->x*2, g->nodes[i]->y*2, e.end->x*2, e.end->y*2);
        });
    });

    g->nodes.forEach([&r](Fieldpoint *p, int i){
        // Set x and y, doubled because canavas is scaled up, subtract 10 to centre
        r.x = p->x*2-10;
        r.y = p->y*2-10;
        switch (p->alliance){
            case Alliance::RED:
                SDL_SetRenderDrawColor(fieldRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                break;
            case Alliance::BLUE:
                SDL_SetRenderDrawColor(fieldRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
                break;
            default:
                SDL_SetRenderDrawColor(fieldRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                break;
        }
        SDL_RenderFillRect(fieldRenderer,&r);
    });
}

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
        if(activeGraph != NULL){
            drawGraph(activeGraph);
        }
        SDL_RenderPresent(fieldRenderer);
    }
    SDL_DestroyWindow(fieldWindow);
}

void Interface::setGraph(Graph *g){
    activeGraph = g;
}