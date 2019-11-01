#ifndef __SMALLBALL_H__

#define __SMALLBALL_H__


#include "GameObject.h"
#include "Textures.h"

#define WEAPON_HEIGHT 64
#define WEAPON_WIDTH 160

#define WEAPON_NOT_EXSIST 0
#define WEAPON_EXSIST 1 


class CSmallBall : public CWeapon
{
public:
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif // !__WEAPON_H__