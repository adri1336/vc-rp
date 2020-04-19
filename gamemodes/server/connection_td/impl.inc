#include <YSI\y_hooks>

hook OnScriptInit()
{
	CreateConnectionTextdraws();
	return 1;
}

hook OnScriptExit()
{
	DestroyConnectionTextdraws();
	return 1;
}