#ifndef LVL1_H
#define LVL1_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "debug.h"
#include "collision.h"
#include "utils.h"

extern T3DVec3 lvl1Verts[220];

extern int lvl1FloorCount;
extern Surface* lvl1Floor;

extern int lvl1WallCount;
extern Surface* lvl1Wall;

extern int lvl1SlopeCount;
extern Surface* lvl1Slope;

extern int lvl1SurfacesCount;
extern Surface* lvl1Surfaces;

extern T3DMat4FP* lvl1MatFP;
extern T3DModel *modelLvl1;
extern rspq_block_t *dplLvl1;

void lvl1_init(void);

#endif // LVL1_H
