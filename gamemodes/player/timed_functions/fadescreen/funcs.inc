stock FadePlayerScreenTimed(playerid, from, to, time = 700, fadescreen_color = 0xFFFFFF, bool:disable_layers = true)
{
	if(fadescreen_timer[playerid] != Timer:-1)
	{
		stop fadescreen_timer[playerid];
		fadescreen_timer[playerid] = Timer:-1;
	}
	pFadeScreenColor[playerid] = fadescreen_color;
	fadescreen_timer[playerid] = defer FadePlayerScreenTimed_Timer[time](playerid, from, to);
	if(disable_layers) DisablePlayerLayers(playerid, LAYER_FADESCREEN);
	CallRemoteFunction("OnPlayerFadeScreenStart", "i", playerid);
	return 1;
}