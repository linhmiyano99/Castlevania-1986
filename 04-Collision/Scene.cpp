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


		CTorch* torch0 = new CTorch(3);
		torch0->SetPosition(190, 300);
		objects.push_back(torch0);

		CTorch* torch1 = new CTorch(1);
		torch1->SetPosition(416, 300);
		objects.push_back(torch1);

		CTorch* torch2 = new CTorch(1);
		torch2->SetPosition(640, 300);
		objects.push_back(torch2);

		CTorch* torch3 = new CTorch(2);
		torch3->SetPosition(864, 300);
		objects.push_back(torch3);


		for (int i = 0; i < 96; i++)
		{
			CBrick* brick = new CBrick();
			brick->SetPosition(i * 32, 360);
			objects.push_back(brick);
		}
		hiden = new CHidenObject();
		hiden->SetPosition(1364, 250);
		objects.push_back(hiden);
	}
	else
	{
		map->SetMap(1);

		dagger = CDagger::GetInstance();
		objects.push_back(dagger);

		simon = CSimon::GetInstance();
		simon->SetPosition(0.0f, 20.0f);
		objects.push_back(simon);


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

		CEnemy* enemy = new CEnemy();
		enemy->SetPosition(500, 250);
		enemy->SetSpeed(-0.05f, 0);
		objects.push_back(enemy);

		for (int i = 0; i < 96; i++)
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
		CHidenObject *hiden = new CHidenObject(HIDENOBJECT_TYPE_DOWNSTAIR);
		hiden->SetPosition(1216, 300);
		objects.push_back(hiden);
		CHidenObject *hiden2 = new CHidenObject(HIDENOBJECT_TYPE_UPSTAIR);
		hiden2->SetPosition(1376, 170);
		objects.push_back(hiden2);
		
	}
}

void CScene::Update(DWORD dt)
{
	float cx, cy;
	simon->GetPosition(cx, cy);


	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// Update camera to follow simon
	cx -= SCREEN_WIDTH / 2 - 40;
	cy -= SCREEN_HEIGHT / 2;
	if (id == 0)
	{
		
		if (cx < 0) cx = 0; if (cx > 966) cx = 966;
	}
	else
	{
		if (cx < 0) cx = 0; if (cx > 88*64) cx = 88*64;
	}
	game = CGame::GetInstance();
	game->SetCamPos(cx, 0);
}
void CScene::Render() 
{
	map->DrawMap();

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
}
void CScene::SetMap(int id)
{
	this->id = id;
}