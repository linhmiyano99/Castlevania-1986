#include "Game.h"
#include "Torch.h"
#include "Boss.h"
#include "Boongmerang.h"

CBoongmerang* CBoongmerang::__instance = NULL;
CBoongmerang::CBoongmerang() :CWeapon()
{
	AddAnimation(605);
	isRender = false;
	state = BOONGMERANG_STATE_HIDE;
	start_attack = 0;
	turn = 0;
}
CBoongmerang* CBoongmerang::GetInstance()
{
	if (__instance == NULL) __instance = new CBoongmerang();
	return __instance;
}

void CBoongmerang::SetPosition(float simon_x, float simon_y)
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
void CBoongmerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (start_attack > 0)
	{
		if (GetTickCount() - start_attack > BOONGMERANG_TIME_ATTACK)
		{
			state = BOONGMERANG_STATE_HIDE;
			start_attack = 0;
			isRender = false;
			float c_y;
			CGame::GetInstance()->GetCamPos(leftLimit, c_y);
			rightLimit = leftLimit + SCREEN_WIDTH;
			vx = nx * BOONGMERANG_SPEED;
			turn = 0;
		}
	}
	if (state == BOONGMERANG_STATE_ATTACK) {
		if (start_attack == 0)
		{
			start_attack = GetTickCount();
			isRender = true;
		}

		x += dt * vx;
		if ((x < leftLimit && vx < 0) || (x > rightLimit&& vx > 0))
		{
			vx = -vx;
			nx = -nx;
			turn++;
		}
		if(turn < 2)
			CollisionWithObject(dt, *coObjects);


	}
}

void CBoongmerang::Render()
{
	if (state == BOONGMERANG_STATE_ATTACK && turn < 2) {
		animations[0]->Render(x, y, nx, 255);
		//RenderBoundingBox();
	}
}

void CBoongmerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BOONGMERANG_STATE_ATTACK)
	{
		left = x;
		right = x + 40;
		top = y;
		bottom = y + 20;
	}

}
void CBoongmerang::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (state == BOONGMERANG_STATE_ATTACK)
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
						Sound::GetInstance()->Play(eSound::soundHurting);

						if (torch->GetType() == eType::BRICK_1 || torch->GetType() == eType::BRICK_2)
						{
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


void CBoongmerang::SetState(int _state) {
	CGameObject::SetState(_state);
	if (state == BOONGMERANG_STATE_ATTACK)
	{
		vx = nx * BOONGMERANG_SPEED;
		if (!start_attack)
			start_attack = GetTickCount();
		float c_y;
		CGame::GetInstance()->GetCamPos(leftLimit, c_y);
		rightLimit = leftLimit + SCREEN_WIDTH;
	}
}