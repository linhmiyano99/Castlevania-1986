#include "Torch.h"

CTorch::CTorch(int id, int level) : CGameObject()
{
	dt_die = 0;
	state = TORCH_STATE_EXSIST;
	if (level == 0)
	{
		AddAnimation(501);
	}
	else
	{
		AddAnimation(502);
	}
	AddAnimation(800);
	switch (id)
	{
	case ID_WHIPUPGRADE:
		item = new CWhipUpgrade();
		break;
	case ID_DAGGER:
		item = new CItemDagger();
		break;
	case ID_HEART:
		item = new CItemHeart();
		break;
	case 0:
		break;
	default:
		break;
	}
}

void CTorch::Render()
{
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
void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (dt_die == 0)
	{
		if (state == TORCH_STATE_NOT_EXSIST) {
			dt_die = GetTickCount();
		}
	}
	else
	{
		if (item != NULL) {//co item
			if (GetTickCount() - dt_die > 150) // cho 150 mili second
			{

				item->Update(dt, coObjects);
				state = TORCH_STATE_ITEM;
			}
		}
	}

}

void CTorch::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		right = x + TORCH_WIDTH;
		top = y;
		bottom = y + TORCH_HEIGHT;
	}
	else if (state == TORCH_STATE_ITEM)
	{
		item->GetPosition(x,y);
		item->GetBoundingBox(left, top, right, bottom);
	}
}
