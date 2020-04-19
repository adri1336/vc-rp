DestroyPlayerLoadScreen(playerid, bool:call = true)
{
	if(loadscreen_timer[playerid] != Timer:-1)
	{
		stop loadscreen_timer[playerid];
		loadscreen_timer[playerid] = Timer:-1;
	}
	if(PTD_Load_Screen[playerid][0] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_Load_Screen[playerid][0]);
		PTD_Load_Screen[playerid][0] = PlayerText:INVALID_TEXT_DRAW;
	}

	if(PTD_Load_Screen[playerid][1] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_Load_Screen[playerid][1]);
		PTD_Load_Screen[playerid][1] = PlayerText:INVALID_TEXT_DRAW;
	}
	EnablePlayerLayers(playerid);
	if(call) CallRemoteFunction("OnPlayerLoadScreenFin", "i", playerid);
	return 1;
}

LoadScreen(playerid, screen = -1)
{	
	DestroyPlayerLoadScreen(playerid, false);

	if(screen == -1) screen = random(sizeof LoadScreens);

	new td_str[45];
	format(td_str, sizeof td_str, ""TEXTDRAW_CUSTOM_PATH"%s", LoadScreens[screen][loadscreen_NAME]);
	PTD_Load_Screen[playerid][0] = CreatePlayerTextDraw(playerid, -1.000000, -1.000000, td_str);
	PlayerTextDrawTextSize(playerid, PTD_Load_Screen[playerid][0], 641.000000, 450.000000);
	PlayerTextDrawFont(playerid, PTD_Load_Screen[playerid][0], 4);
	SetPlayerTextDrawLayer(playerid, PTD_Load_Screen[playerid][0], LAYER_LOADSCREEN);

	new Float:result_x, Float:result_size_x, Float:logo_size_y = LoadScreens[screen][loadscreen_LOGO_SIZE] * (LOGO_ORIGINAL_SIZE_Y / LOGO_ORIGINAL_SIZE_X);
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], LoadScreens[screen][loadscreen_LOGO_X], LoadScreens[screen][loadscreen_LOGO_SIZE], true, result_x, result_size_x);
	PTD_Load_Screen[playerid][1] = CreatePlayerTextDraw(playerid, result_x, LoadScreens[screen][loadscreen_LOGO_Y], ""TEXTDRAW_CUSTOM_PATH"logo");
	PlayerTextDrawTextSize(playerid, PTD_Load_Screen[playerid][1], result_size_x, logo_size_y);
	PlayerTextDrawFont(playerid, PTD_Load_Screen[playerid][1], 4);
	SetPlayerTextDrawLayer(playerid, PTD_Load_Screen[playerid][1], LAYER_LOADSCREEN);

	PlayerTextDrawShow(playerid, PTD_Load_Screen[playerid][0]);
	PlayerTextDrawShow(playerid, PTD_Load_Screen[playerid][1]);
	DisablePlayerLayers(playerid, LAYER_LOADSCREEN);
	TogglePlayerControllable(playerid, false);
	CallRemoteFunction("OnPlayerLoadScreenStart", "i", playerid);
	return 1;
}

LoadScreenTimed(playerid, time = 2000, screen = -1)
{
	DestroyPlayerLoadScreen(playerid, false);

	if(screen == -1) screen = random(sizeof(LoadScreens));

	new td_str[45];
	format(td_str, sizeof td_str, ""TEXTDRAW_CUSTOM_PATH"%s", LoadScreens[screen][loadscreen_NAME]);
	PTD_Load_Screen[playerid][0] = CreatePlayerTextDraw(playerid, -1.000000, -1.000000, td_str);
	PlayerTextDrawTextSize(playerid, PTD_Load_Screen[playerid][0], 641.000000, 450.000000);
	PlayerTextDrawFont(playerid, PTD_Load_Screen[playerid][0], 4);
	SetPlayerTextDrawLayer(playerid, PTD_Load_Screen[playerid][0], LAYER_LOADSCREEN);

	new Float:result_x, Float:result_size_x, Float:logo_size_y = LoadScreens[screen][loadscreen_LOGO_SIZE] * (LOGO_ORIGINAL_SIZE_Y / LOGO_ORIGINAL_SIZE_X);
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], LoadScreens[screen][loadscreen_LOGO_X], LoadScreens[screen][loadscreen_LOGO_SIZE], true, result_x, result_size_x);
	PTD_Load_Screen[playerid][1] = CreatePlayerTextDraw(playerid, result_x, LoadScreens[screen][loadscreen_LOGO_Y], ""TEXTDRAW_CUSTOM_PATH"logo");
	PlayerTextDrawTextSize(playerid, PTD_Load_Screen[playerid][1], result_size_x, logo_size_y);
	PlayerTextDrawFont(playerid, PTD_Load_Screen[playerid][1], 4);
	SetPlayerTextDrawLayer(playerid, PTD_Load_Screen[playerid][1], LAYER_LOADSCREEN);

	PlayerTextDrawShow(playerid, PTD_Load_Screen[playerid][0]);
	PlayerTextDrawShow(playerid, PTD_Load_Screen[playerid][1]);
	DisablePlayerLayers(playerid, LAYER_LOADSCREEN);
	TogglePlayerControllable(playerid, false);
	loadscreen_timer[playerid] = defer OnLoadScreenFinish[time](playerid);
	CallRemoteFunction("OnPlayerLoadScreenStart", "i", playerid);
	return 1;
}