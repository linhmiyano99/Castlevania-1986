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
#include "HolyWater.h"
#include "Boongmerang.h"


CGrid* CGrid::__instance = NULL;

CGrid* CGrid::GetInstance()
{
	if (__instance == NULL) __instance = new CGrid();
	return __instance;
}

void CGrid::GetListObject(vector<LPGAMEOBJECT>& ListObj, float cam_x, float cam_y)
{
	ListObj.clear();
	//CScene* scene = CScene::GetInstance();
	unordered_map<int, LPGAMEOBJECT> mapObject;


	int top = (int)(cam_y) / GRID_CELL_HEIGHT;
	int bottom = (int)(cam_y + SCREEN_HEIGHT) / GRID_CELL_HEIGHT;
	

	int left = (int)(cam_x) / GRID_CELL_WIDTH;
		if(left > 0)left--;
	int right = (int)(cam_x + SCREEN_HEIGHT) / GRID_CELL_WIDTH;
		right++;

	for (int i = top; i <= bottom; i++)
	{
		for (int j = left; j <= right; j++)
		{
			for (UINT k = 0; k < cells[i][j].size(); k++)
			{
				if (cells[i][j].at(k)->GetState() != TORCH_STATE_ITEM_NOT_EXSIST || dynamic_cast<CEnemy*>(cells[i][j].at(k))) // còn tồn tại || enemy
				{
					if (mapObject.find(cells[i][j].at(k)->GetID()) == mapObject.end()) // chưa có trong map
						mapObject[cells[i][j].at(k)->GetID()] = cells[i][j].at(k);
				}
			}
		}
	}
	for (auto& x : mapObject)
	{
		ListObj.push_back(x.second);
	}
	ListObj.push_back(CBoss::GetInstance());
	//scene = NULL;
}
void CGrid::LoadObject(char* filename)
{
	for (int i = 0; i < GRID_ROW_MAX; i++)
		for (int j = 0; j < GRID_COLUMN_MAX; j++)
		{
			cells[i][j].clear();
		}

	//listBrick.clear();
	ifstream inFile(filename);

	int id, grid_x, grid_y, type, trend, id_item, nx, ny, object;
	float x, y, w, h;

	if (inFile)
	{
		while (inFile >> id >> grid_x >> grid_y >> type >> trend >> x >> y >> w >> h >> id_item >> object)
		{
			Insert(id ,grid_x, grid_y, type, trend, x, y, w, h, id_item, object);
		}
		inFile.close();
	}
}
void CGrid::Insert(int id, int grid_x, int grid_y, int type, int trend, float x, float y, float w, float h, int id_item, int object)
{
	CGameObject* obj = GetNewObject(type, trend, x, y, w, h, id_item, object);
	if (obj == NULL)
		return;

	obj->SetTrend(trend);
	obj->SetID(id);
	/*if (obj->GetType() == eType::BRICK_2)
		listBrick.push_back(obj);*/
	cells[grid_x][grid_y].push_back(obj);

}
CGameObject* CGrid::GetNewObject( int type, int trend, int x, int y, int w, int h, int id_item, int object)
{
	switch (object)
	{
	case eType::ID_BRICK:
		return new CBrick(x, y, id_item, type, w, h);
	case eType::ID_TORCH:
		return new CTorch(x, y, id_item, type);
	case eType::ID_HIDDEN:
		return new CHidenObject(x, y, type);
	case eType::STAIR_DOWN: return new CHidenObject(x, y, type, trend, -1);
	case eType::STAIR_UP: return new CHidenObject(x, y, type, trend, 1);
	case eType::GATE: return new CGate(x, y);
	case eType::PANTHER: return new CPanther(x, y, id_item);
	case eType::FISHMEN: return new CFishman(x, y, id_item);
	case eType::GHOST: return new CGhost(x, y, id_item);
	case eType::BAT: return new CBat(x, y, id_item);
	case eType::MONEY_5: return new CItemMoney(x, y, MONEY_5);
	default:
		return NULL;
	}
}


