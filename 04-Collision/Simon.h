#ifndef __SIMON_H__
#define __SIMON_H__

#pragma once
#include "GameObject.h"
#include "Item.h"
#include "VampireKiller.h"
#include "Weapon.h"
#include "Dagger.h"
#include "WaterEffection.h"

#define SIMON_WALKING_SPEED		0.2f
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
#define SIMON_STATE_GO_UP			1000
#define SIMON_STATE_GO_DOWN			1001
#define SIMON_STATE_IDLE_UP			1002
#define SIMON_STATE_IDLE_DOWN		1003
#define SIMON_STATE_HURT			1100
#define SIMON_STATE_DIE				1101

#define SIMON_ANI_IDLE						0
#define SIMON_ANI_WALKING					1
#define SIMON_ANI_JUMPING					2
#define SIMON_ANI_SITTING					3
#define SIMON_ANI_STANDING_ATTACKING 		4
#define SIMON_ANI_SITTING_ATTACKING			5
#define SIMON_ANI_TRANS						6
#define SIMON_ANI_GO_UP 					7
#define SIMON_ANI_GO_DOWN					8
#define SIMON_ANI_HURT						9
#define SIMON_ANI_IDLE_UP					10
#define SIMON_ANI_IDLE_DOWN					11
#define SIMON_ANI_DIE						12

#define SIMON_HEIGHT_STAND			60
#define SIMON_HEIGHT_SIT			45
#define SIMON_WIDTH					40
#define SIMON_HEIGHT_DIE			30
#define SIMON_WIDTH_DIE				60

#define SIMON_UNTOUCHABLE_TIME		1300
#define SIMON_HURT_TIME				300

#define ID_WEAPON_VAMPIREKILLER		0
#define ID_WEAPON_DAGGER			1

#define ATTACK_TIME			300
#define ATTACK_TIME_WAIT	500
#define JUMP_TIME			0
#define DIE_TIME			2000
#define TIME_FOR_PER_STEP  205

using namespace std;
class CSimon : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	DWORD trans_start;
	DWORD attack_start;
	DWORD _count;
	DWORD die_start;
	DWORD start_stair;
	unordered_map<int, CWeapon*> weapons;
	vector<CWaterEffection*> list;
	bool isFall;

	static CSimon* __instance;
	int _heart;
	int isCanOnStair;
	bool isOnStair;
	int _stairTrend;
	bool isAutoGo;
	int auto_x;
	int _score;
	int _lives;
	int _step;
	float _ground;
	float new_x;
	float new_y;
	bool isUnder;

public:
	static CSimon* GetInstance();
	CSimon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void CollisionWithItem(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	CVampireKiller* getWeapon(int i = 0) { return (CVampireKiller *)(weapons[0]); }
	int GetHeart() { return _heart; }
	void SetHeart(int heart) { _heart = heart; }
	void HeartDown()
	{
		if (GetTickCount() - _count >= 50)
		{
			_count = GetTickCount();
			_score += 100;
			_heart--;
		}
	}
	void CollisionWithBrick(DWORD dt, vector<LPGAMEOBJECT>& listObj, float min_tx, float min_ty, int nx, int ny);
	void CollisionWithTorch(DWORD dt, vector<LPGAMEOBJECT>& listObj, float min_tx, float min_ty, int nx, int ny);
	void CollisionWithHidenObject(DWORD dt, vector<LPGAMEOBJECT>& listObj, float min_tx, float min_ty, int nx, int ny);
	void CollisionWithEnemy(DWORD dt, vector<LPGAMEOBJECT>& listObj, float min_tx, float min_ty, int nx, int ny);
	void CollisionWithGate(DWORD dt, vector<LPGAMEOBJECT>& listObj, float min_tx, float min_ty, int nx, int ny);
	int IsCanOnStair(vector<LPGAMEOBJECT>& listObj);
	bool IsOnStair() { return isOnStair; }
	int GetStairTrend() { return _stairTrend; }
	int GetNx() { return nx; }
	void AutoGo();
	void TransScene();
	bool IsAutoGo() { return isAutoGo; }
	int GetScore() { return _score; }
	void SetScore(int score) { _score += score; }
	int GetLives() { return _lives; }
	void UpEnergy() 
	{
		if (GetTickCount() - _count >= 50)
		{
			_count = GetTickCount();
			_energy++;
		}
	}
	bool IsAttacking() { if (attack_start > 0)return true; return false; }
	void ResetWater()
	{
		list[0]->SetPosition(x, y + 20);
		list[1]->SetPosition(x + 10, y + 60);
		list[2]->SetPosition(x + 20, y + 20);
	}
	void SetUnder() { isUnder = true; }
};
#endif