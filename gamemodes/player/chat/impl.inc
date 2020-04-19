#include <YSI\y_hooks>

loadtext lang[chat];

hook OnPlayerText(playerid, text[])
{
	if(GetPlayerGameState(playerid) == GAME_STATE_SPAWNED)
	{
		ChatMsg(playerid, 15.0, text);
		SetPlayerChatBubble(playerid, text, 0xFFFFFFFF, 15.0, 5000);
	}
	return Y_HOOKS_BREAK_RETURN_0;
}

ChatMsg(playerid, Float:radi, text[], bool:phone = false)
{
	new drunk_level = GetPlayerDrunkLevel(playerid),
		Float:oldposx, Float:oldposy, Float:oldposz, current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);

	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, radi, oldposx, oldposy, oldposz))
		{
			if(phone) Text_Send(i, $MESSAGE_CHAT_PHONE, PI[playerid][pi_RP_NAME], text);
			else
			{
				if(drunk_level > 2000) Text_Send(i, $MESSAGE_CHAT_DRUNK, PI[playerid][pi_RP_NAME], text);
				else Text_Send(i, $MESSAGE_CHAT, PI[playerid][pi_RP_NAME], text);
			}
		}
	}
	return 1;
}