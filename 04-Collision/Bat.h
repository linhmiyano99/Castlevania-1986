#pragma once
#include "Enemy.h"

#define BAT_BBOX_WIDTH 32
#define BAT_BBOX_HEIGHT 32

class CBat : public CEnemy
{
public:
	CBat(float _x = 3500, float _y = 200, int id = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};