#include "Brick.h"


CBrick::CBrick(float _x, float _y, int id, int type) :CTorch(_x, _y, id, type)
{
}

void CBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + BRICK_WIDTH;
		bottom = y + BRICK_WIDTH;

	}
	else if (state == ITEM_STATE_EXSIST)
	{
		item->GetPosition(x, y);
		item->GetBoundingBox(left, top, right, bottom);
	}
}


