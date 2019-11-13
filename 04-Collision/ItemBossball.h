#pragma once
#ifndef __ITEMBOSSBALL_H_
#define __ITEMBOSSBALL_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMBOSSBALL_WIDTH 32
#define ITEMBOSSBALL_HEIGHT 32


class CItemBossBall : public CItem
{
public:
	CItemBossBall(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(712);
		_type = eType::BOSSBALL;
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);


};
#endif // !__DAGGER_H_