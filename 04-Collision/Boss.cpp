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
				if(item)
				item->SetPosition(x, y);
			}
			else
			{
				
				if (CScene::GetInstance()->GetScene() == 5)
					vx = 0.15f;
				CGameObject::Update(dt);
				x += dx;
				y += dy;
				if (x <= scene->GetLeft() || x >= scene->GetRight())
					vx = -vx;
				if (y <= 80 || y >= SCREEN_HEIGHT - 80)
					vy = -vy;
			}
		}
		else
		{
			if (item) {//co item
				if (GetTickCount() - dt_die > 150) // cho 150 mili second
				{
					item->Update(dt, coObjects);
					item->GetPosition(x, y);
					state = TORCH_STATE_ITEM;
				}
			}
			else
				state = ITEM_STATE_NOT_EXSIST;
		}
	}
	if (x <= scene->GetLeft() + 20 || x >= scene->GetRight() - 100)
		vx = -vx;
	if (y <= 40 || y >= SCREEN_HEIGHT - 100)
		vy = -vy;

}
void CBoss::Render()
{
	if (state == TORCH_STATE_EXSIST)
	{
		if (vx == 0)
		{
			animations[BOSS_ANI_SLEEPING]->Render(x,y);
		}
		else if (vx != 0)
		{
			animations[BOSS_ANI_FLYING]->Render(x, y, nx, 255);
		}
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
		item->GetBoundingBox(left, top, right, bottom);
	}
}
