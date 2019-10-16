#ifndef __MANAGEMENTTEXTURE_H_
#define __MANAGEMENTTEXTURE_H_



#include "Sprites.h"
#include "fstream"
#include "Textures.h"

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define ID_TEX_SIMON			0
#define ID_TEX_MAP				10
#define ID_TEX_GROUND			20
#define ID_TEX_TORCH			30
#define ID_TEX_VAMPIREKILLER	40
#define ID_TEX_ITEM				50
#define ID_TEX_TORCH_FIRE		60
#define ID_TEX_SIMON_TRANS		70


#define SIMON_ANI_IDLE				0
#define SIMON_ANI_WALKING			1
#define SIMON_ANI_SITTING			2
#define SIMON_ANI_JUMPING			3
#define SIMON_ANI_ATTACKING 		4
#define SIMON_ANI_SITTING_ATTACKING	5
#define BRICK_ANI					6
#define TORCH_ANI_FIRE				7
#define VAMPIREKILLER_1				8
#define VAMPIREKILLER_2				9
#define VAMPIREKILLER_3				10


class CManagementTexture
{
public:
	CManagementTexture();
};
#endif // !__MANAGEMENTTEXTURE_H_