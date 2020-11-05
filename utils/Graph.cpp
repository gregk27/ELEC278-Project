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

void Graph::printAdj(){
    adjacency.forEach([](LinkedList<Edge> *l, int i)->void {
        printf("%d->", i);
        l->forEach([](Edge e, int i)->void {
            printf("%d:%d,", e.end->index, e.distance);
        });
        printf("\n");
    });
}
