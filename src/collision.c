#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "collision.h"
#include "utils.h"

T3DVec3 center = {{0,0,0}};
T3DVec3 norm = {{0,1,0}};
T3DVec3 up = {{0,1,0}};
T3DVec3 down = {{0,-1,0}};
T3DVec3 left = {{-1,0,0}};
T3DVec3 right = {{1,0,0}};
T3DVec3 farther = {{0,0,-1}};
T3DVec3 nearer = {{0,0,1}};

// Check AABB to AABB
bool check_box_collision(AABB a, AABB b) {
// Check for overlap along the X axis
    bool overlapX = (a.min.v[0] <= b.max.v[0] && a.max.v[0] >= b.min.v[0]);
    // Check for overlap along the Y axis
    bool overlapY = (a.min.v[1] <= b.max.v[1] && a.max.v[1] >= b.min.v[1]);
    // Check for overlap along the Z axis
    bool overlapZ = (a.min.v[2] <= b.max.v[2] && a.max.v[2] >= b.min.v[2]);

    // A collision occurs if there is overlap along all three axes
    return overlapX && overlapY && overlapZ;

}

void calculate_collision_point(AABB a, AABB b, T3DVec3 *collision_point) {
    collision_point->v[0] = (fmaxf(a.min.v[0], b.min.v[0]) + fminf(a.max.v[0], b.max.v[0])) / 2.0f;
    collision_point->v[1] = (fmaxf(a.min.v[1], b.min.v[1]) + fminf(a.max.v[1], b.max.v[1])) / 2.0f;
    collision_point->v[2] = (fmaxf(a.min.v[2], b.min.v[2]) + fminf(a.max.v[2], b.max.v[2])) / 2.0f;
}

// Move pos outside of AABB
void resolve_box_collision(AABB aabb, T3DVec3 *pos) {
    // Check if the point is inside the AABB
    if (pos->v[0] >= aabb.min.v[0] && pos->v[0] <= aabb.max.v[0] &&
        pos->v[1] >= aabb.min.v[1] && pos->v[1] <= aabb.max.v[1] &&
        pos->v[2] >= aabb.min.v[2] && pos->v[2] <= aabb.max.v[2]) {

        // Find the closest edge and move the point to it
        float dxMin = fabsf(pos->v[0] - aabb.min.v[0]);
        float dxMax = fabsf(pos->v[0] - aabb.max.v[0]);
        float dyMin = fabsf(pos->v[1] - aabb.min.v[1]);
        float dyMax = fabsf(pos->v[1] - aabb.max.v[1]);
        float dzMin = fabsf(pos->v[2] - aabb.min.v[2]);
        float dzMax = fabsf(pos->v[2] - aabb.max.v[2]);

        float minDist = fminf(fminf(dxMin, dxMax), fminf(dyMin, dyMax));
        minDist = fminf(minDist, fminf(dzMin, dzMax));

        if (minDist == dxMin) {
            pos->v[0] = aabb.min.v[0];
        } else if (minDist == dxMax) {
            pos->v[0] = aabb.max.v[0];
        } else if (minDist == dyMin) {
            pos->v[1] = aabb.min.v[1];
        } else if (minDist == dyMax) {
            pos->v[1] = aabb.max.v[1];
        } else if (minDist == dzMin) {
            pos->v[2] = aabb.min.v[2];
        } else if (minDist == dzMax) {
            pos->v[2] = aabb.max.v[2];
        }
    }
}

// Move position outside AABB only along X and Z
void resolve_box_collision_xz(AABB aabb, T3DVec3 *pos) {
    // Calculate the dimensions of the AABB
    float width = aabb.max.v[0] - aabb.min.v[0];
    float depth = aabb.max.v[2] - aabb.min.v[2];
    
    // Check if the point is inside the AABB
    if (pos->v[0] >= aabb.min.v[0] && pos->v[0] <= aabb.max.v[0] &&
        pos->v[1] >= aabb.min.v[1] && pos->v[1] <= aabb.max.v[1] &&
        pos->v[2] >= aabb.min.v[2] && pos->v[2] <= aabb.max.v[2]) {

        // Find the closest edge and move the point to it, only considering x and z
        float dxMin = fabsf(pos->v[0] - aabb.min.v[0]);
        float dxMax = fabsf(pos->v[0] - aabb.max.v[0]);
        float dzMin = fabsf(pos->v[2] - aabb.min.v[2]);
        float dzMax = fabsf(pos->v[2] - aabb.max.v[2]);

        float minDist = fminf(fminf(dxMin, dxMax), fminf(dzMin, dzMax));

        if (minDist == dxMin) { pos->v[0] = aabb.min.v[0] - width; return; }
        if (minDist == dxMax) { pos->v[0] = aabb.max.v[0] + width; return; }
        if (minDist == dzMin) { pos->v[2] = aabb.min.v[2] - depth; return; }
        if (minDist == dzMax) { pos->v[2] = aabb.max.v[2] + depth; return; }
    }
}

// Move pos outside of AABB
void resolve_box_collision_offset(AABB aabb, T3DVec3 *pos, float offset) {
    // Check if the point is inside the AABB
    if (pos->v[0] >= aabb.min.v[0] && pos->v[0] <= aabb.max.v[0] &&
        pos->v[1] >= aabb.min.v[1] && pos->v[1] <= aabb.max.v[1] &&
        pos->v[2] >= aabb.min.v[2] && pos->v[2] <= aabb.max.v[2]) {

        // Find the closest edge and move the point to it
        float dxMin = fabsf(pos->v[0] - aabb.min.v[0]);
        float dxMax = fabsf(pos->v[0] - aabb.max.v[0]);
        float dyMin = fabsf(pos->v[1] - aabb.min.v[1]);
        float dyMax = fabsf(pos->v[1] - aabb.max.v[1]);
        float dzMin = fabsf(pos->v[2] - aabb.min.v[2]);
        float dzMax = fabsf(pos->v[2] - aabb.max.v[2]);

        float minDist = fminf(fminf(dxMin, dxMax), fminf(dyMin, dyMax));
        minDist = fminf(minDist, fminf(dzMin, dzMax));

        if (minDist == dxMin) {
            pos->v[0] = aabb.min.v[0] - offset;
        } else if (minDist == dxMax) {
            pos->v[0] = aabb.max.v[0] + offset;
        } else if (minDist == dyMin) {
            pos->v[1] = aabb.min.v[1] - offset;
        } else if (minDist == dyMax) {
            pos->v[1] = aabb.max.v[1] + offset;
        } else if (minDist == dzMin) {
            pos->v[2] = aabb.min.v[2] - offset;
        } else if (minDist == dzMax) {
            pos->v[2] = aabb.max.v[2] + offset;
        }
    }
}

// Move position outside AABB only along X and Z
void resolve_box_collision_offset_xz(AABB aabb, T3DVec3 *pos, float offset) {
    // Calculate the dimensions of the AABB
    float width = aabb.max.v[0] - aabb.min.v[0];
    float depth = aabb.max.v[2] - aabb.min.v[2];

    // Calculate the offset as a fraction of the AABB's dimensions
    float offsetX = width * offset;
    float offsetZ = depth * offset;
    
    // Check if the point is inside the AABB
    if (pos->v[0] >= aabb.min.v[0] && pos->v[0] <= aabb.max.v[0] &&
        pos->v[1] >= aabb.min.v[1] && pos->v[1] <= aabb.max.v[1] &&
        pos->v[2] >= aabb.min.v[2] && pos->v[2] <= aabb.max.v[2]) {

        // Find the closest edge and move the point to it, only considering x and z
        float dxMin = fabsf(pos->v[0] - aabb.min.v[0]);
        float dxMax = fabsf(pos->v[0] - aabb.max.v[0]);
        float dzMin = fabsf(pos->v[2] - aabb.min.v[2]);
        float dzMax = fabsf(pos->v[2] - aabb.max.v[2]);

        float minDist = fminf(fminf(dxMin, dxMax), fminf(dzMin, dzMax));

        if (minDist == dxMin) { pos->v[0] = aabb.min.v[0] - offsetX; return; }
        if (minDist == dxMax) { pos->v[0] = aabb.max.v[0] + offsetX; return; }
        if (minDist == dzMin) { pos->v[2] = aabb.min.v[2] - offsetZ; return; }
        if (minDist == dzMax) { pos->v[2] = aabb.max.v[2] + offsetZ; return; }
    }
}


// Check for sphere to sphere
bool check_sphere_collision(Sphere a, Sphere b) {
    // Calculate the squared distance between centers
    float distanceSquared = t3d_vec3_distance(&a.center, &b.center);
    float radiusSquared = a.radius + b.radius;

    // Check collision
    float e = 1e-6f;
    if (distanceSquared <= (radiusSquared + e)) {
        return true; // Collision detected
    } else {
        return false; // No collision
    }
}

void resolve_sphere_collision(Sphere sphere, T3DVec3 *pos) {
    // Calculate the vector from the sphere's center to the point
    T3DVec3 direction;
    t3d_vec3_diff(&direction, pos, &sphere.center);

    // Normalize the direction vector
    t3d_vec3_norm(&direction);

    // Calculate the distance from the sphere's center to the position
    float distance = t3d_vec3_distance(&sphere.center, pos);

    // If the point is within the sphere, resolve the collision
    if (distance < sphere.radius) {
        // Calculate the target position on the surface of the sphere
        float targetDistance = sphere.radius + 1e-6f;
        pos->v[0] = sphere.center.v[0] + direction.v[0] * targetDistance;
        pos->v[1] = sphere.center.v[1] + direction.v[1] * targetDistance;
        pos->v[2] = sphere.center.v[2] + direction.v[2] * targetDistance;

        // Move point to away from center of sphere
        pos->v[0] = sphere.center.v[0] + (pos->v[0] - sphere.center.v[0]);
        pos->v[1] = sphere.center.v[1] + (pos->v[1] - sphere.center.v[1]);
        pos->v[2] = sphere.center.v[2] + (pos->v[2] - sphere.center.v[2]);
    }
}

void resolve_sphere_collision_xz(Sphere sphere, T3DVec3 *pos) {
    // Calculate the vector from the sphere's center to the point
    T3DVec3 direction;
    t3d_vec3_diff(&direction, pos, &sphere.center);

    // Normalize the direction vector
    t3d_vec3_norm(&direction);

    // Calculate the distance from the sphere's center to the position
    float distance = t3d_vec3_distance(&sphere.center, pos);

    // If the point is within the sphere, resolve the collision
    if (distance < sphere.radius) {
        // Calculate the target position on the surface of the sphere
        float targetDistance = sphere.radius + 1e-6f;
        pos->v[0] = sphere.center.v[0] + direction.v[0] * targetDistance;
        pos->v[2] = sphere.center.v[2] + direction.v[2] * targetDistance;

        // Move point to away from center of sphere
        pos->v[0] = sphere.center.v[0] + (pos->v[0] - sphere.center.v[0]);
        pos->v[2] = sphere.center.v[2] + (pos->v[2] - sphere.center.v[2]);
    }
}

void resolve_sphere_collision_offset(Sphere sphere, T3DVec3 *pos, float offset) {
    // Calculate the vector from the sphere's center to the point
    T3DVec3 direction;
    t3d_vec3_diff(&direction, pos, &sphere.center);

    // Normalize the direction vector
    t3d_vec3_norm(&direction);

    // Calculate the distance from the sphere's center to the position
    float distance = t3d_vec3_distance(&sphere.center, pos);

    // If the point is within the sphere, resolve the collision
    if (distance < sphere.radius) {
        // Calculate the target position on the surface of the sphere
        float targetDistance = sphere.radius + 1e-6f;
        pos->v[0] = sphere.center.v[0] + direction.v[0] * targetDistance;
        pos->v[1] = sphere.center.v[1] + direction.v[1] * targetDistance;
        pos->v[2] = sphere.center.v[2] + direction.v[2] * targetDistance;

        // Apply offset to smooth the movement
        pos->v[0] = sphere.center.v[0] + (pos->v[0] - sphere.center.v[0]) * offset;
        pos->v[1] = sphere.center.v[1] + (pos->v[1] - sphere.center.v[1]) * offset;
        pos->v[2] = sphere.center.v[2] + (pos->v[2] - sphere.center.v[2]) * offset;
    }
}

void resolve_sphere_collision_offset_xz(Sphere sphere, T3DVec3 *pos, float offset) {
    // Calculate the vector from the sphere's center to the point
    T3DVec3 direction;
    t3d_vec3_diff(&direction, pos, &sphere.center);

    // Normalize the direction vector
    t3d_vec3_norm(&direction);

    // Calculate the distance from the sphere's center to the position
    float distance = t3d_vec3_distance(&sphere.center, pos);

    // If the point is within the sphere, resolve the collision
    if (distance < sphere.radius) {
        // Calculate the target position on the surface of the sphere
        float targetDistance = sphere.radius + 1e-6f;
        pos->v[0] = sphere.center.v[0] + direction.v[0] * targetDistance;
        pos->v[2] = sphere.center.v[2] + direction.v[2] * targetDistance;

        // Apply offset to smooth the movement
        pos->v[0] = sphere.center.v[0] + (pos->v[0] - sphere.center.v[0]) * offset;
        pos->v[2] = sphere.center.v[2] + (pos->v[2] - sphere.center.v[2]) * offset;
    }
}


// Check for sphere to AABB, use resolve_box_collision
bool check_sphere_box_collision(Sphere sphere, AABB box) {
    // Find the closest point on the AABB to the sphere's center
    float closestX = clamp(sphere.center.v[0], box.min.v[0], box.max.v[0]);
    float closestY = clamp(sphere.center.v[1], box.min.v[1], box.max.v[1]);
    float closestZ = clamp(sphere.center.v[2], box.min.v[2], box.max.v[2]);

    // Calculate the distance between the sphere's center and this closest point
    float distanceX = sphere.center.v[0] - closestX;
    float distanceY = sphere.center.v[1] - closestY;
    float distanceZ = sphere.center.v[2] - closestZ;

    // Calculate the squared distance and compare with squared radius
    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY) + (distanceZ * distanceZ);
    float radiusSquared = sphere.radius * sphere.radius;

    // If the squared distance is less than the squared radius, there is a collision
    float e = 1e-6f;
    return distanceSquared <= (radiusSquared + e);
}


// QUADS
float point_plane_dist(T3DVec3 point, T3DVec3 planePoint, T3DVec3 planeNormal) {
    T3DVec3 diff;
    t3d_vec3_diff(&diff, &point, &planePoint);
    return t3d_vec3_dot(&diff, &planeNormal);
}

T3DVec3 project_point_on_plane(T3DVec3 point, T3DVec3 planePoint, T3DVec3 planeNormal) {
    float distance = point_plane_dist(point, planePoint, planeNormal);
    T3DVec3 scaledNormal = {{planeNormal.v[0] * distance, planeNormal.v[1] * distance, planeNormal.v[2] * distance}};
    T3DVec3 diff;
    t3d_vec3_diff(&diff, &point, &scaledNormal);
    return diff;
}
// Function to compute the center of quad as a vector3
T3DVec3 compute_quad_center(T3DQuad quad) {
    T3DVec3 center;
    center.v[0] = (float)(quad.v[0].posA[0] + quad.v[0].posB[0] + quad.v[1].posA[0] + quad.v[1].posB[0]) / 4.0f;
    center.v[1] = (float)(quad.v[0].posA[1] + quad.v[0].posB[1] + quad.v[1].posA[1] + quad.v[1].posB[1]) / 4.0f;
    center.v[2] = (float)(quad.v[0].posA[2] + quad.v[0].posB[2] + quad.v[1].posA[2] + quad.v[1].posB[2]) / 4.0f;
    
    return center;
}

int point_in_quad(T3DVec3 point, T3DQuad quad) {
    // Check if the point is inside the quad using a point-in-polygon test in 3D
    T3DVec3 A, B, C, u, v, w;

    A.v[0] = (float)(quad.v[0].posA[0]);
    A.v[1] = (float)(quad.v[0].posA[1]);
    A.v[2] = (float)(quad.v[0].posA[2]);

    B.v[0] = (float)(quad.v[0].posB[0]);
    B.v[1] = (float)(quad.v[0].posB[1]);
    B.v[2] = (float)(quad.v[0].posB[2]);

    C.v[0] = (float)(quad.v[1].posA[0]);
    C.v[1] = (float)(quad.v[1].posA[1]);
    C.v[2] = (float)(quad.v[1].posA[2]);

    t3d_vec3_diff(&u, &B, &A);
    t3d_vec3_diff(&v, &C, &A);
    t3d_vec3_diff(&w, &point, &A);

    float uu = t3d_vec3_dot(&u, &u);
    float uv = t3d_vec3_dot(&u, &v);
    float vv = t3d_vec3_dot(&v, &v);
    float wu = t3d_vec3_dot(&w, &u);
    float wv = t3d_vec3_dot(&w, &v);

    float denominator = uv * uv - uu * vv;
    if (denominator == 0){
        denominator = 0.01f;
    }

    float s = (uv * wv - vv * wu) / denominator;
    float t = (uv * wu - uu * wv) / denominator;

    return (s >= 0.1f) && (t >= 0.1f) && (s + t <= 1.0f);
}

float calc_dist_to_quad(T3DVec3 point, T3DQuad quad) {
    T3DVec3 A, B, C, u, v, planeNormal;
    
    A.v[0] = (float)(quad.v[0].posA[0]);
    A.v[1] = (float)(quad.v[0].posA[1]);
    A.v[2] = (float)(quad.v[0].posA[2]);

    B.v[0] = (float)(quad.v[0].posB[0]);
    B.v[1] = (float)(quad.v[0].posB[1]);
    B.v[2] = (float)(quad.v[0].posB[2]);

    C.v[0] = (float)(quad.v[1].posA[0]);
    C.v[1] = (float)(quad.v[1].posA[1]);
    C.v[2] = (float)(quad.v[1].posA[2]);

    t3d_vec3_diff(&u, &B, &A);
    t3d_vec3_diff(&v, &C, &A);

    t3d_vec3_cross(&planeNormal, &u, &v);

    if(planeNormal.v > 0){
        t3d_vec3_norm(&planeNormal);
    }
    T3DVec3 projectedPoint = project_point_on_plane(point, A, planeNormal);

    if (point_in_quad(projectedPoint, quad)) {
        return fabsf(point_plane_dist(point, A, planeNormal));
    }

    // If the point is outside the quad, find the minimum distance to the edges or vertices
    float minDistance = FLT_MAX;
    T3DVec3 edge, pointToVertex, projection;
    T3DVec3 *current = malloc_uncached(sizeof(T3DVec3));
    T3DVec3 *next = malloc_uncached(sizeof(T3DVec3));

    for (int i = 0; i < 2; i++) {

        current->v[0] = (float)(quad.v[i].posA[0]);
        current->v[1] = (float)(quad.v[i].posA[1]);
        current->v[2] = (float)(quad.v[i].posA[2]);
        next->v[0] = (float)(quad.v[i].posB[0]);
        next->v[1] = (float)(quad.v[i].posB[1]);
        next->v[2] = (float)(quad.v[i].posB[2]);


        t3d_vec3_diff(&edge, next, current);
        t3d_vec3_diff(&pointToVertex, &point, current);
        float t = t3d_vec3_dot(&pointToVertex, &edge) / t3d_vec3_dot(&edge, &edge);

        if (t < 0.0f) {
            minDistance = fminf(minDistance, t3d_vec3_distance(&point, current));
        } else if (t > 1.0f) {
            minDistance = fminf(minDistance, t3d_vec3_distance(&point, next));
        } else {
            projection = (T3DVec3){{current->v[0] + t * edge.v[0], 
                                    current->v[1] + t * edge.v[1], 
                                    current->v[2] + t * edge.v[2]}};
            minDistance = fminf(minDistance, t3d_vec3_distance(&point, &projection));
        }
    }

    return sqrtf(minDistance);
}

T3DVec3 reflect_velocity(T3DVec3 velocity, T3DVec3 normal) {
    float dotProduct = t3d_vec3_dot(&velocity, &normal);
    T3DVec3 reflectionVel = {{velocity.v[0] - 2 * dotProduct * normal.v[0], 
                              velocity.v[1] - 2 * dotProduct * normal.v[1], 
                              velocity.v[2] - 2 * dotProduct * normal.v[2]}};
    return reflectionVel;
}


// Function to resolve slope collision in 3D
void resolve_slope_collision(T3DVec3 position, T3DVec3 velocity, T3DQuad quad) {
    
    // Check collision with the slope (assuming slope is a quad)
    if (point_in_quad(position, quad)) {
        // Move the object's position to the slope's surface
        // For simplicity, assume we adjust the object's position to lie on the quad
        position.v[1] = quad.v[0].posA[1]; // Adjust this based on slope geometry
        
        // Adjust the velocity to move along the slope's normal direction
        // For now, we reset the velocity to zero to simulate a frictionless slope
        velocity.v[0] = -velocity.v[0];
        velocity.v[2] = -velocity.v[2];
    }
}

T3DVec3 get_quad_normal(T3DQuad quad) {
 
    T3DVec3 normalA, normalB, normalC;
    t3d_vert_unpack_normal(quad.v[0].normA, &normalA);
    t3d_vert_unpack_normal(quad.v[0].normB, &normalB);
    t3d_vert_unpack_normal(quad.v[1].normA, &normalC);

    T3DVec3 u, v, quadNormal;
    t3d_vec3_diff(&u, &normalB, &normalA);
    t3d_vec3_diff(&v, &normalC, &normalA);
    t3d_vec3_cross(&quadNormal, &u, &v);
    t3d_vec3_norm(&quadNormal);
    
    return quadNormal;
}

T3DQuad get_closest_quad(T3DVec3 originPos, T3DModel* targetModel, int targetModelCount){
    T3DVertPacked* verts = t3d_model_get_vertices(targetModel);
    T3DQuad closestQuad;
    float minDistance = FLT_MAX;

    for (uint16_t i = 0; i < targetModel->totalVertCount; i += 2) {

        // Calculate the center of the closest quad
        T3DQuad currQuad = {{verts[i],verts[i+1]}};
        T3DVec3 quadCenter = compute_quad_center(currQuad);

        float distance = t3d_vec3_distance(&originPos, &quadCenter);
        if (distance < minDistance) {
            minDistance = distance;

            closestQuad = currQuad;
        }
    }
    return closestQuad;
}

bool check_sphere_quad_collision(Sphere a, T3DQuad quad) {
    // Calculate the squared distance between centers
    float distanceSquared = calc_dist_to_quad(a.center, quad);

    // Check collision
    float e = 1e-6f;
    if (distanceSquared <= (a.radius + e)) {
        return true; // Collision detected
    } else {
        return false; // No collision
    }
}

// Function to calculate the D value for a plane given its normal and a point on the plane
float calculate_plane_d(T3DVec3 planeNormal, T3DVec3 pointOnPlane) {
    return t3d_vec3_dot(&planeNormal, &pointOnPlane);
}

// Function to resolve the intersection of a sphere with a quad
void resolve_sphere_quad_collision(T3DVec3* sphereCenter, float sphereRadius, T3DVec3 planeNormal, float planeD) {
    // Calculate the signed distance from the sphere center to the plane
    float signedDistance = (planeNormal.v[0] * sphereCenter->v[0] + planeNormal.v[1] * sphereCenter->v[1] + planeNormal.v[2] * sphereCenter->v[2] + planeD) /
                           sqrtf(planeNormal.v[0] * planeNormal.v[0] + planeNormal.v[1] * planeNormal.v[1] + planeNormal.v[2] * planeNormal.v[2]);
    
    // If the sphere intersects the plane, resolve the collision
    if (fabsf(signedDistance) <= sphereRadius) {
        // Calculate the penetration depth
        float penetrationDepth = sphereRadius - fabsf(signedDistance);
        
        // Move the sphere center along the plane normal direction to resolve the intersection
        sphereCenter->v[0] -= penetrationDepth * (signedDistance > 0 ? planeNormal.v[0] : -planeNormal.v[0]);
        sphereCenter->v[1] -= penetrationDepth * (signedDistance > 0 ? planeNormal.v[1] : -planeNormal.v[1]);
        sphereCenter->v[2] -= penetrationDepth * (signedDistance > 0 ? planeNormal.v[2] : -planeNormal.v[2]);
    }
}

//SURFACES
T3DVec3 calc_surface_center(Surface surf) {
    T3DVec3 centroid;
    centroid.v[0] = (surf.posA.v[0] + surf.posB.v[0] + surf.posC.v[0]) / 3.0f;
    centroid.v[1] = (surf.posA.v[1] + surf.posB.v[1] + surf.posC.v[1]) / 3.0f;
    centroid.v[2] = (surf.posA.v[2] + surf.posB.v[2] + surf.posC.v[2]) / 3.0f;
    return centroid;
}

T3DVec3 calc_surface_norm(Surface surf) {
    T3DVec3 edge1;  t3d_vec3_diff(&edge1, &surf.posB, &surf.posA);
    T3DVec3 edge2;  t3d_vec3_diff(&edge2, &surf.posC, &surf.posA);
    T3DVec3 normal; t3d_vec3_cross(&normal, &edge1, &edge2);
    t3d_vec3_norm(&normal);
    return normal;
}

// Function to calculate the distance to surface
float distance_to_surface(T3DVec3 position, Surface surf) {

    // Calculate vectors from triangle vertices
    T3DVec3 AB;
    T3DVec3 AC;
    t3d_vec3_diff(&AB, &surf.posB, &surf.posA);
    t3d_vec3_diff(&AC, &surf.posC, &surf.posA);
    
    // Calculate normal vector of the triangle
    T3DVec3 N;
    t3d_vec3_cross(&N, &AB, &AC);

    // Calculate vector from any vertex of surface to the position
    T3DVec3 PA;
    t3d_vec3_diff(&PA, &position, &surf.posA); 

    // Calculate distance from position to the plane of the surface
    float dotProduct = t3d_vec3_dot(&N, &PA);
    float N_mag = t3d_vec3_len(&N);
    if(N_mag < 0.001f){
        N_mag = 0.001f;
    }
    float dist = fabsf(dotProduct) / N_mag;

    if(surf.type == SURFACE_FLOOR) {
        dist = fabsf(position.v[1] - surf.center.v[1]);
    }

    return dist;
}

// Function to check sphere collision with a surface
bool check_sphere_surface_collision(Sphere sphere, Surface surf) {
    // Calculate distance from sphere center to the surface
    float dist = distance_to_surface(sphere.center, surf);
    float dist2 = t3d_vec3_distance(&sphere.center, &surf.center);
    //float dist3 = t3d_vec3_distance(&sphere.center, &surf.normal);

    // Check distances per surface
    if(surf.type == SURFACE_SLOPE) {
        if (dist <= sphere.radius*1.2f) {
            if (dist2 <= sphere.radius*5.0f) {
                return true;
            } else {
               return false; 
            }
        } else {
            // No collision
            return false;
        }
    } else if(surf.type == SURFACE_WALL) {
        if (dist < sphere.radius) {
            return true;
        } else {
            return false;
        }
    } else if(surf.type == SURFACE_FLOOR) {
        if (dist <= sphere.radius*1.7f) {
            if (dist2 <= sphere.radius*5.0f) {
                return true;
            } else {
               return false; 
            }
        } else {
            // No collision
            return false;
        }
    } else {
        if (dist <= sphere.radius) {
            if (dist2 <= sphere.radius) {
                return true;
            } else {
               return false; 
            }
        } else {
            return false;
        }
    }
}

bool check_box_surface_collision(AABB a, Surface surf) {
// Check for overlap along the X axis
    bool overlapX = (a.min.v[0] <= surf.center.v[0] && a.max.v[0] >= surf.center.v[0]);
    // Check for overlap along the Y axis
    bool overlapY = (a.min.v[1] <= surf.center.v[1] && a.max.v[1] >= surf.center.v[1]);
    // Check for overlap along the Z axis
    bool overlapZ = (a.min.v[2] <= surf.center.v[2] && a.max.v[2] >= surf.center.v[2]);

    // A collision occurs if there is overlap along all three axes
    return overlapX && overlapY && overlapZ;

}

Surface find_closest_surface(T3DVec3 position, Surface* surfaces, int numSurfaces) {
    float minDistance = FLT_MAX;
    float dist = FLT_MIN;
    Surface closestSurface;

    for (int i = 0; i < numSurfaces; ++i) {
        dist = t3d_vec3_distance(&position, &surfaces[i].center);
        if (!isnan(dist) && dist < minDistance) {
            minDistance = dist;
            closestSurface = surfaces[i];
        }
    }

    return closestSurface;
}

// Function to resolve collision between sphere and surface
void resolve_sphere_surface_collision(Sphere *sphere, T3DVec3 *position, T3DVec3 *velocity, Surface *surf) {
    // Calculate normal vector of the triangle
    T3DVec3 AB, AC;
    t3d_vec3_diff(&AB, &surf->posB, &surf->posA);
    t3d_vec3_diff(&AC, &surf->posC, &surf->posA);
    
    T3DVec3 N;
    t3d_vec3_cross(&N, &AB, &AC);
    t3d_vec3_norm(&N);

    // Calculate vector from surface to sphere center
    T3DVec3 surf_to_sphere;
    t3d_vec3_diff(&surf_to_sphere, &sphere->center, &surf->posA);

    // Calculate penetration depth
    float dist = t3d_vec3_dot(&N, &surf_to_sphere);
    float penetration_depth = sphere->radius - dist;

    // Calculate collision point on the surface
    T3DVec3 collision_point;
    t3d_vec3_scale(&collision_point, &N, penetration_depth);
    t3d_vec3_add(&collision_point, &sphere->center, &collision_point);

    // Resolve collision: move sphere center along the normal vector
    T3DVec3 move_direction;
    if(surf->type == SURFACE_SLOPE) {
        t3d_vec3_scale(&move_direction, &N, penetration_depth);
        t3d_vec3_add(&sphere->center, &sphere->center, &move_direction);
        position->v[1] = collision_point.v[1] - sphere->radius;
 
    }
    if(surf->type == SURFACE_WALL) {

        t3d_vec3_scale(&move_direction, &N, (penetration_depth*1.1f));
        
        sphere->center.v[0] = t3d_lerp(sphere->center.v[0], sphere->center.v[0] + move_direction.v[0], 0.7f);
        sphere->center.v[2] = t3d_lerp(sphere->center.v[2], sphere->center.v[2] + move_direction.v[2], 0.7f);


        velocity->v[0] = velocity->v[0] * 0.5f; // Damp velocity to prevent oscillation
        velocity->v[2] = velocity->v[2] * 0.5f;
        position->v[0] = sphere->center.v[0];
        position->v[2] = sphere->center.v[2];
    }
    if(surf->type == SURFACE_FLOOR) {
        t3d_vec3_scale(&move_direction, &N, penetration_depth);
        sphere->center.v[0] = sphere->center.v[0] + move_direction.v[0];
        sphere->center.v[2] = sphere->center.v[2] + move_direction.v[2];
        position->v[0] = sphere->center.v[0];
        position->v[2] = sphere->center.v[2];
        //t3d_vec3_add(&sphere->center, &sphere->center, &move_direction);
        sphere->center.v[1] = collision_point.v[1];
 
    }
}

// Function to check if a ray intersects a surface
float intersectionY;
bool ray_intersects_surface(T3DVec3 rayOrigin, T3DVec3 rayDir, Surface surface, float* intersectionAngle) {
    T3DVec3 vertex0 = surface.posA;
    T3DVec3 vertex1 = surface.posB;
    T3DVec3 vertex2 = surface.posC;

    T3DVec3 edge1;
    t3d_vec3_diff(&edge1, &vertex1, &vertex0);
    T3DVec3 edge2;
    t3d_vec3_diff(&edge2, &vertex2, &vertex0);

    T3DVec3 h;
    t3d_vec3_cross(&h, &rayDir, &edge2);
    float a = t3d_vec3_dot(&edge1, &h);
    if (a > -FLT_MIN && a < FLT_MIN) {
        return false; // Ray is parallel to the triangle
    }
    if (a == 0){
        a = FLT_MIN;
    }
    float f = 1.0f / a;
    T3DVec3 s;
    t3d_vec3_diff(&s, &rayOrigin, &vertex0);
    float u = f * t3d_vec3_dot(&s, &h);
    if (u < 0.0f || u > 1.0f) {
        return false; // Intersection is outside the triangle
    }
    T3DVec3 q;
    t3d_vec3_cross(&q, &s, &edge1);
    float v = f * t3d_vec3_dot(&rayDir, &q);
    if (v < 0.0f || u + v > 1.0f) {
        return false; // Intersection is outside the triangle
    }
    float t = f * t3d_vec3_dot(&edge2, &q);
    if (t > FLT_MIN) { // Intersection point is on the ray
        *intersectionAngle = rayOrigin.v[1] - t; // Intersection point's Y value
        return true;
    } else {
        return false; // Intersection point is behind the ray origin
    }
}

// Function to cast a ray and find the closest intersection point with the surfaces downwards
RaycastResult closest_surface_below_raycast(T3DVec3 startPos, Surface* surfaces, int surfaceCount) {
    Surface closestSurface;
    RaycastResult closestRayResult;
    float closestDist = FLT_MAX;
    float dist = FLT_MIN;

    for (int i = 0; i < surfaceCount; i++) {
        Surface currentSurface = surfaces[i];
        // Check for intersection of the ray with the current surface
        if (ray_intersects_surface(startPos, down, currentSurface, &intersectionY)) {
          dist = fabsf(startPos.v[1] - intersectionY);
          if (dist < closestDist) {
            closestDist = dist;
            closestSurface = currentSurface;
          }
        }
    }

    closestRayResult.surf = closestSurface;
    if(!isnan(intersectionY)){
        closestRayResult.posY = intersectionY;
    } else {
        closestRayResult.posY = 0;
    }
    return closestRayResult;
}

// Function to compare two SurfaceDistance structures by distance
int compare_surface_distance(const void* a, const void* b) {
    SurfaceDistance* sd1 = (SurfaceDistance*)a;
    SurfaceDistance* sd2 = (SurfaceDistance*)b;
    if (sd1->distance < sd2->distance) return -1;
    if (sd1->distance > sd2->distance) return 1;
    return 0;
}

// Function to find the closest 4 surfaces of the same type within a specified range
void find_closest_surfaces(T3DVec3 position, Surface* surfaces, int numSurfaces, Surface* closestSurfaces, int* closestCount, SURFACE_TYPE type, float range) {
    SurfaceDistance* surfaceDistances = (SurfaceDistance*)malloc(numSurfaces * sizeof(SurfaceDistance));

    // Calculate the distance to each surface and store it in surfaceDistances
    int count = 0;
    for (int i = 0; i < numSurfaces; ++i) {
        if (surfaces[i].type == type) {
            float distance = t3d_vec3_distance(&position, &surfaces[i].center);
            if (distance <= range) {
                surfaceDistances[count].surface = surfaces[i];
                surfaceDistances[count].distance = distance;
                count++;
            }
        }
    }

    // Sort the surfaces by distance
    qsort(surfaceDistances, count, sizeof(SurfaceDistance), compare_surface_distance);

    // Collect the closest 4 surfaces
    *closestCount = (count < 4) ? count : 4;
    for (int i = 0; i < *closestCount; ++i) {
        closestSurfaces[i] = surfaceDistances[i].surface;
    }

    free(surfaceDistances);
}

// Function to find the closest 3 surfaces of any type within a specified range
void find_closest_surfaces_any_type(T3DVec3 position, Surface* surfaces, int numSurfaces, Surface* closestSurfaces, int* closestCount, float range) {
    SurfaceDistance* surfaceDistances = (SurfaceDistance*)malloc(numSurfaces * sizeof(SurfaceDistance));

    // Calculate the distance to each surface and store it in surfaceDistances
    int count = 0;
    for (int i = 0; i < numSurfaces; ++i) {
        float distance = t3d_vec3_distance(&position, &surfaces[i].center);
        if (distance <= range) {
            surfaceDistances[count].surface = surfaces[i];
            surfaceDistances[count].distance = distance;
            count++;
        }
    }

    // Sort the surfaces by distance
    qsort(surfaceDistances, count, sizeof(SurfaceDistance), compare_surface_distance);

    // Collect the closest 3 surfaces
    *closestCount = (count < 3) ? count : 3;
    for (int i = 0; i < *closestCount; ++i) {
        closestSurfaces[i] = surfaceDistances[i].surface;
    }

    free(surfaceDistances);
}

// Function to combine multiple surface arrays into a single array
void combine_surfaces(Surface* combinedArray, int* combinedCount, Surface* wallArray, int wallCount, Surface* slopeArray, int slopeCount, Surface* floorArray, int floorCount) {
    int count = 0;

    // Copy floor surfaces
    memcpy(&combinedArray[count], floorArray, floorCount * sizeof(Surface));
    count += floorCount;

    // Copy slope surfaces
    memcpy(&combinedArray[count], slopeArray, slopeCount * sizeof(Surface));
    count += slopeCount;

    // Copy wall surfaces
    memcpy(&combinedArray[count], wallArray, wallCount * sizeof(Surface));
    count += wallCount;

    *combinedCount = count;
}

void combine_normals(T3DVec3* normals, int count, T3DVec3* combinedNormal) {
    combinedNormal->v[0] = 0;
    combinedNormal->v[1] = 0;
    combinedNormal->v[2] = 0;

    for (int i = 0; i < count; ++i) {
        combinedNormal->v[0] += normals[i].v[0];
        combinedNormal->v[1] += normals[i].v[1];
        combinedNormal->v[2] += normals[i].v[2];
    }

    t3d_vec3_norm(combinedNormal);
}

void resolve_multi_collision(Sphere* sphere, T3DVec3* position, T3DVec3* velocity, T3DVec3* normal, float penetrationDepth) {
    T3DVec3 moveDirection;
    t3d_vec3_scale(&moveDirection, normal, penetrationDepth);
    t3d_vec3_diff(&sphere->center, &sphere->center, &moveDirection);

    // Adjust position and velocity accordingly
    position->v[0] = sphere->center.v[0];
    position->v[1] = sphere->center.v[1];
    position->v[2] = sphere->center.v[2];

    // Zero out the velocity component in the direction of the normal
    float dot = t3d_vec3_dot(velocity, normal);
    T3DVec3 normalComponent;
    t3d_vec3_scale(&normalComponent, normal, dot);
    t3d_vec3_diff(velocity, velocity, &normalComponent);
}

void handle_multi_collisions(Sphere* sphere, T3DVec3* position, T3DVec3* velocity, Surface* surfaces, int numSurfaces) {
    T3DVec3 normals[3]; // Assuming at most 3 surfaces at corners
    int collisionCount = 0;
    float penetrationDepth = 0;

    for (int i = 0; i < numSurfaces; ++i) {
        Surface* surf = &surfaces[i];
        if (check_sphere_surface_collision(*sphere, *surf)) {
            T3DVec3 normal = calc_surface_norm(*surf);
            normals[collisionCount] = normal;
            // Compute penetration depth
            T3DVec3 surfToSphere;
            t3d_vec3_diff(&surfToSphere, &sphere->center, &surf->posA);
            float dist = t3d_vec3_dot(&normal, &surfToSphere);
            penetrationDepth = sphere->radius - dist;
            collisionCount++;
        }
    }

    if (collisionCount > 0) {
        T3DVec3 combinedNormal;
        combine_normals(normals, collisionCount, &combinedNormal);
        resolve_multi_collision(sphere, position, velocity, &combinedNormal, penetrationDepth);
    }
}

void get_closest_point_on_wall(T3DVec3* closestPoint, Surface* surface, T3DVec3* point) {
    // Assuming the surface is a vertical wall, we'll only consider the x and z coordinates
    closestPoint->v[0] = point->v[0];
    closestPoint->v[1] = surface->center.v[1];
    closestPoint->v[2] = point->v[2];
}

// Function to resolve collision with a corner formed by two walls and keep track of the floor collision
void resolve_corner_collision(Sphere* sphere, T3DVec3* position, T3DVec3* velocity, Surface* wall1, Surface* wall2, Surface* floor) {
    // Calculate the closest point on each wall to the sphere
    T3DVec3 closestPointWall1, closestPointWall2;
    get_closest_point_on_wall(&closestPointWall1, wall1, &sphere->center);
    get_closest_point_on_wall(&closestPointWall2, wall2, &sphere->center);

    // Calculate vector from each closest point to the sphere center
    T3DVec3 wall1ToSphere, wall2ToSphere;
    t3d_vec3_diff(&wall1ToSphere, &sphere->center, &closestPointWall1);
    t3d_vec3_diff(&wall2ToSphere, &sphere->center, &closestPointWall2);

    // Calculate distances from the sphere center to the closest points on the walls
    float distToWall1 = t3d_vec3_len(&wall1ToSphere);
    float distToWall2 = t3d_vec3_len(&wall2ToSphere);

    // Resolve collision if the sphere is penetrating either wall
    if (distToWall1*1.1f < sphere->radius) {
        float penetrationDepth = sphere->radius - distToWall1;
        t3d_vec3_norm(&wall1ToSphere);
        t3d_vec3_scale(&wall1ToSphere, &wall1ToSphere, penetrationDepth);
        sphere->center.v[0] += wall1ToSphere.v[0];
        sphere->center.v[2] += wall1ToSphere.v[2];
    }

    if (distToWall2*1.1f < sphere->radius) {
        float penetrationDepth = sphere->radius - distToWall2;
        t3d_vec3_norm(&wall2ToSphere);
        t3d_vec3_scale(&wall2ToSphere, &wall2ToSphere, penetrationDepth);
        sphere->center.v[0] += wall2ToSphere.v[0];
        sphere->center.v[2] += wall2ToSphere.v[2];
    }

    // Adjust position and velocity accordingly
    position->v[0] = sphere->center.v[0];
    position->v[2] = sphere->center.v[2];

    // Handle floor collision to keep the player grounded
    T3DVec3 closestPointFloor;
    get_closest_point_on_wall(&closestPointFloor, floor, &sphere->center);
    T3DVec3 floorToSphere;
    t3d_vec3_diff(&floorToSphere, &sphere->center, &closestPointFloor);
    float distToFloor = t3d_vec3_len(&floorToSphere);

    if (distToFloor*1.1f < sphere->radius) {
        float penetrationDepth = sphere->radius - distToFloor;
        sphere->center.v[0] += penetrationDepth;
        sphere->center.v[1] += penetrationDepth;
        sphere->center.v[2] += penetrationDepth;
        position->v[1] = sphere->center.v[1];
        position->v[0] = sphere->center.v[0];
        position->v[2] = sphere->center.v[2];
        velocity->v[1] = 0; // Reset vertical velocity to keep grounded
    }

    // Recalculate velocity to avoid pointing directly into the walls
    T3DVec3 adjustedVelocity = *velocity;
    T3DVec3 surfaceNormal;
    t3d_vec3_cross(&surfaceNormal, &wall1->normal, &wall2->normal);
    t3d_vec3_norm(&surfaceNormal);
    float dot = t3d_vec3_dot(&adjustedVelocity, &surfaceNormal);
    if (dot < 0) {
        t3d_vec3_scale(&surfaceNormal, &surfaceNormal, dot);
        t3d_vec3_diff(&adjustedVelocity, &adjustedVelocity, &surfaceNormal);
    }

    // Apply dampened adjusted velocity
    velocity->v[0] = adjustedVelocity.v[0] * 0.5f;
    velocity->v[2] = adjustedVelocity.v[2] * 0.5f;
}

// Catch all
bool check_sphere_actor_collision(Sphere sphere, CollisionShape shape) {
    if (shape.type == SHAPE_BOX) {
        return check_sphere_box_collision(sphere, shape.aabb);
    }
    if (shape.type == SHAPE_SPHERE) {
        return check_sphere_collision(sphere, shape.sphere);
    }
    return false;
}

bool check_collisions(CollisionShape a, CollisionShape b) {
    if (a.type == SHAPE_BOX && b.type == SHAPE_BOX) {
        return check_box_collision(a.aabb, b.aabb);
    }
    if (a.type == SHAPE_SPHERE && b.type == SHAPE_SPHERE) {
        return check_sphere_collision(a.sphere, b.sphere);
    }
    if (a.type != b.type) {
        if (a.type == SHAPE_SPHERE){
            return check_sphere_box_collision(a.sphere, b.aabb);
        } else {
            return check_sphere_box_collision(b.sphere, a.aabb);
        }
    }
    return false;
}
