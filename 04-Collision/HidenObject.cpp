#include "HidenObject.h"

void CHidenObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + _width;
	bottom = y + _height;
}
void CHidenObject::Render()
{
	RenderBoundingBox();
}
void CHidenObject::SetPosition(float _x, float _y)
{
	CGameObject::SetPosition(_x, _y);
	if (state == HIDENOBJECT_TYPE_DOWNSTAIR)
	{
		if (nx > 0)
			_autoX = x - 10;
		else
			_autoX = x - 20;
	}
	else if (state == HIDENOBJECT_TYPE_UPSTAIR)
	{
		if (nx < 0)
			_autoX = x - 30;
		else
			_autoX = x + 40;

	}
	else
		_autoX = x + 40;
}
