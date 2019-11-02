#pragma once


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
#include "Torch.h"
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



class CScene
{
	static CScene* __instance;
	CSimon* simon;
	CBoss* boss;
	CMap* map;
	CDagger* dagger;
	CGame* game;
	CHidenObject* hiden;
	vector<LPGAMEOBJECT> objects;
	int id;
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

	void LoadObject(char* filename);
	void Insert(int id, int type, int trend, float x, float y, float w, float h, int id_item);
	CGameObject* GetNewObject(int type, int x, int y, int w, int h, int id_item);
};