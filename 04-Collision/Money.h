#pragma once
#include "Item.h"

class CMoney :public CItem
{
public:
	CMoney() :CItem()
	{

	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

};