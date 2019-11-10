
#include "Scene.h"
#include "Enemy.h"


CScene* CScene::__instance = NULL;

CScene* CScene::GetInstance()
{
	if (__instance == NULL) __instance = new CScene();
	return __instance;
}


CScene::CScene(int id)
{
	this->id = id;
	map = CMap::GetInstance();
	game = CGame::GetInstance();
	board = CBoard::GetInstance();
	grid = CGrid::GetInstance();
	isAutoTran = false;
	auto_tran = 0;
	_stage = 1;
}


void CScene::LoadResoure()
{
	CManagementTexture* manage = new CManagementTexture();

	objects.clear();

	dagger = CDagger::GetInstance();
	objects.push_back(dagger);
	if (id == 0) {
		map->SetMap(0);
		
		grid->LoadObject("map/Obj1.txt");
		simon = CSimon::GetInstance();
		simon->SetPosition(0.0f, 20.0f);
		objects.push_back(simon);
	}
	else
	{
		map->SetMap(1);
		
		grid->LoadObject("map/Obj2.txt");
		dagger = CDagger::GetInstance();
		objects.push_back(dagger);
		simon = CSimon::GetInstance();
		simon->SetPosition(3205.0f, 20.0f);
		objects.push_back(simon);
		boss = CBoss::GetInstance();
		boss->SetPosition(5340.0f, 95.0f);
		objects.push_back(boss);

	}
}
		
void CScene::LoadSimon()
{
	float simon_x, simon_y;
	simon = CSimon::GetInstance();
	simon->GetPosition(simon_x, simon_y);
	smallballs.clear();
	if (id == 1)
	{
		simon->SetPosition(0.0f, 20.0f);		
	}
	else if (id == 2)
	{
		if (simon_y < 190)
			simon->SetPosition(simon_x, simon_y);
		else
			simon->SetPosition(simon_x - 15, simon_y - 65);
	}
	else if (id == 3)
	{
		simon->SetPosition(simon_x + 15, simon_y + 65);
	}
	else if (id == 4)
	{
		simon->SetPosition(simon_x - 15, simon_y - 65);
	}
	else
	{		

	}
}

void CScene::Update(DWORD dt)
{
	board->Update(dt);
	for each (LPGAMEOBJECT var in smallballs)
	{
		var->Update(dt);
	}
	float c_x, c_y;

	game->GetCamPos(c_x, c_y);

	if (isAutoTran)
	{

		if (c_x < auto_tran)
		{
			if (c_x < auto_tran - SCREEN_WIDTH / 2)
				game->SetCamPos(c_x + 1.0f, c_y);
			else
			{
				if (simon->IsAutoGo())
					simon->Update(dt);
				else
					game->SetCamPos(c_x + 1.0f, c_y);
			}

		}
		else
		{
			if (id == 1)
				id = 2;
			else
				id = 4;
			isAutoTran = false;
			_stage++;
		}
	}
	else
	{
		float cx, cy;
		simon->GetPosition(cx, cy);


		if (cy >= 370 && id != 3)
		{
			SetMap(3);
			LoadSimon();
			cy = 430;
		}
		else if (id == 3)
		{
			if (cy < 465)
			{
				if ((cx > 3070 && cx < 3290) || (cx > 3740 && cx < 3940) && simon->IsOnStair())
				{
					id = 2;
					SetMap(2);
					LoadSimon();
					cy = 0;
				}
				else
					cy = 430;

			}
			else
				cy = 430;
		}
		else if (id == 4 && cx > 5356)
		{
			id = 5;
		}
		else
			cy = 0;
		
		// Update camera to follow simon
		cx -= SCREEN_WIDTH / 2 - 40;
		//cy -= SCREEN_HEIGHT / 2 + 40;

		vector<LPGAMEOBJECT> coObjects;
		for (int i = 0; i < objects.size(); i++)
		{
			coObjects.push_back(objects[i]);
		}

		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &coObjects);
		}



		if (cx < GetLeft())
			cx = GetLeft();
		if (id != 4)
		{
			if (cx > GetRight() - SCREEN_WIDTH + 10)
				cx = GetRight() - SCREEN_WIDTH + 10;
		}


		game->SetCamPos(cx, cy);
		grid->GetListObject(objects, cx , cy);

	}

}
void CScene::Render() 
{
	map->DrawMap();

	for each (LPGAMEOBJECT var in smallballs)
	{
		var->Render();
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	CSprites* sprites = CSprites::GetInstance();
	board->Render();
}
void CScene::SetMap(int id)
{
	this->id = id;
}
int CScene::GetLeft()
{
	if (isAutoTran)
	{
		float c_x, c_y;
		game->GetCamPos(c_x, c_y);
		return c_x;
	}
	switch (id)
	{
	case 0:
		return 0;
	case 1:
		return 0;
	case 2:
		return 3074;
	case 3:
		return 3074;
	case 4:
		return 4096;
	case 5:
		return 5086;
	default:
		return 0;
	}
}
int CScene::GetTop()
{
	switch (id)
	{
	case 0:
	case 1:
	case 2:
	case 4:
	case 5:
		return 40;
	case 3:
		return 430;
	default:
		return 0;
	}
}
int CScene::GetRight()
{
	if (isAutoTran)
	{
		float c_x, c_y;
		game->GetCamPos(c_x, c_y);
		return c_x + SCREEN_WIDTH;
	}
	switch (id)
	{
	case 0:
		return 1536;
	case 1:
		return 3074;
	case 2:
	case 3:
		return 4097;
	case 4:
	case 5:
		return 5632;
	default:
		return 0;
	}
}
int CScene::GetBottom()
{
	switch (id)
	{
	case 0:
	case 1:
	case 2:
	case 4:
	case 5:
		return 384;
	case 3:
		return 768;
	default:
		return 384;
	}
}

void CScene::TranScene(float _x)
{
	auto_tran = _x;
	isAutoTran = true;

}
void CScene::AddSmallBall(LPGAMEOBJECT smallball)
{
	smallballs.push_back(smallball);
}

