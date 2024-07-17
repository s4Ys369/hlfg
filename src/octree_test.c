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
#include "octree_test.h"
#include "player.h"
#include "test_level.h"
#include "utils.h"

T3DVec3 octreeCenter = {0.0f, 0.0f, 0.0f};  // Center of your game world
float octreeHalfSize = 600.0f;              // Half the size of your game world
int maxActorsPerNode = 4;                  // Maximum number of actors per node before splitting

OctreeNode* create_octree_node(T3DVec3 center, float halfSize, int maxActors) {
    OctreeNode *node = (OctreeNode *)malloc(sizeof(OctreeNode));
    node->center = center;
    node->halfSize = halfSize;
    node->actorCount = 0;
    node->maxActors = maxActors;
    node->actors = (Actor **)malloc(maxActors * sizeof(Actor *));
    for (int i = 0; i < 8; ++i) {
        node->children[i] = NULL;
    }
    return node;
}

int get_octant(OctreeNode *node, T3DVec3 *pos) {
    int octant = 0;
    if (pos->v[0] >= node->center.v[0]) octant |= 4;
    if (pos->v[1] >= node->center.v[1]) octant |= 2;
    if (pos->v[2] >= node->center.v[2]) octant |= 1;
    return octant;
}

void insert_actor(OctreeNode *node, Actor *actor) {
    if (node->actorCount < node->maxActors) {
        node->actors[node->actorCount++] = actor;
        return;
    }

    // If the node is full, split and reinsert the actors
    if (!node->children[0]) {
        float quarterSize = node->halfSize / 2.0f;
        for (int i = 0; i < 8; ++i) {
            T3DVec3 newCenter = node->center;
            newCenter.v[0] += (i & 4 ? quarterSize : -quarterSize);
            newCenter.v[1] += (i & 2 ? quarterSize : -quarterSize);
            newCenter.v[2] += (i & 1 ? quarterSize : -quarterSize);
            node->children[i] = create_octree_node(newCenter, quarterSize, node->maxActors);
        }

        for (int i = 0; i < node->actorCount; ++i) {
            int octant = get_octant(node, &node->actors[i]->pos);
            insert_actor(node->children[octant], node->actors[i]);
        }

        free(node->actors);
        node->actors = NULL;
        node->actorCount = 0;
    }

    int octant = get_octant(node, &actor->pos);
    insert_actor(node->children[octant], actor);
}

OctreeNode* create_octree(T3DVec3 center, float halfSize, int maxActors) {
    return create_octree_node(center, halfSize, maxActors);
}

void populate_octree(OctreeNode *root, Actor **actors, int actorCount) {
    for (int i = 0; i < actorCount; ++i) {
        insert_actor(root, actors[i]);
    }
}

// Check for actor collisions within a node
void check_actor_collisions_in_node(OctreeNode *node, Sphere *sphere, CollisionCallback collisionCallback, int playerCount) {
    if (!node) return;

    // Check for collisions within this node
    for (int i = 0; i < node->actorCount; ++i) {
        if (check_sphere_actor_collision(sphere, node->actors[i])) {
            collisionCallback(node->actors[i], playerCount);
        }
    }

    // Check for collisions in child nodes
    for (int i = 0; i < 8; ++i) {
        if (node->children[i]) {
            T3DVec3 diff;
            t3d_vec3_diff(&diff, &sphere->center, &node->children[i]->center);
            float distSq = t3d_vec3_len2(&diff);
            if (distSq < (sphere->radius + node->children[i]->halfSize) * (sphere->radius + node->children[i]->halfSize)) {
                check_actor_collisions_in_node(node->children[i], sphere, collisionCallback, playerCount);
            }
        }
    }
}

// Handle actor collisions using the octree
void handle_actor_octree_collisions(OctreeNode *root, Actor **actors, int actorCount, int playerCount) {
    Sphere playerSphere = player[playerCount]->hitbox;
    check_actor_collisions_in_node(root, &playerSphere, [](Actor *actor, int playerCount) {
        if (actor->hitbox.shape.type == SHAPE_BOX) {
            if (check_sphere_box_collision(player[playerCount]->hitbox, actor->hitbox.shape.aabb)) {
                if (actor->IsBouncy) {
                    resolve_sphere_collision_offset(player[playerCount]->hitbox, &actor->pos, 2.0f);
                    actor->pos.v[0] += player[playerCount]->forward.v[0] * player[playerCount]->currSpeed;
                    actor->pos.v[2] += player[playerCount]->forward.v[2] * player[playerCount]->currSpeed;
                }
                resolve_box_collision_offset_xz(actor->hitbox.shape.aabb, &player[playerCount]->hitbox.center, player[playerCount]->hitbox.radius);
                resolve_box_collision_offset_xz(actor->hitbox.shape.aabb, &player[playerCount]->pos, 0.2f);
                t3d_lerp(player[playerCount]->pos.v[0], player[playerCount]->hitbox.center.v[0], 0.2f);
                t3d_lerp(player[playerCount]->pos.v[2], player[playerCount]->hitbox.center.v[2], 0.2f);
            }
        } else if (actor->hitbox.shape.type == SHAPE_SPHERE) {
            if (check_sphere_collision(player[playerCount]->hitbox, actor->hitbox.shape.sphere)) {
                if (actor->IsBouncy) {
                    resolve_sphere_collision_offset(player[playerCount]->hitbox, &actor->hitbox.shape.sphere.center, 1.4f);
                }
                resolve_sphere_collision_xz(actor->hitbox.shape.sphere, &player[playerCount]->pos);
            }
        }
        // Add more collision handling logic as needed
    }, playerCount);
}

void free_octree(OctreeNode *node) {
    if (!node) return;
    for (int i = 0; i < 8; ++i) {
        free_octree(node->children[i]);
    }
    if (node->actors) {
        free(node->actors);
    }
    free(node);
}


/*

// Add to actors_init
OctreeNode *ballOctree = create_octree(octreeCenter, octreeHalfSize, maxActorsPerNode);
OctreeNode *boxOctree = create_octree(octreeCenter, octreeHalfSize, maxActorsPerNode);
populate_octree(ballOctree, balls, numBalls);
populate_octree(boxOctree, crates, numCrates);

// Add to player_update
handle_actor_octree_collisions(ballOctree, balls, numBalls, playerCount);
handle_actor_octree_collisions(boxOctree, crates, numCrates, playerCount);

// Add after main
free_octree(ballOctree);
free_octree(boxOctree);
*/