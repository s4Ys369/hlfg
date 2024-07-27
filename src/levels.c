#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "collision.h"
#include "debug.h"
#include "levels.h"
#include "lvl1.h"
#include "map.h"
#include "utils.h"
#include "test_level.h"

Level levels[MAX_LEVELS];
int currLevel = 1;
int prevLevel = 0;

void levels_init(void) {
    test_level_init();
    levels[0].floorCount = testLevelFloorCount;
    levels[0].floors = testLevelFloor;
    levels[0].slopeCount = testLevelSlopeCount;
    levels[0].slopes = testLevelSlope;
    levels[0].wallCount = testLevelWallCount;
    levels[0].walls = testLevelWall;
    levels[0].totalSurfaceCount = testLevelSurfacesCount;
    levels[0].surfaces = testLevelSurfaces;
    levels[0].matFP = testLevelMatFP;
    levels[0].model = modelTestLevel;
    levels[0].dpl = dplTestLevel;

    lvl1_init();
    levels[1].floorCount = lvl1FloorCount;
    levels[1].floors = lvl1Floor;
    levels[1].slopeCount = lvl1SlopeCount;
    levels[1].slopes = lvl1Slope;
    levels[1].wallCount = lvl1WallCount;
    levels[1].walls = lvl1Wall;
    levels[1].totalSurfaceCount = lvl1SurfacesCount;
    levels[1].surfaces = lvl1Surfaces;
    levels[1].matFP = lvl1MatFP;
    levels[1].model = modelLvl1;
    levels[1].dpl = dplLvl1;
}