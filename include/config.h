#ifndef CONFIG_H
#define CONFIG_H

#include <libdragon.h>
#include <t3d/t3d.h>

// SEED is used for random number generation, see src/utils.c
#define SEED 15724

// See src/input.c
#define FORCE_PLAYERS 1

// Always print instead of just when R trigger is held
//#define FORCE_DEBUG_PRINT

#endif // CONFIG_H