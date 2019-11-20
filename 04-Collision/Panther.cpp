#include "Panther.h"
#include "Scene.h"
#include "HidenObject.h"

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (dt_appear > 0)
	{
		float cam_x, cam_y;
		CGame::GetInstance()->GetCamPos(cam_x, cam_y);
		if (GetTickCount() - dt_appear > TIME_APPEAR )
		{
			state = TORCH_STATE_EXSIST;
			x = start_x;
			y = start_y;
			vx = vx = 0;
			nx = -1;

			if (item)
				item->SetState(ITEM_STATE_EXSIST);
			dt_appear = 0;
			dt_die = 0;
		}
		else
			return;
	}
	if (dt_die == 0)
	{
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
		else
		{
			CGameObject::Update(dt);
			float cam_x, cam_y;
			CGame::GetInstance()->GetCamPos(cam_x, cam_y);
			if (x < cam_x - 600)
			{
				state = TORCH_STATE_ITEM_NOT_EXSIST;
				dt_appear = GetTickCount();
				return;
			}

			// Simple fall down
			vy += SIMON_GRAVITY * dt;

			vector<LPGAMEOBJECT> listBrick;
			vector<LPGAMEOBJECT> listHiden;
			for (int i = 0; i < coObjects->size(); i++)
			{

				if (dynamic_cast<CBrick*>(coObjects->at(i)))
				{
					CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
					listBrick.push_back(brick);
				}
				else if (dynamic_cast<CHidenObject*>(coObjects->at(i)) && coObjects->at(i)->GetState() == HIDENOBJECT_TYPE_PANTHER_JUMP)
				{
					CHidenObject* brick = dynamic_cast<CHidenObject*>(coObjects->at(i));
					listHiden.push_back(brick);
				}
			}

			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();

			CalcPotentialCollisions(&listHiden, coEvents);

			// No collision occured, proceed normally
			if (coEvents.size() != 0)
			{
				float min_tx, min_ty, nx = 0, ny;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

				//// block 
				//x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				x += dx;
				y += dy;
				vy -= 0.4f;
				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
				return;
			}
			// clean up collision events


			coEvents.clear();
			// turn off collision when die 
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
	if (x < LeftLimit || x > 3020)
	{
		nx = - nx;
		vx = -vx;
	}
}


void CPanther::Render()
{
	if (CScene::GetInstance()->IsTranScene())
		return;
	if (state == TORCH_STATE_EXSIST)
	{
		if (vx == 0)
		{
			animations[PANTHER_ANI_SIT]->Render(x, y, -1, 255);
		}
		else
		{
			if (vx < 0)
				animations[PANTHER_ANI_RUNNING]->Render(x, y, -1, 255);
			else
				animations[PANTHER_ANI_RUNNING]->Render(x, y, 1, 255);
		}
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

void CPanther::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + PANTHER_BBOX_WIDTH;
		bottom = y + PANTHER_BBOX_HEIGHT;
	}
	else if (state == TORCH_STATE_ITEM)
	{
		item->GetPosition(x, y);
		item->GetBoundingBox(left, top, right, bottom);
	}
}
//
//void CPanther::SetState(int state)
//{
//	CGameObject::SetState(state);
//	switch (state)
//	{
//	case ENEMY_STATE_DIE:
//
//		break;
//	case ENEMY_STATE_WALKING:
//		vx = -PANTHER_RUNNING_SPEED_X;
//		vy = -PANTHER_RUNNING_SPEED_Y;
//	}
//
//}