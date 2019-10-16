#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "MagagementTexture.h"

#define BRICK_WIDTH 32


class CBrick : public CGameObject
{
public:
	CBrick() :CGameObject()
	{
		AddAnimation(500);
	}
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	//void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

};