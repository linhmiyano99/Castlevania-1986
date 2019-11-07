#pragma once
#include <vector>
#include "GameObject.h"
#include "Game.h"
#include "Define.h"

#define GRID_ROW_MAX	3
#define GRID_COLUMN_MAX 12
#define GRID_CELL_HEIGHT SCREEN_HEIGHT;
#define GRID_CELL_WIDTH SCREEN_WIDTH;

using namespace std;
class CGrid
{
	vector<LPGAMEOBJECT> grid[GRID_ROW_MAX][GRID_COLUMN_MAX];
public:
	void GetListObject(vector<LPGAMEOBJECT>& ListObj);
};