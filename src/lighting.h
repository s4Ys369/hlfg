#ifndef LIGHTING_H
#define LIGHTING_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"


#define MAX_LIGHTS 4
#define RED (color_t){209, 0, 0, 255}
#define GREEN (color_t){51, 221, 0, 255}
#define BLUE (color_t){17, 51, 204, 255}
#define ORANGE (color_t){255, 102, 34, 255}
extern PointLight point_lights[MAX_LIGHTS];
void set_point_lights(PointLight *pl, int numPointLights);

#endif // LIGHTING_H