loadtext lang[gps];

DestroyPlayerGpsTextdraws(playerid)
{
	for(new i = 0; i < sizeof GPS_Body_PTD[]; i ++)
	{
		if(GPS_Body_PTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, GPS_Body_PTD[playerid][i]);
			GPS_Body_PTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	for(new i = 0; i < sizeof GPS_Options_PTD[]; i ++)
	{
		if(GPS_Options_PTD[playerid][i][gps_option_ICON] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, GPS_Options_PTD[playerid][i][gps_option_ICON]);
			GPS_Options_PTD[playerid][i][gps_option_ICON] = PlayerText:INVALID_TEXT_DRAW;
		}
		if(GPS_Options_PTD[playerid][i][gps_option_TICK] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, GPS_Options_PTD[playerid][i][gps_option_TICK]);
			GPS_Options_PTD[playerid][i][gps_option_TICK] = PlayerText:INVALID_TEXT_DRAW;
		}
		if(GPS_Options_PTD[playerid][i][gps_option_TEXT] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, GPS_Options_PTD[playerid][i][gps_option_TEXT]);
			GPS_Options_PTD[playerid][i][gps_option_TEXT] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	if(GPS_MapID[playerid] != INVALID_VC_TDMAP_ID)
	{
		DestroyVcPTdMap(playerid, GPS_MapID[playerid]);
		GPS_MapID[playerid] = INVALID_VC_TDMAP_ID;
	}
	return 1;
}

CreatePlayerGpsTextdraws(playerid)
{
	new Float:result_x, Float:result_size_x, Float:result_mapsize_x, Float:result_paddingsize;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, PLAYER_GPS_MAP_SIZE_X, false, result_x, result_mapsize_x);
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, PLAYER_GPS_MAP_PADDING, false, result_x, result_paddingsize);
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], PLAYER_GPS_TD_X, PLAYER_GPS_TD_SIZE_X, true, result_x, result_size_x);

	GPS_Body_PTD[playerid][0] = CreatePlayerTextDraw(playerid, result_x, PLAYER_GPS_TD_Y, ""TEXTDRAW_CUSTOM_PATH"gps_body");
	PlayerTextDrawTextSize(playerid, GPS_Body_PTD[playerid][0], result_size_x, PLAYER_GPS_TD_SIZE_Y);
	PlayerTextDrawAlignment(playerid, GPS_Body_PTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, GPS_Body_PTD[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, GPS_Body_PTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, GPS_Body_PTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, GPS_Body_PTD[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, GPS_Body_PTD[playerid][0], 0);
	SetPlayerTextDrawLayer(playerid, GPS_Body_PTD[playerid][0], LAYER_GPS);

	GPS_Body_PTD[playerid][1] = CreatePlayerTextDraw(playerid, (result_x + result_size_x) - (PLAYER_GPS_CLOSE_BUTTON_PADDING * 1.5), PLAYER_GPS_TD_Y + PLAYER_GPS_CLOSE_BUTTON_PADDING, "~r~X");
	PlayerTextDrawLetterSize(playerid, GPS_Body_PTD[playerid][1], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, GPS_Body_PTD[playerid][1], 3);
	PlayerTextDrawColor(playerid, GPS_Body_PTD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, GPS_Body_PTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, GPS_Body_PTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, GPS_Body_PTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, GPS_Body_PTD[playerid][1], 1);
	PlayerTextDrawTextSize(playerid, GPS_Body_PTD[playerid][1], ((result_x + result_size_x) - (PLAYER_GPS_CLOSE_BUTTON_PADDING * 1.5)) + 20.0, 10.0);
	PlayerTextDrawSetSelectable(playerid, GPS_Body_PTD[playerid][1], true);
	SetPlayerTextDrawLayer(playerid, GPS_Body_PTD[playerid][1], LAYER_GPS);

	new Float:offx = (57.5 * result_size_x) / 512.0;
	GPS_Body_PTD[playerid][2] = CreatePlayerTextDraw(playerid, (result_x + result_size_x) - offx, 150.000000, "GPS");
	PlayerTextDrawLetterSize(playerid, GPS_Body_PTD[playerid][2], 0.230415, 1.314815);
	PlayerTextDrawTextSize(playerid, GPS_Body_PTD[playerid][2], 0.000000, 58.000000);
	PlayerTextDrawAlignment(playerid, GPS_Body_PTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, GPS_Body_PTD[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, GPS_Body_PTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, GPS_Body_PTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, GPS_Body_PTD[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, GPS_Body_PTD[playerid][2], 1);
	SetPlayerTextDrawLayer(playerid, GPS_Body_PTD[playerid][2], LAYER_GPS);

	GPS_Body_PTD[playerid][3] = CreatePlayerTextDraw(playerid, (result_x + result_size_x) - offx, 220.000000, "LEYENDA");
	PlayerTextDrawLetterSize(playerid, GPS_Body_PTD[playerid][3], 0.230415, 1.314815);
	PlayerTextDrawTextSize(playerid, GPS_Body_PTD[playerid][3], 0.000000, 58.000000);
	PlayerTextDrawAlignment(playerid, GPS_Body_PTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, GPS_Body_PTD[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, GPS_Body_PTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, GPS_Body_PTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, GPS_Body_PTD[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, GPS_Body_PTD[playerid][3], 1);
	SetPlayerTextDrawLayer(playerid, GPS_Body_PTD[playerid][3], LAYER_GPS);

	//options
	//fijas
	new td_count, Float:offset_y = 48.0,
		Float:text_pos_x = (result_x + result_size_x) - (PLAYER_GPS_OPTION_PADDING * 1.5);

	for(new i = 0; i < _:GPS_OPTION_CATEGORY_DB; i ++)
	{
		new str[24];
		format(str, sizeof str, "Option %d", i);
		new Float:letterx = 0.4;//GetTdTextFontX(1, str, true, 0.0, PLAYER_GPS_TEXT_MAX_SIZE);

		GPS_Options_PTD[playerid][td_count][gps_option_TEXT] = CreatePlayerTextDraw(playerid, text_pos_x, PLAYER_GPS_TD_Y + offset_y, str);
		PlayerTextDrawLetterSize(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], letterx, PLAYER_GPS_TEXT_LETTERY);
		PlayerTextDrawTextSize(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 58.000000, 0.000000);
		PlayerTextDrawAlignment(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 3);
		PlayerTextDrawColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], -1);
		PlayerTextDrawSetShadow(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 0);
		PlayerTextDrawBackgroundColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 255);
		PlayerTextDrawFont(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 1);
		PlayerTextDrawSetProportional(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 1);
		PlayerTextDrawTextSize(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], text_pos_x + PLAYER_GPS_TEXT_MAX_SIZE, 9.0);
		PlayerTextDrawSetSelectable(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], true);
		SetPlayerTextDrawLayer(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], LAYER_GPS);
		
		if(i == _:GPS_OPTION_CANCEL_ROUTE) offset_y += 22.0; //34.0
		else
		{
			GPS_Options_PTD[playerid][td_count][gps_option_ICON] = CreatePlayerTextDraw(playerid, text_pos_x - PLAYER_GPS_TEXT_MAX_SIZE - PLAYER_GPS_ICON_PADDING - PLAYER_GPS_ICON_SIZE, PLAYER_GPS_TD_Y + offset_y + 3.0, GetGpsOptionIcon(td_count));
			PlayerTextDrawTextSize(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], PLAYER_GPS_ICON_SIZE, PLAYER_GPS_ICON_SIZE);
			PlayerTextDrawAlignment(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], 1);
			if(i == _:GPS_OPTION_CATEGORY_OBJECTIVES) PlayerTextDrawColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], GetPlayerObjectiveColor(playerid));
			else PlayerTextDrawColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], -1);
			PlayerTextDrawSetShadow(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], 0);
			PlayerTextDrawBackgroundColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], 255);
			PlayerTextDrawFont(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], 4);
			PlayerTextDrawSetProportional(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], 0);
			SetPlayerTextDrawLayer(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], LAYER_GPS);
		
			GPS_Options_PTD[playerid][td_count][gps_option_TICK] = CreatePlayerTextDraw(playerid, text_pos_x - PLAYER_GPS_TEXT_MAX_SIZE - (PLAYER_GPS_ICON_PADDING * 2.0) - (PLAYER_GPS_ICON_SIZE * 2.0), PLAYER_GPS_TD_Y + offset_y + 3.0, ""TEXTDRAW_CUSTOM_PATH"tick_no");
			PlayerTextDrawTextSize(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], PLAYER_GPS_ICON_SIZE, PLAYER_GPS_ICON_SIZE);
			PlayerTextDrawAlignment(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], 1);
			PlayerTextDrawColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], -1);
			PlayerTextDrawSetShadow(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], 0);
			PlayerTextDrawBackgroundColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], 255);
			PlayerTextDrawFont(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], 4);
			PlayerTextDrawSetProportional(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], 0);	
			SetPlayerTextDrawLayer(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], LAYER_GPS);
		}	
		offset_y += PLAYER_GPS_OPTION_OFFSETY;
		td_count ++;
	}

	//categories
	foreach(new i : GPS_Cat)
	{
		new str[24];
		format(str, sizeof str, "Category %d", i);
		new Float:letterx = 0.2;//GetTdTextFontX(1, str, true, 0.0, PLAYER_GPS_TEXT_MAX_SIZE);

		GPS_Options_PTD[playerid][td_count][gps_option_TEXT] = CreatePlayerTextDraw(playerid, text_pos_x, PLAYER_GPS_TD_Y + offset_y, str);
		PlayerTextDrawLetterSize(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], letterx, PLAYER_GPS_TEXT_LETTERY);
		PlayerTextDrawTextSize(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 58.000000, 0.000000);
		PlayerTextDrawAlignment(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 3);
		PlayerTextDrawColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], -1);
		PlayerTextDrawSetShadow(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 0);
		PlayerTextDrawBackgroundColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 255);
		PlayerTextDrawFont(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 1);
		PlayerTextDrawSetProportional(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], 1);
		PlayerTextDrawTextSize(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], text_pos_x + PLAYER_GPS_TEXT_MAX_SIZE, 9.0);
		PlayerTextDrawSetSelectable(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], true);
		SetPlayerTextDrawLayer(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], LAYER_GPS);

		GPS_Options_PTD[playerid][td_count][gps_option_ICON] = CreatePlayerTextDraw(playerid, text_pos_x - PLAYER_GPS_TEXT_MAX_SIZE - PLAYER_GPS_ICON_PADDING - PLAYER_GPS_ICON_SIZE, PLAYER_GPS_TD_Y + offset_y + 3.0, GPS_Cat[i][gps_cat_ICON]);
		PlayerTextDrawTextSize(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], PLAYER_GPS_ICON_SIZE, PLAYER_GPS_ICON_SIZE);
		PlayerTextDrawAlignment(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], 1);
		PlayerTextDrawColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], -1);
		PlayerTextDrawSetShadow(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], 0);
		PlayerTextDrawBackgroundColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], 255);
		PlayerTextDrawFont(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], 4);
		PlayerTextDrawSetProportional(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], 0);
		SetPlayerTextDrawLayer(playerid, GPS_Options_PTD[playerid][td_count][gps_option_ICON], LAYER_GPS);
	
		GPS_Options_PTD[playerid][td_count][gps_option_TICK] = CreatePlayerTextDraw(playerid, text_pos_x - PLAYER_GPS_TEXT_MAX_SIZE - (PLAYER_GPS_ICON_PADDING * 2.0) - (PLAYER_GPS_ICON_SIZE * 2.0), PLAYER_GPS_TD_Y + offset_y + 3.0, ""TEXTDRAW_CUSTOM_PATH"tick_no");
		PlayerTextDrawTextSize(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], PLAYER_GPS_ICON_SIZE, PLAYER_GPS_ICON_SIZE);
		PlayerTextDrawAlignment(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], 1);
		PlayerTextDrawColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], -1);
		PlayerTextDrawSetShadow(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], 0);
		PlayerTextDrawBackgroundColor(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], 255);
		PlayerTextDrawFont(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], 4);
		PlayerTextDrawSetProportional(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], 0);	
		SetPlayerTextDrawLayer(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], LAYER_GPS);
		
		offset_y += PLAYER_GPS_OPTION_OFFSETY;
		td_count ++;
	}
	return 1;
}

GetGpsOptionIcon(option)
{
	new icon[32];
	switch(option)
	{
		case GPS_OPTION_MINIMAP: icon = "hud:radar_north";
		case GPS_OPTION_LOCATION: icon = "hud:arrow";
		case GPS_OPTION_ROUTE: icon = "hud:radar_waypoint";
		case GPS_OPTION_CATEGORY_OBJECTIVES: icon = ""TEXTDRAW_CUSTOM_PATH"icon_pos";
		case GPS_OPTION_CATEGORY_PROPERTIES: icon = "hud:radar_propertyg";
		case GPS_OPTION_CATEGORY_BUSINESS: icon = ""TEXTDRAW_CUSTOM_PATH"radar_propertyb";
		case GPS_OPTION_CATEGORY_VEHICLES: icon = ""TEXTDRAW_CUSTOM_PATH"icon_car";
	}
	return icon;
}

UpdatePlayerGpsTicks(playerid)
{
	if(PI[playerid][pi_GPS_MINIMAP]) PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_MINIMAP][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
	else PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_MINIMAP][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_no");
	if(PI[playerid][pi_GPS_LOCATION]) PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_LOCATION][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
	else PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_LOCATION][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_no");
	if(PI[playerid][pi_GPS_ROUTE]) PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_ROUTE][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
	else PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_ROUTE][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_no");
	if(PI[playerid][pi_GPS_OBJECTIVES]) PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_OBJECTIVES][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
	else PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_OBJECTIVES][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_no");
	if(PI[playerid][pi_GPS_PROPERTIES]) PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_PROPERTIES][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
	else PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_PROPERTIES][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_no");
	if(PI[playerid][pi_GPS_BUSINESS]) PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_BUSINESS][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
	else PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_BUSINESS][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_no");
	if(PI[playerid][pi_GPS_VEHICLES]) PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_VEHICLES][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
	else PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_VEHICLES][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_no");

	new td_count = _:GPS_OPTION_CATEGORY_DB;
	foreach(new i : GPS_Cat)
	{
		if(Player_Gps_Cats[playerid][i]) PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
		else PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TICK], ""TEXTDRAW_CUSTOM_PATH"tick_no");
		td_count ++;
	}
	return 1;
}

ShowPlayerGpsTextdraws(playerid)
{
	for(new i = 0; i < sizeof GPS_Body_PTD[]; i ++)
	{
		if(GPS_Body_PTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, GPS_Body_PTD[playerid][i]);
	}
	for(new i = 0; i < sizeof GPS_Options_PTD[]; i ++)
	{
		if(GPS_Options_PTD[playerid][i][gps_option_ICON] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, GPS_Options_PTD[playerid][i][gps_option_ICON]);
		if(GPS_Options_PTD[playerid][i][gps_option_TICK] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, GPS_Options_PTD[playerid][i][gps_option_TICK]);
		if(GPS_Options_PTD[playerid][i][gps_option_TEXT] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, GPS_Options_PTD[playerid][i][gps_option_TEXT]);
	}
	ShowVcPTdMapForPlayer(playerid, GPS_MapID[playerid]);
	return 1;
}

ShowPlayerGps(playerid, autopilotveh = INVALID_VEHICLE_ID)
{
	CreateGpsMap(playerid);
	CreatePlayerGpsTextdraws(playerid);
	FormatPlayerGpsTextdraws(playerid);
	UpdatePlayerGpsTicks(playerid);
	ShowPlayerGpsTextdraws(playerid);
	
	SelectTextDraw(playerid, 0xFFFFFFFF);//0xFFCCFFFF);
	pGps[playerid] = true;
	pGpsAutopilotVehicle[playerid] = autopilotveh;

	//quitar minimapa
	DisablePlayerLayers(playerid, LAYER_GPS);
	if(IsPlayerInRoute(playerid)) HidePlayerRoute(playerid, true);
	CallRemoteFunction("OnPlayerOpenGps", "i", playerid);
	return 1;
}

HidePlayerGps(playerid)
{
	pGps[playerid] = false;
	DestroyPlayerGpsTextdraws(playerid);
	UpdatePlayerGpsCats(playerid);

	EnablePlayerLayers(playerid);
	if(IsPlayerInRoute(playerid)) ShowPlayerRoute(playerid);
	CallRemoteFunction("OnPlayerRequestAnimEnvStop", "i", playerid);
	CallRemoteFunction("OnPlayerCloseGps", "i", playerid);
	return 1;
}

LoadPlayerGpsCats(playerid)
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_GPS_CATEGORIES)
				{
					printf("[ERROR]: Límite rebasado en Player_Gps_Cats en LoadPlayerGpsCats (pid: %d)", PI[playerid][pi_ID]);
					break;
				}
				new id_cat, cat_index;
				cache_get_value_name_int(i, "id_cat", id_cat);
				cat_index = GetGpsCatIndexById(id_cat);
				if(cat_index != -1) cache_get_value_name_int(i, "enabled", Player_Gps_Cats[playerid][cat_index]);
			}
		}
	}
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM player_gps_cats WHERE id_player = %d;", PI[playerid][pi_ID]);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	return 1;
}

UpdatePlayerGpsCats(playerid)
{
	foreach(new i : GPS_Cat)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_gps_cats VALUES (%d, %d, %d) ON DUPLICATE KEY UPDATE enabled = %d;", PI[playerid][pi_ID], GPS_Cat[i][gps_cat_ID], Player_Gps_Cats[playerid][i], Player_Gps_Cats[playerid][i]);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}
	return 1;
}

RecreateGpsMap(playerid, bool:show = true)
{
	if(GPS_MapID[playerid] != INVALID_VC_TDMAP_ID)
	{
		DestroyVcPTdMap(playerid, GPS_MapID[playerid]);
		GPS_MapID[playerid] = INVALID_VC_TDMAP_ID;
	}

	CreateGpsMap(playerid);
	if(show) ShowVcPTdMapForPlayer(playerid, GPS_MapID[playerid]);
	return 1;
}

CreateGpsMap(playerid)
{
	new Float:result_x, Float:result_size_x, Float:result_mapsize_x, Float:result_paddingsize;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, PLAYER_GPS_MAP_SIZE_X, false, result_x, result_mapsize_x);
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, PLAYER_GPS_MAP_PADDING, false, result_x, result_paddingsize);
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], PLAYER_GPS_TD_X, PLAYER_GPS_TD_SIZE_X, true, result_x, result_size_x);
	GPS_MapID[playerid] = CreateVcPTdMap(playerid, result_x + result_paddingsize, PLAYER_GPS_TD_Y + result_paddingsize, result_mapsize_x - (result_paddingsize * 2.0), PLAYER_GPS_TD_SIZE_Y - (result_paddingsize * 2.0));
	SetPlayerTextDrawLayer(playerid, Vc_PTdMaps[playerid][ GPS_MapID[playerid] ][vc_ptdmap_TD], LAYER_GPS);

	//cats
	foreach(new i : GPS_Cat)
	{
		if(Player_Gps_Cats[playerid][i])
		{
			foreach(new j : GPS_Sites[i])
			{
				new icon[32];
				if(isnull(GPS_Sites[i][j][gps_site_ICON])) format(icon, 32, "%s", GPS_Cat[i][gps_cat_ICON]);
				else format(icon, 32, "%s", GPS_Sites[i][j][gps_site_ICON]);
				new point_index = AddPointToVcPTdMap(playerid, GPS_MapID[playerid], icon, GPS_Sites[i][j][gps_site_X], GPS_Sites[i][j][gps_site_Y], GPS_Sites[i][j][gps_site_Z], pIconMapSize[playerid], PLAYER_GPS_ICON_MAP_SIZE, "Taxi", .description_selectable = true, .description_ls_x = 0.149333 * 1.5, .description_ls_y = 0.766222 * 1.5, .selectable = true);
				SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD], LAYER_GPS);
				SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD_DESCRIPTION], LAYER_GPS);
			}
		}
	}

	//properties
	if(PI[playerid][pi_GPS_PROPERTIES])
	{
		foreach(new i : PlayerProperties<playerid>)
		{
			if(Iter_Contains(PropertyDoor[i], 0))
			{
				new point_index = AddPointToVcPTdMap(playerid, GPS_MapID[playerid], "hud:radar_propertyg", PropertyDoor[i][0][prop_door_EXT_X], PropertyDoor[i][0][prop_door_EXT_Y], PropertyDoor[i][0][prop_door_EXT_Z], pIconMapSize[playerid], PLAYER_GPS_ICON_MAP_SIZE, .selectable = true);
				SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD], LAYER_GPS);
				SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD_DESCRIPTION], LAYER_GPS);
			}
		}
	}

	//business
	if(PI[playerid][pi_GPS_BUSINESS])
	{
		foreach(new i : PlayerBusiness<playerid>)
		{
			if(Iter_Contains(BusinessDoors[i], 0))
			{
				new point_index = AddPointToVcPTdMap(playerid, GPS_MapID[playerid], ""TEXTDRAW_CUSTOM_PATH"radar_propertyb", BusinessDoors[i][0][bdoor_EXT_X], BusinessDoors[i][0][bdoor_EXT_Y], BusinessDoors[i][0][bdoor_EXT_Z], pIconMapSize[playerid], PLAYER_GPS_ICON_MAP_SIZE, .selectable = true);
				SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD], LAYER_GPS);
				SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD_DESCRIPTION], LAYER_GPS);
			}
		}
	}

	//ruta
	if(IsPlayerInRoute(playerid) && PI[playerid][pi_GPS_ROUTE])
	{
		new cp, last_cp = Iter_Last(RouteCps[playerid]);
		if(GetPlayerRouteCP(playerid) == -1) cp = Iter_First(RouteCps[playerid]);
		else cp = Iter_Next(RouteCps[playerid], GetPlayerRouteCP(playerid));
		for(new i = cp; i < last_cp; i = Iter_Next(RouteCps[playerid], i))
		{
			new point_index = AddPointToVcPTdMap(playerid, GPS_MapID[playerid], GetRouteIconNameByAngle(RouteCps[playerid][i][routecp_ANGLE]), RouteCps[playerid][i][routecp_X], RouteCps[playerid][i][routecp_Y], RouteCps[playerid][i][routecp_Z], pIconMapSize[playerid] * 0.7, PLAYER_GPS_ICON_MAP_SIZE * 0.7);
			SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD], LAYER_GPS);
			SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD_DESCRIPTION], LAYER_GPS);
		}
		new point_index = AddPointToVcPTdMap(playerid, GPS_MapID[playerid], "hud:radar_flag", RouteCps[playerid][last_cp][routecp_X], RouteCps[playerid][last_cp][routecp_Y], RouteCps[playerid][last_cp][routecp_Z], pIconMapSize[playerid], PLAYER_GPS_ICON_MAP_SIZE);
		SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD], LAYER_GPS);
		SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD_DESCRIPTION], LAYER_GPS);
	}
	
	//vehicles
	if(PI[playerid][pi_GPS_VEHICLES])
	{
		foreach(new i : PlayerVehicles[playerid])
		{
			if(VehicleInfo[i][vinfo_VEHICLE_ID] != INVALID_VEHICLE_ID && GetPlayerVehicleID(playerid) != VehicleInfo[i][vinfo_VEHICLE_ID])
			{
				if(VehicleInfo[i][vinfo_TYPE] == VEHICLE_TYPE_JOB && pLastVehicleIndex[playerid] != i)
				continue;
				
				new Float:pos[3];
				GetVehiclePos(VehicleInfo[i][vinfo_VEHICLE_ID], pos[0], pos[1], pos[2]);
				new point_index = AddPointToVcPTdMap(playerid, GPS_MapID[playerid], GetVehicleModelIcon(VehicleInfo[i][vinfo_MODELID]), pos[0], pos[1], pos[2], pIconMapSize[playerid], PLAYER_GPS_ICON_MAP_SIZE, .selectable = true, .color = GetPlayerVehicleIconColor(playerid, i));
				SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD], LAYER_GPS);
				SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD_DESCRIPTION], LAYER_GPS);
			}
		}
	}

	//objetivos
	if(PI[playerid][pi_GPS_OBJECTIVES])
	{
		switch(GetPlayerJobId(playerid))
		{
			case JOB_TAXI:
			{
				foreach(new i : Player)
				{
					if(pTaxiRequested[i])
					{
						new Float:pos[3], Float:angle, interiorid, worldid;
						GetPlayerExteriorPos(i, pos[0], pos[1], pos[2], angle, interiorid, worldid, .radar = true);
						new point_index = AddPointToVcPTdMap(playerid, GPS_MapID[playerid], ""TEXTDRAW_CUSTOM_PATH"icon_pos", pos[0], pos[1], pos[2], pIconMapSize[playerid] / 2.0, PLAYER_GPS_ICON_MAP_SIZE / 2.0, .selectable = true, .color = GetPlayerObjectiveColor(playerid));
						SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD], LAYER_GPS);
						SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD_DESCRIPTION], LAYER_GPS);
					}
				}
			}
		}
	}

	//location
	if(PI[playerid][pi_GPS_LOCATION])
	{
		new Float:xangle, Float:pos[3], Float:angle, interiorid, worldid;
		GetPlayerExteriorPos(playerid, pos[0], pos[1], pos[2], angle, interiorid, worldid, .radar = true);
		if(IsPlayerInAnyVehicle(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), xangle);
		else GetPlayerFacingAngle(playerid, xangle);
		new point_index = AddPointToVcPTdMap(playerid, GPS_MapID[playerid], GetIconNameByAngle(xangle), pos[0], pos[1], pos[2], pIconMapSize[playerid], PLAYER_GPS_ICON_MAP_SIZE);
		SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD], LAYER_GPS);
		SetPlayerTextDrawLayer(playerid, Vc_PTdMaps_Points[playerid][ GPS_MapID[playerid] ][point_index][vc_ptdmap_point_TD_DESCRIPTION], LAYER_GPS);
	}
	return 1;
}

GetRouteIconNameByAngle(Float:angle)
{
	new icon[32], compass = GetCompassByAngle(angle);
	switch(compass)
	{
		case 0: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"route_n");
		case 1: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"route_nw");
		case 2: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"route_w");
		case 3: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"route_sw");
		case 4: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"route_s");
		case 5: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"route_se");
		case 6: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"route_e");
		case 7: format(icon, sizeof icon, ""TEXTDRAW_CUSTOM_PATH"route_ne");
		default: format(icon, sizeof icon, "hud:radar_light");
	}
	return icon;
}

FormatPlayerGpsTextdraws(playerid)
{
	new str[64], Float:letterx;
	//GPS_OPTION_MINIMAP
	Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $GPS_OPTION_MINIMAP);
	letterx = GetTdTextFontX(1, str, true, 0.0, PLAYER_GPS_TEXT_MAX_SIZE);
	PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_MINIMAP][gps_option_TEXT], str);
	PlayerTextDrawLetterSize(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_MINIMAP][gps_option_TEXT], letterx, PLAYER_GPS_TEXT_LETTERY);

	//GPS_OPTION_LOCATION
	Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $GPS_OPTION_LOCATION);
	letterx = GetTdTextFontX(1, str, true, 0.0, PLAYER_GPS_TEXT_MAX_SIZE);
	PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_LOCATION][gps_option_TEXT], str);
	PlayerTextDrawLetterSize(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_LOCATION][gps_option_TEXT], letterx, PLAYER_GPS_TEXT_LETTERY);

	//GPS_OPTION_ROUTE
	Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $GPS_OPTION_ROUTE);
	letterx = GetTdTextFontX(1, str, true, 0.0, PLAYER_GPS_TEXT_MAX_SIZE);
	PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_ROUTE][gps_option_TEXT], str);
	PlayerTextDrawLetterSize(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_ROUTE][gps_option_TEXT], letterx, PLAYER_GPS_TEXT_LETTERY);

	if(GPS_Options_PTD[playerid][_:GPS_OPTION_CANCEL_ROUTE][gps_option_TEXT] != PlayerText:INVALID_TEXT_DRAW)
	{
		//GPS_OPTION_CANCEL_ROUTE
		Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $GPS_OPTION_CANCEL_ROUTE);
		letterx = GetTdTextFontX(1, str, true, 0.0, PLAYER_GPS_TEXT_MAX_SIZE);
		PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CANCEL_ROUTE][gps_option_TEXT], str);
		PlayerTextDrawLetterSize(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CANCEL_ROUTE][gps_option_TEXT], letterx, PLAYER_GPS_TEXT_LETTERY);
	}

	//GPS_OPTION_CATEGORY_OBJECTIVES
	Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $GPS_OPTION_CATEGORY_OBJECTIVES);
	letterx = GetTdTextFontX(1, str, true, 0.0, PLAYER_GPS_TEXT_MAX_SIZE);
	PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_OBJECTIVES][gps_option_TEXT], str);
	PlayerTextDrawLetterSize(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_OBJECTIVES][gps_option_TEXT], letterx, PLAYER_GPS_TEXT_LETTERY);

	//GPS_OPTION_CATEGORY_PROPERTIES
	Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $GPS_OPTION_CATEGORY_PROPERTIES);
	letterx = GetTdTextFontX(1, str, true, 0.0, PLAYER_GPS_TEXT_MAX_SIZE);
	PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_PROPERTIES][gps_option_TEXT], str);
	PlayerTextDrawLetterSize(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_PROPERTIES][gps_option_TEXT], letterx, PLAYER_GPS_TEXT_LETTERY);

	//GPS_OPTION_CATEGORY_BUSINESS
	Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $GPS_OPTION_CATEGORY_BUSINESS);
	letterx = GetTdTextFontX(1, str, true, 0.0, PLAYER_GPS_TEXT_MAX_SIZE);
	PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_BUSINESS][gps_option_TEXT], str);
	PlayerTextDrawLetterSize(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_BUSINESS][gps_option_TEXT], letterx, PLAYER_GPS_TEXT_LETTERY);

	//GPS_OPTION_CATEGORY_VEHICLES
	Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $GPS_OPTION_CATEGORY_VEHICLES);
	letterx = GetTdTextFontX(1, str, true, 0.0, PLAYER_GPS_TEXT_MAX_SIZE);
	PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_VEHICLES][gps_option_TEXT], str);
	PlayerTextDrawLetterSize(playerid, GPS_Options_PTD[playerid][_:GPS_OPTION_CATEGORY_VEHICLES][gps_option_TEXT], letterx, PLAYER_GPS_TEXT_LETTERY);

	//categorias
	new td_count = _:GPS_OPTION_CATEGORY_DB;
	foreach(new i : GPS_Cat)
	{
		format(str, sizeof str, "%s", GetCategoryNameForPlayer(playerid, GPS_Cat[i][gps_cat_ID]));
		if(isnull(str)) format(str, sizeof str, "%s", GPS_Cat[i][gps_cat_NAME]);
		letterx = GetTdTextFontX(1, str, true, 0.0, PLAYER_GPS_TEXT_MAX_SIZE);
		PlayerTextDrawSetString(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], str);
		PlayerTextDrawLetterSize(playerid, GPS_Options_PTD[playerid][td_count][gps_option_TEXT], letterx, PLAYER_GPS_TEXT_LETTERY);
		td_count ++;
	}
	return 1;
}

GetCategoryNameForPlayer(playerid, catid)
{
	new name[64];
	switch(catid)
	{
		case GPS_CAT_HOSPITAL: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $GPS_CAT_HOSPITAL);
		case GPS_CAT_BANK: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $GPS_CAT_BANK);
		case GPS_CAT_POLICE: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $GPS_CAT_POLICE);
		case GPS_CAT_MECHANIC: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $GPS_CAT_MECHANIC);
		case GPS_CAT_DRIVING_SCHOOL: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $GPS_CAT_DRIVING_SCHOOL);
		case GPS_CAT_JOBS: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $GPS_CAT_JOBS);
		case GPS_CAT_REAL_ESTATES: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $GPS_CAT_REAL_ESTATES);
		case GPS_CAT_BUSINESS: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $GPS_CAT_BUSINESS);
	}
	return name;
}