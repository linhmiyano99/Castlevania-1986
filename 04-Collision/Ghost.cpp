#include"Ghost.h"
#include"Scene.h"
#include"HidenObject.h"

bool CGhost::isStart = false;

CGhost::CGhost(float _x, float _y, int id) :CEnemy(_x, _y, id, eType::GHOST)
{
	animations.clear();
	AddAnimation(1000);
	AddAnimation(800);
	AddAnimation(802);
	nx = -1;
	SetSpeed(GetTrend() * GHOST_SPEED, 0);
	dt_appear = 0;
	isOnStair = false;
}
void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!CScene::IsGoGhost())
		return;
	if (dt_appear > 0)
	{
		float cam_x, cam_y;
		CGame::GetInstance()->GetCamPos(cam_x, cam_y);
		if (start_x > cam_x + 660 || start_x < cam_x - 100)
			return;
		if (GetTickCount() - dt_appear > TIME_APPEAR && (start_x > cam_x + 560 ) || (start_x < cam_x ) )
		{
			float s_x, s_y;
			CSimon::GetInstance()->GetPosition(s_x, s_y);
			if(start_x > s_x)
			{
				nx = -1;
			}
			else if (start_x < s_x)
			{
				nx = 1;
			}
			state = TORCH_STATE_EXSIST;
			x = start_x;
			y = start_y;
			vx = nx * GHOST_SPEED;

			if (item)
				item->SetState(ITEM_STATE_EXSIST);
			dt_appear = 0;
			dt_die = 0;
			isOnStair = false;
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
			float _x, _y;
			CSimon::GetInstance()->GetPosition(_x, _y);
			if (_x > 4000)
			{
				if ((x < 4100 && nx < 0) || (x > 5000 && nx > 0))
				{
					nx = -nx;
					vx = -vx;
				}
			}
			else {
				if ((x < 0 && nx < 0) || (x > 3020 && nx > 0))
				{
					vx = -vx;
					nx = -nx;
				}
			}

			vector<LPGAMEOBJECT> listBrick;
			vector<LPGAMEOBJECT> listHiden;
			vector<LPGAMEOBJECT> listStairUp;
			vector<LPGAMEOBJECT> listStairDown;
			vector<LPGAMEOBJECT> list;
			for (int i = 0; i < coObjects->size(); i++)
			{

				if (dynamic_cast<CBrick*>(coObjects->at(i)))
				{
					CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
					listBrick.push_back(brick);
					list.push_back(brick);
				}
				else if (dynamic_cast<CHidenObject*>(coObjects->at(i)) && coObjects->at(i)->GetState() == HIDENOBJECT_TYPE_GHOST_2)
				{
					CHidenObject* brick = dynamic_cast<CHidenObject*>(coObjects->at(i));
					listHiden.push_back(brick);
					list.push_back(brick);

				}
				else if (dynamic_cast<CHidenObject*>(coObjects->at(i)) && coObjects->at(i)->GetState() == HIDENOBJECT_TYPE_GHOST_UP)
				{
					CHidenObject* brick = dynamic_cast<CHidenObject*>(coObjects->at(i));
					listStairUp.push_back(brick);
					list.push_back(brick);

				}
				else if (dynamic_cast<CHidenObject*>(coObjects->at(i)) && (coObjects->at(i)->GetState() == HIDENOBJECT_TYPE_GHOST_DOWN))
				{
					CHidenObject* brick = dynamic_cast<CHidenObject*>(coObjects->at(i));
					listStairDown.push_back(brick);
					list.push_back(brick);

				}
			}

			vy += SIMON_GRAVITY * dt;

			CGameObject::Update(dt);

			// Simple fall down
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();


			CalcPotentialCollisions(&list, coEvents);

			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else {
				float min_tx, min_ty, nx = 0, ny_1;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny_1);

				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<CBrick*>(e->obj))
					{
						listBrick.clear();
						CBrick* torch = dynamic_cast<CBrick*>(e->obj);
						listBrick.push_back(torch);
						CollisionWithBrick(dt, listBrick, min_tx, min_ty, nx, ny_1);
					}
					if (dynamic_cast<CHidenObject*>(e->obj))
					{
						listHiden.clear();
						CHidenObject* torch = dynamic_cast<CHidenObject*>(e->obj);
						listHiden.push_back(torch);
						CollisionWithHiden(dt, listHiden, min_tx, min_ty, nx, ny_1);
					}

				}

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
	if (!CScene::IsGoGhost())
		return;
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
		if (GetTickCount() - dt_die < 300)
		{
			animations[1]->Render(x, y);
			if (animations[1]->GetCurrentFrame() > 0)
				animations[2]->Render(x - 2, y - 5);
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
void CGhost::CollisionWithBrick(DWORD dt, vector<LPGAMEOBJECT>& listBrick, float min_tx0, float min_ty0, int nx0, int ny0)
{
	float b_x, b_y;
	listBrick.at(0)->GetPosition(b_x, b_y);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(&listBrick, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//// block 
	if (min_tx <= min_tx0)
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	if (min_ty <= min_ty0)
		y += min_ty * dy + ny * 0.4f;
	if (ny != 0) vy = 0;

}

void CGhost::CollisionWithHiden(DWORD dt, vector<LPGAMEOBJECT>& list, float min_tx0, float min_ty0, int nx0, int ny0)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(&list, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//// block 


	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CHidenObject* ohiden = dynamic_cast<CHidenObject*>(list.at(0));
	if (ohiden->GetState() == HIDENOBJECT_TYPE_GHOST_2)
	{
		vx = 0;
		vy = GHOST_SPEED * 2;
		y += vy * dt;
		x += vx * dt;
	}
	else {
		if (ohiden->GetState() == HIDENOBJECT_TYPE_UPSTAIR)
		{
			isOnStair = true;
			vx = 0.3f;
			vx = 0.3f;
			y += vy * dt;
			x += vx * dt;
		}
		else if (isOnStair && ohiden->GetState() == HIDENOBJECT_TYPE_DOWNSTAIR)
		{
			vx = GHOST_SPEED;
			vy = 0;
			y += vy * dt;
			x += vx * dt;

		}
		else
		{
			x += vx * dt;

		}
	}

}