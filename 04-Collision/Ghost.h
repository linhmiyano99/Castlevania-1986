#pragma once
#include "Enemy.h"

#define GHOST_BBOX_WIDTH 40
#define GHOST_BBOX_HEIGHT 60

#define GHOST_SPEED 0.07f

class CGhost: public CEnemy
{
	static bool isStart;

public:
	CGhost(float _x = 2000, float _y = 0, int id = 0) :CEnemy(_x, _y, id, eType::GHOST)
	{
		animations.clear();
		AddAnimation(1000);
		AddAnimation(800);
		nx = -1;
		vx = vy = 0;
		dt_appear = 0;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	static void Start() { isStart = true; }
	static void Stop() { isStart = false; }
	static bool IsStart() { return isStart; }
	void Go() { vx = nx * GHOST_SPEED; }
	
};