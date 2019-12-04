#include "ItemCross.h"


void CItemCross::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEMCROSS_WIDTH;
		top = y;
		bottom = y + ITEMCROSS_HEIGHT;
	}
}