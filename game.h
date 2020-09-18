#ifndef GAME_H
#define GAME_H

const int HIGH_POINTS;
const int LOW_POINTS;

const int CROSS_POINTS;

/* 
Bitmask flags for each defense
Examples:
    Passive ---- 0xF0F0
    Most solos - 0xF0FF
    Cross all -- 0xFFFF
NOTE: While binary flags would be more efficient, this leaves room for extra data
*/
typedef enum _defence 
{
    // Category A
    PORTCULLIS      = 0x3*0x1, // Fill lower 2 bits, shift by 0
    CHEVAL_DE_FRISE = 0xC*0x1, // Fill upper 2 bits, shift by 0
    // Category B
    MOAT            = 0x3*0x10, // Fill lower 2 bits, shfit by 1 byte
    RAMPARTS        = 0xC*0x10, // Fill upper 2 bits, shift by 1 byte
    // Category C
    DRAWBRIDGE      = 0x3*0x100,
    SALLY_PORT      = 0xC*0x100,
    // Category D
    ROCK_WALL       = 0x3*0x1000,
    ROUGH_TERRAIN   = 0xC*0x1000
} Defence;

// Mask for all defenses
const unsigned int ALL_DEFENSES;
// Mask for passive defenses (drive over)
const unsigned int PASSIVE_DEFENSES;
// Mask for solo defenses (not sally port or drawbridge)
const unsigned int SOLO_DEFENSES;

#endif // !GAME_H