#ifndef ACTORS_H
#define ACTORS_H


#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/types.h"
#include "collision.h"
#include "debug.h"
#include "map.h"
#include "player.h"
#include "utils.h"

// Crates
extern T3DMat4FP* crateMatFP[MAX_CRATES];
extern rspq_block_t *dplCrate[MAX_CRATES];
extern T3DModel *modelCrate;
extern Actor *crates[MAX_CRATES];
extern int numCrates;

// Balls
extern T3DMat4FP* ballMatFP[MAX_BALLS];
extern rspq_block_t *dplBall[MAX_BALLS];
extern T3DModel *modelBall;
extern Actor *balls[MAX_BALLS];
extern int numBalls;
extern bool ballBounced[MAX_BALLS];
extern float ballVelY[MAX_BALLS];
extern float ballBounceForce[MAX_BALLS];

void resolve_actor_to_actor_col(Actor *origin, Actor **target, int targetCount, int originCount);
void crates_init(void);
void balls_init(void);
void actors_init(void);
void balls_update(void);
void crates_update(void);
void actors_update(void);


#endif // ACTORS_H