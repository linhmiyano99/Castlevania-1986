﻿#include "Game.h"
#include "Axe.h"
#include "Torch.h"
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
	if (state == AXE_STATE_ATTACK) {
		if (start_attack == 0)
			start_attack = GetTickCount();
		if (nx > 0)
			x += dt * vx;
		else
			x -= dt * vx;
		CollisionWithObject(dt, *coObjects);
		if (GetTickCount() - start_attack > 2000)
		{
			state = AXE_STATE_HIDE;
			start_attack = 0;
		}

	}
}

void CAxe::Render()
{
	if (state == AXE_STATE_ATTACK) {
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
				if (listObj.at(i)->GetState() == TORCH_STATE_EXSIST)
				{
					listObj.at(i)->GetBoundingBox(l1, t1, r1, b1);
					rect1.left = (int)l1;
					rect1.top = (int)t1;
					rect1.right = (int)r1;
					rect1.bottom = (int)b1;
					if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
					{
						listObj.at(i)->SetState(TORCH_STATE_NOT_EXSIST);
						this->state = AXE_STATE_HIDE;
						break;
					}
				}
			}
		}
	}
}

