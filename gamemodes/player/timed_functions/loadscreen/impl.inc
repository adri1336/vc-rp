#include <YSI\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
	DestroyPlayerLoadScreen(playerid, false);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	DestroyPlayerLoadScreen(playerid, false);
	return 1;
}

timer OnLoadScreenFinish[2000](playerid)
{
	loadscreen_timer[playerid] = Timer:-1;
	TogglePlayerControllable(playerid, true);
	DestroyPlayerLoadScreen(playerid, true);
}