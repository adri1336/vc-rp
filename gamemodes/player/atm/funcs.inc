loadtext lang[atm];

CreatePlayerAtmTds(playerid)
{
	new Float:result_x, Float:result_size_x;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 320.0, 373.0, true, result_x, result_size_x);
	PTD_Atm[playerid][0] = CreatePlayerTextDraw(playerid, result_x, 100.000000, ""TEXTDRAW_CUSTOM_PATH"atm");
	PlayerTextDrawTextSize(playerid, PTD_Atm[playerid][0], result_size_x, 260.000000);
	PlayerTextDrawAlignment(playerid, PTD_Atm[playerid][0], 1);
	PlayerTextDrawColor(playerid, PTD_Atm[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Atm[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Atm[playerid][0], 255);
	PlayerTextDrawFont(playerid, PTD_Atm[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, PTD_Atm[playerid][0], 0);
	SetPlayerTextDrawLayer(playerid, PTD_Atm[playerid][0], LAYER_ATM);

	PTD_Atm[playerid][1] = CreatePlayerTextDraw(playerid, 235.000000, 144.000000, "name");
	PlayerTextDrawLetterSize(playerid, PTD_Atm[playerid][1], 0.202999, 0.969481);
	PlayerTextDrawAlignment(playerid, PTD_Atm[playerid][1], 1);
	PlayerTextDrawColor(playerid, PTD_Atm[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Atm[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Atm[playerid][1], 255);
	PlayerTextDrawFont(playerid, PTD_Atm[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Atm[playerid][1], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Atm[playerid][1], LAYER_ATM);

	PTD_Atm[playerid][2] = CreatePlayerTextDraw(playerid, 405.000000, 144.000000, "$0");
	PlayerTextDrawLetterSize(playerid, PTD_Atm[playerid][2], 0.202999, 0.969481);
	PlayerTextDrawAlignment(playerid, PTD_Atm[playerid][2], 3);
	PlayerTextDrawColor(playerid, PTD_Atm[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Atm[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Atm[playerid][2], 255);
	PlayerTextDrawFont(playerid, PTD_Atm[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, PTD_Atm[playerid][2], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Atm[playerid][2], LAYER_ATM);

	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 320.0, 140.0, true, result_x, result_size_x);
	PTD_Atm[playerid][3] = CreatePlayerTextDraw(playerid, result_x, 185.000000, "LD_SPAC:white"); // Retirar
	PlayerTextDrawTextSize(playerid, PTD_Atm[playerid][3], result_size_x, 40.000000);
	PlayerTextDrawAlignment(playerid, PTD_Atm[playerid][3], 1);
	PlayerTextDrawColor(playerid, PTD_Atm[playerid][3], -591370497);
	PlayerTextDrawSetShadow(playerid, PTD_Atm[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Atm[playerid][3], 255);
	PlayerTextDrawFont(playerid, PTD_Atm[playerid][3], 4);
	PlayerTextDrawSetProportional(playerid, PTD_Atm[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, PTD_Atm[playerid][3], true);
	SetPlayerTextDrawLayer(playerid, PTD_Atm[playerid][3], LAYER_ATM);

	PTD_Atm[playerid][4] = CreatePlayerTextDraw(playerid, result_x, 234.000000, "LD_SPAC:white"); //Depositar
	PlayerTextDrawTextSize(playerid, PTD_Atm[playerid][4], result_size_x, 40.000000);
	PlayerTextDrawAlignment(playerid, PTD_Atm[playerid][4], 1);
	PlayerTextDrawColor(playerid, PTD_Atm[playerid][4], -591370497);
	PlayerTextDrawSetShadow(playerid, PTD_Atm[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Atm[playerid][4], 255);
	PlayerTextDrawFont(playerid, PTD_Atm[playerid][4], 4);
	PlayerTextDrawSetProportional(playerid, PTD_Atm[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, PTD_Atm[playerid][4], true);
	SetPlayerTextDrawLayer(playerid, PTD_Atm[playerid][4], LAYER_ATM);

	PTD_Atm[playerid][5] = CreatePlayerTextDraw(playerid, result_x, 283.000000, "LD_SPAC:white"); //Salir
	PlayerTextDrawTextSize(playerid, PTD_Atm[playerid][5], result_size_x, 40.000000);
	PlayerTextDrawAlignment(playerid, PTD_Atm[playerid][5], 1);
	PlayerTextDrawColor(playerid, PTD_Atm[playerid][5], -591370497);
	PlayerTextDrawSetShadow(playerid, PTD_Atm[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Atm[playerid][5], 255);
	PlayerTextDrawFont(playerid, PTD_Atm[playerid][5], 4);
	PlayerTextDrawSetProportional(playerid, PTD_Atm[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, PTD_Atm[playerid][5], true);
	SetPlayerTextDrawLayer(playerid, PTD_Atm[playerid][5], LAYER_ATM);

	PTD_Atm[playerid][6] = CreatePlayerTextDraw(playerid, 320.000000, 195.000000, "text");
	PlayerTextDrawLetterSize(playerid, PTD_Atm[playerid][6], 0.373999, 1.877926);
	PlayerTextDrawAlignment(playerid, PTD_Atm[playerid][6], 2);
	PlayerTextDrawColor(playerid, PTD_Atm[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Atm[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Atm[playerid][6], 255);
	PlayerTextDrawFont(playerid, PTD_Atm[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, PTD_Atm[playerid][6], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Atm[playerid][6], LAYER_ATM);

	PTD_Atm[playerid][7] = CreatePlayerTextDraw(playerid, 320.000000, 244.000000, "text");
	PlayerTextDrawLetterSize(playerid, PTD_Atm[playerid][7], 0.373999, 1.877926);
	PlayerTextDrawAlignment(playerid, PTD_Atm[playerid][7], 2);
	PlayerTextDrawColor(playerid, PTD_Atm[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Atm[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Atm[playerid][7], 255);
	PlayerTextDrawFont(playerid, PTD_Atm[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, PTD_Atm[playerid][7], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Atm[playerid][7], LAYER_ATM);

	PTD_Atm[playerid][8] = CreatePlayerTextDraw(playerid, 320.000000, 292.000000, "text");
	PlayerTextDrawLetterSize(playerid, PTD_Atm[playerid][8], 0.373999, 1.877926);
	PlayerTextDrawAlignment(playerid, PTD_Atm[playerid][8], 2);
	PlayerTextDrawColor(playerid, PTD_Atm[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, PTD_Atm[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_Atm[playerid][8], 255);
	PlayerTextDrawFont(playerid, PTD_Atm[playerid][8], 2);
	PlayerTextDrawSetProportional(playerid, PTD_Atm[playerid][8], 1);
	SetPlayerTextDrawLayer(playerid, PTD_Atm[playerid][8], LAYER_ATM);
	return 1;
}

DestroyPlayerAtmTds(playerid)
{
	for(new i = 0; i != sizeof PTD_Atm[]; i ++)
	{
		if(PTD_Atm[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_Atm[playerid][i]);
			PTD_Atm[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

FormatPlayerAtmTds(playerid)
{
	PlayerTD_Text(playerid, PTD_Atm[playerid][6], $TEXTDRAW_WITHDRAW);
	PlayerTD_Text(playerid, PTD_Atm[playerid][7], $TEXTDRAW_DEPOSIT);
	PlayerTD_Text(playerid, PTD_Atm[playerid][8], $TEXTDRAW_EXIT);
	return 1;
}

ShowPlayerAtm(playerid)
{
	pUsingAtm[playerid] = true;
	CreatePlayerAtmTds(playerid);
	FormatPlayerAtmTds(playerid);
	FormatPlayerAtmInfoTds(playerid);
	for(new i = 0; i != sizeof PTD_Atm[]; i ++)
	{
		if(PTD_Atm[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, PTD_Atm[playerid][i]);
	}

	SelectTextDraw(playerid, 0xb29b52FF);
	DisablePlayerLayers(playerid, LAYER_ATM);
	return 1;
}

HidePlayerAtm(playerid)
{
	pUsingAtm[playerid] = false;
	DestroyPlayerAtmTds(playerid);
	EnablePlayerLayers(playerid);
	return 1;
}

FormatPlayerAtmInfoTds(playerid)
{
	PlayerTextDrawSetString(playerid, PTD_Atm[playerid][1], PI[playerid][pi_NAME]);

	new td_str[24];
	format(td_str, sizeof td_str, "$%d", PI[playerid][pi_BANK_MONEY]);
	PlayerTextDrawSetString(playerid, PTD_Atm[playerid][2], td_str);
	return 1;
}