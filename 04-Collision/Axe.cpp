#include "Game.h"
#include "Axe.h"
#include "Torch.h"
#include "Boss.h"

CAxe* CAxe::__instance = NULL;

CAxe* CAxe::GetInstance()
{
	if (__instance == NULL) __instance = new CAxe();
	return __instance;
}

void CAxe::SetPosition(float simon_x, float simon_y)
{
	if (nx < 0)
	{
		x = simon_x + 5;
	}
	else {
		x = simon_x - 20;
	}

	y = simon_y;
}
void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (start_attack > 0)
	{
		if (GetTickCount() - start_attack > AXE_TIME_ATTACK)
		{
			state = AXE_STATE_HIDE;
			start_attack = 0;
			vy = -AXE_SPEED_Y;
			isRender = false;
		}
	}
	if (state == AXE_STATE_ATTACK) {
		if (start_attack == 0)
		{
			start_attack = GetTickCount();
			isRender = true;
		}

		x += dt * vx;
		vy += GRAVITY * dt;
		y += vy * dt;
		CollisionWithObject(dt, *coObjects);
		

	}
}

void CAxe::Render()
{
	if (isRender) {
		animations[0]->Render(x, y, nx, 255);
		//RenderBoundingBox();
	}
}

void CAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == AXE_STATE_ATTACK)
	{
		left = x;
		right = x + 40;
		top = y;
		bottom = y + 20;
	}

}
void CAxe::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (state == AXE_STATE_ATTACK)
	{
		RECT rect, rect1;
		float l, t, r, b;
		float l1, t1, r1, b1;

		GetBoundingBox(l, t, r, b);
		rect.left = (int)l;
		rect.top = (int)t;
		rect.right = (int)r;
		rect.bottom = (int)b;

		for (int i = 0; i < listObj.size(); i++)
		{
			if (dynamic_cast<CTorch*>(listObj.at(i)))
			{
				CTorch* torch = dynamic_cast<CTorch*>(listObj.at(i));
				if (torch->GetState() == TORCH_STATE_EXSIST ||
					((torch->GetState() == BOSS_STATE_ATTACK || torch->GetState() == BOSS_STATE_FLY) && torch->GetType() == eType::BOSS))
				{
					
					torch->GetBoundingBox(l1, t1, r1, b1);
					rect1.left = (int)l1;
					rect1.top = (int)t1;
					rect1.right = (int)r1;
					rect1.bottom = (int)b1;
					if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
					{
						if (torch->GetType() == eType::BRICK_1 || torch->GetType() == eType::BRICK_2)
						{
							vx = vy = 0;
							state = AXE_STATE_HIDE;
							continue;
						}
						torch->Hurt();

						if (torch->GetEnergy() <= 0)
						{
							CSimon* simon = CSimon::GetInstance();
							if (torch->GetType() == eType::GHOST)
								simon->SetScore(100);
							else if (torch->GetType() == eType::PANTHER)
								simon->SetScore(300);
							else if (torch->GetType() == eType::BAT)
								simon->SetScore(200);
							else if (torch->GetType() == eType::FISHMEN)
								simon->SetScore(300);

							if (torch->GetEnergy() <= 0)
							{
								if (torch->GetType() == eType::BOSS)
								{
									torch->SetState(BOSS_STATE_NOT_EXSIST);
									simon->SetScore(1000);
								}
								else
								{
									torch->SetState(TORCH_STATE_NOT_EXSIST);
								}
							}
						}
						isRender = false;
						break;
					}
				}
			}
		}
	}
}


