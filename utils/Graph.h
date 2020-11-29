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

        struct DijkstraNode{
            Fieldpoint *node;
            DijkstraNode *prev;
            float weight;
            float time;
        };

        LinkedList<Fieldpoint *> nodes;
        LinkedList<LinkedList<Edge>*> adjacency;

        Graph() {};
        void addNode(Fieldpoint *f);
        void addNodes(Fieldpoint f[], int i);
        void addNodes(Defense b[], int i);
        void addEdge(Fieldpoint *a, Fieldpoint *b);
        void addEdge(Fieldpoint *a, Fieldpoint *b, int weight);
        void addDirectedEdge(Fieldpoint *a, Fieldpoint *b);
        void addDirectedEdge(Fieldpoint *a, Fieldpoint *b, int weight);
        // If crossing is true, path will enter main node, if false path with enter alt node
        void addDefenseEdge(Defense *d, Fieldpoint *f, bool crossing);
        void addDefenseEdge(Fieldpoint *f, Defense *d, bool crossing);
        void printAdj();
};

#endif // !GRAPH_H
