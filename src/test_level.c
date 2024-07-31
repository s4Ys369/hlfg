#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "debug.h"
#include "collision.h"
#include "test_level.h"
#include "utils.h"

T3DMat4FP* testLevelMatFP;
T3DModel *modelTestLevel;
rspq_block_t *dplTestLevel;

T3DVec3 testLevelVerts[196] =
{
       {{512, 0, -398}},
       {{398, 0, -512}},
       {{398, 0, -398}},
       {{-171, 0, -398}},
       {{-284, 0, -512}},
       {{-284, 0, -398}},
       {{171, 0, -398}},
       {{57, 0, -512}},
       {{57, 0, -398}},
       {{171, 0, 284}},
       {{57, 0, 171}},
       {{57, 0, 284}},
       {{-171, 0, 284}},
       {{-284, 0, 171}},
       {{-284, 0, 284}},
       {{512, 0, 284}},
       {{398, 0, 171}},
       {{398, 0, 284}},
       {{-171, 0, -57}},
       {{-284, 0, -171}},
       {{-284, 0, -57}},
       {{512, 0, -57}},
       {{398, 0, -171}},
       {{398, 0, -57}},
       {{-398, 0, -57}},
       {{-512, 0, -171}},
       {{-512, 0, -57}},
       {{-398, 0, -398}},
       {{-512, 0, -512}},
       {{-512, 0, -398}},
       {{-398, 0, -171}},
       {{-398, 0, -512}},
       {{-57, 0, -398}},
       {{-171, 0, -512}},
       {{57, 0, -57}},
       {{-57, 0, -171}},
       {{-57, 0, -57}},
       {{-57, 0, -512}},
       {{284, 0, -398}},
       {{171, 0, -512}},
       {{284, 0, 171}},
       {{284, 0, 284}},
       {{284, 0, -512}},
       {{57, 0, -171}},
       {{-57, 0, -284}},
       {{-398, 0, -284}},
       {{-171, 0, -171}},
       {{-284, 0, -284}},
       {{512, 0, -171}},
       {{398, 0, -284}},
       {{57, 0, -284}},
       {{-171, 0, -284}},
       {{512, 0, -284}},
       {{284, 0, 57}},
       {{-57, 0, 57}},
       {{-57, 0, 171}},
       {{-171, 0, 57}},
       {{-171, 0, 171}},
       {{-398, 0, 57}},
       {{-398, 0, 171}},
       {{512, 0, 171}},
       {{398, 0, 57}},
       {{284, 0, -57}},
       {{171, 0, -57}},
       {{171, 0, 57}},
       {{57, 0, 57}},
       {{-512, 0, 57}},
       {{512, 0, 57}},
       {{398, 0, 512}},
       {{284, 0, 398}},
       {{284, 0, 512}},
       {{171, 0, 398}},
       {{171, 0, 512}},
       {{57, 0, 512}},
       {{-57, 0, 398}},
       {{-57, 0, 512}},
       {{512, 0, 512}},
       {{398, 0, 398}},
       {{57, 0, 398}},
       {{-171, 0, 398}},
       {{512, 0, 398}},
       {{512, 0, -512}},
       {{398, 64, -57}},
       {{284, 64, -171}},
       {{284, 64, -57}},
       {{398, 64, -171}},
       {{284, 128, -57}},
       {{171, 128, -171}},
       {{171, 128, -57}},
       {{284, 128, -171}},
       {{171, 192, -57}},
       {{57, 192, -171}},
       {{57, 192, -57}},
       {{171, 192, -171}},
       {{171, 256, -171}},
       {{57, 256, -284}},
       {{57, 256, -171}},
       {{171, 256, -284}},
       {{171, 320, -284}},
       {{57, 320, -398}},
       {{57, 320, -284}},
       {{171, 320, -398}},
       {{284, 384, -284}},
       {{171, 384, -398}},
       {{171, 384, -284}},
       {{284, 384, -398}},
       {{398, 448, -284}},
       {{284, 448, -398}},
       {{284, 448, -284}},
       {{398, 448, -398}},
       {{284, 582, -171}},
       {{171, 582, -284}},
       {{171, 582, -171}},
       {{284, 582, -284}},
       {{-57, 64, -57}},
       {{-171, 64, -171}},
       {{-171, 64, -57}},
       {{-57, 64, -171}},
       {{-57, 128, -171}},
       {{-171, 128, -284}},
       {{-171, 128, -171}},
       {{-57, 128, -284}},
       {{-512, 0, -284}},
       {{-284, 96, -284}},
       {{-398, 96, -284}},
       {{-398, 96, -398}},
       {{-284, 96, -398}},
       {{-284, 160, -284}},
       {{-398, 160, -398}},
       {{-398, 160, -284}},
       {{-284, 160, -398}},
       {{-398, 64, 284}},
       {{-512, 64, 171}},
       {{-512, 192, 284}},
       {{-57, 64, 284}},
       {{171, 128, 171}},
       {{-284, 192, 57}},
       {{-171, 64, 512}},
       {{-284, 192, 512}},
       {{-398, 192, 398}},
       {{-398, 256, 512}},
       {{-512, 256, 398}},
       {{-512, 320, 512}},
       {{-284, 64, 398}},
       {{398, 512, -171}},
       {{398, 512, -284}},
       {{398, 64, -398}},
       {{57, 64, -398}},
       {{-57, 64, -284}},
       {{171, 64, -398}},
       {{57, 64, -284}},
       {{57, 64, -57}},
       {{57, 64, -171}},
       {{171, 64, -57}},
       {{398, 64, -284}},
       {{284, 64, -398}},
       {{57, 128, -57}},
       {{284, 128, -398}},
       {{57, 128, -398}},
       {{57, 128, -284}},
       {{398, 128, -398}},
       {{398, 128, -284}},
       {{398, 128, -171}},
       {{57, 128, -171}},
       {{171, 128, -398}},
       {{284, 192, -398}},
       {{284, 192, -171}},
       {{57, 192, -398}},
       {{57, 192, -284}},
       {{398, 192, -398}},
       {{398, 192, -284}},
       {{398, 192, -171}},
       {{171, 192, -398}},
       {{398, 256, -398}},
       {{398, 256, -284}},
       {{398, 256, -171}},
       {{171, 256, -398}},
       {{284, 256, -171}},
       {{284, 256, -398}},
       {{57, 256, -398}},
       {{171, 320, -171}},
       {{398, 320, -284}},
       {{398, 320, -171}},
       {{284, 320, -171}},
       {{284, 320, -398}},
       {{398, 320, -398}},
       {{171, 384, -171}},
       {{398, 384, -284}},
       {{398, 384, -171}},
       {{284, 384, -171}},
       {{398, 384, -398}},
       {{284, 448, -171}},
       {{171, 448, -171}},
       {{171, 448, -284}},
       {{398, 448, -171}},
       {{-171, 64, -284}}
};

int testLevelFloorCount = 130;
Surface* testLevelFloor;
int testLevelSlopeCount = 36;
Surface* testLevelSlope;
int testLevelWallCount = 184;
Surface* testLevelWall;
int testLevelSurfacesCount = 0;
Surface* testLevelSurfaces;

void test_level_init(void){

    testLevelWall = malloc(testLevelWallCount * sizeof(Surface));
    testLevelSlope = malloc(testLevelSlopeCount * sizeof(Surface));
    testLevelFloor = malloc(testLevelFloorCount * sizeof(Surface));
    testLevelSurfaces = malloc((testLevelWallCount + testLevelSlopeCount + testLevelFloorCount) * sizeof(Surface));

    testLevelFloor[0].posA = testLevelVerts[0]; testLevelFloor[0].posB = testLevelVerts[1]; testLevelFloor[0].posC = testLevelVerts[2];
    testLevelFloor[1].posA = testLevelVerts[3]; testLevelFloor[1].posB = testLevelVerts[4]; testLevelFloor[1].posC = testLevelVerts[5];
    testLevelFloor[2].posA = testLevelVerts[6]; testLevelFloor[2].posB = testLevelVerts[7]; testLevelFloor[2].posC = testLevelVerts[8];
    testLevelFloor[3].posA = testLevelVerts[9]; testLevelFloor[3].posB = testLevelVerts[10]; testLevelFloor[3].posC = testLevelVerts[11];
    testLevelFloor[4].posA = testLevelVerts[12]; testLevelFloor[4].posB = testLevelVerts[13]; testLevelFloor[4].posC = testLevelVerts[14];
    testLevelFloor[5].posA = testLevelVerts[15]; testLevelFloor[5].posB = testLevelVerts[16]; testLevelFloor[5].posC = testLevelVerts[17];
    testLevelFloor[6].posA = testLevelVerts[18]; testLevelFloor[6].posB = testLevelVerts[19]; testLevelFloor[6].posC = testLevelVerts[20];
    testLevelFloor[7].posA = testLevelVerts[21]; testLevelFloor[7].posB = testLevelVerts[22]; testLevelFloor[7].posC = testLevelVerts[23];
    testLevelFloor[8].posA = testLevelVerts[24]; testLevelFloor[8].posB = testLevelVerts[25]; testLevelFloor[8].posC = testLevelVerts[26];
    testLevelFloor[9].posA = testLevelVerts[27]; testLevelFloor[9].posB = testLevelVerts[28]; testLevelFloor[9].posC = testLevelVerts[29];
    testLevelFloor[10].posA = testLevelVerts[20]; testLevelFloor[10].posB = testLevelVerts[30]; testLevelFloor[10].posC = testLevelVerts[24];
    testLevelFloor[11].posA = testLevelVerts[5]; testLevelFloor[11].posB = testLevelVerts[31]; testLevelFloor[11].posC = testLevelVerts[27];
    testLevelFloor[12].posA = testLevelVerts[32]; testLevelFloor[12].posB = testLevelVerts[33]; testLevelFloor[12].posC = testLevelVerts[3];
    testLevelFloor[13].posA = testLevelVerts[34]; testLevelFloor[13].posB = testLevelVerts[35]; testLevelFloor[13].posC = testLevelVerts[36];
    testLevelFloor[14].posA = testLevelVerts[8]; testLevelFloor[14].posB = testLevelVerts[37]; testLevelFloor[14].posC = testLevelVerts[32];
    testLevelFloor[15].posA = testLevelVerts[38]; testLevelFloor[15].posB = testLevelVerts[39]; testLevelFloor[15].posC = testLevelVerts[6];
    testLevelFloor[16].posA = testLevelVerts[17]; testLevelFloor[16].posB = testLevelVerts[40]; testLevelFloor[16].posC = testLevelVerts[41];
    testLevelFloor[17].posA = testLevelVerts[2]; testLevelFloor[17].posB = testLevelVerts[42]; testLevelFloor[17].posC = testLevelVerts[38];
    testLevelFloor[18].posA = testLevelVerts[43]; testLevelFloor[18].posB = testLevelVerts[44]; testLevelFloor[18].posC = testLevelVerts[35];
    testLevelFloor[19].posA = testLevelVerts[19]; testLevelFloor[19].posB = testLevelVerts[45]; testLevelFloor[19].posC = testLevelVerts[30];
    testLevelFloor[20].posA = testLevelVerts[46]; testLevelFloor[20].posB = testLevelVerts[47]; testLevelFloor[20].posC = testLevelVerts[19];
    testLevelFloor[21].posA = testLevelVerts[48]; testLevelFloor[21].posB = testLevelVerts[49]; testLevelFloor[21].posC = testLevelVerts[22];
    testLevelFloor[22].posA = testLevelVerts[50]; testLevelFloor[22].posB = testLevelVerts[32]; testLevelFloor[22].posC = testLevelVerts[44];
    testLevelFloor[23].posA = testLevelVerts[44]; testLevelFloor[23].posB = testLevelVerts[3]; testLevelFloor[23].posC = testLevelVerts[51];
    testLevelFloor[24].posA = testLevelVerts[51]; testLevelFloor[24].posB = testLevelVerts[5]; testLevelFloor[24].posC = testLevelVerts[47];
    testLevelFloor[25].posA = testLevelVerts[52]; testLevelFloor[25].posB = testLevelVerts[2]; testLevelFloor[25].posC = testLevelVerts[49];
    testLevelFloor[26].posA = testLevelVerts[16]; testLevelFloor[26].posB = testLevelVerts[53]; testLevelFloor[26].posC = testLevelVerts[40];
    testLevelFloor[27].posA = testLevelVerts[10]; testLevelFloor[27].posB = testLevelVerts[54]; testLevelFloor[27].posC = testLevelVerts[55];
    testLevelFloor[28].posA = testLevelVerts[55]; testLevelFloor[28].posB = testLevelVerts[56]; testLevelFloor[28].posC = testLevelVerts[57];
    testLevelFloor[29].posA = testLevelVerts[13]; testLevelFloor[29].posB = testLevelVerts[58]; testLevelFloor[29].posC = testLevelVerts[59];
    testLevelFloor[30].posA = testLevelVerts[60]; testLevelFloor[30].posB = testLevelVerts[61]; testLevelFloor[30].posC = testLevelVerts[16];
    testLevelFloor[31].posA = testLevelVerts[61]; testLevelFloor[31].posB = testLevelVerts[62]; testLevelFloor[31].posC = testLevelVerts[53];
    testLevelFloor[32].posA = testLevelVerts[53]; testLevelFloor[32].posB = testLevelVerts[63]; testLevelFloor[32].posC = testLevelVerts[64];
    testLevelFloor[33].posA = testLevelVerts[65]; testLevelFloor[33].posB = testLevelVerts[36]; testLevelFloor[33].posC = testLevelVerts[54];
    testLevelFloor[34].posA = testLevelVerts[54]; testLevelFloor[34].posB = testLevelVerts[18]; testLevelFloor[34].posC = testLevelVerts[56];
    testLevelFloor[35].posA = testLevelVerts[58]; testLevelFloor[35].posB = testLevelVerts[26]; testLevelFloor[35].posC = testLevelVerts[66];
    testLevelFloor[36].posA = testLevelVerts[67]; testLevelFloor[36].posB = testLevelVerts[23]; testLevelFloor[36].posC = testLevelVerts[61];
    testLevelFloor[37].posA = testLevelVerts[64]; testLevelFloor[37].posB = testLevelVerts[34]; testLevelFloor[37].posC = testLevelVerts[65];
    testLevelFloor[38].posA = testLevelVerts[68]; testLevelFloor[38].posB = testLevelVerts[69]; testLevelFloor[38].posC = testLevelVerts[70];
    testLevelFloor[39].posA = testLevelVerts[70]; testLevelFloor[39].posB = testLevelVerts[71]; testLevelFloor[39].posC = testLevelVerts[72];
    testLevelFloor[40].posA = testLevelVerts[73]; testLevelFloor[40].posB = testLevelVerts[74]; testLevelFloor[40].posC = testLevelVerts[75];
    testLevelFloor[41].posA = testLevelVerts[76]; testLevelFloor[41].posB = testLevelVerts[77]; testLevelFloor[41].posC = testLevelVerts[68];
    testLevelFloor[42].posA = testLevelVerts[72]; testLevelFloor[42].posB = testLevelVerts[78]; testLevelFloor[42].posC = testLevelVerts[73];
    testLevelFloor[43].posA = testLevelVerts[77]; testLevelFloor[43].posB = testLevelVerts[41]; testLevelFloor[43].posC = testLevelVerts[69];
    testLevelFloor[44].posA = testLevelVerts[69]; testLevelFloor[44].posB = testLevelVerts[9]; testLevelFloor[44].posC = testLevelVerts[71];
    testLevelFloor[45].posA = testLevelVerts[74]; testLevelFloor[45].posB = testLevelVerts[12]; testLevelFloor[45].posC = testLevelVerts[79];
    testLevelFloor[46].posA = testLevelVerts[80]; testLevelFloor[46].posB = testLevelVerts[17]; testLevelFloor[46].posC = testLevelVerts[77];
    testLevelFloor[47].posA = testLevelVerts[71]; testLevelFloor[47].posB = testLevelVerts[11]; testLevelFloor[47].posC = testLevelVerts[78];
    testLevelFloor[48].posA = testLevelVerts[0]; testLevelFloor[48].posB = testLevelVerts[81]; testLevelFloor[48].posC = testLevelVerts[1];
    testLevelFloor[49].posA = testLevelVerts[3]; testLevelFloor[49].posB = testLevelVerts[33]; testLevelFloor[49].posC = testLevelVerts[4];
    testLevelFloor[50].posA = testLevelVerts[6]; testLevelFloor[50].posB = testLevelVerts[39]; testLevelFloor[50].posC = testLevelVerts[7];
    testLevelFloor[51].posA = testLevelVerts[12]; testLevelFloor[51].posB = testLevelVerts[57]; testLevelFloor[51].posC = testLevelVerts[13];
    testLevelFloor[52].posA = testLevelVerts[15]; testLevelFloor[52].posB = testLevelVerts[60]; testLevelFloor[52].posC = testLevelVerts[16];
    testLevelFloor[53].posA = testLevelVerts[18]; testLevelFloor[53].posB = testLevelVerts[46]; testLevelFloor[53].posC = testLevelVerts[19];
    testLevelFloor[54].posA = testLevelVerts[21]; testLevelFloor[54].posB = testLevelVerts[48]; testLevelFloor[54].posC = testLevelVerts[22];
    testLevelFloor[55].posA = testLevelVerts[24]; testLevelFloor[55].posB = testLevelVerts[30]; testLevelFloor[55].posC = testLevelVerts[25];
    testLevelFloor[56].posA = testLevelVerts[27]; testLevelFloor[56].posB = testLevelVerts[31]; testLevelFloor[56].posC = testLevelVerts[28];
    testLevelFloor[57].posA = testLevelVerts[20]; testLevelFloor[57].posB = testLevelVerts[19]; testLevelFloor[57].posC = testLevelVerts[30];
    testLevelFloor[58].posA = testLevelVerts[14]; testLevelFloor[58].posB = testLevelVerts[13]; testLevelFloor[58].posC = testLevelVerts[59];
    testLevelFloor[59].posA = testLevelVerts[5]; testLevelFloor[59].posB = testLevelVerts[4]; testLevelFloor[59].posC = testLevelVerts[31];
    testLevelFloor[60].posA = testLevelVerts[32]; testLevelFloor[60].posB = testLevelVerts[37]; testLevelFloor[60].posC = testLevelVerts[33];
    testLevelFloor[61].posA = testLevelVerts[34]; testLevelFloor[61].posB = testLevelVerts[43]; testLevelFloor[61].posC = testLevelVerts[35];
    testLevelFloor[62].posA = testLevelVerts[11]; testLevelFloor[62].posB = testLevelVerts[10]; testLevelFloor[62].posC = testLevelVerts[55];
    testLevelFloor[63].posA = testLevelVerts[8]; testLevelFloor[63].posB = testLevelVerts[7]; testLevelFloor[63].posC = testLevelVerts[37];
    testLevelFloor[64].posA = testLevelVerts[38]; testLevelFloor[64].posB = testLevelVerts[42]; testLevelFloor[64].posC = testLevelVerts[39];
    testLevelFloor[65].posA = testLevelVerts[17]; testLevelFloor[65].posB = testLevelVerts[16]; testLevelFloor[65].posC = testLevelVerts[40];
    testLevelFloor[66].posA = testLevelVerts[2]; testLevelFloor[66].posB = testLevelVerts[1]; testLevelFloor[66].posC = testLevelVerts[42];
    testLevelFloor[67].posA = testLevelVerts[43]; testLevelFloor[67].posB = testLevelVerts[50]; testLevelFloor[67].posC = testLevelVerts[44];
    testLevelFloor[68].posA = testLevelVerts[19]; testLevelFloor[68].posB = testLevelVerts[47]; testLevelFloor[68].posC = testLevelVerts[45];
    testLevelFloor[69].posA = testLevelVerts[46]; testLevelFloor[69].posB = testLevelVerts[51]; testLevelFloor[69].posC = testLevelVerts[47];
    testLevelFloor[70].posA = testLevelVerts[48]; testLevelFloor[70].posB = testLevelVerts[52]; testLevelFloor[70].posC = testLevelVerts[49];
    testLevelFloor[71].posA = testLevelVerts[50]; testLevelFloor[71].posB = testLevelVerts[8]; testLevelFloor[71].posC = testLevelVerts[32];
    testLevelFloor[72].posA = testLevelVerts[44]; testLevelFloor[72].posB = testLevelVerts[32]; testLevelFloor[72].posC = testLevelVerts[3];
    testLevelFloor[73].posA = testLevelVerts[51]; testLevelFloor[73].posB = testLevelVerts[3]; testLevelFloor[73].posC = testLevelVerts[5];
    testLevelFloor[74].posA = testLevelVerts[52]; testLevelFloor[74].posB = testLevelVerts[0]; testLevelFloor[74].posC = testLevelVerts[2];
    testLevelFloor[75].posA = testLevelVerts[16]; testLevelFloor[75].posB = testLevelVerts[61]; testLevelFloor[75].posC = testLevelVerts[53];
    testLevelFloor[76].posA = testLevelVerts[40]; testLevelFloor[76].posB = testLevelVerts[53]; testLevelFloor[76].posC = testLevelVerts[64];
    testLevelFloor[77].posA = testLevelVerts[10]; testLevelFloor[77].posB = testLevelVerts[65]; testLevelFloor[77].posC = testLevelVerts[54];
    testLevelFloor[78].posA = testLevelVerts[55]; testLevelFloor[78].posB = testLevelVerts[54]; testLevelFloor[78].posC = testLevelVerts[56];
    testLevelFloor[79].posA = testLevelVerts[59]; testLevelFloor[79].posB = testLevelVerts[58]; testLevelFloor[79].posC = testLevelVerts[66];
    testLevelFloor[80].posA = testLevelVerts[60]; testLevelFloor[80].posB = testLevelVerts[67]; testLevelFloor[80].posC = testLevelVerts[61];
    testLevelFloor[81].posA = testLevelVerts[61]; testLevelFloor[81].posB = testLevelVerts[23]; testLevelFloor[81].posC = testLevelVerts[62];
    testLevelFloor[82].posA = testLevelVerts[53]; testLevelFloor[82].posB = testLevelVerts[62]; testLevelFloor[82].posC = testLevelVerts[63];
    testLevelFloor[83].posA = testLevelVerts[65]; testLevelFloor[83].posB = testLevelVerts[34]; testLevelFloor[83].posC = testLevelVerts[36];
    testLevelFloor[84].posA = testLevelVerts[54]; testLevelFloor[84].posB = testLevelVerts[36]; testLevelFloor[84].posC = testLevelVerts[18];
    testLevelFloor[85].posA = testLevelVerts[58]; testLevelFloor[85].posB = testLevelVerts[24]; testLevelFloor[85].posC = testLevelVerts[26];
    testLevelFloor[86].posA = testLevelVerts[67]; testLevelFloor[86].posB = testLevelVerts[21]; testLevelFloor[86].posC = testLevelVerts[23];
    testLevelFloor[87].posA = testLevelVerts[56]; testLevelFloor[87].posB = testLevelVerts[18]; testLevelFloor[87].posC = testLevelVerts[20];
    testLevelFloor[88].posA = testLevelVerts[64]; testLevelFloor[88].posB = testLevelVerts[63]; testLevelFloor[88].posC = testLevelVerts[34];
    testLevelFloor[89].posA = testLevelVerts[68]; testLevelFloor[89].posB = testLevelVerts[77]; testLevelFloor[89].posC = testLevelVerts[69];
    testLevelFloor[90].posA = testLevelVerts[70]; testLevelFloor[90].posB = testLevelVerts[69]; testLevelFloor[90].posC = testLevelVerts[71];
    testLevelFloor[91].posA = testLevelVerts[73]; testLevelFloor[91].posB = testLevelVerts[78]; testLevelFloor[91].posC = testLevelVerts[74];
    testLevelFloor[92].posA = testLevelVerts[75]; testLevelFloor[92].posB = testLevelVerts[74]; testLevelFloor[92].posC = testLevelVerts[79];
    testLevelFloor[93].posA = testLevelVerts[76]; testLevelFloor[93].posB = testLevelVerts[80]; testLevelFloor[93].posC = testLevelVerts[77];
    testLevelFloor[94].posA = testLevelVerts[72]; testLevelFloor[94].posB = testLevelVerts[71]; testLevelFloor[94].posC = testLevelVerts[78];
    testLevelFloor[95].posA = testLevelVerts[77]; testLevelFloor[95].posB = testLevelVerts[17]; testLevelFloor[95].posC = testLevelVerts[41];
    testLevelFloor[96].posA = testLevelVerts[69]; testLevelFloor[96].posB = testLevelVerts[41]; testLevelFloor[96].posC = testLevelVerts[9];
    testLevelFloor[97].posA = testLevelVerts[80]; testLevelFloor[97].posB = testLevelVerts[15]; testLevelFloor[97].posC = testLevelVerts[17];
    testLevelFloor[98].posA = testLevelVerts[79]; testLevelFloor[98].posB = testLevelVerts[12]; testLevelFloor[98].posC = testLevelVerts[14];
    testLevelFloor[99].posA = testLevelVerts[71]; testLevelFloor[99].posB = testLevelVerts[9]; testLevelFloor[99].posC = testLevelVerts[11];
    testLevelFloor[100].posA = testLevelVerts[82]; testLevelFloor[100].posB = testLevelVerts[83]; testLevelFloor[100].posC = testLevelVerts[84];
    testLevelFloor[101].posA = testLevelVerts[82]; testLevelFloor[101].posB = testLevelVerts[85]; testLevelFloor[101].posC = testLevelVerts[83];
    testLevelFloor[102].posA = testLevelVerts[86]; testLevelFloor[102].posB = testLevelVerts[87]; testLevelFloor[102].posC = testLevelVerts[88];
    testLevelFloor[103].posA = testLevelVerts[86]; testLevelFloor[103].posB = testLevelVerts[89]; testLevelFloor[103].posC = testLevelVerts[87];
    testLevelFloor[104].posA = testLevelVerts[90]; testLevelFloor[104].posB = testLevelVerts[91]; testLevelFloor[104].posC = testLevelVerts[92];
    testLevelFloor[105].posA = testLevelVerts[90]; testLevelFloor[105].posB = testLevelVerts[93]; testLevelFloor[105].posC = testLevelVerts[91];
    testLevelFloor[106].posA = testLevelVerts[94]; testLevelFloor[106].posB = testLevelVerts[95]; testLevelFloor[106].posC = testLevelVerts[96];
    testLevelFloor[107].posA = testLevelVerts[94]; testLevelFloor[107].posB = testLevelVerts[97]; testLevelFloor[107].posC = testLevelVerts[95];
    testLevelFloor[108].posA = testLevelVerts[98]; testLevelFloor[108].posB = testLevelVerts[99]; testLevelFloor[108].posC = testLevelVerts[100];
    testLevelFloor[109].posA = testLevelVerts[98]; testLevelFloor[109].posB = testLevelVerts[101]; testLevelFloor[109].posC = testLevelVerts[99];
    testLevelFloor[110].posA = testLevelVerts[102]; testLevelFloor[110].posB = testLevelVerts[103]; testLevelFloor[110].posC = testLevelVerts[104];
    testLevelFloor[111].posA = testLevelVerts[102]; testLevelFloor[111].posB = testLevelVerts[105]; testLevelFloor[111].posC = testLevelVerts[103];
    testLevelFloor[112].posA = testLevelVerts[106]; testLevelFloor[112].posB = testLevelVerts[107]; testLevelFloor[112].posC = testLevelVerts[108];
    testLevelFloor[113].posA = testLevelVerts[106]; testLevelFloor[113].posB = testLevelVerts[109]; testLevelFloor[113].posC = testLevelVerts[107];
    testLevelFloor[114].posA = testLevelVerts[110]; testLevelFloor[114].posB = testLevelVerts[111]; testLevelFloor[114].posC = testLevelVerts[112];
    testLevelFloor[115].posA = testLevelVerts[110]; testLevelFloor[115].posB = testLevelVerts[113]; testLevelFloor[115].posC = testLevelVerts[111];
    testLevelFloor[116].posA = testLevelVerts[114]; testLevelFloor[116].posB = testLevelVerts[115]; testLevelFloor[116].posC = testLevelVerts[116];
    testLevelFloor[117].posA = testLevelVerts[114]; testLevelFloor[117].posB = testLevelVerts[117]; testLevelFloor[117].posC = testLevelVerts[115];
    testLevelFloor[118].posA = testLevelVerts[118]; testLevelFloor[118].posB = testLevelVerts[119]; testLevelFloor[118].posC = testLevelVerts[120];
    testLevelFloor[119].posA = testLevelVerts[118]; testLevelFloor[119].posB = testLevelVerts[121]; testLevelFloor[119].posC = testLevelVerts[119];
    testLevelFloor[120].posA = testLevelVerts[5]; testLevelFloor[120].posB = testLevelVerts[27]; testLevelFloor[120].posC = testLevelVerts[47];
    testLevelFloor[121].posA = testLevelVerts[45]; testLevelFloor[121].posB = testLevelVerts[47]; testLevelFloor[121].posC = testLevelVerts[27];
    testLevelFloor[122].posA = testLevelVerts[25]; testLevelFloor[122].posB = testLevelVerts[30]; testLevelFloor[122].posC = testLevelVerts[122];
    testLevelFloor[123].posA = testLevelVerts[45]; testLevelFloor[123].posB = testLevelVerts[122]; testLevelFloor[123].posC = testLevelVerts[30];
    testLevelFloor[124].posA = testLevelVerts[45]; testLevelFloor[124].posB = testLevelVerts[29]; testLevelFloor[124].posC = testLevelVerts[122];
    testLevelFloor[125].posA = testLevelVerts[27]; testLevelFloor[125].posB = testLevelVerts[29]; testLevelFloor[125].posC = testLevelVerts[45];
    testLevelFloor[126].posA = testLevelVerts[123]; testLevelFloor[126].posB = testLevelVerts[124]; testLevelFloor[126].posC = testLevelVerts[125];
    testLevelFloor[127].posA = testLevelVerts[123]; testLevelFloor[127].posB = testLevelVerts[125]; testLevelFloor[127].posC = testLevelVerts[126];
    testLevelFloor[128].posA = testLevelVerts[127]; testLevelFloor[128].posB = testLevelVerts[128]; testLevelFloor[128].posC = testLevelVerts[129];
    testLevelFloor[129].posA = testLevelVerts[127]; testLevelFloor[129].posB = testLevelVerts[130]; testLevelFloor[129].posC = testLevelVerts[128];

    for (int i = 0; i < testLevelFloorCount; i++) {
        testLevelFloor[i].type = SURFACE_FLOOR;
        testLevelFloor[i].center = center;
        testLevelFloor[i].normal = norm;
        testLevelFloor[i].center = calc_surface_center(testLevelFloor[i]);
        testLevelFloor[i].normal = calc_surface_norm(testLevelFloor[i]);
    }

    testLevelSlope[0].posA = testLevelVerts[131]; testLevelSlope[0].posB = testLevelVerts[132]; testLevelSlope[0].posC = testLevelVerts[133];
    testLevelSlope[1].posA = testLevelVerts[14]; testLevelSlope[1].posB = testLevelVerts[59]; testLevelSlope[1].posC = testLevelVerts[131];
    testLevelSlope[2].posA = testLevelVerts[134]; testLevelSlope[2].posB = testLevelVerts[57]; testLevelSlope[2].posC = testLevelVerts[12];
    testLevelSlope[3].posA = testLevelVerts[11]; testLevelSlope[3].posB = testLevelVerts[55]; testLevelSlope[3].posC = testLevelVerts[134];
    testLevelSlope[4].posA = testLevelVerts[41]; testLevelSlope[4].posB = testLevelVerts[135]; testLevelSlope[4].posC = testLevelVerts[9];
    testLevelSlope[5].posA = testLevelVerts[40]; testLevelSlope[5].posB = testLevelVerts[64]; testLevelSlope[5].posC = testLevelVerts[135];
    testLevelSlope[6].posA = testLevelVerts[59]; testLevelSlope[6].posB = testLevelVerts[66]; testLevelSlope[6].posC = testLevelVerts[132];
    testLevelSlope[7].posA = testLevelVerts[57]; testLevelSlope[7].posB = testLevelVerts[136]; testLevelSlope[7].posC = testLevelVerts[13];
    testLevelSlope[8].posA = testLevelVerts[135]; testLevelSlope[8].posB = testLevelVerts[65]; testLevelSlope[8].posC = testLevelVerts[10];
    testLevelSlope[9].posA = testLevelVerts[136]; testLevelSlope[9].posB = testLevelVerts[24]; testLevelSlope[9].posC = testLevelVerts[58];
    testLevelSlope[10].posA = testLevelVerts[56]; testLevelSlope[10].posB = testLevelVerts[20]; testLevelSlope[10].posC = testLevelVerts[136];
    testLevelSlope[11].posA = testLevelVerts[75]; testLevelSlope[11].posB = testLevelVerts[79]; testLevelSlope[11].posC = testLevelVerts[137];
    testLevelSlope[12].posA = testLevelVerts[138]; testLevelSlope[12].posB = testLevelVerts[139]; testLevelSlope[12].posC = testLevelVerts[140];
    testLevelSlope[13].posA = testLevelVerts[140]; testLevelSlope[13].posB = testLevelVerts[141]; testLevelSlope[13].posC = testLevelVerts[142];
    testLevelSlope[14].posA = testLevelVerts[137]; testLevelSlope[14].posB = testLevelVerts[143]; testLevelSlope[14].posC = testLevelVerts[138];
    testLevelSlope[15].posA = testLevelVerts[78]; testLevelSlope[15].posB = testLevelVerts[134]; testLevelSlope[15].posC = testLevelVerts[74];
    testLevelSlope[16].posA = testLevelVerts[143]; testLevelSlope[16].posB = testLevelVerts[131]; testLevelSlope[16].posC = testLevelVerts[139];
    testLevelSlope[17].posA = testLevelVerts[139]; testLevelSlope[17].posB = testLevelVerts[133]; testLevelSlope[17].posC = testLevelVerts[141];
    testLevelSlope[18].posA = testLevelVerts[79]; testLevelSlope[18].posB = testLevelVerts[14]; testLevelSlope[18].posC = testLevelVerts[143];
    testLevelSlope[19].posA = testLevelVerts[9]; testLevelSlope[19].posB = testLevelVerts[135]; testLevelSlope[19].posC = testLevelVerts[10];
    testLevelSlope[20].posA = testLevelVerts[131]; testLevelSlope[20].posB = testLevelVerts[59]; testLevelSlope[20].posC = testLevelVerts[132];
    testLevelSlope[21].posA = testLevelVerts[134]; testLevelSlope[21].posB = testLevelVerts[55]; testLevelSlope[21].posC = testLevelVerts[57];
    testLevelSlope[22].posA = testLevelVerts[41]; testLevelSlope[22].posB = testLevelVerts[40]; testLevelSlope[22].posC = testLevelVerts[135];
    testLevelSlope[23].posA = testLevelVerts[13]; testLevelSlope[23].posB = testLevelVerts[136]; testLevelSlope[23].posC = testLevelVerts[58];
    testLevelSlope[24].posA = testLevelVerts[57]; testLevelSlope[24].posB = testLevelVerts[56]; testLevelSlope[24].posC = testLevelVerts[136];
    testLevelSlope[25].posA = testLevelVerts[135]; testLevelSlope[25].posB = testLevelVerts[64]; testLevelSlope[25].posC = testLevelVerts[65];
    testLevelSlope[26].posA = testLevelVerts[136]; testLevelSlope[26].posB = testLevelVerts[20]; testLevelSlope[26].posC = testLevelVerts[24];
    testLevelSlope[27].posA = testLevelVerts[138]; testLevelSlope[27].posB = testLevelVerts[143]; testLevelSlope[27].posC = testLevelVerts[139];
    testLevelSlope[28].posA = testLevelVerts[140]; testLevelSlope[28].posB = testLevelVerts[139]; testLevelSlope[28].posC = testLevelVerts[141];
    testLevelSlope[29].posA = testLevelVerts[137]; testLevelSlope[29].posB = testLevelVerts[79]; testLevelSlope[29].posC = testLevelVerts[143];
    testLevelSlope[30].posA = testLevelVerts[78]; testLevelSlope[30].posB = testLevelVerts[11]; testLevelSlope[30].posC = testLevelVerts[134];
    testLevelSlope[31].posA = testLevelVerts[74]; testLevelSlope[31].posB = testLevelVerts[134]; testLevelSlope[31].posC = testLevelVerts[12];
    testLevelSlope[32].posA = testLevelVerts[143]; testLevelSlope[32].posB = testLevelVerts[14]; testLevelSlope[32].posC = testLevelVerts[131];
    testLevelSlope[33].posA = testLevelVerts[139]; testLevelSlope[33].posB = testLevelVerts[131]; testLevelSlope[33].posC = testLevelVerts[133];
    testLevelSlope[34].posA = testLevelVerts[144]; testLevelSlope[34].posB = testLevelVerts[113]; testLevelSlope[34].posC = testLevelVerts[110];
    testLevelSlope[35].posA = testLevelVerts[144]; testLevelSlope[35].posB = testLevelVerts[145]; testLevelSlope[35].posC = testLevelVerts[113];

    for (int i = 0; i < testLevelSlopeCount; i++) {
        testLevelSlope[i].type = SURFACE_SLOPE;
        testLevelSlope[i].center = center;
        testLevelSlope[i].normal = norm;
        testLevelSlope[i].center = calc_surface_center(testLevelSlope[i]);
        testLevelSlope[i].normal = calc_surface_norm(testLevelSlope[i]);
    }

    testLevelWall[0].posA = testLevelVerts[18]; testLevelWall[0].posB = testLevelVerts[115]; testLevelWall[0].posC = testLevelVerts[46];
    testLevelWall[1].posA = testLevelVerts[44]; testLevelWall[1].posB = testLevelVerts[117]; testLevelWall[1].posC = testLevelVerts[35];
    testLevelWall[2].posA = testLevelVerts[23]; testLevelWall[2].posB = testLevelVerts[84]; testLevelWall[2].posC = testLevelVerts[62];
    testLevelWall[3].posA = testLevelVerts[49]; testLevelWall[3].posB = testLevelVerts[85]; testLevelWall[3].posC = testLevelVerts[22];
    testLevelWall[4].posA = testLevelVerts[38]; testLevelWall[4].posB = testLevelVerts[146]; testLevelWall[4].posC = testLevelVerts[2];
    testLevelWall[5].posA = testLevelVerts[50]; testLevelWall[5].posB = testLevelVerts[147]; testLevelWall[5].posC = testLevelVerts[8];
    testLevelWall[6].posA = testLevelVerts[51]; testLevelWall[6].posB = testLevelVerts[148]; testLevelWall[6].posC = testLevelVerts[44];
    testLevelWall[7].posA = testLevelVerts[8]; testLevelWall[7].posB = testLevelVerts[149]; testLevelWall[7].posC = testLevelVerts[6];
    testLevelWall[8].posA = testLevelVerts[22]; testLevelWall[8].posB = testLevelVerts[82]; testLevelWall[8].posC = testLevelVerts[23];
    testLevelWall[9].posA = testLevelVerts[43]; testLevelWall[9].posB = testLevelVerts[150]; testLevelWall[9].posC = testLevelVerts[50];
    testLevelWall[10].posA = testLevelVerts[63]; testLevelWall[10].posB = testLevelVerts[151]; testLevelWall[10].posC = testLevelVerts[34];
    testLevelWall[11].posA = testLevelVerts[36]; testLevelWall[11].posB = testLevelVerts[116]; testLevelWall[11].posC = testLevelVerts[18];
    testLevelWall[12].posA = testLevelVerts[34]; testLevelWall[12].posB = testLevelVerts[152]; testLevelWall[12].posC = testLevelVerts[43];
    testLevelWall[13].posA = testLevelVerts[62]; testLevelWall[13].posB = testLevelVerts[153]; testLevelWall[13].posC = testLevelVerts[63];
    testLevelWall[14].posA = testLevelVerts[2]; testLevelWall[14].posB = testLevelVerts[154]; testLevelWall[14].posC = testLevelVerts[49];
    testLevelWall[15].posA = testLevelVerts[6]; testLevelWall[15].posB = testLevelVerts[155]; testLevelWall[15].posC = testLevelVerts[38];
    testLevelWall[16].posA = testLevelVerts[153]; testLevelWall[16].posB = testLevelVerts[156]; testLevelWall[16].posC = testLevelVerts[151];
    testLevelWall[17].posA = testLevelVerts[149]; testLevelWall[17].posB = testLevelVerts[157]; testLevelWall[17].posC = testLevelVerts[155];
    testLevelWall[18].posA = testLevelVerts[83]; testLevelWall[18].posB = testLevelVerts[86]; testLevelWall[18].posC = testLevelVerts[84];
    testLevelWall[19].posA = testLevelVerts[84]; testLevelWall[19].posB = testLevelVerts[88]; testLevelWall[19].posC = testLevelVerts[153];
    testLevelWall[20].posA = testLevelVerts[150]; testLevelWall[20].posB = testLevelVerts[158]; testLevelWall[20].posC = testLevelVerts[147];
    testLevelWall[21].posA = testLevelVerts[152]; testLevelWall[21].posB = testLevelVerts[159]; testLevelWall[21].posC = testLevelVerts[150];
    testLevelWall[22].posA = testLevelVerts[155]; testLevelWall[22].posB = testLevelVerts[160]; testLevelWall[22].posC = testLevelVerts[146];
    testLevelWall[23].posA = testLevelVerts[85]; testLevelWall[23].posB = testLevelVerts[89]; testLevelWall[23].posC = testLevelVerts[83];
    testLevelWall[24].posA = testLevelVerts[146]; testLevelWall[24].posB = testLevelVerts[161]; testLevelWall[24].posC = testLevelVerts[154];
    testLevelWall[25].posA = testLevelVerts[154]; testLevelWall[25].posB = testLevelVerts[162]; testLevelWall[25].posC = testLevelVerts[85];
    testLevelWall[26].posA = testLevelVerts[151]; testLevelWall[26].posB = testLevelVerts[163]; testLevelWall[26].posC = testLevelVerts[152];
    testLevelWall[27].posA = testLevelVerts[147]; testLevelWall[27].posB = testLevelVerts[164]; testLevelWall[27].posC = testLevelVerts[149];
    testLevelWall[28].posA = testLevelVerts[89]; testLevelWall[28].posB = testLevelVerts[93]; testLevelWall[28].posC = testLevelVerts[87];
    testLevelWall[29].posA = testLevelVerts[164]; testLevelWall[29].posB = testLevelVerts[165]; testLevelWall[29].posC = testLevelVerts[157];
    testLevelWall[30].posA = testLevelVerts[162]; testLevelWall[30].posB = testLevelVerts[166]; testLevelWall[30].posC = testLevelVerts[89];
    testLevelWall[31].posA = testLevelVerts[88]; testLevelWall[31].posB = testLevelVerts[92]; testLevelWall[31].posC = testLevelVerts[156];
    testLevelWall[32].posA = testLevelVerts[159]; testLevelWall[32].posB = testLevelVerts[167]; testLevelWall[32].posC = testLevelVerts[158];
    testLevelWall[33].posA = testLevelVerts[163]; testLevelWall[33].posB = testLevelVerts[168]; testLevelWall[33].posC = testLevelVerts[159];
    testLevelWall[34].posA = testLevelVerts[87]; testLevelWall[34].posB = testLevelVerts[90]; testLevelWall[34].posC = testLevelVerts[88];
    testLevelWall[35].posA = testLevelVerts[157]; testLevelWall[35].posB = testLevelVerts[169]; testLevelWall[35].posC = testLevelVerts[160];
    testLevelWall[36].posA = testLevelVerts[156]; testLevelWall[36].posB = testLevelVerts[91]; testLevelWall[36].posC = testLevelVerts[163];
    testLevelWall[37].posA = testLevelVerts[160]; testLevelWall[37].posB = testLevelVerts[170]; testLevelWall[37].posC = testLevelVerts[161];
    testLevelWall[38].posA = testLevelVerts[161]; testLevelWall[38].posB = testLevelVerts[171]; testLevelWall[38].posC = testLevelVerts[162];
    testLevelWall[39].posA = testLevelVerts[158]; testLevelWall[39].posB = testLevelVerts[172]; testLevelWall[39].posC = testLevelVerts[164];
    testLevelWall[40].posA = testLevelVerts[91]; testLevelWall[40].posB = testLevelVerts[95]; testLevelWall[40].posC = testLevelVerts[168];
    testLevelWall[41].posA = testLevelVerts[165]; testLevelWall[41].posB = testLevelVerts[173]; testLevelWall[41].posC = testLevelVerts[169];
    testLevelWall[42].posA = testLevelVerts[93]; testLevelWall[42].posB = testLevelVerts[96]; testLevelWall[42].posC = testLevelVerts[91];
    testLevelWall[43].posA = testLevelVerts[169]; testLevelWall[43].posB = testLevelVerts[174]; testLevelWall[43].posC = testLevelVerts[170];
    testLevelWall[44].posA = testLevelVerts[170]; testLevelWall[44].posB = testLevelVerts[175]; testLevelWall[44].posC = testLevelVerts[171];
    testLevelWall[45].posA = testLevelVerts[166]; testLevelWall[45].posB = testLevelVerts[94]; testLevelWall[45].posC = testLevelVerts[93];
    testLevelWall[46].posA = testLevelVerts[167]; testLevelWall[46].posB = testLevelVerts[176]; testLevelWall[46].posC = testLevelVerts[172];
    testLevelWall[47].posA = testLevelVerts[171]; testLevelWall[47].posB = testLevelVerts[177]; testLevelWall[47].posC = testLevelVerts[166];
    testLevelWall[48].posA = testLevelVerts[172]; testLevelWall[48].posB = testLevelVerts[178]; testLevelWall[48].posC = testLevelVerts[165];
    testLevelWall[49].posA = testLevelVerts[168]; testLevelWall[49].posB = testLevelVerts[179]; testLevelWall[49].posC = testLevelVerts[167];
    testLevelWall[50].posA = testLevelVerts[177]; testLevelWall[50].posB = testLevelVerts[180]; testLevelWall[50].posC = testLevelVerts[94];
    testLevelWall[51].posA = testLevelVerts[94]; testLevelWall[51].posB = testLevelVerts[98]; testLevelWall[51].posC = testLevelVerts[97];
    testLevelWall[52].posA = testLevelVerts[173]; testLevelWall[52].posB = testLevelVerts[181]; testLevelWall[52].posC = testLevelVerts[174];
    testLevelWall[53].posA = testLevelVerts[174]; testLevelWall[53].posB = testLevelVerts[182]; testLevelWall[53].posC = testLevelVerts[175];
    testLevelWall[54].posA = testLevelVerts[179]; testLevelWall[54].posB = testLevelVerts[101]; testLevelWall[54].posC = testLevelVerts[176];
    testLevelWall[55].posA = testLevelVerts[97]; testLevelWall[55].posB = testLevelVerts[100]; testLevelWall[55].posC = testLevelVerts[95];
    testLevelWall[56].posA = testLevelVerts[175]; testLevelWall[56].posB = testLevelVerts[183]; testLevelWall[56].posC = testLevelVerts[177];
    testLevelWall[57].posA = testLevelVerts[176]; testLevelWall[57].posB = testLevelVerts[184]; testLevelWall[57].posC = testLevelVerts[178];
    testLevelWall[58].posA = testLevelVerts[95]; testLevelWall[58].posB = testLevelVerts[99]; testLevelWall[58].posC = testLevelVerts[179];
    testLevelWall[59].posA = testLevelVerts[178]; testLevelWall[59].posB = testLevelVerts[185]; testLevelWall[59].posC = testLevelVerts[173];
    testLevelWall[60].posA = testLevelVerts[183]; testLevelWall[60].posB = testLevelVerts[186]; testLevelWall[60].posC = testLevelVerts[180];
    testLevelWall[61].posA = testLevelVerts[185]; testLevelWall[61].posB = testLevelVerts[187]; testLevelWall[61].posC = testLevelVerts[181];
    testLevelWall[62].posA = testLevelVerts[180]; testLevelWall[62].posB = testLevelVerts[104]; testLevelWall[62].posC = testLevelVerts[98];
    testLevelWall[63].posA = testLevelVerts[101]; testLevelWall[63].posB = testLevelVerts[105]; testLevelWall[63].posC = testLevelVerts[184];
    testLevelWall[64].posA = testLevelVerts[181]; testLevelWall[64].posB = testLevelVerts[188]; testLevelWall[64].posC = testLevelVerts[182];
    testLevelWall[65].posA = testLevelVerts[98]; testLevelWall[65].posB = testLevelVerts[103]; testLevelWall[65].posC = testLevelVerts[101];
    testLevelWall[66].posA = testLevelVerts[182]; testLevelWall[66].posB = testLevelVerts[189]; testLevelWall[66].posC = testLevelVerts[183];
    testLevelWall[67].posA = testLevelVerts[184]; testLevelWall[67].posB = testLevelVerts[190]; testLevelWall[67].posC = testLevelVerts[185];
    testLevelWall[68].posA = testLevelVerts[105]; testLevelWall[68].posB = testLevelVerts[109]; testLevelWall[68].posC = testLevelVerts[190];
    testLevelWall[69].posA = testLevelVerts[188]; testLevelWall[69].posB = testLevelVerts[191]; testLevelWall[69].posC = testLevelVerts[189];
    testLevelWall[70].posA = testLevelVerts[190]; testLevelWall[70].posB = testLevelVerts[106]; testLevelWall[70].posC = testLevelVerts[187];
    testLevelWall[71].posA = testLevelVerts[189]; testLevelWall[71].posB = testLevelVerts[192]; testLevelWall[71].posC = testLevelVerts[186];
    testLevelWall[72].posA = testLevelVerts[186]; testLevelWall[72].posB = testLevelVerts[193]; testLevelWall[72].posC = testLevelVerts[104];
    testLevelWall[73].posA = testLevelVerts[187]; testLevelWall[73].posB = testLevelVerts[194]; testLevelWall[73].posC = testLevelVerts[188];
    testLevelWall[74].posA = testLevelVerts[191]; testLevelWall[74].posB = testLevelVerts[144]; testLevelWall[74].posC = testLevelVerts[110];
    testLevelWall[75].posA = testLevelVerts[108]; testLevelWall[75].posB = testLevelVerts[145]; testLevelWall[75].posC = testLevelVerts[106];
    testLevelWall[76].posA = testLevelVerts[191]; testLevelWall[76].posB = testLevelVerts[112]; testLevelWall[76].posC = testLevelVerts[192];
    testLevelWall[77].posA = testLevelVerts[192]; testLevelWall[77].posB = testLevelVerts[111]; testLevelWall[77].posC = testLevelVerts[193];
    testLevelWall[78].posA = testLevelVerts[102]; testLevelWall[78].posB = testLevelVerts[107]; testLevelWall[78].posC = testLevelVerts[105];
    testLevelWall[79].posA = testLevelVerts[104]; testLevelWall[79].posB = testLevelVerts[108]; testLevelWall[79].posC = testLevelVerts[102];
    testLevelWall[80].posA = testLevelVerts[193]; testLevelWall[80].posB = testLevelVerts[113]; testLevelWall[80].posC = testLevelVerts[108];
    testLevelWall[81].posA = testLevelVerts[106]; testLevelWall[81].posB = testLevelVerts[144]; testLevelWall[81].posC = testLevelVerts[194];
    testLevelWall[82].posA = testLevelVerts[115]; testLevelWall[82].posB = testLevelVerts[119]; testLevelWall[82].posC = testLevelVerts[195];
    testLevelWall[83].posA = testLevelVerts[195]; testLevelWall[83].posB = testLevelVerts[121]; testLevelWall[83].posC = testLevelVerts[148];
    testLevelWall[84].posA = testLevelVerts[35]; testLevelWall[84].posB = testLevelVerts[114]; testLevelWall[84].posC = testLevelVerts[36];
    testLevelWall[85].posA = testLevelVerts[46]; testLevelWall[85].posB = testLevelVerts[195]; testLevelWall[85].posC = testLevelVerts[51];
    testLevelWall[86].posA = testLevelVerts[117]; testLevelWall[86].posB = testLevelVerts[120]; testLevelWall[86].posC = testLevelVerts[115];
    testLevelWall[87].posA = testLevelVerts[148]; testLevelWall[87].posB = testLevelVerts[118]; testLevelWall[87].posC = testLevelVerts[117];
    testLevelWall[88].posA = testLevelVerts[18]; testLevelWall[88].posB = testLevelVerts[116]; testLevelWall[88].posC = testLevelVerts[115];
    testLevelWall[89].posA = testLevelVerts[44]; testLevelWall[89].posB = testLevelVerts[148]; testLevelWall[89].posC = testLevelVerts[117];
    testLevelWall[90].posA = testLevelVerts[23]; testLevelWall[90].posB = testLevelVerts[82]; testLevelWall[90].posC = testLevelVerts[84];
    testLevelWall[91].posA = testLevelVerts[49]; testLevelWall[91].posB = testLevelVerts[154]; testLevelWall[91].posC = testLevelVerts[85];
    testLevelWall[92].posA = testLevelVerts[38]; testLevelWall[92].posB = testLevelVerts[155]; testLevelWall[92].posC = testLevelVerts[146];
    testLevelWall[93].posA = testLevelVerts[50]; testLevelWall[93].posB = testLevelVerts[150]; testLevelWall[93].posC = testLevelVerts[147];
    testLevelWall[94].posA = testLevelVerts[51]; testLevelWall[94].posB = testLevelVerts[195]; testLevelWall[94].posC = testLevelVerts[148];
    testLevelWall[95].posA = testLevelVerts[8]; testLevelWall[95].posB = testLevelVerts[147]; testLevelWall[95].posC = testLevelVerts[149];
    testLevelWall[96].posA = testLevelVerts[22]; testLevelWall[96].posB = testLevelVerts[85]; testLevelWall[96].posC = testLevelVerts[82];
    testLevelWall[97].posA = testLevelVerts[43]; testLevelWall[97].posB = testLevelVerts[152]; testLevelWall[97].posC = testLevelVerts[150];
    testLevelWall[98].posA = testLevelVerts[63]; testLevelWall[98].posB = testLevelVerts[153]; testLevelWall[98].posC = testLevelVerts[151];
    testLevelWall[99].posA = testLevelVerts[36]; testLevelWall[99].posB = testLevelVerts[114]; testLevelWall[99].posC = testLevelVerts[116];
    testLevelWall[100].posA = testLevelVerts[34]; testLevelWall[100].posB = testLevelVerts[151]; testLevelWall[100].posC = testLevelVerts[152];
    testLevelWall[101].posA = testLevelVerts[62]; testLevelWall[101].posB = testLevelVerts[84]; testLevelWall[101].posC = testLevelVerts[153];
    testLevelWall[102].posA = testLevelVerts[2]; testLevelWall[102].posB = testLevelVerts[146]; testLevelWall[102].posC = testLevelVerts[154];
    testLevelWall[103].posA = testLevelVerts[6]; testLevelWall[103].posB = testLevelVerts[149]; testLevelWall[103].posC = testLevelVerts[155];
    testLevelWall[104].posA = testLevelVerts[153]; testLevelWall[104].posB = testLevelVerts[88]; testLevelWall[104].posC = testLevelVerts[156];
    testLevelWall[105].posA = testLevelVerts[149]; testLevelWall[105].posB = testLevelVerts[164]; testLevelWall[105].posC = testLevelVerts[157];
    testLevelWall[106].posA = testLevelVerts[83]; testLevelWall[106].posB = testLevelVerts[89]; testLevelWall[106].posC = testLevelVerts[86];
    testLevelWall[107].posA = testLevelVerts[84]; testLevelWall[107].posB = testLevelVerts[86]; testLevelWall[107].posC = testLevelVerts[88];
    testLevelWall[108].posA = testLevelVerts[150]; testLevelWall[108].posB = testLevelVerts[159]; testLevelWall[108].posC = testLevelVerts[158];
    testLevelWall[109].posA = testLevelVerts[152]; testLevelWall[109].posB = testLevelVerts[163]; testLevelWall[109].posC = testLevelVerts[159];
    testLevelWall[110].posA = testLevelVerts[155]; testLevelWall[110].posB = testLevelVerts[157]; testLevelWall[110].posC = testLevelVerts[160];
    testLevelWall[111].posA = testLevelVerts[85]; testLevelWall[111].posB = testLevelVerts[162]; testLevelWall[111].posC = testLevelVerts[89];
    testLevelWall[112].posA = testLevelVerts[146]; testLevelWall[112].posB = testLevelVerts[160]; testLevelWall[112].posC = testLevelVerts[161];
    testLevelWall[113].posA = testLevelVerts[154]; testLevelWall[113].posB = testLevelVerts[161]; testLevelWall[113].posC = testLevelVerts[162];
    testLevelWall[114].posA = testLevelVerts[151]; testLevelWall[114].posB = testLevelVerts[156]; testLevelWall[114].posC = testLevelVerts[163];
    testLevelWall[115].posA = testLevelVerts[147]; testLevelWall[115].posB = testLevelVerts[158]; testLevelWall[115].posC = testLevelVerts[164];
    testLevelWall[116].posA = testLevelVerts[89]; testLevelWall[116].posB = testLevelVerts[166]; testLevelWall[116].posC = testLevelVerts[93];
    testLevelWall[117].posA = testLevelVerts[164]; testLevelWall[117].posB = testLevelVerts[172]; testLevelWall[117].posC = testLevelVerts[165];
    testLevelWall[118].posA = testLevelVerts[162]; testLevelWall[118].posB = testLevelVerts[171]; testLevelWall[118].posC = testLevelVerts[166];
    testLevelWall[119].posA = testLevelVerts[88]; testLevelWall[119].posB = testLevelVerts[90]; testLevelWall[119].posC = testLevelVerts[92];
    testLevelWall[120].posA = testLevelVerts[159]; testLevelWall[120].posB = testLevelVerts[168]; testLevelWall[120].posC = testLevelVerts[167];
    testLevelWall[121].posA = testLevelVerts[163]; testLevelWall[121].posB = testLevelVerts[91]; testLevelWall[121].posC = testLevelVerts[168];
    testLevelWall[122].posA = testLevelVerts[87]; testLevelWall[122].posB = testLevelVerts[93]; testLevelWall[122].posC = testLevelVerts[90];
    testLevelWall[123].posA = testLevelVerts[157]; testLevelWall[123].posB = testLevelVerts[165]; testLevelWall[123].posC = testLevelVerts[169];
    testLevelWall[124].posA = testLevelVerts[156]; testLevelWall[124].posB = testLevelVerts[92]; testLevelWall[124].posC = testLevelVerts[91];
    testLevelWall[125].posA = testLevelVerts[160]; testLevelWall[125].posB = testLevelVerts[169]; testLevelWall[125].posC = testLevelVerts[170];
    testLevelWall[126].posA = testLevelVerts[161]; testLevelWall[126].posB = testLevelVerts[170]; testLevelWall[126].posC = testLevelVerts[171];
    testLevelWall[127].posA = testLevelVerts[158]; testLevelWall[127].posB = testLevelVerts[167]; testLevelWall[127].posC = testLevelVerts[172];
    testLevelWall[128].posA = testLevelVerts[91]; testLevelWall[128].posB = testLevelVerts[96]; testLevelWall[128].posC = testLevelVerts[95];
    testLevelWall[129].posA = testLevelVerts[165]; testLevelWall[129].posB = testLevelVerts[178]; testLevelWall[129].posC = testLevelVerts[173];
    testLevelWall[130].posA = testLevelVerts[93]; testLevelWall[130].posB = testLevelVerts[94]; testLevelWall[130].posC = testLevelVerts[96];
    testLevelWall[131].posA = testLevelVerts[169]; testLevelWall[131].posB = testLevelVerts[173]; testLevelWall[131].posC = testLevelVerts[174];
    testLevelWall[132].posA = testLevelVerts[170]; testLevelWall[132].posB = testLevelVerts[174]; testLevelWall[132].posC = testLevelVerts[175];
    testLevelWall[133].posA = testLevelVerts[166]; testLevelWall[133].posB = testLevelVerts[177]; testLevelWall[133].posC = testLevelVerts[94];
    testLevelWall[134].posA = testLevelVerts[167]; testLevelWall[134].posB = testLevelVerts[179]; testLevelWall[134].posC = testLevelVerts[176];
    testLevelWall[135].posA = testLevelVerts[171]; testLevelWall[135].posB = testLevelVerts[175]; testLevelWall[135].posC = testLevelVerts[177];
    testLevelWall[136].posA = testLevelVerts[172]; testLevelWall[136].posB = testLevelVerts[176]; testLevelWall[136].posC = testLevelVerts[178];
    testLevelWall[137].posA = testLevelVerts[168]; testLevelWall[137].posB = testLevelVerts[95]; testLevelWall[137].posC = testLevelVerts[179];
    testLevelWall[138].posA = testLevelVerts[177]; testLevelWall[138].posB = testLevelVerts[183]; testLevelWall[138].posC = testLevelVerts[180];
    testLevelWall[139].posA = testLevelVerts[94]; testLevelWall[139].posB = testLevelVerts[180]; testLevelWall[139].posC = testLevelVerts[98];
    testLevelWall[140].posA = testLevelVerts[173]; testLevelWall[140].posB = testLevelVerts[185]; testLevelWall[140].posC = testLevelVerts[181];
    testLevelWall[141].posA = testLevelVerts[174]; testLevelWall[141].posB = testLevelVerts[181]; testLevelWall[141].posC = testLevelVerts[182];
    testLevelWall[142].posA = testLevelVerts[179]; testLevelWall[142].posB = testLevelVerts[99]; testLevelWall[142].posC = testLevelVerts[101];
    testLevelWall[143].posA = testLevelVerts[97]; testLevelWall[143].posB = testLevelVerts[98]; testLevelWall[143].posC = testLevelVerts[100];
    testLevelWall[144].posA = testLevelVerts[175]; testLevelWall[144].posB = testLevelVerts[182]; testLevelWall[144].posC = testLevelVerts[183];
    testLevelWall[145].posA = testLevelVerts[176]; testLevelWall[145].posB = testLevelVerts[101]; testLevelWall[145].posC = testLevelVerts[184];
    testLevelWall[146].posA = testLevelVerts[95]; testLevelWall[146].posB = testLevelVerts[100]; testLevelWall[146].posC = testLevelVerts[99];
    testLevelWall[147].posA = testLevelVerts[178]; testLevelWall[147].posB = testLevelVerts[184]; testLevelWall[147].posC = testLevelVerts[185];
    testLevelWall[148].posA = testLevelVerts[183]; testLevelWall[148].posB = testLevelVerts[189]; testLevelWall[148].posC = testLevelVerts[186];
    testLevelWall[149].posA = testLevelVerts[185]; testLevelWall[149].posB = testLevelVerts[190]; testLevelWall[149].posC = testLevelVerts[187];
    testLevelWall[150].posA = testLevelVerts[180]; testLevelWall[150].posB = testLevelVerts[186]; testLevelWall[150].posC = testLevelVerts[104];
    testLevelWall[151].posA = testLevelVerts[101]; testLevelWall[151].posB = testLevelVerts[103]; testLevelWall[151].posC = testLevelVerts[105];
    testLevelWall[152].posA = testLevelVerts[181]; testLevelWall[152].posB = testLevelVerts[187]; testLevelWall[152].posC = testLevelVerts[188];
    testLevelWall[153].posA = testLevelVerts[98]; testLevelWall[153].posB = testLevelVerts[104]; testLevelWall[153].posC = testLevelVerts[103];
    testLevelWall[154].posA = testLevelVerts[182]; testLevelWall[154].posB = testLevelVerts[188]; testLevelWall[154].posC = testLevelVerts[189];
    testLevelWall[155].posA = testLevelVerts[184]; testLevelWall[155].posB = testLevelVerts[105]; testLevelWall[155].posC = testLevelVerts[190];
    testLevelWall[156].posA = testLevelVerts[105]; testLevelWall[156].posB = testLevelVerts[107]; testLevelWall[156].posC = testLevelVerts[109];
    testLevelWall[157].posA = testLevelVerts[188]; testLevelWall[157].posB = testLevelVerts[194]; testLevelWall[157].posC = testLevelVerts[191];
    testLevelWall[158].posA = testLevelVerts[190]; testLevelWall[158].posB = testLevelVerts[109]; testLevelWall[158].posC = testLevelVerts[106];
    testLevelWall[159].posA = testLevelVerts[189]; testLevelWall[159].posB = testLevelVerts[191]; testLevelWall[159].posC = testLevelVerts[192];
    testLevelWall[160].posA = testLevelVerts[186]; testLevelWall[160].posB = testLevelVerts[192]; testLevelWall[160].posC = testLevelVerts[193];
    testLevelWall[161].posA = testLevelVerts[187]; testLevelWall[161].posB = testLevelVerts[106]; testLevelWall[161].posC = testLevelVerts[194];
    testLevelWall[162].posA = testLevelVerts[191]; testLevelWall[162].posB = testLevelVerts[194]; testLevelWall[162].posC = testLevelVerts[144];
    testLevelWall[163].posA = testLevelVerts[108]; testLevelWall[163].posB = testLevelVerts[113]; testLevelWall[163].posC = testLevelVerts[145];
    testLevelWall[164].posA = testLevelVerts[191]; testLevelWall[164].posB = testLevelVerts[110]; testLevelWall[164].posC = testLevelVerts[112];
    testLevelWall[165].posA = testLevelVerts[192]; testLevelWall[165].posB = testLevelVerts[112]; testLevelWall[165].posC = testLevelVerts[111];
    testLevelWall[166].posA = testLevelVerts[102]; testLevelWall[166].posB = testLevelVerts[108]; testLevelWall[166].posC = testLevelVerts[107];
    testLevelWall[167].posA = testLevelVerts[104]; testLevelWall[167].posB = testLevelVerts[193]; testLevelWall[167].posC = testLevelVerts[108];
    testLevelWall[168].posA = testLevelVerts[193]; testLevelWall[168].posB = testLevelVerts[111]; testLevelWall[168].posC = testLevelVerts[113];
    testLevelWall[169].posA = testLevelVerts[106]; testLevelWall[169].posB = testLevelVerts[145]; testLevelWall[169].posC = testLevelVerts[144];
    testLevelWall[170].posA = testLevelVerts[115]; testLevelWall[170].posB = testLevelVerts[120]; testLevelWall[170].posC = testLevelVerts[119];
    testLevelWall[171].posA = testLevelVerts[195]; testLevelWall[171].posB = testLevelVerts[119]; testLevelWall[171].posC = testLevelVerts[121];
    testLevelWall[172].posA = testLevelVerts[35]; testLevelWall[172].posB = testLevelVerts[117]; testLevelWall[172].posC = testLevelVerts[114];
    testLevelWall[173].posA = testLevelVerts[46]; testLevelWall[173].posB = testLevelVerts[115]; testLevelWall[173].posC = testLevelVerts[195];
    testLevelWall[174].posA = testLevelVerts[117]; testLevelWall[174].posB = testLevelVerts[118]; testLevelWall[174].posC = testLevelVerts[120];
    testLevelWall[175].posA = testLevelVerts[148]; testLevelWall[175].posB = testLevelVerts[121]; testLevelWall[175].posC = testLevelVerts[118];
    testLevelWall[176].posA = testLevelVerts[126]; testLevelWall[176].posB = testLevelVerts[127]; testLevelWall[176].posC = testLevelVerts[123];
    testLevelWall[177].posA = testLevelVerts[123]; testLevelWall[177].posB = testLevelVerts[129]; testLevelWall[177].posC = testLevelVerts[124];
    testLevelWall[178].posA = testLevelVerts[125]; testLevelWall[178].posB = testLevelVerts[130]; testLevelWall[178].posC = testLevelVerts[126];
    testLevelWall[179].posA = testLevelVerts[124]; testLevelWall[179].posB = testLevelVerts[128]; testLevelWall[179].posC = testLevelVerts[125];
    testLevelWall[180].posA = testLevelVerts[126]; testLevelWall[180].posB = testLevelVerts[130]; testLevelWall[180].posC = testLevelVerts[127];
    testLevelWall[181].posA = testLevelVerts[123]; testLevelWall[181].posB = testLevelVerts[127]; testLevelWall[181].posC = testLevelVerts[129];
    testLevelWall[182].posA = testLevelVerts[125]; testLevelWall[182].posB = testLevelVerts[128]; testLevelWall[182].posC = testLevelVerts[130];
    testLevelWall[183].posA = testLevelVerts[124]; testLevelWall[183].posB = testLevelVerts[129]; testLevelWall[183].posC = testLevelVerts[128];

    for (int i = 0; i < testLevelWallCount; i++) {
        testLevelWall[i].type = SURFACE_WALL;
        testLevelWall[i].center = center;
        testLevelWall[i].normal = norm;
        testLevelWall[i].center = calc_surface_center(testLevelWall[i]);
        testLevelWall[i].normal = calc_surface_norm(testLevelWall[i]);
    }

    // Combine the surfaces for collision detection
    combine_surfaces(
        testLevelSurfaces, &testLevelSurfacesCount, 
        testLevelWall, testLevelWallCount,
        testLevelSlope, testLevelSlopeCount,
        testLevelFloor, testLevelFloorCount
        
    );

    // Allocate map's matrix and construct
    testLevelMatFP = malloc_uncached(sizeof(T3DMat4FP));

    // Load model
    modelTestLevel = t3d_model_load("rom:/models/test_level.t3dm");

    // Create map's RSPQ block
    rspq_block_begin();
        t3d_matrix_push(testLevelMatFP);
        matCount++;
        rdpq_set_prim_color(WHITE);
        t3d_model_draw(modelTestLevel);
        t3d_matrix_pop(1);
    dplTestLevel = rspq_block_end();
}