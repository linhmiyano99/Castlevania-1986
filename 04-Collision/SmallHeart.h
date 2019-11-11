#pragma once
#include "Item.h"

#define SMALLHEART_SPEED_X 0.03f
#define SMALLHEART_SPEED_Y 0.02f

class CSmallHeart :public CItem
{
	float left_limit;
	float right_limit;
public:
	CSmallHeart(float _x, float _y) : CItem(_x, _y)
	{
		animations.clear();
		AddAnimation(703);
		_type = eType::SMALLHEART;
		vx = SMALLHEART_SPEED_X;
		vy = SMALLHEART_SPEED_Y;
		left_limit = x - 20;
		right_limit = x + 20;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

};