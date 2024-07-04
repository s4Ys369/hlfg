#ifndef MAP_H
#define MAP_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "collision.h"
#include "debug.h"
#include "utils.h"
#include "test_level.h"

extern T3DMat4FP* mapMatFP;
extern T3DModel *modelMap;
extern rspq_block_t *dplMap;
extern AABB FloorBox;
extern float groundLevel;

extern T3DMat4FP* meshMatFP;
extern T3DModel *modelMesh;
extern rspq_block_t *dplMesh;

extern T3DMat4FP* mesh2MatFP;
extern T3DModel *modelMesh2;
extern rspq_block_t *dplMesh2;

extern int wallCount;
extern Surface Wall[8];
extern int slopeCount;
extern Surface Slope[13];
extern int floorCount;
extern Surface Floor[11];

extern int mesh2FloorCount;
extern Surface mesh2Floor[12];
extern int mesh2SlopeCount;
extern Surface mesh2Slope[30];
extern int mesh2WallCount;
extern Surface mesh2Wall[64];

void map_init(void);

#endif // MAP_H