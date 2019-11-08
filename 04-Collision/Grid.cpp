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


CGrid* CGrid::__instance = NULL;

CGrid* CGrid::GetInstance()
{
	if (__instance == NULL) __instance = new CGrid();
	return __instance;
}

void CGrid::GetListObject(vector<LPGAMEOBJECT>& ListObj)
{
	ListObj.clear();


	float cam_x, cam_y;
	CGame* game = new CGame();
	game->GetCamPos(cam_x, cam_y);

	int bottom = (int)((cam_y + SCREEN_HEIGHT) / SCREEN_HEIGHT);
	int top = (int)((cam_y) / SCREEN_HEIGHT);

	int left = (int)((cam_x) / SCREEN_WIDTH);
	int right = (int)((cam_x + SCREEN_WIDTH) / SCREEN_WIDTH);
	for (int i = top; i <= bottom + 1; i++)
	{
		for (int j = left; j <= right +1; j++)
		{
			if (bottom <= GRID_ROW_MAX && right <= GRID_COLUMN_MAX)
			{
				for (UINT k = 0; k < cells[i][j].size(); k++)
				{
					//if (cells[i][j].at(k)->GetState()) // đối tượng còn tồn tại
					{
						ListObj.push_back(cells[i][j].at(k));
					}
				}
			}
		}
	}
	
	
	for each (LPGAMEOBJECT var in listBrick)
	{
		ListObj.push_back(var);
	}
	CSimon* simon = CSimon::GetInstance();
	ListObj.push_back(simon);
	CDagger* dagger = CDagger::GetInstance();
	ListObj.push_back(dagger);
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

	int id, type, trend, id_item, nx, ny;
	float x, y, w, h;

	if (inFile)
	{
		while (inFile >> id >> type >> trend >> x >> y >> w >> h >> id_item)
		{
			if (type == eType::BRICK_1 || type == eType::BRICK_2)
			{
				for (int i = 0; i < w / h; i++)
					Insert(id, type, trend, x + i * 32, y, w, h, id_item);
			}
			else
				Insert(id, type, trend, x, y, w, h, id_item);
		}
		inFile.close();
	}
}
void CGrid::Insert(int id, int type, int trend, float x, float y, float w, float h, int id_item)
{

	int top = (int)(y )/ GRID_CELL_HEIGHT;
	int bottom = (int)(y + h) / GRID_CELL_HEIGHT;
	int left = (int)(x) / GRID_CELL_WIDTH;
	int right = (int)(x + w) / GRID_CELL_WIDTH;

	CGameObject* obj = GetNewObject(type, trend, x, y, w, h, id_item);
	if (obj == NULL)
		return;

	obj->SetID(id);
	obj->SetTrend(trend);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			cells[i][j].push_back(obj);
	if (type == eType::BRICK_1 || type == eType::BRICK_2)
		listBrick.push_back(obj);
}
CGameObject* CGrid::GetNewObject(int type, int trend, int x, int y, int w, int h, int id_item)
{
	if (type == eType::BRICK_1) return new CBrick(x, y);
	if (type == eType::BRICK_2) return new CBrick(x, y, 1);
	if (type == eType::TORCH) return new CTorch(x, y, id_item);
	if (type == eType::CANDLE) return new CTorch(x, y, id_item, 1);
	if (type == eType::OBJECT_HIDDEN_DOOR) return new CHidenObject(x, y);
	if (type == eType::STAIR_DOWN) return new CHidenObject(x, y, HIDENOBJECT_TYPE_DOWNSTAIR, trend, -1);
	if (type == eType::STAIR_UP) return new CHidenObject(x, y, HIDENOBJECT_TYPE_UPSTAIR, trend, 1);
	if (type == eType::GATE) return new CGate(x, y);
	if (type == eType::PANTHER) return new CPanther(x, y);
	if (type == eType::FISHMEN) return new CFishman(x, y);
	if (type == eType::GHOST) return new CGhost(x, y);
	if (type == eType::BAT) return new CBat(x, y);

	return NULL;
}


