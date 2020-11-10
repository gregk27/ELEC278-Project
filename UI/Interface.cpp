#include <string>
#include <stdbool.h>
#include "interface.h"
#include "../SDL2/SDL.h"
#include "../SDL2/SDL_render.h"
#include "../SDL_GFX/SDL_gfxPrimitives.h"
#include "../SDL_GFX/SDL_gfxBlitFunc.h"
#include "../SDL2/SDL_rect.h"
#include "../field/field.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"

using namespace Interface;

SDL_Window *fieldWindow;
SDL_Renderer *fieldRenderer;
SDL_Texture *fieldImage;
Graph *activeGraph;

SDL_Surface *generateGraph(Graph *g){
    SDL_Rect r;

    SDL_Surface *surf = SDL_CreateRGBSurface(0, 650*2, 320*2, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

    r.h=20;
    r.w=20;

    SDL_SetRenderDrawColor(fieldRenderer, 0,0,0,SDL_ALPHA_OPAQUE);
    g->adjacency.forEach([&surf,g](LinkedList<Graph::Edge>* l, int i){
        l->forEach([&surf,i,l,g](Graph::Edge e, int j){
            // If it's a going to a shot node, set the colour then revert
            if(e.end->type == Fieldpoint::Type::SHOTNODE){
                lineColor(surf, g->nodes[i]->x*2, g->nodes[i]->y*2, e.end->x*2, e.end->y*2, 0xFF00FFFF);
            } else { // Otherwise just draw the white line
                lineColor(surf, g->nodes[i]->x*2, g->nodes[i]->y*2, e.end->x*2, e.end->y*2, 0xFFFFFFFF);
            }
        });
    });

    g->nodes.forEach([&surf,&r](Fieldpoint *p, int i){
        // Set x and y, doubled because canavas is scaled up, subtract 10 to centre
        r.x = p->x*2-10;
        r.y = p->y*2-10;
        // Set the node colour based on owning alliance
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
        // If it's a shot node set the colour
        if(p->type == Fieldpoint::Type::SHOTNODE){
            SDL_SetRenderDrawColor(fieldRenderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderFillRect(fieldRenderer,&r);
    });

    return surf;
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
            SDL_RenderCopy(fieldRenderer, SDL_CreateTextureFromSurface(fieldRenderer, generateGraph(activeGraph)), NULL, &dest);
        }
        SDL_RenderPresent(fieldRenderer);
    }
    SDL_DestroyWindow(fieldWindow);
}

void Interface::setGraph(Graph *g){
    activeGraph = g;
}