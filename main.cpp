#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include "field/field.h"

int main(){

    printf("Hello World");

    // // Robot r;
    // // parse_csv("./robots.csv", &r, 1);

    // // print_bin(r.defenses, 16);

    // // printf("%d, %d, %d, %d\n",
    // // r.defenses,
    // // can_cross(&r, PORTCULLIS),
    // // can_cross(&r, SALLY_PORT), 
    // // can_cross(&r, ROCK_WALL));
    print_field(true);

    // std::cout << "/* message */" << std::endl;
    return 0;
}