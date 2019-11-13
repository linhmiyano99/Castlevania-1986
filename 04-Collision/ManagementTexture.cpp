#include "MagagementTexture.h"
#include "Simon.h"
#include "Torch.h"
#include "Brick.h"
#include "VampireKiller.h"

CManagementTexture::CManagementTexture()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_BBOX, L"map\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX, L"texture\\texture.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex = textures->Get(ID_TEX);

	ifstream inFile("texture/sprites.txt");

	// If the file opened correctly then call load methods
	while (inFile)
	{
		CSprite* sprite = new CSprite();
		sprite->load(inFile);
		sprites->Add(sprite);
	}



#pragma region add sprites Simon 

	LPANIMATION ani;

	ani = new CAnimation(100); //simon idle left
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(30); //simon trans idle left
	ani->Add(10400);
	ani->Add(10401);
	ani->Add(10402);
	ani->Add(10403);
	animations->Add(399, ani);

	ani = new CAnimation(100);// simon walk left
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add(401, ani);

	ani = new CAnimation(100);// simon jump left
	ani->Add(10005);
	animations->Add(402, ani);

	ani = new CAnimation(100);// simon sit left
	ani->Add(10005);
	animations->Add(403, ani);

	ani = new CAnimation(100);// simon stand attack
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(404, ani);

	ani = new CAnimation(100);//simon sit attack
	ani->Add(10016);
	ani->Add(10014);
	ani->Add(10015);
	animations->Add(405, ani);

	ani = new CAnimation(100);//simon go up stair
	ani->Add(10100);
	ani->Add(10101);
	animations->Add(406, ani);

	ani = new CAnimation(100);//simon go down stair
	ani->Add(10102);
	ani->Add(10103);
	animations->Add(407, ani);

	ani = new CAnimation(100);//simon hurt
	ani->Add(10104);
	animations->Add(408, ani);
	
	ani = new CAnimation(100);//simon idle up
	ani->Add(10100);
	animations->Add(409, ani);
	
	ani = new CAnimation(100);//simon idle down
	ani->Add(10102);
	animations->Add(410, ani);

#pragma endregion

#pragma region Add sprites Map
	int index = 0;
	int _x = 4, _y = 699;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			sprites->Add(index++, j * 64 + _x, i * 64 + _y, j * 64 + 64 +_x, i * 64 + 64 +_y, tex);
		}
	}
	index = 20000;
	_x = 4, _y = 970;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			sprites->Add(index++, j * 64 + _x, i * 64 + _y, j * 64 + 64 + _x, i * 64 + 64 + _y, tex);
		}
	}

#pragma endregion

#pragma region Add sprites Ground

	ani = new CAnimation(100);
	ani->Add(9999);
	animations->Add(499, ani); //ground1
	
	ani = new CAnimation(100);
	ani->Add(10000);
	animations->Add(500, ani); //ground2

	ani = new CAnimation(100);
	ani->Add(9998);
	animations->Add(498, ani); //ground3

#pragma endregion

#pragma region Add sprites Torch & Candle
	

	ani = new CAnimation(100);
	ani->Add(11000);
	ani->Add(11001);
	animations->Add(501, ani); // torch

	ani = new CAnimation(100);
	ani->Add(11002);
	ani->Add(11003);
	animations->Add(502, ani);//candle


#pragma endregion

#pragma region Add sprites Vampire Killer
	

	ani = new CAnimation(100);
	ani->Add(12000);
	ani->Add(12001);
	ani->Add(12002);
	animations->Add(600, ani); // lv1
	
	ani = new CAnimation(100);
	ani->Add(12010);
	ani->Add(12011);
	ani->Add(12012);
	animations->Add(601, ani);//lv2
	
	ani = new CAnimation(100);
	ani->Add(12020);
	ani->Add(12021);
	ani->Add(12022);
	animations->Add(602, ani);//lv3

	
#pragma endregion

#pragma region Add sprites items
	ani = new CAnimation(100);
	ani->Add(13000);
	animations->Add(700, ani);//Whip upgrade - item

	ani = new CAnimation(100);
	ani->Add(13001);
	animations->Add(701, ani);//dragger - item

	ani = new CAnimation(100);
	ani->Add(13002);
	animations->Add(702, ani);//heart - item

	ani = new CAnimation(100);
	ani->Add(13003);
	animations->Add(703, ani);//smallheart - item

	ani = new CAnimation(100);
	ani->Add(13004);
	animations->Add(704, ani);//chicken - item

	ani = new CAnimation(100);
	ani->Add(13005);
	animations->Add(705, ani);//money - item

	ani = new CAnimation(100);
	ani->Add(13006);
	animations->Add(706, ani);//money - item

	ani = new CAnimation(100);
	ani->Add(13007);
	animations->Add(707, ani);//money - item

	ani = new CAnimation(100);
	ani->Add(13008);
	animations->Add(708, ani);//money - item

	ani = new CAnimation(100);
	ani->Add(13009);
	animations->Add(709, ani);//clock - item

	ani = new CAnimation(100);
	ani->Add(13010);
	animations->Add(710, ani);//axe - item

	ani = new CAnimation(100);
	ani->Add(13011);
	animations->Add(711, ani);//cross - item


#pragma endregion

#pragma region Add sprites fire after torch not exsist
	ani = new CAnimation(100);
	ani->Add(13100);
	ani->Add(13101);
	ani->Add(13102);
	animations->Add(800, ani); // fire after torch not exsist
#pragma endregion

#pragma region Add sprites broken brick after brick not exsist
	ani = new CAnimation(100);
	ani->Add(13100);
	ani->Add(13101);
	ani->Add(13102);
	animations->Add(800, ani); // fire after torch not exsist
#pragma endregion

#pragma region Add enemies
	ani = new CAnimation(100);
	ani->Add(30000);
	ani->Add(30001);
	animations->Add(1000, ani); // ghost go
	
	ani = new CAnimation(100);
	ani->Add(30002);
	animations->Add(1001, ani); // panther sit 

	ani = new CAnimation(100);

	ani->Add(30003);
	ani->Add(30004);
	ani->Add(30005);
	animations->Add(1002, ani); // panther run 

	ani = new CAnimation(100);
	ani->Add(30006);
	ani->Add(30007);
	ani->Add(30008);
	ani->Add(30009);
	animations->Add(1003, ani); // bat run 

	ani = new CAnimation(100);
	ani->Add(30012);
	animations->Add(1004, ani); // fishman jump 
	
	ani = new CAnimation(100);
	ani->Add(30011);
	ani->Add(30012);
	animations->Add(1005, ani); // fishman walking

	ani = new CAnimation(400);
	ani->Add(30010);
	ani->Add(30012);
	animations->Add(1006, ani); // fishman attack

	ani = new CAnimation(100);
	ani->Add(30013);
	animations->Add(1090, ani); // boss sleep

	ani = new CAnimation(100);
	//ani->Add(30013);
	ani->Add(30014);
	ani->Add(30015);
	animations->Add(1091, ani); // boss run 

	ani = new CAnimation(100);
	ani->Add(70000);
	animations->Add(1100, ani); // smallball 

#pragma endregion

#pragma region Add Door

	ani = new CAnimation(100);
	ani->Add(40000);
	animations->Add(1200, ani); // door close

	ani = new CAnimation(2000);
	ani->Add(40000);
	ani->Add(40000);
	ani->Add(40002);
	ani->Add(40001);
	ani->Add(40000);
	ani->Add(40000);
	ani->Add(40000);

	
	animations->Add(1201, ani); // door open

#pragma endregion


}