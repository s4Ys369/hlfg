#ifndef UTILS_H
#define UTILS_H

#include <libdragon.h>
#include "../include/types.h"

extern float lastTime;
extern float deltaTime;
extern float jumpTime;

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

#endif // UTILS_H