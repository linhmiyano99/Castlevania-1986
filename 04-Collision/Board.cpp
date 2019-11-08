#include "Board.h"

CBoard* CBoard::__instance = NULL;

CBoard* CBoard::GetInstance()
{
	if (__instance == NULL) __instance = new CBoard();
	return __instance;
}

void CBoard::Update(DWORD dt)
{

}
void CBoard::Render()
{

	CGame* game = CGame::GetInstance();
	float cx, cy;
	game->GetCamPos(cx, cy);
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(50000)->Draw(cx, cy);

	code->DrawNumber(6, cx + 110, cy + 12, 500);
	code->DrawNumber(4, cx + 295, cy + 12, 300);
	code->DrawNumber(2, cx + 465, cy + 12, 1);
	code->DrawNumber(2, cx + 400, cy + 32, 1);
	code->DrawNumber(2, cx + 400, cy + 52, 1);
	code->DrawEnergyBar(cx + 110, cy + 30, 0, 5);
	code->DrawEnergyBar(cx + 110, cy + 50, 1, 5);

}