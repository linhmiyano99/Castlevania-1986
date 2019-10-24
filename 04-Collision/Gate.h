#pragma once
#include "GameObject.h"

class CGate : public CGameObject 
{

public:
	CGate() :CGameObject()
	{
		AddAnimation(1100);
	}
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};