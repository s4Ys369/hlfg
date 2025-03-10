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
#include "utils/debug.h"
#include "input.h"
#include "levels.h"
#include "map.h"
#include "octree_test.h"
#include "sound.h"
#include "utils/utils.h"
#include "levels/test_level.h"

extern T3DModel *modelPlayer;
extern T3DModel *modelProjectile;
extern T3DModel *modelShadow;
extern Player *player[MAX_PLAYERS];
extern int playerState[MAX_PLAYERS];
extern int airAttackCount;

void check_player_collisions(Player *players[], int numPlayers);
void player_init(void);
void check_actor_collisions(Actor **actor, int actorCount, int playerCount);
void check_attack_collisions(Actor **actor, int actorCount, int playerCount);
void player_bounced(Player *player[], int playerCount) ;
void check_midair_actor_collisions(Actor **actor, int actorCount, int playerCount);
void player_update(void);
void player_free(int numPlayers);


#endif // PLAYER_H