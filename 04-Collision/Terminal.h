#pragma once
#include <d3dx9.h>
using namespace std;
class CTerminal
{
private:
	int _score;
	int _playerBlood;
	int _enemyBlood;
	int _time;
	int _stage;
	int _heart;
	int _life;
	static CTerminal* __instance;
public:
	static CTerminal* GetInstance();
	/*CTerminal();
	void LoadResources();*/
	int GetScore() { return _score; }
	int GetPlayerBlood() { return _playerBlood; }
	int GetEnemyBlood() { return _enemyBlood; }
	int GetTime() { return _time; }
	int GetStage() { return _stage; }
	int GetHeart() { return _heart; }
	int GetLife() { return _life; }
};