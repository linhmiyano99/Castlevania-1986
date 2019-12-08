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
			
		switch (_weapon)
		{
		case eType::DAGGER:
			sprites->Get(13001)->Draw(cx + 310, cy + 40);;
			break;
		case eType::ITEMAXE:
			sprites->Get(13010)->Draw(cx + 310, cy + 30);
			break;
		case eType::ITEMHOLLYWATTER:
			sprites->Get(13015)->Draw(cx + 310, cy + 27);
			break;
		case eType::ITEMBOONGMERANG:
			sprites->Get(13020)->Draw(cx + 310, cy + 27);
			break;
		default:
			break;
		}
		if (_numberOfWeapon != 0)
		{
			if (_numberOfWeapon == 2)
			{
				sprites->Get(13014)->Draw(cx + 440, cy + 40);
			}
			else if (_numberOfWeapon == 3)
			{
				sprites->Get(13017)->Draw(cx + 440, cy + 40);
			}
		}

	}
	game = NULL;
	sprites = NULL;
	simon = NULL;
	boss = NULL;
	scene = NULL;
}
void CBoard::ChangeWeapon()
{
	switch (_weapon)
	{
	case 0:
		SetWeapon(eType::DAGGER);
		break;
	case eType::DAGGER:
		SetWeapon(eType::ITEMAXE);
		break;
	case eType::ITEMAXE:
		SetWeapon(eType::ITEMHOLLYWATTER);
		break;
	case eType::ITEMHOLLYWATTER:
		SetWeapon(eType::ITEMBOONGMERANG);
		break;
	case eType::ITEMBOONGMERANG:
		SetWeapon(eType::DAGGER);
		break;
	default:
		break;
	}
}
