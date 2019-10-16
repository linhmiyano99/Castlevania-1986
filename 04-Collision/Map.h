#include "Sprites.h"
#include "Textures.h"
#include "Sprites.h"

using namespace std;

class CMap
{

private:

	int TileMap[200][200];
public:
	int getTile(int x, int y);
	void LoadMap();
	void DrawMap();
};