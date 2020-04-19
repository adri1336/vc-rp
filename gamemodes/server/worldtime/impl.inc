#include <YSI\y_hooks>

hook OnScriptInit()
{
	SetMyWorldTime(180);
	return 1;
}

task WorldTimeTimer[worldtime_timer_interval]()
{
	SERVER_TIME[1] ++;
	if(SERVER_TIME[1] == 60)
	{
		SERVER_TIME[0] ++;
		if(SERVER_TIME[0] == 24) SERVER_TIME[0] = 0;
		SERVER_TIME[1] = 0;
	}

	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) == GAME_STATE_SPAWNED)
		{
			SetPlayerTime(i, SERVER_TIME[0], SERVER_TIME[1]);
			SetPlayerWeather(i, SERVER_WEATHER);
		}
	}
}