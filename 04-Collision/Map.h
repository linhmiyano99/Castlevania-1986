#ifndef __CMAP_H__

#define __CMAP_H__



#include "Sprites.h"
#include "Textures.h"
#include "Sprites.h"

#define TILE_SIZE 64
#define BRICK_SIZE 32

using namespace std;

class CMap
{
private:
	int _scene;
	int _column;
	int _row;
	int TileMap[200][200];
	static CMap* __instance;
public:
	static CMap* GetInstance();
	CMap(int i = 1);
	int getTile(int x, int y);
	void LoadMap();
	void DrawMap();
	float GetWidth() { return 64 * _column; }
	float GetHeight() { return 64 * _row; }
	void SetMap(int id);
};
#endif // !__CMAP_H__