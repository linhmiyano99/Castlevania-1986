#pragma once
#include "GameObject.h"

#define BRICK_GRAVITY			0.002f
#define WATTER_WIDTH 10 

class CWaterEffection : public CGameObject
{
public:
	CWaterEffection() :CGameObject()
	{
		AddAnimation(803);
		vy = -0.2f;
		vx = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	void SetPosition(float _x, float _y)
	{
		x = _x; y = _y; 
		vy = -0.2f;
		vx = 0;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};