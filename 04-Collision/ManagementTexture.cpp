#include "MagagementTexture.h"
#include "Simon.h"
#include "Torch.h"
#include "Brick.h"
#include "VampireKiller.h"

CManagementTexture::CManagementTexture()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_SIMON, L"simon\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_SIMON_TRANS, L"simon\\simon_trans.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_VAMPIREKILLER, L"simon\\morningstar.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_TORCH, L"map\\torch.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_CANDLE, L"map\\candle.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MAP, L"map\\map.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MAP2, L"map\\map2.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GROUND, L"map\\ground.png", D3DCOLOR_XRGB(0, 0, 0));
	textures->Add(ID_TEX_GROUND2, L"map\\ground2.png", D3DCOLOR_XRGB(0, 0, 0));
	textures->Add(ID_TEX_BBOX, L"map\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ITEM, L"item\\items.png", D3DCOLOR_XRGB(128, 0, 0));
	textures->Add(ID_TEX_TORCH_FIRE, L"item\\Torch_fire.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GHOST, L"enemy\\ghost.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texmap = textures->Get(ID_TEX_MAP);
	LPDIRECT3DTEXTURE9 texmap2 = textures->Get(ID_TEX_MAP2);

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
	ani->Add(10004);
	animations->Add(400, ani);

	ani = new CAnimation(1); //simon trans idle left
	ani->Add(10400);
	ani->Add(10004);
	animations->Add(410, ani);

	ani = new CAnimation(100);// simon walk left
	ani->Add(10011);
	ani->Add(10012);
	animations->Add(401, ani);

	ani = new CAnimation(100);// simon jump left
	ani->Add(10201);
	animations->Add(402, ani);

	ani = new CAnimation(100);// simon sit left
	ani->Add(10201);
	animations->Add(403, ani);

	ani = new CAnimation(100);// simon stand attack
	ani->Add(10300);
	ani->Add(10301);
	ani->Add(10302);
	animations->Add(404, ani);

	ani = new CAnimation(100);//simon sit attack
	ani->Add(10310);
	ani->Add(10311);
	ani->Add(10312);
	animations->Add(405, ani);

	ani = new CAnimation(100);//simon go up stair
	ani->Add(10114);
	ani->Add(10115);
	animations->Add(406, ani);

	ani = new CAnimation(100);//simon go down stair
	ani->Add(10114);
	ani->Add(10116);
	animations->Add(407, ani);

#pragma endregion

#pragma region Add sprites Map
	int index = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			sprites->Add(index++, j * 64, i * 64, j * 64 + 64, i * 64 + 64, texmap);
		}
	}
	index = 20000;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			sprites->Add(index++, j * 64, i * 64, j * 64 + 64, i * 64 + 64, texmap2);
		}
	}

#pragma endregion

#pragma region Add sprites Ground
	ani = new CAnimation(100);
	ani->Add(10000);
	animations->Add(500, ani); //ground2

	ani = new CAnimation(100);
	ani->Add(9999);
	animations->Add(499, ani); //ground1
	

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
	ani->Add(13010);
	animations->Add(702, ani);//fire - item


	ani = new CAnimation(100);
	ani->Add(13002);
	animations->Add(704, ani);//heart - item


#pragma endregion

#pragma region Add sprites fire after torch not exsist
	ani = new CAnimation(100);

	ani->Add(14002);
	ani->Add(14001);
	ani->Add(14000);
	animations->Add(800, ani); // fire after torch not exsist
#pragma endregion

#pragma region Add enemies
	ani = new CAnimation(100);

	ani->Add(30000);
	ani->Add(30001);
	animations->Add(10000, ani); // enemy 
#pragma endregion

}