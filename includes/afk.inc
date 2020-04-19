#if defined _inc_afk
	#endinput
#endif
#define _inc_afk

#include <YSI\y_hooks>

#define AFK_CHECK_TIMER_INTERVAL 1000

forward OnPlayerPause(playerid);
forward OnPlayerUnPause(playerid, time_sec);

new
	pOpuTime[MAX_PLAYERS],
	pAFKTime[MAX_PLAYERS],
	bool:pAFK[MAX_PLAYERS];

#define IsPlayerPaused(%0) pAFK[%0]

hook OnPlayerConnect(playerid)
{
	pAFK[playerid] = false;
	return 1;
}

hook OnPlayerUpdate(playerid)
{
	if(pAFK[playerid])
	{
		pAFK[playerid] = false;
		CallRemoteFunction("OnPlayerUnPause", "id", playerid, gettime() - pAFKTime[playerid]);
	}
	pOpuTime[playerid] = gettime();
	return 1;
}

ptask CheckPlayerAFK[AFK_CHECK_TIMER_INTERVAL](playerid)
{
	if(!pAFK[playerid])
	{
		if(gettime() - pOpuTime[playerid] > 2)
		{
			pAFKTime[playerid] = gettime();
			pAFK[playerid] = true;
			CallRemoteFunction("OnPlayerPause", "i", playerid);
		}
	}
	return 1;
}