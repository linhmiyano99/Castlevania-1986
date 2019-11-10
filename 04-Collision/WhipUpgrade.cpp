#include "WhipUpgrade.h"


//
//void CWhipUpgrade::Render()
//{
//	if (state == WHIPUPGRADE_STATE_EXSIST)
//	{
//		animations[0]->Render(x, y);
//	}
//	//RenderBoundingBox();
//}
//
//void CWhipUpgrade::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	if (state == WHIPUPGRADE_STATE_EXSIST)
//	{
//		left = x;
//		right = x + WHIPUPGRADE_WIDTH;
//		top = y;
//		bottom = y + WHIPUPGRADE_HEIGHT;
//	}
//}


void CWhipUpgrade::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + 32;
		top = y;
		bottom = y + 32;
	}
}