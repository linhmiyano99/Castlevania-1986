#ifndef __VAMPIREILLER_H__

#define __VAMPIREILLER_H__


#include "GameObject.h"
#include "Textures.h"
#include "Weapon.h"

#define VAMPIREKILLER_HEIGHT 64
#define VAMPIREKILLER_WIDTH 160

#define VAMPIREKILLER_NOT_EXSIST 0
#define VAMPIREKILLER_EXSIST 1 


class CVampireKiller: public CWeapon
{
	int _level;
	static CVampireKiller* __instance;
public:

	static CVampireKiller* GetInstance();
	CVampireKiller() :CWeapon()
	{
		_level = 1;
		AddAnimation(600);
		AddAnimation(601);
		AddAnimation(602);
	}
	void SetPosition(float simon_x, float simon_y);
	void Render();
	void setDefaultLevel();
	void setUpLevel();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
};
#endif // !__VAMPIREILLER_H__