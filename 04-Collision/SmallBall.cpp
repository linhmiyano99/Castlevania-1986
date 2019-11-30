#include "Torch.h"
#include "Game.h"
#include "SmallBall.h"
#include "Scene.h"

void CSmallBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state = SMALLBALL_EXSIST)
	{
		left = x;
		top = y;
		right = x + 10;
		bottom = y + 10;
	}
}
void CSmallBall::Render()
{
	if (state == SMALLBALL_EXSIST)
	{
		animations[0]->Render(x,y,nx, 255);
	}
}
void CSmallBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x <= CScene::GetInstance()->GetLeft() || x >= CScene::GetInstance()->GetRight())
	{
		state = SMALLBALL_NOT_EXSIST;
		return;
	}
	if (state == SMALLBALL_EXSIST)
	{
		x += vx * dt;
		y += vy * dt;
		RECT rect, rect1;
		float l, t, r, b;
		float l1, t1, r1, b1;

		GetBoundingBox(l, t, r, b);
		rect.left = (int)l;
		rect.top = (int)t;
		rect.right = (int)r;
		rect.bottom = (int)b;

		CSimon* simon = CSimon::GetInstance();

		//if (simon->GetState() == TORCH_STATE_EXSIST)
		{
			simon->GetBoundingBox(l1, t1, r1, b1);
			rect1.left = (int)l1;
			rect1.top = (int)t1;
			rect1.right = (int)r1;
			rect1.bottom = (int)b1;
			if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
			{
				//simon->Hurt();
				simon->StartHurt(x, y);
				state = SMALLBALL_NOT_EXSIST;
			}
		}


	}
}
