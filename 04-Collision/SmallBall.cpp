#include "Torch.h"
#include "Game.h"
#include "SmallBall.h"

void CSmallBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (SMALLBALL_EXSIST)
	{
		left = x;
		top = y;
		right = x + 10;
		bottom = y + 10;
	}
}
void CSmallBall::Render()
{
	if (SMALLBALL_EXSIST)
	{
		animations[0]->Render(x,y,nx, 255);
	}
}