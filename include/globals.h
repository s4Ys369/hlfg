#ifndef GLOBALS_H
#define GLOBALS_H

#include <libdragon.h>
#include <t3d/t3d.h>

#define VERSION 0.1
#define VERSION_SUFFIX 0

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define GRAVITY -100

// Used for struct memory allocation
#define MAX_PLAYERS 4
#define MAX_CRATES 4
#define MAX_BALLS 5
#define MAX_LEVELS 1

// Surface cells, starting off with same size as sm64
#define LEVEL_BOUNDARY_MAX  8192
#define CELL_SIZE 1024
#define CELL_HEIGHT_LIMIT           20000
#define FLOOR_LOWER_LIMIT           -11000
#define FLOOR_LOWER_LIMIT_MISC      (FLOOR_LOWER_LIMIT + 1000)
#define NUM_CELLS (2 * LEVEL_BOUNDARY_MAX / CELL_SIZE)
#define NUM_CELLS_INDEX (NUM_SURFACES_PER_CELL - 1)

extern uint8_t segmentID;

#endif // GLOBALS_H