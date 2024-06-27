#ifndef TYPES_H
#define TYPES_H

#include <libdragon.h>
#include <t3d/t3d.h>

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
    };
} CollisionShape;

typedef struct {
    CollisionShape shape;
} ActorHitBox;

// PLAYER
typedef struct {
    T3DVec3 pos;
    T3DVec3 dir;
    ActorHitBox hitbox;
    float speed;
    bool isActive;
    float length;
} ProjectileParams;

typedef struct {
    T3DVec3 moveDir;
    T3DVec3 pos;
    T3DVec3 shadowPos;
    T3DVec3 forward;
    ActorHitBox hitbox;
    ProjectileParams projectile;
    CameraParams cam;
    float yaw;
    float currSpeed;
    float animBlend;
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