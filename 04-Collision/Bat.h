#pragma once
#include "Enemy.h"

#define BAT_BBOX_WIDTH 32
#define BAT_BBOX_HEIGHT 32

#define BAT_LEFT_LIMIT 3080
#define BAT_TOP_LIMIT 40
#define BAT_RIGHT_LIMIT 4028
#define BAT_BOTTOM_LIMIT 500

class CBat : public CEnemy
{
	float topLimit;
	float bottomLimit;
	static bool isStart;
public:
	CBat(float _x = 3500, float _y = 200, int id = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	static void Start() { isStart = true; }
	static void Stop() { isStart = false; }
	static bool IsStart() { return isStart; }
};