/**
 * Console.cpp/h
 * These files contain the code used for displaying the GUI
 */

#ifndef INTERFACE_H
#define INTERFACE_H
#include "../SDL2/SDL.h"
#include "../game.h"
#include "../utils/utils.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"

/**
 * Namespace with functions to interact with interface
*/
namespace Interface {
    /**
     * Start the interface.
     * This will block the thread 
    */
    void init();

    /**
     * Set the graph to display
     * - g: Pointer to the graph 
     */
    void setGraph(Graph *g);
    /**
     * Set the event list to use
     * - e: Pointer to the event list
    */
    void setEventList(LinkedList<Event> *e);
    /**
     * Set the currently selected event
     * - e: Pointer to the event
    */
    void setEvent(Node<Event> *e);
    /**
     * Cycle graph visibility between hidden, nodes only, and nodes+edges
    */
    void toggleGraph();
    /**
     * Close the graph, by extent ending the thread
    */
    void close();

    // Exception thrown when window creation fails
    struct window_creation_exception: public ExceptionBase{
        using ExceptionBase::ExceptionBase;
    };
}

#endif // !INTERFACE_H
