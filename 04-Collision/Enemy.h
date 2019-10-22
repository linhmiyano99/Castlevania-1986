#pragma once
#include"GameObject.h"
#include"Torch.h"

#define ENEMY_WALKING_SPEED 0.05f;

#define ENEMY_BBOX_WIDTH 40
#define ENEMY_BBOX_HEIGHT 60

#define ENEMY_STATE_WALKING 100
#define ENEMY_STATE_DIE 200

#define ENEMY_ANI_WALKING 0
#define ENEMY_ANI_DIE 1

#define SIMON_GRAVITY			0.002f

class CEnemy : public CTorch
{
	

public:
	CEnemy(int id =0, int level = 0)
	{
		
		dt_die = 0;
		state = TORCH_STATE_EXSIST;
		animations.clear();
		AddAnimation(10000);
		AddAnimation(800);
		switch (id)
		{
		case ID_WHIPUPGRADE:
			item = new CWhipUpgrade();
			break;
		case ID_DAGGER:
			item = new CItemDagger();
			break;
		case ID_HEART:
			item = new CItemHeart();
			break;
		case 0:
			break;
		default:
			break;
		}
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	
};