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
	if (scene->GetScene() == 5)
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
	
	if (x <= scene->GetLeft() || x >= scene->GetRight())
		vx = -vx;
	if (y <= 80 || y >= SCREEN_HEIGHT - 80)
		vy = -vy;
}
void CBoss::Render()
{
	if (state == TORCH_STATE_EXSIST)
	{
		if (vx == 0)
		{
			animations[ENEMY_ANI_WALKING]->ResetFrame();
			animations[ENEMY_ANI_WALKING]->Render(x,y);
		}
		else if (vx < 0)
			animations[ENEMY_ANI_WALKING]->Render(x, y);
		else
			animations[ENEMY_ANI_WALKING]->Render(x, y, vx, 255);
	}
	else if (state == TORCH_STATE_ITEM)
	{
		if (item != NULL)
			item->Render();

	}
	else
	{
		if (GetTickCount() - dt_die < 150)
		{
			animations[1]->Render(x, y);

		}
	}
	//RenderBoundingBox();
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
