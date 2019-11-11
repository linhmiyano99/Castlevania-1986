#include "VampireKiller.h"
#include "Torch.h"
#include "Enemy.h"
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
	animation = animations[0];
}

void CVampireKiller::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> listObj;
	// Collision logic with items
	
	CollisionWithObject(dt, *coObjects);


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
	animation->Render(x, y, nx, 255);
	y += 15;
	if (animation->GetCurrentFrame() < 2)
		return;
	RenderBoundingBox();
}

void CVampireKiller::setDefaultLevel()
{
	_level = 1;
}void CVampireKiller::setUpLevel()
{
	if (_level < 3)
		_level++;
	animation = animations[_level - 1];
}
void CVampireKiller::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
	if (_level == 1 || _level == 2)
	{
		left = x;
		right = x + 120;
		top = y;
		bottom = y + 20;
	}
	else
	{
		left = x;
		right = x + 145;
		top = y;
		bottom = y + 20;
	
	}
}


void CVampireKiller::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (animation->GetCurrentFrame() < 2)
		return;


	RECT rect, rect1;
	float l, t, r, b;
	float l1, t1, r1, b1;

	GetBoundingBox(l, t, r, b);
	rect.left = (int)l;
	rect.top = (int)t;
	rect.right = (int)r;
	rect.bottom = (int)b;

	for (int i = 0; i < listObj.size(); i++)
	{
		if (dynamic_cast<CTorch*>(listObj.at(i)))
		{
			CTorch* torch = dynamic_cast<CTorch*>(listObj.at(i));
			if (torch->GetState() == TORCH_STATE_EXSIST)
			{
				if(torch->GetType() == eType::BRICK_1 || torch->GetType() == eType::BRICK_2)
					continue;
				torch->GetBoundingBox(l1, t1, r1, b1);
				rect1.left = (int)l1;
				rect1.top = (int)t1;
				rect1.right = (int)r1;
				rect1.bottom = (int)b1;
				if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
				{
					torch->SetState(TORCH_STATE_NOT_EXSIST);

				}
			}
		}
	}
}
