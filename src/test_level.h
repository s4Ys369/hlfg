#ifndef TEST_LEVEL_H
#define TEST_LEVEL_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "debug.h"
#include "collision.h"
#include "utils.h"


extern T3DVec3 testLevelVerts[196];

extern int testLevelFloorCount;
extern Surface testLevelFloor[130];

extern int testLevelSlopeCount;
extern Surface testLevelSlope[36];

extern int testLevelWallCount ;
extern Surface testLevelWall[184];

extern T3DMat4FP* testLevelMatFP;
extern T3DModel *modelTestLevel;
extern rspq_block_t *dplTestLevel;

void test_level_init(void);

#endif // TEST_LEVEL_H