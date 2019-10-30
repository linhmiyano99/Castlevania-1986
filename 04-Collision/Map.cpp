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

	CGame* game = CGame::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);
	if (cam_y == 0)
	{
		for (int i = (int)(cam_y) / 64; i < (int)(cam_y + 560) / 64 + 3; i++)
		{
			for (int j = (int)(cam_x) / 64; j < (int)(cam_x + 460) / 64 + 3; j++)
			{
				sprites->Get(getTile(i, j))->Draw(64 * j, 64 * i + 40);
			}
		}
	}
	else
	{
		for (int i = 0; i < 12; i++)
		{
			for (int j = (int)(cam_x) / 64; j < (int)(cam_x + 460) / 64 + 3; j++)
			{

				sprites->Get(getTile(i, j))->Draw(64 * j, 64 * i + 80);


			}
		}
	}

}


