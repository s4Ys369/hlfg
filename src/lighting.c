#include <libdragon.h>
#include <t3d/t3d.h>
#include "lighting.h"

PointLight point_lights[MAX_LIGHTS] = {
    {{{  100.0f, 20.0f, 100.0f}},  1.0f, false, RED    },
    {{{  200.0f, 20.0f, 100.0f}},  2.0f, false, GREEN  },
    {{{ -100.0f, 40.0f, 100.0f}},  3.0f, false, BLUE   },
    {{{ -200.0f, 20.0f, 100.0f}},  0.5f, false, ORANGE },
};

void set_point_lights(PointLight *pl, int numPointLights) {
  for(int i = 0 ; i < numPointLights; ++i) {
    t3d_light_set_point(i, &pl[i].color.r, &(T3DVec3){{
      pl[i].pos.v[0],
      pl[i].pos.v[1],
      pl[i].pos.v[2]
    }}, pl[i].size, pl[i].ignoreNormals);
  }
}
