#pragma once
#include"GameObject.h"
#include"Torch.h"
#include "Brick.h"

#define ENEMY_WALKING_SPEED 0.05f;

#define ENEMY_BBOX_WIDTH 40
#define ENEMY_BBOX_HEIGHT 60

#define ENEMY_STATE_WALKING 100
#define ENEMY_STATE_DIE 200

#define ENEMY_ANI_WALKING 0
#define ENEMY_ANI_DIE 1

#define SIMON_GRAVITY			0.002f
#define TIME_APPEAR     1000

class CEnemy : public CTorch
{
protected:
	int ny;
	float start_x, start_y;

public:
	CEnemy(float _x, float _y, int id = 0, int type = 0) : CTorch(_x, _y, id, type)
	{
		start_x = _x;
		start_y = _y;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	
};