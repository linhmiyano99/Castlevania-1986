#pragma once
#ifndef __ITEM_H_
#define __ITEM_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Define.h"


#define ITEM_STATE_NOT_EXSIST 0
#define ITEM_STATE_EXSIST 1

#define TYPE_ITEM		 0
#define ITEM_GRAVITY	 0.02f
#define TIME_ITEM_EXSIST 5000


class CItem : public CGameObject
{
protected:
	DWORD time_exsist;
public:
	CItem(float _x = 0, float _y = 0) : CGameObject(_x, _y)
	{
		state = ITEM_STATE_EXSIST;
		_type = TYPE_ITEM;
		time_exsist = 0;
	}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
};
#endif // !__ITEM_H_