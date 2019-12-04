#include "ItemBoongmerang.h"


void CItemBoongmerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEM_BOONGMERANG_WATTER_WIDTH;
		top = y;
		bottom = y + ITEM_BOONGMERANG_WATTER_HEIGHT;
	}
}