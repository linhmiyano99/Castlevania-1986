#include "Panther.h"
#include "Scene.h"
#include "HidenObject.h"

bool CPanther::isReset = false;
CPanther::CPanther(float _x, float _y, int id) :CEnemy(_x, _y, id, eType::PANTHER)
{
	animations.clear();
	AddAnimation(1001);
	AddAnimation(1002);
	AddAnimation(800);
	if (_x < 1460)
	{
		LeftLimit = 1230;
	}
	else if (_x < 1810)
	{
		LeftLimit = 1387;
	}
	else
	{
		LeftLimit = 1754;
	}
	isStart = false;
	isJump = false;
}
void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (CPanther::IsResetting())
	{
		Reset();
		return;
	}
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	if (CScene::GetInstance()->IsKillAllEnemy() && x > cam_x&& x < cam_x + SCREEN_WIDTH)
	{
		Dead();
	}
	if (dt_appear > 0)
	{
		
		if (GetTickCount() - dt_appear > TIME_APPEAR &&  x > cam_x + SCREEN_WIDTH)
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
			isJump = false;
			isStart = false;
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
			float s_x, s_y;
			CSimon::GetInstance()->GetPosition(s_x, s_y);
			if (!isStart)
			{
				if ((abs(x - s_x) < DISTANCE_TO_START1) || (abs(x - s_x) < DISTANCE_TO_START2 && s_y + PANTHER_BBOX_HEIGHT > y))
				{
					SetSpeed(0,0);
					isStart = true;
				}
				return;
			}
			CGameObject::Update(dt);
			float cam_x, cam_y;
			CGame::GetInstance()->GetCamPos(cam_x, cam_y);
			if (x < cam_x - 600)
			{
				state = TORCH_STATE_ITEM_NOT_EXSIST;
				dt_appear = GetTickCount();
				return;
			}
			vector<LPGAMEOBJECT> list;
			for (int i = 0; i < coObjects->size(); i++)
			{

				if (dynamic_cast<CBrick*>(coObjects->at(i)))
				{
					list.push_back(coObjects->at(i));
				}
				else if (coObjects->at(i)->GetState() == eType::OBJECT_HIDDEN_PANTHER_JUMP)
				{
					list.push_back(coObjects->at(i));
				}
			}
			// Simple fall down
			vy += PANTHER_GRAVITY * dt;

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
						CollisionWithBrick(dt, e->obj, min_tx, min_ty, nx, ny_1);
					}
					if (dynamic_cast<CHidenObject*>(e->obj))
					{
						CollisionWithHiden(dt, e->obj, min_tx, min_ty, nx, ny_1);
					}

				}
			}
			// clean up collision events
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
			list.clear();
		}
	}
	else
	{
		if (item != NULL) {//co item

			if (GetTickCount() - dt_die > TIME_ENEMY_DIE) // cho 150 mili second
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
	if (x < LeftLimit)
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
		if (GetTickCount() - dt_die < TIME_ENEMY_DIE)
		{
			animations[2]->Render(x, y);
		}
	}
	//RenderBoundingBox();
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
void CPanther::CollisionWithBrick(DWORD dt, LPGAMEOBJECT& obj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	float b_x, b_y;

	obj->GetPosition(b_x, b_y);

	vector<LPGAMEOBJECT> listBrick;
	listBrick.push_back((LPGAMEOBJECT)(obj));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(&listBrick, coEvents);

	float min_tx, min_ty, nx1 = 0, ny1;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx1, ny1);

	//// block 
	x += dx;
	if (min_ty <= min_ty0)
		y += min_ty * dy + ny1 * 0.4f;
	if (ny1 != 0) vy = 0;
	listBrick.clear();

}

void CPanther::CollisionWithHiden(DWORD dt, LPGAMEOBJECT& obj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	if (!isJump)
	{
		x += dx - 10;
		vy = -0.3f;
		y += vy * dt;
		isJump = true;
	}
}
void CPanther::SetSpeed(float _vx, float _vy) {
	vx = -PANTHER_RUNNING_SPEED_X; vy = PANTHER_RUNNING_SPEED_Y;
}
void CPanther::SetState(int state)
{
	this->state = state;
	if (state == TORCH_STATE_ITEM_NOT_EXSIST)
	{
		dt_appear = GetTickCount();
	}
}
void CPanther::Reset()
{
	state = TORCH_STATE_EXSIST;
	x = start_x;
	y = start_y;
	nx = -1;
	vx = vy = 0;
	isStart = false;
	isJump = false;
}
