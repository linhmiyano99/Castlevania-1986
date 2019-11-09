#ifndef __TORCH_H_
#define __TORCH_H_




#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"

//item
#include "WhipUpgrade.h"
#include "ItemDagger.h"
#include "ItemHeart.h"
#include "Define.h"

#define TORCH_WIDTH 32
#define TORCH_HEIGHT 64
#define CANDLE_WIDTH 16
#define CANDLE_HEIGHT 32

#define TORCH_STATE_NOT_EXSIST 0
#define TORCH_STATE_EXSIST 1
#define TORCH_STATE_ITEM 2
#define TORCH_STATE_ITEM_NOT_EXSIST 3


#define ID_WHIPUPGRADE  1
#define ID_DAGGER		2
#define ID_HEART		3



class CTorch : public CGameObject
{
protected:
	DWORD dt_die;
	CItem* item;
	int _level;
public:


	CTorch(float _x, float _y, int id = 0, int _level = 0);
	~CTorch()
	{
		CGameObject::~CGameObject();
		SAFE_DELETE(item);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetPosition(float _x, float _y) { x = _x; y = _y; if(item != NULL) item->SetPosition(_x, _y); }
	virtual CItem* GetItem() { return item; }
};
#endif // !__TORCH_H_