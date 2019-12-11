
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

}


void CScene::LoadResoure()
{
	CManagementTexture* manage = new CManagementTexture();
	SAFE_DELETE(manage);

	objects.clear();

	dagger = CDagger::GetInstance();
	objects.push_back(dagger);
	axe = CAxe::GetInstance();
	objects.push_back(axe);
	holly = CHollyWatter::GetInstance();
	objects.push_back(holly);
	boongmerang = CBoongmerang::GetInstance();
	objects.push_back(boongmerang);
	sound = Sound::GetInstance();
	sound->Play(eSound::musicStage1);
	if (id == 0) {
		map->SetMap(0);
		
		grid->LoadObject("texture/objects_1.txt");
		simon = CSimon::GetInstance();
		//simon->SetPosition(SIMON_POSITION_0);
		objects.push_back(simon);
	}
	else
	{
		map->SetMap(1);
		
		grid->LoadObject("texture/objects_2.txt");
		dagger = CDagger::GetInstance();
		objects.push_back(dagger);
		simon = CSimon::GetInstance();
		objects.push_back(simon);
		boss = CBoss::GetInstance();
		boss->SetPosition(BOSS_POSITION);
		objects.push_back(boss);

	}
}
		
void CScene::LoadSimon()
{
	float simon_x, simon_y;
	simon = CSimon::GetInstance();
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
	if (board->IsStop())
	{

		sound->Stop(eSound::music_Boss);
		if (simon->GetEnergy() < SIMON_MAX_ENERGY)
		{
			simon->UpEnergy();
			return;
		}
		else if (board->GetTime() > 0)
		{
			sound->Play(eSound::soundGetScoreTimer);
			board->TimeDown();
			return;
		}
		else if (simon->GetHeart() > 0)
		{
			sound->Play(eSound::soundGetScoreHeart);
			simon->HeartDown();
			return;
		}
	}	
	if (start_killAllEnemy > 0)
	{
		if (GetTickCount() - start_killAllEnemy > TIME_KILL_ALL_ENEMY)
		{
			start_killAllEnemy = 0;
		}
	}

	board->Update(dt);
	for each (LPGAMEOBJECT var in smallballs)
	{
		var->Update(dt);
	}
	float c_x, c_y;

	game->GetCamPos(c_x, c_y);

	if (isAutoTran)
	{

		if (c_x < auto_tran)
		{
			if (c_x < auto_tran - SCREEN_WIDTH / 2)
				game->SetCamPos(c_x + 2.0f, c_y);
			else
			{
				if (simon->IsAutoGo())
					simon->Update(dt);
				else
					game->SetCamPos(c_x + 2.0f, c_y);
			}

		}
		else
		{
			if (id == 1)
			{
				id = 2;
				simon->SetStart(SCENCE_2_LEFT, SIMON_START_HIGH);
				CBat::Start();
			}
			else
			{
				id = 4;
				CGate::Stop();
				simon->SetStart(SCENCE_4_LEFT, SIMON_START_HIGH);
				CBat::Stop();
			}
			isAutoTran = false;
			_stage++;
			simon->SetTrend(1);
			CGate::Stop();
		}
	}
	else
	{
		if (id == 5)
		{
			sound->Stop(eSound::musicStage1);
			sound->Play(eSound::music_Boss);
		}
		float cx, cy, cam_x, cam_y;
		simon->GetPosition(cx, cy);
		CGame::GetInstance()->GetCamPos(cam_x, cam_y);
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
			boss->SetState(BOSS_STATE_FLY);
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



		if (cx < GetLeft())
			cx = GetLeft();
		if (id != 4)
		{
			if (cx > GetRight() - SCREEN_WIDTH)
				cx = GetRight() - SCREEN_WIDTH;
		}


		game->SetCamPos(cx, cy);
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
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	CSprites* sprites = CSprites::GetInstance();
	board->Render();
	float s_x, s_y;
	simon->GetPosition(s_x, s_y);
	if (simon->IsOnStair() && (s_y > START_DOWN&& s_y < DONE_DOWN) && simon->GetState() != SIMON_STATE_DIE)
	{
		CSprites* sprites = CSprites::GetInstance();
		sprites->Get(70001)->Draw(cx, cy);
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
		float c_x, c_y;
		game->GetCamPos(c_x, c_y);
		return c_x;
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
		float c_x, c_y;
		game->GetCamPos(c_x, c_y);
		return c_x + SCREEN_WIDTH;
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
		CBoss* boss = CBoss::GetInstance();
		boss->ResetBoss();
		boss = NULL;
		sound->Play(eSound::musicStage1);
		sound->Stop(eSound::music_Boss);
	}
}
void CScene::TestStage(int stage)
{
	_stage = stage;
	if (stage == 1)
	{
		id = 1;
		LoadResoure();
		simon->SetPosition(SCENCE_1_LEFT , SIMON_START_LOW);
		simon->SetStart(SCENCE_1_LEFT, SIMON_START_LOW);
	}
	else if (stage == 2)
	{
		id = 2;
		LoadResoure();
		simon->SetPosition(SCENCE_2_LEFT , SIMON_START_HIGH);
		simon->SetStart(SCENCE_2_LEFT, SIMON_START_HIGH);
		CBat::Start();
	}
	else if (stage == 3)
	{
		id = 4;
		LoadResoure();
		simon->SetPosition(SCENCE_4_LEFT , SIMON_START_HIGH);
		simon->SetStart(SCENCE_4_LEFT, SIMON_START_HIGH);
	}
	CGate::Stop();
}
bool CScene::IsKillAllEnemy()
{
	if (start_killAllEnemy > 0)
		return true;
	return false;
}