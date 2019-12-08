#pragma once
#ifndef __BOONGMERANG_H__

#define __BOONGMERANG_H__


#include "GameObject.h"
#include "Textures.h"
#include "Weapon.h"

#define BOONGMERANG_HEIGHT 32
#define BOONGMERANG_WIDTH 32

#define BOONGMERANG_NOT_EXSIST 0
#define BOONGMERANG_EXSIST 1 

#define BOONGMERANG_SPEED 0.5f

#define BOONGMERANG_STATE_HIDE  0
#define BOONGMERANG_STATE_ATTACK 1

#define GRAVITY 0.002f

#define BOONGMERANG_TIME_ATTACK 2000


class CBoongmerang : public CWeapon
{
	static CBoongmerang* __instance;
	DWORD start_attack;
	float leftLimit;
	float rightLimit;
	int turn;
public:

	static CBoongmerang* GetInstance();
	CBoongmerang();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetPosition(float simon_x, float simon_y);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	void SetState(int _state);

};
#endif // !__VAMPIREILLER_H__