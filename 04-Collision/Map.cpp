#include "Map.h"
#include "fstream"
#include "Game.h"

CMap* CMap::__instance = NULL;

CMap* CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}


CMap::CMap(int i)
{
	_scene = i;
	switch (i)
	{
	case 0:
		_column = 24;
		_row = 6;
		break;
	case 1:
		_column = 88;
		_row = 12;
		break;
	default:
		break;
	}
	LoadMap();
}
void CMap::SetMap(int i)
{
	_scene = i;
	switch (i)
	{
	case 0:
		_column = 24;
		_row = 6;
		break;
	case 1:
		_column = 88;
		_row = 12;
		break;
	default:
		break;
	}
	LoadMap();
}

void CMap::LoadMap()
{
	ifstream inFile;
	switch (_scene)
	{
	case 0:
		inFile.open("map/map.txt");
		break;
	case 1:
		inFile.open("map/map2.txt");
		break;
	default:
		break;
	}
	

	// If the file opened correctly then call load methods

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			inFile >> TileMap[i][j];
		}
	}
}
int CMap::getTile(int x, int y)
{
	return TileMap[x][y];
}


void CMap::DrawMap()
{

	//CGame* game = CGame::GetInstance();
	//float cam_x, cam_y;
	//game->GetCamPos(cam_x, cam_y);

	//for (int i = (int)(cam_y) / 64 - 1; i < (int)(cam_y + 560) / 64 + 3; i++)
	//	for (int j = (int)(cam_x) / 64 - 1; j < (int)(cam_x + 460) / 64 + 3; j++)
	//	{
	//		if (!(i < 0 || i > _row || j < 0 || j > _column))
	//		{
	//			CSprites* sprites = CSprites::GetInstance();
	//			//sprites->Get(getTile(i, j))->DrawStatic(64 * j - cam_x, 64 * i - cam_y + 40);
	//			sprites->Get(getTile(i, j))->Draw(64 * j , 64 * i - + 40);

	//		}
	//	}

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 88; j++)
		{
			//if (!(i < 0 || i > _row || j < 0 || j > _column))
			{
				CSprites* sprites = CSprites::GetInstance();
				//sprites->Get(getTile(i, j))->DrawStatic(64 * j - cam_x, 64 * i - cam_y + 40);
				sprites->Get(getTile(i, j))->Draw(64 * j, 64 * i  +40);

			}
		}
}


