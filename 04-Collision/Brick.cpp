#include "Brick.h"
CBrick::CBrick(float _x, float _y, int id , int type, float width, float height) :CTorch(_x, _y, id, type)
{

	if (type == eType::BRICK_4 || type == eType::BRICK_3 || type == eType::BRICK_5)
	{
		for (int i = 0; i < 4; i++)
		{
			CBrickBreak* brick = new CBrickBreak(_x, _y, i);
			list.push_back(brick);
		}
	}
	w = width;
	h = height;
}
void CBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + w;
		bottom = y + h;
		if (_type == eType::BRICK_5)
		{
			right = x + 28;
		}

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
			if (GetTickCount() - dt_die > 400) // cho 300 mili second
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
		else
		{
			if (GetTickCount() - dt_die < 400) // cho 300 mili second
			{
				if (list.size() > 0)
				{
					for each (CBrickBreak * var in list)
					{
						var->Update(dt);
					}
				}
			}
			else
				state = ITEM_STATE_NOT_EXSIST;
		}
	}

}

void CBrick::Render()
{
	if (_type == eType::BRICK_2)
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

