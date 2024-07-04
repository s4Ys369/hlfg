#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "debug.h"
#include "collision.h"
#include "mesh2.h"
#include "utils.h"

T3DMat4FP* mesh2MatFP;
T3DModel *modelMesh2;
rspq_block_t *dplMesh2;

T3DVec3 mesh2Verts[62] =
{
    {{256, 256, -85}},
    {{85, 256, -256}},
    {{85, 256, -85}},
    {{256, 256, 256}},
    {{85, 256, 85}},
    {{85, 256, 256}},
    {{256, 256, 85}},
    {{256, 256, -256}},
    {{768, 448, -85}},
    {{896, 448, -85}},
    {{896, 448, -256}},
    {{768, 448, 256}},
    {{896, 448, 256}},
    {{896, 448, 85}},
    {{768, 448, 85}},
    {{768, 448, -256}},
    {{-85, 128, -85}},
    {{-256, 0, -256}},
    {{-256, 0, -85}},
    {{-85, 128, -256}},
    {{-85, 128, 85}},
    {{-85, 128, 256}},
    {{-256, 0, 85}},
    {{-256, 0, 256}},
    {{597, 352, -256}},
    {{597, 352, -85}},
    {{427, 320, -85}},
    {{427, 320, -256}},
    {{597, 352, 256}},
    {{427, 320, 85}},
    {{427, 320, 256}},
    {{597, 352, 85}},
    {{768, 128, 256}},
    {{768, 352, 256}},
    {{512, 0, 256}},
    {{341, 128, 256}},
    {{341, 0, 256}},
    {{512, 128, 256}},
    {{171, 128, 256}},
    {{171, 0, 256}},
    {{768, 351, -256}},
    {{768, 128, -256}},
    {{512, 0, -256}},
    {{341, 0, -256}},
    {{341, 107, -256}},
    {{512, 107, -256}},
    {{171, 107, -256}},
    {{171, 0, -256}},
    {{768, 0, -256}},
    {{896, 351, -256}},
    {{768, 0, 256}},
    {{896, 0, 256}},
    {{896, 128, 256}},
    {{896, 128, -256}},
    {{896, 0, -256}},
    {{896, 352, 256}},
    {{896, 352, -85}},
    {{896, 128, -85}},
    {{896, 352, 85}},
    {{896, 128, 85}},
    {{896, 0, 85}},
    {{896, 0, -85}},
};

int mesh2FloorCount = 12;
Surface mesh2Floor[12];
int mesh2SlopeCount = 30;
Surface mesh2Slope[30];
int mesh2WallCount = 64;
Surface mesh2Wall[64];

void mesh2_init(void){
    mesh2Floor[0].posA = mesh2Verts[0]; mesh2Floor[0].posB = mesh2Verts[1]; mesh2Floor[0].posC = mesh2Verts[2];
    mesh2Floor[1].posA = mesh2Verts[3]; mesh2Floor[1].posB = mesh2Verts[4]; mesh2Floor[1].posC = mesh2Verts[5];
    mesh2Floor[2].posA = mesh2Verts[6]; mesh2Floor[2].posB = mesh2Verts[2]; mesh2Floor[2].posC = mesh2Verts[4];
    mesh2Floor[3].posA = mesh2Verts[0]; mesh2Floor[3].posB = mesh2Verts[7]; mesh2Floor[3].posC = mesh2Verts[1];
    mesh2Floor[4].posA = mesh2Verts[3]; mesh2Floor[4].posB = mesh2Verts[6]; mesh2Floor[4].posC = mesh2Verts[4];
    mesh2Floor[5].posA = mesh2Verts[6]; mesh2Floor[5].posB = mesh2Verts[0]; mesh2Floor[5].posC = mesh2Verts[2];
    mesh2Floor[6].posA = mesh2Verts[8]; mesh2Floor[6].posB = mesh2Verts[9]; mesh2Floor[6].posC = mesh2Verts[10];
    mesh2Floor[7].posA = mesh2Verts[11]; mesh2Floor[7].posB = mesh2Verts[12]; mesh2Floor[7].posC = mesh2Verts[13];
    mesh2Floor[8].posA = mesh2Verts[11]; mesh2Floor[8].posB = mesh2Verts[13]; mesh2Floor[8].posC = mesh2Verts[14];
    mesh2Floor[9].posA = mesh2Verts[8]; mesh2Floor[9].posB = mesh2Verts[10]; mesh2Floor[9].posC = mesh2Verts[15];
    mesh2Floor[10].posA = mesh2Verts[14]; mesh2Floor[10].posB = mesh2Verts[9]; mesh2Floor[10].posC = mesh2Verts[8];
    mesh2Floor[11].posA = mesh2Verts[14]; mesh2Floor[11].posB = mesh2Verts[13]; mesh2Floor[11].posC = mesh2Verts[9];
    mesh2Slope[0].posA = mesh2Verts[16]; mesh2Slope[0].posB = mesh2Verts[17]; mesh2Slope[0].posC = mesh2Verts[18];
    mesh2Slope[1].posA = mesh2Verts[2]; mesh2Slope[1].posB = mesh2Verts[19]; mesh2Slope[1].posC = mesh2Verts[16];
    mesh2Slope[2].posA = mesh2Verts[5]; mesh2Slope[2].posB = mesh2Verts[20]; mesh2Slope[2].posC = mesh2Verts[21];
    mesh2Slope[3].posA = mesh2Verts[21]; mesh2Slope[3].posB = mesh2Verts[22]; mesh2Slope[3].posC = mesh2Verts[23];
    mesh2Slope[4].posA = mesh2Verts[4]; mesh2Slope[4].posB = mesh2Verts[16]; mesh2Slope[4].posC = mesh2Verts[20];
    mesh2Slope[5].posA = mesh2Verts[20]; mesh2Slope[5].posB = mesh2Verts[18]; mesh2Slope[5].posC = mesh2Verts[22];
    mesh2Slope[6].posA = mesh2Verts[16]; mesh2Slope[6].posB = mesh2Verts[19]; mesh2Slope[6].posC = mesh2Verts[17];
    mesh2Slope[7].posA = mesh2Verts[2]; mesh2Slope[7].posB = mesh2Verts[1]; mesh2Slope[7].posC = mesh2Verts[19];
    mesh2Slope[8].posA = mesh2Verts[5]; mesh2Slope[8].posB = mesh2Verts[4]; mesh2Slope[8].posC = mesh2Verts[20];
    mesh2Slope[9].posA = mesh2Verts[21]; mesh2Slope[9].posB = mesh2Verts[20]; mesh2Slope[9].posC = mesh2Verts[22];
    mesh2Slope[10].posA = mesh2Verts[4]; mesh2Slope[10].posB = mesh2Verts[2]; mesh2Slope[10].posC = mesh2Verts[16];
    mesh2Slope[11].posA = mesh2Verts[20]; mesh2Slope[11].posB = mesh2Verts[16]; mesh2Slope[11].posC = mesh2Verts[18];
    mesh2Slope[12].posA = mesh2Verts[8]; mesh2Slope[12].posB = mesh2Verts[24]; mesh2Slope[12].posC = mesh2Verts[25];
    mesh2Slope[13].posA = mesh2Verts[26]; mesh2Slope[13].posB = mesh2Verts[7]; mesh2Slope[13].posC = mesh2Verts[0];
    mesh2Slope[14].posA = mesh2Verts[25]; mesh2Slope[14].posB = mesh2Verts[27]; mesh2Slope[14].posC = mesh2Verts[26];
    mesh2Slope[15].posA = mesh2Verts[28]; mesh2Slope[15].posB = mesh2Verts[29]; mesh2Slope[15].posC = mesh2Verts[30];
    mesh2Slope[16].posA = mesh2Verts[30]; mesh2Slope[16].posB = mesh2Verts[6]; mesh2Slope[16].posC = mesh2Verts[3];
    mesh2Slope[17].posA = mesh2Verts[11]; mesh2Slope[17].posB = mesh2Verts[31]; mesh2Slope[17].posC = mesh2Verts[28];
    mesh2Slope[18].posA = mesh2Verts[31]; mesh2Slope[18].posB = mesh2Verts[26]; mesh2Slope[18].posC = mesh2Verts[29];
    mesh2Slope[19].posA = mesh2Verts[29]; mesh2Slope[19].posB = mesh2Verts[0]; mesh2Slope[19].posC = mesh2Verts[6];
    mesh2Slope[20].posA = mesh2Verts[14]; mesh2Slope[20].posB = mesh2Verts[25]; mesh2Slope[20].posC = mesh2Verts[31];
    mesh2Slope[21].posA = mesh2Verts[8]; mesh2Slope[21].posB = mesh2Verts[15]; mesh2Slope[21].posC = mesh2Verts[24];
    mesh2Slope[22].posA = mesh2Verts[26]; mesh2Slope[22].posB = mesh2Verts[27]; mesh2Slope[22].posC = mesh2Verts[7];
    mesh2Slope[23].posA = mesh2Verts[25]; mesh2Slope[23].posB = mesh2Verts[24]; mesh2Slope[23].posC = mesh2Verts[27];
    mesh2Slope[24].posA = mesh2Verts[28]; mesh2Slope[24].posB = mesh2Verts[31]; mesh2Slope[24].posC = mesh2Verts[29];
    mesh2Slope[25].posA = mesh2Verts[30]; mesh2Slope[25].posB = mesh2Verts[29]; mesh2Slope[25].posC = mesh2Verts[6];
    mesh2Slope[26].posA = mesh2Verts[11]; mesh2Slope[26].posB = mesh2Verts[14]; mesh2Slope[26].posC = mesh2Verts[31];
    mesh2Slope[27].posA = mesh2Verts[31]; mesh2Slope[27].posB = mesh2Verts[25]; mesh2Slope[27].posC = mesh2Verts[26];
    mesh2Slope[28].posA = mesh2Verts[29]; mesh2Slope[28].posB = mesh2Verts[26]; mesh2Slope[28].posC = mesh2Verts[0];
    mesh2Slope[29].posA = mesh2Verts[14]; mesh2Slope[29].posB = mesh2Verts[8]; mesh2Slope[29].posC = mesh2Verts[25];
    mesh2Wall[0].posA = mesh2Verts[28]; mesh2Wall[0].posB = mesh2Verts[32]; mesh2Wall[0].posC = mesh2Verts[33];
    mesh2Wall[1].posA = mesh2Verts[34]; mesh2Wall[1].posB = mesh2Verts[35]; mesh2Wall[1].posC = mesh2Verts[36];
    mesh2Wall[2].posA = mesh2Verts[37]; mesh2Wall[2].posB = mesh2Verts[30]; mesh2Wall[2].posC = mesh2Verts[35];
    mesh2Wall[3].posA = mesh2Verts[38]; mesh2Wall[3].posB = mesh2Verts[5]; mesh2Wall[3].posC = mesh2Verts[21];
    mesh2Wall[4].posA = mesh2Verts[39]; mesh2Wall[4].posB = mesh2Verts[21]; mesh2Wall[4].posC = mesh2Verts[23];
    mesh2Wall[5].posA = mesh2Verts[35]; mesh2Wall[5].posB = mesh2Verts[3]; mesh2Wall[5].posC = mesh2Verts[38];
    mesh2Wall[6].posA = mesh2Verts[36]; mesh2Wall[6].posB = mesh2Verts[38]; mesh2Wall[6].posC = mesh2Verts[39];
    mesh2Wall[7].posA = mesh2Verts[34]; mesh2Wall[7].posB = mesh2Verts[32]; mesh2Wall[7].posC = mesh2Verts[37];
    mesh2Wall[8].posA = mesh2Verts[24]; mesh2Wall[8].posB = mesh2Verts[40]; mesh2Wall[8].posC = mesh2Verts[41];
    mesh2Wall[9].posA = mesh2Verts[42]; mesh2Wall[9].posB = mesh2Verts[43]; mesh2Wall[9].posC = mesh2Verts[44];
    mesh2Wall[10].posA = mesh2Verts[45]; mesh2Wall[10].posB = mesh2Verts[44]; mesh2Wall[10].posC = mesh2Verts[27];
    mesh2Wall[11].posA = mesh2Verts[46]; mesh2Wall[11].posB = mesh2Verts[19]; mesh2Wall[11].posC = mesh2Verts[1];
    mesh2Wall[12].posA = mesh2Verts[47]; mesh2Wall[12].posB = mesh2Verts[17]; mesh2Wall[12].posC = mesh2Verts[19];
    mesh2Wall[13].posA = mesh2Verts[44]; mesh2Wall[13].posB = mesh2Verts[46]; mesh2Wall[13].posC = mesh2Verts[7];
    mesh2Wall[14].posA = mesh2Verts[43]; mesh2Wall[14].posB = mesh2Verts[47]; mesh2Wall[14].posC = mesh2Verts[46];
    mesh2Wall[15].posA = mesh2Verts[45]; mesh2Wall[15].posB = mesh2Verts[41]; mesh2Wall[15].posC = mesh2Verts[48];
    mesh2Wall[16].posA = mesh2Verts[15]; mesh2Wall[16].posB = mesh2Verts[10]; mesh2Wall[16].posC = mesh2Verts[49];
    mesh2Wall[17].posA = mesh2Verts[50]; mesh2Wall[17].posB = mesh2Verts[51]; mesh2Wall[17].posC = mesh2Verts[52];
    mesh2Wall[18].posA = mesh2Verts[41]; mesh2Wall[18].posB = mesh2Verts[53]; mesh2Wall[18].posC = mesh2Verts[54];
    mesh2Wall[19].posA = mesh2Verts[40]; mesh2Wall[19].posB = mesh2Verts[24]; mesh2Wall[19].posC = mesh2Verts[15];
    mesh2Wall[20].posA = mesh2Verts[33]; mesh2Wall[20].posB = mesh2Verts[11]; mesh2Wall[20].posC = mesh2Verts[28];
    mesh2Wall[21].posA = mesh2Verts[32]; mesh2Wall[21].posB = mesh2Verts[52]; mesh2Wall[21].posC = mesh2Verts[55];
    mesh2Wall[22].posA = mesh2Verts[32]; mesh2Wall[22].posB = mesh2Verts[55]; mesh2Wall[22].posC = mesh2Verts[33];
    mesh2Wall[23].posA = mesh2Verts[41]; mesh2Wall[23].posB = mesh2Verts[54]; mesh2Wall[23].posC = mesh2Verts[48];
    mesh2Wall[24].posA = mesh2Verts[28]; mesh2Wall[24].posB = mesh2Verts[37]; mesh2Wall[24].posC = mesh2Verts[32];
    mesh2Wall[25].posA = mesh2Verts[34]; mesh2Wall[25].posB = mesh2Verts[37]; mesh2Wall[25].posC = mesh2Verts[35];
    mesh2Wall[26].posA = mesh2Verts[37]; mesh2Wall[26].posB = mesh2Verts[28]; mesh2Wall[26].posC = mesh2Verts[30];
    mesh2Wall[27].posA = mesh2Verts[38]; mesh2Wall[27].posB = mesh2Verts[3]; mesh2Wall[27].posC = mesh2Verts[5];
    mesh2Wall[28].posA = mesh2Verts[39]; mesh2Wall[28].posB = mesh2Verts[38]; mesh2Wall[28].posC = mesh2Verts[21];
    mesh2Wall[29].posA = mesh2Verts[35]; mesh2Wall[29].posB = mesh2Verts[30]; mesh2Wall[29].posC = mesh2Verts[3];
    mesh2Wall[30].posA = mesh2Verts[36]; mesh2Wall[30].posB = mesh2Verts[35]; mesh2Wall[30].posC = mesh2Verts[38];
    mesh2Wall[31].posA = mesh2Verts[34]; mesh2Wall[31].posB = mesh2Verts[50]; mesh2Wall[31].posC = mesh2Verts[32];
    mesh2Wall[32].posA = mesh2Verts[50]; mesh2Wall[32].posB = mesh2Verts[52]; mesh2Wall[32].posC = mesh2Verts[32];
    mesh2Wall[33].posA = mesh2Verts[15]; mesh2Wall[33].posB = mesh2Verts[49]; mesh2Wall[33].posC = mesh2Verts[40];
    mesh2Wall[34].posA = mesh2Verts[40]; mesh2Wall[34].posB = mesh2Verts[53]; mesh2Wall[34].posC = mesh2Verts[41];
    mesh2Wall[35].posA = mesh2Verts[33]; mesh2Wall[35].posB = mesh2Verts[12]; mesh2Wall[35].posC = mesh2Verts[11];
    mesh2Wall[36].posA = mesh2Verts[24]; mesh2Wall[36].posB = mesh2Verts[41]; mesh2Wall[36].posC = mesh2Verts[45];
    mesh2Wall[37].posA = mesh2Verts[42]; mesh2Wall[37].posB = mesh2Verts[44]; mesh2Wall[37].posC = mesh2Verts[45];
    mesh2Wall[38].posA = mesh2Verts[45]; mesh2Wall[38].posB = mesh2Verts[27]; mesh2Wall[38].posC = mesh2Verts[24];
    mesh2Wall[39].posA = mesh2Verts[46]; mesh2Wall[39].posB = mesh2Verts[1]; mesh2Wall[39].posC = mesh2Verts[7];
    mesh2Wall[40].posA = mesh2Verts[47]; mesh2Wall[40].posB = mesh2Verts[19]; mesh2Wall[40].posC = mesh2Verts[46];
    mesh2Wall[41].posA = mesh2Verts[44]; mesh2Wall[41].posB = mesh2Verts[7]; mesh2Wall[41].posC = mesh2Verts[27];
    mesh2Wall[42].posA = mesh2Verts[43]; mesh2Wall[42].posB = mesh2Verts[46]; mesh2Wall[42].posC = mesh2Verts[44];
    mesh2Wall[43].posA = mesh2Verts[45]; mesh2Wall[43].posB = mesh2Verts[48]; mesh2Wall[43].posC = mesh2Verts[42];
    mesh2Wall[44].posA = mesh2Verts[13]; mesh2Wall[44].posB = mesh2Verts[56]; mesh2Wall[44].posC = mesh2Verts[9];
    mesh2Wall[45].posA = mesh2Verts[57]; mesh2Wall[45].posB = mesh2Verts[54]; mesh2Wall[45].posC = mesh2Verts[53];
    mesh2Wall[46].posA = mesh2Verts[58]; mesh2Wall[46].posB = mesh2Verts[52]; mesh2Wall[46].posC = mesh2Verts[59];
    mesh2Wall[47].posA = mesh2Verts[57]; mesh2Wall[47].posB = mesh2Verts[49]; mesh2Wall[47].posC = mesh2Verts[56];
    mesh2Wall[48].posA = mesh2Verts[58]; mesh2Wall[48].posB = mesh2Verts[12]; mesh2Wall[48].posC = mesh2Verts[55];
    mesh2Wall[49].posA = mesh2Verts[58]; mesh2Wall[49].posB = mesh2Verts[57]; mesh2Wall[49].posC = mesh2Verts[56];
    mesh2Wall[50].posA = mesh2Verts[56]; mesh2Wall[50].posB = mesh2Verts[10]; mesh2Wall[50].posC = mesh2Verts[9];
    mesh2Wall[51].posA = mesh2Verts[60]; mesh2Wall[51].posB = mesh2Verts[52]; mesh2Wall[51].posC = mesh2Verts[51];
    mesh2Wall[52].posA = mesh2Verts[61]; mesh2Wall[52].posB = mesh2Verts[59]; mesh2Wall[52].posC = mesh2Verts[60];
    mesh2Wall[53].posA = mesh2Verts[13]; mesh2Wall[53].posB = mesh2Verts[58]; mesh2Wall[53].posC = mesh2Verts[56];
    mesh2Wall[54].posA = mesh2Verts[57]; mesh2Wall[54].posB = mesh2Verts[61]; mesh2Wall[54].posC = mesh2Verts[54];
    mesh2Wall[55].posA = mesh2Verts[58]; mesh2Wall[55].posB = mesh2Verts[55]; mesh2Wall[55].posC = mesh2Verts[52];
    mesh2Wall[56].posA = mesh2Verts[57]; mesh2Wall[56].posB = mesh2Verts[53]; mesh2Wall[56].posC = mesh2Verts[49];
    mesh2Wall[57].posA = mesh2Verts[58]; mesh2Wall[57].posB = mesh2Verts[13]; mesh2Wall[57].posC = mesh2Verts[12];
    mesh2Wall[58].posA = mesh2Verts[58]; mesh2Wall[58].posB = mesh2Verts[59]; mesh2Wall[58].posC = mesh2Verts[57];
    mesh2Wall[59].posA = mesh2Verts[56]; mesh2Wall[59].posB = mesh2Verts[49]; mesh2Wall[59].posC = mesh2Verts[10];
    mesh2Wall[60].posA = mesh2Verts[60]; mesh2Wall[60].posB = mesh2Verts[59]; mesh2Wall[60].posC = mesh2Verts[52];
    mesh2Wall[61].posA = mesh2Verts[61]; mesh2Wall[61].posB = mesh2Verts[57]; mesh2Wall[61].posC = mesh2Verts[59];
    mesh2Wall[62].posA = mesh2Verts[40]; mesh2Wall[62].posB = mesh2Verts[49]; mesh2Wall[62].posC = mesh2Verts[53];
    mesh2Wall[63].posA = mesh2Verts[33]; mesh2Wall[63].posB = mesh2Verts[55]; mesh2Wall[63].posC = mesh2Verts[12];

    for (int i = 0; i < mesh2FloorCount; i++) {
        mesh2Floor[i].type = SURFACE_FLOOR;
        mesh2Floor[i].center = center;
        mesh2Floor[i].normal = norm;
        mesh2Floor[i].center = calc_surface_center(mesh2Floor[i]);
        mesh2Floor[i].normal = calc_surface_norm(mesh2Floor[i]);
    }

    for (int i = 0; i < mesh2SlopeCount; i++) {
        mesh2Slope[i].type = SURFACE_SLOPE;
        mesh2Slope[i].center = center;
        mesh2Slope[i].normal = norm;
        mesh2Slope[i].center = calc_surface_center(mesh2Slope[i]);
        mesh2Slope[i].normal = calc_surface_norm(mesh2Slope[i]);
    }

    for (int i = 0; i < mesh2WallCount; i++) {
        mesh2Wall[i].type = SURFACE_WALL;
        mesh2Wall[i].center = center;
        mesh2Wall[i].normal = norm;
        mesh2Wall[i].center = calc_surface_center(mesh2Wall[i]);
        mesh2Wall[i].normal = calc_surface_norm(mesh2Wall[i]);
    }

    // Allocate map's matrix and construct
    mesh2MatFP = malloc_uncached(sizeof(T3DMat4FP));
    t3d_mat4fp_from_srt_euler(mesh2MatFP, (float[3]){1.0f, 1.0f, 1.0f}, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});

    // Load model
    modelMesh2 = t3d_model_load("rom:/mesh2.t3dm");

    // Create map's RSPQ block
    rspq_block_begin();
        t3d_matrix_push(mesh2MatFP);
        matCount++;
        rdpq_set_prim_color(WHITE);
        t3d_model_draw(modelMesh2);
        t3d_matrix_pop(1);
    dplMesh2 = rspq_block_end();
}