#ifndef OCTREE_TEST_H
#define OCTREE_TEST_H

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/globals.h"
#include "../include/enums.h"
#include "../include/types.h"
#include "actors.h"
#include "collision.h"
#include "debug.h"
#include "map.h"
#include "player.h"
#include "test_level.h"
#include "utils.h"

extern T3DVec3 octreeCenter;
extern float octreeHalfSize;
extern int maxActorsPerNode;   

OctreeNode* create_octree(T3DVec3 center, float halfSize, int maxActors);
void populate_octree(OctreeNode *root, Actor **actors, int actorCount);
void handle_actor_octree_collisions(OctreeNode *root, Actor **actors, int actorCount, int playerCount);
void free_octree(OctreeNode *node);

#endif // OCTREE_TEST_H