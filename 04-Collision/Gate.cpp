#include"Gate.h"

void CGate::Render()
{
	animations[0]->ResetFrame();
	animations[0]->Render(x, y);
}

void CGate::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 32;
	bottom = y + 96;
}
