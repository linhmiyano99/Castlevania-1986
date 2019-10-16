#include "VampireKiller.h"
#include "Torch.h"
#include "Game.h"
CVampireKiller* CVampireKiller::__instance = NULL;

CVampireKiller* CVampireKiller::GetInstance()
{
	if (__instance == NULL) __instance = new CVampireKiller();
	return __instance;
}

CVampireKiller::CVampireKiller() :CWeapon()
{
	_level = 1;
	AddAnimation(600);
	AddAnimation(601);
	AddAnimation(602);
}

void CVampireKiller::SetPosition(float simon_x, float simon_y)
{
	if (_level == 1 || _level == 2)
	{
		if (nx < 0)
		{
			x = simon_x - 50;
		}
		else {
			x = simon_x - 10;
		}
	}
	else
	{
		if (nx < 0)
		{
			x = simon_x - 80;
		}
		else {
			x = simon_x - 10;
		}
	}
	y = simon_y;

}


void CVampireKiller::Render()
{
	
	switch (_level)
	{
	case 1:
		animations[0]->Render(x, y, nx);
		break;
	case 2:
		animations[1]->Render(x, y, nx);
		break;
	case 3:
		animations[2]->Render(x, y, nx);
		break;
	default:
		break;
	}

	//RenderBoundingBox();
}

void CVampireKiller::setDefaultLevel()
{
	_level = 1;
}void CVampireKiller::setUpLevel()
{
	if (_level < 3)
		_level++;
}
void CVampireKiller::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
	if (_level == 1 || _level == 2)
	{
		left = x;
		right = x + 120;
		top = y;
		bottom = y + 30;
	}
	else
	{
		left = x;
		right = x + 145;
		top = y;
		bottom = y + 30;
	
	}
}


void CVampireKiller::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	RECT rect, rect1;
	float l, t, r, b;
	float l1, t1, r1, b1;

	GetBoundingBox(l, t, r, b);
	rect.left = (int)l;
	rect.top = (int)t;
	rect.right = (int)r;
	rect.bottom = (int)b;

	for (int i = 0; i < listObj.size(); i++)
		if (dynamic_cast<CTorch*>(listObj.at(i)))
		{
			if (listObj.at(i)->GetState() == TORCH_STATE_EXSIST)
			{
				listObj.at(i)->GetBoundingBox(l1, t1, r1, b1);
				rect1.left = (int)l1;
				rect1.top = (int)t1;
				rect1.right = (int)r1;
				rect1.bottom = (int)b1;
				if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
				{
					listObj.at(i)->SetState(TORCH_STATE_NOT_EXSIST);

				}
			}
		}
}
