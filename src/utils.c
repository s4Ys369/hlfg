#include <float.h>
#include <libdragon.h>
#include "../include/config.h"
#include "../include/types.h"
#include "utils.h"

float lastTime;
float deltaTime;
float jumpTime;

color_t RED = (color_t){209, 0, 0, 255};
color_t ORANGE = (color_t){255, 102, 34, 255};
color_t YELLOW = (color_t){255, 218, 33, 255};
color_t GREEN = (color_t){51, 221, 0, 255};
color_t BLUE = (color_t){17, 51, 204, 255};
color_t INDIGO = (color_t){34, 0, 102, 255};
color_t VIOLET = (color_t){51, 0, 68, 255};
color_t BLACK = (color_t){0,0,0,255};
color_t WHITE = (color_t){255, 255, 255, 255};
color_t GREY = (color_t){192, 192, 192, 255};
color_t TRANSPARENT = (color_t){0, 0, 0, 127};

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

// Function to find the closest object
int closestIndex = -1;
int find_closest(T3DVec3 origin, Actor **target, int numObjects) {
  float minDistance = FLT_MAX;
  for (int i = 0; i < numObjects; i++) {
    if(target[i]){
        float dist = t3d_vec3_distance(&origin, &target[i]->pos);
        if (dist < minDistance) {
            minDistance = dist;
            closestIndex = i;
        }
    }
  }
  return closestIndex;
}


void t3d_vert_unpack_normal(uint16_t packed, T3DVec3 *normal) {
    int32_t xInt = (int32_t)((packed >> 10) & 0b11111);
    int32_t yInt = (int32_t)((packed >>  5) & 0b11111);
    int32_t zInt = (int32_t)((packed >>  0) & 0b11111);

    // Adjust for signed values
    if (xInt & 0b10000) xInt -= 0b100000;
    if (yInt & 0b10000) yInt -= 0b100000;
    if (zInt & 0b10000) zInt -= 0b100000;

    normal->v[0] = (float)xInt / 15.5f;
    normal->v[1] = (float)yInt / 15.5f;
    normal->v[2] = (float)zInt / 15.5f;

    // Normalize the vector
    t3d_vec3_norm(normal);
}

void t3d_vec3_scale(T3DVec3 *result, const T3DVec3 *vec, float scalar) {
    result->v[0] = vec->v[0] * scalar;
    result->v[1] = vec->v[1] * scalar;
    result->v[2] = vec->v[2] * scalar;
}
