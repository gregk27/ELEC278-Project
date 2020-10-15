#include <stdio.h>
#include "utils.h"


void print_bin(int num, int length){
    for(int i=length-1; i>=0; i--){
        if(num & 0b1<<i)
            printf("1");
        else
            printf("0");
        if(i % 4 == 0)
            printf(" ");
        num >> 1;
    }
    printf("\n");
}