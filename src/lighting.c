#include <libdragon.h>
#include <t3d/t3d.h>
#include "lighting.h"

PointLight point_lights[MAX_LIGHTS] = {
    {{{ 150.0f, 20.0f,   -5.0f}},  0.1f, RED},
    {{{-150.0f, 20.0f,   -5.0f}},  0.2f, GREEN},
    {{{   0.0f, 40.0f, -190.0f}},  0.3f, BLUE},
    {{{   0.0f, 20.0f,   30.0f}},  0.05f, ORANGE},
};

void set_point_lights(PointLight *pl, int numPointLights) {
    for(int i = 0 ; i < numPointLights; ++i) {
      t3d_light_set_point(i, &pl[i].color.r, &(T3DVec3){{
        pl[i].pos.v[0],
        pl[i].pos.v[1],
        pl[i].pos.v[2]
      }}, pl[i].strength);
    }
    t3d_light_set_count(numPointLights+2); // TODO: unhardcoded adding the ambient and directional
}
