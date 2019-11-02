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
		simon->SetPosition(5125.0f, 20.0f);
		objects.push_back(simon);


		/*
		{
			CTorch* candle = new CTorch(3, 1);
			candle->SetPosition(190, 300);
			objects.push_back(candle);

			CTorch* candle1 = new CTorch(1, 1);
			candle1->SetPosition(416, 250);
			objects.push_back(candle1);

			CTorch* candle2 = new CTorch(1, 1);
			candle2->SetPosition(640, 300);
			objects.push_back(candle2);

			CTorch* candle3 = new CTorch(2, 1);
			candle3->SetPosition(864, 250);
			objects.push_back(candle3);

			CGhost* enemy = new CGhost();
			enemy->SetPosition(500, 250);
			enemy->SetSpeed(-0.05f, 0);
			objects.push_back(enemy);

			CPanther* enemy2 = new CPanther();
			enemy2->SetPosition(1800, 150);
			enemy2->SetSpeed(0, 0);
			objects.push_back(enemy2);

			for (int i = 0; i < 98; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 394);
				objects.push_back(brick);
			}
			for (int i = 100; i < 112; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 394);
				objects.push_back(brick);
			}
			for (int i = 43; i < 46; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 265);
				objects.push_back(brick);
			}

			for (int i = 47; i < 57; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 200);
				objects.push_back(brick);
			}
			for (int i = 58; i < 63; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 264);
				objects.push_back(brick);
			}
			for (int i = 87; i < 105; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 200);
				objects.push_back(brick);
			}
			for (int i = 104; i < 107; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 264);
				objects.push_back(brick);
			}
			CHidenObject* hiden = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR, 1, -1);
			hiden->SetPosition(1236, 370);
			objects.push_back(hiden);
			CHidenObject* hiden2 = new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR, -1, 1);
			hiden2->SetPosition(1385, 195);
			objects.push_back(hiden2);
			CHidenObject* hiden3 = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR, 1, -1);
			hiden3->SetPosition(1425, 240);
			objects.push_back(hiden3);
			CHidenObject* hiden4 = new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR, -1, 1);
			hiden4->SetPosition(1525, 130);
			objects.push_back(hiden4);
			CHidenObject* hiden5 = new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR, 1, 1);
			hiden5->SetPosition(1790, 130);
			objects.push_back(hiden5);
			CHidenObject* hiden6 = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR, -1, -1);
			hiden6->SetPosition(1890, 240);
			objects.push_back(hiden6);

			CHidenObject* hiden7 = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR, 1, -1);
			hiden7->SetPosition(2580, 370);
			objects.push_back(hiden7);
			CHidenObject* hiden8 = new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR, -1, 1);
			hiden8->SetPosition(2800, 130);
			objects.push_back(hiden8);

			CGate* gate = new CGate();
			gate->SetPosition(3063, 105);
			objects.push_back(gate);

			CGate* gate2 = new CGate();
			gate2->SetPosition(4067, 105);
			objects.push_back(gate2);
		}
	
		{

			for (int i = 94; i < 104; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 200);
				objects.push_back(brick);
			}

			for (int i = 104; i < 107; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 264);
				objects.push_back(brick);
			}

			for (int i = 94; i < 99; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 394);
				objects.push_back(brick);
			}

			for (int i = 100; i < 112; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 394);
				objects.push_back(brick);
			}
			CBat* bat = new CBat();
			bat->SetPosition(3580, 141);
			bat->SetSpeed(0.1f, 0.1f);
			objects.push_back(bat);

			CHidenObject* hiden = new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR, 1, 1);
			hiden->SetPosition(3115, 325);
			objects.push_back(hiden);
			CHidenObject* hiden1 = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR, -1, -1);
			hiden1->SetPosition(3540, 365);
			objects.push_back(hiden1);
			CHidenObject* hiden2 = new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR, 1, 1);
			hiden2->SetPosition(3393, 195);
			objects.push_back(hiden2);
		}

		{
		
			for (int i = 96; i < 110; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 654);
				objects.push_back(brick);
			}

			for (int i = 112; i < 114; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 654);
				objects.push_back(brick);
			}
			for (int i = 116; i < 125; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 654);
				objects.push_back(brick);
			}
			for (int i = 102; i < 104; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 590);
				objects.push_back(brick);
			}

			for (int i = 126; i < 128; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 720);
				objects.push_back(brick);
			}

			for (int i = 124; i < 126; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 780);
				objects.push_back(brick);
			}
			CFishman* fishman = new CFishman();
			fishman->SetPosition(3344, 716);
			objects.push_back(fishman);
			
			CHidenObject* hiden1 = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR, -1, -1);
			hiden1->SetPosition(3240, 560);
			objects.push_back(hiden1);
			CHidenObject* hiden2 = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR, -1, -1);
			hiden2->SetPosition(3930, 610);
			objects.push_back(hiden2);
		}

		{

			for (int i = 116; i < 119; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 390);
				objects.push_back(brick);
			}
			for (int i = 120; i < 176; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 390);
				objects.push_back(brick);
			}
			for (int i = 116; i < 118; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 230);
				objects.push_back(brick);
			}
			for (int i = 118; i < 121; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 262);
				objects.push_back(brick);
			}
			for (int i = 122; i < 135; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 200);
				objects.push_back(brick);
			}
			for (int i = 136; i < 147; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 264);
				objects.push_back(brick);
			}
			for (int i = 170; i < 171; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 330);
				objects.push_back(brick);
			}
			for (int i = 173; i < 176; i++)
			{
				CBrick* brick = new CBrick(1);
				brick->SetPosition(i * 32, 264);
				objects.push_back(brick);
			}


			CHidenObject* hiden = new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR, 1, 1);
			hiden->SetPosition(3717, 320);
			objects.push_back(hiden);
			CHidenObject* hiden2 = new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR, 1, 1);
			hiden2->SetPosition(3805, 205);
			objects.push_back(hiden2); 
			CHidenObject* hiden3 = new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR, 1, 1);
			hiden3->SetPosition(4290, 140);
			objects.push_back(hiden3); 
			CHidenObject* hiden4 = new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR, 1, 1);
			hiden4->SetPosition(4640, 210);
			objects.push_back(hiden4);
			CHidenObject* hiden5= new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR, -1, 1);
			hiden5->SetPosition(5560, 215);
			objects.push_back(hiden5);
			CHidenObject* hiden6 = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR, 1, 1);
			hiden6->SetPosition(4000, 370);
			objects.push_back(hiden6);
			CHidenObject* hiden7 = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR, 1, 1);
			hiden7->SetPosition(4390, 230);
			objects.push_back(hiden7);
			CHidenObject* hiden8 = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR, -1, -1);
			hiden8->SetPosition(4835, 370);
			objects.push_back(hiden8);
			CHidenObject* hiden9 = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR, 1, -1);
			hiden9->SetPosition(5460, 316);
			objects.push_back(hiden9);
			boss = CBoss::GetInstance();
			boss->SetPosition(5311, 100);
			objects.push_back(boss);

		}
		*/
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
		simon->SetPosition(simon_x + 20, simon_y + 65);

	}
	else if (id == 4)
	{
		simon->SetPosition(simon_x + 20, simon_y);
	}
	else
	{
		//simon->SetPosition(simon_x + 20, simon_y);
		
		boss->SetSpeed(0.1f, 0.1f);
	}
}

void CScene::Update(DWORD dt)
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
	//else if (id == 2 && cy <= 140 && cx > 4037)
	//{

	//	id = 4;
	//	SetMap(4);
	//	LoadSimon();
	//}
	else if (id == 4 && cx > 5115)
	{
		id = 5;
		SetMap(5);
		LoadSimon();
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
		if (cx > GetRight() - SCREEN_WIDTH)
			cx = GetRight() - SCREEN_WIDTH;
	}


	game = CGame::GetInstance();
	game->SetCamPos(cx, cy);


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
		return 5116;
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
		return 5119;
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

	int id, type, trend, id_item;
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
	CGameObject* obj = GetNewObject(type, x, y, w, h, id_item);
	if (obj == NULL)
	{
		DebugOut(L"[Insert Object GRID Fail] : Bo tay roi :v Khong tao duoc object!\n");
		return;
	}
	obj->SetTrend(trend);

	objects.push_back(obj);
}
CGameObject* CScene::GetNewObject(int type, int x, int y, int w, int h, int id_item)
{
	if (type == eType::BRICK_1) return new CBrick(x, y);
	if (type == eType::TORCH) return new CTorch(x, y, id_item);
	if (type == eType::OBJECT_HIDDEN_DOOR) return new CHidenObject(x, y);


	return NULL;
}
