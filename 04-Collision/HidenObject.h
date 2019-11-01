#pragma once
#include "GameObject.h"

#define HIDENOBJECT_TYPE_DOOR		0
#define HIDENOBJECT_TYPE_UPSTAIR	1
#define HIDENOBJECT_TYPE_DOWNSTAIR  2

class CHidenObject : public CGameObject
{
private:
	int _height;
	int _width;
	int _autoX;
	int ny;
public:
	CHidenObject(int state = 0, int trendX = 0,int trendY = 0) :CGameObject()
	{
		_height = 10;
		_width = 50;
		nx = trendX;
		ny = trendY;
		this->state = state;
	}
	void SetPosition(float x, float y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	int getNx() { return nx; }
	int getNy() { return ny; }
	int GetAutoX() { return _autoX; }
};