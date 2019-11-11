#pragma once
#ifndef __ITEMMONEY_H_
#define __ITEMMONEY_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMDRAGGER_WIDTH 32
#define ITEMDRAGGER_HEIGHT 32


class CItemMoney : public CItem
{
public:
	CItemMoney(float _x, float _y, int type) : CItem(_x, _y)
	{
		switch (type)
		{
		case eType::MONEY_1:
			AddAnimation(705);
			break;
		case eType::MONEY_2:
			AddAnimation(706);
			break;
		case eType::MONEY_3:
			AddAnimation(707);
			break;
		case eType::MONEY_4:
			AddAnimation(708);
			break;
		default:
			break;
		}
		_type = type;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__DAGGER_H_