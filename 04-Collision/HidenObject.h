#pragma once
#include "GameObject.h"
#include "Define.h"

//#define HIDENOBJECT_TYPE_DOOR			0
//#define HIDENOBJECT_TYPE_UPSTAIR		1
//#define HIDENOBJECT_TYPE_DOWNSTAIR		2
//#define HIDENOBJECT_TYPE_FISHMAN		13
//#define HIDENOBJECT_TYPE_GHOST_1		4
//#define HIDENOBJECT_TYPE_GHOST_STOP_1   5
//#define HIDENOBJECT_TYPE_GHOST_2	    6
//#define HIDENOBJECT_TYPE_PANTHER_JUMP   7
//#define HIDENOBJECT_TYPE_BRICK          8
//#define HIDENOBJECT_TYPE_GHOST_UP	    9
//#define HIDENOBJECT_TYPE_GHOST_DOWN	    10
//#define HIDENOBJECT_TYPE_GATE_OPEN	    11

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

		_height = 10;
		_width = 15;
		nx = trendX;
		ny = trendY;
		this->state = state;
		switch (state)
		{
		case eType::STAIR_DOWN:
			if (nx > 0)
				_autoX = x - 5;
			else
				_autoX = x - 10;
			break;
		case eType::STAIR_UP:
			if (nx < 0)
				_autoX = x - 30;
			else
				_autoX = x + 10;
			break;
		case eType::OBJECT_HIDDEN_DOOR:
			_autoX = x + 40;
			break;
		case eType::OBJECT_HIDDEN_PANTHER_JUMP:
			_height = 150;
			_width = 15;
			break;

		default:
			break;
		}

	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	int getNx() { return nx; }
	int getNy() { return ny; }
	int GetAutoX() { return _autoX; }
};