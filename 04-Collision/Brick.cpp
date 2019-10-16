#include "Brick.h"

void CBrick::Render()
{

	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BRICK_WIDTH;
	bottom = y + BRICK_WIDTH;
}

//void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	CGameObject::Update(dt, coObjects);
//
//	//
//	// TO-DO: make sure Goomba can interact with the world and to each of them too!
//	// 
//
//	x += dx;
//	y += dy;
//
//	if (vx < 0 && x < 0) {
//		x = 0; vx = -vx;
//	}
//
//	if (vx > 0 && x > 290) {
//		x = 290; vx = -vx;
//	}
//}



//void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	CGameObject::Update(dt, coObjects);
//
//	//
//	// TO-DO: make sure Goomba can interact with the world and to each of them too!
//	// 
//
//	x += dx;
//	y += dy;
//
//	if (vx < 0 && x < 0) {
//		x = 0; vx = -vx;
//	}
//
//	if (vx > 0 && x > 290) {
//		x = 290; vx = -vx;
//	}
//}
//
