#pragma once
#include "GameObject.h"

#define HIDENOBJECT_TYPE_DOOR			0
#define HIDENOBJECT_TYPE_UPSTAIR		1
#define HIDENOBJECT_TYPE_DOWNSTAIR		2
#define HIDENOBJECT_TYPE_FISHMAN		3
#define HIDENOBJECT_TYPE_GHOST_1		4
#define HIDENOBJECT_TYPE_GHOST_STOP_1   5
#define HIDENOBJECT_TYPE_GHOST_2	    6
#define HIDENOBJECT_TYPE_PANTHER_JUMP   7
#define HIDENOBJECT_TYPE_BRICK          8


class CHidenObject : public CGameObject
{
private:
	int _height;
	int _width;
	int _autoX;
	int ny;
public:
	CHidenObject(float _x = 0, float _y = 0,int state = 0, int trendX = 0,int trendY = 0) :CGameObject(_x, _y)
	{
		if (trendX > 1)
		{
			_height = trendY;
			_width = trendX;
			nx = ny = 1;
		}
		else {
			_height = 10;
			_width = 50;
			nx = trendX;
			ny = trendY;
		}
		this->state = state;
		switch (state)
		{
		case HIDENOBJECT_TYPE_DOWNSTAIR:
			if (nx > 0)
				_autoX = x - 10;
			else
				_autoX = x + 20;
			break;
		case HIDENOBJECT_TYPE_UPSTAIR:
			if (nx < 0)
				_autoX = x - 30;
			else
				_autoX = x + 40;
			break;
		case HIDENOBJECT_TYPE_DOOR:
			_autoX = x + 40;
			break;
		default:
			break;
		}

	}
	void SetPosition(float x, float y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	int getNx() { return nx; }
	int getNy() { return ny; }
	int GetAutoX() { return _autoX; }
};