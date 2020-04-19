#include <YSI\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
	if(pInRoute[playerid]) DestroyPlayerRoute(playerid);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(pInRoute[playerid]) DestroyPlayerRoute(playerid);
	return 1;
}

timer OnPlayerRouteUpdate[ROUTE_PERCENTAGE_UPDATE_MS](playerid)
{
	if(pInRoute[playerid])
	{
		new Float:percentage = GetPlayerRoutePercentage(playerid);
		if(pRoute_ProgressBar[playerid] != INVALID_PROGRESS_BAR_ID)
		{
			SetPlayerProgressBarValue(playerid, pRoute_ProgressBar[playerid], percentage);
			ShowPlayerProgressBar(playerid, pRoute_ProgressBar[playerid]);
		}
		if(pRoute_Percentage_TD[playerid] != PlayerText:INVALID_TEXT_DRAW)
		{
			new string[24];
			format(string, sizeof string, "%.0f%%", percentage);
			PlayerTextDrawSetString(playerid, pRoute_Percentage_TD[playerid], string);
		}
	}
	else DestroyPlayerRoute(playerid);
	return 1;
}