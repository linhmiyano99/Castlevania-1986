#include "ItemChicken.h"


void CItemChicken::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + 35;
		top = y;
		bottom = y + 27;
	}
}