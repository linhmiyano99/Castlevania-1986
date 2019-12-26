#pragma once
#ifndef __ITEM_AXE_H_
#define __ITEM_AXE_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEM_AXE_WIDTH 32
#define ITEM_AXE_HEIGHT 32


class CItemAxe : public CItem
{
public:
	CItemAxe(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(710);
		_type = eType::ITEMAXE;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__DAGGER_H_