#include "Board.h"
#include "Boss.h"
#include "Scene.h"

CBoard* CBoard::__instance = NULL;

CBoard* CBoard::GetInstance()
{
	if (__instance == NULL) __instance = new CBoard();
	return __instance;
}

void CBoard::Update(DWORD dt)
{
	if (isStop)
	{
		return;
	}
	if (GetTickCount() - _count >= 1000)
	{
		_time--;
		_count = GetTickCount();
	}
}
void CBoard::Render()
{

	CGame* game = CGame::GetInstance();
	float cx, cy;
	game->GetCamPos(cx, cy);
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(50000)->Draw(cx, cy);
	CSimon* simon = CSimon::GetInstance();
	CBoss* boss = CBoss::GetInstance();
	CScene* scene = CScene::GetInstance();

	code->DrawNumber(6, cx + 110, cy + 12, simon->GetScore());
	code->DrawNumber(4, cx + 295, cy + 12, _time);
	code->DrawNumber(2, cx + 465, cy + 12, scene->GetStage());
	code->DrawNumber(2, cx + 400, cy + 32, simon->GetHeart());
	code->DrawNumber(2, cx + 400, cy + 52, simon->GetLives());
	code->DrawEnergyBar(cx + 110, cy + 30, 0, simon->GetEnergy());
	code->DrawEnergyBar(cx + 110, cy + 50, 1, boss->GetEnergy());
	if (_weapon != 0)
	{
		if (_weapon == eType::DAGGER)
			sprites->Get(13001)->Draw(cx + 310, cy + 40);
	}
}