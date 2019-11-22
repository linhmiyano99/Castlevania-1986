#include "Brick.h"

void CBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + BRICK_WIDTH;
		bottom = y + BRICK_WIDTH;

	}
	else 
	{
		if (item != NULL)
		{
			item->SetPosition(x, y);
			item->GetBoundingBox(left, top, right, bottom);
		}
	}
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
			if (GetTickCount() - dt_die > 600) // cho 300 mili second
			{
				item->Update(dt, coObjects);
				item->GetPosition(x, y);
				state = TORCH_STATE_ITEM;
			}
			else
			{
				if (list.size() > 0)
				{
					for each (CBrickBreak * var in list)
					{
						var->Update(dt);
					}
				}
			}
		}
	}

}

void CBrick::Render()
{
	if (_type == eType::BRICK_2)
		return;
	if (_type == eType::BRICK_1)
	{
		animations[0]->Render(x, y);
		return;
	}
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
		if (list.size() > 0)
		{
			if (GetTickCount() - dt_die <= 600)
			{
				for each (CBrickBreak *var in list)
				{
					var->Render();
				}
			}
		}
	}
	////RenderBoundingBox();
}

