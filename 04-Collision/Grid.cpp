#include "Grid.h"


void CGrid::GetListObject(vector<LPGAMEOBJECT>& ListObj)
{
	ListObj.clear();

	unordered_map<int, LPGAMEOBJECT> mapObject;
	float cam_x, cam_y;
	CGame* game = new CGame();
	game->GetCamPos(cam_x, cam_y);

	int bottom = (int)((cam_y + SCREEN_HEIGHT - 1) / SCREEN_HEIGHT);
	int top = (int)((cam_y + 1) / SCREEN_HEIGHT);

	int left = (int)((cam_x + 1) / SCREEN_WIDTH);
	int right = (int)((cam_x + SCREEN_WIDTH - 1) / SCREEN_WIDTH);

	
	for (auto& x : mapObject)
	{
		ListObj.push_back(x.second);
	}
}