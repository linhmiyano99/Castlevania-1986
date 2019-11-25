#include "Boss.h"
#include "Scene.h"
#include "SmallBall.h"
#include <ctime> 

CBoss* CBoss::__instance = NULL;
CBoss::CBoss(float _x, float _y) :CEnemy(_x, _y, ID_BOSSBALL, eType::BOSS)
{
	animations.clear();
	AddAnimation(1090);
	AddAnimation(1091);
	AddAnimation(1092);
	AddAnimation(800);
	type = 0;
	step = 0;
	_energy = 16;
	start_attack = 0;
	start_hurt = 0;
	vx = vy = 0;
	state = BOSS_STATE_SLEEP;
	dt_die = 0;
	start_fly = 0;
	x1 = x2 = y1 = y2 = 0;
	start_fly;
	start_curve = 0;
}
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

			if (GetTickCount() - start_attack >= BOSS_TIME_ATTACK && start_fly == 0)
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
				if (start_curve > 0)
					start_curve += BOSS_TIME_ATTACK2;
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
				if (GetTickCount() - start_attack > BOSS_TIME_ATTACK2 )
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
				if (x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0)
				{
					goto A;
				}
				if (start_fly > 0)
				{
					if (GetTickCount() - start_fly > BOSS_TIME_CHECK_FLY)
					{
					A:
						start_fly = 0;
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

							start_curve = GetTickCount();

							srand((unsigned)time(0));
							_type = rand() % 2;
							float s_x, s_y;
							if (_type == 0)
							{
								if (x < c_x + 150)
									s_x = x + 150;
								else
									s_x = x - 150;
							}
							else
							{
								if (x < c_x + 50)
									s_x = x + 400;
								else if (x > c_x + 430)
									s_x = x - 400;
								else if (x < c_x + 150)
									s_x = x + 150;
								else
									s_x = x - 150;
							}
							srand((unsigned)time(0));
							_type = rand() % 2;
							if (_type == 0)
							{
								if (y < c_y + 150)
									s_y = y + 50;
								else
									s_y = y - 50;
							}
							else
							{
								if (y > c_y + 400)
									s_y = y - 100;
								else
									s_y = y + 100;
							}
							AutoFly(s_x, y);
						}
						else
						{

							if (x < c_x + 200)
								AutoAttack(x + 50, y);
							else
								AutoAttack(x - 50, y);

						}

					}
					else
					{

						if (x > 5340)
						{
							if (abs(x - 5537) > 2 && abs(y - 210) > 2)
								FlyStraight(5537, 210);
							else
								vx = vy = 0;
						}
						else
						{
							if (abs(x - 5080) > 2 && abs(y - 210) > 2)
								FlyStraight(5080, 210);
							else
								vx = vy = 0;
						}
						x += vx * dt * 0.3f;
						y += vy * dt * 0.3f;

					}
				}


				if (!start_fly) {
					if (type == 0)
					{
						if (start_curve > 0)
						{
							step = 1;
							float t = GetTickCount() - start_curve;
							if (t < 2000)
								// The Green Line
							{
								float xa, xb, ya, yb;
								xa = getPt(x0, x1, t * 0.0005f);
								ya = getPt(y0, y1, t * 0.0005f);
								xb = getPt(x1, x2, t * 0.0005f);
								yb = getPt(y1, y2, t * 0.0005f);

								// The Black Dot
								x = getPt(xa, xb, t * 0.0005f);
								y = getPt(ya, yb, t * 0.0005f);

							}
							else
							{
								start_curve = 0;
								start_fly = GetTickCount();
								step = 0;
							}
						}
					}
					else 
					{

						if (step == 0)
						{
							if (abs(x - x1) > 2 && abs(y - y1) > 2)
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
							if (abs(x - x2) > 2 && abs(y - y2) > 2)
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
							start_fly = GetTickCount();
						}
						if ((x <= CScene::GetInstance()->GetLeft()  && vx < 0) || (vx > 0 && x >= CScene::GetInstance()->GetRight() - 80))
							vx = -vx;
						if ((y <= 80 && vy < 0) || (y >= SCREEN_HEIGHT - 80 && vy > 0))
							vy = -vy;
						x += vx * dt;
						y += vy * dt;
					}
				}
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

void CBoss::AutoFly(float next_x, float next_y)
{
	x0 = x;
	y0 = y;
	x2 = next_x;
	y2 = y;
	CSimon::GetInstance()->GetPosition(x1, y1);

	
}
void CBoss::AutoAttack(float next_x, float next_y)
{
	CSimon::GetInstance()->GetPosition(x1, y1);
	x2 = next_x;
	y2 = next_y + 50;
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
		SetSpeed(0.3f * nx, 1.0 * (next_y - y) / (next_x - x) * nx * 0.3f);
	
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
	
	//vy += 0.001f;
}
float CBoss::getPt(int n1, int n2, float perc)
{
	int diff = n2 - n1;

	return n1 + (diff * perc);
}
