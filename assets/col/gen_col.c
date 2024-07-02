T3DVec3 verts[25] =
{
    {{ {{96, 128, -128}} }},
    {{ {{96, 0, -256}} }},
    {{ {{96, 0, -128}} }},
    {{ {{96, 128, 128}} }},
    {{ {{96, 0, 0}} }},
    {{ {{96, 0, 128}} }},
    {{ {{96, 128, 256}} }},
    {{ {{96, 0, 256}} }},
    {{ {{96, 128, 0}} }},
    {{ {{96, 128, -256}} }},
    {{ {{-32, 0, 128}} }},
    {{ {{-160, 128, 0}} }},
    {{ {{-160, 128, 128}} }},
    {{ {{-32, 0, -128}} }},
    {{ {{-160, 128, -256}} }},
    {{ {{-160, 128, -128}} }},
    {{ {{-32, 0, 256}} }},
    {{ {{-160, 128, 256}} }},
    {{ {{-32, 0, 0}} }},
    {{ {{-288, 128, -128}} }},
    {{ {{-288, 219, 0}} }},
    {{ {{-288, 219, 128}} }},
    {{ {{-288, 219, 256}} }},
    {{ {{-32, 0, -256}} }},
    {{ {{-288, 128, -256}} }}
};

int Surface_wallCount = 8;
Surface Surface_wall[8];
int Surface_slopeCount = 13;
Surface Surface_slope[13];
int Surface_floorCount = 11;
Surface Surface_floor[11];
void mesh_init(void){

    Surface_wall[0].posA = verts[0]; Surface_wall[0].posB = verts[1]; Surface_wall[0].posC = verts[2];
    Surface_wall[1].posA = verts[3]; Surface_wall[1].posB = verts[4]; Surface_wall[1].posC = verts[5];
    Surface_wall[2].posA = verts[6]; Surface_wall[2].posB = verts[5]; Surface_wall[2].posC = verts[7];
    Surface_wall[3].posA = verts[8]; Surface_wall[3].posB = verts[2]; Surface_wall[3].posC = verts[4];
    Surface_wall[4].posA = verts[0]; Surface_wall[4].posB = verts[9]; Surface_wall[4].posC = verts[1];
    Surface_wall[5].posA = verts[3]; Surface_wall[5].posB = verts[8]; Surface_wall[5].posC = verts[4];
    Surface_wall[6].posA = verts[6]; Surface_wall[6].posB = verts[3]; Surface_wall[6].posC = verts[5];
    Surface_wall[7].posA = verts[8]; Surface_wall[7].posB = verts[0]; Surface_wall[7].posC = verts[2];

    for (int i = 0; i < Surface_wallCount; i++) {
        Surface_wall[i].type = SURFACE_WALL;
        Surface_wall[i].center = center;
        Surface_wall[i].normal = norm;
        Surface_wall[i].center = calc_surface_center(Surface_wall[i]);
        Surface_wall[i].normal = calc_surface_norm(Surface_wall[i]);
    }

    Surface_slope[0].posA = verts[10]; Surface_slope[0].posB = verts[11]; Surface_slope[0].posC = verts[12];
    Surface_slope[1].posA = verts[13]; Surface_slope[1].posB = verts[14]; Surface_slope[1].posC = verts[15];
    Surface_slope[2].posA = verts[16]; Surface_slope[2].posB = verts[12]; Surface_slope[2].posC = verts[17];
    Surface_slope[3].posA = verts[18]; Surface_slope[3].posB = verts[15]; Surface_slope[3].posC = verts[11];
    Surface_slope[4].posA = verts[11]; Surface_slope[4].posB = verts[19]; Surface_slope[4].posC = verts[20];
    Surface_slope[5].posA = verts[17]; Surface_slope[5].posB = verts[21]; Surface_slope[5].posC = verts[22];
    Surface_slope[6].posA = verts[12]; Surface_slope[6].posB = verts[20]; Surface_slope[6].posC = verts[21];
    Surface_slope[7].posA = verts[10]; Surface_slope[7].posB = verts[18]; Surface_slope[7].posC = verts[11];
    Surface_slope[8].posA = verts[13]; Surface_slope[8].posB = verts[23]; Surface_slope[8].posC = verts[14];
    Surface_slope[9].posA = verts[16]; Surface_slope[9].posB = verts[10]; Surface_slope[9].posC = verts[12];
    Surface_slope[10].posA = verts[18]; Surface_slope[10].posB = verts[13]; Surface_slope[10].posC = verts[15];
    Surface_slope[11].posA = verts[17]; Surface_slope[11].posB = verts[12]; Surface_slope[11].posC = verts[21];
    Surface_slope[12].posA = verts[12]; Surface_slope[12].posB = verts[11]; Surface_slope[12].posC = verts[20];

    for (int i = 0; i < Surface_slopeCount; i++) {
        Surface_slope[i].type = SURFACE_SLOPE;
        Surface_slope[i].center = center;
        Surface_slope[i].normal = norm;
        Surface_slope[i].center = calc_surface_center(Surface_slope[i]);
        Surface_slope[i].normal = calc_surface_norm(Surface_slope[i]);
    }

    Surface_floor[0].posA = verts[4]; Surface_floor[0].posB = verts[13]; Surface_floor[0].posC = verts[18];
    Surface_floor[1].posA = verts[7]; Surface_floor[1].posB = verts[10]; Surface_floor[1].posC = verts[16];
    Surface_floor[2].posA = verts[5]; Surface_floor[2].posB = verts[18]; Surface_floor[2].posC = verts[10];
    Surface_floor[3].posA = verts[2]; Surface_floor[3].posB = verts[23]; Surface_floor[3].posC = verts[13];
    Surface_floor[4].posA = verts[15]; Surface_floor[4].posB = verts[24]; Surface_floor[4].posC = verts[19];
    Surface_floor[5].posA = verts[4]; Surface_floor[5].posB = verts[2]; Surface_floor[5].posC = verts[13];
    Surface_floor[6].posA = verts[7]; Surface_floor[6].posB = verts[5]; Surface_floor[6].posC = verts[10];
    Surface_floor[7].posA = verts[5]; Surface_floor[7].posB = verts[4]; Surface_floor[7].posC = verts[18];
    Surface_floor[8].posA = verts[2]; Surface_floor[8].posB = verts[1]; Surface_floor[8].posC = verts[23];
    Surface_floor[9].posA = verts[11]; Surface_floor[9].posB = verts[15]; Surface_floor[9].posC = verts[19];
    Surface_floor[10].posA = verts[15]; Surface_floor[10].posB = verts[14]; Surface_floor[10].posC = verts[24];

    for (int i = 0; i < Surface_floorCount; i++) {
        Surface_floor[i].type = SURFACE_FLOOR;
        Surface_floor[i].center = center;
        Surface_floor[i].normal = norm;
        Surface_floor[i].center = calc_surface_center(Surface_floor[i]);
        Surface_floor[i].normal = calc_surface_norm(Surface_floor[i]);
    }

}