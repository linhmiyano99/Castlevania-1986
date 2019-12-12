#include "Map.h"
#include "fstream"
#include "Game.h"
#include "Define.h"

CMap* CMap::__instance = NULL;

CMap* CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}


CMap::CMap(int i)
{
	SetMap(i);
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
		inFile.open("texture/map.txt");
		break;
	case 1:
		inFile.open("texture/map2.txt");
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

	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	if (cam_y == 0)
	{
		for (int i = (int)cam_y / TILE_SIZE; i < (int)(cam_y + SCREEN_HEIGHT) / TILE_SIZE + 2; i++)
		{
			for (int j = (int)cam_x / TILE_SIZE; j < (int)(cam_x + SCREEN_WIDTH) / TILE_SIZE + 3; j++)
			{
				if (!(i < 0 || j >= _column))
					CSprites::GetInstance()->Get(getTile(i, j))->Draw(TILE_SIZE * j, TILE_SIZE * i + 40);
			}
		}
	}
	else
	{
		for (int i = (int)cam_y / TILE_SIZE; i < 12; i++)
		{
			for (int j = (int)cam_x / 64; j < (int)(cam_x + SCREEN_WIDTH) / TILE_SIZE + 3; j++)
			{
				if (!(i < 0 || j >= _column))
				{
					CSprites::GetInstance()->Get(getTile(i, j))->Draw(TILE_SIZE * j, TILE_SIZE * i + 80);
				}

			}
		}
	}
	if (_scene == 0)
	{
		for (int i = (int)cam_x / TILE_SIZE; i <= (int)(cam_x + SCREEN_WIDTH) / BRICK_SIZE; i++)
			CSprites::GetInstance()->Get(9999)->Draw(i * BRICK_SIZE, 360);
	}
}


