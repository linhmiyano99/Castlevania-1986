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
#include "Axe.h"
#include "Boongmerang.h"


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
	_energy = SIMON_MAX_ENERGY;
	isAutoGo = false;
	auto_x = -1;
	_score = 0;
	_lives = 99;
	_count = 0;
	start_stair = 0;
	isFall = false;
	isUnder = false;
	start_disappear = 0;
	start_jump = 0;
	for (int i = 0; i < 3; i++)
	{
		CWaterEffection* water = new CWaterEffection();
		list.push_back(water);
	}
	weapons[eType::DAGGER] = CDagger::GetInstance();
	weapons[eType::AXE] = CAxe::GetInstance(); 
	weapons[eType::HOLLYWATTER] = CHollyWatter::GetInstance();
	weapons[eType::BOONGMERANG] = CBoongmerang::GetInstance();
	
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
	CSimon::AddAnimation(409);		//10. idle up
	CSimon::AddAnimation(410);		//11. idle down
	CSimon::AddAnimation(411);		//12. die
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (die_start != 0)
	{

		if (GetTickCount() - die_start > DIE_TIME)
		{
			if (_lives > 0)
			{
				Sound::GetInstance()->Play(eSound::musicStage1);
				_lives--;
				_energy = SIMON_MAX_ENERGY;
			
				CScene::GetInstance()->ResetScene();
				untouchable_start = 0;
				untouchable = 0;
				die_start = 0;
				isFall = false;
				isUnder = false;
				isAutoGo = false;
				isOnStair = false;
				start_jump = 0;
				start_stair = 0;
				if (CBoard::GetInstance()->GetWeapon() != 0)
				{
					if (CBoard::GetInstance()->GetNumberOfWeapon() == 2)
					{
						CBoard::GetInstance()->SetWeapon(0);
					}
					else if (CBoard::GetInstance()->GetNumberOfWeapon() == 3)
					{
						CBoard::GetInstance()->SetWeapon(2);
					}
					else
					{
						CBoard::GetInstance()->SetWeapon(0);
					}
				}
				x = start_x;
				y = start_y;
			}
			else
			{

				return;

			}
			state = SIMON_STATE_IDLE;
			weapons[eType::VAMPIREKILLER]->Reset();

			return;
		}
	}
	if (die_start == 0 &&(_energy <= 0 || (y > WATTER_Y + 85)))
	{
		Sound::GetInstance()->Play(eSound::musicLifeLost);
		Sound::GetInstance()->Stop(eSound::musicStage1);
		die_start = GetTickCount();
		attack_start = 0;
		trans_start = 0;
		state = SIMON_STATE_DIE;
		isOnStair = false;
		vx = 0;
		if ((y > WATTER_Y + 80))
			Sound::GetInstance()->Play(eSound::soundFallingDownWaterSurface);
	}
	if (start_stair > 0)
	{
		if (GetTickCount() - start_stair > TIME_FOR_PER_STEP)
		{
			start_stair = 0;
			if (IsOnStair()) {
				if ((_stairTrend == 0 && nx == 1) || (_stairTrend == 1 && nx == -1))
					SetState(SIMON_STATE_IDLE_UP);
				else
					SetState(SIMON_STATE_IDLE_DOWN);
			}
		}
	}
	if (attack_start > 0)
	{
		if (GetTickCount() - attack_start < ATTACK_TIME)
		{
		}
		else if (GetTickCount() - attack_start < ATTACK_TIME_WAIT)
		{
			if (state == SIMON_STATE_SIT_ATTACK || state == SIMON_STATE_SIT)
			{
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
	if (start_disappear > 0)
	{
		if (GetTickCount() - start_disappear > SIMON_DISAPPEAR_TIME)
		{
			start_disappear = 0;
		}
	}

	if (isAutoGo && !CScene::GetInstance()->IsTranScene() && !CScene::GetInstance()->IsOutSide())
	{
		if (IsFall(dt))
			return;
		AutoGo();
		if (abs(auto_x - x) > 0.5f)
		{
			x += 0.5 * nx;
		}
		else
		{

			isAutoGo = false;
			if (isCanOnStair == 1)
			{
				nx = -nx;
				new_y = y - PER_STEP;
				if (_stairTrend == 0)
					new_x = x + PER_STEP;
				else
					new_x = x - PER_STEP;
			}
			else
			{
				state = SIMON_STATE_GO_DOWN;
				new_y = y + PER_STEP;
				if (_stairTrend == 0)
					new_x = x - PER_STEP;
				else
					new_x = x + PER_STEP;
			}
			animations[SIMON_ANI_GO_UP]->ResetFrame();
			animations[SIMON_ANI_GO_DOWN]->ResetFrame();
		}
	}
	else if (isAutoGo && !CScene::GetInstance()->IsTranScene() && CScene::GetInstance()->IsOutSide() && !isOnStair)
	{
		if (IsFall(dt))
			return;
		AutoGo();
		if (abs(auto_x - x) > 0.5f)
		{
			x += 0.5 * nx;
		}
		else
		{
			isAutoGo = false;
			CScene::GetInstance()->GoInside();
			CScene::GetInstance()->SetMap(1);
			CScene::GetInstance()->LoadResoure();
			CScene::GetInstance()->LoadSimon();
		}
		return;
	}
	
	else if (isAutoGo && CScene::GetInstance()->IsTranScene())
	{
		if (IsFall(dt))
			return;
		AutoGo();
		state = SIMON_STATE_WALKING_RIGHT;
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
		if (!IsFall(dt))
		{
			vx = 0;
			if (GetTickCount() - trans_start > SIMON_STRANS_TIME)
			{
				trans_start = 0;
			}
			return;
		}
	}
	else {
		if (y > WATTER_Y && !isFall)
		{
			isFall = true;
			ResetWater();
		}
		if (isFall)
		{
			for each (CWaterEffection * var in list)
			{
				var->Update(dt);
			}
		}
		if (start_jump > 0)
		{
			if (state == SIMON_STATE_ATTACK_DAGGER || state == SIMON_STATE_STAND_ATTACK)
			{
				start_jump = 0;

			}
			else if (GetTickCount() - start_jump > SIMON_TIME_START_JUMP)
			{
				start_jump = 0;
			}
			else if (GetTickCount() - start_jump > SIMON_TIME_STATE_JUMP)
			{
				state = SIMON_STATE_IDLE;

			}
			else
			{
				state = SIMON_STATE_JUMP;
			}
		}

		
		vector<LPGAMEOBJECT> listBrick;
		vector<LPGAMEOBJECT> listHideObject;
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CHidenObject*>(coObjects->at(i)) 
				&& (coObjects->at(i)->GetState() == eType::STAIR_DOWN 
					|| coObjects->at(i)->GetState() == eType::STAIR_UP))
			{
				listHideObject.push_back(coObjects->at(i));
			}
			else if (dynamic_cast<CBrick*>(coObjects->at(i)))
			{
				listBrick.push_back(coObjects->at(i));
			}
		}

		
		if (isOnStair)
		{
			if (start_stair > 0 && GetTickCount() - start_stair < 200)
			{
				if (state == SIMON_STATE_GO_DOWN)
				{
					if (_stairTrend == 0)
					{
						nx = -1;
						dx = -SIMON_SPEED_ON_STAIR;
						dy = SIMON_SPEED_ON_STAIR;
					}
					else
					{
						nx = 1;
						dx = SIMON_SPEED_ON_STAIR;
						dy = SIMON_SPEED_ON_STAIR;
					}
				}
				else if (state == SIMON_STATE_GO_UP)
				{
					if (_stairTrend == 0)
					{
						nx = 1;
						dx = SIMON_SPEED_ON_STAIR;
						dy = -SIMON_SPEED_ON_STAIR;
					}
					else
					{
						nx = -1;
						dx = -SIMON_SPEED_ON_STAIR;
						dy = -SIMON_SPEED_ON_STAIR;
					}
				}
				else
				{
					dx = 0;
					dy = 0;
				}
			}
			else
			{
				
				if (isCanOnStair == 0)
				{
					if (x != new_x || y != new_y)
					{
						dx = 0;
						dy = 0;
						
					}
				}
				int tem_x = x, tem_y = y;
				x = new_x;
				y = new_y;
				if (listHideObject.size() > 0)
					IsCanOnStair(listHideObject);
				if (isCanOnStair != 0)
				{
					if (isCanOnStair == 1)
					{
						x = tem_x;
						y = tem_y;
					}
					else
					{
						
					}
					isOnStair = false;
					vx = vy = 0;
				}
			
			}
		}
		else {
			CGameObject::Update(dt);
			if (start_jump > 0 && attack_start == 0)
			{
				vy += 0.2 * SIMON_GRAVITY * dt;
			}
			else if(attack_start > 0 && GetTickCount() - attack_start < ATTACK_TIME)
			{

			}
			else
			{
				vy += SIMON_GRAVITY * dt;

			}
		}
	
		if (listHideObject.size() > 0)
			IsCanOnStair(listHideObject);

		if (state == SIMON_STATE_SIT_ATTACK || state == SIMON_STATE_STAND_ATTACK)
		{
			weapons[eType::VAMPIREKILLER]->SetPosition(x, y);
			weapons[eType::VAMPIREKILLER]->SetTrend(nx);
			weapons[eType::VAMPIREKILLER]->CollisionWithObject(dt, *coObjects);
		}
		else if (_heart > 0 && state == SIMON_STATE_ATTACK_DAGGER )
			switch ( CBoard::GetInstance()->GetWeapon())
			{
			case  eType::DAGGER:
				if (weapons[eType::DAGGER]->GetState() == DAGGER_STATE_HIDE) 
				{
					weapons[eType::DAGGER]->SetPosition(x, y);
					weapons[eType::DAGGER]->SetTrend(nx);
					weapons[eType::DAGGER]->SetState(DAGGER_STATE_ATTACK);
					_heart--;
				}
				break;
			case eType::ITEMAXE:
				if (weapons[eType::AXE]->GetState() == DAGGER_STATE_HIDE && dynamic_cast<CAxe*>(weapons[eType::AXE])->IsCanAttack())
				{
					weapons[eType::AXE]->SetPosition(x, y);
					weapons[eType::AXE]->SetTrend(nx);
					weapons[eType::AXE]->SetState(DAGGER_STATE_ATTACK);
				}
				break;
			case eType::ITEMHOLLYWATTER:
				if (weapons[eType::HOLLYWATTER]->GetState() == DAGGER_STATE_HIDE)
				{
					weapons[eType::HOLLYWATTER]->SetPosition(x, y);
					weapons[eType::HOLLYWATTER]->SetTrend(nx);
					weapons[eType::HOLLYWATTER]->SetState(DAGGER_STATE_ATTACK);
					_heart--;
				}
				break;
			case eType::ITEMBOONGMERANG:
				if (weapons[eType::BOONGMERANG]->GetState() == DAGGER_STATE_HIDE)
				{
					weapons[eType::BOONGMERANG]->SetPosition(x, y);
					weapons[eType::BOONGMERANG]->SetTrend(nx);
					weapons[eType::BOONGMERANG]->SetState(DAGGER_STATE_ATTACK);
					_heart--;
				}
				break;
			default:
				break;
			}
			


		// Calculate dx, dy 

		// Simple fall down

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 
		if (state != SIMON_STATE_DIE)
		{
			CalcPotentialCollisions(coObjects, coEvents);


			// reset untouchable timer if untouchable time has passed
			if (untouchable_start)
			{
				if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
				{
					untouchable_start = 0;
					untouchable = 0;
				}
				else if (GetTickCount() - untouchable_start < SIMON_HURT_TIME && untouchable == 1)
				{
					if (!isOnStair)
					{
						/*if (attack_start > 0)
						{
							animations[SIMON_ANI_STANDING_ATTACKING]->ResetFrame();
							animations[SIMON_ANI_SITTING_ATTACKING]->ResetFrame();
							attack_start = 0;
						}*/

						state = SIMON_STATE_HURT;
					}
				}
				else
				{
					if (!isOnStair)
					{
						/*if (attack_start > 0)
						{
							animations[SIMON_ANI_STANDING_ATTACKING]->ResetFrame();
							animations[SIMON_ANI_SITTING_ATTACKING]->ResetFrame();
							attack_start = 0;
						}*/
						if (attack_start > 0 && GetTickCount() - attack_start < ATTACK_TIME)
							vy += SIMON_GRAVITY * dt;
					}
					if (_energy <= 0)
					{
						state = SIMON_STATE_DIE;
						isOnStair = false;
					}
				}
			}
			listHideObject.clear();

			// No collision occured, proceed normally
			if (coEvents.size() == 0)
			{
				if (state == SIMON_STATE_JUMP)
				{
					x += dx * 1.1f;
				}
				else
				{
					x += dx;
				}
				y += dy;
				RECT rect, rect1;
				float l, t, r, b;
				float l1, t1, r1, b1;

				GetBoundingBox(l, t, r, b);
				rect.left = (int)l;
				rect.top = (int)t;
				rect.right = (int)r;
				rect.bottom = (int)b;
				for (int i = 0; i < coObjects->size(); i++)
				{

					if (dynamic_cast<CTorch*>(coObjects->at(i)) && coObjects->at(i)->GetState() == TORCH_STATE_ITEM)
					{

						CTorch *torch = dynamic_cast<CTorch*>(coObjects->at(i));
						torch->GetBoundingBox(l1, t1, r1, b1);
						rect1.left = (int)l1;
						rect1.top = (int)t1;
						rect1.right = (int)r1;
						rect1.bottom = (int)b1;
						if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
						{
							if (dynamic_cast<CItem*>(torch->GetItem()))
							{
								LPGAMEOBJECT item = torch->GetItem();
								CollisionWithItem(dt, item);
								item = NULL;
							}
						}
						torch = NULL;
					}
					else if (dynamic_cast<CBoss*>(coObjects->at(i)) && coObjects->at(i)->GetState() == BOSS_STATE_ITEM)
					{
						CBoss* torch = dynamic_cast<CBoss*>(coObjects->at(i)); torch->GetBoundingBox(l1, t1, r1, b1);
						rect1.left = (int)l1;
						rect1.top = (int)t1;
						rect1.right = (int)r1;
						rect1.bottom = (int)b1;
						if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
						{
							if (dynamic_cast<CItem*>(torch->GetItem()))
							{
								LPGAMEOBJECT item = torch->GetItem();
								CollisionWithItem(dt, item);
								item = NULL;
							}
						}
						torch = NULL;
					}
				}
			}
			else
			{
				/*if (state == SIMON_STATE_JUMP)
				{
					if (GetTickCount() - start_jump > SIMON_TIME_STATE_JUMP)
					{
						start_jump = 0;
						state = SIMON_STATE_IDLE;
					}
				}*/
				float min_tx, min_ty, nx = 0, ny;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<CBrick*>(e->obj))
					{
						if (!isOnStair) {
							CollisionWithBrick(dt, e->obj, min_tx, min_ty, nx, ny);
						}
						else
						{
							x += dx;
							y += dy;
						}
					}
					else if (dynamic_cast<CHidenObject*>(e->obj))
					{
						if( dynamic_cast<CHidenObject*>(e->obj)->GetState() == eType::OBJECT_HIDDEN_PANTHER_JUMP)
						{
							x += dx;

							if (isOnStair)
							{
								y += dy;
							}
						}
						else
							CollisionWithHidenObject(dt, e->obj, min_tx, min_ty, nx, ny);
					}
					else if (dynamic_cast<CGate*>(e->obj))
					{
						if (CGate::IsStart())
						{
							CollisionWithGate(dt, e->obj, min_tx, min_ty, nx, ny);
						}
					}
					else if (dynamic_cast<CItem*>(e->obj))
					{
	
						CollisionWithItem(dt, e->obj);
						
					}
					else if (dynamic_cast<CTorch*>(e->obj))
					{ 
						if (!(untouchable_start || start_disappear))
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
											CollisionWithEnemy(dt, e->obj, min_tx, min_ty, nx, ny);

											if (state == SIMON_STATE_SIT || state == SIMON_STATE_SIT_ATTACK)
											{
												y -= 15;
											}
											if (attack_start > 0)
											{
												y -= 50;
											}
											StartUntouchable();
										}
										/*else
										{
											x += dx;
											y += dy;
										}*/
									}
									else
									{
										if (dynamic_cast<CItem*>(torch->GetItem()))
										{
											LPGAMEOBJECT item = torch->GetItem();
											CollisionWithItem(dt, item);
											item = NULL;
										}
									}
									boss = NULL;
								}
								else {
									if ((torch->GetState() == TORCH_STATE_EXSIST))
									{
										if (untouchable == 0)
										{
											CollisionWithEnemy(dt, e->obj, min_tx, min_ty, nx, ny);
											if (dynamic_cast<CBat*>(torch))
											{
												CBat* bat = dynamic_cast<CBat*>(e->obj);
												bat->SetState(TORCH_STATE_NOT_EXSIST);
												bat = NULL;
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
												panther = NULL;

											}
											if (state == SIMON_STATE_SIT || state == SIMON_STATE_SIT_ATTACK)
											{
												y -= 15;
											}
											if (attack_start > 0)
											{
												y -= 50;
											}
											StartUntouchable();
										}
										/*else
										{
											x += dx;
											if (y < _ground)
												y += dy;
										}*/
									}
									else {
										if (dynamic_cast<CItem*>(torch->GetItem()))
										{
											LPGAMEOBJECT item = torch->GetItem();
											CollisionWithItem(dt, item);
											item = NULL;
										}
									}
								}
								break;
							}
							else {
								CollisionWithTorch(dt, e->obj, min_tx, min_ty, nx, ny);
							}
							torch = NULL;

						}
						else
						{
							float o_x, o_y;
							e->obj->GetPosition(o_x, o_y);
							x += dx;
							if (y + SIMON_HEIGHT_STAND <= o_y)
								y += dy;
							break;
						}
					}
					else 
					{
						break;
					}
					

				}
			}
			// clean up collision events
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
			
			listBrick.clear();
			listHideObject.clear();
		}
		else
		{
			CalcPotentialCollisions(&listBrick, coEvents);
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
			listBrick.clear();
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

		}

		if (x < CScene::GetInstance()->GetLeft())
			x = CScene::GetInstance()->GetLeft();
		if (x > CScene::GetInstance()->GetRight())
			x = CScene::GetInstance()->GetRight();

	}
}
void CSimon::Render()
{
	int id;
	
	if (isAutoGo)
	{
		if (CScene::GetInstance()->IsTranScene())
		{
			/*
				int id = nextScenceObj->getID()
				CScence *s = CSceneManager::GetScene(id);
				int left = s->getStartX();

			*/
			if(state == SIMON_STATE_WALKING_RIGHT)
				id = SIMON_ANI_WALKING;
			else
				id = SIMON_ANI_IDLE;
		}
		else
			id = SIMON_ANI_WALKING;
	}
	else if (state == SIMON_STATE_DIE)
	{
		id = SIMON_ANI_DIE;
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
		weapons[eType::VAMPIREKILLER]->Render();
	}
	else if (state == SIMON_STATE_STAND_ATTACK)
	{
		id = SIMON_ANI_STANDING_ATTACKING;
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
		if (start_jump > 0)
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
	if ( untouchable 
		&&( isOnStair || GetTickCount() - untouchable_start > SIMON_HURT_TIME) 
		&&(die_start == 0)) alpha = 128;
	if (start_disappear)
	{
		alpha = (GetTickCount() - start_disappear) / 1000 * 50;
	}
	animations[id]->Render(x, y, nx, alpha);
	//RenderBoundingBox();
	if (isFall)
	{
		for each (CWaterEffection * var in list)
		{
			var->Render();
		}
	}
	
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
	else if (die_start > 0) {

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
	else if (state == SIMON_STATE_JUMP)
	{
		if (!start_jump)
		{
			if (y < _ground + 1 && y > _ground -1 && !untouchable) {
				vy = -SIMON_JUMP_SPEED_Y;
				start_jump = GetTickCount();
				if (this->state == SIMON_STATE_IDLE)
					vx = 0;
			}
		}
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
		case SIMON_STATE_SIT_ATTACK:
			attack_start = GetTickCount();
			Sound::GetInstance()->Play(eSound::soundWhip);
			animations[SIMON_ANI_SITTING_ATTACKING]->ResetFrame();
			weapons[eType::VAMPIREKILLER]->GetAnimation()->ResetFrame();
			vx = 0;
			break;
		case SIMON_STATE_SIT:
			//y = 272.0f;
			vx = 0;
			break;
		case SIMON_STATE_STAND_ATTACK:
			attack_start = GetTickCount();
			Sound::GetInstance()->Play(eSound::soundWhip);
			animations[SIMON_ANI_STANDING_ATTACKING]->ResetFrame();
			weapons[eType::VAMPIREKILLER]->GetAnimation()->ResetFrame();
			vx = 0;
			break;
		case SIMON_STATE_ATTACK_DAGGER:
			attack_start = GetTickCount();
			vx = 0;
			if (_heart > 0 && (CBoard::GetInstance()->GetWeapon() != 0))
			{
				switch (CBoard::GetInstance()->GetWeapon())
				{
				case eType::DAGGER:
					if (CDagger::GetInstance()->GetState() == DAGGER_STATE_ATTACK)
					{
						this->state = SIMON_STATE_IDLE;
					}
					else
					{
						Sound::GetInstance()->Play(eSound::soundDagger);
					}
					break;	
				case eType::ITEMAXE:
					if (CAxe::GetInstance()->GetState() == DAGGER_STATE_ATTACK || !CAxe::GetInstance()->IsCanAttack())
					{
						this->state = SIMON_STATE_IDLE;
					}
					else
					{
						Sound::GetInstance()->Play(eSound::soundAxe);
					}
					break;
				case eType::ITEMHOLLYWATTER:
					if (CHollyWatter::GetInstance()->GetState() == DAGGER_STATE_ATTACK)
					{
						this->state = SIMON_STATE_IDLE;
					}
					else
					{
						Sound::GetInstance()->Play(eSound::soundHolyWater);
					}
					break;
				case eType::ITEMBOONGMERANG:
					if (CBoongmerang::GetInstance()->GetState() == DAGGER_STATE_ATTACK)
					{
						this->state = SIMON_STATE_IDLE;
					}
					else
					{
						Sound::GetInstance()->Play(eSound::soundBoomerang);
					}
					break;

				default:
					this->state = SIMON_STATE_IDLE;
					break;
				}
				animations[SIMON_ANI_STANDING_ATTACKING]->ResetFrame();
			}
			else
			{
				this->state = SIMON_STATE_IDLE;

			}
			break;
		case SIMON_STATE_UP:
			y -= 15;

		case SIMON_STATE_IDLE:
			vx = 0;
			break;
		case SIMON_STATE_GO_UP:
			if (isOnStair)
			{
				if (start_stair == 0)
				{
					start_stair = GetTickCount();
					if (!isUnder)
					{
						new_y = y - PER_STEP;
						if (_stairTrend == 0)
							new_x = x + PER_STEP;
						else
							new_x = x - PER_STEP;
					}
					else
					{
						new_y = y;
						new_x = x + 100;
						isUnder = false;
						CBat::Start();
					}
				}
				break;
			}
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
			{
				if (start_stair == 0)
				{
					start_stair = GetTickCount();
					if (!isUnder)
					{
						new_y = y + PER_STEP;
						if (_stairTrend == 0)
							new_x = x - PER_STEP;
						else
							new_x = x + PER_STEP;
					}
					else
					{
						new_y = y;
						new_x = x - 100;
						isUnder = false;
						CBat::Stop();
					}
				}
				break;
			}

			if (isCanOnStair != -1)
			{
				this->state = SIMON_STATE_SIT;
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
	if (state == SIMON_STATE_DIE)
	{
		right = this->x + SIMON_WIDTH_DIE;
		bottom = this->y + SIMON_HEIGHT_DIE;
	}
	else if ((state == SIMON_STATE_GO_DOWN && isCanOnStair != -1) 
		|| state == SIMON_STATE_SIT_ATTACK  
		||(state == SIMON_STATE_SIT) 
		|| (start_jump > 0 && GetTickCount() - start_jump <= SIMON_TIME_STATE_JUMP))
	{
		bottom = this->y + SIMON_HEIGHT_SIT;
	}

}

void CSimon::CollisionWithItem(DWORD dt, LPGAMEOBJECT& Obj)
{

	if ((Obj->GetState() == ITEM_STATE_EXSIST && Obj->GetType() != eType::BOSS) 
		|| (Obj->GetState() == BOSS_STATE_ITEM && Obj->GetType() == eType::BOSS))
	{
		switch (Obj->GetType())
		{
		case eType::WHIPUPGRADE:
			Sound::GetInstance()->Play(eSound::soundCollectWeapon);
			CVampireKiller::GetInstance()->setUpLevel();
			trans_start = GetTickCount();
			break;
		case eType::DAGGER:
			Sound::GetInstance()->Play(eSound::soundCollectWeapon);
			weapons[eType::DAGGER] = CDagger::GetInstance();
			CBoard::GetInstance()->SetWeapon(eType::DAGGER);
			break;
		case eType::ITEMAXE:
			Sound::GetInstance()->Play(eSound::soundCollectWeapon);
			weapons[eType::AXE] = CAxe::GetInstance();
			CBoard::GetInstance()->SetWeapon(eType::ITEMAXE);
			break;
		case  eType::ITEMHOLLYWATTER:
			Sound::GetInstance()->Play(eSound::soundCollectWeapon);
			weapons[eType::HOLLYWATTER] = CHollyWatter::GetInstance();
			CBoard::GetInstance()->SetWeapon(eType::ITEMHOLLYWATTER);
			break;
		case  eType::ITEMBOONGMERANG:
			Sound::GetInstance()->Play(eSound::soundCollectWeapon);
			weapons[eType::HOLLYWATTER] = CBoongmerang::GetInstance();
			CBoard::GetInstance()->SetWeapon(eType::ITEMBOONGMERANG);
			break;
		case eType::ITEMVASE:
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			Disappear();
			break;
		case eType::ITEMCROSS:
			CScene::GetInstance()->KillAllEnemy();
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			break;
		case eType::HEART:
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			_heart += 5;
			break;
		case eType::SMALLHEART:
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			_heart++;
			break;
		case eType::MONEY_1:
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			_score += 100;
			break;
		case eType::MONEY_2:
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			_score += 400;
			break;
		case eType::MONEY_3:
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			_score += 700;
			break;
		case eType::MONEY_4:
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			_score += 1000;
			break;
		case eType::MONEY_5:
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			_score += 1000;
			break;
		case eType::ITEMII:
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			CBoard::GetInstance()->SetNumberOfWeapon(2);
			break;
		case eType::ITEMIII:
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			CBoard::GetInstance()->SetNumberOfWeapon(3);
			break;
		case eType::CHICKEN:
			Sound::GetInstance()->Play(eSound::soundCollectItem);
			_energy = SIMON_MAX_ENERGY;
			break;
		default:
			break;
		}

		if (Obj->GetType() == eType::BOSSBALL)
		{
			Obj->SetState(BOSS_STATE_ITEM_NOT_EXSIST);
			CBoard::GetInstance()->Stop();
			CGate::Start();
			Sound::GetInstance()->Stop(eSound::musicStage1);
			Sound::GetInstance()->Stop(eSound::music_Boss);
		}
		else
			Obj->SetState(ITEM_STATE_NOT_EXSIST);

	}
}
void CSimon::CollisionWithBrick(DWORD dt, LPGAMEOBJECT &Obj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	float b_x, b_y;
	Obj->GetPosition(b_x, b_y);
	if (b_y + BRICK_WIDTH >= y)
	{
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();


		vector<LPGAMEOBJECT> listObj;
		listObj.push_back((LPGAMEOBJECT)(Obj));

		// turn off collision when die 

		CalcPotentialCollisions(&listObj, coEvents);

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//// block 
		if (min_tx <= min_tx0)
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		
		if (nx != 0) vx = 0;
		if (ny < 0)
		{
			if (!untouchable)
			{
				vy = 0;
			}
			_ground = y;

			if (start_jump > 0)
			{
				start_jump = 0;

			}
			
		}
		if (min_ty <= min_ty0)
			y += min_ty * dy + ny * 0.4f;
		if (state == SIMON_STATE_DIE)
		{
			vy = 0;
		}
		// clean up collision events

		CTorch* torch = dynamic_cast<CTorch*>(Obj);// if e->obj is torch 
		if (torch->GetState() == TORCH_STATE_EXSIST) {

		}
		else
		{
			if (dynamic_cast<CItem*>(torch->GetItem())) // if e->obj->tiem is items 
			{
				LPGAMEOBJECT item = torch->GetItem();
				CollisionWithItem(dt, item);
				item = NULL;
			}
		}

	
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		/*if ((state == SIMON_STATE_JUMP || state == SIMON_STATE_SIT || state == SIMON_STATE_SIT_ATTACK) && untouchable == 1)
		{
			y -= 15;
		}*/
	}
	else
	{
		x += dx;
		y -= abs(dy);
	}
	//if (start_jump > 0)
	//{
	//	start_jump = 0;
	//	state = SIMON_STATE_IDLE;
	//}

}
void CSimon::CollisionWithTorch(DWORD dt, LPGAMEOBJECT &Obj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> listObj;
	listObj.push_back((LPGAMEOBJECT)(Obj));

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
	CTorch* torch = dynamic_cast<CTorch*>(Obj);// if e->obj is torch 
	if (torch->GetState() == TORCH_STATE_EXSIST) {

	}
	else
	{
		if (dynamic_cast<CItem*>(torch->GetItem())) // if e->obj->tiem is items 
		{
			LPGAMEOBJECT item = torch->GetItem();
			CollisionWithItem(dt, item);
			item = NULL;
		}
	}

	
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CSimon::CollisionWithHidenObject(DWORD dt, LPGAMEOBJECT& Obj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	vector<LPGAMEOBJECT> listObj;
	listObj.push_back((LPGAMEOBJECT)(Obj));

	CalcPotentialCollisions(&listObj, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//// block 


	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CHidenObject* ohiden = dynamic_cast<CHidenObject*>(listObj.at(0));
	if (ohiden->GetState() == eType::OBJECT_HIDDEN_BRICK)
	{
		if (min_tx <= min_tx0)
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (min_ty <= min_ty0)
			y += min_ty * dy + ny * 0.4f;
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
	else {
		
		if (isOnStair)
		{
			if (ohiden->GetState() == eType::STAIR_UP || ohiden->GetState() == eType::STAIR_DOWN)
			{	
				isOnStair = false;
				state = SIMON_ANI_IDLE;
				if (min_tx <= min_tx0)
					x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				if (min_ty <= min_ty0)
					y += min_ty * dy + ny * 0.4f;
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				state = SIMON_STATE_IDLE;
				y -= 5;
			}
			IsCanOnStair(listObj);
		}
		else {
			if (min_tx <= min_tx0)
				x += dx;
			if (min_ty <= min_ty0)
				y += dy;
			if (ohiden->GetState() == eType::OBJECT_HIDDEN_DOOR)
			{

				auto_x = x + 30;
				isAutoGo = true;
				
			}
			else if (ohiden->GetState() == eType::OBJECT_HIDDEN_GATE_OPEN)
			{
				CGate::Start();
				CBat::Stop();
			}
			else if (ohiden->GetState() == eType::OBJECT_HIDDEN_FISHMAN)
			{
				CFishman::Start();
			}
			else if (ohiden->GetState() == eType::OBJECT_HIDDEN_GHOST_1)
			{
				CGhost::Start();
			}
			else if (ohiden->GetState() == eType::OBJECT_HIDDEN_GHOST_STOP_1)
			{
				CGhost::Stop();
				CFishman::Stop();
				CBat::Start();
			}
			else if (ohiden->GetState() == eType::OBJECT_HIDDEN_GHOST_2)
			{
				//CGhost::Start();
			}
			else if (ohiden->GetState() == eType::OBJECT_HIDDEN_MONEY)
			{
				CItemMoney::Start();
			}
			else if (ohiden->GetState() == eType::OBJECT_HIDDEN_RESET_PANTHER)
			{
				CPanther::StartReset();
			}
			else if (ohiden->GetState() == eType::OBJECT_HIDDEN_STOP_RESET_PANTHER)
			{
				CPanther::StopReset();
			}

			if (ohiden->getNx() * ohiden->getNy() > 0)
			{
				_stairTrend = 1;
			}
			else if(ohiden->getNx() * ohiden->getNy() < 0)
			{
				_stairTrend = 0;
			}
			else
			{
				_stairTrend = -1;
			}
		}
	}
	ohiden = NULL;
}

void CSimon::CollisionWithEnemy(DWORD dt, LPGAMEOBJECT& Obj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	

	if (isOnStair || state == SIMON_STATE_STAND_ATTACK || state == SIMON_STATE_SIT_ATTACK)
	{
		_energy -= ONE_HIT;

	}
	else {
		if (attack_start > 0)
		{
			animations[SIMON_ANI_STANDING_ATTACKING]->ResetFrame();
			animations[SIMON_ANI_SITTING_ATTACKING]->ResetFrame();
			weapons[eType::VAMPIREKILLER]->GetAnimation()->ResetFrame();
			attack_start = 0;
		} 
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		// turn off collision when die 
		vector<LPGAMEOBJECT> listObj;
		listObj.push_back((LPGAMEOBJECT)(Obj));

		CalcPotentialCollisions(&listObj, coEvents);

		float min_tx, min_ty, nx1 = 0, ny1;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx1, ny1);

		float _x, _y;
		Obj->GetPosition(_x, _y);
		if (_x > x)
			nx = -1;
		else
			nx = 1;
		//// block 
		vx = nx * SIMON_WALKING_SPEED;
		vy = -SIMON_JUMP_SPEED_Y;
		_energy -= ONE_HIT;
		start_jump = 0;
		

		state = SIMON_STATE_HURT;
		attack_start = 0;
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	if (_energy <= 0)
	{
		Sound::GetInstance()->Play(eSound::musicLifeLost);
		Sound::GetInstance()->Stop(eSound::musicStage1);
		_energy = 0;
		die_start = GetTickCount();
		vx = vy = 0;
		state = SIMON_STATE_DIE;
		isOnStair = false;
	}
}

void CSimon::CollisionWithGate(DWORD dt, LPGAMEOBJECT& Obj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	Sound::GetInstance()->Play(eSound::soundOpenDoor);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> listObj;
	listObj.push_back((LPGAMEOBJECT)(Obj));

	// turn off collision when die 

	CalcPotentialCollisions(&listObj, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	CGate* gate0 = dynamic_cast<CGate*>(Obj);// if e->obj is torch 

	if (gate0->GetState() == GATE_STATE_CLOSE)
	{
		if (min_tx <= min_tx0)
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (min_ty <= min_ty0)
			y += min_ty * dy + ny * 0.4f;
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		gate0->ResetGate();
		TransScene();
		gate0->SetState(GATE_STATE_OPEN);
		//SetStart(CScene::GetInstance()->GetLeft(), 0);
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	gate0 = NULL;
	state = SIMON_STATE_IDLE;
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
		if (listObj.at(i)->GetState() == eType::STAIR_UP || listObj.at(i)->GetState() == eType::STAIR_DOWN)
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
				if (ohiden->GetState() == eType::STAIR_UP)
				{
					isCanOnStair = -1;
					return -1;
				}
				if (ohiden->GetState() == eType::STAIR_DOWN)
				{
					
					isCanOnStair = 1;
					return 1;
				}
				ohiden = NULL;

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
	CScene::GetInstance()->TranScene();
	isAutoGo = true;
	auto_x = x + 100;
}
void CSimon::HeartDown()
{
	if (GetTickCount() - _count >= TIME_RATE_END_GAME)
	{
		_count = GetTickCount();
		_score += 100;
		_heart--;
	}
}
void CSimon::UpEnergy()
{
	if (GetTickCount() - _count >= TIME_RATE_END_GAME)
	{
		_count = GetTickCount();
		_energy++;
	}
}
void CSimon::ResetWater()
{
	list[0]->SetPosition(x, y + SIMON_HEIGHT_STAND / 3);
	list[1]->SetPosition(x + WATTER_WIDTH, y + SIMON_HEIGHT_STAND);
	list[2]->SetPosition(x + WATTER_WIDTH * 2, y + SIMON_HEIGHT_STAND / 3);
}
void CSimon::StartHurt(float _x, float _y)
{
	if (untouchable_start > 0)
		return;
	_energy -= ONE_HIT;
	if (!isOnStair)
	{
		if (_x > x)
			nx = -1;
		else
			nx = 1;
		vx = nx * SIMON_WALKING_SPEED;
		vy = -SIMON_JUMP_SPEED_Y;
		state = SIMON_STATE_HURT;
		attack_start = 0;
	}
	if (_energy <= 0)
	{
		Sound::GetInstance()->Play(eSound::musicLifeLost);
		Sound::GetInstance()->Stop(eSound::musicStage1);
		_energy = 0;
		die_start = GetTickCount();
		vx = vy = 0;
		state = SIMON_STATE_DIE;
		isOnStair = false;
	}

	StartUntouchable();
}
void CSimon::SetDownEnerGy()
{
	if (_energy == SIMON_MAX_ENERGY)
		_energy = ONE_HIT; 
	else _energy = SIMON_MAX_ENERGY;
}
void CSimon::GoFast()
{
	if (x < CScene::GetInstance()->GetRight() - 500) // dịch chuyển simon sang phải 500 đơn vị
		x += 500;
}
bool CSimon::IsFall(DWORD dt)
{
	if (y < _ground)
	{
		vy += GRAVITY * dt;
		y += vy * dt;
		return true;
	}
	y = _ground;
	vy = 0;
	return false;
}