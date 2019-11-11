#pragma once
#include "Item.h"

class CMoney :public CItem
{
public:
	CMoney(float _x, float _y) : CItem(_x, _y)
	{
		_type = eType::MONEY;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

};