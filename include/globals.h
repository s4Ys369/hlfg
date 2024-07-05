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

extern uint8_t segmentID;

#endif // GLOBALS_H