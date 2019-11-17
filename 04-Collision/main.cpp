/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 03 - KEYBOARD AND OBJECT STATE

	This sample illustrates how to:

		1/ Process keyboard input
		2/ Control object state with keyboard events
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "fstream"

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "MagagementTexture.h"
#include "Define.h"

#include "Camera.h"

#include "Simon.h"
#include "Map.h"
#include "Torch.h"
#include "WhipUpgrade.h"
#include "ItemDagger.h"
#include "Brick.h"
#include "Dagger.h"

#include "Scene.h"




CGame * game;
CSimon* simon;
CManagementTexture* manage;
CScene* scene;

vector<CGameObject*> objects;


using namespace std;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander* keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		
		break;
	/*case DIK_Z:
		if (game->IsKeyDown(DIK_DOWN))
			simon->SetState(SIMON_STATE_SIT_ATTACK);
		else if (game->IsKeyDown(DIK_UP))
		{
			simon->SetState(SIMON_STATE_ATTACK_DAGGER);
		}
		else
			simon->SetState(SIMON_STATE_STAND_ATTACK);
		break;*/
	case DIK_X:
		break;
	case DIK_DOWN:
		break;
	case DIK_UP:
		simon->SetState(SIMON_STATE_GO_UP);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		if(!simon->IsOnStair())
			simon->SetState(SIMON_STATE_UP);
		break;
	case DIK_Z:
		if (simon->GetState() == SIMON_STATE_SIT_ATTACK)
		{
			if(game->IsKeyDown(DIK_DOWN))
				simon->SetState(SIMON_STATE_SIT);
			else
				simon->SetState(SIMON_STATE_UP);
		}
		break;

	}
}

void CSampleKeyHander::KeyState(BYTE* states)
{
	if (game->IsKeyDown(DIK_Z) && game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_STATE_SIT_ATTACK);
	}
	else if (game->IsKeyDown(DIK_Z) && game->IsKeyDown(DIK_UP))
	{
		simon->SetState(SIMON_STATE_ATTACK_DAGGER);

	}
	else if(game->IsKeyDown(DIK_UP) && game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_STATE_SIT);
	}
	else  if (game->IsKeyDown(DIK_Z))
	{
		if (simon->GetState() == SIMON_STATE_SIT || simon->GetState() == SIMON_STATE_SIT_ATTACK)
			simon->SetState(SIMON_STATE_UP);
		else if (simon->GetState() == SIMON_STATE_IDLE || simon->GetState() == SIMON_STATE_WALKING_LEFT || simon->GetState() == SIMON_STATE_WALKING_RIGHT)
			simon->SetState(SIMON_STATE_STAND_ATTACK);
	}
	else if (game->IsKeyDown(DIK_X))
	{
		simon->SetState(SIMON_STATE_JUMP);
	}
	else if (game->IsKeyDown(DIK_DOWN) && game->IsKeyDown(DIK_Z))
	{
		simon->SetState(SIMON_STATE_SIT_ATTACK);


	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_STATE_GO_DOWN);

	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		if(!simon->IsAttacking())
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (!simon->IsAttacking())
			simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_X))
	{
		//simon->SetState(SIMON_STATE_ATTACK_DAGGER);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		simon->SetState(SIMON_STATE_GO_UP);
	}
	else if(!game->IsKeyDown(DIK_DOWN)&& !game->IsKeyDown(DIK_Z)){

		if (simon->IsOnStair()) {
			if ((simon->GetStairTrend() == 0 && simon->GetNx() == 1) || (simon->GetStairTrend() == 1 && simon->GetNx() == -1))
				simon->SetState(SIMON_STATE_IDLE_UP);
			else
				simon->SetState(SIMON_STATE_IDLE_DOWN);
		}
		else if(simon->GetState() == SIMON_STATE_SIT || simon->GetState() == SIMON_STATE_SIT_ATTACK)
			simon->SetState(SIMON_STATE_UP);
		else
			simon->SetState(SIMON_STATE_IDLE);
	}
		
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and simon object
*/
void LoadResources()
{

	scene->LoadResoure();
	simon = CSimon::GetInstance();

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{	
	scene->Update(dt);
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		scene->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	scene = CScene::GetInstance();


	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();
	Run();

	return 0;
}