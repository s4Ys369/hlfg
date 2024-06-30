#ifndef DEBUG_H
#define DEBUG_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3ddebug.h>
#include "../include/config.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "camera.h"
#include "input.h"
#include "player.h"

extern T3DModel *modelDebugBox;
extern T3DModel *modelDebugSphere;
extern T3DMat4FP* boxLPMatFP[];
extern T3DMat4FP* boxSMatFP[];
extern int col_debug;
extern int matCount;

void debug_models_init(void);
void draw_debug_ui(void);


#endif // DEBUG_H