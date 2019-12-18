#include "Money.h"
#include "Brick.h"

bool CItemMoney::isStartShowHiden = false;

void CItemMoney::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (start_effection == 0 && state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEMMONEY_WIDTH;
		top = y;
		bottom = y + ITEMMONEY_HEIGHT;
	}
}



void CItemMoney::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (_type != eType::MONEY_5)
	{
		if (state == ITEM_STATE_EXSIST)
		{
			if (start_effection > 0)
			{
				if (GetTickCount() - start_effection > 1000)
				{
					start_effection = 0;
					state = ITEM_STATE_NOT_EXSIST;
				}
				return;
			}
			if (!time_exsist)
			{
				time_exsist = GetTickCount();
			}
			else
			{
				if (GetTickCount() - time_exsist >= TIME_ITEM_EXSIST)
				{
					state = ITEM_STATE_NOT_EXSIST;
					time_exsist = 0;
				}
			}
			CGameObject::Update(dt);

			// Simple fall down
			vy += ITEM_GRAVITY * dt;

			vector<LPGAMEOBJECT> listBrick;
			for (int i = 0; i < coObjects->size(); i++)
			{

				if (dynamic_cast<CBrick*>(coObjects->at(i)))
				{
					CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
					listBrick.push_back(brick);
				}

			}

			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();

			// turn off collision when die 
			if (state != SIMON_STATE_DIE)
				CalcPotentialCollisions(&listBrick, coEvents);

			// No collision occured, proceed normally
			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else
			{
				float min_tx, min_ty, nx = 0, ny;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

				//// block 
				//x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
			// clean up collision events
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
	}
	else
	{
		if (y >= destination_y && CItemMoney::IsStart())
		{
			y -= 0.1f * dt;
		}
	}
}


void CItemMoney::Render()
{
	if (_type != eType::MONEY_5) {
		if (start_effection > 0)
		{
			animations[1]->Render(x - 20, y - 20);
			return;
		}
		if (state == ITEM_STATE_EXSIST)
		{
			if (animations.size() > 0)
				animations[0]->Render(x, y);
		}
	}
	else
	{
		if (CItemMoney::IsStart())
		{
			if (start_effection > 0)
			{
				//animations[1]->Render(x - 20, y - 20);
				return;
			}
			if (state == ITEM_STATE_EXSIST)
			{
				if (animations.size() > 0)
					animations[0]->Render(x, y);
			}
		}
	}
	//RenderBoundingBox();

}
