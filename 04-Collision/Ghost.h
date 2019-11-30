#pragma once
#include "Enemy.h"

#define GHOST_BBOX_WIDTH 40
#define GHOST_BBOX_HEIGHT 60

#define GHOST_SPEED 0.05f
#define GHOST_GRAVITY 0.05f

#define GHOST_DISTANCE_TOO_FAR 300

class CGhost: public CEnemy
{
	static bool isStart;
	float _leftLimit;
	float _rightLimit;
public:
	CGhost(float _x, float _y, int id = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	static void Start() { isStart = true; }
	static void Stop() { isStart = false; }
	static bool IsStart() { return isStart; }
	void CollisionWithBrick(DWORD dt, LPGAMEOBJECT& listBrick, float min_tx0, float min_ty0, int nx0, int ny0);
	void CollisionWithHiden(DWORD dt, LPGAMEOBJECT& listBrick, float min_tx0, float min_ty0, int nx0, int ny0);
	
};