#ifndef TYPES_H
#define TYPES_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include "enums.h"

// CAMERA
typedef struct {
    T3DVec3 forward;
    T3DVec3 right;
} T3DVec3Pair;

typedef struct {
    T3DViewport viewport;
    T3DVec3 camPos;
    T3DVec3 camTarget;
    T3DVec3 camForward;
    T3DVec3 camRight;
    T3DVec3Pair camResults;
    float camYaw;
    int cam_mode;
} CameraParams;


// COLLISIONS
typedef struct {
    T3DVertPacked v[2];
} T3DQuad;

typedef struct {
    T3DVec3 min;
    T3DVec3 max;
} AABB;

typedef struct {
    T3DVec3 center;
    float radius;
} Sphere;

typedef struct {
    SHAPE_TYPE type;
    union {
        AABB aabb;
        Sphere sphere;
        // More to be added
    };
} CollisionShape;

typedef struct {
    CollisionShape shape;
} ActorHitBox;

typedef struct {
    T3DVec3 pos;
    T3DVec3 moveDir;
    T3DVec3 forward;
    T3DVec3 vel;
    T3DVec3 rot;
    ActorHitBox hitbox;
    bool isSafe;
    bool IsBouncy;
} Actor;

// PLAYER
typedef struct {
    T3DVec3 pos;
    T3DVec3 dir;
    Sphere hitbox;
    float speed;
    bool isActive;
    float length;
} ProjectileParams;

typedef struct {
    T3DVec3 moveDir;
    T3DVec3 pos;
    T3DVec3 shadowPos;
    T3DVec3 forward;
    T3DVec3 vel;
    Sphere hitbox;
    ProjectileParams projectile;
    CameraParams cam;
    float yaw;
    float currSpeed;
    float animBlend;
    bool isIdle;
    bool isAttack;
    bool isJumpStart;
    bool isJumping;
    bool isGrounded;
    bool isFalling;
    bool isWalking;
    float velY;
    float jumpForce;
    int score;
} PlayerParams;

#endif // TYPES_H