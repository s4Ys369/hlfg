#ifndef UTILS_H
#define UTILS_H

#include <float.h>
#include <libdragon.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"

extern float deltaTime;
extern float jumpTime;
extern float fixedTime;
extern float jumpFixedTime;
extern float fallFixedTime;

extern color_t RED;
extern color_t ORANGE;
extern color_t YELLOW;
extern color_t GREEN;
extern color_t BLUE;
extern color_t INDIGO;
extern color_t VIOLET;
extern color_t BLACK;
extern color_t WHITE;
extern color_t GREY;
extern color_t TRANSPARENT;
extern color_t T_RED;
extern color_t T_ORANGE;
extern color_t T_YELLOW;
extern color_t T_GREEN;
extern color_t T_BLUE;
extern color_t T_INDIGO ;
extern color_t T_VIOLET;
extern color_t T_BLACK;
extern color_t T_WHITE;
extern color_t T_GREY;
extern color_t DARK_RED;
extern color_t DARK_GREEN;

extern uint32_t myrand(void);
#define RANDN(n) ({ \
	__builtin_constant_p((n)) ? \
		(myrand()%(n)) : \
		(uint32_t)(((uint64_t)myrand() * (n)) >> 32); \
})

float get_jump_time();
float random_float(float min, float max);
void shuffle_array(float arr[], int size);
float clamp(float value, float min, float max);
int find_closest(T3DVec3 origin, Actor **target, int numObjects);
void t3d_vert_unpack_normal(uint16_t packed, T3DVec3 *normal);
void block_free_safe(rspq_block_t *block);

#endif // UTILS_H