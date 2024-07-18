#ifndef MESH2_H
#define MESH2_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "debug.h"
#include "collision.h"
#include "utils.h"

extern T3DVec3 mesh2Verts[62];

extern int mesh2FloorCount;
extern Surface mesh2Floor[12];

extern int mesh2SlopeCount;
extern Surface mesh2Slope[30];

extern int mesh2WallCount;
extern Surface mesh2Wall[64];

extern int mesh2SurfacesCount;
extern Surface mesh2Surfaces[106];

extern T3DMat4FP* mesh2MatFP;
extern T3DModel *modelMesh2;
extern rspq_block_t *dplMesh2;

void mesh2_init(void);

#endif // MESH2_H
