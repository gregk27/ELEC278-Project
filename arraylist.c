#include "arraylist.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct _t {
    char* message;
} Test;

void print(void* elem){
    printf("%s\n", ((Test*)elem)->message);
}

int main(){
    Arraylist *a;
    a = arraylist_create(10);
    arraylist_add(a, &(Test) {.message="Hello"});
    arraylist_add(a, &(Test) {.message="World"});
    arraylist_add(a, &(Test) {.message="This"});
    arraylist_add(a, &(Test) {.message="Is"});
    arraylist_add(a, &(Test) {.message="A"});
    arraylist_add(a, &(Test) {.message="Message"});
    arraylist_add(a, &(Test) {.message="Test"});
    arraylist_add(a, &(Test) {.message="Test 2"});
    arraylist_print(a,print);
    arraylist_add(a, &(Test) {.message="This"});
    arraylist_add(a, &(Test) {.message="Is"});
    arraylist_add(a, &(Test) {.message="Longer"});
    arraylist_add(a, &(Test) {.message="Now"});
    arraylist_print(a,print);

    printf("%s\n", ((Test*)a->elems[5])->message);
    return 0;
}


Arraylist *arraylist_create(int defaultSize){
    // Create arraylist
    Arraylist *l = malloc(sizeof(Arraylist));
    if(l == NULL) return NULL;
    l->length = 0;
    l->size = defaultSize;

    // Allocate memory for list
    l->elems = (void **) malloc(defaultSize*sizeof(void *));

    // Check that memory was allocated
    if(l->elems == NULL) return NULL;

    // Nullfiy contents
    for(int i=0; i<defaultSize; i++){
        l->elems[i] = NULL;
    }
    return l;
}

int arraylist_add(Arraylist *l, void *obj){
    if(l->length == l->size){
        // Increase allocated memory
        void **mem = (void **) realloc(l->elems, (l->size+1)*(sizeof(void *)));
        // Return on failure
        if(mem == NULL) return -1;
        // Update list
        l->elems = mem; 
        l->size ++;
    }
    // Add to the array
    l->elems[l->length] = obj;
    // Increase the length
    l->length ++;
    // Return the index of the added element
    return l->length-1;
}

void arraylist_print(Arraylist *l, void (*callback)(void*)){
    printf("Arraylist with %d/%d items\n", l->length, l->size);
    if(callback != NULL){
        for(int i=0; i<l->length; i++){
            printf("%d: ", i);
            callback(l->elems[i]);
        }
    }
}