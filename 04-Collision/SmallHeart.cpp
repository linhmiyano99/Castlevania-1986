#include "SmallHeart.h"
#include "Brick.h"

void CSmallHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + 16;
		top = y;
		bottom = y + 16;
	}
}
void CSmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!time_exsist)
	{
		time_exsist = GetTickCount();
	}
	else
	{
		if (GetTickCount() - time_exsist >= TIME_ITEM_EXSIST)
			state = ITEM_STATE_NOT_EXSIST;
	}
	CGameObject::Update(dt);

	// Simple fall down

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
		vx = vy = 0;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (x <= left_limit || x >= right_limit)
	{
		vx = -vx;
	}
}
