loadtext lang[register];

CreatePlayerRegisterTextdraws(playerid)
{
	new Float:result_x, Float:result_size_x;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 320.0, 294.0, true, result_x, result_size_x);
	PTD_VCRP_REGISTER[playerid][0] = CreatePlayerTextDraw(playerid, result_x, 100.000000, ""TEXTDRAW_CUSTOM_PATH"register");
	PlayerTextDrawTextSize(playerid, PTD_VCRP_REGISTER[playerid][0], result_size_x, 210.000000);
	PlayerTextDrawAlignment(playerid, PTD_VCRP_REGISTER[playerid][0], 1);
	PlayerTextDrawColor(playerid, PTD_VCRP_REGISTER[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, PTD_VCRP_REGISTER[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VCRP_REGISTER[playerid][0], 255);
	PlayerTextDrawFont(playerid, PTD_VCRP_REGISTER[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, PTD_VCRP_REGISTER[playerid][0], 0);

	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 270.0, 100.0, true, result_x, result_size_x);
	PTD_VCRP_REGISTER[playerid][1] = CreatePlayerTextDraw(playerid, result_x, 180.000000, "");
	PlayerTextDrawTextSize(playerid, PTD_VCRP_REGISTER[playerid][1], result_size_x, 100.000000);
	PlayerTextDrawAlignment(playerid, PTD_VCRP_REGISTER[playerid][1], 1);
	PlayerTextDrawColor(playerid, PTD_VCRP_REGISTER[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, PTD_VCRP_REGISTER[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VCRP_REGISTER[playerid][1], 1515870910);
	PlayerTextDrawFont(playerid, PTD_VCRP_REGISTER[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, PTD_VCRP_REGISTER[playerid][1], 0);
	PlayerTextDrawSetPreviewModel(playerid, PTD_VCRP_REGISTER[playerid][1], 0);
	PlayerTextDrawSetPreviewRot(playerid, PTD_VCRP_REGISTER[playerid][1], 0.000000, 0.000000, 0.000000, 1.000000);

	PTD_VCRP_REGISTER[playerid][2] = CreatePlayerTextDraw(playerid, 330.000000, 179.000000, "Gender");
	PlayerTextDrawLetterSize(playerid, PTD_VCRP_REGISTER[playerid][2], 0.248333, 1.442370);
	PlayerTextDrawAlignment(playerid, PTD_VCRP_REGISTER[playerid][2], 1);
	PlayerTextDrawColor(playerid, PTD_VCRP_REGISTER[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, PTD_VCRP_REGISTER[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VCRP_REGISTER[playerid][2], 255);
	PlayerTextDrawFont(playerid, PTD_VCRP_REGISTER[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, PTD_VCRP_REGISTER[playerid][2], 1);

	PTD_VCRP_REGISTER[playerid][3] = CreatePlayerTextDraw(playerid, 372.000000, 195.000000, "Male");
	PlayerTextDrawLetterSize(playerid, PTD_VCRP_REGISTER[playerid][3], 0.282665, 1.330369);
	PlayerTextDrawTextSize(playerid, PTD_VCRP_REGISTER[playerid][3], 10.000000, 81.000000);
	PlayerTextDrawAlignment(playerid, PTD_VCRP_REGISTER[playerid][3], 2);
	PlayerTextDrawColor(playerid, PTD_VCRP_REGISTER[playerid][3], -1);
	PlayerTextDrawUseBox(playerid, PTD_VCRP_REGISTER[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, PTD_VCRP_REGISTER[playerid][3], 1515870910);
	PlayerTextDrawSetShadow(playerid, PTD_VCRP_REGISTER[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VCRP_REGISTER[playerid][3], 255);
	PlayerTextDrawFont(playerid, PTD_VCRP_REGISTER[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, PTD_VCRP_REGISTER[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, PTD_VCRP_REGISTER[playerid][3], true);

	PTD_VCRP_REGISTER[playerid][4] = CreatePlayerTextDraw(playerid, 330.000000, 219.000000, "Character");
	PlayerTextDrawLetterSize(playerid, PTD_VCRP_REGISTER[playerid][4], 0.248333, 1.442370);
	PlayerTextDrawAlignment(playerid, PTD_VCRP_REGISTER[playerid][4], 1);
	PlayerTextDrawColor(playerid, PTD_VCRP_REGISTER[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, PTD_VCRP_REGISTER[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VCRP_REGISTER[playerid][4], 255);
	PlayerTextDrawFont(playerid, PTD_VCRP_REGISTER[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, PTD_VCRP_REGISTER[playerid][4], 1);

	PTD_VCRP_REGISTER[playerid][5] = CreatePlayerTextDraw(playerid, 372.000000, 235.000000, "0/0");
	PlayerTextDrawLetterSize(playerid, PTD_VCRP_REGISTER[playerid][5], 0.282665, 1.330369);
	PlayerTextDrawTextSize(playerid, PTD_VCRP_REGISTER[playerid][5], 10.000000, 81.000000);
	PlayerTextDrawAlignment(playerid, PTD_VCRP_REGISTER[playerid][5], 2);
	PlayerTextDrawColor(playerid, PTD_VCRP_REGISTER[playerid][5], -1);
	PlayerTextDrawUseBox(playerid, PTD_VCRP_REGISTER[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, PTD_VCRP_REGISTER[playerid][5], 1515870910);
	PlayerTextDrawSetShadow(playerid, PTD_VCRP_REGISTER[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VCRP_REGISTER[playerid][5], 255);
	PlayerTextDrawFont(playerid, PTD_VCRP_REGISTER[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, PTD_VCRP_REGISTER[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, PTD_VCRP_REGISTER[playerid][5], true);

	PTD_VCRP_REGISTER[playerid][6] = CreatePlayerTextDraw(playerid, 372.000000, 259.000000, "Let's go!");
	PlayerTextDrawLetterSize(playerid, PTD_VCRP_REGISTER[playerid][6], 0.276333, 1.579259);
	PlayerTextDrawTextSize(playerid, PTD_VCRP_REGISTER[playerid][6], 10.000000, 81.000000);
	PlayerTextDrawAlignment(playerid, PTD_VCRP_REGISTER[playerid][6], 2);
	PlayerTextDrawColor(playerid, PTD_VCRP_REGISTER[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, PTD_VCRP_REGISTER[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VCRP_REGISTER[playerid][6], 255);
	PlayerTextDrawFont(playerid, PTD_VCRP_REGISTER[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, PTD_VCRP_REGISTER[playerid][6], 1);
	PlayerTextDrawSetSelectable(playerid, PTD_VCRP_REGISTER[playerid][6], true);
	return 1;
}

DestroyPlayerRegisterTextdraws(playerid)
{
	for(new i = 0, j = sizeof PTD_VCRP_REGISTER[]; i != j; i ++)
	{
		if(PTD_VCRP_REGISTER[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_VCRP_REGISTER[playerid][i]);
			PTD_VCRP_REGISTER[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

ShowPlayerRegisterTextdraws(playerid)
{
	for(new i = 0, j = sizeof PTD_VCRP_REGISTER[]; i != j; i ++)
	{
		if(PTD_VCRP_REGISTER[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawShow(playerid, PTD_VCRP_REGISTER[playerid][i]);
		}
	}
	return 1;
}

FormatRegisterPlayerTextDraws(playerid, skin, max_skin, PlayerText:ptds[], bool:show = true)
{
	PlayerTextDrawSetPreviewModel(playerid, ptds[1], GetPlayerClothingSkinModel(playerid));
	if(show) PlayerTextDrawShow(playerid, ptds[1]);

	PlayerTD_Text(playerid, ptds[2], $TEXTDRAW_GENDER);
	if(!PI[playerid][pi_GENDER]) { PlayerTD_Text(playerid, ptds[3], $TEXTDRAW_GENDER_MALE); }
	else { PlayerTD_Text(playerid, ptds[3], $TEXTDRAW_GENDER_FEMALE); }
	PlayerTD_Text(playerid, ptds[4], $TEXTDRAW_CHARACTER);
	PlayerTD_Text(playerid, ptds[6], $TEXTDRAW_CONTINUE);

	new td_str[12];
	format(td_str, sizeof td_str, "%d/%d", skin, max_skin);
	PlayerTextDrawSetString(playerid, ptds[5], td_str);
	return 1;
}