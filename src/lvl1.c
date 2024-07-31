#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "debug.h"
#include "collision.h"
#include "lvl1.h"
#include "utils.h"

T3DMat4FP* lvl1MatFP;
T3DModel *modelLvl1;
rspq_block_t *dplLvl1;

T3DVec3 lvl1Verts[220] =
{
    {{398, 0, -398}},
    {{512, 0, -512}},
    {{398, 0, -512}},
    {{398, 0, -57}},
    {{512, 0, -171}},
    {{398, 0, -171}},
    {{57, 0, -57}},
    {{171, 0, -171}},
    {{57, 0, -171}},
    {{57, 0, -398}},
    {{171, 0, -512}},
    {{57, 0, -512}},
    {{171, 0, -57}},
    {{284, 0, -171}},
    {{171, 0, -398}},
    {{284, 0, -512}},
    {{284, 0, -57}},
    {{284, 0, -398}},
    {{398, 0, -284}},
    {{284, 0, -284}},
    {{171, 0, -284}},
    {{57, 0, -284}},
    {{512, 0, -284}},
    {{512, 0, -398}},
    {{284, 0, 171}},
    {{398, 0, 57}},
    {{284, 0, 57}},
    {{171, 0, 171}},
    {{171, 0, 57}},
    {{57, 0, 171}},
    {{57, 0, 57}},
    {{398, 0, 171}},
    {{512, 0, 57}},
    {{512, 0, -57}},
    {{512, 0, 171}},
    {{398, 256, 284}},
    {{512, 256, 171}},
    {{398, 256, 171}},
    {{-284, 64, 284}},
    {{-171, 64, 171}},
    {{-284, 64, 171}},
    {{-512, 64, 284}},
    {{-398, 64, 171}},
    {{-512, 64, 171}},
    {{-398, 64, 284}},
    {{-171, 64, 284}},
    {{-57, 64, 171}},
    {{-57, 64, -398}},
    {{57, 64, -512}},
    {{-57, 64, -512}},
    {{-57, 64, 284}},
    {{57, 64, 171}},
    {{-57, 64, -57}},
    {{57, 64, -171}},
    {{-57, 64, -171}},
    {{57, 64, -284}},
    {{-57, 64, -284}},
    {{57, 64, -398}},
    {{57, 64, 57}},
    {{-57, 64, 57}},
    {{57, 64, -57}},
    {{-171, 64, 512}},
    {{-57, 64, 398}},
    {{-171, 64, 398}},
    {{-398, 64, 512}},
    {{-284, 64, 398}},
    {{-398, 64, 398}},
    {{-512, 64, 512}},
    {{-512, 64, 398}},
    {{-284, 64, 512}},
    {{398, 320, 512}},
    {{512, 320, 398}},
    {{398, 320, 398}},
    {{57, 64, 284}},
    {{512, 256, 284}},
    {{57, 512, 512}},
    {{-57, 512, 398}},
    {{-57, 512, 512}},
    {{199, 64, 341}},
    {{0, 64, 341}},
    {{512, 320, 512}},
    {{228, 64, 284}},
    {{398, 64, 341}},
    {{398, 64, 284}},
    {{398, 64, 398}},
    {{171, 64, 398}},
    {{-57, 64, 512}},
    {{171, 512, 398}},
    {{171, 512, 512}},
    {{57, 512, 398}},
    {{-512, 64, -398}},
    {{-398, 64, -284}},
    {{-398, 64, -398}},
    {{-512, 64, -57}},
    {{-398, 64, -171}},
    {{-512, 64, -171}},
    {{-284, 64, -171}},
    {{-169, 64, -57}},
    {{-170, 64, -171}},
    {{-284, 64, 57}},
    {{-398, 64, -57}},
    {{-398, 64, 57}},
    {{-284, 64, -398}},
    {{-170, 64, -284}},
    {{-170, 64, -398}},
    {{-284, 64, -284}},
    {{-170, 64, 57}},
    {{-284, 64, -57}},
    {{-512, 64, 57}},
    {{-512, 64, -284}},
    {{-57, 213, 171}},
    {{-171, 213, 57}},
    {{-171, 213, 171}},
    {{-57, 213, 57}},
    {{-57, 213, -57}},
    {{-171, 213, -57}},
    {{-57, 213, -171}},
    {{-171, 213, -171}},
    {{-171, 213, -284}},
    {{-284, 213, -398}},
    {{-171, 213, -512}},
    {{-284, 213, -512}},
    {{-512, 213, -398}},
    {{-398, 213, -512}},
    {{-512, 213, -512}},
    {{-512, 213, -57}},
    {{-398, 213, -171}},
    {{-512, 213, -171}},
    {{-398, 213, -398}},
    {{-171, 213, -398}},
    {{-57, 213, -512}},
    {{-284, 213, -284}},
    {{-398, 213, -284}},
    {{-512, 213, -284}},
    {{-284, 213, -171}},
    {{-57, 213, -398}},
    {{-398, 213, 171}},
    {{-284, 213, 57}},
    {{-398, 213, 57}},
    {{-512, 213, 171}},
    {{-512, 213, 57}},
    {{-284, 213, 171}},
    {{-398, 213, -57}},
    {{-57, 213, -284}},
    {{398, 64, 171}},
    {{512, 64, 171}},
    {{171, 64, 171}},
    {{284, 64, 171}},
    {{398, 136, 284}},
    {{398, 288, 341}},
    {{-57, 107, -512}},
    {{-171, 149, -512}},
    {{-57, 149, -512}},
    {{-512, 149, -171}},
    {{398, 151, 341}},
    {{398, 166, 398}},
    {{284, 192, 284}},
    {{171, 128, 284}},
    {{171, 128, 171}},
    {{398, 128, 171}},
    {{512, 128, 171}},
    {{284, 128, 171}},
    {{398, 192, 171}},
    {{512, 192, 171}},
    {{284, 192, 171}},
    {{-57, 400, 398}},
    {{-57, 288, 398}},
    {{-57, 400, 512}},
    {{-57, 288, 512}},
    {{-57, 176, 398}},
    {{-57, 176, 512}},
    {{284, 384, 398}},
    {{171, 171, 398}},
    {{171, 389, 398}},
    {{97, 393, 398}},
    {{-57, 107, -398}},
    {{-512, 149, 57}},
    {{-57, 149, -171}},
    {{-57, 149, -57}},
    {{-57, 149, 171}},
    {{-171, 149, 171}},
    {{-284, 149, -398}},
    {{-171, 149, -398}},
    {{-57, 149, -398}},
    {{-512, 64, -512}},
    {{-398, 107, -512}},
    {{-398, 64, -512}},
    {{-512, 107, -512}},
    {{-512, 149, -398}},
    {{-284, 107, -512}},
    {{-172, 64, -512}},
    {{-284, 64, -512}},
    {{-57, 149, 57}},
    {{-398, 149, -512}},
    {{-57, 149, -284}},
    {{-512, 149, -284}},
    {{-284, 149, 171}},
    {{-512, 149, -512}},
    {{-171, 149, -57}},
    {{-171, 149, 57}},
    {{-284, 149, -171}},
    {{-398, 149, -171}},
    {{-284, 149, 57}},
    {{-398, 149, 171}},
    {{-284, 149, -512}},
    {{-398, 149, 57}},
    {{-171, 149, -284}},
    {{-171, 149, -171}},
    {{-512, 149, -57}},
    {{-512, 149, 171}},
    {{-398, 149, -57}},
    {{-171, 64, 57}},
    {{-171, 64, -171}},
    {{-171, 64, -57}},
    {{-171, 64, -284}},
    {{-398, 149, -398}},
    {{-171, 107, -512}},
    {{-285, 149, -284}},
    {{-398, 149, -284}},
    {{284, 384, 512}},
};


int lvl1FloorCount = 175;
Surface* lvl1Floor;

int lvl1WallCount = 209;
Surface* lvl1Wall;

int lvl1SlopeCount = 12;
Surface* lvl1Slope;

int lvl1SurfacesCount = 0;
Surface* lvl1Surfaces;

void lvl1_init(void){

    lvl1Wall = malloc(lvl1WallCount * sizeof(Surface));
    lvl1Slope = malloc(lvl1SlopeCount * sizeof(Surface));
    lvl1Floor = malloc(lvl1FloorCount * sizeof(Surface));
    lvl1Surfaces = malloc((lvl1WallCount + lvl1SlopeCount + lvl1FloorCount) * sizeof(Surface));

    lvl1Floor[0].posA = lvl1Verts[0]; lvl1Floor[0].posB = lvl1Verts[1]; lvl1Floor[0].posC = lvl1Verts[2];
    lvl1Floor[1].posA = lvl1Verts[3]; lvl1Floor[1].posB = lvl1Verts[4]; lvl1Floor[1].posC = lvl1Verts[5];
    lvl1Floor[2].posA = lvl1Verts[6]; lvl1Floor[2].posB = lvl1Verts[7]; lvl1Floor[2].posC = lvl1Verts[8];
    lvl1Floor[3].posA = lvl1Verts[9]; lvl1Floor[3].posB = lvl1Verts[10]; lvl1Floor[3].posC = lvl1Verts[11];
    lvl1Floor[4].posA = lvl1Verts[12]; lvl1Floor[4].posB = lvl1Verts[13]; lvl1Floor[4].posC = lvl1Verts[7];
    lvl1Floor[5].posA = lvl1Verts[14]; lvl1Floor[5].posB = lvl1Verts[15]; lvl1Floor[5].posC = lvl1Verts[10];
    lvl1Floor[6].posA = lvl1Verts[16]; lvl1Floor[6].posB = lvl1Verts[5]; lvl1Floor[6].posC = lvl1Verts[13];
    lvl1Floor[7].posA = lvl1Verts[17]; lvl1Floor[7].posB = lvl1Verts[2]; lvl1Floor[7].posC = lvl1Verts[15];
    lvl1Floor[8].posA = lvl1Verts[13]; lvl1Floor[8].posB = lvl1Verts[18]; lvl1Floor[8].posC = lvl1Verts[19];
    lvl1Floor[9].posA = lvl1Verts[7]; lvl1Floor[9].posB = lvl1Verts[19]; lvl1Floor[9].posC = lvl1Verts[20];
    lvl1Floor[10].posA = lvl1Verts[8]; lvl1Floor[10].posB = lvl1Verts[20]; lvl1Floor[10].posC = lvl1Verts[21];
    lvl1Floor[11].posA = lvl1Verts[5]; lvl1Floor[11].posB = lvl1Verts[22]; lvl1Floor[11].posC = lvl1Verts[18];
    lvl1Floor[12].posA = lvl1Verts[19]; lvl1Floor[12].posB = lvl1Verts[0]; lvl1Floor[12].posC = lvl1Verts[17];
    lvl1Floor[13].posA = lvl1Verts[20]; lvl1Floor[13].posB = lvl1Verts[17]; lvl1Floor[13].posC = lvl1Verts[14];
    lvl1Floor[14].posA = lvl1Verts[21]; lvl1Floor[14].posB = lvl1Verts[14]; lvl1Floor[14].posC = lvl1Verts[9];
    lvl1Floor[15].posA = lvl1Verts[18]; lvl1Floor[15].posB = lvl1Verts[23]; lvl1Floor[15].posC = lvl1Verts[0];
    lvl1Floor[16].posA = lvl1Verts[24]; lvl1Floor[16].posB = lvl1Verts[25]; lvl1Floor[16].posC = lvl1Verts[26];
    lvl1Floor[17].posA = lvl1Verts[27]; lvl1Floor[17].posB = lvl1Verts[26]; lvl1Floor[17].posC = lvl1Verts[28];
    lvl1Floor[18].posA = lvl1Verts[29]; lvl1Floor[18].posB = lvl1Verts[28]; lvl1Floor[18].posC = lvl1Verts[30];
    lvl1Floor[19].posA = lvl1Verts[31]; lvl1Floor[19].posB = lvl1Verts[32]; lvl1Floor[19].posC = lvl1Verts[25];
    lvl1Floor[20].posA = lvl1Verts[26]; lvl1Floor[20].posB = lvl1Verts[3]; lvl1Floor[20].posC = lvl1Verts[16];
    lvl1Floor[21].posA = lvl1Verts[28]; lvl1Floor[21].posB = lvl1Verts[16]; lvl1Floor[21].posC = lvl1Verts[12];
    lvl1Floor[22].posA = lvl1Verts[30]; lvl1Floor[22].posB = lvl1Verts[12]; lvl1Floor[22].posC = lvl1Verts[6];
    lvl1Floor[23].posA = lvl1Verts[25]; lvl1Floor[23].posB = lvl1Verts[33]; lvl1Floor[23].posC = lvl1Verts[3];
    lvl1Floor[24].posA = lvl1Verts[0]; lvl1Floor[24].posB = lvl1Verts[23]; lvl1Floor[24].posC = lvl1Verts[1];
    lvl1Floor[25].posA = lvl1Verts[3]; lvl1Floor[25].posB = lvl1Verts[33]; lvl1Floor[25].posC = lvl1Verts[4];
    lvl1Floor[26].posA = lvl1Verts[6]; lvl1Floor[26].posB = lvl1Verts[12]; lvl1Floor[26].posC = lvl1Verts[7];
    lvl1Floor[27].posA = lvl1Verts[9]; lvl1Floor[27].posB = lvl1Verts[14]; lvl1Floor[27].posC = lvl1Verts[10];
    lvl1Floor[28].posA = lvl1Verts[12]; lvl1Floor[28].posB = lvl1Verts[16]; lvl1Floor[28].posC = lvl1Verts[13];
    lvl1Floor[29].posA = lvl1Verts[14]; lvl1Floor[29].posB = lvl1Verts[17]; lvl1Floor[29].posC = lvl1Verts[15];
    lvl1Floor[30].posA = lvl1Verts[16]; lvl1Floor[30].posB = lvl1Verts[3]; lvl1Floor[30].posC = lvl1Verts[5];
    lvl1Floor[31].posA = lvl1Verts[17]; lvl1Floor[31].posB = lvl1Verts[0]; lvl1Floor[31].posC = lvl1Verts[2];
    lvl1Floor[32].posA = lvl1Verts[13]; lvl1Floor[32].posB = lvl1Verts[5]; lvl1Floor[32].posC = lvl1Verts[18];
    lvl1Floor[33].posA = lvl1Verts[7]; lvl1Floor[33].posB = lvl1Verts[13]; lvl1Floor[33].posC = lvl1Verts[19];
    lvl1Floor[34].posA = lvl1Verts[8]; lvl1Floor[34].posB = lvl1Verts[7]; lvl1Floor[34].posC = lvl1Verts[20];
    lvl1Floor[35].posA = lvl1Verts[5]; lvl1Floor[35].posB = lvl1Verts[4]; lvl1Floor[35].posC = lvl1Verts[22];
    lvl1Floor[36].posA = lvl1Verts[19]; lvl1Floor[36].posB = lvl1Verts[18]; lvl1Floor[36].posC = lvl1Verts[0];
    lvl1Floor[37].posA = lvl1Verts[20]; lvl1Floor[37].posB = lvl1Verts[19]; lvl1Floor[37].posC = lvl1Verts[17];
    lvl1Floor[38].posA = lvl1Verts[21]; lvl1Floor[38].posB = lvl1Verts[20]; lvl1Floor[38].posC = lvl1Verts[14];
    lvl1Floor[39].posA = lvl1Verts[18]; lvl1Floor[39].posB = lvl1Verts[22]; lvl1Floor[39].posC = lvl1Verts[23];
    lvl1Floor[40].posA = lvl1Verts[24]; lvl1Floor[40].posB = lvl1Verts[31]; lvl1Floor[40].posC = lvl1Verts[25];
    lvl1Floor[41].posA = lvl1Verts[27]; lvl1Floor[41].posB = lvl1Verts[24]; lvl1Floor[41].posC = lvl1Verts[26];
    lvl1Floor[42].posA = lvl1Verts[29]; lvl1Floor[42].posB = lvl1Verts[27]; lvl1Floor[42].posC = lvl1Verts[28];
    lvl1Floor[43].posA = lvl1Verts[31]; lvl1Floor[43].posB = lvl1Verts[34]; lvl1Floor[43].posC = lvl1Verts[32];
    lvl1Floor[44].posA = lvl1Verts[26]; lvl1Floor[44].posB = lvl1Verts[25]; lvl1Floor[44].posC = lvl1Verts[3];
    lvl1Floor[45].posA = lvl1Verts[28]; lvl1Floor[45].posB = lvl1Verts[26]; lvl1Floor[45].posC = lvl1Verts[16];
    lvl1Floor[46].posA = lvl1Verts[30]; lvl1Floor[46].posB = lvl1Verts[28]; lvl1Floor[46].posC = lvl1Verts[12];
    lvl1Floor[47].posA = lvl1Verts[25]; lvl1Floor[47].posB = lvl1Verts[32]; lvl1Floor[47].posC = lvl1Verts[33];
    lvl1Floor[48].posA = lvl1Verts[35]; lvl1Floor[48].posB = lvl1Verts[36]; lvl1Floor[48].posC = lvl1Verts[37];
    lvl1Floor[49].posA = lvl1Verts[38]; lvl1Floor[49].posB = lvl1Verts[39]; lvl1Floor[49].posC = lvl1Verts[40];
    lvl1Floor[50].posA = lvl1Verts[41]; lvl1Floor[50].posB = lvl1Verts[42]; lvl1Floor[50].posC = lvl1Verts[43];
    lvl1Floor[51].posA = lvl1Verts[44]; lvl1Floor[51].posB = lvl1Verts[40]; lvl1Floor[51].posC = lvl1Verts[42];
    lvl1Floor[52].posA = lvl1Verts[45]; lvl1Floor[52].posB = lvl1Verts[46]; lvl1Floor[52].posC = lvl1Verts[39];
    lvl1Floor[53].posA = lvl1Verts[47]; lvl1Floor[53].posB = lvl1Verts[48]; lvl1Floor[53].posC = lvl1Verts[49];
    lvl1Floor[54].posA = lvl1Verts[50]; lvl1Floor[54].posB = lvl1Verts[51]; lvl1Floor[54].posC = lvl1Verts[46];
    lvl1Floor[55].posA = lvl1Verts[52]; lvl1Floor[55].posB = lvl1Verts[53]; lvl1Floor[55].posC = lvl1Verts[54];
    lvl1Floor[56].posA = lvl1Verts[54]; lvl1Floor[56].posB = lvl1Verts[55]; lvl1Floor[56].posC = lvl1Verts[56];
    lvl1Floor[57].posA = lvl1Verts[56]; lvl1Floor[57].posB = lvl1Verts[57]; lvl1Floor[57].posC = lvl1Verts[47];
    lvl1Floor[58].posA = lvl1Verts[46]; lvl1Floor[58].posB = lvl1Verts[58]; lvl1Floor[58].posC = lvl1Verts[59];
    lvl1Floor[59].posA = lvl1Verts[59]; lvl1Floor[59].posB = lvl1Verts[60]; lvl1Floor[59].posC = lvl1Verts[52];
    lvl1Floor[60].posA = lvl1Verts[61]; lvl1Floor[60].posB = lvl1Verts[62]; lvl1Floor[60].posC = lvl1Verts[63];
    lvl1Floor[61].posA = lvl1Verts[64]; lvl1Floor[61].posB = lvl1Verts[65]; lvl1Floor[61].posC = lvl1Verts[66];
    lvl1Floor[62].posA = lvl1Verts[67]; lvl1Floor[62].posB = lvl1Verts[66]; lvl1Floor[62].posC = lvl1Verts[68];
    lvl1Floor[63].posA = lvl1Verts[69]; lvl1Floor[63].posB = lvl1Verts[63]; lvl1Floor[63].posC = lvl1Verts[65];
    lvl1Floor[64].posA = lvl1Verts[70]; lvl1Floor[64].posB = lvl1Verts[71]; lvl1Floor[64].posC = lvl1Verts[72];
    lvl1Floor[65].posA = lvl1Verts[62]; lvl1Floor[65].posB = lvl1Verts[73]; lvl1Floor[65].posC = lvl1Verts[50];
    lvl1Floor[66].posA = lvl1Verts[63]; lvl1Floor[66].posB = lvl1Verts[50]; lvl1Floor[66].posC = lvl1Verts[45];
    lvl1Floor[67].posA = lvl1Verts[66]; lvl1Floor[67].posB = lvl1Verts[38]; lvl1Floor[67].posC = lvl1Verts[44];
    lvl1Floor[68].posA = lvl1Verts[68]; lvl1Floor[68].posB = lvl1Verts[44]; lvl1Floor[68].posC = lvl1Verts[41];
    lvl1Floor[69].posA = lvl1Verts[65]; lvl1Floor[69].posB = lvl1Verts[45]; lvl1Floor[69].posC = lvl1Verts[38];
    lvl1Floor[70].posA = lvl1Verts[35]; lvl1Floor[70].posB = lvl1Verts[74]; lvl1Floor[70].posC = lvl1Verts[36];
    lvl1Floor[71].posA = lvl1Verts[38]; lvl1Floor[71].posB = lvl1Verts[45]; lvl1Floor[71].posC = lvl1Verts[39];
    lvl1Floor[72].posA = lvl1Verts[41]; lvl1Floor[72].posB = lvl1Verts[44]; lvl1Floor[72].posC = lvl1Verts[42];
    lvl1Floor[73].posA = lvl1Verts[44]; lvl1Floor[73].posB = lvl1Verts[38]; lvl1Floor[73].posC = lvl1Verts[40];
    lvl1Floor[74].posA = lvl1Verts[45]; lvl1Floor[74].posB = lvl1Verts[50]; lvl1Floor[74].posC = lvl1Verts[46];
    lvl1Floor[75].posA = lvl1Verts[47]; lvl1Floor[75].posB = lvl1Verts[57]; lvl1Floor[75].posC = lvl1Verts[48];
    lvl1Floor[76].posA = lvl1Verts[50]; lvl1Floor[76].posB = lvl1Verts[73]; lvl1Floor[76].posC = lvl1Verts[51];
    lvl1Floor[77].posA = lvl1Verts[52]; lvl1Floor[77].posB = lvl1Verts[60]; lvl1Floor[77].posC = lvl1Verts[53];
    lvl1Floor[78].posA = lvl1Verts[54]; lvl1Floor[78].posB = lvl1Verts[53]; lvl1Floor[78].posC = lvl1Verts[55];
    lvl1Floor[79].posA = lvl1Verts[56]; lvl1Floor[79].posB = lvl1Verts[55]; lvl1Floor[79].posC = lvl1Verts[57];
    lvl1Floor[80].posA = lvl1Verts[46]; lvl1Floor[80].posB = lvl1Verts[51]; lvl1Floor[80].posC = lvl1Verts[58];
    lvl1Floor[81].posA = lvl1Verts[59]; lvl1Floor[81].posB = lvl1Verts[58]; lvl1Floor[81].posC = lvl1Verts[60];
    lvl1Floor[82].posA = lvl1Verts[75]; lvl1Floor[82].posB = lvl1Verts[76]; lvl1Floor[82].posC = lvl1Verts[77];
    lvl1Floor[83].posA = lvl1Verts[64]; lvl1Floor[83].posB = lvl1Verts[69]; lvl1Floor[83].posC = lvl1Verts[65];
    lvl1Floor[84].posA = lvl1Verts[67]; lvl1Floor[84].posB = lvl1Verts[64]; lvl1Floor[84].posC = lvl1Verts[66];
    lvl1Floor[85].posA = lvl1Verts[78]; lvl1Floor[85].posB = lvl1Verts[73]; lvl1Floor[85].posC = lvl1Verts[79];
    lvl1Floor[86].posA = lvl1Verts[69]; lvl1Floor[86].posB = lvl1Verts[61]; lvl1Floor[86].posC = lvl1Verts[63];
    lvl1Floor[87].posA = lvl1Verts[70]; lvl1Floor[87].posB = lvl1Verts[80]; lvl1Floor[87].posC = lvl1Verts[71];
    lvl1Floor[88].posA = lvl1Verts[63]; lvl1Floor[88].posB = lvl1Verts[62]; lvl1Floor[88].posC = lvl1Verts[50];
    lvl1Floor[89].posA = lvl1Verts[66]; lvl1Floor[89].posB = lvl1Verts[65]; lvl1Floor[89].posC = lvl1Verts[38];
    lvl1Floor[90].posA = lvl1Verts[68]; lvl1Floor[90].posB = lvl1Verts[66]; lvl1Floor[90].posC = lvl1Verts[44];
    lvl1Floor[91].posA = lvl1Verts[65]; lvl1Floor[91].posB = lvl1Verts[63]; lvl1Floor[91].posC = lvl1Verts[45];
    lvl1Floor[92].posA = lvl1Verts[78]; lvl1Floor[92].posB = lvl1Verts[81]; lvl1Floor[92].posC = lvl1Verts[73];
    lvl1Floor[93].posA = lvl1Verts[82]; lvl1Floor[93].posB = lvl1Verts[83]; lvl1Floor[93].posC = lvl1Verts[81];
    lvl1Floor[94].posA = lvl1Verts[84]; lvl1Floor[94].posB = lvl1Verts[82]; lvl1Floor[94].posC = lvl1Verts[78];
    lvl1Floor[95].posA = lvl1Verts[85]; lvl1Floor[95].posB = lvl1Verts[79]; lvl1Floor[95].posC = lvl1Verts[62];
    lvl1Floor[96].posA = lvl1Verts[79]; lvl1Floor[96].posB = lvl1Verts[85]; lvl1Floor[96].posC = lvl1Verts[78];
    lvl1Floor[97].posA = lvl1Verts[82]; lvl1Floor[97].posB = lvl1Verts[81]; lvl1Floor[97].posC = lvl1Verts[78];
    lvl1Floor[98].posA = lvl1Verts[84]; lvl1Floor[98].posB = lvl1Verts[78]; lvl1Floor[98].posC = lvl1Verts[85];
    lvl1Floor[99].posA = lvl1Verts[61]; lvl1Floor[99].posB = lvl1Verts[86]; lvl1Floor[99].posC = lvl1Verts[62];
    lvl1Floor[100].posA = lvl1Verts[87]; lvl1Floor[100].posB = lvl1Verts[75]; lvl1Floor[100].posC = lvl1Verts[88];
    lvl1Floor[101].posA = lvl1Verts[75]; lvl1Floor[101].posB = lvl1Verts[89]; lvl1Floor[101].posC = lvl1Verts[76];
    lvl1Floor[102].posA = lvl1Verts[87]; lvl1Floor[102].posB = lvl1Verts[89]; lvl1Floor[102].posC = lvl1Verts[75];
    lvl1Floor[103].posA = lvl1Verts[90]; lvl1Floor[103].posB = lvl1Verts[91]; lvl1Floor[103].posC = lvl1Verts[92];
    lvl1Floor[104].posA = lvl1Verts[93]; lvl1Floor[104].posB = lvl1Verts[94]; lvl1Floor[104].posC = lvl1Verts[95];
    lvl1Floor[105].posA = lvl1Verts[96]; lvl1Floor[105].posB = lvl1Verts[91]; lvl1Floor[105].posC = lvl1Verts[94];
    lvl1Floor[106].posA = lvl1Verts[96]; lvl1Floor[106].posB = lvl1Verts[97]; lvl1Floor[106].posC = lvl1Verts[98];
    lvl1Floor[107].posA = lvl1Verts[99]; lvl1Floor[107].posB = lvl1Verts[100]; lvl1Floor[107].posC = lvl1Verts[101];
    lvl1Floor[108].posA = lvl1Verts[102]; lvl1Floor[108].posB = lvl1Verts[103]; lvl1Floor[108].posC = lvl1Verts[104];
    lvl1Floor[109].posA = lvl1Verts[40]; lvl1Floor[109].posB = lvl1Verts[101]; lvl1Floor[109].posC = lvl1Verts[42];
    lvl1Floor[110].posA = lvl1Verts[98]; lvl1Floor[110].posB = lvl1Verts[105]; lvl1Floor[110].posC = lvl1Verts[96];
    lvl1Floor[111].posA = lvl1Verts[104]; lvl1Floor[111].posB = lvl1Verts[56]; lvl1Floor[111].posC = lvl1Verts[47];
    lvl1Floor[112].posA = lvl1Verts[106]; lvl1Floor[112].posB = lvl1Verts[107]; lvl1Floor[112].posC = lvl1Verts[99];
    lvl1Floor[113].posA = lvl1Verts[39]; lvl1Floor[113].posB = lvl1Verts[99]; lvl1Floor[113].posC = lvl1Verts[40];
    lvl1Floor[114].posA = lvl1Verts[101]; lvl1Floor[114].posB = lvl1Verts[93]; lvl1Floor[114].posC = lvl1Verts[108];
    lvl1Floor[115].posA = lvl1Verts[94]; lvl1Floor[115].posB = lvl1Verts[107]; lvl1Floor[115].posC = lvl1Verts[96];
    lvl1Floor[116].posA = lvl1Verts[94]; lvl1Floor[116].posB = lvl1Verts[109]; lvl1Floor[116].posC = lvl1Verts[95];
    lvl1Floor[117].posA = lvl1Verts[42]; lvl1Floor[117].posB = lvl1Verts[108]; lvl1Floor[117].posC = lvl1Verts[43];
    lvl1Floor[118].posA = lvl1Verts[92]; lvl1Floor[118].posB = lvl1Verts[105]; lvl1Floor[118].posC = lvl1Verts[102];
    lvl1Floor[119].posA = lvl1Verts[90]; lvl1Floor[119].posB = lvl1Verts[109]; lvl1Floor[119].posC = lvl1Verts[91];
    lvl1Floor[120].posA = lvl1Verts[93]; lvl1Floor[120].posB = lvl1Verts[100]; lvl1Floor[120].posC = lvl1Verts[94];
    lvl1Floor[121].posA = lvl1Verts[96]; lvl1Floor[121].posB = lvl1Verts[105]; lvl1Floor[121].posC = lvl1Verts[91];
    lvl1Floor[122].posA = lvl1Verts[96]; lvl1Floor[122].posB = lvl1Verts[107]; lvl1Floor[122].posC = lvl1Verts[97];
    lvl1Floor[123].posA = lvl1Verts[99]; lvl1Floor[123].posB = lvl1Verts[107]; lvl1Floor[123].posC = lvl1Verts[100];
    lvl1Floor[124].posA = lvl1Verts[102]; lvl1Floor[124].posB = lvl1Verts[105]; lvl1Floor[124].posC = lvl1Verts[103];
    lvl1Floor[125].posA = lvl1Verts[40]; lvl1Floor[125].posB = lvl1Verts[99]; lvl1Floor[125].posC = lvl1Verts[101];
    lvl1Floor[126].posA = lvl1Verts[98]; lvl1Floor[126].posB = lvl1Verts[103]; lvl1Floor[126].posC = lvl1Verts[105];
    lvl1Floor[127].posA = lvl1Verts[104]; lvl1Floor[127].posB = lvl1Verts[103]; lvl1Floor[127].posC = lvl1Verts[56];
    lvl1Floor[128].posA = lvl1Verts[106]; lvl1Floor[128].posB = lvl1Verts[97]; lvl1Floor[128].posC = lvl1Verts[107];
    lvl1Floor[129].posA = lvl1Verts[39]; lvl1Floor[129].posB = lvl1Verts[106]; lvl1Floor[129].posC = lvl1Verts[99];
    lvl1Floor[130].posA = lvl1Verts[101]; lvl1Floor[130].posB = lvl1Verts[100]; lvl1Floor[130].posC = lvl1Verts[93];
    lvl1Floor[131].posA = lvl1Verts[94]; lvl1Floor[131].posB = lvl1Verts[100]; lvl1Floor[131].posC = lvl1Verts[107];
    lvl1Floor[132].posA = lvl1Verts[94]; lvl1Floor[132].posB = lvl1Verts[91]; lvl1Floor[132].posC = lvl1Verts[109];
    lvl1Floor[133].posA = lvl1Verts[42]; lvl1Floor[133].posB = lvl1Verts[101]; lvl1Floor[133].posC = lvl1Verts[108];
    lvl1Floor[134].posA = lvl1Verts[92]; lvl1Floor[134].posB = lvl1Verts[91]; lvl1Floor[134].posC = lvl1Verts[105];
    lvl1Floor[135].posA = lvl1Verts[110]; lvl1Floor[135].posB = lvl1Verts[111]; lvl1Floor[135].posC = lvl1Verts[112];
    lvl1Floor[136].posA = lvl1Verts[113]; lvl1Floor[136].posB = lvl1Verts[114]; lvl1Floor[136].posC = lvl1Verts[115];
    lvl1Floor[137].posA = lvl1Verts[114]; lvl1Floor[137].posB = lvl1Verts[116]; lvl1Floor[137].posC = lvl1Verts[117];
    lvl1Floor[138].posA = lvl1Verts[116]; lvl1Floor[138].posB = lvl1Verts[118]; lvl1Floor[138].posC = lvl1Verts[117];
    lvl1Floor[139].posA = lvl1Verts[114]; lvl1Floor[139].posB = lvl1Verts[117]; lvl1Floor[139].posC = lvl1Verts[115];
    lvl1Floor[140].posA = lvl1Verts[113]; lvl1Floor[140].posB = lvl1Verts[115]; lvl1Floor[140].posC = lvl1Verts[111];
    lvl1Floor[141].posA = lvl1Verts[119]; lvl1Floor[141].posB = lvl1Verts[120]; lvl1Floor[141].posC = lvl1Verts[121];
    lvl1Floor[142].posA = lvl1Verts[122]; lvl1Floor[142].posB = lvl1Verts[123]; lvl1Floor[142].posC = lvl1Verts[124];
    lvl1Floor[143].posA = lvl1Verts[125]; lvl1Floor[143].posB = lvl1Verts[126]; lvl1Floor[143].posC = lvl1Verts[127];
    lvl1Floor[144].posA = lvl1Verts[128]; lvl1Floor[144].posB = lvl1Verts[121]; lvl1Floor[144].posC = lvl1Verts[123];
    lvl1Floor[145].posA = lvl1Verts[129]; lvl1Floor[145].posB = lvl1Verts[130]; lvl1Floor[145].posC = lvl1Verts[120];
    lvl1Floor[146].posA = lvl1Verts[126]; lvl1Floor[146].posB = lvl1Verts[131]; lvl1Floor[146].posC = lvl1Verts[132];
    lvl1Floor[147].posA = lvl1Verts[127]; lvl1Floor[147].posB = lvl1Verts[132]; lvl1Floor[147].posC = lvl1Verts[133];
    lvl1Floor[148].posA = lvl1Verts[134]; lvl1Floor[148].posB = lvl1Verts[118]; lvl1Floor[148].posC = lvl1Verts[131];
    lvl1Floor[149].posA = lvl1Verts[118]; lvl1Floor[149].posB = lvl1Verts[135]; lvl1Floor[149].posC = lvl1Verts[129];
    lvl1Floor[150].posA = lvl1Verts[132]; lvl1Floor[150].posB = lvl1Verts[119]; lvl1Floor[150].posC = lvl1Verts[128];
    lvl1Floor[151].posA = lvl1Verts[133]; lvl1Floor[151].posB = lvl1Verts[128]; lvl1Floor[151].posC = lvl1Verts[122];
    lvl1Floor[152].posA = lvl1Verts[131]; lvl1Floor[152].posB = lvl1Verts[129]; lvl1Floor[152].posC = lvl1Verts[119];
    lvl1Floor[153].posA = lvl1Verts[136]; lvl1Floor[153].posB = lvl1Verts[137]; lvl1Floor[153].posC = lvl1Verts[138];
    lvl1Floor[154].posA = lvl1Verts[139]; lvl1Floor[154].posB = lvl1Verts[138]; lvl1Floor[154].posC = lvl1Verts[140];
    lvl1Floor[155].posA = lvl1Verts[141]; lvl1Floor[155].posB = lvl1Verts[111]; lvl1Floor[155].posC = lvl1Verts[137];
    lvl1Floor[156].posA = lvl1Verts[140]; lvl1Floor[156].posB = lvl1Verts[142]; lvl1Floor[156].posC = lvl1Verts[125];
    lvl1Floor[157].posA = lvl1Verts[119]; lvl1Floor[157].posB = lvl1Verts[129]; lvl1Floor[157].posC = lvl1Verts[120];
    lvl1Floor[158].posA = lvl1Verts[122]; lvl1Floor[158].posB = lvl1Verts[128]; lvl1Floor[158].posC = lvl1Verts[123];
    lvl1Floor[159].posA = lvl1Verts[125]; lvl1Floor[159].posB = lvl1Verts[142]; lvl1Floor[159].posC = lvl1Verts[126];
    lvl1Floor[160].posA = lvl1Verts[128]; lvl1Floor[160].posB = lvl1Verts[119]; lvl1Floor[160].posC = lvl1Verts[121];
    lvl1Floor[161].posA = lvl1Verts[129]; lvl1Floor[161].posB = lvl1Verts[135]; lvl1Floor[161].posC = lvl1Verts[130];
    lvl1Floor[162].posA = lvl1Verts[126]; lvl1Floor[162].posB = lvl1Verts[134]; lvl1Floor[162].posC = lvl1Verts[131];
    lvl1Floor[163].posA = lvl1Verts[127]; lvl1Floor[163].posB = lvl1Verts[126]; lvl1Floor[163].posC = lvl1Verts[132];
    lvl1Floor[164].posA = lvl1Verts[134]; lvl1Floor[164].posB = lvl1Verts[117]; lvl1Floor[164].posC = lvl1Verts[118];
    lvl1Floor[165].posA = lvl1Verts[118]; lvl1Floor[165].posB = lvl1Verts[143]; lvl1Floor[165].posC = lvl1Verts[135];
    lvl1Floor[166].posA = lvl1Verts[132]; lvl1Floor[166].posB = lvl1Verts[131]; lvl1Floor[166].posC = lvl1Verts[119];
    lvl1Floor[167].posA = lvl1Verts[133]; lvl1Floor[167].posB = lvl1Verts[132]; lvl1Floor[167].posC = lvl1Verts[128];
    lvl1Floor[168].posA = lvl1Verts[131]; lvl1Floor[168].posB = lvl1Verts[118]; lvl1Floor[168].posC = lvl1Verts[129];
    lvl1Floor[169].posA = lvl1Verts[136]; lvl1Floor[169].posB = lvl1Verts[141]; lvl1Floor[169].posC = lvl1Verts[137];
    lvl1Floor[170].posA = lvl1Verts[139]; lvl1Floor[170].posB = lvl1Verts[136]; lvl1Floor[170].posC = lvl1Verts[138];
    lvl1Floor[171].posA = lvl1Verts[141]; lvl1Floor[171].posB = lvl1Verts[112]; lvl1Floor[171].posC = lvl1Verts[111];
    lvl1Floor[172].posA = lvl1Verts[140]; lvl1Floor[172].posB = lvl1Verts[138]; lvl1Floor[172].posC = lvl1Verts[142];
    lvl1Floor[173].posA = lvl1Verts[116]; lvl1Floor[173].posB = lvl1Verts[143]; lvl1Floor[173].posC = lvl1Verts[118];
    lvl1Floor[174].posA = lvl1Verts[110]; lvl1Floor[174].posB = lvl1Verts[113]; lvl1Floor[174].posC = lvl1Verts[111];
    lvl1Wall[0].posA = lvl1Verts[11]; lvl1Wall[0].posB = lvl1Verts[57]; lvl1Wall[0].posC = lvl1Verts[9];
    lvl1Wall[1].posA = lvl1Verts[6]; lvl1Wall[1].posB = lvl1Verts[58]; lvl1Wall[1].posC = lvl1Verts[30];
    lvl1Wall[2].posA = lvl1Verts[34]; lvl1Wall[2].posB = lvl1Verts[144]; lvl1Wall[2].posC = lvl1Verts[145];
    lvl1Wall[3].posA = lvl1Verts[27]; lvl1Wall[3].posB = lvl1Verts[51]; lvl1Wall[3].posC = lvl1Verts[146];
    lvl1Wall[4].posA = lvl1Verts[21]; lvl1Wall[4].posB = lvl1Verts[53]; lvl1Wall[4].posC = lvl1Verts[8];
    lvl1Wall[5].posA = lvl1Verts[24]; lvl1Wall[5].posB = lvl1Verts[146]; lvl1Wall[5].posC = lvl1Verts[147];
    lvl1Wall[6].posA = lvl1Verts[30]; lvl1Wall[6].posB = lvl1Verts[51]; lvl1Wall[6].posC = lvl1Verts[29];
    lvl1Wall[7].posA = lvl1Verts[35]; lvl1Wall[7].posB = lvl1Verts[148]; lvl1Wall[7].posC = lvl1Verts[149];
    lvl1Wall[8].posA = lvl1Verts[31]; lvl1Wall[8].posB = lvl1Verts[147]; lvl1Wall[8].posC = lvl1Verts[144];
    lvl1Wall[9].posA = lvl1Verts[8]; lvl1Wall[9].posB = lvl1Verts[60]; lvl1Wall[9].posC = lvl1Verts[6];
    lvl1Wall[10].posA = lvl1Verts[150]; lvl1Wall[10].posB = lvl1Verts[151]; lvl1Wall[10].posC = lvl1Verts[152];
    lvl1Wall[11].posA = lvl1Verts[9]; lvl1Wall[11].posB = lvl1Verts[55]; lvl1Wall[11].posC = lvl1Verts[21];
    lvl1Wall[12].posA = lvl1Verts[153]; lvl1Wall[12].posB = lvl1Verts[127]; lvl1Wall[12].posC = lvl1Verts[133];
    lvl1Wall[13].posA = lvl1Verts[148]; lvl1Wall[13].posB = lvl1Verts[154]; lvl1Wall[13].posC = lvl1Verts[149];
    lvl1Wall[14].posA = lvl1Verts[149]; lvl1Wall[14].posB = lvl1Verts[155]; lvl1Wall[14].posC = lvl1Verts[72];
    lvl1Wall[15].posA = lvl1Verts[155]; lvl1Wall[15].posB = lvl1Verts[154]; lvl1Wall[15].posC = lvl1Verts[82];
    lvl1Wall[16].posA = lvl1Verts[148]; lvl1Wall[16].posB = lvl1Verts[83]; lvl1Wall[16].posC = lvl1Verts[82];
    lvl1Wall[17].posA = lvl1Verts[82]; lvl1Wall[17].posB = lvl1Verts[84]; lvl1Wall[17].posC = lvl1Verts[155];
    lvl1Wall[18].posA = lvl1Verts[156]; lvl1Wall[18].posB = lvl1Verts[148]; lvl1Wall[18].posC = lvl1Verts[35];
    lvl1Wall[19].posA = lvl1Verts[148]; lvl1Wall[19].posB = lvl1Verts[156]; lvl1Wall[19].posC = lvl1Verts[81];
    lvl1Wall[20].posA = lvl1Verts[81]; lvl1Wall[20].posB = lvl1Verts[156]; lvl1Wall[20].posC = lvl1Verts[157];
    lvl1Wall[21].posA = lvl1Verts[81]; lvl1Wall[21].posB = lvl1Verts[157]; lvl1Wall[21].posC = lvl1Verts[73];
    lvl1Wall[22].posA = lvl1Verts[148]; lvl1Wall[22].posB = lvl1Verts[81]; lvl1Wall[22].posC = lvl1Verts[83];
    lvl1Wall[23].posA = lvl1Verts[146]; lvl1Wall[23].posB = lvl1Verts[51]; lvl1Wall[23].posC = lvl1Verts[158];
    lvl1Wall[24].posA = lvl1Verts[145]; lvl1Wall[24].posB = lvl1Verts[159]; lvl1Wall[24].posC = lvl1Verts[160];
    lvl1Wall[25].posA = lvl1Verts[147]; lvl1Wall[25].posB = lvl1Verts[158]; lvl1Wall[25].posC = lvl1Verts[161];
    lvl1Wall[26].posA = lvl1Verts[144]; lvl1Wall[26].posB = lvl1Verts[161]; lvl1Wall[26].posC = lvl1Verts[159];
    lvl1Wall[27].posA = lvl1Verts[160]; lvl1Wall[27].posB = lvl1Verts[162]; lvl1Wall[27].posC = lvl1Verts[163];
    lvl1Wall[28].posA = lvl1Verts[161]; lvl1Wall[28].posB = lvl1Verts[158]; lvl1Wall[28].posC = lvl1Verts[164];
    lvl1Wall[29].posA = lvl1Verts[159]; lvl1Wall[29].posB = lvl1Verts[164]; lvl1Wall[29].posC = lvl1Verts[162];
    lvl1Wall[30].posA = lvl1Verts[163]; lvl1Wall[30].posB = lvl1Verts[37]; lvl1Wall[30].posC = lvl1Verts[36];
    lvl1Wall[31].posA = lvl1Verts[162]; lvl1Wall[31].posB = lvl1Verts[164]; lvl1Wall[31].posC = lvl1Verts[37];
    lvl1Wall[32].posA = lvl1Verts[34]; lvl1Wall[32].posB = lvl1Verts[31]; lvl1Wall[32].posC = lvl1Verts[144];
    lvl1Wall[33].posA = lvl1Verts[27]; lvl1Wall[33].posB = lvl1Verts[29]; lvl1Wall[33].posC = lvl1Verts[51];
    lvl1Wall[34].posA = lvl1Verts[24]; lvl1Wall[34].posB = lvl1Verts[27]; lvl1Wall[34].posC = lvl1Verts[146];
    lvl1Wall[35].posA = lvl1Verts[31]; lvl1Wall[35].posB = lvl1Verts[24]; lvl1Wall[35].posC = lvl1Verts[147];
    lvl1Wall[36].posA = lvl1Verts[145]; lvl1Wall[36].posB = lvl1Verts[144]; lvl1Wall[36].posC = lvl1Verts[159];
    lvl1Wall[37].posA = lvl1Verts[147]; lvl1Wall[37].posB = lvl1Verts[146]; lvl1Wall[37].posC = lvl1Verts[158];
    lvl1Wall[38].posA = lvl1Verts[144]; lvl1Wall[38].posB = lvl1Verts[147]; lvl1Wall[38].posC = lvl1Verts[161];
    lvl1Wall[39].posA = lvl1Verts[160]; lvl1Wall[39].posB = lvl1Verts[159]; lvl1Wall[39].posC = lvl1Verts[162];
    lvl1Wall[40].posA = lvl1Verts[159]; lvl1Wall[40].posB = lvl1Verts[161]; lvl1Wall[40].posC = lvl1Verts[164];
    lvl1Wall[41].posA = lvl1Verts[163]; lvl1Wall[41].posB = lvl1Verts[162]; lvl1Wall[41].posC = lvl1Verts[37];
    lvl1Wall[42].posA = lvl1Verts[165]; lvl1Wall[42].posB = lvl1Verts[77]; lvl1Wall[42].posC = lvl1Verts[76];
    lvl1Wall[43].posA = lvl1Verts[166]; lvl1Wall[43].posB = lvl1Verts[167]; lvl1Wall[43].posC = lvl1Verts[165];
    lvl1Wall[44].posA = lvl1Verts[168]; lvl1Wall[44].posB = lvl1Verts[169]; lvl1Wall[44].posC = lvl1Verts[170];
    lvl1Wall[45].posA = lvl1Verts[170]; lvl1Wall[45].posB = lvl1Verts[62]; lvl1Wall[45].posC = lvl1Verts[86];
    lvl1Wall[46].posA = lvl1Verts[165]; lvl1Wall[46].posB = lvl1Verts[167]; lvl1Wall[46].posC = lvl1Verts[77];
    lvl1Wall[47].posA = lvl1Verts[166]; lvl1Wall[47].posB = lvl1Verts[168]; lvl1Wall[47].posC = lvl1Verts[167];
    lvl1Wall[48].posA = lvl1Verts[168]; lvl1Wall[48].posB = lvl1Verts[166]; lvl1Wall[48].posC = lvl1Verts[169];
    lvl1Wall[49].posA = lvl1Verts[170]; lvl1Wall[49].posB = lvl1Verts[169]; lvl1Wall[49].posC = lvl1Verts[62];
    lvl1Wall[50].posA = lvl1Verts[155]; lvl1Wall[50].posB = lvl1Verts[84]; lvl1Wall[50].posC = lvl1Verts[85];
    lvl1Wall[51].posA = lvl1Verts[171]; lvl1Wall[51].posB = lvl1Verts[72]; lvl1Wall[51].posC = lvl1Verts[172];
    lvl1Wall[52].posA = lvl1Verts[169]; lvl1Wall[52].posB = lvl1Verts[85]; lvl1Wall[52].posC = lvl1Verts[62];
    lvl1Wall[53].posA = lvl1Verts[76]; lvl1Wall[53].posB = lvl1Verts[89]; lvl1Wall[53].posC = lvl1Verts[165];
    lvl1Wall[54].posA = lvl1Verts[169]; lvl1Wall[54].posB = lvl1Verts[172]; lvl1Wall[54].posC = lvl1Verts[85];
    lvl1Wall[55].posA = lvl1Verts[172]; lvl1Wall[55].posB = lvl1Verts[72]; lvl1Wall[55].posC = lvl1Verts[155];
    lvl1Wall[56].posA = lvl1Verts[85]; lvl1Wall[56].posB = lvl1Verts[172]; lvl1Wall[56].posC = lvl1Verts[155];
    lvl1Wall[57].posA = lvl1Verts[172]; lvl1Wall[57].posB = lvl1Verts[173]; lvl1Wall[57].posC = lvl1Verts[171];
    lvl1Wall[58].posA = lvl1Verts[172]; lvl1Wall[58].posB = lvl1Verts[174]; lvl1Wall[58].posC = lvl1Verts[173];
    lvl1Wall[59].posA = lvl1Verts[172]; lvl1Wall[59].posB = lvl1Verts[165]; lvl1Wall[59].posC = lvl1Verts[174];
    lvl1Wall[60].posA = lvl1Verts[172]; lvl1Wall[60].posB = lvl1Verts[166]; lvl1Wall[60].posC = lvl1Verts[165];
    lvl1Wall[61].posA = lvl1Verts[172]; lvl1Wall[61].posB = lvl1Verts[169]; lvl1Wall[61].posC = lvl1Verts[166];
    lvl1Wall[62].posA = lvl1Verts[171]; lvl1Wall[62].posB = lvl1Verts[173]; lvl1Wall[62].posC = lvl1Verts[87];
    lvl1Wall[63].posA = lvl1Verts[174]; lvl1Wall[63].posB = lvl1Verts[87]; lvl1Wall[63].posC = lvl1Verts[173];
    lvl1Wall[64].posA = lvl1Verts[174]; lvl1Wall[64].posB = lvl1Verts[165]; lvl1Wall[64].posC = lvl1Verts[89];
    lvl1Wall[65].posA = lvl1Verts[149]; lvl1Wall[65].posB = lvl1Verts[154]; lvl1Wall[65].posC = lvl1Verts[155];
    lvl1Wall[66].posA = lvl1Verts[154]; lvl1Wall[66].posB = lvl1Verts[148]; lvl1Wall[66].posC = lvl1Verts[82];
    lvl1Wall[67].posA = lvl1Verts[174]; lvl1Wall[67].posB = lvl1Verts[89]; lvl1Wall[67].posC = lvl1Verts[87];
    lvl1Wall[68].posA = lvl1Verts[47]; lvl1Wall[68].posB = lvl1Verts[49]; lvl1Wall[68].posC = lvl1Verts[175];
    lvl1Wall[69].posA = lvl1Verts[176]; lvl1Wall[69].posB = lvl1Verts[140]; lvl1Wall[69].posC = lvl1Verts[125];
    lvl1Wall[70].posA = lvl1Verts[54]; lvl1Wall[70].posB = lvl1Verts[177]; lvl1Wall[70].posC = lvl1Verts[178];
    lvl1Wall[71].posA = lvl1Verts[46]; lvl1Wall[71].posB = lvl1Verts[179]; lvl1Wall[71].posC = lvl1Verts[180];
    lvl1Wall[72].posA = lvl1Verts[151]; lvl1Wall[72].posB = lvl1Verts[120]; lvl1Wall[72].posC = lvl1Verts[130];
    lvl1Wall[73].posA = lvl1Verts[181]; lvl1Wall[73].posB = lvl1Verts[92]; lvl1Wall[73].posC = lvl1Verts[102];
    lvl1Wall[74].posA = lvl1Verts[104]; lvl1Wall[74].posB = lvl1Verts[47]; lvl1Wall[74].posC = lvl1Verts[175];
    lvl1Wall[75].posA = lvl1Verts[182]; lvl1Wall[75].posB = lvl1Verts[102]; lvl1Wall[75].posC = lvl1Verts[104];
    lvl1Wall[76].posA = lvl1Verts[175]; lvl1Wall[76].posB = lvl1Verts[152]; lvl1Wall[76].posC = lvl1Verts[183];
    lvl1Wall[77].posA = lvl1Verts[150]; lvl1Wall[77].posB = lvl1Verts[152]; lvl1Wall[77].posC = lvl1Verts[175];
    lvl1Wall[78].posA = lvl1Verts[184]; lvl1Wall[78].posB = lvl1Verts[185]; lvl1Wall[78].posC = lvl1Verts[186];
    lvl1Wall[79].posA = lvl1Verts[187]; lvl1Wall[79].posB = lvl1Verts[90]; lvl1Wall[79].posC = lvl1Verts[188];
    lvl1Wall[80].posA = lvl1Verts[189]; lvl1Wall[80].posB = lvl1Verts[190]; lvl1Wall[80].posC = lvl1Verts[191];
    lvl1Wall[81].posA = lvl1Verts[49]; lvl1Wall[81].posB = lvl1Verts[150]; lvl1Wall[81].posC = lvl1Verts[175];
    lvl1Wall[82].posA = lvl1Verts[56]; lvl1Wall[82].posB = lvl1Verts[177]; lvl1Wall[82].posC = lvl1Verts[54];
    lvl1Wall[83].posA = lvl1Verts[192]; lvl1Wall[83].posB = lvl1Verts[114]; lvl1Wall[83].posC = lvl1Verts[113];
    lvl1Wall[84].posA = lvl1Verts[193]; lvl1Wall[84].posB = lvl1Verts[123]; lvl1Wall[84].posC = lvl1Verts[121];
    lvl1Wall[85].posA = lvl1Verts[54]; lvl1Wall[85].posB = lvl1Verts[178]; lvl1Wall[85].posC = lvl1Verts[52];
    lvl1Wall[86].posA = lvl1Verts[52]; lvl1Wall[86].posB = lvl1Verts[192]; lvl1Wall[86].posC = lvl1Verts[59];
    lvl1Wall[87].posA = lvl1Verts[183]; lvl1Wall[87].posB = lvl1Verts[135]; lvl1Wall[87].posC = lvl1Verts[143];
    lvl1Wall[88].posA = lvl1Verts[56]; lvl1Wall[88].posB = lvl1Verts[194]; lvl1Wall[88].posC = lvl1Verts[177];
    lvl1Wall[89].posA = lvl1Verts[59]; lvl1Wall[89].posB = lvl1Verts[179]; lvl1Wall[89].posC = lvl1Verts[46];
    lvl1Wall[90].posA = lvl1Verts[195]; lvl1Wall[90].posB = lvl1Verts[133]; lvl1Wall[90].posC = lvl1Verts[122];
    lvl1Wall[91].posA = lvl1Verts[196]; lvl1Wall[91].posB = lvl1Verts[141]; lvl1Wall[91].posC = lvl1Verts[136];
    lvl1Wall[92].posA = lvl1Verts[187]; lvl1Wall[92].posB = lvl1Verts[184]; lvl1Wall[92].posC = lvl1Verts[90];
    lvl1Wall[93].posA = lvl1Verts[188]; lvl1Wall[93].posB = lvl1Verts[197]; lvl1Wall[93].posC = lvl1Verts[187];
    lvl1Wall[94].posA = lvl1Verts[198]; lvl1Wall[94].posB = lvl1Verts[199]; lvl1Wall[94].posC = lvl1Verts[111];
    lvl1Wall[95].posA = lvl1Verts[200]; lvl1Wall[95].posB = lvl1Verts[126]; lvl1Wall[95].posC = lvl1Verts[201];
    lvl1Wall[96].posA = lvl1Verts[202]; lvl1Wall[96].posB = lvl1Verts[111]; lvl1Wall[96].posC = lvl1Verts[199];
    lvl1Wall[97].posA = lvl1Verts[196]; lvl1Wall[97].posB = lvl1Verts[136]; lvl1Wall[97].posC = lvl1Verts[203];
    lvl1Wall[98].posA = lvl1Verts[195]; lvl1Wall[98].posB = lvl1Verts[122]; lvl1Wall[98].posC = lvl1Verts[188];
    lvl1Wall[99].posA = lvl1Verts[183]; lvl1Wall[99].posB = lvl1Verts[143]; lvl1Wall[99].posC = lvl1Verts[194];
    lvl1Wall[100].posA = lvl1Verts[193]; lvl1Wall[100].posB = lvl1Verts[121]; lvl1Wall[100].posC = lvl1Verts[204];
    lvl1Wall[101].posA = lvl1Verts[205]; lvl1Wall[101].posB = lvl1Verts[137]; lvl1Wall[101].posC = lvl1Verts[202];
    lvl1Wall[102].posA = lvl1Verts[206]; lvl1Wall[102].posB = lvl1Verts[194]; lvl1Wall[102].posC = lvl1Verts[143];
    lvl1Wall[103].posA = lvl1Verts[206]; lvl1Wall[103].posB = lvl1Verts[143]; lvl1Wall[103].posC = lvl1Verts[118];
    lvl1Wall[104].posA = lvl1Verts[207]; lvl1Wall[104].posB = lvl1Verts[198]; lvl1Wall[104].posC = lvl1Verts[115];
    lvl1Wall[105].posA = lvl1Verts[192]; lvl1Wall[105].posB = lvl1Verts[178]; lvl1Wall[105].posC = lvl1Verts[114];
    lvl1Wall[106].posA = lvl1Verts[151]; lvl1Wall[106].posB = lvl1Verts[130]; lvl1Wall[106].posC = lvl1Verts[152];
    lvl1Wall[107].posA = lvl1Verts[176]; lvl1Wall[107].posB = lvl1Verts[125]; lvl1Wall[107].posC = lvl1Verts[208];
    lvl1Wall[108].posA = lvl1Verts[153]; lvl1Wall[108].posB = lvl1Verts[133]; lvl1Wall[108].posC = lvl1Verts[195];
    lvl1Wall[109].posA = lvl1Verts[177]; lvl1Wall[109].posB = lvl1Verts[194]; lvl1Wall[109].posC = lvl1Verts[143];
    lvl1Wall[110].posA = lvl1Verts[203]; lvl1Wall[110].posB = lvl1Verts[139]; lvl1Wall[110].posC = lvl1Verts[209];
    lvl1Wall[111].posA = lvl1Verts[152]; lvl1Wall[111].posB = lvl1Verts[135]; lvl1Wall[111].posC = lvl1Verts[183];
    lvl1Wall[112].posA = lvl1Verts[207]; lvl1Wall[112].posB = lvl1Verts[134]; lvl1Wall[112].posC = lvl1Verts[200];
    lvl1Wall[113].posA = lvl1Verts[178]; lvl1Wall[113].posB = lvl1Verts[177]; lvl1Wall[113].posC = lvl1Verts[116];
    lvl1Wall[114].posA = lvl1Verts[209]; lvl1Wall[114].posB = lvl1Verts[140]; lvl1Wall[114].posC = lvl1Verts[176];
    lvl1Wall[115].posA = lvl1Verts[188]; lvl1Wall[115].posB = lvl1Verts[124]; lvl1Wall[115].posC = lvl1Verts[197];
    lvl1Wall[116].posA = lvl1Verts[180]; lvl1Wall[116].posB = lvl1Verts[141]; lvl1Wall[116].posC = lvl1Verts[196];
    lvl1Wall[117].posA = lvl1Verts[179]; lvl1Wall[117].posB = lvl1Verts[192]; lvl1Wall[117].posC = lvl1Verts[113];
    lvl1Wall[118].posA = lvl1Verts[197]; lvl1Wall[118].posB = lvl1Verts[123]; lvl1Wall[118].posC = lvl1Verts[193];
    lvl1Wall[119].posA = lvl1Verts[204]; lvl1Wall[119].posB = lvl1Verts[120]; lvl1Wall[119].posC = lvl1Verts[151];
    lvl1Wall[120].posA = lvl1Verts[208]; lvl1Wall[120].posB = lvl1Verts[127]; lvl1Wall[120].posC = lvl1Verts[153];
    lvl1Wall[121].posA = lvl1Verts[201]; lvl1Wall[121].posB = lvl1Verts[142]; lvl1Wall[121].posC = lvl1Verts[210];
    lvl1Wall[122].posA = lvl1Verts[180]; lvl1Wall[122].posB = lvl1Verts[179]; lvl1Wall[122].posC = lvl1Verts[110];
    lvl1Wall[123].posA = lvl1Verts[211]; lvl1Wall[123].posB = lvl1Verts[39]; lvl1Wall[123].posC = lvl1Verts[180];
    lvl1Wall[124].posA = lvl1Verts[212]; lvl1Wall[124].posB = lvl1Verts[213]; lvl1Wall[124].posC = lvl1Verts[198];
    lvl1Wall[125].posA = lvl1Verts[214]; lvl1Wall[125].posB = lvl1Verts[212]; lvl1Wall[125].posC = lvl1Verts[207];
    lvl1Wall[126].posA = lvl1Verts[213]; lvl1Wall[126].posB = lvl1Verts[211]; lvl1Wall[126].posC = lvl1Verts[199];
    lvl1Wall[127].posA = lvl1Verts[46]; lvl1Wall[127].posB = lvl1Verts[180]; lvl1Wall[127].posC = lvl1Verts[39];
    lvl1Wall[128].posA = lvl1Verts[210]; lvl1Wall[128].posB = lvl1Verts[138]; lvl1Wall[128].posC = lvl1Verts[205];
    lvl1Wall[129].posA = lvl1Verts[59]; lvl1Wall[129].posB = lvl1Verts[192]; lvl1Wall[129].posC = lvl1Verts[179];
    lvl1Wall[130].posA = lvl1Verts[103]; lvl1Wall[130].posB = lvl1Verts[214]; lvl1Wall[130].posC = lvl1Verts[206];
    lvl1Wall[131].posA = lvl1Verts[206]; lvl1Wall[131].posB = lvl1Verts[194]; lvl1Wall[131].posC = lvl1Verts[143];
    lvl1Wall[132].posA = lvl1Verts[206]; lvl1Wall[132].posB = lvl1Verts[143]; lvl1Wall[132].posC = lvl1Verts[118];
    lvl1Wall[133].posA = lvl1Verts[52]; lvl1Wall[133].posB = lvl1Verts[178]; lvl1Wall[133].posC = lvl1Verts[192];
    lvl1Wall[134].posA = lvl1Verts[215]; lvl1Wall[134].posB = lvl1Verts[90]; lvl1Wall[134].posC = lvl1Verts[92];
    lvl1Wall[135].posA = lvl1Verts[181]; lvl1Wall[135].posB = lvl1Verts[215]; lvl1Wall[135].posC = lvl1Verts[92];
    lvl1Wall[136].posA = lvl1Verts[175]; lvl1Wall[136].posB = lvl1Verts[183]; lvl1Wall[136].posC = lvl1Verts[182];
    lvl1Wall[137].posA = lvl1Verts[182]; lvl1Wall[137].posB = lvl1Verts[104]; lvl1Wall[137].posC = lvl1Verts[175];
    lvl1Wall[138].posA = lvl1Verts[182]; lvl1Wall[138].posB = lvl1Verts[181]; lvl1Wall[138].posC = lvl1Verts[102];
    lvl1Wall[139].posA = lvl1Verts[215]; lvl1Wall[139].posB = lvl1Verts[188]; lvl1Wall[139].posC = lvl1Verts[90];
    lvl1Wall[140].posA = lvl1Verts[211]; lvl1Wall[140].posB = lvl1Verts[180]; lvl1Wall[140].posC = lvl1Verts[199];
    lvl1Wall[141].posA = lvl1Verts[212]; lvl1Wall[141].posB = lvl1Verts[198]; lvl1Wall[141].posC = lvl1Verts[207];
    lvl1Wall[142].posA = lvl1Verts[214]; lvl1Wall[142].posB = lvl1Verts[207]; lvl1Wall[142].posC = lvl1Verts[206];
    lvl1Wall[143].posA = lvl1Verts[213]; lvl1Wall[143].posB = lvl1Verts[199]; lvl1Wall[143].posC = lvl1Verts[198];
    lvl1Wall[144].posA = lvl1Verts[177]; lvl1Wall[144].posB = lvl1Verts[143]; lvl1Wall[144].posC = lvl1Verts[116];
    lvl1Wall[145].posA = lvl1Verts[203]; lvl1Wall[145].posB = lvl1Verts[136]; lvl1Wall[145].posC = lvl1Verts[139];
    lvl1Wall[146].posA = lvl1Verts[152]; lvl1Wall[146].posB = lvl1Verts[130]; lvl1Wall[146].posC = lvl1Verts[135];
    lvl1Wall[147].posA = lvl1Verts[178]; lvl1Wall[147].posB = lvl1Verts[116]; lvl1Wall[147].posC = lvl1Verts[114];
    lvl1Wall[148].posA = lvl1Verts[209]; lvl1Wall[148].posB = lvl1Verts[139]; lvl1Wall[148].posC = lvl1Verts[140];
    lvl1Wall[149].posA = lvl1Verts[188]; lvl1Wall[149].posB = lvl1Verts[122]; lvl1Wall[149].posC = lvl1Verts[124];
    lvl1Wall[150].posA = lvl1Verts[180]; lvl1Wall[150].posB = lvl1Verts[112]; lvl1Wall[150].posC = lvl1Verts[141];
    lvl1Wall[151].posA = lvl1Verts[179]; lvl1Wall[151].posB = lvl1Verts[113]; lvl1Wall[151].posC = lvl1Verts[110];
    lvl1Wall[152].posA = lvl1Verts[197]; lvl1Wall[152].posB = lvl1Verts[124]; lvl1Wall[152].posC = lvl1Verts[123];
    lvl1Wall[153].posA = lvl1Verts[204]; lvl1Wall[153].posB = lvl1Verts[121]; lvl1Wall[153].posC = lvl1Verts[120];
    lvl1Wall[154].posA = lvl1Verts[208]; lvl1Wall[154].posB = lvl1Verts[125]; lvl1Wall[154].posC = lvl1Verts[127];
    lvl1Wall[155].posA = lvl1Verts[180]; lvl1Wall[155].posB = lvl1Verts[110]; lvl1Wall[155].posC = lvl1Verts[112];
    lvl1Wall[156].posA = lvl1Verts[216]; lvl1Wall[156].posB = lvl1Verts[204]; lvl1Wall[156].posC = lvl1Verts[151];
    lvl1Wall[157].posA = lvl1Verts[216]; lvl1Wall[157].posB = lvl1Verts[49]; lvl1Wall[157].posC = lvl1Verts[190];
    lvl1Wall[158].posA = lvl1Verts[204]; lvl1Wall[158].posB = lvl1Verts[185]; lvl1Wall[158].posC = lvl1Verts[193];
    lvl1Wall[159].posA = lvl1Verts[187]; lvl1Wall[159].posB = lvl1Verts[197]; lvl1Wall[159].posC = lvl1Verts[193];
    lvl1Wall[160].posA = lvl1Verts[189]; lvl1Wall[160].posB = lvl1Verts[186]; lvl1Wall[160].posC = lvl1Verts[185];
    lvl1Wall[161].posA = lvl1Verts[150]; lvl1Wall[161].posB = lvl1Verts[216]; lvl1Wall[161].posC = lvl1Verts[151];
    lvl1Wall[162].posA = lvl1Verts[184]; lvl1Wall[162].posB = lvl1Verts[187]; lvl1Wall[162].posC = lvl1Verts[185];
    lvl1Wall[163].posA = lvl1Verts[189]; lvl1Wall[163].posB = lvl1Verts[216]; lvl1Wall[163].posC = lvl1Verts[190];
    lvl1Wall[164].posA = lvl1Verts[216]; lvl1Wall[164].posB = lvl1Verts[189]; lvl1Wall[164].posC = lvl1Verts[204];
    lvl1Wall[165].posA = lvl1Verts[216]; lvl1Wall[165].posB = lvl1Verts[150]; lvl1Wall[165].posC = lvl1Verts[49];
    lvl1Wall[166].posA = lvl1Verts[204]; lvl1Wall[166].posB = lvl1Verts[189]; lvl1Wall[166].posC = lvl1Verts[185];
    lvl1Wall[167].posA = lvl1Verts[193]; lvl1Wall[167].posB = lvl1Verts[185]; lvl1Wall[167].posC = lvl1Verts[187];
    lvl1Wall[168].posA = lvl1Verts[189]; lvl1Wall[168].posB = lvl1Verts[191]; lvl1Wall[168].posC = lvl1Verts[186];
    lvl1Wall[169].posA = lvl1Verts[205]; lvl1Wall[169].posB = lvl1Verts[209]; lvl1Wall[169].posC = lvl1Verts[176];
    lvl1Wall[170].posA = lvl1Verts[208]; lvl1Wall[170].posB = lvl1Verts[201]; lvl1Wall[170].posC = lvl1Verts[210];
    lvl1Wall[171].posA = lvl1Verts[210]; lvl1Wall[171].posB = lvl1Verts[176]; lvl1Wall[171].posC = lvl1Verts[208];
    lvl1Wall[172].posA = lvl1Verts[205]; lvl1Wall[172].posB = lvl1Verts[203]; lvl1Wall[172].posC = lvl1Verts[209];
    lvl1Wall[173].posA = lvl1Verts[208]; lvl1Wall[173].posB = lvl1Verts[153]; lvl1Wall[173].posC = lvl1Verts[201];
    lvl1Wall[174].posA = lvl1Verts[210]; lvl1Wall[174].posB = lvl1Verts[205]; lvl1Wall[174].posC = lvl1Verts[176];
    lvl1Wall[175].posA = lvl1Verts[202]; lvl1Wall[175].posB = lvl1Verts[180]; lvl1Wall[175].posC = lvl1Verts[196];
    lvl1Wall[176].posA = lvl1Verts[205]; lvl1Wall[176].posB = lvl1Verts[196]; lvl1Wall[176].posC = lvl1Verts[203];
    lvl1Wall[177].posA = lvl1Verts[202]; lvl1Wall[177].posB = lvl1Verts[199]; lvl1Wall[177].posC = lvl1Verts[180];
    lvl1Wall[178].posA = lvl1Verts[205]; lvl1Wall[178].posB = lvl1Verts[202]; lvl1Wall[178].posC = lvl1Verts[196];
    lvl1Wall[179].posA = lvl1Verts[206]; lvl1Wall[179].posB = lvl1Verts[181]; lvl1Wall[179].posC = lvl1Verts[182];
    lvl1Wall[180].posA = lvl1Verts[195]; lvl1Wall[180].posB = lvl1Verts[201]; lvl1Wall[180].posC = lvl1Verts[153];
    lvl1Wall[181].posA = lvl1Verts[198]; lvl1Wall[181].posB = lvl1Verts[111]; lvl1Wall[181].posC = lvl1Verts[115];
    lvl1Wall[182].posA = lvl1Verts[200]; lvl1Wall[182].posB = lvl1Verts[134]; lvl1Wall[182].posC = lvl1Verts[126];
    lvl1Wall[183].posA = lvl1Verts[202]; lvl1Wall[183].posB = lvl1Verts[137]; lvl1Wall[183].posC = lvl1Verts[111];
    lvl1Wall[184].posA = lvl1Verts[205]; lvl1Wall[184].posB = lvl1Verts[138]; lvl1Wall[184].posC = lvl1Verts[137];
    lvl1Wall[185].posA = lvl1Verts[207]; lvl1Wall[185].posB = lvl1Verts[115]; lvl1Wall[185].posC = lvl1Verts[117];
    lvl1Wall[186].posA = lvl1Verts[207]; lvl1Wall[186].posB = lvl1Verts[117]; lvl1Wall[186].posC = lvl1Verts[134];
    lvl1Wall[187].posA = lvl1Verts[201]; lvl1Wall[187].posB = lvl1Verts[126]; lvl1Wall[187].posC = lvl1Verts[142];
    lvl1Wall[188].posA = lvl1Verts[210]; lvl1Wall[188].posB = lvl1Verts[142]; lvl1Wall[188].posC = lvl1Verts[138];
    lvl1Wall[189].posA = lvl1Verts[206]; lvl1Wall[189].posB = lvl1Verts[217]; lvl1Wall[189].posC = lvl1Verts[181];
    lvl1Wall[190].posA = lvl1Verts[215]; lvl1Wall[190].posB = lvl1Verts[195]; lvl1Wall[190].posC = lvl1Verts[188];
    lvl1Wall[191].posA = lvl1Verts[201]; lvl1Wall[191].posB = lvl1Verts[217]; lvl1Wall[191].posC = lvl1Verts[200];
    lvl1Wall[192].posA = lvl1Verts[217]; lvl1Wall[192].posB = lvl1Verts[215]; lvl1Wall[192].posC = lvl1Verts[181];
    lvl1Wall[193].posA = lvl1Verts[200]; lvl1Wall[193].posB = lvl1Verts[206]; lvl1Wall[193].posC = lvl1Verts[207];
    lvl1Wall[194].posA = lvl1Verts[195]; lvl1Wall[194].posB = lvl1Verts[218]; lvl1Wall[194].posC = lvl1Verts[201];
    lvl1Wall[195].posA = lvl1Verts[215]; lvl1Wall[195].posB = lvl1Verts[218]; lvl1Wall[195].posC = lvl1Verts[195];
    lvl1Wall[196].posA = lvl1Verts[201]; lvl1Wall[196].posB = lvl1Verts[218]; lvl1Wall[196].posC = lvl1Verts[217];
    lvl1Wall[197].posA = lvl1Verts[217]; lvl1Wall[197].posB = lvl1Verts[218]; lvl1Wall[197].posC = lvl1Verts[215];
    lvl1Wall[198].posA = lvl1Verts[200]; lvl1Wall[198].posB = lvl1Verts[217]; lvl1Wall[198].posC = lvl1Verts[206];
    lvl1Wall[199].posA = lvl1Verts[206]; lvl1Wall[199].posB = lvl1Verts[194]; lvl1Wall[199].posC = lvl1Verts[103];
    lvl1Wall[200].posA = lvl1Verts[194]; lvl1Wall[200].posB = lvl1Verts[56]; lvl1Wall[200].posC = lvl1Verts[103];
    lvl1Wall[201].posA = lvl1Verts[183]; lvl1Wall[201].posB = lvl1Verts[194]; lvl1Wall[201].posC = lvl1Verts[206];
    lvl1Wall[202].posA = lvl1Verts[206]; lvl1Wall[202].posB = lvl1Verts[182]; lvl1Wall[202].posC = lvl1Verts[183];
    lvl1Wall[203].posA = lvl1Verts[11]; lvl1Wall[203].posB = lvl1Verts[48]; lvl1Wall[203].posC = lvl1Verts[57];
    lvl1Wall[204].posA = lvl1Verts[6]; lvl1Wall[204].posB = lvl1Verts[60]; lvl1Wall[204].posC = lvl1Verts[58];
    lvl1Wall[205].posA = lvl1Verts[21]; lvl1Wall[205].posB = lvl1Verts[55]; lvl1Wall[205].posC = lvl1Verts[53];
    lvl1Wall[206].posA = lvl1Verts[30]; lvl1Wall[206].posB = lvl1Verts[58]; lvl1Wall[206].posC = lvl1Verts[51];
    lvl1Wall[207].posA = lvl1Verts[8]; lvl1Wall[207].posB = lvl1Verts[53]; lvl1Wall[207].posC = lvl1Verts[60];
    lvl1Wall[208].posA = lvl1Verts[9]; lvl1Wall[208].posB = lvl1Verts[57]; lvl1Wall[208].posC = lvl1Verts[55];
    lvl1Slope[0].posA = lvl1Verts[73]; lvl1Slope[0].posB = lvl1Verts[158]; lvl1Slope[0].posC = lvl1Verts[51];
    lvl1Slope[1].posA = lvl1Verts[157]; lvl1Slope[1].posB = lvl1Verts[164]; lvl1Slope[1].posC = lvl1Verts[158];
    lvl1Slope[2].posA = lvl1Verts[156]; lvl1Slope[2].posB = lvl1Verts[37]; lvl1Slope[2].posC = lvl1Verts[164];
    lvl1Slope[3].posA = lvl1Verts[219]; lvl1Slope[3].posB = lvl1Verts[72]; lvl1Slope[3].posC = lvl1Verts[171];
    lvl1Slope[4].posA = lvl1Verts[88]; lvl1Slope[4].posB = lvl1Verts[171]; lvl1Slope[4].posC = lvl1Verts[87];
    lvl1Slope[5].posA = lvl1Verts[72]; lvl1Slope[5].posB = lvl1Verts[74]; lvl1Slope[5].posC = lvl1Verts[35];
    lvl1Slope[6].posA = lvl1Verts[73]; lvl1Slope[6].posB = lvl1Verts[157]; lvl1Slope[6].posC = lvl1Verts[158];
    lvl1Slope[7].posA = lvl1Verts[156]; lvl1Slope[7].posB = lvl1Verts[35]; lvl1Slope[7].posC = lvl1Verts[37];
    lvl1Slope[8].posA = lvl1Verts[219]; lvl1Slope[8].posB = lvl1Verts[70]; lvl1Slope[8].posC = lvl1Verts[72];
    lvl1Slope[9].posA = lvl1Verts[88]; lvl1Slope[9].posB = lvl1Verts[219]; lvl1Slope[9].posC = lvl1Verts[171];
    lvl1Slope[10].posA = lvl1Verts[72]; lvl1Slope[10].posB = lvl1Verts[71]; lvl1Slope[10].posC = lvl1Verts[74];
    lvl1Slope[11].posA = lvl1Verts[157]; lvl1Slope[11].posB = lvl1Verts[156]; lvl1Slope[11].posC = lvl1Verts[164];

    for (int i = 0; i < lvl1FloorCount; i++) {
        lvl1Floor[i].type = SURFACE_FLOOR;
        lvl1Floor[i].center = center;
        lvl1Floor[i].normal = norm;
        lvl1Floor[i].center = calc_surface_center(lvl1Floor[i]);
        lvl1Floor[i].normal = calc_surface_norm(lvl1Floor[i]);
    }

    for (int i = 0; i < lvl1WallCount; i++) {
        lvl1Wall[i].type = SURFACE_WALL;
        lvl1Wall[i].center = center;
        lvl1Wall[i].normal = norm;
        lvl1Wall[i].center = calc_surface_center(lvl1Wall[i]);
        lvl1Wall[i].normal = calc_surface_norm(lvl1Wall[i]);
    }

    for (int i = 0; i < lvl1SlopeCount; i++) {
        lvl1Slope[i].type = SURFACE_SLOPE;
        lvl1Slope[i].center = center;
        lvl1Slope[i].normal = norm;
        lvl1Slope[i].center = calc_surface_center(lvl1Slope[i]);
        lvl1Slope[i].normal = calc_surface_norm(lvl1Slope[i]);
    }

    // Combine the surfaces for collision detection
    combine_surfaces(
       lvl1Surfaces, &lvl1SurfacesCount,
       lvl1Floor, lvl1FloorCount,
       lvl1Wall, lvl1WallCount,
       lvl1Slope, lvl1SlopeCount
    );

    // Allocate map's matrix and construct
    lvl1MatFP = malloc_uncached(sizeof(T3DMat4FP));
    t3d_mat4fp_from_srt_euler(lvl1MatFP, (float[3]){1.0f, 1.0f, 1.0f}, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});

    // Load model
    modelLvl1 = t3d_model_load("rom:/models/lvl_1.t3dm");

    // Create map's RSPQ block
    rspq_block_begin();
        t3d_matrix_push(lvl1MatFP);
        matCount++;
        rdpq_set_prim_color(WHITE);
        t3d_model_draw(modelLvl1);
        t3d_matrix_pop(1);
    dplLvl1 = rspq_block_end();
}
