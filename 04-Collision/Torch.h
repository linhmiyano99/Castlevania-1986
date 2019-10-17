#ifndef __TORCH_H_
#define __TORCH_H_




#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"

//item
#include "WhipUpgrade.h"
#include "ItemDagger.h"
#include "ItemHeart.h"

#define TORCH_WIDTH 32
#define TORCH_HEIGHT 64

#define TORCH_STATE_NOT_EXSIST 0
#define TORCH_STATE_EXSIST 1
#define TORCH_STATE_ITEM 2
#define TORCH_STATE_ITEM_NOT_EXSIST 3


#define ID_WHIPUPGRADE  1
#define ID_DAGGER		2
#define ID_HEART		3



class CTorch : public CGameObject
{
	DWORD dt_die;
	CItem* item;
	int _level;
public:


	CTorch(int id = 0, int _level = 0);
	~CTorch()
	{
		CGameObject::~CGameObject();
		if (item != NULL)
			delete item;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetPosition(float _x, float _y) { x = _x; y = _y; if(item != NULL) item->SetPosition(_x, _y); }
	CItem* GetItem() { return item; }
};
#endif // !__TORCH_H_