#include "ItemDagger.h"


void CItemDagger::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + 55;
		top = y;
		bottom = y + 40;
	}
}