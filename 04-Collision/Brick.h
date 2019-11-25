#ifndef __BRICK_H_

#define __BRICK_H_




#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "MagagementTexture.h"
#include "Define.h"
#include "ItemChicken.h"
#include "Torch.h"
#include "BrickBreak.h"

#define BRICK_WIDTH 32

class CBrick : public CTorch
{
	vector<CBrickBreak*> list;
public:
	CBrick(float _x, float _y, int id = 0, int type = 0);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};
#endif // !__BRICK_H_
