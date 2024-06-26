#ifndef ACTORS_H
#define ACTORS_H

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3danim.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dskeleton.h>
#include "../include/config.h"
#include "../include/types.h"
#include "collision.h"
#include "debug.h"
#include "map.h"
#include "player.h"
#include "utils.h"

//Hills
extern T3DMat4FP* hillMatFP[NUM_HILLS];
extern T3DVec3 hillPos[NUM_HILLS];
extern AABB hillBox[NUM_HILLS];
extern rspq_block_t *dplHill[NUM_HILLS];
extern T3DModel *modelHill;

//Lilypads
extern T3DMat4FP* lilypadMatFP[NUM_LILYPADS];
extern T3DMat4FP* boxMatFP[NUM_LILYPADS];
extern T3DVec3 lilypadPos[NUM_LILYPADS];
extern AABB lilypadBox[NUM_LILYPADS];
extern rspq_block_t *dplLilypad[NUM_LILYPADS];
extern rspq_block_t *dplDebugBox[NUM_LILYPADS];
extern T3DModel *modelLilyPad;

// Springs
extern T3DMat4FP* springMatFP[NUM_SPRINGS];
extern T3DVec3 springPos[NUM_SPRINGS];
extern AABB springBox[NUM_SPRINGS];
extern rspq_block_t *dplSpring[NUM_SPRINGS];
extern rspq_block_t *dplDebugBox2[NUM_SPRINGS];
extern T3DModel *modelSpring;
extern T3DSkeleton springSkels[NUM_SPRINGS];
extern T3DSkeleton springSkelBlends[NUM_SPRINGS];
extern T3DAnim animsSpring[NUM_SPRINGS];
extern bool springActive[NUM_SPRINGS];
extern float springForce;

// Flys
extern T3DMat4FP* flyMatFP[NUM_FLYS];
extern T3DMat4FP* sphereFlyMatFP[NUM_FLYS];
extern T3DVec3 flyPos[NUM_FLYS];
extern T3DVec3 flyDir[NUM_FLYS];
extern float flyYaw[NUM_FLYS];
extern float flyPitch[NUM_FLYS];
extern Sphere flyBox[NUM_FLYS];
extern float flySpeed[NUM_FLYS];
extern bool flyActive[NUM_FLYS];
extern int flyPointV[NUM_FLYS];
extern FlyParams fly[NUM_FLYS];
extern rspq_block_t *dplFly[NUM_FLYS];
extern rspq_block_t *dplDebugSphereFly[NUM_FLYS];
extern T3DModel *modelFly;
extern T3DSkeleton flySkels[NUM_FLYS];
extern T3DSkeleton flySkelBlends[NUM_FLYS];
extern T3DAnim animsFlying[NUM_FLYS];
extern T3DAnim animsDeath[NUM_FLYS];
extern int flyHide[NUM_FLYS];

void check_actor_collisions(T3DVec3 *posA, T3DVec3 *posB, AABB *boxA, AABB *boxB, int targetCount);
void actors_init(void);
void hills_init(void);
void lilypads_init(void);
void springs_init(void);
void spring_update(void);
void flys_init(void);
void fly_update(void);
void actors_update(void);


#endif // ACTORS_H