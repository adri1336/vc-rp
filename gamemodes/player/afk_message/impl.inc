#include <YSI\y_hooks>

loadtext lang[afk];

hook OnPlayerUnPause(playerid, time_sec)
{
	if(GetPlayerGameState(playerid) == GAME_STATE_SPAWNED && time_sec > 5)
	{
		new days, hours, minutes, seconds;
		TimeConvert(time_sec, days, hours, minutes, seconds);

		if(days) Text_Send(playerid, $MESSAGE_INFO_AFK_DAYS, days, hours, minutes);
		else if(hours) Text_Send(playerid, $MESSAGE_INFO_AFK_HOURS, hours, minutes);
		else if(minutes) Text_Send(playerid, $MESSAGE_INFO_AFK_MINUTES, minutes, seconds);
		else Text_Send(playerid, $MESSAGE_INFO_AFK_SECONDS, time_sec);
	}
	return 1;
}