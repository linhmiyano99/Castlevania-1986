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


CSimon* CSimon::__instance = NULL;

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

CSimon::CSimon() : CGameObject()
{
	CVampireKiller* rob = CVampireKiller::GetInstance();
	weapons.push_back(rob);
	/*CDagger* dagger = CDagger::GetInstance();
	weapons.push_back(dagger);*/
	untouchable = 0;
	trans_start = 0;
	_heart = 5;
	isCanOnStair = 0;
	isOnStair = false;
	_stairTrend = 0;
	_enegy = 20;
	isAutoGo = false;
	auto_x = -1;
	
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
	if (isAutoGo)
	{
		if (auto_x - x < 0)
			x -= 0.5;
		else
		{
			isAutoGo = false;
		}
		return;
	}
	else if (trans_start > 0)
	{
		vx = 0;
		if (GetTickCount() - trans_start > 200)
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
			listPanther.at(i)->GetPosition(p_x, p_y);
			if (abs(x - p_x) < 200 && abs(y-p_y) < 40)
				listPanther.at(i)->SetSpeed(-0.1f, -0.01f);
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
			weapons[0]->SetPosition(x, y);
			weapons[0]->SetTrend(nx);
			weapons[0]->CollisionWithObject(dt, *coObjects);
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
				if (dynamic_cast<CTorch*>(e->obj))
				{
					if (untouchable == 0)
					{
						CTorch* torch = dynamic_cast<CTorch*>(e->obj);
						if (dynamic_cast<CGhost*>(torch))
						{

							CGhost* torch = dynamic_cast<CGhost*>(e->obj);

							if (torch->GetState() == TORCH_STATE_EXSIST)
							{
								listEnemy.push_back(torch);
								CollisionWithEnemy(dt, listEnemy, min_tx, min_ty, nx, ny);
								StartUntouchable();
								listEnemy.clear();
							}
							else {
								continue;
							}

						}
						else if (dynamic_cast<CPanther*>(torch))
						{
							CPanther* torch = dynamic_cast<CPanther*>(e->obj);

							if (torch->GetState() == TORCH_STATE_EXSIST)
							{
								listEnemy.push_back(torch);
								CollisionWithEnemy(dt, listEnemy, min_tx, min_ty, nx, ny);
								StartUntouchable();
								listEnemy.clear();
							}
							else {
								continue;
							}
						}
						else {
							listTorch.push_back(torch);
							CollisionWithTorch(dt, listTorch, min_tx, min_ty, nx, ny);
							listTorch.clear();
						}
					}
				}
				else if (dynamic_cast<CBrick*>(e->obj))
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

					listGate.push_back(torch);
					CollisionWithGate(dt, listGate, min_tx, min_ty, nx, ny);
					listGate.clear();
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
		weapons[0]->Render();
	}
	else if (state == SIMON_STATE_STAND_ATTACK)
	{
		id = SIMON_ANI_STANDING_ATTACKING;
		weapons[0]->Render();

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
		nx = - nx;
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
	if (untouchable) alpha = 128;
	animations[id]->Render(x, y, nx, alpha);
	RenderBoundingBox();

	
}

void CSimon::SetState(int state)
{
	if (isAutoGo)
	{

	}
	else if (trans_start > 0) {

	}
	else if (animations[SIMON_ANI_ATTACKING]->GetCurrentFrame() > 0)
	{

	}
	else if (animations[SIMON_ANI_GO_UP]->GetCurrentFrame() > 0 && isOnStair)
	{

	}
	else if (animations[SIMON_ANI_GO_DOWN]->GetCurrentFrame() > 0 && isOnStair)
	{

	}
	/*else if (animations[SIMON_ANI_SITTING_ATTACKING]->GetCurrentFrame() > 0)
	{
		
	}*/
	else if (this->state == SIMON_STATE_SIT_ATTACK)
	{
		 this->state = SIMON_STATE_SIT;
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
			vx = 0;
			break;
		case SIMON_STATE_SIT:
			//y = 272.0f;
			vx = 0;
			break;
		case SIMON_STATE_STAND_ATTACK:
			vx = 0;
			break;
		case SIMON_STATE_ATTACK_DAGGER:
			vx = 0;
			if (_heart > 0 && weapons.size() > 1)
			{
				CDagger* dagger = CDagger::GetInstance();
				if (dagger->GetState() == DAGGER_STATE_HIDE)
				{
					dagger->SetState(DAGGER_STATE_ATTACK);
					dagger->SetPosition(x, y);
					dagger->SetTrend(nx);
					_heart--;
				}
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

				if (auto_x - x < 0)
					AutoGo();
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

				if (auto_x - x < 0)
					AutoGo();
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
		|| state == SIMON_STATE_JUMP 
		||(state == SIMON_STATE_SIT))
	{
		bottom = this->y + SIMON_HEIGHT_SIT;
	}

}

void CSimon::CollisionWithItem(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	for (int i = 0; i < listObj.size(); i++)
	{
		if (listObj.at(i)->GetState() == ITEM_STATE_EXSIST)
		{
			if (listObj.at(i)->getType() == TYPE_ITEM_WHIPUPGRADE)
			{
				CVampireKiller::GetInstance()->setUpLevel();
				listObj.at(i)->SetState(ITEM_STATE_NOT_EXSIST);
				trans_start = GetTickCount();
			}
			else if (listObj.at(i)->getType() == TYPE_ITEM_DAGGER)
			{
				CDagger* dagger = CDagger::GetInstance();
				weapons.push_back(dagger);
				listObj.at(i)->SetState(ITEM_STATE_NOT_EXSIST);

			}
			else if (listObj.at(i)->getType() == TYPE_ITEM_HEART)
			{
				_heart++;
				listObj.at(i)->SetState(ITEM_STATE_NOT_EXSIST);
			}

		}
	}
}
void CSimon::CollisionWithBrick(DWORD dt, vector<LPGAMEOBJECT>& listBrick, float min_tx0, float min_ty0, int nx0, int ny0)
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
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

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
	if (nx != 0) vx = 0;
	if (ny != 0) vy = 0;

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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
				scene->SetMap(scene->GetScene() +1);
				scene->LoadResoure();
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
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(&listObj, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//// block 
	if (min_tx <= min_tx0 || min_ty <= min_ty0)
	{
		x += min_tx * dx + nx * 50.0f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y -= 50.0f;
	}
	if (nx != 0) vx = nx * 0.2f;
	vy = -0.2f;
	state = SIMON_STATE_HURT;
	_enegy--;

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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
	}
	else
	{
		x += dx;
	}
	// clean up collision events
	

	for (int i = 0; i < listObj.size(); i++)
	{
		CGate* gate = dynamic_cast<CGate*>(listObj.at(i));// if e->obj is torch 
		if (gate->GetState() == GATE_STATE_CLOSE)
		{
			gate->SetState(GATE_STATE_OPEN);
			CScene* scene = CScene::GetInstance();
			scene->SetMap(2);
			scene->LoadResoure();
			break;
		}

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
	if (auto_x - x < 0)
	{
		nx = -1;
		isAutoGo = true;
	}
	else
	{
		isAutoGo = false;
	}
}