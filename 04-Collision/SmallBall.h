#ifndef __SMALLBALL_H__

#define __SMALLBALL_H__


#include "GameObject.h"
#include "Textures.h"

#define SMALLBALL_HEIGHT 64
#define SMALLBALL_WIDTH 160

#define SMALLBALL_NOT_EXSIST 0
#define SMALLBALL_EXSIST 1 

#define SMALLBALL_SPEED 0.03f


class CSmallBall : public CGameObject
{
public:
	CSmallBall(float _x, float _y, int trend):CGameObject(_x,_y)
	{
		animations.clear();
		vx = trend * SMALLBALL_SPEED;
		nx = trend;
		AddAnimation(800);
	}
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif // !__SMALLBALL_H__