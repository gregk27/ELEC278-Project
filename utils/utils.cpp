/**
 * utils.cpp/h
 * These files contain a few random utilities that did not belong elsewhere, but were too small for own files
 */

#include <stdio.h>
#include <string>
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

ExceptionBase::ExceptionBase(const std::string msg){
    this->msg = msg;
}

const char * ExceptionBase::what () const throw () {
    return msg.c_str();
}
