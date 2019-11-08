#pragma once
#include <vector>
#include "GameObject.h"
#include "Game.h"
#include "Define.h"
#include "debug.h"

#define GRID_ROW_MAX	3
#define GRID_COLUMN_MAX 12
#define GRID_CELL_HEIGHT SCREEN_HEIGHT;
#define GRID_CELL_WIDTH SCREEN_WIDTH;

using namespace std;
class CGrid
{
	static CGrid* __instance;
	vector<LPGAMEOBJECT> listBrick;
	vector<LPGAMEOBJECT> cells[GRID_ROW_MAX][GRID_COLUMN_MAX];
public:
	static CGrid* GetInstance();
	void LoadObject(char* filename);
	void Insert(int id, int type, int trend, float x, float y, float w, float h, int id_item);
	CGameObject* GetNewObject(int type, int trend, int x, int y, int w, int h, int id_item);
	void GetListObject(vector<LPGAMEOBJECT>& ListObj, float cam_x, float cam_y);

};