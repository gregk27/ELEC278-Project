#ifndef ARRAYLIST_H
#define ARRAYLIST_H

// Structure defining an arraylist
typedef struct _arraylist {
    // Number of elements malloced
    int size;
    // Number of elements in the array
    int length;
    // Pointers to array elements
    void **elems;
} Arraylist;

/**
 * Create a new Arraylist.
 *  - defaultSize:  The initial size of the list, should be around the max number of items expected for efficiency
 * Returns: An empty Arraylist with specified length.
 */
Arraylist *arraylist_create(int defaultSize);

/**
 * Add an object to an arraylist
 *  - l:    The arralist to add to
 *  - obj:  Pointer to the object to be added
 * Returns: Index of added element, -1 on failure
 */
int arraylist_add(Arraylist *l, void *obj);

/**
 * Print info about an arraylist
 *  - l:        This list to print
 *  - callback: Optional callback to print info about each element
 */
void arraylist_print(Arraylist *l, void (*callback)(void*));

#endif // !ARRAYLIST_H