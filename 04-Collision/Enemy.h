#pragma once
#include"GameObject.h"
#include"Torch.h"
#include "Brick.h"

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
protected:
	int ny;
public:
	CEnemy(float _x, float _y, int id = 0, int level = 0) : CTorch(_x, _y, id, level)
	{
		
		dt_die = 0;
		state = TORCH_STATE_EXSIST;
		nx = ny = 1;

		/*switch (id)
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
		}*/
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	
};