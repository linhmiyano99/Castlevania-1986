#pragma once
#include "Enemy.h"
#include "ItemBossball.h"

#define BOSS_BBOX_WIDTH  100
#define BOSS_BBOX_HEIGHT 50

#define BOSS_ANI_SLEEPING  0
#define BOSS_ANI_FLYING	   1
#define BOSS_ANI_ATTACKING 2


#define BOSS_STATE_NOT_EXSIST		0
#define BOSS_STATE_ITEM				1
#define BOSS_STATE_ITEM_NOT_EXSIST 	2
#define BOSS_STATE_SLEEP			3
#define BOSS_STATE_FLY				4	
#define BOSS_STATE_ATTACK			5

#define BOSS_TIME_ATTACK	4000
#define BOSS_TIME_HURT		200

class CBoss : public CEnemy
{
	static CBoss* __instance;
	DWORD start_attack;
	DWORD start_hurt;
public:
	static CBoss* GetInstance();

	CBoss(float _x, float _y, int id = 10) :CEnemy(_x, _y, id, eType::BOSS)
	{
		animations.clear();
		AddAnimation(1090);
		AddAnimation(1091);
		AddAnimation(1092);
		AddAnimation(800);
		_energy = 16;
		start_attack = 0;
		start_hurt = 0;
		vx = vy = 0;
		state = BOSS_STATE_SLEEP;
		dt_die = 0;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void Hurt();
};