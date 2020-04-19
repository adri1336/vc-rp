stock FreezePlayerTimed(playerid, time = 2000)
{
	if(freezeplayer_timer[playerid] != Timer:-1)
	{
		stop freezeplayer_timer[playerid];
		freezeplayer_timer[playerid] = Timer:-1;
	}

	TogglePlayerControllable(playerid, false);
	freezeplayer_timer[playerid] = defer UnfreezePlayer[time](playerid);
	return 1;
}