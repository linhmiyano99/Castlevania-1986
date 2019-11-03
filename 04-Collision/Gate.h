#pragma once
#include "GameObject.h"
#define GATE_STATE_CLOSE 0
#define GATE_STATE_OPEN  1


class CGate : public CGameObject 
{

public:
	CGate(float _x, float _y) :CGameObject(_x, _y)
	{
		state = 0;
		AddAnimation(1100);
	}
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};