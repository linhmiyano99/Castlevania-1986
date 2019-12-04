#include "ItemAxe.h"


void CItemAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEM_AXE_WATTER_WIDTH;
		top = y;
		bottom = y + ITEM_AXE_WATTER_HEIGHT;
	}
}