#include "Torch.h"
#include "Game.h"
#include "Weapon.h"


void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> listObj;
	// Collision logic with items
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT object = coObjects->at(i);
		listObj.push_back(object);
	}

	CollisionWithObject(dt, listObj);


}


void CWeapon::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{

	for (int i = 0; i < listObj.size(); i++)
	{
		if (dynamic_cast<CTorch*>(listObj.at(i)))
		{
			if (listObj.at(i)->GetState() == TORCH_STATE_EXSIST)
			{
				LPCOLLISIONEVENT e = SweptAABBEx(listObj.at(i));
				if (e->t > 0) //đụng độ
				{
					listObj.at(i)->SetState(TORCH_STATE_NOT_EXSIST);
				}
			}
		}
	}
}
