/**
 * heaptest.cpp
 * Small class used to test heap functionality while developing 
 */

#include <stdio.h>
#include <sstream>
#include "../utils/Heap.h"


int main(){
    Heap<int> h = Heap<int>([](int a, int b)->bool{return a > b;}, [](int i)->const char*{
        std::stringstream s;
        s << i << ",";
        return s.str().c_str();
    });


    h.push(10);
    h.push(9);
    h.push(8);
    h.push(7);
    h.push(6);
    h.push(5);
    h.push(4);
    h.push(3);
    h.push(2);
    h.push(1);
    int t;
    for(int i = 0; i<100; i++){
        h.pop(&t, 4);
        h.push(i+t);
    }


}