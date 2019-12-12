
#pragma once
#include "GameObject.h"
#define GATE_STATE_CLOSE 0
#define GATE_STATE_OPEN  1

#define GATE_ANI_CLOSING   0
#define GATE_ANI_OPENNING  1


class CGate : public CGameObject
{
	static bool isCanOpen;
public:
	CGate(float _x, float _y);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void ResetGate() { animations[1]->ResetFrame(); }
	static void Start() { isCanOpen = true; }
	static void Stop() { isCanOpen = false; }
	static bool IsStart() { return isCanOpen; }
};