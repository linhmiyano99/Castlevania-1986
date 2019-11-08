#pragma once
#include <string>

using namespace std;

class CCode
{
private:
	int max;
public:

	void DrawNumber(int max,float x, float y, int s = 0);
	void DrawEnergyBar(float x, float y, int type = 0, int s = 0);
	int convert(char c);
};