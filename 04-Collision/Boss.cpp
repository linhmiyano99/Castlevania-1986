#include "Boss.h"
#include "Scene.h"
#include "SmallBall.h"
#include <ctime> 

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
					if (vx == 0)
						vx = 0.15f;
					if (vy == 0)
						vy = 0.1f;
				}
			}
			if (state == BOSS_STATE_FLY)
			{
				if (!isFlying)
				{
					int _type;
					srand((unsigned)time(0));
					_type = rand() % 3;
					if (_type == 2)
						type = 1;
					else
						type = 0;
					float c_x, c_y;
					CGame::GetInstance()->GetCamPos(c_x, c_y);
					
					if (type == 0)
					{
						/*srand((unsigned)time(0));
						_type = rand() % 3;
						if (_type == 0)
						{
							if (x < c_x + 100)
							{
								AutoFly(x + 100, y);
							}
							else
							{
								AutoFly(x - 100, y);
							}
						}
						else if (_type == 1)
						{
							if (x < c_x + 200)
							{
								AutoFly(x + 200, y);
							}
							else
							{
								AutoFly(x - 200, y);
							}
						}
						else  if (_type == 2)
						{
							if (x < c_x + 100)
							{
								AutoFly(x + 400, y);
							}
							else if (x > c_x + 460)
							{
								AutoFly(x - 400, y);
							}
							else
							{
								AutoFly(x - 100, y);
							}
						}*/
					}
					else
					{
						
						if( x  < c_x + 200)
							AutoAttack(x + 50, y);
						else
							AutoAttack(x - 50, y);
						
					}
					isFlying = true;
					if (vy == 0)
						vy = 0.1f;
					if (vx == 0)
						vx = 0.1f;
					
				}
				
				

				if (isFlying) {
					if (type == 0)
					{
						if (step == 0)
						{
							if (abs(x - x1) > 10)
							{
								FlyCurve(x1, y1);
							}
							else
							{
								step = 1;
							}
						}
						else if (step == 1)
						{
							if (abs(x - x2) > 10)
							{
								
								//FlyCurve(x2, y2);
							}
							else
							{
								step = 2;
							}
						}
						else
						{
							step = 0;
						}
					}
					else
					{

						if (step == 0)
						{
							if (abs(x - x1) > 10)
							{
								FlyStraight(x1, y1);
							}
							else
							{
								step = 1;
								vy = -vy;
							}
						}
						else if (step == 1)
						{
							if (abs(x - x2) > 10)
							{
								
								FlyStraight(x2, y2);

							}
							else
							{
								step = 2;
							}
						}
						else
						{
							step = 0;
							isFlying = false;
						}
					}
				}
				
				x += vx * dt;
				y += vy * dt;

				if ((x <= CScene::GetInstance()->GetLeft() + 20 && vx <0) || (vx > 0 && x >= CScene::GetInstance()->GetRight() - 80))
					vx = -vx;
				if ((vy <= 200 && y < 0) || (y >= SCREEN_HEIGHT - 80 && vy > 0))
					vy = -vy;
				
			}
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
//void CBoss::AutoFly(float next_x, float next_y)
//{
//	if (next_x == x)
//	{
//		vx = 0;
//		vy = -0.5f * nx;
//	}
//	else if (next_y == y)
//	{
//		vx = -0.5f * nx;
//		vy = 0;
//	}
//	else
//	{
//		vx = 0.5f * nx;
//		vy = 1.0 * (next_x - y - 20) / (next_y - x - 20) * nx * 0.5f;
//	}
//}

void CBoss::AutoFly(float next_x, float next_y)
{
	x1 = (x + next_x) / 2;
	y1 = y + 200;
	if (y1 > 400)
		y1 = 400;
	x2 = next_x;
	y2 = y + 20;
}
void CBoss::AutoAttack(float next_x, float next_y)
{
	CSimon::GetInstance()->GetPosition(x1, y1);
	x2 = next_x;
	y2 = next_y;
}
void CBoss::FlyStraight(float next_x, float next_y)
{

	if (x < next_x)
	{
		nx = 1;
	}
	else
	{
		nx = -1;
	}
	if (next_x != x && next_y != y)
		SetSpeed(0.12f * nx, 1.0 * (next_y - y) / (next_x - x) * nx * 0.12f);
	
}
void CBoss::FlyCurve(float next_x, float next_y)
{
	if (x < next_x)
	{
		nx = 1;
	}
	else
	{
		nx = -1;
	}

	vy -= 0.001f;
}