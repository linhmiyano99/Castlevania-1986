#pragma once
#ifndef __ITEMII_H_
#define __ITEMII_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMII_WIDTH 27
#define ITEMII_HEIGHT 27


class CItemII : public CItem
{
public:
	CItemII(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(713);
		_type = eType::ITEMII;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__DAGGER_H_