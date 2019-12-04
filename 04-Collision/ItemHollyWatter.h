#pragma once
#ifndef __ITEMHOLLYWATTER_H_
#define __ITEMHOLLYWATTER_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEM_HOLLYWATTER_WIDTH 35
#define ITEM_HOLLYWATTER_HEIGHT 27


class CItemHollyWatter : public CItem
{
public:
	CItemHollyWatter(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(714);
		_type = eType::ITEMHOLLYWATTER;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__DAGGER_H_