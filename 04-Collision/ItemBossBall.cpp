#include "ItemBossBall.h"


void CItemBossBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEMBOSSBALL_WIDTH;
		top = y;
		bottom = y + ITEMBOSSBALL_HEIGHT;
	}
}