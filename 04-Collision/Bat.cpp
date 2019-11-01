#include"Bat.h"
#include"Scene.h"

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	CScene* scene = CScene::GetInstance();

	if (nx < 0)
	{
		if (x <= scene->GetLeft())
		{
			vx = -vx;
			nx = 1;
		}
	}
	else if (nx > 0)
	{
		if (x >= scene->GetRight() - 32)
		{
			vx = -vx;
			nx = -1;
		}
	}
	if (ny < 0)
	{
		if (y <= scene->GetTop())
		{
			vy = -vy;
			ny = 1;
		}
	}
	else if (ny > 0)
	{
		if (y >= scene->GetBottom() - 32)
		{
			vy = -vy;
			ny = -1;
		}
	}
}
void CBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + GHOST_BBOX_WIDTH;
		bottom = y + GHOST_BBOX_HEIGHT;
	}
	else if (state == TORCH_STATE_ITEM)
	{
		item->GetPosition(x, y);
		item->GetBoundingBox(left, top, right, bottom);
	}
}
