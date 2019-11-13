#include "Torch.h"

CTorch::CTorch(float _x, float _y, int id, int type) : CGameObject(_x, _y, type)
{
	dt_die = 0;
	state = TORCH_STATE_EXSIST;
	
	switch (type)
	{
	case eType::TORCH:
		AddAnimation(501);
		break;
	case eType::CANDLE:
		AddAnimation(502);
		break;
	case eType::BRICK_1:
		AddAnimation(499);
		break;
	case eType::BRICK_2:
		AddAnimation(500);
		break;
	case eType::BRICK_3:
		AddAnimation(498);
		break;
	}
	AddAnimation(800);

	switch (id)
	{
	case ID_WHIPUPGRADE:
		item = new CWhipUpgrade(_x,_y);
		break;
	case ID_DAGGER:
		item = new CItemDagger(_x,_y);
		break;
	case ID_HEART:
		item = new CItemHeart(_x, _y);
		break;
	case ID_SMALLHEART:
		item = new CSmallHeart(_x, _y);
		break;
	case ID_CHICKEN:
		item = new CItemChicken(_x, _y);
		break;
	case ID_MONEY_1:
		item = new CItemMoney(_x, _y, eType::MONEY_1);
		break;
	case ID_MONEY_2:
		item = new CItemMoney(_x, _y, eType::MONEY_2);
		break;
	case ID_MONEY_3:
		item = new CItemMoney(_x, _y, eType::MONEY_3);
		break;
	case ID_MONEY_4:
		item = new CItemMoney(_x, _y, eType::MONEY_4);
		break;
	default:
		item = NULL;
		break;
	}

	x = _x;
	y = _y;
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
			if (item)
				item->SetPosition(x, y);
			else
				state = ITEM_STATE_NOT_EXSIST;
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

}

void CTorch::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		if (_type == eType::CANDLE)
		{
			right = x + CANDLE_WIDTH;
			bottom = y + CANDLE_HEIGHT;
		}
		else
		{
			right = x + TORCH_WIDTH;
			bottom = y + TORCH_HEIGHT;
		}
	}
	else if (state == TORCH_STATE_ITEM)
	{
		//item->SetPosition(x,y);
		item->GetBoundingBox(left, top, right, bottom);
	}
}
