#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "collision.h"
#include "debug.h"
#include "map.h"
#include "utils.h"

T3DMat4FP* mapMatFP;
T3DModel *modelMap;
rspq_block_t *dplMap;
AABB FloorBox;
float groundLevel;

T3DMat4FP* meshMatFP;
T3DModel *modelMesh;
rspq_block_t *dplMesh;

T3DVec3 center = {{0,0,0}};
T3DVec3 norm = {{0,0,1}};


T3DVec3 verts[25] =
{
    {{96, 128, -128}},
    {{96, 0, -256}},
    {{96, 0, -128}},
    {{96, 128, 128}},
    {{96, 0, 0}},
    {{96, 0, 128}},
    {{96, 128, 256}},
    {{96, 0, 256}},
    {{96, 128, 0}},
    {{96, 128, -256}},
    {{-32, 0, 128}},
    {{-160, 128, 0}},
    {{-160, 128, 128}},
    {{-32, 0, -128}},
    {{-160, 128, -256}},
    {{-160, 128, -128}},
    {{-32, 0, 256}},
    {{-160, 128, 256}},
    {{-32, 0, 0}},
    {{-288, 128, -128}},
    {{-288, 219, 0}},
    {{-288, 219, 128}},
    {{-288, 219, 256}},
    {{-32, 0, -256}},
    {{-288, 128, -256}},
};

int wallCount = 8;
Surface Wall[8];
int slopeCount = 13;
Surface Slope[13];
int floorCount = 11;
Surface Floor[11];

void mesh_init(void){

    Wall[0].posA = verts[0]; Wall[0].posB = verts[1]; Wall[0].posC = verts[2];
    Wall[1].posA = verts[3]; Wall[1].posB = verts[4]; Wall[1].posC = verts[5];
    Wall[2].posA = verts[6]; Wall[2].posB = verts[5]; Wall[2].posC = verts[7];
    Wall[3].posA = verts[8]; Wall[3].posB = verts[2]; Wall[3].posC = verts[4];
    Wall[4].posA = verts[0]; Wall[4].posB = verts[9]; Wall[4].posC = verts[1];
    Wall[5].posA = verts[3]; Wall[5].posB = verts[8]; Wall[5].posC = verts[4];
    Wall[6].posA = verts[6]; Wall[6].posB = verts[3]; Wall[6].posC = verts[5];
    Wall[7].posA = verts[8]; Wall[7].posB = verts[0]; Wall[7].posC = verts[2];

    for (int i = 0; i < wallCount; i++) {
        Wall[i].type = SURFACE_WALL;
        Wall[i].center = center;
        Wall[i].normal = norm;
        Wall[i].center = calc_surface_center(Wall[i]);
        Wall[i].normal = calc_surface_norm(Wall[i]);
    }

    Slope[ 0].posA = verts[10]; Slope[ 0].posB = verts[11]; Slope[ 0].posC = verts[12];
    Slope[ 1].posA = verts[13]; Slope[ 1].posB = verts[14]; Slope[ 1].posC = verts[15];
    Slope[ 2].posA = verts[16]; Slope[ 2].posB = verts[12]; Slope[ 2].posC = verts[17];
    Slope[ 3].posA = verts[18]; Slope[ 3].posB = verts[15]; Slope[ 3].posC = verts[11];
    Slope[ 4].posA = verts[11]; Slope[ 4].posB = verts[19]; Slope[ 4].posC = verts[20];
    Slope[ 5].posA = verts[17]; Slope[ 5].posB = verts[21]; Slope[ 5].posC = verts[22];
    Slope[ 6].posA = verts[12]; Slope[ 6].posB = verts[20]; Slope[ 6].posC = verts[21];
    Slope[ 7].posA = verts[10]; Slope[ 7].posB = verts[18]; Slope[ 7].posC = verts[11];
    Slope[ 8].posA = verts[13]; Slope[ 8].posB = verts[23]; Slope[ 8].posC = verts[14];
    Slope[ 9].posA = verts[16]; Slope[ 9].posB = verts[10]; Slope[ 9].posC = verts[12];
    Slope[10].posA = verts[18]; Slope[10].posB = verts[13]; Slope[10].posC = verts[15];
    Slope[11].posA = verts[17]; Slope[11].posB = verts[12]; Slope[11].posC = verts[21];
    Slope[12].posA = verts[12]; Slope[12].posB = verts[11]; Slope[12].posC = verts[20];

    for (int i = 0; i < slopeCount; i++) {
        Slope[i].type = SURFACE_SLOPE;
        Slope[i].center = center;
        Slope[i].normal = norm;
        Slope[i].center = calc_surface_center(Slope[i]);
        Slope[i].normal = calc_surface_norm(Slope[i]);
    }

    Floor[ 0].posA = verts[ 4];  Floor[ 0].posA = verts[13];  Floor[ 0].posA = verts[18];
    Floor[ 1].posA = verts[ 7];  Floor[ 1].posA = verts[10];  Floor[ 1].posA = verts[16];
    Floor[ 2].posA = verts[ 5];  Floor[ 2].posA = verts[18];  Floor[ 2].posA = verts[10];
    Floor[ 3].posA = verts[ 2];  Floor[ 3].posA = verts[23];  Floor[ 3].posA = verts[13];
    Floor[ 4].posA = verts[15];  Floor[ 4].posA = verts[24];  Floor[ 4].posA = verts[19];
    Floor[ 5].posA = verts[ 4];  Floor[ 5].posA = verts[ 2];  Floor[ 5].posA = verts[13];
    Floor[ 6].posA = verts[ 7];  Floor[ 6].posA = verts[ 5];  Floor[ 6].posA = verts[10];
    Floor[ 7].posA = verts[ 5];  Floor[ 7].posA = verts[ 4];  Floor[ 7].posA = verts[18];
    Floor[ 8].posA = verts[ 2];  Floor[ 8].posA = verts[ 1];  Floor[ 8].posA = verts[23];
    Floor[ 9].posA = verts[11];  Floor[ 9].posA = verts[15];  Floor[ 9].posA = verts[19];
    Floor[10].posA = verts[15];  Floor[10].posA = verts[14];  Floor[10].posA = verts[24];

    for (int i = 0; i < floorCount; i++) {
        Floor[i].type = SURFACE_FLOOR;
        Floor[i].center = center;
        Floor[i].normal = norm;
        Floor[i].center = calc_surface_center(Floor[i]);
        Floor[i].normal = calc_surface_norm(Floor[i]);
    }
}

void map_init(void){

    // Allocate map's matrix and construct
    mapMatFP = malloc_uncached(sizeof(T3DMat4FP));
    meshMatFP = malloc_uncached(sizeof(T3DMat4FP));
    t3d_mat4fp_from_srt_euler(mapMatFP, (float[3]){1.0f, 1.0f, 1.0f}, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});
    t3d_mat4fp_from_srt_euler(meshMatFP, (float[3]){1.0f, 1.0f, 1.0f}, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});

    // Load model
    modelMap = t3d_model_load("rom:/map.t3dm");
    modelMesh = t3d_model_load("rom:/mesh.t3dm");

    // Create map's RSPQ block
    rspq_block_begin();
        t3d_matrix_push(mapMatFP);
        matCount++;
        rdpq_set_prim_color(WHITE);
        t3d_model_draw(modelMap);
        t3d_matrix_pop(1);
    dplMap = rspq_block_end();

    rspq_block_begin();
        t3d_matrix_push(meshMatFP);
        matCount++;
        rdpq_set_prim_color(WHITE);
        t3d_model_draw(modelMesh);
        t3d_matrix_pop(1);
    dplMesh = rspq_block_end();

    // Set collisions
    FloorBox = (AABB){{{-512.0f, -1.0f, -512.0f}},{{512.0f, 0.15f, 512.0f}}}; // Map's AABB
    groundLevel = 0.15f;

    mesh_init();
}