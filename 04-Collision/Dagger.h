#ifndef __DAGGER_H__

#define __DAGGER_H__


#include "GameObject.h"
#include "Textures.h"
#include "Weapon.h"

#define DAGGER_HEIGHT 22
#define DAGGER_WIDTH 55

#define DAGGER_NOT_EXSIST 0
#define DAGGER_EXSIST 1 

#define DAGGER_SPEED 0.5f

#define DAGGER_STATE_HIDE  0
#define DAGGER_STATE_ATTACK 1

#define DAGGER_TIME_ATTACK 1000


class CDagger : public CWeapon
{
	static CDagger* __instance;
	DWORD start_attack;
public:

	static CDagger* GetInstance();
	CDagger();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetPosition(float simon_x, float simon_y);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);

};
#endif // !__VAMPIREILLER_H__