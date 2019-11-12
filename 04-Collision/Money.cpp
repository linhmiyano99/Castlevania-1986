#include "Money.h"


void CItemMoney::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEMMONEY_WIDTH;
		top = y;
		bottom = y + ITEMMONEY_HEIGHT;
	}
}