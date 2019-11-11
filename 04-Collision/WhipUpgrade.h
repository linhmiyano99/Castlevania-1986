#ifndef __WHIPUPGRADE_H_
#define __WHIPUPGRADE_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define WHIPUPGRADE_WIDTH 32
#define WHIPUPGRADE_HEIGHT 32

#define WHIPUPGRADE_ANI_FIRE 7

class CWhipUpgrade : public CItem
{
public:
	CWhipUpgrade(float _x, float _y) : CItem(_x, _y)
	{
		AddAnimation(700);
		_type = eType::WHIPUPGRADE;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
#endif // !__WHIPUPGRADE_H_