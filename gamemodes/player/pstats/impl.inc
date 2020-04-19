#include <YSI\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
	DestroyPlayerStatsTextdraws(playerid);
	DestroyPlayerStatsProgressbars(playerid);
	return 1;
}

hook OnPlayerLogin(playerid)
{
	CreatePlayerStatsTextdraws(playerid);
	CreatePlayerStatsProgressbars(playerid);
	FormatPlayerStatsTextDraws(playerid, PTD_PLAYER_STATS[playerid][2], PTD_PLAYER_STATS[playerid][3]);

	SetPlayerProgressBarValue(playerid, PROGRESSBAR_REPUTATION[playerid], GetPlayerRepPercent(playerid, REP_MULTIPLIER));
	SetPlayerProgressBarValue(playerid, PROGRESSBAR_HUNGRY[playerid], PI[playerid][pi_HUNGRY]);
	SetPlayerProgressBarValue(playerid, PROGRESSBAR_THIRST[playerid], PI[playerid][pi_THIRST]);
	return 1;
}

hook OnPlayerGameStateChange(playerid, newstate, oldstate)
{
	if(oldstate == _:GAME_STATE_SPAWNED && pStatsMenu[playerid])
	{
		HidePlayerStatsMenu(playerid);
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(GetPlayerGameState(playerid) == GAME_STATE_SPAWNED)
	{
		if(PRESSED(KEY_SHOW_PSTATS)) ShowPlayerStatsMenu(playerid);
		else if(RELEASED(KEY_SHOW_PSTATS)) HidePlayerStatsMenu(playerid);
	}
	return 1;
}