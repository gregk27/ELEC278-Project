#include <stdio.h>
#include <stdbool.h>
#include "robot.h"
#include "game.h"
#include "utils.h"


int main(){
    Robot r = {
        .id = 0,
        .alliance = RED_ALLIANCE,
        .can_lowbar = true,
        .speed=5,
        .team=2708,
        .defenses = SOLO_DEFENSES
    };

    print_bin(r.defenses, 16);

    printf("%d, %d, %d, %d\n",
    r.defenses,
    can_cross(&r, PORTCULLIS),
    can_cross(&r, SALLY_PORT), 
    can_cross(&r, ROCK_WALL));
}