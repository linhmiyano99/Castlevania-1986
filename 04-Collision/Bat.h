#pragma once
#include "Enemy.h"

#define GHOST_BBOX_WIDTH 40
#define GHOST_BBOX_HEIGHT 60

class CBat : public CEnemy
{
public:
	CBat(float _x = 3500, float _y = 200, int id = 0) :CEnemy(_x,_y, id)
	{
		animations.clear();
		AddAnimation(1003;
		AddAnimation(800);
		vx = -0.1f;
		vy = 0.1f;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};