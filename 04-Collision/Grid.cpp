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


CGrid* CGrid::__instance = NULL;

CGrid* CGrid::GetInstance()
{
	if (__instance == NULL) __instance = new CGrid();
	return __instance;
}

void CGrid::GetListObject(vector<LPGAMEOBJECT>& ListObj, float cam_x, float cam_y)
{
	ListObj.clear();
	CScene* scene = CScene::GetInstance();

	int top = (int)(cam_y) / GRID_CELL_HEIGHT;
	int bottom = (int)(cam_y + SCREEN_HEIGHT) / GRID_CELL_HEIGHT;
	

	int left = (int)(cam_x) / GRID_CELL_WIDTH;
	if (left > 0 && scene->GetScene() > 0 && scene->GetScene() < 5)
		left--;
	int right = (int)(cam_x + SCREEN_HEIGHT) / GRID_CELL_WIDTH;
	if (right < GRID_COLUMN_MAX && scene->GetScene() > 0 && scene->GetScene() < 5)
		right++;

	for (int i = top; i <= bottom; i++)
	{
		for (int j = left; j <= right; j++)
		{
			for (UINT k = 0; k < cells[i][j].size(); k++)
			{
				ListObj.push_back(cells[i][j].at(k));
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
	CAxe* axe = CAxe::GetInstance();
	ListObj.push_back(axe);
	CHollyWatter *holly = CHollyWatter::GetInstance();
	ListObj.push_back(holly);
	CBoss* boss = CBoss::GetInstance();
	ListObj.push_back(boss);
	simon = NULL;
	dagger = NULL;
	axe = NULL;
	scene = NULL;
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
			Insert(type, trend, x, y, w, h, id_item);
		}
		inFile.close();
	}
}
void CGrid::Insert(int type, int trend, float x, float y, float w, float h, int id_item)
{

	int top = (int)(y) / GRID_CELL_HEIGHT;
	int bottom = (int)(y + h) / GRID_CELL_HEIGHT;
	int left = (int)(x) / GRID_CELL_WIDTH;
	int right = (int)(x + w) / GRID_CELL_WIDTH;

	CGameObject* obj = GetNewObject(type, trend, x, y, w, h, id_item);
	if (obj == NULL)
		return;

	obj->SetTrend(trend);
	if (obj->GetType() == eType::BRICK_2)
		listBrick.push_back(obj);
	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			cells[i][j].push_back(obj);
	obj = NULL;

}
CGameObject* CGrid::GetNewObject(int type, int trend, int x, int y, int w, int h, int id_item)
{
	switch (type)
	{
	case eType::BRICK_1: return new CBrick(x, y, 0, eType::BRICK_1);
	case eType::BRICK_2: return new CBrick(x, y, 0, eType::BRICK_2, w, h);
	case eType::BRICK_3: return new CBrick(x, y, id_item, eType::BRICK_3);
	case eType::BRICK_4: return new CBrick(x, y, id_item, eType::BRICK_4);
	case eType::BRICK_5: return new CBrick(x, y, id_item, eType::BRICK_5);
	case eType::TORCH: return new CTorch(x, y, id_item, eType::TORCH);
	case eType::CANDLE: return new CTorch(x, y, id_item, eType::CANDLE);
	case eType::OBJECT_HIDDEN_DOOR: return new CHidenObject(x, y);
	case eType::STAIR_DOWN: return new CHidenObject(x, y, HIDENOBJECT_TYPE_DOWNSTAIR, trend, -1);
	case eType::STAIR_UP: return new CHidenObject(x, y, HIDENOBJECT_TYPE_UPSTAIR, trend, 1);
	case eType::OBJECT_HIDDEN_FISHMAN: return new CHidenObject(x, y, HIDENOBJECT_TYPE_FISHMAN);
	case eType::OBJECT_HIDDEN_GHOST_1: return new CHidenObject(x, y, HIDENOBJECT_TYPE_GHOST_1);
	case eType::OBJECT_HIDDEN_GHOST_STOP_1: return new CHidenObject(x, y, HIDENOBJECT_TYPE_GHOST_STOP_1);
	case eType::OBJECT_HIDDEN_GHOST_2: return new CHidenObject(x, y, HIDENOBJECT_TYPE_GHOST_2, w, h);
	case eType::OBJECT_HIDDEN_GHOST_UP: return new CHidenObject(x, y, HIDENOBJECT_TYPE_GHOST_UP, w, h);
	case eType::OBJECT_HIDDEN_GHOST_DOWN: return new CHidenObject(x, y, HIDENOBJECT_TYPE_GHOST_DOWN, w, h);
	case eType::OBJECT_HIDDEN_PANTHER_JUMP: return new CHidenObject(x, y, HIDENOBJECT_TYPE_PANTHER_JUMP, w, h);
	case eType::OBJECT_HIDDEN_BRICK: return new CHidenObject(x, y, HIDENOBJECT_TYPE_BRICK, w, h);
	case eType::OBJECT_HIDDEN_GATE_OPEN: return new CHidenObject(x, y, HIDENOBJECT_TYPE_GATE_OPEN, w, h);
	case eType::GATE: return new CGate(x, y);
	case eType::PANTHER: return new CPanther(x, y);
	case eType::FISHMEN: return new CFishman(x, y);
	case eType::GHOST: return new CGhost(x, y, id_item);
	case eType::BAT: return new CBat(x, y);
	default:
		break;
	}
	

	return NULL;
}


