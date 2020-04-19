TimedKick(playerid, time = 2000)
{
	if(timedkick_timer[playerid] != Timer:-1)
	{
		stop timedkick_timer[playerid];
		timedkick_timer[playerid] = Timer:-1;
	}

	timedkick_timer[playerid] = defer Kick_Timer[time](playerid);
	return 1;
}