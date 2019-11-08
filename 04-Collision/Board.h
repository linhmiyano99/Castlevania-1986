#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Code.h"


#define SCORE_X 110
#define SCORE_Y 12


class CBoard
{
	int _time;
	DWORD _count;
	CCode* code;
	static CBoard* __instance;

public:
	static CBoard* GetInstance();
	CBoard()
	{
		_time = 300;
		_count = GetTickCount();
		code = new CCode();
	}
	~CBoard()
	{
		if (code != NULL)
			delete code;
		code = NULL;
	}
	void Update(DWORD dt);
	void Render();
};
