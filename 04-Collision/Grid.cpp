#include "Grid.h"
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
#include "Board.h"
#include "Scene.h"
#include "Axe.h"


CGrid* CGrid::__instance = NULL;

CGrid* CGrid::GetInstance()
{
	if (__instance == NULL) __instance = new CGrid();
	return __instance;
}

void CGrid::GetListObject(vector<LPGAMEOBJECT>& ListObj, float cam_x, float cam_y)
{
	ListObj.clear();


	int top = (int)(cam_y + 1) / GRID_CELL_HEIGHT;
	int bottom = (int)(cam_y + SCREEN_HEIGHT + 1 ) / GRID_CELL_HEIGHT;


	int left = (int)(cam_x + 1) / GRID_CELL_WIDTH;
	int right = (int)(cam_x + SCREEN_HEIGHT - 1) / GRID_CELL_WIDTH ;

	for (int i = top - 1; i < bottom + 2; i++)
	{
		for (int j = left - 1; j < right + 2; j++)
		{
			if (i <= GRID_ROW_MAX && j <= GRID_COLUMN_MAX && i >= 0 && j >= 0)
			{
				for (UINT k = 0; k < cells[i][j].size(); k++)
				{
					
					{
						ListObj.push_back(cells[i][j].at(k));
					}
				}
			}
		}
	}
	
	
	CSimon* simon = CSimon::GetInstance();
	ListObj.push_back(simon);
	CDagger* dagger = CDagger::GetInstance();
	ListObj.push_back(dagger);
	CAxe* axe = CAxe::GetInstance();
	ListObj.push_back(axe);
	CBoss* boss = CBoss::GetInstance();
	ListObj.push_back(boss);
}
void CGrid::LoadObject(char* filename)
{
	//objects.clear();

	for (int i = 0; i < GRID_ROW_MAX; i++)
		for (int j = 0; j < GRID_COLUMN_MAX; j++)
		{
			cells[i][j].clear();
		}

	listBrick.clear();
	ifstream inFile(filename);

	int type, trend, id_item, nx, ny;
	float x, y, w, h;

	if (inFile)
	{
		while (inFile >> type >> trend >> x >> y >> w >> h >> id_item)
		{
			if (type == eType::BRICK_1 || type == eType::BRICK_2 || type == eType::BRICK_3)
			{
				for (int i = 0; i < w / h; i++)
					Insert(type, trend, x + i * 32, y, w, h, id_item);
			}
			else
				Insert(type, trend, x, y, w, h, id_item);
		}
		inFile.close();
	}
}
void CGrid::Insert(int type, int trend, float x, float y, float w, float h, int id_item)
{

	int top = (int)(y )/ GRID_CELL_HEIGHT;
	int bottom = (int)(y + h) / GRID_CELL_HEIGHT;
	int left = (int)(x) / GRID_CELL_WIDTH;
	int right = (int)(x + w) / GRID_CELL_WIDTH;

	CGameObject* obj = GetNewObject(type, trend, x, y, w, h, id_item);
	if (obj == NULL)
		return;

	obj->SetTrend(trend);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			cells[i][j].push_back(obj);

}
CGameObject* CGrid::GetNewObject(int type, int trend, int x, int y, int w, int h, int id_item)
{
	if (type == eType::BRICK_1) return new CBrick(x, y, 0, eType::BRICK_1);
	if (type == eType::BRICK_2) return new CBrick(x, y, 0, eType::BRICK_2);
	if (type == eType::BRICK_3) return new CBrick(x, y, id_item, eType::BRICK_3);
	if (type == eType::TORCH) return new CTorch(x, y, id_item, eType::TORCH);
	if (type == eType::CANDLE) return new CTorch(x, y, id_item, eType::CANDLE);
	if (type == eType::OBJECT_HIDDEN_DOOR) return new CHidenObject(x, y);
	if (type == eType::STAIR_DOWN) return new CHidenObject(x, y, HIDENOBJECT_TYPE_DOWNSTAIR, trend, -1);
	if (type == eType::STAIR_UP) return new CHidenObject(x, y, HIDENOBJECT_TYPE_UPSTAIR, trend, 1);
	if (type == eType::OBJECT_HIDDEN_FISHMAN) return new CHidenObject(x, y, HIDENOBJECT_TYPE_FISHMAN);
	if (type == eType::OBJECT_HIDDEN_GHOST_1) return new CHidenObject(x, y, HIDENOBJECT_TYPE_GHOST_1);
	if (type == eType::OBJECT_HIDDEN_GHOST_STOP_1) return new CHidenObject(x, y, HIDENOBJECT_TYPE_GHOST_STOP_1);
	if (type == eType::OBJECT_HIDDEN_GHOST_2) return new CHidenObject(x, y, HIDENOBJECT_TYPE_GHOST_2);
	if (type == eType::GATE) return new CGate(x, y);
	if (type == eType::PANTHER) return new CPanther(x, y);
	if (type == eType::FISHMEN) return new CFishman(x, y);
	if (type == eType::GHOST) return new CGhost(x, y, id_item);
	if (type == eType::BAT) return new CBat(x, y);

	return NULL;
}


