#pragma once
#ifndef __ITEMCLOCK_H_
#define __ITEMCLOCK_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMCLOCK_WIDTH 35
#define ITEMCLOCK_HEIGHT 27


class CItemClock : public CItem
{
public:
	CItemClock(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(709);
		_type = eType::ITEMCLOCK;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__DAGGER_H_