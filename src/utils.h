#ifndef UTILS_H
#define UTILS_H

#include <float.h>
#include <libdragon.h>
#include "../include/config.h"
#include "../include/types.h"

extern float lastTime;
extern float deltaTime;
extern float jumpTime;

extern color_t RED;
extern color_t ORANGE;
extern color_t YELLOW;
extern color_t GREEN;
extern color_t BLUE;
extern color_t INDIGO;
extern color_t VIOLET;
extern color_t BLACK;
extern color_t WHITE;
extern color_t TRANSPARENT;

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

#endif // UTILS_H