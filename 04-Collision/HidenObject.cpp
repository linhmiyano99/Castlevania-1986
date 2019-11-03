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
	
}
