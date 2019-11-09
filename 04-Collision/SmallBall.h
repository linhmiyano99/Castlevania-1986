#ifndef __SMALLBALL_H__

#define __SMALLBALL_H__


#include "GameObject.h"
#include "Textures.h"

#define SMALLBALL_HEIGHT 12
#define SMALLBALL_WIDTH 12

#define SMALLBALL_NOT_EXSIST 0
#define SMALLBALL_EXSIST 1 

#define SMALLBALL_SPEED 0.3f


class CSmallBall : public CGameObject
{
public:
	CSmallBall(float _x, float _y, int trend):CGameObject(_x,_y)
	{
		animations.clear();
		vx = trend * SMALLBALL_SPEED;
		nx = trend;
		AddAnimation(1100);
		state = SMALLBALL_EXSIST;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif // !__SMALLBALL_H__