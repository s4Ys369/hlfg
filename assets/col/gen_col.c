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
       {{-288, 128, -256}}
};

int WallCount = 8;
Surface Wall[8];
int SlopeCount = 13;
Surface Slope[13];
int FloorCount = 11;
Surface Floor[11];

void col_init(void){

    Wall[0].posA = verts[0]; Wall[0].posB = verts[1]; Wall[0].posC = verts[2];
    Wall[1].posA = verts[3]; Wall[1].posB = verts[4]; Wall[1].posC = verts[5];
    Wall[2].posA = verts[6]; Wall[2].posB = verts[5]; Wall[2].posC = verts[7];
    Wall[3].posA = verts[8]; Wall[3].posB = verts[2]; Wall[3].posC = verts[4];
    Wall[4].posA = verts[0]; Wall[4].posB = verts[9]; Wall[4].posC = verts[1];
    Wall[5].posA = verts[3]; Wall[5].posB = verts[8]; Wall[5].posC = verts[4];
    Wall[6].posA = verts[6]; Wall[6].posB = verts[3]; Wall[6].posC = verts[5];
    Wall[7].posA = verts[8]; Wall[7].posB = verts[0]; Wall[7].posC = verts[2];

    for (int i = 0; i < WallCount; i++) {
        Wall[i].type = SURFACE_WALL;
        Wall[i].center = center;
        Wall[i].normal = norm;
        Wall[i].center = calc_surface_center(Wall[i]);
        Wall[i].normal = calc_surface_norm(Wall[i]);
    }

    Slope[0].posA = verts[10]; Slope[0].posB = verts[11]; Slope[0].posC = verts[12];
    Slope[1].posA = verts[13]; Slope[1].posB = verts[14]; Slope[1].posC = verts[15];
    Slope[2].posA = verts[16]; Slope[2].posB = verts[12]; Slope[2].posC = verts[17];
    Slope[3].posA = verts[18]; Slope[3].posB = verts[15]; Slope[3].posC = verts[11];
    Slope[4].posA = verts[11]; Slope[4].posB = verts[19]; Slope[4].posC = verts[20];
    Slope[5].posA = verts[17]; Slope[5].posB = verts[21]; Slope[5].posC = verts[22];
    Slope[6].posA = verts[12]; Slope[6].posB = verts[20]; Slope[6].posC = verts[21];
    Slope[7].posA = verts[10]; Slope[7].posB = verts[18]; Slope[7].posC = verts[11];
    Slope[8].posA = verts[13]; Slope[8].posB = verts[23]; Slope[8].posC = verts[14];
    Slope[9].posA = verts[16]; Slope[9].posB = verts[10]; Slope[9].posC = verts[12];
    Slope[10].posA = verts[18]; Slope[10].posB = verts[13]; Slope[10].posC = verts[15];
    Slope[11].posA = verts[17]; Slope[11].posB = verts[12]; Slope[11].posC = verts[21];
    Slope[12].posA = verts[12]; Slope[12].posB = verts[11]; Slope[12].posC = verts[20];

    for (int i = 0; i < SlopeCount; i++) {
        Slope[i].type = SURFACE_SLOPE;
        Slope[i].center = center;
        Slope[i].normal = norm;
        Slope[i].center = calc_surface_center(Slope[i]);
        Slope[i].normal = calc_surface_norm(Slope[i]);
    }

    Floor[0].posA = verts[4]; Floor[0].posB = verts[13]; Floor[0].posC = verts[18];
    Floor[1].posA = verts[7]; Floor[1].posB = verts[10]; Floor[1].posC = verts[16];
    Floor[2].posA = verts[5]; Floor[2].posB = verts[18]; Floor[2].posC = verts[10];
    Floor[3].posA = verts[2]; Floor[3].posB = verts[23]; Floor[3].posC = verts[13];
    Floor[4].posA = verts[15]; Floor[4].posB = verts[24]; Floor[4].posC = verts[19];
    Floor[5].posA = verts[4]; Floor[5].posB = verts[2]; Floor[5].posC = verts[13];
    Floor[6].posA = verts[7]; Floor[6].posB = verts[5]; Floor[6].posC = verts[10];
    Floor[7].posA = verts[5]; Floor[7].posB = verts[4]; Floor[7].posC = verts[18];
    Floor[8].posA = verts[2]; Floor[8].posB = verts[1]; Floor[8].posC = verts[23];
    Floor[9].posA = verts[11]; Floor[9].posB = verts[15]; Floor[9].posC = verts[19];
    Floor[10].posA = verts[15]; Floor[10].posB = verts[14]; Floor[10].posC = verts[24];

    for (int i = 0; i < FloorCount; i++) {
        Floor[i].type = SURFACE_FLOOR;
        Floor[i].center = center;
        Floor[i].normal = norm;
        Floor[i].center = calc_surface_center(Floor[i]);
        Floor[i].normal = calc_surface_norm(Floor[i]);
    }

}