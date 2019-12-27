#include "Sprites.h"
#include "Game.h"
#include "debug.h"
#include "fstream"
#include "Textures.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}
CSprite::CSprite()
{
	this->id = 0;
	this->left = 0;
	this->top = 0;
	this->right = 0;
	this->bottom = 0;
	this->texture = NULL;
}
CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha)
{
	//CGame* game = CGame::GetInstance();
	CGame::GetInstance()->Draw(x, y, texture, left, top, right, bottom, alpha);
}
void CSprite::DrawCam(float x, float y, int alpha)
{
	//CGame* game = CGame::GetInstance();
	CGame::GetInstance()->DrawFlipX(x, y, texture, left, top, right, bottom, alpha);
}
//void CSprite::DrawStatic(float x, float y)
//{
//	CGame* game = CGame::GetInstance();
//	game->DrawStatic(x, y, texture, left, top, right, bottom);
//}
void CSprite::DrawFlipX(float x, float y, int alpha) {
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;

	D3DXVECTOR2 top_left = D3DXVECTOR2(x, y);

	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;

	spriteHandler->SetTransform(&finalMt);

	x -= getwidth();

	this->DrawCam(x , y, alpha);

	spriteHandler->SetTransform(&oldMt);
}
void CSprite::load(std::ifstream& inFile)
{
	string garbage;
	int idTexture;
	inFile >> garbage >> id;
	inFile >> garbage >> left;
	inFile >> garbage >> top;
	inFile >> garbage >> right;
	inFile >> garbage >> bottom;
	inFile >> garbage >> idTexture;
	CTextures* textures = CTextures::GetInstance();
	texture = textures->Get(idTexture);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	//LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = new CSprite(id, left, top, right, bottom, tex);
}

void CSprites::Add(LPSPRITE lpsprite)
{
	sprites[lpsprite->getID()] = lpsprite;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}



void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	//LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(CSprites::GetInstance()->Get(spriteId), t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int trend, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
		}

	}
	if(trend <0)
		frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
	else
		frames[currentFrame]->GetSprite()->DrawFlipX(x, y, alpha);
}
void CAnimation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

CAnimations* CAnimations::__instance = NULL;

CAnimations* CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}