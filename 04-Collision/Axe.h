#pragma once
#ifndef __AXE_H__

#define __AXE_H__


#include "GameObject.h"
#include "Textures.h"
#include "Weapon.h"

#define AXE_HEIGHT 32
#define AXE_WIDTH 32

#define AXE_NOT_EXSIST 0
#define AXE_EXSIST 1 

#define AXE_SPEED 0.4f
#define AXE_SPEED_Y 0.5f

#define AXE_STATE_HIDE  0
#define AXE_STATE_ATTACK 1

#define GRAVITY 0.002f

#define AXE_TIME_ATTACK 1000


class CAxe : public CWeapon
{
	static CAxe* __instance;
	DWORD start_attack;
public:

	static CAxe* GetInstance();
	CAxe();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetPosition(float simon_x, float simon_y);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	void SetState(int _state);
	bool IsCanAttack() { if (start_attack == 0) return true; return false;}

};
#endif // !__VAMPIREILLER_H__