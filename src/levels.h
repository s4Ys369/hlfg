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
#include "map.h"
#include "utils.h"
#include "test_level.h"

extern LevelSurfaces levels[MAX_LEVELS];
extern int currLevel;

void levels_init(void);

#endif // LEVELS_H