#include "Torch.h"
#include "Game.h"
#include "SmallBall.h"

void CSmallBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 10;
	bottom = y + 10;
}
