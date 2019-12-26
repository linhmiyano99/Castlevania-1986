#include"Bat.h"
#include"Scene.h"


bool CBat::isStart = false;

CBat::CBat(float _x , float _y , int id ) :CEnemy(_x, _y, id, eType::BAT)
{
	animations.clear();
	AddAnimation(1003);
	AddAnimation(800);
	vx = -0.07f;
	vy = 0.04f;
	nx = -1;
	ny = 1;
	CSimon::GetInstance()->GetPosition(bottomLimit, topLimit);
	bottomLimit = topLimit + 2 * SIMON_HEIGHT_STAND;
	topLimit -= SIMON_HEIGHT_STAND;
}
void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!CBat::IsStart())
		return;
	float c_x, c_y;
	CGame::GetInstance()->GetCamPos(c_x, c_y);
	if (CScene::GetInstance()->IsKillAllEnemy() && x > c_x && x < c_x + SCREEN_WIDTH)
		Dead();

	if (dt_die == 0)
	{
		if (state == TORCH_STATE_NOT_EXSIST) {
			dt_die = GetTickCount();
			if(item)
				item->SetPosition(x, y);
		}
		else
		{
			
			CSimon::GetInstance()->GetPosition(bottomLimit, topLimit);
			bottomLimit = topLimit + 2 * SIMON_HEIGHT_STAND;
			topLimit -= SIMON_HEIGHT_STAND;
			if ((x <= c_x && nx < 0) || (x >= c_x + SCREEN_WIDTH && nx > 0))
			{
				vx = -vx;
				nx = -nx;
			}
			if ((y <= topLimit && ny < 0) || (y >= bottomLimit && ny > 0))
			{
				vy = -vy;
				ny = -ny;
			}
			CGameObject::Update(dt);
			x += dx;
			y += dy;
			
		}
	}
	else
	{
		if (item != NULL) {//co item
			if (GetTickCount() - dt_die > TIME_ENEMY_DIE) // cho 150 mili second
			{
				item->Update(dt, coObjects);
				item->GetPosition(x, y);
				state = TORCH_STATE_ITEM;
			}
		}
	}

}
void CBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (!CBat::IsStart())
		return;
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + BAT_BBOX_WIDTH;
		bottom = y + BAT_BBOX_HEIGHT;
	}
	else if (state == TORCH_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
}
void CBat::Render()
{
	if (!CBat::IsStart())
		return;
	if (CScene::GetInstance()->IsTranScene())
		return;
	if (state == TORCH_STATE_EXSIST)
	{
		animations[0]->Render(x, y, nx, 255);
	}
	else if (state == TORCH_STATE_ITEM)
	{
		if (item != NULL)
			item->Render();

	}
	else
	{
		if (GetTickCount() - dt_die < TIME_ENEMY_DIE)
		{
			animations[1]->Render(x, y);
		}
	}

	//RenderBoundingBox();
}