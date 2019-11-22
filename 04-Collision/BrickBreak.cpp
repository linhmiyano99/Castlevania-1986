#include "BrickBreak.h"

void CBrickBreak::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += BRICK_GRAVITY * dt;
	x += dx;
	y += dy;
}

void CBrickBreak::Render()
{
	if(animations.size() > 0)
	animations[0]->Render(x, y);
}

void CBrickBreak::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = top = right = bottom = 0;
}