loadtext lang[pstats];

CreatePlayerStatsProgressbars(playerid)
{
	new Float:result_x, Float:result_size_x, Float:separation;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, 145.0, false, result_x, result_size_x);
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, 5.0, false, result_x, separation);
	PROGRESSBAR_REPUTATION[playerid] = CreatePlayerProgressBar(playerid, 20.0 + separation, 353.0, result_size_x, 5.0, -2105376001, -1);
	SetPlayerTextDrawLayer(playerid, PlayerProgress_Bar[playerid][ PROGRESSBAR_REPUTATION[playerid] ][playerprogress_bar_BOX], LAYER_STATS);
	SetPlayerTextDrawLayer(playerid, PlayerProgress_Bar[playerid][ PROGRESSBAR_REPUTATION[playerid] ][playerprogress_bar_BAR], LAYER_STATS);

	PROGRESSBAR_HUNGRY[playerid] = CreatePlayerProgressBar(playerid, 20.0 + separation, 386.0, result_size_x, 5.0, -2105376001, -1);
	SetPlayerTextDrawLayer(playerid, PlayerProgress_Bar[playerid][ PROGRESSBAR_HUNGRY[playerid] ][playerprogress_bar_BOX], LAYER_STATS);
	SetPlayerTextDrawLayer(playerid, PlayerProgress_Bar[playerid][ PROGRESSBAR_HUNGRY[playerid] ][playerprogress_bar_BAR], LAYER_STATS);

	PROGRESSBAR_THIRST[playerid] = CreatePlayerProgressBar(playerid, 20.0 + separation, 412.0, result_size_x, 5.0, -2105376001, -1);
	SetPlayerTextDrawLayer(playerid, PlayerProgress_Bar[playerid][ PROGRESSBAR_THIRST[playerid] ][playerprogress_bar_BOX], LAYER_STATS);
	SetPlayerTextDrawLayer(playerid, PlayerProgress_Bar[playerid][ PROGRESSBAR_THIRST[playerid] ][playerprogress_bar_BAR], LAYER_STATS);
	return 1;
}

DestroyPlayerStatsProgressbars(playerid)
{
	if(PROGRESSBAR_REPUTATION[playerid] != INVALID_PROGRESS_BAR_ID)
	{
		DestroyPlayerProgressBar(playerid, PROGRESSBAR_REPUTATION[playerid]);
		PROGRESSBAR_REPUTATION[playerid] = INVALID_PROGRESS_BAR_ID;
	}
	if(PROGRESSBAR_HUNGRY[playerid] != INVALID_PROGRESS_BAR_ID)
	{
		DestroyPlayerProgressBar(playerid, PROGRESSBAR_HUNGRY[playerid]);
		PROGRESSBAR_HUNGRY[playerid] = INVALID_PROGRESS_BAR_ID;
	}
	if(PROGRESSBAR_THIRST[playerid] != INVALID_PROGRESS_BAR_ID)
	{
		DestroyPlayerProgressBar(playerid, PROGRESSBAR_THIRST[playerid]);
		PROGRESSBAR_THIRST[playerid] = INVALID_PROGRESS_BAR_ID;
	}
	return 1;
}

CreatePlayerStatsTextdraws(playerid)
{
	new Float:result_x, Float:result_size_x, Float:separation;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, 155.0, false, result_x, result_size_x);
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, 5.0, false, result_x, separation);
	PTD_PLAYER_STATS[playerid][0] = CreatePlayerTextDraw(playerid, 20.000000, 320.000000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, PTD_PLAYER_STATS[playerid][0], result_size_x, 110.000000);
	PlayerTextDrawAlignment(playerid, PTD_PLAYER_STATS[playerid][0], 1);
	PlayerTextDrawFont(playerid, PTD_PLAYER_STATS[playerid][0], 4);
	PlayerTextDrawColor(playerid, PTD_PLAYER_STATS[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, PTD_PLAYER_STATS[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_PLAYER_STATS[playerid][0], 255);
	PlayerTextDrawSetProportional(playerid, PTD_PLAYER_STATS[playerid][0], 0);
	SetPlayerTextDrawLayer(playerid, PTD_PLAYER_STATS[playerid][0], LAYER_STATS);

	PTD_PLAYER_STATS[playerid][1] = CreatePlayerTextDraw(playerid, 20.0 + separation, 328.000000, "Level_0~n~Reputation_0/0");
	PlayerTextDrawLetterSize(playerid, PTD_PLAYER_STATS[playerid][1], 0.263666, 1.226666);
	PlayerTextDrawAlignment(playerid, PTD_PLAYER_STATS[playerid][1], 1);
	PlayerTextDrawColor(playerid, PTD_PLAYER_STATS[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, PTD_PLAYER_STATS[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_PLAYER_STATS[playerid][1], 255);
	PlayerTextDrawFont(playerid, PTD_PLAYER_STATS[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, PTD_PLAYER_STATS[playerid][1], 1);
	SetPlayerTextDrawLayer(playerid, PTD_PLAYER_STATS[playerid][1], LAYER_STATS);

	PTD_PLAYER_STATS[playerid][2] = CreatePlayerTextDraw(playerid, 20.0 + separation, 373.000000, "Hungry");
	PlayerTextDrawLetterSize(playerid, PTD_PLAYER_STATS[playerid][2], 0.263666, 1.226666);
	PlayerTextDrawAlignment(playerid, PTD_PLAYER_STATS[playerid][2], 1);
	PlayerTextDrawColor(playerid, PTD_PLAYER_STATS[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, PTD_PLAYER_STATS[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_PLAYER_STATS[playerid][2], 255);
	PlayerTextDrawFont(playerid, PTD_PLAYER_STATS[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, PTD_PLAYER_STATS[playerid][2], 1);
	SetPlayerTextDrawLayer(playerid, PTD_PLAYER_STATS[playerid][2], LAYER_STATS);

	PTD_PLAYER_STATS[playerid][3] = CreatePlayerTextDraw(playerid, 20.0 + separation, 398.000000, "Thirst");
	PlayerTextDrawLetterSize(playerid, PTD_PLAYER_STATS[playerid][3], 0.263666, 1.226666);
	PlayerTextDrawAlignment(playerid, PTD_PLAYER_STATS[playerid][3], 1);
	PlayerTextDrawColor(playerid, PTD_PLAYER_STATS[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, PTD_PLAYER_STATS[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_PLAYER_STATS[playerid][3], 255);
	PlayerTextDrawFont(playerid, PTD_PLAYER_STATS[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, PTD_PLAYER_STATS[playerid][3], 1);
	SetPlayerTextDrawLayer(playerid, PTD_PLAYER_STATS[playerid][3], LAYER_STATS);
	return 1;
}

DestroyPlayerStatsTextdraws(playerid)
{
	for(new i = 0, j = sizeof PTD_PLAYER_STATS[]; i != j; i ++)
	{
		if(PTD_PLAYER_STATS[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_PLAYER_STATS[playerid][i]);
			PTD_PLAYER_STATS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

ShowPlayerStatsTextdraws(playerid)
{
	for(new i = 0, j = sizeof PTD_PLAYER_STATS[]; i != j; i ++)
	{
		if(PTD_PLAYER_STATS[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawShow(playerid, PTD_PLAYER_STATS[playerid][i]);
		}
	}
	return 1;
}

HidePlayerStatsTextdraws(playerid)
{
	for(new i = 0, j = sizeof PTD_PLAYER_STATS[]; i != j; i ++)
	{
		if(PTD_PLAYER_STATS[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, PTD_PLAYER_STATS[playerid][i]);
		}
	}
	return 1;
}

ShowPlayerStatsMenu(playerid)
{
	if(pStatsMenu[playerid] || GetPlayerGameState(playerid) != GAME_STATE_SPAWNED) return 0;

	FormatPlayerStatsTextDraws_Lvl(playerid, PI[playerid][pi_LEVEL], PI[playerid][pi_REPUTATION], PI[playerid][pi_LEVEL] * REP_MULTIPLIER, PTD_PLAYER_STATS[playerid][1]);
	ShowPlayerStatsTextdraws(playerid);
	SetPlayerProgressBarValue(playerid, PROGRESSBAR_HUNGRY[playerid], PI[playerid][pi_HUNGRY]);
	SetPlayerProgressBarValue(playerid, PROGRESSBAR_THIRST[playerid], PI[playerid][pi_THIRST]);
	ShowPlayerProgressBar(playerid, PROGRESSBAR_REPUTATION[playerid]);
	ShowPlayerProgressBar(playerid, PROGRESSBAR_HUNGRY[playerid]);
	ShowPlayerProgressBar(playerid, PROGRESSBAR_THIRST[playerid]);
	pStatsMenu[playerid] = true;
	DisablePlayerLayers(playerid, LAYER_STATS);
	CallRemoteFunction("OnPlayerOpenStatsTds", "i", playerid);
	return 1;
}

HidePlayerStatsMenu(playerid)
{
	if(!pStatsMenu[playerid]) return 0;

	HidePlayerStatsTextdraws(playerid);
	HidePlayerProgressBar(playerid, PROGRESSBAR_REPUTATION[playerid]);
	HidePlayerProgressBar(playerid, PROGRESSBAR_HUNGRY[playerid]);
	HidePlayerProgressBar(playerid, PROGRESSBAR_THIRST[playerid]);
	EnablePlayerLayers(playerid);
	pStatsMenu[playerid] = false;
	CallRemoteFunction("OnPlayerCloseStatsTds", "i", playerid);
	return 1;
}

FormatPlayerStatsTextDraws(playerid, PlayerText:td1, PlayerText:td2)
{
	PlayerTD_Text(playerid, td1, $TEXTDRAW_HUNGRY);
	PlayerTD_Text(playerid, td2, $TEXTDRAW_THIRST);
	return 1;
}

FormatPlayerStatsTextDraws_Lvl(playerid, level, Float:rep, max_rep, PlayerText:td)
{
	new td_str[128];
	Text_Format_TD(td_str, sizeof td_str, PI[playerid][pi_LANG_ID], $TEXTDRAW_STATS, level, rep, max_rep);
	PlayerTextDrawSetString(playerid, td, td_str);
	return 1;
}