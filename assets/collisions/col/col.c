#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "debug.h"
#include "collision.h"
#include "col.h"
#include "utils.h"

T3DMat4FP* colMatFP;
T3DModel *modelCol;
rspq_block_t *dplCol;

T3DVec3 colVerts[25] =
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


int colWallCount = 8;
Surface colWall[8];

int colSlopeCount = 13;
Surface colSlope[13];

int colFloorCount = 11;
Surface colFloor[11];

int colSurfacesCount = 0;
Surface colSurfaces[32];

void col_init(void){
    colWall[0].posA = colVerts[0]; colWall[0].posB = colVerts[1]; colWall[0].posC = colVerts[2];
    colWall[1].posA = colVerts[3]; colWall[1].posB = colVerts[4]; colWall[1].posC = colVerts[5];
    colWall[2].posA = colVerts[6]; colWall[2].posB = colVerts[5]; colWall[2].posC = colVerts[7];
    colWall[3].posA = colVerts[8]; colWall[3].posB = colVerts[2]; colWall[3].posC = colVerts[4];
    colWall[4].posA = colVerts[0]; colWall[4].posB = colVerts[9]; colWall[4].posC = colVerts[1];
    colWall[5].posA = colVerts[3]; colWall[5].posB = colVerts[8]; colWall[5].posC = colVerts[4];
    colWall[6].posA = colVerts[6]; colWall[6].posB = colVerts[3]; colWall[6].posC = colVerts[5];
    colWall[7].posA = colVerts[8]; colWall[7].posB = colVerts[0]; colWall[7].posC = colVerts[2];
    colSlope[0].posA = colVerts[10]; colSlope[0].posB = colVerts[11]; colSlope[0].posC = colVerts[12];
    colSlope[1].posA = colVerts[13]; colSlope[1].posB = colVerts[14]; colSlope[1].posC = colVerts[15];
    colSlope[2].posA = colVerts[16]; colSlope[2].posB = colVerts[12]; colSlope[2].posC = colVerts[17];
    colSlope[3].posA = colVerts[18]; colSlope[3].posB = colVerts[15]; colSlope[3].posC = colVerts[11];
    colSlope[4].posA = colVerts[11]; colSlope[4].posB = colVerts[19]; colSlope[4].posC = colVerts[20];
    colSlope[5].posA = colVerts[17]; colSlope[5].posB = colVerts[21]; colSlope[5].posC = colVerts[22];
    colSlope[6].posA = colVerts[12]; colSlope[6].posB = colVerts[20]; colSlope[6].posC = colVerts[21];
    colSlope[7].posA = colVerts[10]; colSlope[7].posB = colVerts[18]; colSlope[7].posC = colVerts[11];
    colSlope[8].posA = colVerts[13]; colSlope[8].posB = colVerts[23]; colSlope[8].posC = colVerts[14];
    colSlope[9].posA = colVerts[16]; colSlope[9].posB = colVerts[10]; colSlope[9].posC = colVerts[12];
    colSlope[10].posA = colVerts[18]; colSlope[10].posB = colVerts[13]; colSlope[10].posC = colVerts[15];
    colSlope[11].posA = colVerts[17]; colSlope[11].posB = colVerts[12]; colSlope[11].posC = colVerts[21];
    colSlope[12].posA = colVerts[12]; colSlope[12].posB = colVerts[11]; colSlope[12].posC = colVerts[20];
    colFloor[0].posA = colVerts[4]; colFloor[0].posB = colVerts[13]; colFloor[0].posC = colVerts[18];
    colFloor[1].posA = colVerts[7]; colFloor[1].posB = colVerts[10]; colFloor[1].posC = colVerts[16];
    colFloor[2].posA = colVerts[5]; colFloor[2].posB = colVerts[18]; colFloor[2].posC = colVerts[10];
    colFloor[3].posA = colVerts[2]; colFloor[3].posB = colVerts[23]; colFloor[3].posC = colVerts[13];
    colFloor[4].posA = colVerts[15]; colFloor[4].posB = colVerts[24]; colFloor[4].posC = colVerts[19];
    colFloor[5].posA = colVerts[4]; colFloor[5].posB = colVerts[2]; colFloor[5].posC = colVerts[13];
    colFloor[6].posA = colVerts[7]; colFloor[6].posB = colVerts[5]; colFloor[6].posC = colVerts[10];
    colFloor[7].posA = colVerts[5]; colFloor[7].posB = colVerts[4]; colFloor[7].posC = colVerts[18];
    colFloor[8].posA = colVerts[2]; colFloor[8].posB = colVerts[1]; colFloor[8].posC = colVerts[23];
    colFloor[9].posA = colVerts[11]; colFloor[9].posB = colVerts[15]; colFloor[9].posC = colVerts[19];
    colFloor[10].posA = colVerts[15]; colFloor[10].posB = colVerts[14]; colFloor[10].posC = colVerts[24];

    for (int i = 0; i < colWallCount; i++) {
        colWall[i].type = SURFACE_WALL;
        colWall[i].center = center;
        colWall[i].normal = norm;
        colWall[i].center = calc_surface_center(colWall[i]);
        colWall[i].normal = calc_surface_norm(colWall[i]);
    }

    for (int i = 0; i < colSlopeCount; i++) {
        colSlope[i].type = SURFACE_SLOPE;
        colSlope[i].center = center;
        colSlope[i].normal = norm;
        colSlope[i].center = calc_surface_center(colSlope[i]);
        colSlope[i].normal = calc_surface_norm(colSlope[i]);
    }

    for (int i = 0; i < colFloorCount; i++) {
        colFloor[i].type = SURFACE_FLOOR;
        colFloor[i].center = center;
        colFloor[i].normal = norm;
        colFloor[i].center = calc_surface_center(colFloor[i]);
        colFloor[i].normal = calc_surface_norm(colFloor[i]);
    }

    // Combine the surfaces for collision detection
    combine_surfaces(
       colSurfaces, &colSurfacesCount,
       colWall, colWallCount,
       colSlope, colSlopeCount,
       colFloor, colFloorCount,
    );

    // Allocate map's matrix and construct
    colMatFP = malloc_uncached(sizeof(T3DMat4FP));
    t3d_mat4fp_from_srt_euler(colMatFP, (float[3]){1.0f, 1.0f, 1.0f}, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});

    // Load model
    modelCol = t3d_model_load("rom:/models/col.t3dm");

    // Create map's RSPQ block
    rspq_block_begin();
        t3d_matrix_push(colMatFP);
        matCount++;
        rdpq_set_prim_color(WHITE);
        t3d_model_draw(modelCol);
        t3d_matrix_pop(1);
    dplCol = rspq_block_end();
}
