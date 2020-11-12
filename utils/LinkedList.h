#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include <stdbool.h>
#include <functional>
#include <sstream>
#include <stdexcept>

/**
 * Node used in linkedlist
 * Supports generic data
 */
template <class T> 
class Node {
    public:
        // Next node in the list
        Node<T> *next;
        // Previous node in the list
        Node<T> *previous;
        // Node's data
        T data;
        /**
         * Create a new node
         *  - next: The next node in the list
         *  - previous: The previous node in the list
         *  - data: The node's data
         */
        Node(Node<T> *next, Node<T> *previous, T data){
            this->next = next;
            this->previous = previous;
            this->data = data;
        }
};

/**
 * Class used to represent Linked Lists
 * Can also represent Stacks and Queues
 * 
 * Uses a circular list format
 * Supports negative indicies, but not wraparound
 */
template <class T> 
class LinkedList{
    private:
        // The first node in the list
        Node<T> *first;
        // The number of nodes in the list
        int count;
    public:
        /**
         * Create a new linkedList
         */
        LinkedList(){
            this->first = NULL;
            this->count = 0;
        }

        /**
         * Get the size of the list
         * Returns: The number of nodes in the list
         */
        int size(){
            return this->count;
        }
        
        /**
         * Get a specific node
         * - i: The index of the node
         * Returns: A pointer to the node
         */
        Node<T> *getNode(int i){
            if(abs(i)>=this->size()){
                return NULL;
            }
            // If the index is closer going the opposite direction, the adjust it
            if(abs(i)>this->size()/2)
                i = (abs(i)-this->size()) * (i>0 ? 1 : -1);
            
            Node<T> *n = this->first;
            // Walk until the distance is 0
            while(i != 0){
                if(i > 0){
                    // Walk forward and reduce i
                    n = n->next;
                    i--;
                } else {
                    // Walk backward and increase i
                    n = n->previous;
                    i++;
                }
            }
            return n;
        }
        
        /**
         * Get the data at a point in the list
         *  - i:    The index of the data
         *  - data: Pointer to which data will be copied
         * Returns: True if index exists, otherwise false
         */ 
        bool get(int i, T *data){
            Node<T> *n = this->getNode(i);
            if(n != NULL){
                *data = n->data;
                return true;
            }
            return false;
        }
        
        /**
         * Get the data at the end of the list, calls get(-1, data)
         *  - data: Pointer to which data will be copied
         * Returns: True if list not empty, otherwise false
         */ 
        bool get_end(T *data){
            return this->get(-1, data);
        }

        /**
         * Get the data at a specified index, will throw out of range exception if exceeds size
         *  - i:    The index of the data
         * Returns: Data at that index
         */
        T operator[](int i){
            Node<T> *n = this->getNode(i);
            if(n != NULL){
                return n->data;
            }
            std::stringstream s;
            s << "Index " << i <<" out of bounds";
            throw std::out_of_range(s.str());
        }

        /**
         * Add data to the end of the list
         *  - data: The data to add
         * Returns: The index of the data
         */
        int push(T data){
            if(this->first == NULL){
                // Create node and make it the front
                this->first = new Node<T>(NULL, NULL, data);
                // Create    circular pointer
                this->first->next = this->first;
                this->first->previous = this->first;
            } else {
                // Create node and set its pointers
                Node<T> *n = new Node<T>(this->first, this->first->previous, data);
                // Set pointers of neighbour nodes
                n->previous->next = n;
                n->next->previous = n;
            }
            count ++;
            return count-1;
        }

        /**
         * Add data to the front of the list
         * - data: The data to add
         */
        void push_front(T data){
            // Add the node normally
            this->push(data);
            // Shift the pointer over
            this->first = this->first->previous;
        }

        /**
         * Set the data in a node
         *  - i: Index of node to set
         *  - data: Data to set
         */
        void set(int i, T data){
            Node<T> *n = this->getNode(i);
            if(n != NULL){
                n->data = data;
            }
        }

        /**
         * Remove an item from the list
         *  - i: The index of the item
         * Returns: The removed value
         */
        T remove(int i){
            // Get the node to delete
            Node<T> *n = this->getNode(i);
            // If there is only one node
            if(count == 1){
                this->first = NULL;
            } else {
                // Set its neighbours to point at eachother
                n->previous->next = n->next;
                n->next->previous = n->previous;
                // Move front pointer if applicable
                if(this->first == n){
                    this->first = n->next;
                }
            }
            // Reduce count
            count --;
            // Get the data to return
            T returnVal = n->data;
            // Delete the node
            delete n;

            return returnVal;
        }

        /**
         * Get and remove the last item in the list
         *  - data: Pointer to which data will be copied
         * Returns: True if not empty, otherwise false
         */
        bool pop(T *data){
            if(get(-1, data)){
                remove(-1);
                return true;
            }
            return false;
        }

        /**
         * Iterate over the list with a lambda function
         * - fun: Lambda function of the format: (T,int)-> void, T is data at node, int is index of node
         */ 
        void forEach(std::function<void(T, int)> fun){
            this->forEachNode([fun](Node<T> *n, int i)-> void {
                fun(n->data, i);
            });
        }

        /**
         * Iterate over the list with a lambda function
         * - fun: Lambda function of the format: (Node<T>,int)-> void, Node<T> is the node, int is index of node
         */
        void forEachNode(std::function<void(Node<T>*, int)> fun){
            Node<T> *n = this->first;
            for(int i=0; i<this->size(); i++){
                fun(n, i);
                n = n->next;
            }
        }

        /**
         * Find a node in the list
         * - fun: Comparator function that will be called for each node. Will return when this returns false
         * Returns: The index of the target node, -1 if not found
         */
        int find(std::function<bool(T)> fun){
            Node<T> *n = this->first;
            for(int i=0; i<this->size(); i++){
                if(fun(n->data)){
                    return i;
                }
                n = n->next;
            }
            return -1;
        }

        /**
         * Insert a node into the list at position based on callback
         *  - node: The node to insert
         *  - fun:  Callback comparison function, the node will be inserted when this returns true. First arg is new data, second is node before, second arg is node after. If node is end, second arg will be NULL
         * Returns: The index where the node is inserted
         */
        int orderedInsert(T data, std::function<bool(T, T, T)> fun){

            // If the list is empty automatically add to front
            if(size() == 0){
                push(data);
                return 0;
            }

            Node<T> *n = this->first;
            // Check for front insert cases
            if(fun(data, NULL, n->data)){
                push_front(data);
                return 0;
            }

            // Loop through to find correct place
            for(int i=0; i<this->size(); i++){
                // If we have reached the end of the list, just push it on the back
                if(n->next == first){
                    push(data);
                    return this->size()-1;
                }

                // If this is the correct place, run the insert
                if(fun(data, n->data, n->next->data)){
                    // Create a node from the data
                    Node<T> *node = new Node<T>(n->next, n, data);
                    // Update neighbours
                    n->next->previous = node;
                    n->next = node;

                    count ++;
                    return i;
                }
                n = n->next;
            }
            return 0;
        }

        class Iterator {
            public: 
                Node<T> *current;
                
                Iterator(Node<T> *start){
                    this->current = start;
                }

                bool operator== (const Iterator& other){
                    return current == other.current;   
                }

                bool operator!= (const Iterator& other){
                    return current != other.current;   
                }

                const Iterator& operator++ () {
                    current = current->next;
                    return *this;
                }

                const T operator* (){
                    return current->data;
                }
        };

        Iterator begin(){
            return Iterator(first);
        }
        Iterator end(){
            return Iterator(getNode(-1));
        }
    
};


#endif // !LINKEDLIST_H
