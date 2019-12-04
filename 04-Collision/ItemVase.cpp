#include "ItemVase.h"


void CItemVase::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + 27;
		top = y;
		bottom = y + 35;
	}
}