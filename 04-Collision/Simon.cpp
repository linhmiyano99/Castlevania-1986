#include "Simon.h"
#include "Torch.h"
#include "WhipUpgrade.h"
#include "Game.h"
#include "VampireKiller.h"
#include "ItemDagger.h"
#include "Brick.h"
#include "Dagger.h"


CSimon* CSimon::__instance = NULL;

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (trans_start > 0) {
		vx = 0;
	}
	else {
		// Calculate dx, dy 
		CGameObject::Update(dt);

		// Simple fall down
		vy += SIMON_GRAVITY * dt;
		if (x < 0)
			x = 0;
		if (x > 1370)
			x = 1370;

		vector<LPGAMEOBJECT> listTorch;
		vector<LPGAMEOBJECT> listBrick;
		vector<LPGAMEOBJECT> listItem;
		vector<LPGAMEOBJECT> listObject;

		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CTorch*>(coObjects->at(i)))
			{
				CTorch* torch = dynamic_cast<CTorch*>(coObjects->at(i));

				listTorch.push_back(torch);

			}
			else if (dynamic_cast<CBrick*>(coObjects->at(i)))
			{
				CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
				listBrick.push_back(brick);
			}
		}
		if (state == SIMON_STATE_SIT_ATTACK || state == SIMON_STATE_STAND_ATTACK)
		{
			weapons[0]->SetPosition(x, y);
			weapons[0]->SetTrend(nx);
			weapons[0]->CollisionWithObject(dt, listTorch);
			attack_start = GetTickCount();
		}
		//else if (state == SIMON_STATE_ATTACK_DAGGER)
		//{
		//	//if (weapons.size() > 1)
		//	{
		//		weapons[1]->SetPosition(x, y);
		//		weapons[1]->SetTrend(nx);
		//		weapons[1]->Update(dt);
		//		weapons[1]->CollisionWithObject(dt, *coObjects);
		//	}
		//	attack_start = GetTickCount();
		//}


		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 
		if (state != SIMON_STATE_DIE)
			CalcPotentialCollisions(&listBrick, coEvents);

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

			//// block 
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;
		}


		coEvents.clear();
		if (state != SIMON_STATE_DIE)
			CalcPotentialCollisions(&listTorch, coEvents);

		// reset untouchable timer if untouchable time has passed
		if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}

		// collision occured, proceed normally
		if (coEvents.size() > 0)
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			x += dx;

			// Collision logic with items
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CTorch*>(e->obj)) // if e->obj is torch 
				{
					CTorch* torch = dynamic_cast<CTorch*>(e->obj);// if e->obj is torch 
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
			}
			CollisionWithItem(dt, listItem);
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	
}


void CSimon::Render()
{

	int ani;

	if (state == SIMON_STATE_SIT_ATTACK)
	{
		ani = SIMON_ANI_SITTING_ATTACKING;
		weapons[0]->Render();
	}
	else if (state == SIMON_STATE_STAND_ATTACK)
	{
		ani = SIMON_ANI_STANDING_ATTACKING;
		weapons[0]->Render();

	}
	else if (state == SIMON_STATE_ATTACK_DAGGER)
	{
		ani = SIMON_ANI_IDLE;
		//if (weapons.size() > 1)
		{
			//weapons[1]->Render();
		}
	}
	else if (state == SIMON_STATE_SIT)
	{
		ani = SIMON_ANI_SITTING;

	}
	else if (state == SIMON_STATE_JUMP)
	{
		if (vy < 0)
			ani = SIMON_ANI_JUMPING;
		else
			ani = SIMON_ANI_IDLE;
	}
	else {
		if (vx == 0)
		{
			ani = SIMON_ANI_IDLE;
		}
		else
		{
			ani = SIMON_ANI_WALKING;
		}
	}
	if (trans_start > 0) {
		ani = SIMON_ANI_TRANS;
		if (GetTickCount() - trans_start > 200)
		{
			trans_start = 0;
		}
	}

	animations[ani]->Render(x, y, nx);
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