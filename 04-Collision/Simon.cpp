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
	attack_start = 0;
	trans_start = 0;
	_heart = 5;
	isCanOnStair = 0;
	isOnStair = false;
	
	CSimon::AddAnimation(400);		//0. idle left 
	CSimon::AddAnimation(401);		//1. walk left
	CSimon::AddAnimation(402);		//2. jump left
	CSimon::AddAnimation(403);		//3. sit left
	CSimon::AddAnimation(404);		//4. stand attack
	CSimon::AddAnimation(405);		//5. sit attack
	CSimon::AddAnimation(410);		//6. trans
	CSimon::AddAnimation(406);		//7. go up
	CSimon::AddAnimation(407);		//8. go down
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (trans_start > 0) {
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
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CHidenObject*>(coObjects->at(i)))
			{
				listHideObject.push_back(coObjects->at(i));
			}
		}
		
		if (isOnStair && (state == SIMON_STATE_GO_DOWN || state == SIMON_STATE_GO_UP || state == SIMON_STATE_IDLE))
		{
			if (state == SIMON_STATE_GO_DOWN)
			{
				if (vx >= 0)
				{
					dx += 0.01f * dt;
					dy += 0.01f * dt;
				}
				else if (vx < 0)
				{
					dx -= 0.01f * dt;
					dy += 0.01f * dt;
				}
			}

			else if (state == SIMON_STATE_GO_UP)
			{
				if (vx >= 0)
				{
					dx += 0.01f * dt;
					dy -= 0.01f * dt;
				}
				else if (vx < 0)
				{
					dx -= 0.01f * dt;
					dy -= 0.01f * dt;
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
		if(listHideObject.size() > 0)
			IsCanOnStair(listHideObject);
		listHideObject.clear();
		if (state == SIMON_STATE_SIT_ATTACK || state == SIMON_STATE_STAND_ATTACK)
		{
			weapons[0]->SetPosition(x, y);
			weapons[0]->SetTrend(nx);
			weapons[0]->CollisionWithObject(dt, *coObjects);
			attack_start = GetTickCount();
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
					CTorch* torch = dynamic_cast<CTorch*>(e->obj);

					listTorch.push_back(torch);
					CollisionWithTorch(dt, listTorch, min_tx, min_ty, nx, ny);
					listTorch.clear();
				}
				else if (dynamic_cast<CBrick*>(e->obj))
				{
					CBrick* torch = dynamic_cast<CBrick*>(e->obj);

					listBrick.push_back(torch);
					CollisionWithBrick(dt, listBrick, min_tx, min_ty, nx, ny);
					listBrick.clear();
				}
				else if (dynamic_cast<CHidenObject*>(e->obj))
				{
					CHidenObject* torch = dynamic_cast<CHidenObject*>(e->obj);

					listHideObject.push_back(torch);
					CollisionWithHidenObject(dt, listHideObject, min_tx, min_ty, nx, ny);
					listHideObject.clear();
				}

			}


		/*	if (listTorch.size() > 0)
			{
				CollisionWithTorch(dt, listTorch);
			}
			if (listHideObject.size() > 0)
			{
				CollisionWithHidenObject(dt, listHideObject);
			}
			if (listBrick.size() > 0)
			{
				CollisionWithBrick(dt, listBrick, min_tx, min_ty, nx, ny);
			}
			else {
				x += dx;
				y += dy;
			}*/

		}



		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

	if (x < 0)
		x = 0;
	if (x > CMap::GetInstance()->GetWidth() - SCREEN_WIDTH / 2)
		x = CMap::GetInstance()->GetWidth() - SCREEN_WIDTH / 2;

}



void CSimon::Render()
{
	int id;
	if (state == SIMON_STATE_SIT_ATTACK)
	{
		id = SIMON_ANI_SITTING_ATTACKING;
		weapons[0]->Render();
	}
	else if (state == SIMON_STATE_STAND_ATTACK)
	{
		id = SIMON_ANI_STANDING_ATTACKING;
		weapons[0]->Render();

	}
	else if (state == SIMON_STATE_GO_UP)
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

	animations[id]->Render(x, y, nx);
	//RenderBoundingBox()

	
}

void CSimon::SetState(int state)
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
		if(vy == 0){
			vy = -SIMON_JUMP_SPEED_Y;
			vx = 0;
		}
		break;
	
	case SIMON_STATE_SIT_ATTACK:
		if (attack_start != 0)
		{
			if (GetTickCount() - attack_start >= ATTACK_TIME)
			{
				attack_start = 0;
			}

		}
		else {
			attack_start = GetTickCount();
			vx = 0;

		}
		break;
	case SIMON_STATE_SIT:
		//y = 272.0f;
		vx = 0;
		break;
	case SIMON_STATE_STAND_ATTACK:
		if (attack_start != 0)
		{
			if (GetTickCount() - attack_start >= ATTACK_TIME)
			{
				attack_start = 0;
			}

		}
		else {
			attack_start = GetTickCount();
			vx = 0;

		}
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
			vx = vy = 0;
		}
		else
		{
			isOnStair = true;
		}
		break;
	case SIMON_STATE_GO_DOWN:
		if (isOnStair)
			break;
		if (isCanOnStair != -1)
		{
			state = SIMON_STATE_IDLE;
			vx = vy = 0;
		}
		else
		{
			isOnStair = true;
		}
		break;
	}
}
void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
	left = this->x;
	top = this->y;
	right = this->x + SIMON_WIDTH;
	bottom = this->y + SIMON_HEIGHT_STAND;
	if (state == SIMON_STATE_SIT || state == SIMON_STATE_SIT_ATTACK)
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
				scene->SetMap(1);
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
				vx = vy = 0;
			}
			isCanOnStair = true;

		}
	}
}
//
//void CSimon::CollisionWithEnemy(DWORD dt, vector<LPGAMEOBJECT>& listObj)
//{
//
//}
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
				if (listObj.at(i)->GetState() == HIDENOBJECT_TYPE_UPSTAIR)
				{
					isCanOnStair = -1;
					return -1;
				}
				if (listObj.at(i)->GetState() == HIDENOBJECT_TYPE_DOWNSTAIR)
				{
					
					isCanOnStair = 1;
					return 1;
				}
			}
		}
	}
	isCanOnStair = 0;
	return 0;
}