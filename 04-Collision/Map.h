#ifndef __CMAP_H__

#define __CMAP_H__



#include "Sprites.h"
#include "Textures.h"
#include "Sprites.h"

using namespace std;

class CMap
{
private:
	int _scene;
	int _column;
	int _row;
	int TileMap[200][200];
public:
	CMap(int i = 0);
	int getTile(int x, int y);
	void LoadMap();
	void DrawMap();
};
#endif // !__CMAP_H__