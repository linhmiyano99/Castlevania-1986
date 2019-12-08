#pragma once
#ifndef __HOLLY_WATTER_H__

#define __HOLLY_WATTER_H__


#include "GameObject.h"
#include "Textures.h"
#include "Weapon.h"

#define HOLLY_WATTER_HEIGHT 32
#define HOLLY_WATTER_WIDTH 32

#define HOLLY_WATTER_NOT_EXSIST 0
#define HOLLY_WATTER_EXSIST 1 

#define HOLLY_WATTER_SPEED 0.25f
#define HOLLY_WATTER_SPEED_Y 0.3f

#define HOLLY_WATTER_STATE_HIDE  0
#define HOLLY_WATTER_STATE_ATTACK 1
#define HOLLY_WATTER_STATE_FIRE		 2

#define GRAVITY 0.002f

#define HOLLY_WATTER_TIME_ATTACK 2000


class CHollyWatter : public CWeapon
{
	static CHollyWatter* __instance;
	DWORD start_attack;
public:

	static CHollyWatter* GetInstance();
	CHollyWatter();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetPosition(float simon_x, float simon_y);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	void SetState(int _state);

};
#endif // !__VAMPIREILLER_H__