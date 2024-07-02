#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/types.h"
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
}