#pragma once
#ifndef __ITEMDRAGGER_H_
#define __ITEMDRAGGER_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMDRAGGER_WIDTH 32
#define ITEMDRAGGER_HEIGHT 32


class CItemDagger : public CItem
{
public:
	CItemDagger() : CItem()
	{
		AddAnimation(701);
		_type = TYPE_ITEM_DAGGER;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__DAGGER_H_