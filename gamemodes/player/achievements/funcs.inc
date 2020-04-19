loadtext lang[achievements];

ShowAchievementTextDraw(playerid, string[], seconds = 5, bool:sound = true)
{
	HidePlayerAchievement(playerid);

	new Float:bgresult_x, Float:bgresult_size_x, Float:result_x, Float:result_size_x;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 320.0, ACHIEVEMENT_TD_BG_SIZEX, true, bgresult_x, bgresult_size_x);
	PTD_pAchievement[playerid][0] = CreatePlayerTextDraw(playerid, bgresult_x, 365.000000, ""TEXTDRAW_CUSTOM_PATH"prize_bg");
	PlayerTextDrawTextSize(playerid, PTD_pAchievement[playerid][0], bgresult_size_x, ACHIEVEMENT_TD_SIZE);
	PlayerTextDrawAlignment(playerid, PTD_pAchievement[playerid][0], 1);
	PlayerTextDrawColor(playerid, PTD_pAchievement[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, PTD_pAchievement[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_pAchievement[playerid][0], 255);
	PlayerTextDrawFont(playerid, PTD_pAchievement[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, PTD_pAchievement[playerid][0], 0);

	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, ACHIEVEMENT_TD_SIZE, false, result_x, result_size_x);
	PTD_pAchievement[playerid][1] = CreatePlayerTextDraw(playerid, bgresult_x - result_size_x, 365.000000, ""TEXTDRAW_CUSTOM_PATH"prize_icon");
	PlayerTextDrawTextSize(playerid, PTD_pAchievement[playerid][1], result_size_x, ACHIEVEMENT_TD_SIZE);
	PlayerTextDrawAlignment(playerid, PTD_pAchievement[playerid][1], 1);
	PlayerTextDrawColor(playerid, PTD_pAchievement[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, PTD_pAchievement[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_pAchievement[playerid][1], 255);
	PlayerTextDrawFont(playerid, PTD_pAchievement[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, PTD_pAchievement[playerid][1], 0);

	PTD_pAchievement[playerid][2] = CreatePlayerTextDraw(playerid, bgresult_x + bgresult_size_x, 365.000000, ""TEXTDRAW_CUSTOM_PATH"prize_icon2");
	PlayerTextDrawTextSize(playerid, PTD_pAchievement[playerid][2], result_size_x, ACHIEVEMENT_TD_SIZE);
	PlayerTextDrawAlignment(playerid, PTD_pAchievement[playerid][2], 1);
	PlayerTextDrawColor(playerid, PTD_pAchievement[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, PTD_pAchievement[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_pAchievement[playerid][2], 255);
	PlayerTextDrawFont(playerid, PTD_pAchievement[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, PTD_pAchievement[playerid][2], 0);

	new lines, Float:letter_x = 0.246998, Float:pos_y, Float:separation;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, 10.0, false, result_x, separation);
	new Float:text_size_x = bgresult_size_x + (result_size_x - separation);
	lines = GetTdLines(1, string, true, 0.0, letter_x, text_size_x);
	switch(lines)
	{
		case 1: pos_y = 376.2;
		case 2: pos_y = 371.2;
		default: pos_y = 366.2;
	}

	PTD_pAchievement[playerid][3] = CreatePlayerTextDraw(playerid, 320.0 + (result_size_x / 2), pos_y, string);
	PlayerTextDrawLetterSize(playerid, PTD_pAchievement[playerid][3], letter_x, 1.143702);
	PlayerTextDrawTextSize(playerid, PTD_pAchievement[playerid][3], 0.0, text_size_x);
	PlayerTextDrawAlignment(playerid, PTD_pAchievement[playerid][3], 2);
	PlayerTextDrawColor(playerid, PTD_pAchievement[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, PTD_pAchievement[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_pAchievement[playerid][3], 255);
	PlayerTextDrawFont(playerid, PTD_pAchievement[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, PTD_pAchievement[playerid][3], 1);

	if(seconds) PTD_pAchievement_Timer[playerid] = defer HidePlayerAchievement_Timer[seconds*1000](playerid);
	if(sound) PlayerPlaySound(playerid, ACHIEVEMENT_SOUND_ID, 0.0, 0.0, 0.0);

	PlayerTextDrawShow(playerid, PTD_pAchievement[playerid][0]);
	PlayerTextDrawShow(playerid, PTD_pAchievement[playerid][1]);
	PlayerTextDrawShow(playerid, PTD_pAchievement[playerid][2]);
	PlayerTextDrawShow(playerid, PTD_pAchievement[playerid][3]);
	return 1;
}

HidePlayerAchievement(playerid)
{
	for(new i, j = sizeof PTD_pAchievement[]; i != j; i++)
	{
		if(PTD_pAchievement[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_pAchievement[playerid][i]);
			PTD_pAchievement[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	if(PTD_pAchievement_Timer[playerid] != Timer:-1)
	{
		stop PTD_pAchievement_Timer[playerid];
		PTD_pAchievement_Timer[playerid] = Timer:-1;
	}
	return 1;
}

LoadPlayerAchievements(playerid)
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_ACHIEVEMENTS)
				{
					printf("[ERROR]: Límite rebasado en pAchievements en LoadPlayerAchievements (pid: %d)", PI[playerid][pi_ID]);
					break;
				}

				cache_get_value_name_int(i, "id_achievement", _:pAchievements[playerid][i][pAch_ID]);
				cache_get_value_name(i, "date", pAchievements[playerid][i][pAch_DATE], 24);
				Iter_Add(pAchievements[playerid], i);
			}
		}
	}

	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM player_achievements WHERE id_player = '%d';", PI[playerid][pi_ID]);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	return 1;	
}

AddPlayerAchievement(playerid, ACHIEVEMENTS:id, bool:info = true)
{
	new slot = Iter_Free(pAchievements[playerid]);
	if(slot != cellmin)
	{
		new datetime[24];
		getDateTime(datetime);
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_achievements VALUES (%d, %d, '%s');", PI[playerid][pi_ID], _:id, datetime);
		mysql_tquery(vcrp_db, QUERY_BUFFER);

		pAchievements[playerid][slot][pAch_ID] = id;
		format(pAchievements[playerid][slot][pAch_DATE], 24, "%s", datetime);
		Iter_Add(pAchievements[playerid], slot);

		if(info) ShowAchievementTextDraw(playerid, GetAchievementName(playerid, id));
		return 1;
	}
	return 0;
}

PlayerAchievementsContainsId(playerid, ACHIEVEMENTS:id)
{
	foreach(new i : pAchievements[playerid])
	{
		if(pAchievements[playerid][i][pAch_ID] == id)
		{
			return 1;
		}
	}
	return 0;
}

GetAchievementName(playerid, ACHIEVEMENTS:id, bool:td = true)
{
	new name[256];
	if(td)
	{
		switch(id)
		{
			case ACHIEVEMENT_NEW_USER: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_NEW_USER, SERVER_NAME);
			case ACHIEVEMENT_RENT_CAR: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_RENT_CAR);
			case ACHIEVEMENT_PURCHASE_CAR: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_PURCHASE_CAR);
			case ACHIEVEMENT_PURCHASE_USED_CAR: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_PURCHASE_USED_CAR);
			case ACHIEVEMENT_DRIVER_LICENSE: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_DRIVER_LICENSE);
			case ACHIEVEMENT_HOSPITAL_BED: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_HOSPITAL_BED);
			case ACHIEVEMENT_USE_ATM: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_USE_ATM);
			case ACHIEVEMENT_PURCHASE_PROPERTY: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_PURCHASE_PROPERTY);
			case ACHIEVEMENT_RENT_PROPERTY: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_RENT_PROPERTY);
			case ACHIEVEMENT_PURCHASE_BUSINESS: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_PURCHASE_BUSINESS);
			case ACHIEVEMENT_GUN_LICENSE: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_GUN_LICENSE);
			case ACHIEVEMENT_INTRO: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $TD_ACHIEVEMENT_INTRO);
		}
	}
	else
	{
		switch(id)
		{
			case ACHIEVEMENT_NEW_USER: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_NEW_USER);
			case ACHIEVEMENT_RENT_CAR: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_RENT_CAR);
			case ACHIEVEMENT_PURCHASE_CAR: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_PURCHASE_CAR);
			case ACHIEVEMENT_PURCHASE_USED_CAR: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_PURCHASE_USED_CAR);
			case ACHIEVEMENT_DRIVER_LICENSE: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_DRIVER_LICENSE);
			case ACHIEVEMENT_HOSPITAL_BED: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_HOSPITAL_BED);
			case ACHIEVEMENT_USE_ATM: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_USE_ATM);
			case ACHIEVEMENT_PURCHASE_PROPERTY: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_PURCHASE_PROPERTY);
			case ACHIEVEMENT_RENT_PROPERTY: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_RENT_PROPERTY);
			case ACHIEVEMENT_PURCHASE_BUSINESS: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_PURCHASE_BUSINESS);
			case ACHIEVEMENT_GUN_LICENSE: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_GUN_LICENSE);
			case ACHIEVEMENT_INTRO: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $ACHIEVEMENT_INTRO);
		}
	}
	return name;
}