#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "collision.h"
#include "utils.h"

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
T3DVec3 get_vec3_from_vec4(T3DVec4 vec) {
    T3DVec3 pos = {{ vec.v[0], vec.v[1], vec.v[2] }};
    return pos;
}

float point_plane_dist(T3DVec3 point, T3DVec3 planePoint, T3DVec3 planeNormal) {
    T3DVec3 diff = {{0,0,0}};
    t3d_vec3_diff(&diff, &point, &planePoint);
    return t3d_vec3_dot(&diff, &planeNormal);
}

T3DVec3 project_point_on_plane(T3DVec3 point, T3DVec3 planePoint, T3DVec3 planeNormal) {
    float distance = point_plane_dist(point, planePoint, planeNormal);
    T3DVec3 scaledNormal = {{planeNormal.v[0] * distance, planeNormal.v[1] * distance, planeNormal.v[2] * distance}};
    T3DVec3 diff = {{0,0,0}};
    t3d_vec3_diff(&diff, &point, &scaledNormal);
    return diff;
}

int point_in_quad(T3DVec3 point, T3DQuad quad) {
    // Check if the point is inside the quad using a point-in-polygon test in 3D
    T3DVec3 u = {{0,0,0}};
    T3DVec3 v = {{0,0,0}};
    T3DVec3 w = {{0,0,0}};
    T3DVec3 A = get_vec3_from_vec4(quad.v[0]);
    T3DVec3 B = get_vec3_from_vec4(quad.v[1]);
    T3DVec3 C = get_vec3_from_vec4(quad.v[3]);

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
        denominator = 0.001f;
    }

    float s = (uv * wv - vv * wu) / denominator;
    float t = (uv * wu - uu * wv) / denominator;

    return (s >= 0.1f) && (t >= 0.1f) && (s + t <= 1.0f);
}

float calc_dist_to_quad(T3DVec3 point, T3DQuad quad) {
    T3DVec3 planeNormal = {{0,0,0}};
    T3DVec3 u = {{0,0,0}};
    T3DVec3 v = {{0,0,0}};
    T3DVec3 A = get_vec3_from_vec4(quad.v[0]);
    T3DVec3 B = get_vec3_from_vec4(quad.v[1]);
    T3DVec3 C = get_vec3_from_vec4(quad.v[3]);
    t3d_vec3_diff(&u, &B, &A);
    t3d_vec3_diff(&v, &C, &A);

    t3d_vec3_cross(&planeNormal, &u, &v);

    t3d_vec3_norm(&planeNormal);

    T3DVec3 projectedPoint = project_point_on_plane(point, A, planeNormal);

    if (point_in_quad(projectedPoint, quad)) {
        return fabsf(point_plane_dist(point, A, planeNormal));
    }

    // If the point is outside the quad, find the minimum distance to the edges or vertices
    float minDistance = FLT_MAX;
    T3DVec3 edge = {{0,0,0}};
    T3DVec3 pointToVertex = {{0,0,0}};
    T3DVec3 projection = {{0,0,0}};
    T3DVec3 current = {{0,0,0}};
    T3DVec3 next = {{0,0,0}};

    for (int i = 0; i < 4; ++i) {
        int n = (i + 1) % 4;
        current = get_vec3_from_vec4(quad.v[i]);
        next = get_vec3_from_vec4(quad.v[n]);
        t3d_vec3_diff(&edge, &next, &current);
        t3d_vec3_diff(&pointToVertex, &point, &current);
        float t = t3d_vec3_dot(&pointToVertex, &edge) / t3d_vec3_dot(&edge, &edge);

        if (t < 0.0f) {
            minDistance = fminf(minDistance, t3d_vec3_distance(&point, &current));
        } else if (t > 1.0f) {
            minDistance = fminf(minDistance, t3d_vec3_distance(&point, &next));
        } else {
            projection = (T3DVec3){{current.v[0] + t * edge.v[0], 
                                    current.v[1] + t * edge.v[1], 
                                    current.v[2] + t * edge.v[2]}};
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

T3DVec3 find_closest_quad_from_verts(T3DVec3 originPos, T3DModel* targetModel, int targetModelCount) {
    T3DVertPacked* verts = t3d_model_get_vertices(targetModel);

    T3DQuad closestQuad;
    float minDistance = FLT_MAX;

    for (uint16_t i = 0; i < targetModel->totalVertCount; i += 2) {
        // Extract the positions from packed vertices
        T3DVec4 pos0 = (T3DVec4) {{verts[i].posA[0], verts[i].posA[1], verts[i].posA[2], 0}};
        T3DVec4 pos1 = (T3DVec4) {{verts[i].posB[0], verts[i].posB[1], verts[i].posB[2], 0}};
        T3DVec4 pos2 = (T3DVec4) {{verts[i+1].posA[0], verts[i+1].posA[1], verts[i+1].posA[2], 0}};
        T3DVec4 pos3 = (T3DVec4) {{verts[i+1].posB[0], verts[i+1].posB[1], verts[i+1].posB[2], 0}};

        // Assuming the quads are formed in a way that pos0, pos1, pos2, pos3 make a quad
        T3DQuad quad = {(T3DVec4){{0,0,0,0}},(T3DVec4){{0,0,0,0}},(T3DVec4){{0,0,0,0}},(T3DVec4){{0,0,0,0}}};
        quad.v[0] = pos0;
        quad.v[1] = pos1;
        quad.v[2] = pos2;
        quad.v[3] = pos3;

        float distance = calc_dist_to_quad(originPos, quad);
        if (distance < minDistance) {
            minDistance = distance;
            closestQuad = quad;
        }
    }

    // Calculate the normal of the closest quad
    T3DVec3 quadNormal = {{0,0,0}};
    T3DVec3 u = {{0,0,0}};
    T3DVec3 v = {{0,0,0}};
    T3DVec3 A = get_vec3_from_vec4(closestQuad.v[0]);
    T3DVec3 B = get_vec3_from_vec4(closestQuad.v[1]);
    T3DVec3 C = get_vec3_from_vec4(closestQuad.v[3]);
    t3d_vec3_diff(&u, &B, &A);
    t3d_vec3_diff(&v, &C, &A);
    t3d_vec3_cross(&quadNormal, &u, &v);
    t3d_vec3_norm(&quadNormal);
    return quadNormal;
}


// Catch all
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
