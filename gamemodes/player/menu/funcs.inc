loadtext lang[menu];

CreateMenuPTextdraws(playerid)
{
	// 448 / 2 = 224
	new Float:menu_posy = (224.0 + 25.0) - (2.757703 / 0.2);
	Menu_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 320.000000, menu_posy, "l");
	PlayerTextDrawLetterSize(playerid, Menu_PTD[playerid][0], 41.805324, 2.757703);
	PlayerTextDrawAlignment(playerid, Menu_PTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, Menu_PTD[playerid][0], 170);
	PlayerTextDrawSetShadow(playerid, Menu_PTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, Menu_PTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, Menu_PTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, Menu_PTD[playerid][0], 1);

	new Float:menu_options_posy = menu_posy + (2.757703 / 0.2) - (1.226665 / 0.2);
	Menu_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 230.000000, menu_options_posy, "play");
	PlayerTextDrawLetterSize(playerid, Menu_PTD[playerid][1], 0.218666, 1.226665);
	PlayerTextDrawTextSize(playerid, Menu_PTD[playerid][1], 10.0, 50.0);
	PlayerTextDrawAlignment(playerid, Menu_PTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, Menu_PTD[playerid][1], -3276801);
	PlayerTextDrawSetShadow(playerid, Menu_PTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, Menu_PTD[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, Menu_PTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, Menu_PTD[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, Menu_PTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, Menu_PTD[playerid][1], true);

	Menu_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 290.000000, menu_options_posy, "info");
	PlayerTextDrawLetterSize(playerid, Menu_PTD[playerid][2], 0.218666, 1.226665);
	PlayerTextDrawTextSize(playerid, Menu_PTD[playerid][2], 10.0, 50.0);
	PlayerTextDrawAlignment(playerid, Menu_PTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, Menu_PTD[playerid][2], -3276801);
	PlayerTextDrawSetShadow(playerid, Menu_PTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, Menu_PTD[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, Menu_PTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, Menu_PTD[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, Menu_PTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, Menu_PTD[playerid][2], true);

	Menu_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 350.000000, menu_options_posy, "settings");
	PlayerTextDrawLetterSize(playerid, Menu_PTD[playerid][3], 0.218666, 1.226665);
	PlayerTextDrawTextSize(playerid, Menu_PTD[playerid][3], 10.0, 50.0);
	PlayerTextDrawAlignment(playerid, Menu_PTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, Menu_PTD[playerid][3], -3276801);
	PlayerTextDrawSetShadow(playerid, Menu_PTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, Menu_PTD[playerid][3], 1);
	PlayerTextDrawBackgroundColor(playerid, Menu_PTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, Menu_PTD[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, Menu_PTD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, Menu_PTD[playerid][3], true);

	Menu_PTD[playerid][4] = CreatePlayerTextDraw(playerid, 410.000000, menu_options_posy, "exit");
	PlayerTextDrawLetterSize(playerid, Menu_PTD[playerid][4], 0.218666, 1.226665);
	PlayerTextDrawTextSize(playerid, Menu_PTD[playerid][4], 10.0, 50.0);
	PlayerTextDrawAlignment(playerid, Menu_PTD[playerid][4], 2);
	PlayerTextDrawColor(playerid, Menu_PTD[playerid][4], -3276801);
	PlayerTextDrawSetShadow(playerid, Menu_PTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, Menu_PTD[playerid][4], 1);
	PlayerTextDrawBackgroundColor(playerid, Menu_PTD[playerid][4], 255);
	PlayerTextDrawFont(playerid, Menu_PTD[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, Menu_PTD[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, Menu_PTD[playerid][4], true);

	new Float:logo_size_y = MENU_LOGO_SIZE * (1392.0 / 2001.0), Float:result_x, Float:result_size_x;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 320.0, MENU_LOGO_SIZE, true, result_x, result_size_x);
	Menu_PTD[playerid][5] = CreatePlayerTextDraw(playerid, result_x, menu_posy - MENU_PADDING - logo_size_y, ""TEXTDRAW_CUSTOM_PATH"logo");
	PlayerTextDrawTextSize(playerid, Menu_PTD[playerid][5], result_size_x, logo_size_y);
	PlayerTextDrawAlignment(playerid, Menu_PTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, Menu_PTD[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, Menu_PTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, Menu_PTD[playerid][5], 255);
	PlayerTextDrawFont(playerid, Menu_PTD[playerid][5], 4);
	PlayerTextDrawSetProportional(playerid, Menu_PTD[playerid][5], 0);
	return 1;
}

DestroyMenuPTextdraws(playerid)
{
	for(new i, j = sizeof Menu_PTD[]; i != j; i ++)
	{
		if(Menu_PTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, Menu_PTD[playerid][i]);
			Menu_PTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

HideMenuPTextdraws(playerid)
{
	for(new i, j = sizeof Menu_PTD[]; i != j; i ++)
	{
		PlayerTextDrawHide(playerid, Menu_PTD[playerid][i]);
	}
	return 1;
}

ShowMenuPTextdraws(playerid)
{
	for(new i, j = sizeof Menu_PTD[]; i != j; i ++)
	{
		PlayerTextDrawShow(playerid, Menu_PTD[playerid][i]);
	}
	return 1;
}

ShowPlayerMenu(playerid)
{
	if(!pInMenu[playerid])
	{
		if(GetPlayerGameState(playerid) != GAME_STATE_SPECTATING)
		{
			switch(GetPlayerGameState(playerid))
			{
				case GAME_STATE_SPAWNED:
				{
					PlayAudioStreamForPlayer(playerid, Intro_Audios[random(sizeof Intro_Audios)]);
					SavePlayerWorldInfo_DB(playerid);
					TogglePlayerSpectating(playerid, true);
					CleanPlayerChat(playerid);

					new camera = random(sizeof Intro_Cameras);
					InterpolateCameraPos(playerid, Intro_Cameras[camera][0], Intro_Cameras[camera][1], Intro_Cameras[camera][2], Intro_Cameras[camera][6], Intro_Cameras[camera][7], Intro_Cameras[camera][8], 10000, CAMERA_MOVE);
					InterpolateCameraLookAt(playerid, Intro_Cameras[camera][3], Intro_Cameras[camera][4], Intro_Cameras[camera][5], Intro_Cameras[camera][9], Intro_Cameras[camera][10], Intro_Cameras[camera][11], 10000, CAMERA_MOVE);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, VC_WORLD);
				}
			}
			SetPlayerGameState(playerid, GAME_STATE_SPECTATING);
		}

		CreateMenuPTextdraws(playerid);
		FormatPlayerMenuTds(playerid);
		ShowMenuPTextdraws(playerid);
		ShowConnectionTdsForPlayer(playerid);
		SelectTextDraw(playerid, 0xFFFFFFFF);

		pInMenu[playerid] = true;
		pSpawnFromMenu[playerid] = true;
		CallRemoteFunction("OnPlayerOpenMenu", "i", playerid);
		return 1;
	}
	return 0;
}

HidePlayerMenu(playerid, bool:spawn = true)
{
	if(pInMenu[playerid])
	{
		DestroyMenuPTextdraws(playerid);
		HideConnectionTdsForPlayer(playerid);

		pInMenu[playerid] = false;
		CancelSelectTextDraw(playerid);

		if(spawn)
		{
			LoadScreen(playerid);
			TogglePlayerSpectating(playerid, false);
		}
		return 1;
	}
	return 0;
}

FormatPlayerMenuTds(playerid)
{
	PlayerTD_Text(playerid, Menu_PTD[playerid][1], $TEXTDRAW_PLAY);
	PlayerTD_Text(playerid, Menu_PTD[playerid][2], $TEXTDRAW_INFO);
	PlayerTD_Text(playerid, Menu_PTD[playerid][3], $TEXTDRAW_SETTINGS);
	PlayerTD_Text(playerid, Menu_PTD[playerid][4], $TEXTDRAW_QUIT);
	return 1;
}