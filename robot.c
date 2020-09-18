#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "robot.h"
#include "utils.h"

bool can_cross(Robot *r, Defence d){
    // Mask the defenses to check
    return (r->defenses & d) != 0;
}

/*
Parse a csv file containing robot information
Returns the number of robots found
*/
int parse_csv(char* filename, Robot *bots, int botCount){
    // Open the file
    FILE *f = fopen(filename, "r"); 
    if(f == NULL) return -1;

    // Buffer for read lines. No line following the correct format will exceed 64 characters
    char line[64];
    // The array index of the current entry
    int idx = 0;

    // Remove header line
    fgets (line, 128, f);
    // Read file
    while(fgets (line, 128, f) != NULL){
        // If we're at the end of the array, stop
        if(idx == botCount) break;
        
        // Parse data from line
        bots[idx].id = idx;
        bots[idx].team = (int) strtol(strtok(line, ","), NULL, 10);
        bots[idx].can_lowbar = (int) strtol(strtok(NULL, ","), NULL, 10);
        bots[idx].speed = (int) strtol(strtok(NULL, ","), NULL, 10);
        bots[idx].defenses = (int) strtol(strtok(NULL, ","), NULL, 16);

        // Increment the index
        idx ++;
    }
    printf("Parsed %d robot%c\n", idx, idx != 1 ? 'c' : ' ');
    return idx;
}