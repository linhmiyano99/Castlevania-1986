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
	int ny;
public:
	CHidenObject(int state = 0, int trendX = 0,int trendY = 0, int height = 50, int width = 20) :CGameObject()
	{
		_height = height;
		_width = width;
		nx = trendX;
		ny = trendY;
		this->state = state;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	int getNx() { return nx; }
	int getNy() { return ny; }

};