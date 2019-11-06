#pragma once
#include "Enemy.h"

#define GHOST_BBOX_WIDTH 40
#define GHOST_BBOX_HEIGHT 60

#define FISHMAN_RUNNING_SPEED_X 0.01f;
#define FISHMAN_RUNNING_SPEED_Y 0.01f;

#define FISHMAN_ANI_JUMPING 0
#define FISHMAN_ANI_WALKING 1
#define FISHMAN_ANI_ATTACK 2

#define FISHMAN_STATE_SIT 100
#define FISHMAN_STATE_RUN 200
#define FISHMAN_STATE_DIE 300

class CFishman : public CEnemy
{
public:
	CFishman(float _x = 3300, float _y = 780, int id = 0) :CEnemy(_x, _y, id)
	{
		animations.clear();
		AddAnimation(1003);
		AddAnimation(800);
		vy = -0.5f;
		ny = -1;
		vx = 0;
		nx = 1;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};