#include "game.h"
const int HIGH_POINTS = 5;
const int LOW_POINTS = 2;

const int CROSS_POINTS = 5;

// Mask for all defenses
const unsigned int ALL_DEFENSES = PORTCULLIS|CHEVAL_DE_FRISE|MOAT|RAMPARTS|DRAWBRIDGE|SALLY_PORT|ROCK_WALL|ROUGH_TERRAIN;
// Mask for passive defenses (drive over)
const unsigned int PASSIVE_DEFENSES = MOAT|RAMPARTS|ROCK_WALL|ROUGH_TERRAIN;
// Mask for solo defenses (not sally port or drawbridge)
const unsigned int SOLO_DEFENSES = PORTCULLIS|CHEVAL_DE_FRISE|MOAT|RAMPARTS|ROCK_WALL|ROUGH_TERRAIN;
