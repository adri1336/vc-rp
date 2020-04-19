#include <YSI\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
	if(timedkick_timer[playerid] != Timer:-1)
	{
		stop timedkick_timer[playerid];
		timedkick_timer[playerid] = Timer:-1;
	}
	return 1;
}

timer Kick_Timer[2000](playerid)
{
	timedkick_timer[playerid] = Timer:-1;
	Kick(playerid);
}