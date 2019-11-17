#include "Boss.h"
#include "Scene.h"
#include "SmallBall.h"

CBoss* CBoss::__instance = NULL;

CBoss* CBoss::GetInstance()
{
	if (__instance == NULL) __instance = new CBoss(5311, 100);
	return __instance;
}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BOSS_STATE_SLEEP)
	{
		return;
	}
	if (state == BOSS_STATE_ITEM_NOT_EXSIST)
	{
		return;
	}
	

	if (dt_die == 0)
	{
		if (state == BOSS_STATE_NOT_EXSIST) {
			dt_die = GetTickCount();
			if (item)
				item->SetPosition(x, y);
			else
				state = BOSS_STATE_ITEM_NOT_EXSIST;
		}
		else
		{
			if (GetTickCount() - start_hurt > BOSS_TIME_HURT)
			{
				start_hurt = 0;
			}
			float s_x, s_y;
			CSimon* simon = CSimon::GetInstance();
			simon->GetPosition(s_x, s_y);
			CScene* scene = CScene::GetInstance();

			if (GetTickCount() - start_attack >= BOSS_TIME_ATTACK)
			{
				start_attack = GetTickCount();
				if (x < s_x)
				{
					nx = 1;
				}
				else
				{
					nx = -1;
				}
				state = BOSS_STATE_ATTACK;
				vx = vy = 0;
				CSmallBall* smallball = new CSmallBall(x + 20, y + 20, nx);
				if (s_x == x)
				{
					smallball->SetSpeed(0, -0.3f * nx);
				}
				else if (s_y == y)
				{
					smallball->SetSpeed(-0.3f * nx, 0);

				}
				else
				{
					smallball->SetSpeed(0.25f * nx, 1.0 * (s_y - y - 20) / (s_x - x - 20) * nx * 0.25f);
				}
				CScene::GetInstance()->AddSmallBall(smallball);
				return;
			}
			if (state == BOSS_STATE_ATTACK)
			{
				if (GetTickCount() - start_attack > TIME_ATTACK)
				{
					state = BOSS_STATE_FLY;
					vx = -0.15f;
					vy = 0.05f;
				}
			}
			CGameObject::Update(dt);
			x += dx;
			y += dy;

			if (x <= CScene::GetInstance()->GetLeft() + 20 || x >= CScene::GetInstance()->GetRight() - 100)
				vx = -vx;
			if (y <= 80 || y >= SCREEN_HEIGHT - 80)
				vy = -vy;
		}
	}
	else // đẫ chết
	{
		if (item) {//co item
			if (GetTickCount() - dt_die > 150) // cho 150 mili second
			{
				item->Update(dt, coObjects);
				item->GetPosition(x, y);
				state = BOSS_STATE_ITEM;
			}
		}
		else
		{
			state = BOSS_STATE_ITEM_NOT_EXSIST;
		}
	}

}


void CBoss::Render()
{
	if (state != BOSS_STATE_ITEM_NOT_EXSIST)
	{
		if (state == BOSS_STATE_SLEEP)
		{
			animations[BOSS_ANI_SLEEPING]->Render(x,y);
		}
		else if (state == BOSS_STATE_ATTACK)
		{
			animations[BOSS_ANI_ATTACKING]->Render(x, y, nx, 255);
		}
		else if (state == BOSS_STATE_FLY)
		{
			animations[BOSS_ANI_FLYING]->Render(x, y, nx, 255);
		}
		else if (state == BOSS_STATE_ITEM)
		{
			if (item)
				item->Render();

		}
	}
	else
	{
		if (GetTickCount() - dt_die < 150)
		{
			animations[1]->Render(x, y);

		}
	}
	RenderBoundingBox();
}
void CBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == BOSS_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
	else if (state == BOSS_STATE_FLY || state == BOSS_STATE_ATTACK)
	{
		left = x;
		top = y;
		right = x + BOSS_BBOX_WIDTH;
		bottom = y + BOSS_BBOX_HEIGHT;
	}
	
}
void CBoss::Hurt()
{ 
	if (start_hurt == 0)
	{
		_energy -= 2;
		start_hurt = GetTickCount();
	}
}
void CBoss::AutoFly(float next_x, float next_y)
{
	if (next_x == x)
	{
		vx = 0;
		vy = -0.5f * nx;
	}
	else if (next_y == y)
	{
		vx = -0.5f * nx;
		vy = 0;
	}
	else
	{
		vx = 0.5f * nx;
		vy = 1.0 * (next_x - y - 20) / (next_y - x - 20) * nx * 0.5f;
	}
}