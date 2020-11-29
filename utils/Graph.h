#ifndef GRAPH_H
#define GRAPH_H
#include "LinkedList.h"
#include "../field/Fieldnode.h"


class Graph {
    public: 
        typedef struct {
            Fieldnode *end;
            int distance;
        } Edge;

        struct DijkstraNode{
            Fieldnode *node;
            DijkstraNode *prev;
            float weight;
            float time;
        };

        LinkedList<Fieldnode *> nodes;
        LinkedList<LinkedList<Edge>*> adjacency;

        Graph() {};
        void addNode(Fieldnode *f);
        void addNodes(Fieldnode f[], int i);
        void addNodes(Defense b[], int i);
        void addEdge(Fieldnode *a, Fieldnode *b);
        void addEdge(Fieldnode *a, Fieldnode *b, int weight);
        void addDirectedEdge(Fieldnode *a, Fieldnode *b);
        void addDirectedEdge(Fieldnode *a, Fieldnode *b, int weight);
        // If crossing is true, path will enter main node, if false path with enter alt node
        void addDefenseEdge(Defense *d, Fieldnode *f, bool crossing);
        void addDefenseEdge(Fieldnode *f, Defense *d, bool crossing);
        void printAdj();
};

#endif // !GRAPH_H
