#pragma once
#include "Item.h"

class CSmallHeart :public CItem
{
public:
	CSmallHeart(float _x, float _y) : CItem(_x, _y)
	{

	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

};