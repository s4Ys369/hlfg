#ifndef ENUMS_H
#define ENUMS_H

#include <libdragon.h>
#include <t3d/t3d.h>

// COLLISIONS
typedef enum {
    SHAPE_BOX,
    SHAPE_SPHERE
} SHAPE_TYPE;

// CAMERA
typedef enum {
    CAM_RECENTER,
    CAM_FOLLOW,
    CAM_ROTATE,
    CAM_TOP_DOWN
} CAM_MODE;

// PLAYER
typedef enum {
    PLAYERS_0,
    PLAYERS_1,
    PLAYERS_2,
    PLAYERS_3,
    PLAYERS_4
} NUM_PLAYERS;

typedef enum {
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_JUMP_START,
    PLAYER_JUMP,
    PLAYER_ATTACK_START,
    PLAYER_ATTACK,
    PLAYER_FALL,
    PLAYER_LAND,
    NUM_PLAYER_STATES 
} PLAYER_STATE;

// SOUND
typedef enum {
	SFX1,
	SFX2,
	BGM1,
	BGM2,
	BGM3,
	BGM4,
	BGM5,
	BGM6,
	BGM7,
	BGM8
    // add more?
} SOUND_CHANNEL;


// UI
typedef enum {
    FONT_RESERVED,
    FONT_PACIFICO,
    FONT_8BIT_0,
    FONT_8BIT_1,
    FONT_8BIT_2,
    FONT_8BIT_3,
    FONT_8BIT_4,
    FONT_8BIT_5,
    MAX_NUM_FONTS
} FONT_ID;

typedef enum {
    STYLE_0,
    STYLE_1,
    STYLE_2,
    MAX_NUM_STYLES
} FONT_STYLE_ID;

#endif // ENUMS_H