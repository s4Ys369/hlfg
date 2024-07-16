#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "collision.h"
#include "debug.h"
#include "levels.h"
#include "map.h"
#include "utils.h"
#include "test_level.h"

LevelSurfaces levels[MAX_LEVELS];
int currLevel = 0;

void levels_init(void) {
    levels[0].floorCount = testLevelFloorCount;
    levels[0].floors = testLevelFloor;
    levels[0].slopeCount = testLevelSlopeCount;
    levels[0].slopes = testLevelSlope;
    levels[0].wallCount = testLevelWallCount;
    levels[0].walls = testLevelWall;
    levels[0].totalSurfaceCount = testLevelSurfacesCount;
    levels[0].surfaces = testLevelSurfaces;
}