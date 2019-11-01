#include"Bat.h"
#include"Scene.h"

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CScene* scene = CScene::GetInstance();

	if (dt_die == 0)
	{
		if (state == TORCH_STATE_NOT_EXSIST) {
			dt_die = GetTickCount();
		}
		else
		{
			if (scene->GetScene() == 2)
			{
				CGameObject::Update(dt);
				x += dx;
				y += dy;

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
		}
	}
	else
	{
		if (item != NULL) {//co item
			if (GetTickCount() - dt_die > 150) // cho 150 mili second
			{

				item->Update(dt, coObjects);
				state = TORCH_STATE_ITEM;
			}
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
