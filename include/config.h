#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>

// SEED is used to place objects at random
#define SEED 69

// NUM_PLAYERS must be at least 1
#define NUM_PLAYERS 1

// Optimized setting, but modifiable
#define NUM_HILLS 4
#define NUM_LILYPADS 5
#define NUM_SPRINGS 3
#define NUM_FLYS 20
#define FLY_DRAW_DIST 150

#endif // CONFIG_H