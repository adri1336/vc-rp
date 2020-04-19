#include <YSI\y_hooks>

loadtext lang[vehicle_funcs];

hook OnPlayerConnect(playerid)
{
	pPlayerVehFuncs[playerid] = false;
	return 1;
}

hook OnPlayerLogin(playerid)
{
	CreatePlayerSpeedoTextdraws(playerid);
	CreateVehFuncsProgressbars(playerid);
	CreatePbarsIconsTextdraws(playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	StopPlayerVehFuncsTimer(playerid);
	DestroyPlayerSpeedoTextdraws(playerid);
	DestroyVehFuncsProgressbars(playerid);
	DestroyPbarsIconsTextdraws(playerid);
	return 1;
}

//hook OnPlayerVehicleChange(playerid, from_vehicleid, to_vehicleid)
//if(to_vehicleid != INVALID_OPVC_VEHICLE_ID)
//else if(to_vehicleid == INVALID_OPVC_VEHICLE_ID && from_vehicleid != INVALID_OPVC_VEHICLE_ID)
hook OnPlayerGetVehicleIndex(playerid)
{
	new newstate = GetPlayerState(playerid);
	if(newstate == PLAYER_STATE_DRIVER)
	{
		new index = GetPlayerVehicleIndex(playerid);
		if(VehicleModelHasEngine(VehicleInfo[index][vinfo_MODELID]))
		{
			PlayVehicleRadioForPlayer(playerid, index);
			ShowVehicleFuncs(playerid);
		}
	}
	else if(newstate == PLAYER_STATE_PASSENGER)
	{
		new index = GetPlayerVehicleIndex(playerid);
		if(VehicleModelHasEngine(VehicleInfo[index][vinfo_MODELID]))
		{
			PlayVehicleRadioForPlayer(playerid, index);
		}
	}
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{
		StopAudioStreamForPlayer(playerid);
		if(pPlayerVehFuncs[playerid]) HideVehicleFuncs(playerid);
	}
	return 1;
}

timer OnPlayerVehFuncsUpdate[UPDATE_VEHFUNCS_INTERVAL](playerid, index)
{
	if(index != INVALID_VEHICLE_INDEX)
	{
		if(IsValidVehicle(index) && GetPlayerVehicleID(playerid) == VehicleInfo[index][vinfo_VEHICLE_ID])
		{
			new td_str[24];

			//distance
			new Float:distance = GetVehicleDistanceFromPoint(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_POS][0], VehicleInfo[index][vinfo_POS][1], VehicleInfo[index][vinfo_POS][2]);
			VehicleInfo[index][vinfo_DISTANCE] += distance;
			GetVehiclePos(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_POS][0], VehicleInfo[index][vinfo_POS][1], VehicleInfo[index][vinfo_POS][2]);

			if(!PI[playerid][pi_MPH]) format(td_str, sizeof td_str, "%06d_KM", floatround(VehicleInfo[index][vinfo_DISTANCE] / 1000.0));
			else format(td_str, sizeof td_str, "%06d_M", floatround(KMHtoMPH(VehicleInfo[index][vinfo_DISTANCE] / 1000.0)));
			PlayerTextDrawSetString(playerid, PTD_VehicleSpeedo[playerid][4], td_str);

			//fuel
			if(VehicleInfo[index][vinfo_PARAMS_ENGINE])
			{
				VehicleInfo[index][vinfo_FUEL] -= (distance / 1000.0);
				if(VehicleInfo[index][vinfo_FUEL] <= 0.0)
				{
					VehicleInfo[index][vinfo_PARAMS_ENGINE] = 0;
					SetVehicleParams(index);

					VehicleInfo[index][vinfo_FUEL] = 0.0;
					Text_Send(playerid, $GAMETEXT_INFO_NO_FUEL);
				}
			}

			//progressbars
			GetVehicleHealth(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_HEALTH]);
			
			new Float:health_percent = VehicleInfo[index][vinfo_HEALTH] / 10.0,
				Float:fuel_percent = GetVehicleFuelPercent(index);
			SetPlayerProgressBarBarColor(playerid, PROGRESSBAR_VEHICLE_HEALTH[playerid], GetGradientColor(0xb44e41ff, 0x9fb441ff, health_percent));
			SetPlayerProgressBarBarColor(playerid, PROGRESSBAR_VEHICLE_FUEL[playerid], GetGradientColor(0xc4a473ff, 0xffb441ff, fuel_percent));

			SetPlayerProgressBarValue(playerid, PROGRESSBAR_VEHICLE_HEALTH[playerid], health_percent);
			SetPlayerProgressBarValue(playerid, PROGRESSBAR_VEHICLE_FUEL[playerid], fuel_percent);
			ShowVehFuncProgressBars(playerid);


			//velocidad
			format(td_str, sizeof td_str, "%d", Vehicle_Speed(VehicleInfo[index][vinfo_VEHICLE_ID]));
			PlayerTextDrawSetString(playerid, PTD_VehicleSpeedo[playerid][2], td_str);

			//icons
			if(VehicleInfo[index][vinfo_FUEL] <= 0.0) td_str = ""TEXTDRAW_CUSTOM_PATH"gas_no";
			else if(VehicleInfo[index][vinfo_FUEL] < 10.0) td_str = ""TEXTDRAW_CUSTOM_PATH"gas_critical";
			else td_str = ""TEXTDRAW_CUSTOM_PATH"gas";
			PlayerTextDrawSetString(playerid, PTD_VehiclePbarIcons[playerid][0], td_str);

			if(VehicleInfo[index][vinfo_HEALTH] <= 250.0) td_str = ""TEXTDRAW_CUSTOM_PATH"motor_no";
			else if(VehicleInfo[index][vinfo_HEALTH] < 450.0) td_str = ""TEXTDRAW_CUSTOM_PATH"motor_critical";
			else td_str = ""TEXTDRAW_CUSTOM_PATH"motor";
			PlayerTextDrawSetString(playerid, PTD_VehiclePbarIcons[playerid][1], td_str);
		}
		else HideVehicleFuncs(playerid);
	}
	else HideVehicleFuncs(playerid);
	return 1;
}

YCMD:abrir(playerid, params[], help)
{
	OpenVehicle(playerid);
	return 1;
}

YCMD:cerrar(playerid, params[], help)
{
	CloseVehicle(playerid);
	return 1;
}

YCMD:motor(playerid, params[], help)
{
	EngineVehicle(playerid);
	return 1;
}

YCMD:luces(playerid, params[], help)
{
	LightsVehicle(playerid);
	return 1;
}

YCMD:radio(playerid, params[], help)
{
	RadioVehicle(playerid);
	return 1;
}

OpenVehicle(playerid)
{
	new index = INVALID_VEHICLE_INDEX;
	if(IsPlayerInAnyVehicle(playerid)) index = GetPlayerVehicleIndex(playerid);
	else
	{
		new vehicleid = GetPlayerCameraTargetVehicle(playerid);
		if(vehicleid != INVALID_VEHICLE_ID) index = GetVehicleIndexByVehicleid(vehicleid);
	}

	if(index == INVALID_VEHICLE_INDEX) Text_Send(playerid, $MESSAGE_ERROR_INVALID_VEHICLE_ID);
	else
	{
		if(!VehicleModelHasDoors(VehicleInfo[index][vinfo_MODELID])) Text_Send(playerid, $MESSAGE_ERROR_NO_DOORS);
		else
		{
			if(!HasPlayerAccessToVehicle(playerid, index)) Text_Send(playerid, $MESSAGE_ERROR_NO_ACCESS);
			else
			{
				VehicleInfo[index][vinfo_PARAMS_DOORS] = 0;
				SetVehicleParams(index);
				Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_OPENED);
				CallRemoteFunction("OnPlayerOpenVehicle", "id", playerid, VehicleInfo[index][vinfo_MODELID]);
			}
		}
	}
	return 1;
}

CloseVehicle(playerid)
{
	new index = INVALID_VEHICLE_INDEX;
	if(IsPlayerInAnyVehicle(playerid)) index = GetPlayerVehicleIndex(playerid);
	else
	{
		new vehicleid = GetPlayerCameraTargetVehicle(playerid);
		if(vehicleid != INVALID_VEHICLE_ID) index = GetVehicleIndexByVehicleid(vehicleid);
	}

	if(index == INVALID_VEHICLE_INDEX) Text_Send(playerid, $MESSAGE_ERROR_INVALID_VEHICLE_ID);
	else
	{
		if(!VehicleModelHasDoors(VehicleInfo[index][vinfo_MODELID])) Text_Send(playerid, $MESSAGE_ERROR_NO_DOORS);
		else
		{
			if(!HasPlayerAccessToVehicle(playerid, index)) Text_Send(playerid, $MESSAGE_ERROR_NO_ACCESS);
			else
			{
				VehicleInfo[index][vinfo_PARAMS_DOORS] = 1;
				SetVehicleParams(index);
				Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_CLOSED);
				CallRemoteFunction("OnPlayerCloseVehicle", "id", playerid, VehicleInfo[index][vinfo_MODELID]);
			}
		}
	}
	return 1;
}

EngineVehicle(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) Text_Send(playerid, $MESSAGE_ERROR_NO_DRIVING);
	else
	{
		new index = GetPlayerVehicleIndex(playerid);
		if(!VehicleModelHasEngine(VehicleInfo[index][vinfo_MODELID])) Text_Send(playerid, $MESSAGE_ERROR_NO_ENGINE);
		else
		{
			if(!HasPlayerAccessToVehicle(playerid, index)) Text_Send(playerid, $MESSAGE_ERROR_NO_ACCESS);
			else
			{
				if(VehicleInfo[index][vinfo_GAME_STATE] == VEHICLE_GAME_STATE_POUNDED)
				{
					inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
					{
						#pragma unused pid, dialogid, listitem, inputtext
						if(response)
						{
							if(VEHICLE_POUND_PRICE > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY, VEHICLE_POUND_PRICE);
							else
							{
								GivePlayerMoneyEx(playerid, -VEHICLE_POUND_PRICE, true);

								VehicleInfo[index][vinfo_GAME_STATE] = VEHICLE_GAME_STATE_NORMAL;
								VehicleInfo[index][vinfo_PARAMS_ENGINE] = 1;
								SetVehicleParams(index);
								Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_STARTED);
								CallRemoteFunction("OnPlayerStartVehicle", "id", playerid, VehicleInfo[index][vinfo_MODELID]);
							}
						}
					}
					Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_VEHICLE_POUND_CAPTION, $DIALOG_VEHICLE_POUND_BODY, $DIALOG_VEHICLE_POUND_YES, $DIALOG_VEHICLE_POUND_NO, VEHICLE_POUND_PRICE);
				}
				else
				{
					if(VehicleInfo[index][vinfo_PARAMS_ENGINE])
					{
						VehicleInfo[index][vinfo_PARAMS_ENGINE] = 0;
						Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_STOPPED);
						CallRemoteFunction("OnPlayerStopVehicle", "id", playerid, VehicleInfo[index][vinfo_MODELID]);
					}
					else
					{
						if(VehicleInfo[index][vinfo_FUEL] <= 0.0) Text_Send(playerid, $MESSAGE_ERROR_NO_FUEL);
						else
						{
							VehicleInfo[index][vinfo_PARAMS_ENGINE] = 1;
							Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_STARTED);
							CallRemoteFunction("OnPlayerStartVehicle", "id", playerid, VehicleInfo[index][vinfo_MODELID]);
						}
					}
					SetVehicleParams(index);
				}
			}
		}
	}
	return 1;
}

LightsVehicle(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) Text_Send(playerid, $MESSAGE_ERROR_NO_DRIVING);
	else
	{
		new index = GetPlayerVehicleIndex(playerid);
		if(!VehicleModelHasEngine(VehicleInfo[index][vinfo_MODELID])) Text_Send(playerid, $MESSAGE_ERROR_NO_ENGINE);
		else
		{
			if(VehicleInfo[index][vinfo_PARAMS_LIGHTS])
			{
				VehicleInfo[index][vinfo_PARAMS_LIGHTS] = 0;
				Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_LIGHTS_OFF);
				CallRemoteFunction("OnPlayerVehicleLiOff", "id", playerid, VehicleInfo[index][vinfo_MODELID]);
			}
			else
			{
				VehicleInfo[index][vinfo_PARAMS_LIGHTS] = 1;
				Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_LIGHTS_ON);
				CallRemoteFunction("OnPlayerVehicleLightsOn", "id", playerid, VehicleInfo[index][vinfo_MODELID]);
			}
			SetVehicleParams(index);
		}
	}
	return 1;
}

RadioVehicle(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) Text_Send(playerid, $MESSAGE_ERROR_NO_DRIVING);
	else
	{
		new index = GetPlayerVehicleIndex(playerid);
		if(!VehicleModelHasEngine(VehicleInfo[index][vinfo_MODELID])) Text_Send(playerid, $MESSAGE_ERROR_NO_RADIO);
		else
		{
			new dialog_message[512], line_str[45];
			for(new i = 0, j = sizeof Radios; i != j; i ++)
			{
				if(VehicleInfo[index][vinfo_RADIO] == i) format(line_str, sizeof line_str, "{ec98f9}- %s\n", Radios[i][radio_NAME]);
				else format(line_str, sizeof line_str, "{936c99}- %s\n", Radios[i][radio_NAME]);

				strcat(dialog_message, line_str);
			}

			inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
			{
				#pragma unused pid, dialogid, inputtext
				if(response)
				{
					SetVehicleRadio(index, listitem);
					CallRemoteFunction("OnPlayerChangeVRadio", "idd", playerid, index, listitem);
				}
			}
			Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_LIST, "Radio", dialog_message, ">", "X");
		}
	}
	return 1;
}

YCMD:echar(playerid, params[], help)
{
	new vindex = GetPlayerVehicleIndex(playerid);
	if(IsPlayerInAnyVehicle(playerid) && vindex != INVALID_VEHICLE_INDEX)
	{
		if(HasPlayerAccessToVehicle(playerid, vindex))
		{
			if(!sscanf(params, "u", params[0]))
			{
				if(!IsPlayerConnected(params[0]) || GetPlayerVehicleIndex(params[0]) != vindex || params[0] == playerid) Text_Send(playerid, $MESSAGE_ERROR_PLAYER_NOT_IN_VEHICLE);
				else RemovePlayerFromVehicle(params[0]);
			}
			else Text_Send(playerid, $MESSAGE_ERROR_KICK_SYNTAX);
		}
		else Text_Send(playerid, $MESSAGE_ERROR_NO_VEHICLE_ACCESS);
	}
	else Text_Send(playerid, $MESSAGE_ERROR_POSITION);
	return 1;
}