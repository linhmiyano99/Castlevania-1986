#ifndef __SMALLBALL_H__

#define __SMALLBALL_H__


#include "GameObject.h"
#include "Textures.h"

#define WEAPON_HEIGHT 64
#define WEAPON_WIDTH 160

#define WEAPON_NOT_EXSIST 0
#define WEAPON_EXSIST 1 

#define SMALL_BALL_SPEED 0.8f


class CSmallBall : public CWeapon
{
public:
	CSmallBall(float _x, float _y, int trend)
	{
		animations.clear();
		AddAnimation(800);
		x = _x;
		y = _y;
		vx = trend * SMALL_BALL_SPEED;

	}
	void Render();
	//void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif // !__WEAPON_H__