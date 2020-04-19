ptask PlayerTask[PlayerTask_Interval_Seconds * 1000](playerid)
{
	if(!IsPlayerPaused(playerid))
	{
		PI[playerid][pi_TIME_PLAYING] += PlayerTask_Interval_Seconds;
		if(GetPlayerGameState(playerid) == GAME_STATE_SPAWNED)
		{
			PI[playerid][pi_REPUTATION] += floatdiv(float(PlayerTask_Interval_Seconds), floatmul(floatdiv(float(MINUTES_FOR_REP), 60), 3600));

			if(PI[playerid][pi_REPUTATION] >= PI[playerid][pi_LEVEL] * REP_MULTIPLIER)
			{
				PI[playerid][pi_REPUTATION] = 1.0;	
				PI[playerid][pi_LEVEL] ++;
				orm_update(PI[playerid][pi_ORM]);
				FormatPtaskInfoMessage(playerid, 0);
				SetPlayerScore(playerid, PI[playerid][pi_LEVEL]);
			}

			SetPlayerProgressBarValue(playerid, PROGRESSBAR_REPUTATION[playerid], GetPlayerRepPercent(playerid, REP_MULTIPLIER));

			//sed y hambre
			PI[playerid][pi_THIRST] += floatdiv(float(PlayerTask_Interval_Seconds), floatmul(THIRST_HOURS, 36));
			PI[playerid][pi_HUNGRY] += floatdiv(float(PlayerTask_Interval_Seconds), floatmul(HUNGRY_HOURS, 36));
			if(PI[playerid][pi_THIRST] > 100.0) PI[playerid][pi_THIRST] = 100.0;
			if(PI[playerid][pi_HUNGRY] > 100.0) PI[playerid][pi_HUNGRY] = 100.0;

			SetPlayerProgressBarValue(playerid, PROGRESSBAR_HUNGRY[playerid], PI[playerid][pi_HUNGRY]);
			SetPlayerProgressBarValue(playerid, PROGRESSBAR_THIRST[playerid], PI[playerid][pi_THIRST]);

			new current_gettime = gettime();
			if(PI[playerid][pi_THIRST] > 60.0 && PI[playerid][pi_HUNGRY] > 60.0)
			{
				GivePlayerHealth(playerid, -((PI[playerid][pi_THIRST] + PI[playerid][pi_HUNGRY])/500));
				if(current_gettime - pLastHungryThirstInfoMsg[playerid] > MIN_SECONDS_BETWEEN_INFO_MSG)
				{
					FormatPtaskInfoMessage(playerid, 1);
					pLastHungryThirstInfoMsg[playerid] = current_gettime;
				}
			}
			else if(PI[playerid][pi_THIRST] > 60.0)
			{
				GivePlayerHealth(playerid, -(PI[playerid][pi_THIRST]/500));
				if(current_gettime - pLastHungryThirstInfoMsg[playerid] > MIN_SECONDS_BETWEEN_INFO_MSG)
				{
					FormatPtaskInfoMessage(playerid, 2);
					pLastHungryThirstInfoMsg[playerid] = current_gettime;
				}
			}
			else if(PI[playerid][pi_HUNGRY] > 60.0)
			{
				GivePlayerHealth(playerid, -(PI[playerid][pi_HUNGRY]/500));
				if(current_gettime - pLastHungryThirstInfoMsg[playerid] > MIN_SECONDS_BETWEEN_INFO_MSG)
				{
					FormatPtaskInfoMessage(playerid, 3);
					pLastHungryThirstInfoMsg[playerid] = current_gettime;
				}
			}
		}
	}
	return 1;
}