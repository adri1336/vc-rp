CreateVehFuncsProgressbars(playerid)
{
	new Float:result_x, Float:result_size_x;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 520.0, 10.0, true, result_x, result_size_x);
	PROGRESSBAR_VEHICLE_HEALTH[playerid] = CreatePlayerProgressBar(playerid, result_x, 345.0, result_size_x, 65.0, 180, -1, 2);
	SetPlayerTextDrawLayer(playerid, PlayerProgress_Bar[playerid][ PROGRESSBAR_VEHICLE_HEALTH[playerid] ][playerprogress_bar_BOX], LAYER_SPEEDO);
	SetPlayerTextDrawLayer(playerid, PlayerProgress_Bar[playerid][ PROGRESSBAR_VEHICLE_HEALTH[playerid] ][playerprogress_bar_BAR], LAYER_SPEEDO);

	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 535.0, 10.0, true, result_x, result_size_x);
	PROGRESSBAR_VEHICLE_FUEL[playerid] = CreatePlayerProgressBar(playerid, result_x, 345.0, result_size_x, 65.0, 180, -1, 2);
	SetPlayerTextDrawLayer(playerid, PlayerProgress_Bar[playerid][ PROGRESSBAR_VEHICLE_FUEL[playerid] ][playerprogress_bar_BOX], LAYER_SPEEDO);
	SetPlayerTextDrawLayer(playerid, PlayerProgress_Bar[playerid][ PROGRESSBAR_VEHICLE_FUEL[playerid] ][playerprogress_bar_BAR], LAYER_SPEEDO);
	return 1;
}

DestroyVehFuncsProgressbars(playerid)
{
	if(PROGRESSBAR_VEHICLE_HEALTH[playerid] != INVALID_PROGRESS_BAR_ID)
	{
		DestroyPlayerProgressBar(playerid, PROGRESSBAR_VEHICLE_HEALTH[playerid]);
		PROGRESSBAR_VEHICLE_HEALTH[playerid] = INVALID_PROGRESS_BAR_ID;
	}
	if(PROGRESSBAR_VEHICLE_FUEL[playerid] != INVALID_PROGRESS_BAR_ID)
	{
		DestroyPlayerProgressBar(playerid, PROGRESSBAR_VEHICLE_FUEL[playerid]);
		PROGRESSBAR_VEHICLE_FUEL[playerid] = INVALID_PROGRESS_BAR_ID;
	}
	return 1;
}

CreatePbarsIconsTextdraws(playerid)
{
	new Float:result_x, Float:result_size_x;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 535.0, 10.0, true, result_x, result_size_x);
	PTD_VehiclePbarIcons[playerid][0] = CreatePlayerTextDraw(playerid, result_x, 415.000000, ""TEXTDRAW_CUSTOM_PATH"gas");
	PlayerTextDrawTextSize(playerid, PTD_VehiclePbarIcons[playerid][0], result_size_x, 10.000000);
	PlayerTextDrawAlignment(playerid, PTD_VehiclePbarIcons[playerid][0], 1);
	PlayerTextDrawFont(playerid, PTD_VehiclePbarIcons[playerid][0], 4);
	PlayerTextDrawColor(playerid, PTD_VehiclePbarIcons[playerid][0], -26);
	PlayerTextDrawSetShadow(playerid, PTD_VehiclePbarIcons[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VehiclePbarIcons[playerid][0], 255);
	PlayerTextDrawSetProportional(playerid, PTD_VehiclePbarIcons[playerid][0], 0);
	SetPlayerTextDrawLayer(playerid, PTD_VehiclePbarIcons[playerid][0], LAYER_SPEEDO);

	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 520.0, 10.0, true, result_x, result_size_x);
	PTD_VehiclePbarIcons[playerid][1] = CreatePlayerTextDraw(playerid, result_x, 415.000000, ""TEXTDRAW_CUSTOM_PATH"motor");
	PlayerTextDrawTextSize(playerid, PTD_VehiclePbarIcons[playerid][1], result_size_x, 10.000000);
	PlayerTextDrawAlignment(playerid, PTD_VehiclePbarIcons[playerid][1], 1);
	PlayerTextDrawFont(playerid, PTD_VehiclePbarIcons[playerid][1], 4);
	PlayerTextDrawColor(playerid, PTD_VehiclePbarIcons[playerid][1], -26);
	PlayerTextDrawSetShadow(playerid, PTD_VehiclePbarIcons[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VehiclePbarIcons[playerid][1], 255);
	PlayerTextDrawSetProportional(playerid, PTD_VehiclePbarIcons[playerid][1], 0);
	SetPlayerTextDrawLayer(playerid, PTD_VehiclePbarIcons[playerid][1], LAYER_SPEEDO);
	return 1;
}

DestroyPbarsIconsTextdraws(playerid)
{
	if(PTD_VehiclePbarIcons[playerid][0] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_VehiclePbarIcons[playerid][0]);
		PTD_VehiclePbarIcons[playerid][0] = PlayerText:INVALID_TEXT_DRAW;
	}
	if(PTD_VehiclePbarIcons[playerid][1] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_VehiclePbarIcons[playerid][1]);
		PTD_VehiclePbarIcons[playerid][1] = PlayerText:INVALID_TEXT_DRAW;
	}
	return 1;
}

CreatePlayerSpeedoTextdraws(playerid)
{
	new Float:result_x, Float:result_size_x;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 580.0, 80.0, true, result_x, result_size_x);
	PTD_VehicleSpeedo[playerid][0] = CreatePlayerTextDraw(playerid, result_x, 345.000000, ""TEXTDRAW_CUSTOM_PATH"circle");
	PlayerTextDrawTextSize(playerid, PTD_VehicleSpeedo[playerid][0], result_size_x, 80.000000);
	PlayerTextDrawAlignment(playerid, PTD_VehicleSpeedo[playerid][0], 1);
	PlayerTextDrawFont(playerid, PTD_VehicleSpeedo[playerid][0], 4);
	PlayerTextDrawColor(playerid, PTD_VehicleSpeedo[playerid][0], 180);
	PlayerTextDrawSetShadow(playerid, PTD_VehicleSpeedo[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VehicleSpeedo[playerid][0], 255);
	PlayerTextDrawSetProportional(playerid, PTD_VehicleSpeedo[playerid][0], 0);
	SetPlayerTextDrawLayer(playerid, PTD_VehicleSpeedo[playerid][0], LAYER_SPEEDO);

	PTD_VehicleSpeedo[playerid][1] = CreatePlayerTextDraw(playerid, result_x, 345.000000, ""TEXTDRAW_CUSTOM_PATH"circle_bg");
	PlayerTextDrawTextSize(playerid, PTD_VehicleSpeedo[playerid][1], result_size_x, 80.000000);
	PlayerTextDrawFont(playerid, PTD_VehicleSpeedo[playerid][1], 4);
	PlayerTextDrawAlignment(playerid, PTD_VehicleSpeedo[playerid][1], 1);
	PlayerTextDrawColor(playerid, PTD_VehicleSpeedo[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, PTD_VehicleSpeedo[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VehicleSpeedo[playerid][1], 255);
	PlayerTextDrawSetProportional(playerid, PTD_VehicleSpeedo[playerid][1], 0);
	SetPlayerTextDrawLayer(playerid, PTD_VehicleSpeedo[playerid][1], LAYER_SPEEDO);

	PTD_VehicleSpeedo[playerid][2] = CreatePlayerTextDraw(playerid, 580.0, 359.000000, "0");
	PlayerTextDrawLetterSize(playerid, PTD_VehicleSpeedo[playerid][2], 0.517000, 3.230221);
	PlayerTextDrawAlignment(playerid, PTD_VehicleSpeedo[playerid][2], 2);
	PlayerTextDrawFont(playerid, PTD_VehicleSpeedo[playerid][2], 2);
	PlayerTextDrawColor(playerid, PTD_VehicleSpeedo[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, PTD_VehicleSpeedo[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VehicleSpeedo[playerid][2], 255);
	PlayerTextDrawSetProportional(playerid, PTD_VehicleSpeedo[playerid][2], 1);
	SetPlayerTextDrawLayer(playerid, PTD_VehicleSpeedo[playerid][2], LAYER_SPEEDO);

	PTD_VehicleSpeedo[playerid][3] = CreatePlayerTextDraw(playerid, 580.0, 383.000000, "km/h");
	PlayerTextDrawLetterSize(playerid, PTD_VehicleSpeedo[playerid][3], 0.240997, 1.533630);
	PlayerTextDrawAlignment(playerid, PTD_VehicleSpeedo[playerid][3], 2);
	PlayerTextDrawFont(playerid, PTD_VehicleSpeedo[playerid][3], 2);
	PlayerTextDrawColor(playerid, PTD_VehicleSpeedo[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, PTD_VehicleSpeedo[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VehicleSpeedo[playerid][3], 255);
	PlayerTextDrawSetProportional(playerid, PTD_VehicleSpeedo[playerid][3], 1);
	SetPlayerTextDrawLayer(playerid, PTD_VehicleSpeedo[playerid][3], LAYER_SPEEDO);

	PTD_VehicleSpeedo[playerid][4] = CreatePlayerTextDraw(playerid, 580.0, 398.000000, "0_KM");
	PlayerTextDrawLetterSize(playerid, PTD_VehicleSpeedo[playerid][4], 0.148996, 1.031702);
	PlayerTextDrawAlignment(playerid, PTD_VehicleSpeedo[playerid][4], 2);
	PlayerTextDrawFont(playerid, PTD_VehicleSpeedo[playerid][4], 2);
	PlayerTextDrawColor(playerid, PTD_VehicleSpeedo[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, PTD_VehicleSpeedo[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, PTD_VehicleSpeedo[playerid][4], 255);
	PlayerTextDrawSetProportional(playerid, PTD_VehicleSpeedo[playerid][4], 1);
	SetPlayerTextDrawLayer(playerid, PTD_VehicleSpeedo[playerid][4], LAYER_SPEEDO);
	return 1;
}

DestroyPlayerSpeedoTextdraws(playerid)
{
	for(new i = 0, j = sizeof PTD_VehicleSpeedo[]; i != j; i ++)
	{
		if(PTD_VehicleSpeedo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_VehicleSpeedo[playerid][i]);
			PTD_VehicleSpeedo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

ShowPlayerSpeedoTextdraws(playerid)
{
	for(new i = 0, j = sizeof PTD_VehicleSpeedo[]; i != j; i ++)
	{
		if(PTD_VehicleSpeedo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawShow(playerid, PTD_VehicleSpeedo[playerid][i]);
		}
	}
	return 1;
}

HidePlayerSpeedoTextdraws(playerid)
{
	for(new i = 0, j = sizeof PTD_VehicleSpeedo[]; i != j; i ++)
	{
		if(PTD_VehicleSpeedo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawHide(playerid, PTD_VehicleSpeedo[playerid][i]);
		}
	}
	return 1;
}

ShowVehFuncProgressBars(playerid)
{
	ShowPlayerProgressBar(playerid, PROGRESSBAR_VEHICLE_HEALTH[playerid]);
	ShowPlayerProgressBar(playerid, PROGRESSBAR_VEHICLE_FUEL[playerid]);
	return 1;
}

HideVehFuncProgressBars(playerid)
{
	HidePlayerProgressBar(playerid, PROGRESSBAR_VEHICLE_HEALTH[playerid]);
	HidePlayerProgressBar(playerid, PROGRESSBAR_VEHICLE_FUEL[playerid]);
	return 1;
}

ShowPbarsIcons(playerid)
{
	PlayerTextDrawShow(playerid, PTD_VehiclePbarIcons[playerid][0]);
	PlayerTextDrawShow(playerid, PTD_VehiclePbarIcons[playerid][1]);
	return 1;
}

HidePbarsIcons(playerid)
{
	PlayerTextDrawHide(playerid, PTD_VehiclePbarIcons[playerid][0]);
	PlayerTextDrawHide(playerid, PTD_VehiclePbarIcons[playerid][1]);
	return 1;
}

ShowVehicleFuncsTextDraws(playerid)
{
	ShowPlayerSpeedoTextdraws(playerid);
	ShowVehFuncProgressBars(playerid);
	ShowPbarsIcons(playerid);

	if(!PI[playerid][pi_MPH]) PlayerTextDrawSetString(playerid, PTD_VehicleSpeedo[playerid][3], "km/h");
	else PlayerTextDrawSetString(playerid, PTD_VehicleSpeedo[playerid][3], "mph");
	return 1;
}

HideVehicleFuncsTextDraws(playerid)
{
	HidePlayerSpeedoTextdraws(playerid);
	HideVehFuncProgressBars(playerid);
	HidePbarsIcons(playerid);
	return 1;
}

ShowVehicleFuncs(playerid)
{
	StopPlayerVehFuncsTimer(playerid);

	new index = GetPlayerVehicleIndex(playerid);
	GetVehiclePos(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_POS][0], VehicleInfo[index][vinfo_POS][1], VehicleInfo[index][vinfo_POS][2]);
	
	//progressbars
	GetVehicleHealth(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_HEALTH]);
		
	new Float:health_percent = VehicleInfo[index][vinfo_HEALTH] / 10.0,
		Float:fuel_percent = GetVehicleFuelPercent(index);
	SetPlayerProgressBarBarColor(playerid, PROGRESSBAR_VEHICLE_HEALTH[playerid], GetGradientColor(0xb44e41ff, 0x9fb441ff, health_percent));
	SetPlayerProgressBarBarColor(playerid, PROGRESSBAR_VEHICLE_FUEL[playerid], GetGradientColor(0xc4a473ff, 0xffb441ff, fuel_percent));

	SetPlayerProgressBarValue(playerid, PROGRESSBAR_VEHICLE_HEALTH[playerid], health_percent);
	SetPlayerProgressBarValue(playerid, PROGRESSBAR_VEHICLE_FUEL[playerid], fuel_percent);
	//

	pPlayerVehFuncsTimer[playerid] = repeat OnPlayerVehFuncsUpdate(playerid, index);
	pPlayerVehFuncs[playerid] = true;

	ShowVehicleFuncsTextDraws(playerid);
	return 1;
}

HideVehicleFuncs(playerid)
{
	StopPlayerVehFuncsTimer(playerid);
	HideVehicleFuncsTextDraws(playerid);
	pPlayerVehFuncs[playerid] = false;
	return 1;
}

StopPlayerVehFuncsTimer(playerid)
{
	if(pPlayerVehFuncsTimer[playerid] != Timer:-1)
	{
		stop pPlayerVehFuncsTimer[playerid];
		pPlayerVehFuncsTimer[playerid] = Timer:-1;
		return 1;
	}
	return 0;
}

PlayVehicleRadioForPlayer(playerid, index)
{
	if(VehicleInfo[index][vinfo_RADIO] < 0)
	VehicleInfo[index][vinfo_RADIO] = 0;

	PlayAudioStreamForPlayer(playerid, Radios[ VehicleInfo[index][vinfo_RADIO] ][radio_URL]);
	return 1;
}

SetVehicleRadio(index, radio)
{
	VehicleInfo[index][vinfo_RADIO] = radio;

	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) == GAME_STATE_SPAWNED)
		{
			if(GetPlayerVehicleID(i) == VehicleInfo[index][vinfo_VEHICLE_ID])
			{
				if(VehicleInfo[index][vinfo_RADIO]) PlayAudioStreamForPlayer(i, Radios[ VehicleInfo[index][vinfo_RADIO] ][radio_URL]);
				else StopAudioStreamForPlayer(i);
			}
		}
	}
	return 1;
}

HasPlayerAccessToVehicle(playerid, index)
{
	/*switch(VehicleInfo[index][vinfo_TYPE])
	{
		case VEHICLE_TYPE_PLAYER, VEHICLE_TYPE_RENT:
		{
			new inv_params[16];
			format(inv_params, sizeof inv_params, "%d,%d", VehicleInfo[index][vinfo_ID], VehicleInfo[index][vinfo_MODELID]);
			if(PlayerInvContainsItemEx(playerid, _:INV_ITEM_VEHICLE_MASTER_KEY, _:INV_ITEM_VEHICLE_KEY, _:INV_ITEM_VEHICLE_RENT_KEY, inv_params))
			{
				return true;
			}
		}
		case VEHICLE_TYPE_JOB:
		{
			if(GetPlayerJobPointId(playerid) == VehicleInfo[index][vinfo_ID_JOB_POINT])
			{
				return true;
			}
		}
	}*/
	if(Iter_Contains(PlayerVehicles[playerid], index))
	return true;
	return false;
}