#pragma once
#include "GameObject.h"
#define GATE_STATE_CLOSE 0
#define GATE_STATE_OPEN  1

#define GATE_ANI_CLOSING   0
#define GATE_ANI_OPENNING  1


class CGate : public CGameObject 
{

public:
	CGate(float _x, float _y) :CGameObject(_x, _y)
	{
		state = 0;
		AddAnimation(1100);
		AddAnimation(1101);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};