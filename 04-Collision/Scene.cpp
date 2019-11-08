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
	isAutoTran = false;
	auto_tran = 0;
}


void CScene::LoadResoure()
{
	CManagementTexture* manage = new CManagementTexture();

	objects.clear();

	dagger = CDagger::GetInstance();
	objects.push_back(dagger);
	if (id == 0) {
		map->SetMap(0);
		simon = CSimon::GetInstance();
		simon->SetPosition(0.0f, 20.0f);
		objects.push_back(simon);

		LoadObject("map/Obj1.txt");
	}
	else
	{
		map->SetMap(1);


		dagger = CDagger::GetInstance();
		objects.push_back(dagger);

		simon = CSimon::GetInstance();
		simon->SetPosition(3205.0f, 20.0f);
		objects.push_back(simon);
		LoadObject("map/Obj2.txt");
		
	}
}
		
void CScene::LoadSimon()
{
	float simon_x, simon_y;
	simon = CSimon::GetInstance();
	simon->GetPosition(simon_x, simon_y);
	if (id == 1)
	{
		simon->SetPosition(0.0f, 20.0f);		
	}
	else if (id == 2)
	{
		if (simon_y < 190)
			simon->SetPosition(simon_x, simon_y);
		else
			simon->SetPosition(simon_x - 20, simon_y - 65);
	}
	else if (id == 3)
	{
		simon->SetPosition(simon_x + 15, simon_y + 65);
	}
	else if (id == 4)
	{
		simon->SetPosition(simon_x + 20, simon_y);
	}
	else
	{		

	}
}

void CScene::Update(DWORD dt)
{
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
	}

}
void CScene::Render() 
{
	map->DrawMap();

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(50000)->Draw(cx, cy);
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
		return 3038;
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
		return 3140;
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
void CScene::LoadObject(char* filename)
{

	//objects.clear();
	ifstream inFile(filename);

	int id, type, trend, id_item, nx, ny;
	float x, y, w, h;

	if (inFile)
	{
		while (inFile >> id >> type >> trend >> x >> y >> w >> h >> id_item)
		{
			if (type == eType::BRICK_1 || type == eType::BRICK_2)
			{
				for(int i = 0; i < w / h; i++)
					Insert(id, type, trend, x + i * 32, y, w, h, id_item);
			}
			else
				Insert(id, type, trend, x, y, w, h, id_item);
		}
		inFile.close();
	}
}
void CScene::Insert(int id, int type, int trend, float x, float y, float w, float h,int id_item)
{
	CGameObject* obj = GetNewObject(type, trend, x, y, w, h, id_item);
	if (obj == NULL)
	{
		DebugOut(L"[Insert Object Fail] : object is not create!\n");
		return;
	}
	obj->SetTrend(trend);

	objects.push_back(obj);
}
CGameObject* CScene::GetNewObject(int type, int trend, int x, int y, int w, int h, int id_item)
{
	if (type == eType::BRICK_1) return new CBrick(x, y);
	if (type == eType::BRICK_2) return new CBrick(x, y, 1);
	if (type == eType::TORCH) return new CTorch(x, y, id_item);
	if (type == eType::CANDLE) return new CTorch(x, y, id_item, 1);
	if (type == eType::OBJECT_HIDDEN_DOOR) return new CHidenObject(x, y);
	if (type == eType::STAIR_DOWN) return new CHidenObject(x, y, HIDENOBJECT_TYPE_DOWNSTAIR, trend, -1);
	if (type == eType::STAIR_UP) return new CHidenObject(x, y, HIDENOBJECT_TYPE_UPSTAIR, trend, 1);
	if (type == eType::GATE) return new CGate(x, y);
	if (type == eType::PANTHER) return new CPanther(x, y);
	if (type == eType::FISHMEN) return new CFishman(x, y);
	if (type == eType::GHOST) return new CGhost(x, y);
	if (type == eType::BOSS) return new CBoss(x, y);
	if (type == eType::BAT) return new CBat(x, y);

	return NULL;
}
void CScene::TranScene(float _x)
{
	auto_tran = _x;
	isAutoTran = true;

}
