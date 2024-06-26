#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include "../include/config.h"
#include "../include/types.h"
#include "utils.h"

float lastTime;
float deltaTime;
float jumpTime;

// Fair and fast random generation (using xorshift32, with explicit seed)
static uint32_t rand_state = SEED;
uint32_t myrand(void) {
	uint32_t x = rand_state;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 5;
	return rand_state = x;
}

// RANDN(n): generate a random number from 0 to n-1
#define RANDN(n) ({ \
	__builtin_constant_p((n)) ? \
		(myrand()%(n)) : \
		(uint32_t)(((uint64_t)myrand() * (n)) >> 32); \
})

float get_jump_time(){
    deltaTime = display_get_delta_time();
    jumpTime = deltaTime * 3.5f;
    return jumpTime;
}

float random_float(float min, float max) {
    return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

// Function to shuffle array using Fisher-Yates algorithm
void shuffle_array(float arr[], int size) {
    for (int i = size - 1; i > 0; --i) {
        int j = myrand() % (i + 1);
        float temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

float clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

float get_t3d_distance(T3DVec3 a, T3DVec3 b) {
  return sqrtf(
    (a.v[0] - b.v[0]) * (a.v[0] - b.v[0]) +
    (a.v[1] - b.v[1]) * (a.v[1] - b.v[1]) +
    (a.v[2] - b.v[2]) * (a.v[2] - b.v[2])
  );
}
