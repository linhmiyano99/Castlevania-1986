#pragma once
#include "Enemy.h"

#define GHOST_BBOX_WIDTH  40
#define GHOST_BBOX_HEIGHT 60

#define BOSS_ANI_SLEEPING  0
#define BOSS_ANI_FLYING	   1
#define BOSS_ANI_ATTACKING 2

#define BOSS_STATE_SLEPP   0
#define BOSS_STATE_FLY	   1	
#define BOSS_STATE_ATTACK  2	

class CBoss : public CEnemy
{
	int _energy;
	static CBoss* __instance;
public:
	static CBoss* GetInstance();

	CBoss(float _x, float _y, int id = 0) :CEnemy(_x, _y, id, eType::BOSS)
	{
		animations.clear();
		AddAnimation(1090);
		AddAnimation(1091);
		AddAnimation(800);
		vx = 0.2f;
		vy = 0.1f;
		_energy = 16;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int GetEnergy() { return _energy; }
};