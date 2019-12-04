﻿#pragma once


#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevania 1986"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 520
#define SCREEN_HEIGHT 460

#define MAX_FRAME_RATE 120

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define ID_TEX 1
#define TIME_ENEMY_DIE 150
#define TIME_BOSS_DIE 500
#define BOSS_POSITION 5340.0f, 95.0f
#define SIMON_POSITION_0 0.0f, 300.0f
#define SIMON_POSITION_1 2800.0f, 20.0f



#define BRICK_ANI					6
#define TORCH_ANI_FIRE				7
#define VAMPIREKILLER_1				8
#define VAMPIREKILLER_2				9
#define VAMPIREKILLER_3				10

#define SCENCE_0_LEFT 0
#define SCENCE_1_LEFT 0
#define SCENCE_2_LEFT 3074
#define SCENCE_3_LEFT 3074
#define SCENCE_4_LEFT 4096
#define SCENCE_5_LEFT 5122

#define SCENCE_0_RIGHT 1546
#define SCENCE_1_RIGHT 3084
#define SCENCE_2_RIGHT 4107
#define SCENCE_3_RIGHT 4107
#define SCENCE_4_RIGHT 5642
#define SCENCE_5_RIGHT 5642

#define SCENCE_0_TOP 40
#define SCENCE_1_TOP 430

#define SCENCE_0_BOTTOM 384
#define SCENCE_1_BOTTOM 768

#define SIMON_Y_UPPER 190

#define SIMON_MAX_ENERGY 16
#define PER_STEP 16
#define TIME_RATE_END_GAME 50

#define CAM_Y_UP 40  
#define CAM_Y_DOWN 430  

#define POSITION_START_BOSS 5356

#define WATTER_Y 700

#define START_DOWN 410
#define DONE_DOWN 460

#define START_X 50.0f

#define SMALLBALL_SPEED 0.3f



#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif


// ID của Sprite, object
enum eType
{
	SIMON = 1,
	SIMON_TRANS = 2,

	// object nền
	GATE = 20,
	BRICK_1 = 21,
	BRICK_2 = 22,
	BRICK_3 = 23,
	BRICK_4 = 24,
	BRICK_5 = 25,


	// object
	TORCH = 31,
	OBJECT_HIDDEN_DOOR = 32,
	STAIR_UP = 33,
	STAIR_DOWN = 34,
	CANDLE = 35,
	OBJECT_HIDDEN_FISHMAN = 36,
	OBJECT_HIDDEN_GHOST_1 = 37,
	OBJECT_HIDDEN_GHOST_STOP_1 = 38,
	OBJECT_HIDDEN_PANTHER_JUMP = 39,
	OBJECT_HIDDEN_BRICK = 40,
	OBJECT_HIDDEN_GHOST_2 = 30,
	OBJECT_HIDDEN_GHOST_UP = 28,
	OBJECT_HIDDEN_GHOST_DOWN = 29,


	// weapon
	VAMPIREKILLER = 41,
	DAGGER = 42,
	AXE = 43,

	// item
	HEART = 51,
	WHIPUPGRADE = 52,
	ITEMDAGGER = 53,
	SMALLHEART = 54,
	CHICKEN = 55,
	MONEY_1 = 56,
	MONEY_2 = 57,
	MONEY_3 = 58,
	MONEY_4 = 59,
	CLOCK = 60,
	ITEMAXE = 61,
	CROSS = 62,
	BOSSBALL = 63,
	ITEMII = 64,


	// other
	FONT = 71,
	BOARD = 72,
	MAP1 = 73,
	MAP2 = 74,



	// Enemy
	GHOST = 141,
	PANTHER = 142,
	BAT = 143,
	FISHMEN = 144,

	//BOSS
	BOSS = 150
};

