#include "ItemClock.h"


void CItemClock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEMCLOCK_WIDTH;
		top = y;
		bottom = y + ITEMCLOCK_HEIGHT;
	}
}