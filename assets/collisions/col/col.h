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
extern Surface colWall[8];

extern int colSlopeCount;
extern Surface colSlope[13];

extern int colFloorCount;
extern Surface colFloor[11];

extern int colSurfacesCount;
extern Surface colSurfaces[32];

extern T3DMat4FP* colMatFP;
extern T3DModel *modelCol;
extern rspq_block_t *dplCol;

void col_init(void);

#endif // COL_H
