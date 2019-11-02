#include"Boss.h"
#include"Scene.h"

CBoss* CBoss::__instance = NULL;

CBoss* CBoss::GetInstance()
{
	if (__instance == NULL) __instance = new CBoss(5311, 100, 0);
	return __instance;
}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CScene* scene = CScene::GetInstance();
	if (scene->GetScene() == 4)
	{
		if (dt_die == 0)
		{
			if (state == TORCH_STATE_NOT_EXSIST) {
				dt_die = GetTickCount();
			}
			else
			{
				CGameObject::Update(dt);
				x += dx;
				y += dy;

				if (nx < 0)
				{
					if (x <= 5050)
					{
						vx = -vx;
						nx = 1;
					}
				}
				else if (nx > 0)
				{
					if (x >= scene->GetRight() - 64)
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
					if (y >= scene->GetBottom() - 64)
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
void CBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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
