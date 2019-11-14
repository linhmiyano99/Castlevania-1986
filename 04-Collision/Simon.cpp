#include "Simon.h"
#include "Torch.h"
#include "WhipUpgrade.h"
#include "Game.h"
#include "VampireKiller.h"
#include "ItemDagger.h"
#include "Brick.h"
#include "Dagger.h"
#include "HidenObject.h"
#include "Scene.h"
#include "Enemy.h"
#include "Map.h"
#include "Boss.h"


CSimon* CSimon::__instance = NULL;

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

CSimon::CSimon() : CGameObject()
{
	CVampireKiller* rob = CVampireKiller::GetInstance();
	weapons[eType::VAMPIREKILLER] = rob;
	untouchable = 0;
	trans_start = 0;
	_heart = 5;
	isCanOnStair = 0;
	isOnStair = false;
	_stairTrend = 0;
	_energy = 16;
	isAutoGo = false;
	auto_x = -1;
	_score = 0;
	_lives = 3;
	_count = 0;
	
	CSimon::AddAnimation(400);		//0. idle left 
	CSimon::AddAnimation(401);		//1. walk left
	CSimon::AddAnimation(402);		//2. jump left
	CSimon::AddAnimation(403);		//3. sit left
	CSimon::AddAnimation(404);		//4. stand attack
	CSimon::AddAnimation(405);		//5. sit attack
	CSimon::AddAnimation(399);		//6. trans
	CSimon::AddAnimation(406);		//7. go up
	CSimon::AddAnimation(407);		//8. go down
	CSimon::AddAnimation(408);		//9. hurt
	CSimon::AddAnimation(409);		//9. idle up
	CSimon::AddAnimation(410);		//9. idle down
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (attack_start > 0)
	{
		if (GetTickCount() - attack_start < ATTACK_TIME)
		{
		}
		else if (GetTickCount() - attack_start < ATTACK_TIME_WAIT)
		{
			if (state == SIMON_STATE_SIT_ATTACK)
			{
				y -= 20;
				state = SIMON_STATE_SIT;
			}
			else
			{
				state = SIMON_STATE_IDLE;
			}
		}
		else
		{
			
			attack_start = 0;
		}
	}
	if (_energy <= 0 || y > 780)
	{
		if (_lives > 0)
		{
			_lives--;
			_energy = 16;
			if (CScene::GetInstance()->GetStage() == 1)
			{
				x = 0.0f;
				y = 300.0f;
			}
			else if (CScene::GetInstance()->GetStage() == 2)
			{
				x = 3120.0f;
				y = 50.0f;
			}
			else  if (CScene::GetInstance()->GetStage() == 3)
			{
				x = 4130.0f;
				y = 50.0f;
			}
		}
		else
		{
			_energy = 16;

		}
		weapons[eType::VAMPIREKILLER]->Reset();
		return;
	}
	if (isAutoGo && !CScene::GetInstance()->IsTranScene())
	{
		AutoGo();
		if (abs(auto_x - x) > 0.5f)
			x += 0.5 * nx;
		else
		{
			isAutoGo = false;
		}
		return;
	}
	else if (isAutoGo && CScene::GetInstance()->IsTranScene())
	{
		AutoGo();
		if (abs(auto_x - x) > 0.5f)
			x += 0.5 * nx;
		else
		{
			isAutoGo = false;
		}
		return;
	}
	else if (trans_start > 0)
	{
		vx = 0;
		if (GetTickCount() - trans_start > 400)
		{
			trans_start = 0;
		}
	}
	else {
		vector<LPGAMEOBJECT> listTorch;
		vector<LPGAMEOBJECT> listBrick;
		vector<LPGAMEOBJECT> listHideObject;
		vector<LPGAMEOBJECT> listEnemy;
		vector<LPGAMEOBJECT> listPanther;
		vector<LPGAMEOBJECT> listGate;
		vector<LPGAMEOBJECT> listBat;
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CHidenObject*>(coObjects->at(i)))
			{
				listHideObject.push_back(coObjects->at(i));
			}
			else if (dynamic_cast<CPanther*>(coObjects->at(i)))
			{
				listPanther.push_back(coObjects->at(i));
			}
		}
		for (int i = 0; i < listPanther.size(); i++)
		{
			float p_x, p_y;
			listPanther.at(i)->GetSpeed(p_x, p_y);
			if (p_x == 0)
			{
				listPanther.at(i)->GetPosition(p_x, p_y);
				if ((abs(x - p_x) < 200 && abs(y - p_y) < 40) || abs(x - p_x) < 40)
					listPanther.at(i)->SetSpeed(0.1f, 0.1f);
			}
		}

		if (isOnStair)
		{
			if (state == SIMON_STATE_GO_DOWN)
			{
				if (_stairTrend == 0)
				{
					nx = -1;
					dx = -2.0f;
					dy = 2.0f;
				}
				else
				{
					nx = 1;
					dx = 2.0f;
					dy = 2.0f;
				}
			}

			else if (state == SIMON_STATE_GO_UP)
			{
				if (_stairTrend == 0)
				{
					nx = 1;
					dx = 2.0f;
					dy = -2.0f;
				}
				else
				{
					nx = -1;
					dx = -2.0f;
					dy = -2.0f;
				}
			}
			else
			{
				dx = 0;
				dy = 0;
			}

		}
		else {
			CGameObject::Update(dt);
			vy += SIMON_GRAVITY * dt;
		}
		if (listHideObject.size() > 0)
			IsCanOnStair(listHideObject);
		listHideObject.clear();
		if (state == SIMON_STATE_SIT_ATTACK || state == SIMON_STATE_STAND_ATTACK)
		{
			weapons[eType::VAMPIREKILLER]->SetPosition(x, y);
			weapons[eType::VAMPIREKILLER]->SetTrend(nx);
			weapons[eType::VAMPIREKILLER]->CollisionWithObject(dt, *coObjects);
		}
		else if (_heart > 0 && state == SIMON_STATE_ATTACK_DAGGER && !(weapons.find(eType::DAGGER) == weapons.end()) && weapons[eType::DAGGER]->GetState() == DAGGER_STATE_HIDE)
		{
			weapons[eType::DAGGER]->SetState(DAGGER_STATE_ATTACK);
			weapons[eType::DAGGER]->SetPosition(x, y);
			weapons[eType::DAGGER]->SetTrend(nx);
			_heart--;

		}

		// Calculate dx, dy 

		// Simple fall down

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 
		if (state != SIMON_STATE_DIE)
			CalcPotentialCollisions(coObjects, coEvents);

		// reset untouchable timer if untouchable time has passed
		if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}
		else if (GetTickCount() - untouchable_start < SIMON_HURT_TIME && untouchable == 1)
		{
			if(!isOnStair)
				state = SIMON_STATE_HURT;
		}
		else
		{
			if (!isOnStair)
			{
				if (attack_start > 0)
				{
					animations[SIMON_ANI_STANDING_ATTACKING]->ResetFrame();
					animations[SIMON_ANI_SITTING_ATTACKING]->ResetFrame();
					attack_start = 0;
				}
				state = SIMON_STATE_IDLE;
			}
		}

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

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBrick*>(e->obj))
				{
					if (!isOnStair) {
						CBrick* torch = dynamic_cast<CBrick*>(e->obj);
						listBrick.push_back(torch);
						CollisionWithBrick(dt, listBrick, min_tx, min_ty, nx, ny);
						listBrick.clear();
					}
					else
					{
						x += dx;
						y += dy;
					}
				}
				else if (dynamic_cast<CTorch*>(e->obj))
				{

					CTorch* torch = dynamic_cast<CTorch*>(e->obj);

					if (dynamic_cast<CEnemy*>(torch))
					{
						CEnemy* torch = dynamic_cast<CEnemy*>(e->obj);
						if (dynamic_cast<CBoss*>(torch))
						{
							CBoss* boss = dynamic_cast<CBoss*>(e->obj);
							if (boss->GetState() == BOSS_STATE_ATTACK || boss->GetState() == BOSS_STATE_FLY)
							{
								if (untouchable == 0)
								{
									listEnemy.push_back(torch);
									CollisionWithEnemy(dt, listEnemy, min_tx, min_ty, nx, ny);
									if (dynamic_cast<CBat*>(torch))
									{
										CBat* bat = dynamic_cast<CBat*>(e->obj);
										bat->SetState(TORCH_STATE_NOT_EXSIST);
									}
									else if (dynamic_cast<CPanther*>(torch))
									{
										CPanther* panther = dynamic_cast<CPanther*>(e->obj);
										float _x, _y;
										panther->GetPosition(_x, _y);
										if (_x > x)
											nx = 1;
										else
											nx = -1;

									}
									StartUntouchable();
								}
								listEnemy.clear();
							}
							else
							{
								if (dynamic_cast<CItem*>(torch->GetItem()))
								{
									listEnemy.push_back(torch->GetItem());
									CollisionWithItem(dt, listEnemy);
								}
							}
						}
						else {
							if ((torch->GetState() == TORCH_STATE_EXSIST))
							{
								if (untouchable == 0)
								{
									listEnemy.push_back(torch);
									CollisionWithEnemy(dt, listEnemy, min_tx, min_ty, nx, ny);
									if (dynamic_cast<CBat*>(torch))
									{
										CBat* bat = dynamic_cast<CBat*>(e->obj);
										bat->SetState(TORCH_STATE_NOT_EXSIST);
									}
									else if (dynamic_cast<CPanther*>(torch))
									{
										CPanther* panther = dynamic_cast<CPanther*>(e->obj);
										float _x, _y;
										panther->GetPosition(_x, _y);
										if (_x > x)
											nx = 1;
										else
											nx = -1;

									}
									StartUntouchable();
								}
								listEnemy.clear();
							}
							else {
								if (dynamic_cast<CItem*>(torch->GetItem()))
								{
									listEnemy.push_back(torch->GetItem());
									CollisionWithItem(dt, listEnemy);
								}
							}
						}
					}
					else {
						listTorch.push_back(torch);
						CollisionWithTorch(dt, listTorch, min_tx, min_ty, nx, ny);
						listTorch.clear();
					}


				}

				else if (dynamic_cast<CHidenObject*>(e->obj))
				{
					CHidenObject* torch = dynamic_cast<CHidenObject*>(e->obj);

					listHideObject.push_back(torch);
					CollisionWithHidenObject(dt, listHideObject, min_tx, min_ty, nx, ny);
					listHideObject.clear();
				}
				else if (dynamic_cast<CGate*>(e->obj))
				{
					CGate* torch = dynamic_cast<CGate*>(e->obj);
					if (CBoss::GetInstance()->GetState() == BOSS_STATE_ITEM_NOT_EXSIST && CScene::GetInstance()->GetStage() == 3)
					{

					}
					else {
						listGate.push_back(torch);
						CollisionWithGate(dt, listGate, min_tx, min_ty, nx, ny);
						listGate.clear();
					}
				}


			}

		}



		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

	if (x < CScene::GetInstance()->GetLeft())
		x = CScene::GetInstance()->GetLeft();
	if (x > CScene::GetInstance()->GetRight())
		x = CScene::GetInstance()->GetRight();

}


void CSimon::Render()
{
	int id;
	if (isAutoGo)
	{
		if (CScene::GetInstance()->IsTranScene())
		{
			float c_x, c_y;
			CGame* game = CGame::GetInstance();
			game->GetCamPos(c_x, c_y);
			CScene* scene = CScene::GetInstance();
			CScene* scene2 = new CScene();
			if (scene->GetScene() == 1)
				scene2->SetMap(2);
			else
				scene2->SetMap(4);
			if (c_x < scene2->GetLeft() - SCREEN_WIDTH / 2)
				id = SIMON_ANI_IDLE;
			else
				id = SIMON_ANI_WALKING;
		}
		else
			id = SIMON_ANI_WALKING;
	}
	else if (state == SIMON_STATE_IDLE_DOWN)
	{
		id = SIMON_ANI_IDLE_DOWN;
	}
	else if (state == SIMON_STATE_IDLE_UP)
	{
		id = SIMON_ANI_IDLE_UP;
	}
	else if (state == SIMON_STATE_SIT_ATTACK)
	{
		id = SIMON_ANI_SITTING_ATTACKING;
		weapons[eType::VAMPIREKILLER]->GetAnimation()->SetFrame(animations[SIMON_ANI_SITTING_ATTACKING]->GetCurrentFrame());
		weapons[eType::VAMPIREKILLER]->Render();
	}
	else if (state == SIMON_STATE_STAND_ATTACK)
	{
		id = SIMON_ANI_STANDING_ATTACKING;
		weapons[eType::VAMPIREKILLER]->GetAnimation()->SetFrame(animations[SIMON_ANI_STANDING_ATTACKING]->GetCurrentFrame());
		weapons[eType::VAMPIREKILLER]->Render();

	}
	else if (state == SIMON_STATE_GO_UP && (isCanOnStair == 1 || isOnStair))
	{
		id = SIMON_ANI_GO_UP;
	}
	else if (state == SIMON_STATE_GO_DOWN)
	{
		if(isOnStair)
			id = SIMON_ANI_GO_DOWN;
		else
			id = SIMON_ANI_SITTING;
	}
	else if (state == SIMON_STATE_ATTACK_DAGGER)
	{
		id = SIMON_ANI_STANDING_ATTACKING;
	}
	else if (state == SIMON_STATE_SIT)
	{
		id = SIMON_ANI_SITTING;

	}
	else if (state == SIMON_STATE_JUMP)
	{
		if (vy < 0)
			id = SIMON_ANI_JUMPING;
		else
			id = SIMON_ANI_IDLE;
	}
	else if (state == SIMON_STATE_HURT)
	{
		id = SIMON_ANI_HURT;
	}
	else {
		if (vx == 0)
		{
			id = SIMON_ANI_IDLE;
		}
		else
		{
			id = SIMON_ANI_WALKING;
		}
	}
	if (trans_start > 0) {
		id = SIMON_ANI_TRANS;
	}
	int alpha = 255;
	if ( untouchable &&( isOnStair || GetTickCount() - untouchable_start > SIMON_HURT_TIME)) alpha = 128;
	animations[id]->Render(x, y, nx, alpha);
	RenderBoundingBox();

	
}

void CSimon::SetState(int state)
{
	/*if (animations[SIMON_ANI_STANDING_ATTACKING]->GetCurrentFrame() > 0 && this->state == SIMON_STATE_STAND_ATTACK)
	{

	}
	else if (animations[SIMON_ANI_SITTING_ATTACKING]->GetCurrentFrame() > 0 && this->state == SIMON_STATE_SIT_ATTACK)
	{

	}*/
	if (attack_start > 0)
	{

	}
	else if (trans_start > 0) {

	}
	else if (isAutoGo)
	{

	}
	else if (untouchable && GetTickCount() - untouchable_start < SIMON_HURT_TIME)
	{

	}
	else if (animations[SIMON_ANI_GO_UP]->GetCurrentFrame() > 0 && isOnStair)
	{

	}
	else if (animations[SIMON_ANI_GO_DOWN]->GetCurrentFrame() > 0 && isOnStair)
	{

	}
	else
	{
		CGameObject::SetState(state);
		switch (state)
		{
		case SIMON_STATE_WALKING_RIGHT:
			vx = SIMON_WALKING_SPEED;
			nx = 1;
			break;
		case SIMON_STATE_WALKING_LEFT:
			vx = -SIMON_WALKING_SPEED;
			nx = -1;
			break;
		case SIMON_STATE_JUMP:
			if (vy == 0) {
				vy = -SIMON_JUMP_SPEED_Y;
				vx = 0;
			}
			break;

		case SIMON_STATE_SIT_ATTACK:
			attack_start = GetTickCount();
			vx = 0;
			break;
		case SIMON_STATE_SIT:
			//y = 272.0f;
			vx = 0;
			break;
		case SIMON_STATE_STAND_ATTACK:
			attack_start = GetTickCount();
			vx = 0;
			break;
		case SIMON_STATE_ATTACK_DAGGER:
			attack_start = GetTickCount();
			vx = 0;
			if (_heart > 0 && !(weapons.find(eType::DAGGER) == weapons.end()))
			{
				CDagger* dagger = CDagger::GetInstance();
				if (dagger->GetState() == DAGGER_STATE_ATTACK)
				{
					this->state = SIMON_STATE_IDLE;
				}
			}
			else
			{
				this->state = SIMON_STATE_IDLE;

			}
			break;
		case SIMON_STATE_UP:
			y -= 20;

		case SIMON_STATE_IDLE:
			vx = 0;
			break;
		case SIMON_STATE_GO_UP:
			if (isOnStair)
				break;
			if (isCanOnStair != 1)
			{
				state = SIMON_STATE_IDLE;
				vx = 0;
			}
			else
			{
				isOnStair = true;

				if (abs(auto_x - x) > 0.5f)
					isAutoGo = true;
			}
			break;
		case SIMON_STATE_GO_DOWN:
			if (isOnStair)
				break;
			if (isCanOnStair != -1)
			{
				state = SIMON_STATE_SIT;
				vx = 0;
			}
			else
			{
				isOnStair = true;

				if (abs(auto_x - x) > 0.5f)
					isAutoGo = true;
			}
			break;
		case SIMON_STATE_IDLE_UP:
		case SIMON_STATE_IDLE_DOWN:
			vx = vy = 0;
			break;

		}
	}
}
void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
	left = this->x;
	top = this->y;
	right = this->x + SIMON_WIDTH;
	bottom = this->y + SIMON_HEIGHT_STAND;
	if ((state == SIMON_STATE_GO_DOWN && isCanOnStair != -1) 
		|| state == SIMON_STATE_SIT_ATTACK  
		||(state == SIMON_STATE_SIT))
	{
		bottom = this->y + SIMON_HEIGHT_SIT;
	}

}

void CSimon::CollisionWithItem(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	for (int i = 0; i < listObj.size(); i++)
	{
		if ((listObj.at(i)->GetState() == ITEM_STATE_EXSIST && listObj.at(i)->GetType() != eType::BOSS) || (listObj.at(i)->GetState() == BOSS_STATE_ITEM && listObj.at(i)->GetType() == eType::BOSS))
		{
			if (listObj.at(i)->GetType() == eType::WHIPUPGRADE)
			{
				CVampireKiller::GetInstance()->setUpLevel();
				trans_start = GetTickCount();
			}
			else if (listObj.at(i)->GetType() == eType::DAGGER)
			{
				CDagger* dagger = CDagger::GetInstance();
				weapons[eType::DAGGER] = dagger;
				CBoard::GetInstance()->SetWeapon(eType::DAGGER);
			}
			else if (listObj.at(i)->GetType() == eType::HEART)
			{
				_heart += 5;
			}
			else if (listObj.at(i)->GetType() == eType::SMALLHEART)
			{
				_heart ++;
			}
			else if (listObj.at(i)->GetType() == eType::MONEY_1)
			{
				_score += 100;
			}
			else if (listObj.at(i)->GetType() == eType::MONEY_2)
			{
				_score += 400;
			}
			else if (listObj.at(i)->GetType() == eType::MONEY_3)
			{
				_score += 700;
			}
			else if (listObj.at(i)->GetType() == eType::MONEY_4)
			{
				_score += 1000;
			}
			else if (listObj.at(i)->GetType() == eType::BOSSBALL)
			{
				//_score += 10000;
			}
			if (listObj.at(i)->GetType() == eType::BOSSBALL)
			{
				listObj.at(i)->SetState(BOSS_STATE_ITEM_NOT_EXSIST);
				CBoard::GetInstance()->Stop();
			}
			else
				listObj.at(i)->SetState(ITEM_STATE_NOT_EXSIST);
		}
	}
}
void CSimon::CollisionWithBrick(DWORD dt, vector<LPGAMEOBJECT>& listBrick, float min_tx0, float min_ty0, int nx0, int ny0)
{
	float b_x, b_y;
	listBrick.at(0)->GetPosition(b_x, b_y);
	if (b_y > y)
	{
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
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		// clean up collision events
		vector<LPGAMEOBJECT> listItem;
		for (int i = 0; i < listBrick.size(); i++)
		{
			CTorch* torch = dynamic_cast<CTorch*>(listBrick.at(i));// if e->obj is torch 
			if (torch->GetState() == TORCH_STATE_EXSIST) {

			}
			else
			{
				if (dynamic_cast<CItem*>(torch->GetItem())) // if e->obj->tiem is items 
				{
					CItem* item = dynamic_cast<CItem*>(torch->GetItem());
					listItem.push_back(item);
					torch->SetState(TORCH_STATE_ITEM_NOT_EXSIST);// item í eated 
				}
			}
		}
		CollisionWithItem(dt, listItem);
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else
	{
		x += dx;
		y -= abs(dy);
	}

}
void CSimon::CollisionWithTorch(DWORD dt, vector<LPGAMEOBJECT>& listObj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(&listObj, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//// block 
	if (min_tx <= min_tx0)
		x += dx;
	if (min_ty <= min_ty0)
		y += dy;


	vector<LPGAMEOBJECT> listItem;
	for (int i = 0; i < listObj.size(); i++)
	{
		CTorch* torch = dynamic_cast<CTorch*>(listObj.at(i));// if e->obj is torch 
		if (torch->GetState() == TORCH_STATE_EXSIST) {

		}
		else
		{
			if (dynamic_cast<CItem*>(torch->GetItem())) // if e->obj->tiem is items 
			{
				CItem* item = dynamic_cast<CItem*>(torch->GetItem());
				listItem.push_back(item);
				torch->SetState(TORCH_STATE_ITEM_NOT_EXSIST);// item í eated 
			}
		}
	}
	CollisionWithItem(dt,listItem);
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}
void CSimon::CollisionWithHidenObject(DWORD dt, vector<LPGAMEOBJECT>& listObj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(&listObj, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//// block 
	if (min_tx <= min_tx0)
		x += dx;
	if (min_ty <= min_ty0)
		y += dy;
	if (nx != 0) vx = 0;
	if (ny != 0) vy = 0;

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	for (int i = 0; i < listObj.size(); i++)
	{
		CHidenObject* ohiden = dynamic_cast<CHidenObject*>(listObj.at(i));// if e->obj is torch 
		if (ohiden->GetState() == HIDENOBJECT_TYPE_DOOR)
		{
			if (ohiden->GetState() == HIDENOBJECT_TYPE_DOOR) {
				CScene* scene = CScene::GetInstance();
				scene->SetMap(1);
				scene->LoadResoure();
				scene->LoadSimon();
				break;
			}
		}
		else if (ohiden->GetState() == HIDENOBJECT_TYPE_UPSTAIR || ohiden->GetState() == HIDENOBJECT_TYPE_DOWNSTAIR)
		{
			if (isOnStair)
			{
				isOnStair = false;
				state = SIMON_ANI_IDLE;
			}
			IsCanOnStair(listObj);

		}
		else if (ohiden->GetState() == HIDENOBJECT_TYPE_FISHMAN)
		{
			CFishman::Start();
		}
		else if (ohiden->GetState() == HIDENOBJECT_TYPE_GHOST_1)
		{
			CGhost::Start();
		}
		else if (ohiden->GetState() == HIDENOBJECT_TYPE_GHOST_STOP_1)
		{
			CGhost::Stop();
		}
		else if (ohiden->GetState() == HIDENOBJECT_TYPE_GHOST_2)
		{
			//CGhost::Start();
		}
		if (ohiden->getNx() * ohiden->getNy() > 0)
		{
			_stairTrend = 1;
		}
		else
		{
			_stairTrend = 0;
		}

	}
}

void CSimon::CollisionWithEnemy(DWORD dt, vector<LPGAMEOBJECT>& listObj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	

	if (isOnStair || state == SIMON_STATE_STAND_ATTACK || state == SIMON_STATE_SIT_ATTACK)
	{
		_energy -= 2;

	}
	else {
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		// turn off collision when die 

		CalcPotentialCollisions(&listObj, coEvents);

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//// block 
		if (nx != 0) vx = nx * 0.2f;
		else
			vx = nx;
		vy = -0.2f;
		_energy -= 2;
		if ((min_tx <= min_tx0 || min_ty <= min_ty0) && _energy >0)
		{
			x += min_tx * dx + nx * 50.0f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y -= 50.0f;
		}
		

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CSimon::CollisionWithGate(DWORD dt, vector<LPGAMEOBJECT>& listObj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(&listObj, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	CGate* gate0 = dynamic_cast<CGate*>(listObj.at(0));// if e->obj is torch 

	if (gate0->GetState() == GATE_STATE_CLOSE)
	{
		if (min_tx <= min_tx0)
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (min_ty <= min_ty0)
			y += min_ty * dy + ny * 0.4f;
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		
		TransScene();
		gate0->SetState(GATE_STATE_OPEN);
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
int CSimon::IsCanOnStair(vector<LPGAMEOBJECT>& listObj)
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

		if (listObj.at(i)->GetState() == HIDENOBJECT_TYPE_UPSTAIR || listObj.at(i)->GetState() == HIDENOBJECT_TYPE_DOWNSTAIR)
		{
			listObj.at(i)->GetBoundingBox(l1, t1, r1, b1);
			rect1.left = (int)l1;
			rect1.top = (int)t1;
			rect1.right = (int)r1;
			rect1.bottom = (int)b1;
			if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
			{
				CHidenObject* ohiden = dynamic_cast<CHidenObject*>(listObj.at(i)); 
				if (ohiden->getNx() * ohiden->getNy() > 0)
				{
					_stairTrend = 1;
				}
				else
				{
					_stairTrend = 0;
				}
				auto_x = ohiden->GetAutoX();
				if (ohiden->GetState() == HIDENOBJECT_TYPE_UPSTAIR)
				{
					isCanOnStair = -1;
					return -1;
				}
				if (ohiden->GetState() == HIDENOBJECT_TYPE_DOWNSTAIR)
				{
					
					isCanOnStair = 1;
					return 1;
				}

			}
		}
	}
	auto_x = -1;
	isCanOnStair = 0;
	return 0;
}
void CSimon::AutoGo()
{
	if (auto_x < x)
	{
		nx = -1;
	}
	else if(auto_x > x)
	{
		nx = 1;
	}
}
void CSimon::TransScene()
{
	CScene* scene = CScene::GetInstance();
	CScene* scene2 = new CScene();
	if(scene->GetScene() == 1)
		scene2->SetMap(2);
	else
		scene2->SetMap(4);
	scene->TranScene(scene2->GetLeft());
	isAutoGo = true;
	auto_x = x + 100;
}
