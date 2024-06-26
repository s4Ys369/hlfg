#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/types.h"
#include "map.h"

extern T3DMat4FP* mapMatFP;
extern T3DModel *modelMap;
extern rspq_block_t *dplMap;
extern AABB FloorBox;
extern float groundLevel;

void map_init(void);

#endif // MAP_H