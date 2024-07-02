#ifndef MAP_H
#define MAP_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/types.h"
#include "debug.h"
#include "utils.h"

extern T3DMat4FP* mapMatFP;
extern T3DModel *modelMap;
extern rspq_block_t *dplMap;
extern AABB FloorBox;
extern float groundLevel;

extern T3DMat4FP* meshMatFP;
extern T3DModel *modelMesh;
extern rspq_block_t *dplMesh;

extern int wallCount;
extern Surface Wall[8];
extern int slopeCount;
extern Surface Slope[13];
extern int floorCount;
extern Surface Floor[11];

void map_init(void);

#endif // MAP_H