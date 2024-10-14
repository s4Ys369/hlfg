#ifndef TYPES_H
#define TYPES_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
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
    SURFACE_TYPE type;
    T3DVec3 posA;
    T3DVec3 posB;
    T3DVec3 posC;
    T3DVec3 center;
    T3DVec3 normal;
} Surface;

typedef struct {
    Surface surf;
    float posY;
} RaycastResult;

typedef struct {
    Surface surface;
    float distance;
} SurfaceDistance;

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

typedef struct OctreeNode {
    T3DVec3 center;         // Center of this node's bounding box
    float halfSize;         // Half the size of the bounding box
    struct OctreeNode *children[8];  // Pointers to child nodes
    Actor **actors;         // List of actors in this node
    int actorCount;         // Number of actors in this node
    int maxActors;          // Maximum number of actors before splitting
} OctreeNode;

typedef void (*CollisionCallback)(Actor*, int);

// LEVELS
typedef struct {
    T3DVec3 pos;
    float radius;
    ActorHitBox hitbox;
} Warp;

typedef struct {
    int floorCount;
    Surface* floors;
    int slopeCount;
    Surface* slopes;
    int wallCount;
    Surface* walls;
    int totalSurfaceCount;
    Surface* surfaces;
    T3DMat4FP* matFP;
    T3DModel *model;
    rspq_block_t *dpl;
    Warp warp;
} Level;

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

// POINT LIGHTS
typedef struct {
    T3DVec3 pos;
    float size;
    bool ignoreNormals;
    color_t color;
} PointLight;

#endif // TYPES_H