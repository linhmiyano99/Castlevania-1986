#ifndef __BRICK_H_

#define __BRICK_H_




#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "MagagementTexture.h"
#include "Define.h"
#include "ItemChicken.h"
#include "Torch.h"

#define BRICK_WIDTH 32

class CBrick : public CTorch
{
public:
	CBrick(float _x, float _y, int id = 0, int level = 0);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__BRICK_H_
