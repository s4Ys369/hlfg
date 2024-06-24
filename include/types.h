#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include "config.h"

typedef struct {
    T3DVec3 forward;
    T3DVec3 right;
} T3DVec3Pair;

typedef struct {
    T3DVec3 min;
    T3DVec3 max;
} AABB;

typedef struct {
    T3DVec3 center;
    float radius;
} Sphere;

typedef enum {
    SHAPE_BOX,
    SHAPE_SPHERE
} ShapeType;

typedef struct {
    ShapeType type;
    union {
        AABB aabb;
        Sphere sphere;
    };
} CollisionShape;

typedef struct {
    CollisionShape shape;
} ActorHitBox;

typedef struct {
    T3DVec3 pos;
    T3DVec3 dir;
    Sphere hitbox;
    float speed;
    bool isActive;
    float length;
} TongueParams;

typedef struct {
    T3DVec3 pos;
    T3DVec3 dir;
    float yaw;
    float pitch;
    Sphere hitbox;
    float speed;
    bool isActive;
    int pointValue;
} FlyParams;

typedef struct {
    T3DVec3 moveDir;
    T3DVec3 playerPos;
    T3DVec3 shadowPos;
    T3DVec3 playerForward;
    Sphere playerBox;
    TongueParams tongue[NUM_PLAYERS];
    float rotY;
    float currSpeed;
    float animBlend;
    bool isAttack;
    bool isJumpStart;
    bool isJumping;
    bool isGrounded;
    bool isFalling;
    bool isWalking;
    float playerVelocityY;
    float gravity;
    float jumpForce;
    int score;
    int tongueRetract;
    bool activateSpring[NUM_SPRINGS];
} PlayerParams;

#endif // TYPES_H