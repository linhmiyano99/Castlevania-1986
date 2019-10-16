#include"Terminal.h"

CTerminal* CTerminal::__instance = NULL;

CTerminal* CTerminal::GetInstance()
{
	if (__instance == NULL) __instance = new CTerminal();
	return __instance;
}