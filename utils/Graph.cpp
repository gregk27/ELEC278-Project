/**
 * Graph.cpp/h
 * These files contain code to generate and manage a graph
 * 
 * The graphs are hard-coded to work with Fieldnode
*/

#include <math.h>
#include "Graph.h"

void Graph::addNode(Fieldnode *f){
    f->index = nodes.push(f);
    adjacency.push(new LinkedList<Edge>);
    // If it's a defense being added, primary will be used for entry-only, second for exit-only
    if(f->type == Fieldnode::Type::DEFENSE){
        Defense *d = new Defense(f->x, f->y, f->alliance, f->type);
        d->defType = ((Defense *)f)->defType;
        d->value = 0;
        d->index = nodes.push(d);
        adjacency.push(new LinkedList<Edge>);
    }
}

void Graph::addNodes(Fieldnode f[], int count){
    for(int i=0; i<count; i++){
        addNode(&f[i]);
    }
}

void Graph::addNodes(Defense f[], int count){
    for(int i=0; i<count; i++){
        addNode(&f[i]);
    }
}

void Graph::addEdge(Fieldnode *a, Fieldnode *b){
    addEdge(a, b, sqrt(pow(a->x-b->x, 2)+pow(a->y-b->y, 2)));
}

void Graph::addEdge(Fieldnode *a, Fieldnode *b, int distance){
    Edge e;
    e.end = b;
    e.distance = distance;
    adjacency[a->index]->push(e);
    e.end = a;
    adjacency[b->index]->push(e);
}

void Graph::addDirectedEdge(Fieldnode *a, Fieldnode *b){
    addDirectedEdge(a, b, sqrt(pow(a->x-b->x, 2)+pow(a->y-b->y, 2)));
}

void Graph::addDirectedEdge(Fieldnode *a, Fieldnode *b, int distance){
    Edge e;
    e.end = b;
    e.distance = distance;
    adjacency[a->index]->push(e);
}

void Graph::addDefenseEdge(Defense *d, Fieldnode *f, bool crossing){
    Edge e;
    e.distance = sqrt(pow(d->x-f->x, 2)+pow(d->y-f->y, 2));
    // If crossing is true, paths are from f>main, and alt>f
    if(crossing){
        e.end = d;
        adjacency[f->index]->push(e);
        e.end = f;
        adjacency[d->index+1]->push(e);
    } else {
        // If crossing is false, paths are from main>f and f>alt
        e.end = f;
        adjacency[d->index]->push(e);
        e.end = nodes[d->index+1];
        adjacency[f->index]->push(e);
    }
}

void Graph::addDefenseEdge(Fieldnode *f, Defense *d, bool crossing){
    addDefenseEdge(d, f, crossing);
}


void Graph::printAdj(){
    for(auto i : adjacency){
        printf("%d->", i.index);
        for(auto j : *(i.data)){
            printf("%d:%d,", j.data.end->index, j.data.distance);
        }
        printf("\n");
    }
}