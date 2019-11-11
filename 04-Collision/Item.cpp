#include "Item.h"
#include "Brick.h"



void CItem::Render()
{
	if (state == ITEM_STATE_EXSIST)
	{
		if(animations.size() > 0)
			animations[0]->Render(x, y);
	}
	//RenderBoundingBox();
}




void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
	vy = SIMON_GRAVITY * dt;

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
