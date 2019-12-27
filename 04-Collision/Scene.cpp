#include "Game.h"
#include "Scene.h"
#include "Enemy.h"


CScene* CScene::__instance = NULL;
static bool isKillAllEnemy = false;

CScene* CScene::GetInstance()
{
	if (__instance == NULL) __instance = new CScene();
	return __instance;
}
CScene::CScene(int id)
{
	this->id = id;
	map = CMap::GetInstance();
	game = CGame::GetInstance();
	board = CBoard::GetInstance();
	grid = CGrid::GetInstance();
	isAutoTran = false;
	auto_tran = 0;
	_stage = 1;
	isOutSide = true;
	Sound::GetInstance()->Play(eSound::musicStage1);
	CManagementTexture* manage = new CManagementTexture();
	SAFE_DELETE(manage);
}


void CScene::LoadResoure()
{
	if (id == 0) {
		map->SetMap(0);
		grid->LoadObject("texture/objects_1.txt");
		simon = CSimon::GetInstance();
	}
	else
	{
		map->SetMap(1);
		isOutSide = false;
		grid->LoadObject("texture/objects_2.txt");

	}
}
		
void CScene::LoadSimon()
{
	float simon_x, simon_y;
	simon->GetPosition(simon_x, simon_y);
	smallballs.clear();
	if (id == 1)
	{
		simon->SetPosition(SIMON_POSITION_0);
	}
	else if (id == 2)
	{
		if (simon_y < SIMON_Y_UPPER)
			simon->SetPosition(simon_x, simon_y);
		else
			simon->SetUnder();
	}
	else if (id == 3)
	{
		simon->SetUnder();
	}

}

void CScene::Update(DWORD dt)
{
	game->GetCamPos(cam_x, cam_y);
	if (board->IsStop())
	{
		if (simon->IsFall(dt))
			return;
		if (simon->GetEnergy() < SIMON_MAX_ENERGY)
		{
			simon->UpEnergy();
			return;
		}
		else if (board->GetTime() > 0)
		{
			Sound::GetInstance()->Play(eSound::soundGetScoreTimer);
			board->TimeDown();
			return;
		}
		else if (simon->GetHeart() > 0)
		{
			Sound::GetInstance()->Play(eSound::soundGetScoreHeart);
			simon->HeartDown();
			return;
		}
		Sound::GetInstance()->Stop(eSound::music_Boss);
		return;

	}	
	if (start_killAllEnemy > 0)
	{
		if (GetTickCount() - start_killAllEnemy > TIME_KILL_ALL_ENEMY)
		{
			start_killAllEnemy = 0;
			BACKGROUND_COLOR = BACKGROUND_COLOR_DEFAULT;
		}
		else
		{
			if ((GetTickCount() - start_killAllEnemy) % 10 == 0)
			{
				if (BACKGROUND_COLOR == BACKGROUND_COLOR_DEFAULT)
				{
					BACKGROUND_COLOR = BACKGROUND_COLOR_CROSS;
				}
				else
				{
					BACKGROUND_COLOR = BACKGROUND_COLOR_DEFAULT;
				}
			}
		}
	}

	board->Update(dt);
	for each (LPGAMEOBJECT var in smallballs)
	{
		var->Update(dt);
	}

	game->GetCamPos(cam_x, cam_y);

	if (isAutoTran)
	{
		if (simon->IsFall(dt))
			return;
		if (cam_x < auto_tran)
		{
			if (cam_x < auto_tran - SCREEN_WIDTH / 2)
				game->SetCamPos(cam_x + 2.0f, cam_y);// vận tốc chuyển màn 2.0f pixcel / milisecond 
			else
			{
				if (simon->IsAutoGo())
					simon->Update(dt);
				else
					game->SetCamPos(cam_x + 2.0f, cam_y);// vận tốc chuyển màn 2.0f pixcel / milisecond 
			}

		}
		else
		{
			_stage++;
			id = GetStartScene();
			simon->SetStart(GetLeft(), GetSimonStartHeight());
			isAutoTran = false;
			
			simon->SetTrend(1);
			CGate::Stop();
		}
	}
	else
	{
		if (id == 5)
		{
			Sound::GetInstance()->Stop(eSound::musicStage1);
			Sound::GetInstance()->Play(eSound::music_Boss);
		}
		float cx, cy;
		simon->GetPosition(cx, cy);
		game->GetCamPos(cam_x, cam_y);
		grid->GetListObject(objects, cam_x, cam_y);


		if (cy >= CAM_Y_DOWN && id != 3)
		{
			id = 3;
			SetMap(3);
			LoadSimon();
			cy = CAM_Y_DOWN;
		}
		else if (id == 3)
		{
			if (cy < CAM_Y_DOWN)
			{
				if (simon->IsOnStair())
				{
					id = 2;
					SetMap(2);
					LoadSimon();
					cy = 0;
				}
				else
					cy = CAM_Y_DOWN;

			}
			else
				cy = CAM_Y_DOWN;
		}
		else if (id == 4 && cx > POSITION_START_BOSS)
		{
			id = 5;
			CBoss::GetInstance()->SetState(BOSS_STATE_FLY);
		}
		else
		{
			cy = 0;
		}

		
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
		simon->Update(dt, &coObjects);


		if (cx < GetLeft())
			cx = GetLeft();
		if (id != 4)
		{
			if (cx > GetRight() - SCREEN_WIDTH)
				cx = GetRight() - SCREEN_WIDTH;
		}
		if(!(IsOutSide() && cx > GetRight() - SCREEN_WIDTH))
			game->SetCamPos(cx, cy);
		switch (CBoard::GetInstance()->GetWeapon())
		{
		case  eType::DAGGER:
			CDagger::GetInstance()->Update(dt, &coObjects);
			break;
		case eType::ITEMAXE:
			CAxe::GetInstance()->Update(dt, &coObjects);
			break;
		case eType::ITEMHOLLYWATTER:
			CHollyWatter::GetInstance()->Update(dt, &coObjects);
			break;
		case eType::ITEMBOONGMERANG:
			CBoongmerang::GetInstance()->Update(dt, &coObjects);
			break;
		default:
			break;
		}
		coObjects.clear();

	}

}
void CScene::Render() 
{
	map->DrawMap();

	for each (LPGAMEOBJECT var in smallballs)
	{
		var->Render();
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
	simon->Render();

	switch (CBoard::GetInstance()->GetWeapon())
	{
	case  eType::DAGGER:
		CDagger::GetInstance()->Render();
		break;
	case eType::ITEMAXE:
		CAxe::GetInstance()->Render();
		break;
	case eType::ITEMHOLLYWATTER:
		CHollyWatter::GetInstance()->Render();
		break;
	case eType::ITEMBOONGMERANG:
		CBoongmerang::GetInstance()->Render();
		break;
	default:
		break;
	}

	board->Render();
	float s_x, s_y;
	simon->GetPosition(s_x, s_y);
	if (simon->IsOnStair() && (s_y > START_DOWN&& s_y < DONE_DOWN) && simon->GetState() != SIMON_STATE_DIE)
	{
		CSprites::GetInstance()->Get(70001)->Draw(cam_x, cam_y);
	}
}
void CScene::SetMap(int id)
{
	this->id = id;

}
int CScene::GetLeft()
{
	if (isAutoTran)
	{
		return cam_x;
	}
	switch (id)
	{
	case 0:
		return SCENCE_0_LEFT;
	case 1:
		return SCENCE_1_LEFT;
	case 2:
		return SCENCE_2_LEFT;
	case 3:
		return SCENCE_3_LEFT;
	case 4:
		return SCENCE_4_LEFT;
	case 5:
		return SCENCE_5_LEFT;
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
		return SCENCE_0_TOP;
	case 3:
		return SCENCE_1_TOP;
	default:
		return 0;
	}
}
int CScene::GetRight()
{
	if (isAutoTran)
	{
		return cam_x + SCREEN_WIDTH;
	}
	switch (id)
	{
	case 0:
		return SCENCE_0_RIGHT;
	case 1:
		return SCENCE_1_RIGHT;
	case 2:
	case 3:
		return SCENCE_3_RIGHT;
	case 4:
	case 5:
		return SCENCE_5_RIGHT;
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
		return SCENCE_0_BOTTOM;
	case 3:
		return SCENCE_1_BOTTOM;
	default:
		return SCENCE_0_BOTTOM;
	}
}

void CScene::TranScene()
{
	auto_tran = GetRight();
	isAutoTran = true;

}
void CScene::AddSmallBall(LPGAMEOBJECT smallball)
{
	smallballs.push_back(smallball);
}

void CScene::UpStage()
{ 
	_stage++;
}
void CScene::ResetScene()
{
	if (id == 3 || id == 2)
		id = 2;
	else if (id == 5 || id == 4)
	{
		id = 4;
		CBoss::GetInstance()->ResetBoss();
		Sound::GetInstance()->Play(eSound::musicStage1);
		Sound::GetInstance()->Stop(eSound::music_Boss);
	}
}
void CScene::TestStage(int stage)
{
	_stage = stage;
	switch (_stage)
	{
	case 1:
		id = 1;
		break;
	case 2:
		id = 2;
		CBat::Start();
		break;
	case 3:
		id = 4;
		break;
	default:
		id = 1;
		break;
	}
	LoadResoure();
	simon->SetPosition(GetLeft(), GetSimonStartHeight());
	simon->SetStart(GetLeft(), GetSimonStartHeight());
	CGate::Stop();
}
bool CScene::IsKillAllEnemy()
{
	if (start_killAllEnemy > 0)
		return true;
	return false;
}
float CScene::GetSimonStartHeight()
{
	switch (_stage)
	{
		case 1:
			return SIMON_START_LOW;
		case 2:
		case 3:
			return SIMON_START_HIGH;
	default:
		return SIMON_START_HIGH;
		break;
	}
}
int CScene::GetStartScene()
{
	switch (_stage)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 4;
	default:
		return 0;
		break;
	}
}
float CScene::GetMapRight()
{
	if (id == 0)
		return SCENCE_0_RIGHT;
	else
		return SCENCE_5_RIGHT;
}
