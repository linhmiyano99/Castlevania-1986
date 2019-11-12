#pragma once
#ifndef __ITEMHEART_H_
#define __ITEMHEART_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMHEART_WIDTH 22
#define ITEMHEART_HEIGHT 25


class CItemHeart : public CItem
{
public:
	CItemHeart(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(702);
		_type = eType::HEART;
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);


};
#endif // !__DAGGER_H_