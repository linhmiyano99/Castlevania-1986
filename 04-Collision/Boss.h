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
#define BOSS_TIME_CHECK_FLY 3000
#define BOSS_TIME_HURT		500
#define BOSS_TIME_ATTACK2 300

#define BOSS_RANDOM_X1 5430
#define BOSS_RANDOM_Y1 210
#define BOSS_RANDOM_X2 5150
#define BOSS_RANDOM_Y2 210

#define BOSS_SPEED_AUTO_FLY_X 0.4f
#define BOSS_SPEED_AUTO_FLY_Y 0.3f

#define BOSS_TIME_CURVE 2000

#define TIME_RATE 0.00005f

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
	float start_x;
	float start_y;
public:
	static CBoss* GetInstance();

	CBoss(float _x, float _y);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void Hurt();
	void AutoFly(float next_x, float next_y);
	void AutoAttack(float next_x, float next_y);
	void FlyStraight(float next_x, float next_y);
	void FlyCurve(float next_x, float next_y);
	//https://stackoverflow.com/questions/785097/how-do-i-implement-a-b%C3%A9zier-curve-in-c
	float getPt(int n1, int n2, float perc);
	void ResetBoss();
	void SetFly();
	void Die() { _energy = 0; }
};