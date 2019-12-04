#ifndef __TORCH_H_
#define __TORCH_H_




#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"

//item
#include "WhipUpgrade.h"
#include "ItemDagger.h"
#include "ItemHeart.h"
#include "SmallHeart.h"
#include "Define.h"
#include "ItemChicken.h"
#include "Money.h"
#include "ItemBossBall.h"
#include "ItemAxe.h"
#include "ItemII.h"
#include "ItemBoongmerang.h"
#include "ItemClock.h"
#include "ItemCross.h"
#include "ItemHollyWatter.h"
#include "ItemIII.h"
#include "ItemVase.h"


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
#define ID_SMALLHEART	4
#define ID_CHICKEN		5
#define ID_MONEY_1		6
#define ID_MONEY_2		7
#define ID_MONEY_3		8
#define ID_MONEY_4		9
#define ID_BOSSBALL		10
#define ID_AXE   		11
#define ID_II			12
#define ID_CLOCK		13
#define ID_CROSS		14
#define ID_HOLLYWATTER	15
#define ID_BOONGMERANG	16
#define ID_VASE			17
#define ID_III			18



class CTorch : public CGameObject
{
protected:
	DWORD dt_die;
	CItem* item;
	DWORD dt_appear;
public:


	CTorch(float _x, float _y, int id = 0, int _level = 0);
	~CTorch();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetPosition(float _x, float _y) { x = _x; y = _y; if(item != NULL) item->SetPosition(_x, _y); }
	virtual CItem* GetItem() { return item; }

};
#endif // !__TORCH_H_