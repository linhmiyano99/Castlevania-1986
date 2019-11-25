#pragma once
#include "Enemy.h"
#include "WaterEffection.h"

#define GHOST_BBOX_WIDTH 40
#define GHOST_BBOX_HEIGHT 60

#define FISHMAN_RUNNING_SPEED_X 0.15f;
#define FISHMAN_RUNNING_SPEED_Y 0.5f;

#define FISHMAN_ANI_JUMPING 0
#define FISHMAN_ANI_WALKING 1
#define FISHMAN_ANI_ATTACK 2

#define FISHMAN_STATE_SIT 100
#define FISHMAN_STATE_RUN 200
#define FISHMAN_STATE_DIE 300

#define TIME_START_ATTACK 5000
#define TIME_ATTACK 800

class CFishman : public CEnemy
{
	bool isAttacking;
	bool isJumping;
	DWORD start_attack;
	static bool isStart;
	vector<CWaterEffection*> list;
	bool isFall;

public:
	CFishman(float _x = 3300, float _y = 780, int id = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	bool IsAttacking() { return isAttacking; }
	static void Start() { isStart = true; }
	static bool IsStart() { return isStart; }
	void Go();
	void ResetWater(int type = 0);
};