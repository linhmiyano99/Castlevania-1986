#ifndef __SCENE_H__

#define __SCENE_H__


#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "fstream"

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "MagagementTexture.h"
#include "Define.h"

#include "Camera.h"

#include "Simon.h"
#include "Map.h"
#include "WhipUpgrade.h"
#include "ItemDagger.h"
#include "Brick.h"
#include "Dagger.h"
#include "HidenObject.h"
#include "Ghost.h"
#include "Panther.h"
#include "Gate.h"
#include "Bat.h"
#include "Fishman.h"
#include "Boss.h"
#include "Board.h"
#include "Grid.h"
#include "Axe.h"
#include "HolyWater.h"
#include "Boongmerang.h"


#define TIME_KILL_ALL_ENEMY 100

class CScene
{
	static CScene* __instance;
	CSimon* simon;
	CBoss* boss;
	CMap* map;
	CDagger* dagger;
	CAxe* axe;
	CHollyWatter* holly;
	CBoongmerang* boongmerang;
	CGame* game;
	CHidenObject* hiden;
	CBoard* board;
	CGrid* grid;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> smallballs;
	int id;
	int _stage;
	bool isAutoTran;
	float auto_tran;
	DWORD start_killAllEnemy;
public:
	static CScene* GetInstance();
	CScene(int id = 0);
	void LoadResoure();
	void LoadSimon();
	void Update(DWORD dt);
	void Render();
	void SetMap(int id = 0);
	int GetScene() { return id; }
	vector<LPGAMEOBJECT> GetObjects() { return objects; }
	int GetLeft();
	int GetTop();
	int GetRight();
	int GetBottom();

	void TranScene();
	bool IsTranScene() { return isAutoTran; }
	void AddSmallBall(LPGAMEOBJECT smallball);
	void UpStage();
	int GetStage() { return _stage; }
	void SetScene(int scene) { id = scene; }
	void ResetScene();
	void TestStage(int stage);
	bool IsKillAllEnemy();
	void KillAllEnemy() { start_killAllEnemy = GetTickCount(); }
};
#endif // !__SMALLBALL_H__