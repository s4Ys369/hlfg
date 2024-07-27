#ifndef COL_H
#define COL_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "debug.h"
#include "collision.h"
#include "utils.h"

extern T3DVec3 colVerts[25];

extern int colWallCount;
extern Surface* colWall;

extern int colSlopeCount;
extern Surface* colSlope;

extern int colFloorCount;
extern Surface* colFloor;

extern int colSurfacesCount;
extern Surface* colSurfaces;

extern T3DMat4FP* colMatFP;
extern T3DModel *modelCol;
extern rspq_block_t *dplCol;

void col_init(void);

#endif // COL_H
