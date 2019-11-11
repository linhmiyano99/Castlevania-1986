#pragma once
#ifndef __ITEMCHICKEN_H_
#define __ITEMCHICKEN_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMCHICKEN_WIDTH 35
#define ITEMCHICKEN_HEIGHT 27


class CItemChicken : public CItem
{
public:
	CItemChicken(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(704);
		_type = eType::CHICKEN;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__DAGGER_H_