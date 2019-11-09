#pragma once
#include "Enemy.h"

#define GHOST_BBOX_WIDTH 40
#define GHOST_BBOX_HEIGHT 60

#define FISHMAN_RUNNING_SPEED_X 0.01f;
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
	vector<LPGAMEOBJECT> smallballs;
public:
	CFishman(float _x = 3300, float _y = 780, int id = 0) :CEnemy(_x, _y, id)
	{
		animations.clear();
		AddAnimation(1004);
		AddAnimation(1005);
		AddAnimation(1006);
		AddAnimation(1100);
		isJumping = true;
		vy = -0.5f;
		ny = -1;
		vx = 0;
		nx = -1;
		start_attack = GetTickCount();
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	bool IsAttacking() { return isAttacking; }
};