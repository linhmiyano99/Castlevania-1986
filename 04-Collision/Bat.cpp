#include"Bat.h"
#include"Scene.h"

CBat::CBat(float _x , float _y , int id ) :CEnemy(_x, _y, id, eType::BAT)
{
	animations.clear();
	AddAnimation(1003);
	AddAnimation(800);
	vx = -0.1f;
	vy = 0.1f;
}
void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CScene* scene = CScene::GetInstance();

	if (dt_die == 0)
	{
		if (state == TORCH_STATE_NOT_EXSIST) {
			dt_die = GetTickCount();
			if(item)
				item->SetPosition(x, y);
		}
		else
		{
			if (scene->GetScene() == 2)
			{
				CGameObject::Update(dt);
				x += dx;
				y += dy;
			}
		}
	}
	else
	{
		if (item != NULL) {//co item
			if (GetTickCount() - dt_die > 150) // cho 150 mili second
			{
				item->Update(dt, coObjects);
				item->GetPosition(x, y);
				state = TORCH_STATE_ITEM;
			}
		}
	}
	if (x <= scene->GetLeft() || x >= scene->GetRight())
		vx = -vx;
	if (y <= 40 || y >= SCREEN_HEIGHT)
		vy = -vy;
}
void CBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

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
	if (CScene::GetInstance()->IsTranScene())
		return;
	if (state == TORCH_STATE_EXSIST)
	{
		animations[0]->Render(x, y);
	}
	else if (state == TORCH_STATE_ITEM)
	{
		if (item != NULL)
			item->Render();

	}
	else
	{
		if (GetTickCount() - dt_die < 150)
		{
			animations[1]->Render(x, y);
		}
	}

	//RenderBoundingBox();
}