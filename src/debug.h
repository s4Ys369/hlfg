#ifndef DEBUG_H
#define DEBUG_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "camera.h"
#include "collision.h"
#include "input.h"
#include "player.h"
#include "ui.h"
#include "utils.h"
#include "test_level.h"

extern T3DModel *modelDebugBox;
extern T3DModel *modelDebugSphere;
extern T3DMat4FP* boxLPMatFP[];
extern T3DMat4FP* boxSMatFP[];
extern T3DVertPacked* triVerts;
extern T3DMat4FP* triangleMatFP;
extern rspq_block_t *dplFloorTri;
extern rspq_block_t *dplSlopeTri;
extern rspq_block_t *dplWallTri;
extern int col_debug;
extern int text_debug;
extern int debug_mode;
extern int col_floor;
extern int col_slope;
extern int col_wall;
extern int matCount;
extern rspq_syncpoint_t syncPoint;

void debug_models_init(void);
void draw_debug_ui(void);


#endif // DEBUG_H