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
LinkedList<Event> *eventList;
Node<Event> *event;
bool running = false;

void drawGraph(Graph *g){
    SDL_Rect r;
    r.h=20;
    r.w=20;

    SDL_SetRenderDrawColor(fieldRenderer, 0,0,0,SDL_ALPHA_OPAQUE);
    for(auto i : g->adjacency){
        LinkedList<Graph::Edge> *l = i.data;
        for(auto j : *l) {
            Graph::Edge e = j.data;
            if(e.end->type == Fieldpoint::Type::SHOTNODE || g->nodes[i.index]->type == Fieldpoint::Type::SHOTNODE){
                SDL_SetRenderDrawColor(fieldRenderer, 185, 115, 255, SDL_ALPHA_OPAQUE);
            } else {
                SDL_SetRenderDrawColor(fieldRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            }
            SDL_RenderDrawLine(fieldRenderer, g->nodes[i.index]->x*2, g->nodes[i.index]->y*2, e.end->x*2, e.end->y*2);
        }
    }

    for(auto i : g->nodes){
        Fieldpoint *p = i.data;
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
        if(p->type == Fieldpoint::Type::SHOTNODE){
            SDL_SetRenderDrawColor(fieldRenderer, 185, 115, 255, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderFillRect(fieldRenderer,&r);
    }

    if(event != NULL){
        if(event->data.location != NULL){
            r.x = event->data.location->x*2-15;
            r.y = event->data.location->y*2-15;
            r.h = 30;
            r.w = 30;
            SDL_SetRenderDrawColor(fieldRenderer, 64,128,255, SDL_ALPHA_OPAQUE*0.75);
            SDL_RenderFillRect(fieldRenderer, &r);
        }
        // If the event isn't the first, draw a line between it and the previous
        if(event->previous != eventList->getNode(-1)){
            SDL_SetRenderDrawColor(fieldRenderer, 64, 128, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(fieldRenderer, event->data.location->x*2, event->data.location->y*2, event->previous->data.location->x*2, event->previous->data.location->y*2);

        }
    }
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

    running = true;
    while(running){
        SDL_Event event;
        // Poll over events to prevent hanging
        // Close event not handeled as closure dictaded by console
        while(SDL_PollEvent(&event)) {
        }
        SDL_SetRenderDrawColor(fieldRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
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

void Interface::setEventList(LinkedList<Event> *e){
    eventList = e;
}

void Interface::setEvent(Node<Event> *e){
    event = e;
}

void Interface::close(){
    running = false;
}