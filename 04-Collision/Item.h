#pragma once
#ifndef __ITEM_H_
#define __ITEM_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"


#define ITEM_STATE_NOT_EXSIST 0
#define ITEM_STATE_EXSIST 1

#define TYPE_ITEM			  0
#define TYPE_ITEM_DAGGER	  1
#define TYPE_ITEM_WHIPUPGRADE 2
#define TYPE_ITEM_HEART		  3
#define TYPE_ITEM_SMALLHEART  4
#define TYPE_ITEM_CHICKEN     5

#define ITEM_GRAVITY		  0.05f


class CItem : public CGameObject
{

public:
	CItem(float _x = 0, float _y = 0) : CGameObject(_x, _y)
	{
		state = ITEM_STATE_EXSIST;
		_type = TYPE_ITEM;
	}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
};
#endif // !__ITEM_H_