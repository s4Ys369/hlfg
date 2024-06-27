#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3ddebug.h>
#include "../include/types.h"
#include "camera.h"
#include "input.h"
#include "player.h"

extern T3DModel *modelDebugBox;
extern T3DModel *modelDebugSphere;
extern T3DMat4FP* boxMatFP[];
extern int col_debug;

void debug_models_init(void);
void draw_debug_ui(void);


#endif // DEBUG_H