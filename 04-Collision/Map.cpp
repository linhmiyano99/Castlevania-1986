#ifndef __MAP_H_
#define __MAP_H




#include "Map.h"
#include "fstream"

CMap::CMap(int i)
{
	_scene = i;
	switch (i)
	{
	case 0:
		_column = 24;
		_row = 5;
		break;
	case 1:
		_column = 88;
		_row = 12;
		break;
	default:
		break;
	}
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
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++) // ngay đây dư 1 nên... pla pla..
		{
			CSprites::GetInstance()->Get(getTile(i, j))->Draw(64 * j, 64 * i + 40);
		}
	}
}
#endif // !__MAP_H_