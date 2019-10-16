#ifndef __SIMON_H__
#define __SIMON_H__

#pragma once
#include "GameObject.h"
#include "Item.h"
#include "VampireKiller.h"
#include "Weapon.h"
#include "Dagger.h"
#define SIMON_WALKING_SPEED		0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_GRAVITY			0.002f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_SIT			    400
#define SIMON_STATE_STAND_ATTACK	500
#define SIMON_STATE_SIT_ATTACK		600
#define SIMON_STATE_DIE				700
#define SIMON_STATE_UP				800
#define SIMON_STATE_ATTACK_DAGGER	900

#define SIMON_ANI_IDLE						0
#define SIMON_ANI_WALKING					1
#define SIMON_ANI_JUMPING					2
#define SIMON_ANI_SITTING					3
#define SIMON_ANI_STANDING_ATTACKING 		4
#define SIMON_ANI_SITTING_ATTACKING			5
//#define SIMON_ANI_DAGGER					6
#define SIMON_ANI_TRANS						6

#define SIMON_HEIGHT_STAND			60
#define SIMON_HEIGHT_SIT			45
#define SIMON_WIDTH					40

#define SIMON_UNTOUCHABLE_TIME		5000

#define ID_WEAPON_VAMPIREKILLER		0
#define ID_WEAPON_DAGGER			1

#define ATTACK_TIME			100
#define JUMP_TIME			0

using namespace std;
class CSimon : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	DWORD attack_start;
	DWORD trans_start;
	vector<CWeapon*> weapons;
	static CSimon* __instance;
	int _heart;
public:
	static CSimon* GetInstance();
	CSimon() : CGameObject()
	{
		CVampireKiller* rob = CVampireKiller::GetInstance();
		weapons.push_back(rob);
		/*CDagger* dagger = CDagger::GetInstance();
		weapons.push_back(dagger);*/
		untouchable = 0;
		attack_start = 0;
		trans_start = 0;
		_heart = 5;
		CSimon::AddAnimation(400);		//0. idle left 
		CSimon::AddAnimation(401);		//1. walk left
		CSimon::AddAnimation(402);		//2. jump left
		CSimon::AddAnimation(403);		//3. sit left
		CSimon::AddAnimation(404);		//4. stand attack
		CSimon::AddAnimation(405);		//5. sit attack
		CSimon::AddAnimation(410);		//6. trans
	}
	int getTrend() { return nx; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void CollisionWithItem(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	CVampireKiller* getWeapon(int i = 0) { return (CVampireKiller *)(weapons[0]); }
	int GetHeart() { return _heart; }
	void SetHeart(int heart) { _heart = heart; }
};
#endif