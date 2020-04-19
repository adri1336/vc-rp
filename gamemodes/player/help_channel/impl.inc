#include <YSI\y_hooks>

loadtext lang[help_channel];

hook OnPlayerLogin(playerid)
{
	pLastDoubt[playerid] = gettime();
	return 1;
}

YCMD:doubt(playerid, params[], help)
{
	new string[145];
	if(!sscanf(params, "s[145]", string))
	{
		if(PI[playerid][pi_ADMIN_LEVEL] == 0 && gettime() - pLastDoubt[playerid] < MIN_TIME_BETWEEN_DOUBTS)
		{
			new time_sec = MIN_TIME_BETWEEN_DOUBTS - (gettime() - pLastDoubt[playerid]);
			Text_Send(playerid, $MESSAGE_ERROR_TIME, time_sec);
		}
		else
		{
			foreach(new i : Player)
			{
				if(GetPlayerGameState(i) == GAME_STATE_SPAWNED && PI[i][pi_HELP_CHANNEL])
				{
					Text_Send(i, $MESSAGE_HELP_CHANNEL, PI[playerid][pi_LANG], PI[playerid][pi_NAME], playerid, string);
				}
			}
			pLastDoubt[playerid] = gettime();
		}
	}
	else Text_Send(playerid, $MESSAGE_ERROR_SYNTAX);
	return 1;
}