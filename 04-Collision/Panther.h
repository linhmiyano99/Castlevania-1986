#pragma once
#include "Enemy.h"

#define PANTHER_BBOX_WIDTH 64
#define PANTHER_BBOX_HEIGHT 32

#define PANTHER_RUNNING_SPEED_X 0.1f;
#define PANTHER_RUNNING_SPEED_Y 0.1f;

#define PANTHER_ANI_SIT 0
#define PANTHER_ANI_RUNNING 1
#define PANTHER_ANI_DIE 2

#define PANTHER_STATE_SIT 100
#define PANTHER_STATE_RUN 200
#define PANTHER_STATE_DIE 300


class CPanther : public CEnemy
{
	float LeftLimit;
public:
	CPanther(float _x = 1419, float _y = 230, int id = 0) :CEnemy(_x, _y, id, eType::PANTHER)
	{
		animations.clear();
		AddAnimation(1001);
		AddAnimation(1002);
		AddAnimation(800);
	}
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetSpeed(float _vx, float _vy) {
		vx = -PANTHER_RUNNING_SPEED_X; vy = PANTHER_RUNNING_SPEED_Y; LeftLimit = x - 200;
	}
//	virtual void SetState(int state);
};