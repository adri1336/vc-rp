#include <YSI\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
	if(freezeplayer_timer[playerid] != Timer:-1)
	{
		stop freezeplayer_timer[playerid];
		freezeplayer_timer[playerid] = Timer:-1;
	}
	return 1;
}

timer UnfreezePlayer[2000](playerid)
{
	freezeplayer_timer[playerid] = Timer:-1;
	TogglePlayerControllable(playerid, true);
}