

#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	CSprite();

	void Draw(float x, float y, int alpha = 255);
	//void DrawStatic(float x, float y);
	void DrawFlipX(float x, float y, int alpha= 255);
	void DrawCam(float x, float y, int alpha = 255);
	int getHeight() { return bottom - top; }
	int getwidth() { return right - left; }
	void load(std::ifstream& inFile);
	int getID() { return id; }
};

typedef CSprite* LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites* __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Add(LPSPRITE lpsprite);
	LPSPRITE Get(int id);

	static CSprites* GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame* LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int trend, int alpha = 255);
	void Render(float x, float y, int alpha = 255);
	int GetCurrentFrame() { return currentFrame; }
	void ResetFrame(){ lastFrameTime = -1; currentFrame = -1; }
	int GetLastFrame() { return frames.size() - 1; }
	void SetFrame(int n) { if (n > -1 && n <= GetLastFrame()) currentFrame = n; }
};

typedef CAnimation* LPANIMATION;

class CAnimations
{
	static CAnimations* __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations* GetInstance();
};

