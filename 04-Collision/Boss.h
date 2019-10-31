#pragma once
#include "Enemy.h"

#define GHOST_BBOX_WIDTH 40
#define GHOST_BBOX_HEIGHT 60

class CBoss : public CEnemy
{
public:
	CBoss() :CEnemy()
	{
		animations.clear();
		AddAnimation(1004);
		AddAnimation(800);
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};