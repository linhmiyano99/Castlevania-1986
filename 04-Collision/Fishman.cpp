#include "Fishman.h"
#include "Simon.h"
#include "SmallBall.h"
#include "Scene.h"
#include <ctime> 

bool CFishman::isStart = false;
CFishman::CFishman(float _x , float _y , int id ) :CEnemy(_x, _y, id, eType::FISHMEN)
{
	start_x = _x;
	start_y = _y;
	animations.clear();
	AddAnimation(1004);
	AddAnimation(1005);
	AddAnimation(1006);
	AddAnimation(1100);
	AddAnimation(800);
	isJumping = true;
	isFall = false;
	ny = -1;
	nx = -1;
	vx = vy = 0;
	_ground = 0;
	start_attack = GetTickCount();
	//sound = new Sound();
	for (int i = 0; i < 3; i++)
	{
		CWaterEffection* water = new CWaterEffection();
		list.push_back(water);
		water = NULL;
	}
	state = TORCH_STATE_EXSIST;
	Go();
	ResetWater(0);
	isCanAttack = false;
	GetLimit();
}
void CFishman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!CFishman::IsStart())
		return;
	float c_x, c_y;
	CGame::GetInstance()->GetCamPos(c_x, c_y);
	if (CScene::GetInstance()->IsKillAllEnemy() && x > c_x&& x < c_x + SCREEN_WIDTH)
	{
		Dead();
	}
	if (dt_appear > 0)
	{
		float cam_x, cam_y;
		CGame::GetInstance()->GetCamPos(cam_x, cam_y);
		if (GetTickCount() - dt_appear > TIME_APPEAR)
		{
			state = TORCH_STATE_EXSIST;
			srand((unsigned)time(0));
			int _d = (rand() % 3) * 40 - 100;
			x = cam_x + start_x - CScene::GetInstance()->GetLeft() + _d;
			y = start_y;
			_ground = 0;
			ny = -1;
			isJumping = true;
			Go();
			isFall = false;
			if (item)
				item->SetState(ITEM_STATE_EXSIST);
			dt_appear = 0;
			dt_die = 0;
			ResetWater(0);
			isCanAttack = false;
			GetLimit();
		}
		else
			return;
	}
	if (dt_die == 0)
	{
		if (isJumping) {
			if (y <= FISHMAN_MAX_HEIGHT)
			{
				vy = SIMON_GRAVITY * dt;
				vx = nx * FISHMAN_SPEED;
				isJumping = false;
			}
			for each (CWaterEffection* var in list)
			{
				var->Update(dt);
			}
		}
		if (isJumping)
		{
			y += vy * dt;
			return;
		}
		if (isFall)
		{
			for each (CWaterEffection * var in list)
			{
				var->Update(dt);
			}
		}
		float s_x, s_y;
		CSimon::GetInstance()->GetPosition(s_x, s_y);

		if (GetTickCount() - start_attack > TIME_START_ATTACK && isCanAttack && y == _ground)
		{
			start_attack = GetTickCount();
			if (x < s_x)
			{
				nx = 1;
			}
			else
			{
				nx = -1;
			}
			vx = 0;
			isAttacking = true;
			CSmallBall* smallball = new CSmallBall(x, y, nx);
			CScene::GetInstance()->AddSmallBall(smallball);
			return;
		}
		if (GetTickCount() - start_attack > TIME_ATTACK)
		{
			isAttacking = false;
			vx = nx * 0.15f;
		}



		if (vx == 0)
		{
			CGameObject::Update(dt);
			if (!isAttacking)
				y += dy;
		}
		else
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
				float cam_x, cam_y;
				CGame::GetInstance()->GetCamPos(cam_x, cam_y);
				if (y > WATTER_Y && !isFall)
				{
					isFall = true;
					ResetWater(1);
					Sound::GetInstance()->Play(eSound::soundFallingDownWaterSurface);
				}
				if (x < cam_x - 40 || x > cam_x + SCREEN_WIDTH || y > cam_y + SCREEN_HEIGHT || y < cam_y)
				{
					state = TORCH_STATE_ITEM_NOT_EXSIST;
					dt_appear = GetTickCount();
					return;
				}
			
				/*float s_x, s_y;
				CSimon::GetInstance()->GetPosition(s_x, s_y);
				if (x < s_x - FISHMAN_MAX_DISTANCE_WITH_SIMON)
				{
					nx = 1;
					vx = abs(vx);
				}*/

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

				CalcPotentialCollisions(&listBrick, coEvents);

				// No collision occured, proceed normally
				if (coEvents.size() == 0)
				{
					x += dx;
					y += dy;
					isCanAttack = false;

				}
				else
				{
					float min_tx, min_ty, nx = 0, ny;

					FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

					//// block 
					//x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
					x += dx;
					y += min_ty * dy + ny * 0.4f;

					if (ny != 0)
					{
						vy = 0;
						_ground = y;
					}
					isCanAttack = true;
					
				}
				// clean up collision events
				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
				listBrick.clear();
			}
			


		}

		if ((x <= _leftLimit && vx < 0) || (x >= _rightLimit && vx > 0))
		{
			vx = -vx;
			nx = -nx;
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
}
void CFishman::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!CFishman::IsStart())
		return;
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
void CFishman::Render()
{
	if (!CFishman::IsStart() || state == ITEM_STATE_NOT_EXSIST)
		return;
	if (vx == 0 && vy == 0 && isJumping)
		return;
	if (state == TORCH_STATE_EXSIST)
	{

		if (isJumping)
		{

			animations[FISHMAN_ANI_JUMPING]->Render(x, y, -1, 255);

			for each (CWaterEffection * var in list)
			{
				var->Render();
			}

		}
		else if (isAttacking)
		{
			animations[FISHMAN_ANI_ATTACK]->Render(x, y, nx, 255);
		}
		else
		{
			animations[FISHMAN_ANI_WALKING]->Render(x, y, nx, 255);
			if (isFall)
			{
				for each (CWaterEffection * var in list)
				{
					var->Render();
				}
			}
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
			animations[4]->Render(x, y);

		}
	}
	//RenderBoundingBox();
}
void CFishman::Go() {
	if (isJumping) {
		vx = nx * FISHMAN_RUNNING_SPEED_X;
		vy = ny * FISHMAN_RUNNING_SPEED_Y;
		state = TORCH_STATE_EXSIST;
	}
}
void  CFishman::ResetWater(int type)
{
	if (type == 0)
	{
		list[0]->SetPosition(x, y + FISHMAN_BBOX_HEIGHT);
		list[1]->SetPosition(x + WATTER_WIDTH, y + FISHMAN_BBOX_HEIGHT/3);
		list[2]->SetPosition(x + WATTER_WIDTH * 2, y + FISHMAN_BBOX_HEIGHT);
	}
	else
	{
		list[0]->SetPosition(x, y + FISHMAN_BBOX_HEIGHT/3);
		list[1]->SetPosition(x + WATTER_WIDTH, y + FISHMAN_BBOX_HEIGHT);
		list[2]->SetPosition(x + WATTER_WIDTH * 2, y + FISHMAN_BBOX_HEIGHT/3);
	}
}
void CFishman::GetLimit()
{
	if (x < 3505)
	{
		_leftLimit = 3076;
		_rightLimit = 3474;
	}
	else if (x < 3631)
	{
		_leftLimit = CScene::GetInstance()->GetLeft();
		_rightLimit = CScene::GetInstance()->GetRight();
	}
	else if (x < 4050)
	{
		_leftLimit = 3720;
		_rightLimit = 3968;
	}
	else
	{
		_leftLimit = CScene::GetInstance()->GetLeft();
		_rightLimit = 4065;
	}
}
