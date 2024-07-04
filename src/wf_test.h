#ifndef WF_TEST_H
#define WF_TEST_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "debug.h"
#include "collision.h"
#include "utils.h"

extern int wfWallCount;
extern Surface wfWall[862];
extern int wfSlopeCount;
extern Surface wfSlope[62];
extern int wfFloorCount;
extern Surface wfFloor[264];
extern T3DMat4FP* wfMatFP;
extern T3DModel *modelWF;
extern rspq_block_t *dplWF;

void wf_init(void);

#endif // WF_TEST_H