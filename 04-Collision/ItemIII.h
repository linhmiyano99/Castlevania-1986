#pragma once
#ifndef __ITEMIII_H_
#define __ITEMII_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMIII_WIDTH 27
#define ITEMII_HEIGHT 27


class CItemIII : public CItem
{
public:
	CItemIII(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(716);
		_type = eType::ITEMIII;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__DAGGER_H_