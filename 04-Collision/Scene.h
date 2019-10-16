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




class CScene
{
	CSimon* simon;
	CMap* map;
	CDagger* dagger;
	CGame* game;
	vector<LPGAMEOBJECT> objects;
	int id;
public:
	CScene(int id = 0);
	void LoadResoure();
	void Update(DWORD dt);
	void Render();

};