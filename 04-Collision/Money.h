#pragma once
#ifndef __ITEMMONEY_H_
#define __ITEMMONEY_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMMONEY_WIDTH 32
#define ITEMMONEY_HEIGHT 32


class CItemMoney : public CItem
{
	DWORD start_effection;
public:
	CItemMoney(float _x, float _y, int type) : CItem(_x, _y)
	{
		switch (type)
		{
		case eType::MONEY_1:
			AddAnimation(705);
			AddAnimation(810);
			break;
		case eType::MONEY_2:
			AddAnimation(706);
			AddAnimation(811);
			break;
		case eType::MONEY_3:
			AddAnimation(707);
			AddAnimation(812);
			break;
		case eType::MONEY_4:
			AddAnimation(708);
			AddAnimation(813);
			break;
		default:
			break;
		}
		_type = type;
		start_effection = 0;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetState(int _state)
	{
		if (_state != ITEM_STATE_NOT_EXSIST)
		{
			this->state = _state;
		}
		else
		{
			start_effection = GetTickCount();
		}
	}

};
#endif // !__DAGGER_H_