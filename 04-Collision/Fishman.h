#pragma once
#include "Enemy.h"

#define GHOST_BBOX_WIDTH 40
#define GHOST_BBOX_HEIGHT 60

class CFishman : public CEnemy
{
public:
	CFishman(float _x, float _y, int id) :CEnemy(_x, _y, id)
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
};