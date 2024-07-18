#ifndef TESTLEVEL_H
#define TESTLEVEL_H

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

extern int testLevelWallCount;
extern Surface testLevelWall[184];

extern int testLevelSurfacesCount;
extern Surface testLevelSurfaces[350];

extern T3DMat4FP* testLevelMatFP;
extern T3DModel *modelTestlevel;
extern rspq_block_t *dplTestlevel;

void testLevel_init(void);

#endif // TESTLEVEL_H
