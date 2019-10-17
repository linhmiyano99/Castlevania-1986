#pragma once
#include "GameObject.h"

class CHidenObject : public CGameObject
{
private:
	int _height;
	int _width;
public:
	CHidenObject(int height = 100, int width = 50) :CGameObject()
	{
		_height = height;
		_width = width;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
};