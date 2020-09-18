#include <stdio.h>
#include <stdbool.h>
#include "robot.h"
#include "game.h"
#include "utils.h"


int main(){

    Robot r;
    parse_csv("./robots.csv", &r, 1);

    print_bin(r.defenses, 16);

    printf("%d, %d, %d, %d\n",
    r.defenses,
    can_cross(&r, PORTCULLIS),
    can_cross(&r, SALLY_PORT), 
    can_cross(&r, ROCK_WALL));
}