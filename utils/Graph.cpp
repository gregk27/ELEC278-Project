#include <math.h>
#include "Graph.h"

void Graph::addNode(Fieldpoint *f){
    f->index = nodes.push(f);
    adjacency.push(new LinkedList<Edge>);
}

void Graph::addNodes(Fieldpoint f[], int count){
    for(int i=0; i<count; i++){
        addNode(&f[i]);
    }
}

void Graph::addNodes(Defense f[], int count){
    for(int i=0; i<count; i++){
        addNode(&f[i]);
    }
}

void Graph::addEdge(Fieldpoint *a, Fieldpoint *b){
    Edge e;
    e.end = b;
    e.distance = sqrt(pow(a->x-b->x, 2)+pow(a->y-b->y, 2));
    adjacency[a->index]->push(e);
    e.end = a;
    adjacency[b->index]->push(e);
}

void Graph::addEdge(Fieldpoint *a, Fieldpoint *b, int distance){
    Edge e;
    e.end = b;
    e.distance = distance;
    adjacency[a->index]->push(e);
    e.end = a;
    adjacency[b->index]->push(e);
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