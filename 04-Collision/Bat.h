#pragma once
#include "Enemy.h"

#define GHOST_BBOX_WIDTH 40
#define GHOST_BBOX_HEIGHT 60

class CBat : public CEnemy
{
public:
	CBat() :CEnemy()
	{
		animations.clear();
		AddAnimation(1002);
		AddAnimation(800);
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};