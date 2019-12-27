#pragma once
#include "Enemy.h"

#define PANTHER_BBOX_WIDTH 64
#define PANTHER_BBOX_HEIGHT 32

#define PANTHER_RUNNING_SPEED_X 0.22f;
#define PANTHER_RUNNING_SPEED_Y 0.1f;

#define PANTHER_ANI_SIT 0
#define PANTHER_ANI_RUNNING 1
#define PANTHER_ANI_DIE 2

#define PANTHER_STATE_SIT 100
#define PANTHER_STATE_RUN 200
#define PANTHER_STATE_DIE 300

#define DISTANCE_TO_START1 40
#define DISTANCE_TO_START2 150

#define PANTHER_GRAVITY 0.002f

class CPanther : public CEnemy
{
	float LeftLimit;
	bool isJump;
	bool isStart;
	static bool isReset;
public:
	CPanther(float _x = 1419, float _y = 230, int id = 0);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetSpeed(float _vx, float _vy);
	virtual void SetState(int state);
	void CollisionWithBrick(DWORD dt, LPGAMEOBJECT &listBrick, float min_tx0, float min_ty0, int nx0, int ny0);
	void CollisionWithHiden(DWORD dt, LPGAMEOBJECT &listBrick, float min_tx0, float min_ty0, int nx0, int ny0);
	void Reset();
	static void StopReset() { isReset = false; }
	static void StartReset() { isReset = true; }
	static bool IsResetting() { return isReset; }
};