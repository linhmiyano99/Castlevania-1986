#pragma once
#ifndef __ITEMAXE_H_
#define __ITEMAXE_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMAXE_WIDTH 32
#define ITEMAXE_HEIGHT 32


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