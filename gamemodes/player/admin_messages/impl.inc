#include <YSI\y_hooks>

loadtext lang[admin_messages];

public OnPlayerGetAdminPunishment(playerid, player_name[], adminid, type, reason[])
{
	if(type == PUNISHMENT_TYPE_AC_WARN)
	{	
		new string[145];
		format(string, sizeof string, "{FFFF00}[AC-WARN] {FFFFFF}%s (%d) [%s]", player_name, playerid, reason);
		foreach(new i : Player)
		{
			if(GetPlayerGameState(i) == GAME_STATE_SPAWNED && PI[i][pi_ADMIN_MESSAGES] && PI[i][pi_ADMIN_LEVEL] > 0)
			SendClientMessage(i, -1, string);
		}
	}
	else
	{
		foreach(new i : Player)
		{
			if(GetPlayerGameState(i) == GAME_STATE_SPAWNED && PI[i][pi_ADMIN_MESSAGES])
			{
				switch(type)
				{
					case PUNISHMENT_TYPE_PERM_BAN: Text_Send(i, $MESSAGE_ADMIN_PERM_BAN, PI[adminid][pi_NAME], adminid, player_name, playerid, reason);
					case PUNISHMENT_TYPE_TEMP_BAN: Text_Send(i, $MESSAGE_ADMIN_TEMP_BAN, PI[adminid][pi_NAME], adminid, player_name, playerid, reason);
					case PUNISHMENT_TYPE_KICK: Text_Send(i, $MESSAGE_ADMIN_KICK, PI[adminid][pi_NAME], adminid, player_name, playerid, reason);
					case PUNISHMENT_TYPE_AC_KICK: Text_Send(i, $MESSAGE_ADMIN_AC_KICK, player_name, playerid, reason);
				}
			}
		}
	}
	return 1;
}