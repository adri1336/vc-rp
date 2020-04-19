#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
	pCurrentDialogPage[playerid] = 0;
	return 1;
}