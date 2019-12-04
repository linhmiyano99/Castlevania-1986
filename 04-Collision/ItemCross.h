#pragma once
#ifndef __ITEMCROSS_H_
#define __ITEMCROSS_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMCROSS_WIDTH 35
#define ITEMCROSS_HEIGHT 27


class CItemCross : public CItem
{
public:
	CItemCross(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(711);
		_type = eType::ITEMCROSS;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__DAGGER_H_