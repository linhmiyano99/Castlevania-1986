#pragma once
#include "GameObject.h"

#define BRICK_GRAVITY			0.002f

class CBrickBreak: public CGameObject
{
public:
	CBrickBreak(float x, float y, int id) : CGameObject(x, y)
	{
		AddAnimation(801);
		switch (id)
		{
		case 0:
			vx = 0.07f;
			vy = -0.3f;
			break;
		case 1:
			vx = -0.07f;
			vy = -0.3f;
			break;
		case 2:
			vx = -0.04f;
			vy = -0.1f;
			break;
		case 3:
			vx = 0.04f;
			vy = -0.1f;
			break;
		}
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};