#ifndef __BRICK_H_

#define __BRICK_H_




#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "MagagementTexture.h"

#define BRICK_WIDTH 32


class CBrick : public CGameObject
{
public:
	CBrick(int i = 0) :CGameObject()
	{
		if (i == 0) {
			AddAnimation(499);
		}
		else {
			AddAnimation(500);
		}
	}
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	//void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

};
#endif // !__BRICK_H_
