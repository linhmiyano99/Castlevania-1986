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


