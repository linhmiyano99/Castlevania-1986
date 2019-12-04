#pragma once
#ifndef __ITEM_BOONGMERANG_H_
#define __ITEM_BOONGMERANG_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEM_BOONGMERANG_WATTER_WIDTH 32
#define ITEM_BOONGMERANG_WATTER_HEIGHT 32


class CItemBoongmerang : public CItem
{
public:
	CItemBoongmerang(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(719);
		_type = eType::ITEMBOONGMERANG;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__DAGGER_H_