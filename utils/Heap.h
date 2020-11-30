/**
 * Heap.h
 * This file contains code representing a heap
*/

#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <functional>
#include <string>


template <class T>
class Heap{
    private:
        /**
         * Get the index of the left child
         * - idx: The parent's index
         * Returns: Left child's index
        */
        int getLeft(int idx){
            return 2*idx+1;
        }

        /**
         * Get the index of the right child
         * - idx: The parent's index
         * Returns: Right child's index
        */
        int getRight(int idx){
            return 2*idx+2;
        }

        /**
         * Get the index of the parent
         * - idx: The child's index
         * Returns: Parent's index
        */
        int getParent(int idx){
            return (idx-1)/2;
        }

    public:
        // Vector containing heap data
        std::vector<T> data;
        // Function pointer used to compare 2 items
        std::function<bool(T, T)> comapre;
        // Function pointer used to get string representation of item
        std::function<const char*(T)> toString;

        /**
         * Create a new heap
         * - compare:  A function which takes 2 items, and returns true if the first item should be higher
         * - toString: A function which takes an item, and returns the text representation 
        */
        Heap<T>(std::function<bool(T, T)> comapre, std::function<const char*(T)> toString){
            this->comapre = comapre;
            this->toString = toString;
        }

        /**
         * Reheapify the list for a specific index
         * This will work it's way up the heap, swaping as needed
         * - idx: The index to start from
        */
        void reHeapify(int idx){
            int parent;
            T d = data[idx];
            while(idx != 0){
                parent = getParent(idx);
                // If it's the right place, insert and exit
                if(!comapre(d, data[parent])){
                    break;
                }
                // Otherwise copy value down and go up
                data[idx] = data[parent];
                idx = parent;
            }
            // Place wherever counter wound up
            data[idx] = d;
        }

        /**
         * Push a new item onto the heap
         * - d: The data to be added
        */
        void push(T d){
            int idx = data.size();
            data.push_back(d);
            reHeapify(idx);
        }

        /**
         * Pop the item from the heap
         * - out: Pointer to variable used to store result
         * - idx: Index to pop from
         * Returns: True if pop successful
        */
        bool pop(T *out, int idx){
            if(data.size() == 0){
                return false;
            }
            int lastIdx = data.size()-1;
            T toAdd = data[lastIdx];
            *out = data[idx];
            int parent = getParent(idx);
            // If it's smaller than parent, bubble up
            if(idx != 0 && comapre(toAdd, data[parent])){
                while(idx != 0){
                    parent = getParent(idx);
                    // If it's the right place, insert and exit
                    if(!comapre(toAdd, data[parent])){
                        break;
                    }
                    // Otherwise copy value down and go up
                    data[idx] = data[parent];
                    idx = parent;
                }
            } else { // Otherwise bubble down
                while(idx < lastIdx){
                    int right = getRight(idx);
                    int left = getLeft(idx);
                    // If the right is in bounds, the left will also be
                    if(right < lastIdx){
                        // Take the oposite of compare
                        if(!comapre(data[left],data[right])){
                            data[idx] = data[right];
                            idx = right;
                        } else {
                            data[idx] = data[left];
                            idx = left;
                        }
                    } else if(right == lastIdx) { // If there is only left child
                        if(comapre(data[left],toAdd)){
                            data[idx] = data[left];
                            idx = left;
                        } else {
                            break;
                        }
                    } else if(left >= lastIdx){ // If there are no children, break
                        break;
                    }
                }
            }
            data.pop_back();

            data[idx] = toAdd;
            reHeapify(idx);

            return true;
        }

        /**
         * Peek at the value at an index
         * - i: The index to peek at
         * Returns: A pointer to the item at that index
        */
        T *peek(int i){
            if(i >= data.size()) return NULL;
            return &data[i];
        }

        /**
         * Get the index of an item in the list
         * - isEqual: Function to be used to compare items
         * Returns: Index where isEqual returns true
        */
        int indexOf(std::function<bool(T)> isEqual){
            for(int i=0; i<data.size(); i++){
                if(isEqual(data[i])){
                    return i;
                }
            }
            return -1;
        }

        /**
         * Print whole tree. 
         * We cannot make it look pretty graphically, so we add some characters to make it a little easier to understand. 
         * - idx: The index to start from
         */
        void printTree (int idx)
        {
            // start of this tree
            printf("{");
            // values in the root node (assuming value is pointing to an integer)
            printf("(%s@%d),", toString(data[idx]), idx);
            
            // Now show left subtree or {} if there is no left subtree
            if (getLeft(idx) < data.size())	printTree(getLeft(idx));
            else							printf("{}");
            // Marker between left and right subtrees		
            printf(",");
            // Now show right subtree or {} if there is no right subtree
            if (getRight(idx) < data.size())	printTree(getRight(idx));
            else							printf("{}");
            // Close display of this tree with closing curly bracket	
            printf("}");
        }//printTree()
};


#endif // !HEAP_H
