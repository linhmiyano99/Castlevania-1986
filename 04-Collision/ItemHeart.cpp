#include "ItemHeart.h"


void CItemHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEMHEART_WIDTH;
		top = y;
		bottom = y + ITEMHEART_HEIGHT;
	}
}