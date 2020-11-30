/**
 * Graph.cpp/h
 * These files contain code to generate and manage a graph
 * 
 * The graphs are hard-coded to work with Fieldnode
*/

#ifndef GRAPH_H
#define GRAPH_H
#include "LinkedList.h"
#include "../field/Fieldnode.h"

/**
 * Class representing a graph of Fieldnode
*/
class Graph {
    public: 
        // Struct representing a graph edge
        typedef struct {
            // Node at the end of the edge
            Fieldnode *end;
            // Distance from start to end
            int distance;
        } Edge;

        // Struct representing a node in Dijstra algorightm calculations
        struct DijkstraNode{
            // The node
            Fieldnode *node;
            // The previous node in the chain
            DijkstraNode *prev;
            // The weight to this node
            float weight;
            // The time to this node
            float time;
        };

        // List containing the nodes in the graph
        LinkedList<Fieldnode *> nodes;
        // Adjacency list representing the graph edges
        LinkedList<LinkedList<Edge>*> adjacency;

        // Create a new graph
        Graph() {};

        /**
         * Add a node to the graph
         * - f: The Fieldnode to add
         * 
         * Note: If the node is a defense, this will create a second clone node which represents crossing the defense leaving the courtyard (which is not worth points)
        */
        void addNode(Fieldnode *f);
        /**
         * Add a series of nodes
         * - f: Array of Fieldnodes to add
         * - i: The length of the array
         * See: addNode(Fieldnode *)
        */
        void addNodes(Fieldnode f[], int i);
        /**
         * Add a series of Defenses
         * - d: Array of Defenses to add
         * - i: The length of the array
         * See: addNode(Fieldnode *)
        */
        void addNodes(Defense d[], int i);

        /**
         * Add a bidirectional edge to the graph, automatically calcualtes weight as pythagorean distance between nodes
         * - a: The first node
         * - b: The second nodes
        */
        void addEdge(Fieldnode *a, Fieldnode *b);
        /**
         * Add a bidirectional edge to the graph, with a specified weight
         * - a:      The first node
         * - b:      The second nodes
         * - weight: The weight of the edge
        */
        void addEdge(Fieldnode *a, Fieldnode *b, int weight);
        /**
         * Add a directional edge to the graph, automatically calcualtes weight as pythagorean distance between nodes
         * - a: The start node
         * - b: The end node
        */
        void addDirectedEdge(Fieldnode *a, Fieldnode *b);
            /**
         * Add a directional edge to the graph, with a specified weight
         * - a: The start node
         * - b: The end node
        */
        void addDirectedEdge(Fieldnode *a, Fieldnode *b, int weight);

        /**
         * Add an edge with a defense, this will connect one way to the incoming node, and the other to the outgoing node
         * - d:         The defense
         * - f:         The other Fieldnode
         * - crossing:  If true, the entry will be connected to the incoming node (for centre-field)
        */
        void addDefenseEdge(Defense *d, Fieldnode *f, bool crossing);
        /**
         * Add an edge with a defense, this will connect one way to the incoming node, and the other to the outgoing node
         * - d:         The defense
         * - f:         The other Fieldnode
         * - crossing:  If true, the entry will be connected to the incoming node (for centre-field)
        */
        void addDefenseEdge(Fieldnode *f, Defense *d, bool crossing);
        
        /**
         * Print the adjacency list
        */
        void printAdj();
};

#endif // !GRAPH_H
