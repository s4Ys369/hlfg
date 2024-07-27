#ifndef LEVELS_H
#define LEVELS_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "collision.h"
#include "debug.h"
#include "lvl1.h"
#include "map.h"
#include "utils.h"
#include "test_level.h"

extern Level levels[MAX_LEVELS];
extern int currLevel;
extern int prevLevel;

void level_init(Level* level);
void level_load(int currLevel);
void level_free(Level* level);

#endif // LEVELS_H