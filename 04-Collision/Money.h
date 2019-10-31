#pragma once
#include "Item.h"

class CSmallHeart :public CItem
{
public:
	CSmallHeart() :CItem()
	{

	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

};