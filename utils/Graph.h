#ifndef GRAPH_H
#define GRAPH_H
#include "LinkedList.h"
#include "../field/Fieldpoint.h"

class Graph {
    public: 
        typedef struct {
            Fieldpoint *end;
            int distance;
        } Edge;

        LinkedList<Fieldpoint *> nodes;
        LinkedList<LinkedList<Edge>*> adjacency;

        Graph() {};
        void addNode(Fieldpoint *f);
        void addNodes(Fieldpoint f[], int i);
        void addNodes(Defense b[], int i);
        void addEdge(Fieldpoint *a, Fieldpoint *b);
        void printAdj();
};

#endif // !GRAPH_H
