#pragma once
#include "Enemy.h"

#define GHOST_BBOX_WIDTH 40
#define GHOST_BBOX_HEIGHT 60

class CBoss : public CEnemy
{
	static CBoss* __instance;
public:
	static CBoss* GetInstance();

	CBoss(float _x, float _y, int id) :CEnemy(_x, _y, id)
	{
		animations.clear();
		AddAnimation(1004);
		AddAnimation(800);
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};