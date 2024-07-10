#ifndef TYPES_H
#define TYPES_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include "enums.h"
#include "globals.h"

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
    SURFACE_TYPE type;
    T3DVec3 posA;
    T3DVec3 posB;
    T3DVec3 posC;
    T3DVec3 center;
    T3DVec3 normal;
} Surface;

typedef struct {
    Surface surfaces[NUM_CELLS];
    int surfaceCount;
} Cell;

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
    T3DVec3 shadowRot;
    T3DVec3 forward;
    T3DVec3 vel;
    T3DVec3 rot;
    T3DVec3 scale;
    Sphere hitbox;
    ProjectileParams projectile;
    CameraParams cam;
    float currSpeed;
    float animBlend;
    bool isGrounded;
    float jumpForce;
    int score;
} PlayerParams;

#endif // TYPES_H