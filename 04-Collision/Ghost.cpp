#include"Ghost.h"
#include"Scene.h"

bool CGhost::isStart = false;

void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (dt_appear > 0)
	{
		float cam_x, cam_y;
		CGame::GetInstance()->GetCamPos(cam_x, cam_y);
		if (GetTickCount() - dt_appear > TIME_APPEAR && ((start_x > cam_x + 560 && nx < 0 ) || (start_x < cam_x && nx > 0)))
		{
			state = TORCH_STATE_EXSIST;
			x = start_x;
			y = start_y;
			vx = nx * GHOST_SPEED;
			vy =  0.2f;

			if (item)
				item->SetState(ITEM_STATE_EXSIST);
			dt_appear = 0;
			dt_die = 0;
		}
		else
			return;
	}
	if (vx == 0 && vy == 0)
		return;
	if (dt_die == 0)
	{
		if (state == TORCH_STATE_EXSIST)
		{
			if ((x < 0 && nx < 0) || (x > 3020 && nx > 0))
			{
				vx = -vx;
				nx = -nx;
			}
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
				//x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				x += dx;
				y += min_ty * dy + ny * 0.4f;

				if (ny != 0) vy = 0;
			}
			// clean up collision events
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
		else 
		if (state == TORCH_STATE_NOT_EXSIST) 
		{
			dt_die = GetTickCount();
			if (item)
			{
				item->SetPosition(x, y);
			}
			else
			{
				state = TORCH_STATE_ITEM_NOT_EXSIST;
				dt_appear = GetTickCount();
				return;
			}
		}
	}
	else
	{
		if (item != NULL) {//co item

			if (GetTickCount() - dt_die > 150) // cho 150 mili second
			{
				item->Update(dt, coObjects);
				item->GetPosition(x, y);
				state = TORCH_STATE_ITEM;
				if (item->GetState() == ITEM_STATE_NOT_EXSIST)
				{
					state = TORCH_STATE_ITEM_NOT_EXSIST;
					dt_appear = GetTickCount();
					return;
				}
			}
		}
		else
		{
			state = TORCH_STATE_ITEM_NOT_EXSIST;
			dt_appear = GetTickCount();
			return;
		}
	}

}
void CGhost::Render()
{
	if (CScene::GetInstance()->IsTranScene())
		return;
	if (x == 0 && y == 0)
		return;
	if (state == TORCH_STATE_EXSIST)
	{
		animations[0]->Render(x, y, nx, 255);
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

	RenderBoundingBox();
}
void CGhost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + GHOST_BBOX_WIDTH;
		bottom = y + GHOST_BBOX_HEIGHT;
	}
	else if (state == TORCH_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
}
