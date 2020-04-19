#include <YSI\y_hooks>

hook OnPlayerLogin(playerid)
{
	SetPlayerTextDrawLayer(playerid, screen_fade_ptd[playerid], LAYER_FADESCREEN);
	return 1;
}

hook OnFadeComplete(playerid, bool:in, color, fadeid)
{
	EnablePlayerLayers(playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(fadescreen_timer[playerid] != Timer:-1)
	{
		stop fadescreen_timer[playerid];
		fadescreen_timer[playerid] = Timer:-1;
	}
	return 1;
}

timer FadePlayerScreenTimed_Timer[700](playerid, from, to)
{
	freezeplayer_timer[playerid] = Timer:-1;
	FadePlayerScreen(playerid, pFadeScreenColor[playerid], from, to);
}