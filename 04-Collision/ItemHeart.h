#pragma once
#ifndef __ITEMHEART_H_
#define __ITEMHEART_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMDRAGGER_WIDTH 32
#define ITEMDRAGGER_HEIGHT 32


class CItemHeart : public CItem
{
public:
	CItemHeart(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(702);
		_type = TYPE_ITEM_HEART;
	}

	//void Render();
	//void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);


};
#endif // !__DAGGER_H_