#include <YSI\y_hooks>

loadtext lang[disconnect_message];

Disconnect_Message(playerid, reason, player_name[])
{
	new current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid),
		Float:pos_x, Float:pos_y, Float:pos_z;

	GetPlayerPos(playerid, pos_x, pos_y, pos_z);
	if(GetPlayerGameState(playerid) >= GAME_STATE_SPAWNED)
	{
		foreach(new i : Player)
		{
			if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
			if(GetPlayerVirtualWorld(i) != current_vw) continue;
			if(GetPlayerInterior(i) != current_int) continue;

			if(IsPlayerInRangeOfPoint(i, 15.0, pos_x, pos_y, pos_z))
			{
				switch(reason)
				{
					case 0: Text_Send(i, $MESSAGE_INFO_DISCONNECT_CRASH, player_name);
					case 1: Text_Send(i, $MESSAGE_INFO_DISCONNECT_QUIT, player_name);
					case 2: Text_Send(i, $MESSAGE_INFO_DISCONNECT_KICK, player_name);
				}
			}
		}
	}
	return 1;
}