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
int currLevel = 0;
int prevLevel = 0;

void level_init(Level* level) {
    level->floorCount = 0;
    level->floors = NULL;
    level->slopeCount = 0;
    level->slopes = NULL;
    level->wallCount = 0;
    level->walls = NULL;
    level->totalSurfaceCount = 0;
    level->surfaces = NULL;
    level->matFP = NULL;
    level->model = NULL;
    level->dpl = NULL;
}

void level_load(int currLevel) {
    level_free(&levels[currLevel]);
    if(currLevel == 0){
        test_level_init();
        levels[currLevel].floorCount = testLevelFloorCount;
        levels[currLevel].floors = testLevelFloor;
        levels[currLevel].slopeCount = testLevelSlopeCount;
        levels[currLevel].slopes = testLevelSlope;
        levels[currLevel].wallCount = testLevelWallCount;
        levels[currLevel].walls = testLevelWall;
        levels[currLevel].totalSurfaceCount = testLevelSurfacesCount;
        levels[currLevel].surfaces = testLevelSurfaces;
        levels[currLevel].matFP = testLevelMatFP;
        levels[currLevel].model = modelTestLevel;
        levels[currLevel].dpl = dplTestLevel;
    }
    if(currLevel == 1){
        lvl1_init();
        levels[currLevel].floorCount = lvl1FloorCount;
        levels[currLevel].floors = lvl1Floor;
        levels[currLevel].slopeCount = lvl1SlopeCount;
        levels[currLevel].slopes = lvl1Slope;
        levels[currLevel].wallCount = lvl1WallCount;
        levels[currLevel].walls = lvl1Wall;
        levels[currLevel].totalSurfaceCount = lvl1SurfacesCount;
        levels[currLevel].surfaces = lvl1Surfaces;
        levels[currLevel].matFP = lvl1MatFP;
        levels[currLevel].model = modelLvl1;
        levels[currLevel].dpl = dplLvl1;
    }
}

void level_free(Level* level) {
    if (level->floors) {
        free(level->floors);
        level->floors = NULL;
    }
    if (level->slopes) {
        free(level->slopes);
        level->slopes = NULL;
    }
    if (level->walls) {
        free(level->walls);
        level->walls = NULL;
    }
    if (level->surfaces) {
        free(level->surfaces);
        level->surfaces = NULL;
    }
    if (level->matFP) {
        free_uncached(level->matFP);
        level->matFP = NULL;
    }
    if (level->model) {
        t3d_model_free(level->model);
        level->model = NULL;
    }
    if (level->dpl) {
        block_free_safe(level->dpl);
        level->dpl = NULL;
    }
    level_init(level);
}