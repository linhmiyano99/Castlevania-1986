#include "Enemy.h"
#include "Brick.h"

void CEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ENEMY_BBOX_WIDTH;
	bottom = y + ENEMY_BBOX_HEIGHT;
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (dt_die == 0)
	{
		if (state == TORCH_STATE_NOT_EXSIST) {
			dt_die = GetTickCount();
		}
		else
		{
			CGameObject::Update(dt);

			// Simple fall down
			vy += SIMON_GRAVITY * dt;

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
				x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
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
		if (item != NULL) {//co item
			if (GetTickCount() - dt_die > 150) // cho 150 mili second
			{

				item->Update(dt, coObjects);
				state = TORCH_STATE_ITEM;
			}
		}
	}
	
}

void CEnemy::Render()
{	
	if (state == TORCH_STATE_EXSIST)
	{
		if (vx < 0)
			animations[ENEMY_ANI_WALKING]->Render(x, y);
		else
			animations[ENEMY_ANI_WALKING]->Render(x, y, vx);
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

void CEnemy::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY_STATE_DIE:

		break;
	case ENEMY_STATE_WALKING:
		vx = -ENEMY_WALKING_SPEED;
	}

}
