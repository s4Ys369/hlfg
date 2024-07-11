#ifndef ENUMS_H
#define ENUMS_H

#include <libdragon.h>
#include <t3d/t3d.h>

// COLLISIONS
typedef enum {
    SURFACE_FLOOR,
    SURFACE_CEILING,
    SURFACE_WALL,
    SURFACE_SLOPE,
    NUM_SURFACE_TYPES
} SURFACE_TYPE;

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
    PLAYER_SLIDE,
    PLAYER_SLIDE_DOWN,
    NUM_PLAYER_STATES 
} PLAYER_STATE;

typedef enum {
    SEGMENT_RESERVED,
    SEGMENT_PLAYERS,
    SEGMENT_LEVELS,
    SEGMENT_ACTORS_0,
    SEGMENT_ACTORS_1,
    SEGMENT_DEBUG_0,
    SEGMENT_DEBUG_1,
    SEGMENT_RESERVED_SKEL,
    MAX_SEGMENTS
} SEGMENT_ID;

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
    FONT_abaddon,
    FONT_8BIT_0,
    FONT_8BIT_1,
    FONT_8BIT_2,
    FONT_8BIT_3,
    FONT_8BIT_4,
    FONT_8BIT_5,
    FONT_at01,
    FONT_avenuepixel,
    FONT_bitpotion,
    FONT_chunkysans,
    FONT_CyborgSister,
    FONT_divinty,
    FONT_dmsans,
    FONT_droidsans,
    FONT_EnterCommand,
    FONT_FiraMonoBold,
    FONT_fortzilla,
    FONT_Lato,
    FONT_Liver,
    FONT_m3x6,
    FONT_m5x7,
    FONT_m6x11plus,
    FONT_minimalpixel,
    FONT_monogram,
    FONT_Pacifico,
    FONT_poco,
    FONT_RobotoMedium,
    FONT_roundabout,
    FONT_Silver,
    FONT_slab,
    FONT_timesplitter,
    FONT_Unbalanced,
    FONT_xolonium,
    MAX_NUM_FONTS
} FONT_ID;

typedef enum {
    STYLE_0,
    STYLE_1,
    STYLE_2,
    STYLE_3,
    STYLE_DEBUG,
    STYLE_DB_PASS,
    STYLE_DB_FAIL,
    MAX_NUM_STYLES
} FONT_STYLE_ID;

#endif // ENUMS_H