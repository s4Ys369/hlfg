#ifndef CONFIG_H
#define CONFIG_H

#include <libdragon.h>
#include <t3d/t3d.h>

// SEED is used for random number generation, see src/utils.c
#define SEED 6969

// See src/input.c
#define ARES_1_PLAYER
//#define FORCE_4_PORTS

// Always print instead of just when R trigger is held
//#define DEBUG_PRINT

// Used for struct memory allocation
#define MAX_PLAYERS 4
#define MAX_CRATES 5
#define MAX_BALLS 10

#endif // CONFIG_H