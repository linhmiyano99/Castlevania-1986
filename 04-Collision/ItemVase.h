#pragma once
#ifndef __ITEMVASE_H_
#define __ITEMVASE_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMVASE_WIDTH 27
#define ITEMVASE_HEIGHT 35


class CItemVase : public CItem
{
public:
	CItemVase(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(717);
		_type = eType::ITEMVASE;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__DAGGER_H_