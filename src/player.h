#ifndef PLAYER_H
#define PLAYER_H


#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3danim.h>
#include <t3d/t3dskeleton.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "actors.h"
#include "camera.h"
#include "collision.h"
#include "debug.h"
#include "input.h"
#include "map.h"
#include "sound.h"
#include "utils.h"

extern T3DMat4FP* playerMatFP[MAX_PLAYERS];
extern T3DMat4FP* shadowMatFP[MAX_PLAYERS];
extern T3DMat4FP* projectileMatFP[MAX_PLAYERS];
extern T3DMat4FP* playerhitboxMatFP[MAX_PLAYERS];
extern T3DMat4FP* projectilehitboxMatFP[MAX_PLAYERS];
extern T3DModel *modelPlayer;
extern T3DModel *modelProjectile;
extern T3DModel *modelShadow;
extern T3DSkeleton playerSkel[MAX_PLAYERS];
extern T3DSkeleton playerSkelBlend[MAX_PLAYERS];
extern T3DAnim animIdle[MAX_PLAYERS];
extern T3DAnim animWalk[MAX_PLAYERS];
extern T3DAnim animJump[MAX_PLAYERS];
extern T3DAnim animAttack[MAX_PLAYERS];
extern T3DAnim animFall[MAX_PLAYERS];
extern rspq_block_t *dplPlayerHitBox[MAX_PLAYERS];
extern rspq_block_t *dplProjectileHitBox[MAX_PLAYERS];
extern rspq_block_t *dplPlayer[MAX_PLAYERS];
extern rspq_block_t *dplProjectile[MAX_PLAYERS];
extern rspq_block_t *dplShadow[MAX_PLAYERS];
extern PlayerParams *player[MAX_PLAYERS];
extern int playerState[MAX_PLAYERS];
extern float playerScaleY[MAX_PLAYERS];

void check_player_collisions(PlayerParams *players[], int numPlayers);
void player_init(void);
void check_actor_collisions(Actor **actor, int actorCount, int playerCount);
void check_attack_collisions(Actor **actor, int actorCount, int playerCount);
void player_bounced(PlayerParams *player[], int playerCount) ;
void check_midair_actor_collisions(Actor **actor, int actorCount, int playerCount);
void player_update(void);


#endif // PLAYER_H