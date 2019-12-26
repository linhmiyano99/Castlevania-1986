#include "Code.h"
#include "Sprites.h"

void CCode::DrawNumber(int max, float x, float y, int s)
{
	string str = to_string(s);

	for (int i = 0; i < max - str.size(); i++)
	{
		CSprites::GetInstance()->Get(60000)->Draw(x, y);
		x += 15;
	}
	for (int i = 0; i < str.size(); i++)
	{
		CSprites::GetInstance()->Get(60000 + convert(str[i]))->Draw(x, y);
		x += 15;
	}
}
void CCode::DrawEnergyBar(float x, float y, int type, int s)
{
	CSprites* sprites = CSprites::GetInstance();
	CSprite* sprite1 = sprites->Get(60011);
	CSprite* sprite2 = NULL;
	if(type == 0)
		sprite2 = sprites->Get(60012);
	else
		sprite2 = sprites->Get(60013);
	for (int i = 0; i < s; i++)
	{
		sprite2->Draw(x, y);
		x += 11;
	}
	for (int i = 0; i < 16 - s; i++)
	{
		sprite1->Draw(x, y);
		x += 11;
	}
	sprites = NULL;
	sprite1 = NULL;
	sprite2 = NULL;
}

int CCode::convert(char c)
{
	return c - '0';
}