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

#define BOSS_TIME_ATTACK	10000
#define BOSS_TIME_CHECK_FLY 2500
#define BOSS_TIME_HURT		200
#define BOSS_TIME_ATTACK2 300

class CBoss : public CEnemy
{
	static CBoss* __instance;
	DWORD start_attack;
	DWORD start_hurt;
	DWORD start_fly;
	DWORD start_curve;
	float x0;
	float y0;
	float x1;
	float y1;
	float x2;
	float y2;
	int step;
	int type;
public:
	static CBoss* GetInstance();

	CBoss(float _x, float _y) :CEnemy(_x, _y, ID_BOSSBALL, eType::BOSS)
	{
		animations.clear();
		AddAnimation(1090);
		AddAnimation(1091);
		AddAnimation(1092);
		AddAnimation(800);
		type = 0;
		step = 0;
		_energy = 16;
		start_attack = 0;
		start_hurt = 0;
		vx = vy = 0;
		state = BOSS_STATE_SLEEP;
		dt_die = 0;
		start_fly = 0;
		x1 = x2 = y1 = y2 = 0;
		start_fly;
		start_curve = 0;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void Hurt();
	void AutoFly(float next_x, float next_y);
	void AutoAttack(float next_x, float next_y);
	void FlyStraight(float next_x, float next_y);
	void FlyCurve(float next_x, float next_y);
	//https://stackoverflow.com/questions/785097/how-do-i-implement-a-b%C3%A9zier-curve-in-c
	int getPt(int n1, int n2, float perc);
};