#include"Gate.h"

bool CGate::isCanOpen = true;
CGate::CGate(float _x, float _y) :CGameObject(_x, _y)
{
	state = 0;
	AddAnimation(1200);
	AddAnimation(1201);
}
void CGate::Render()
{

	if (state == GATE_STATE_CLOSE)
	{
		animations[0]->Render(x, y);
	}
	else
	{
		if(animations[1]->GetCurrentFrame() != animations[1]->GetLastFrame())
			animations[1]->Render(x, y);
	
	}

}

void CGate::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 32;
	bottom = y + 96;
}
