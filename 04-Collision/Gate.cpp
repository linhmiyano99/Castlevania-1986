#include"Gate.h"

void CGate::Render()
{
	if (animations[0]->GetCurrentFrame() != animations[0]->GetLastFrame())
	{
		if (state == GATE_STATE_CLOSE)
		{
			animations[0]->ResetFrame();
			animations[0]->Render(x, y);
		}
		else
		{
			animations[0]->Render(x, y);
		}
	}
}

void CGate::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 32;
	bottom = y + 96;
}
