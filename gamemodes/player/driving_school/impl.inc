#include <YSI\y_hooks>

loadtext lang[driving_school];

public OnPlayerRequestDrivingSchool(playerid)
{
	if(GetPlayerInvFreeItemSlot(playerid) == cellmin) Text_Send(playerid, $MESSAGE_ERROR_INV_SLOT);
	else if(PlayerInvContainsItem(playerid, _:INV_ITEM_DRIVER_LICENSE)) Text_Send(playerid, $MESSAGE_ERROR_HAVE_LICENSE);
	else if(DRIVER_LICENSE_PRICE > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
	else
	{
		SavePlayerWorldInfo_DB(playerid);
		SetPlayerGameState(playerid, GAME_STATE_SPECTATING);
		PlayAudioStreamForPlayer(playerid, ""RADIO_URL"/vcrp.ogg");
		HidePlayerInfoMessage(playerid);
		SetPlayerVirtualWorld(playerid, playerid + 1);
		TogglePlayerSpectating(playerid, true);
		InterpolateCameraPos(playerid, Driving_School_Camera_Pos[0], Driving_School_Camera_Pos[1], Driving_School_Camera_Pos[2], Driving_School_Camera_Pos[0], Driving_School_Camera_Pos[1], Driving_School_Camera_Pos[2], 5000, CAMERA_MOVE);
		InterpolateCameraLookAt(playerid, Driving_School_Camera_Pos[3], Driving_School_Camera_Pos[4], Driving_School_Camera_Pos[5], Driving_School_Camera_Pos[3], Driving_School_Camera_Pos[4], Driving_School_Camera_Pos[5], 5000, CAMERA_MOVE);
		pDrivingSchoolPoints[playerid] = 0;
		pDrivingSchoolQuestion[playerid] = 0;

		inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
		{
			#pragma unused pid, dialogid, listitem, inputtext
			if(response)
			{
				GivePlayerMoneyEx(playerid, -DRIVER_LICENSE_PRICE, true);
				ShowPlayerDrivingSchoolTestDlg(playerid);
			}
			else
			{
				LoadScreenTimed(playerid);
				TogglePlayerSpectating(playerid, false);
			}
		}
		Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_LICENSE_INFO_CAPTION, $DIALOG_LICENSE_INFO_BODY, $DIALOG_LICENSE_INFO_YES, $DIALOG_LICENSE_INFO_NO, DRIVER_LICENSE_PRICE);
	}
	return 1;
}

public OnPlayerDrivingSchoolTestDialog(playerid, dialogid, response, listitem, inputtext[])
{
	if(listitem == pDrivingSchoolValidQuestion[playerid] - 1) pDrivingSchoolPoints[playerid] ++;
	pDrivingSchoolQuestion[playerid] ++;

	if(pDrivingSchoolQuestion[playerid] >= 5)
	{
		if(pDrivingSchoolPoints[playerid] == 5)
		{
			//pass
			//vehicle
			pDrivingSchoolVehicleIndex[playerid] = CreateVehicleEx
			(
				VEHICLE_TYPE_DRIVING_SCHOOL,
				405,
				Driving_School_Vehicle_Pos[0],
				Driving_School_Vehicle_Pos[1],
				Driving_School_Vehicle_Pos[2],
				Driving_School_Vehicle_Pos[3],
				.worldid = playerid + 1,
				.params_engine = 1
			);
			
			//player
			pInDrivingSchoolVehicleTest[playerid] = true;
			PI[playerid][pi_X] = Driving_School_Ext_Pos[0];
			PI[playerid][pi_Y] = Driving_School_Ext_Pos[1];
			PI[playerid][pi_Z] = Driving_School_Ext_Pos[2];
			PI[playerid][pi_ANGLE] = Driving_School_Ext_Pos[3];
			PI[playerid][pi_INTERIORID] = 0;
			PI[playerid][pi_WORLDID] = playerid + 1;
			SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_OTHER, 0);
			Text_Send(playerid, $GAMETEXT_INFO_LICENSE_TEST);		
			//route
			DestroyPlayerRoute(playerid);
			for(new i = 0; i != sizeof Driving_School_Points; i ++)
			{
				AddRouteCp(playerid, Driving_School_Points[i][dsp_X], Driving_School_Points[i][dsp_Y], Driving_School_Points[i][dsp_Z]);
			}
		}
		else Text_Send(playerid, $MESSAGE_ERROR_LICENSE_TEST);
		LoadScreenTimed(playerid);
		TogglePlayerSpectating(playerid, false);
	}
	else ShowPlayerDrivingSchoolTestDlg(playerid);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(pInDrivingSchoolVehicleTest[playerid])
	{
		//cam
		InterpolateCameraPos(playerid, Driving_School_Ext_Cam_Pos[0], Driving_School_Ext_Cam_Pos[1], Driving_School_Ext_Cam_Pos[2], Driving_School_Ext_Cam_Pos[0], Driving_School_Ext_Cam_Pos[1], Driving_School_Ext_Cam_Pos[2], 5000, CAMERA_CUT);
		InterpolateCameraLookAt(playerid, Driving_School_Ext_Cam_Pos[3], Driving_School_Ext_Cam_Pos[4], Driving_School_Ext_Cam_Pos[5], Driving_School_Ext_Cam_Pos[3], Driving_School_Ext_Cam_Pos[4], Driving_School_Ext_Cam_Pos[5], 5000, CAMERA_CUT);
		Text_Send(playerid, $MESSAGE_INFO_VEHICLE_LICENSE);
	}
	return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(pInDrivingSchoolVehicleTest[playerid])
	{
		SetCameraBehindPlayer(playerid);
	}
	return 1;
}

hook OnPlayerOpenMenu(playerid)
{
	if(pInDrivingSchoolVehicleTest[playerid]) CancelDrivingSchoolTest(playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(pInDrivingSchoolVehicleTest[playerid]) CancelDrivingSchoolTest(playerid);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(pInDrivingSchoolVehicleTest[playerid]) CancelDrivingSchoolTest(playerid);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(pInDrivingSchoolVehicleTest[playerid])
	{
		if(newstate == PLAYER_STATE_DRIVER)
		{
			if(pDrivingSchoolTest_Timer[playerid] == Timer:-1)
			{
				pDrivingSchoolTest_Timer[playerid] = repeat OnPlayerDrivingSchoolUpdate(playerid);
			}
			HidePlayerInfoMessage(playerid);
			pDrivingSchoolCancelSeconds[playerid] = DRIVING_SCHOOL_CANCEL_SECONDS;
			if(!IsPlayerInRoute(playerid)) StartRoute(playerid);
			else ShowPlayerRoute(playerid);
		}
		else if(oldstate == PLAYER_STATE_DRIVER)
		{
			HidePlayerAuxTextDraw(playerid);
			HidePlayerRoute(playerid);
		}
	}
	return 1;
}

hook OnVehicleDeathEx(vehindex, killerid)
{
	if(pInDrivingSchoolVehicleTest[killerid])
	{
		if(pDrivingSchoolVehicleIndex[killerid] != INVALID_VEHICLE_INDEX)
		{
			if(VehicleInfo[vehindex][vinfo_VEHICLE_ID] == VehicleInfo[ pDrivingSchoolVehicleIndex[killerid] ][vinfo_VEHICLE_ID])
			{
				CancelDrivingSchoolTest(killerid);
				PlayerDrivingSchoolMsg(killerid, 1);

				PI[killerid][pi_X] = Driving_School_Ext_Pos[0];
				PI[killerid][pi_Y] = Driving_School_Ext_Pos[1];
				PI[killerid][pi_Z] = Driving_School_Ext_Pos[2];
				PI[killerid][pi_ANGLE] = Driving_School_Ext_Pos[3];
				PI[killerid][pi_INTERIORID] = 0;
				PI[killerid][pi_WORLDID] = VC_WORLD;
				SetPlayerWorldState(killerid, PLAYER_WORLD_STATE_STREET);
				SetPlayerPosEx(killerid, PI[killerid][pi_X], PI[killerid][pi_Y], PI[killerid][pi_Z], PI[killerid][pi_ANGLE], PI[killerid][pi_INTERIORID], PI[killerid][pi_WORLDID], true);
			}
		}
	}
	return 1;
}

hook OnPlayerRouteFinish(playerid)
{
	if(pInDrivingSchoolVehicleTest[playerid])
	{
		CancelDrivingSchoolTest(playerid);

		new date[24];
		getDateTime(date);
		if(AddPlayerInventoryItem(playerid, _:INV_ITEM_DRIVER_LICENSE, date))
		{
			Text_Send(playerid, $GAMETEXT_INFO_LICENSE_PASSED);
			CallRemoteFunction("OnPlayerGetDriverLicen", "i", playerid);
		}
		else Text_Send(playerid, $MESSAGE_ERROR_INV_SLOT);

		PI[playerid][pi_X] = Driving_School_Ext_Pos[0];
		PI[playerid][pi_Y] = Driving_School_Ext_Pos[1];
		PI[playerid][pi_Z] = Driving_School_Ext_Pos[2];
		PI[playerid][pi_ANGLE] = Driving_School_Ext_Pos[3];
		PI[playerid][pi_INTERIORID] = 0;
		PI[playerid][pi_WORLDID] = VC_WORLD;
		SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
		SetPlayerPosEx(playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], PI[playerid][pi_INTERIORID], PI[playerid][pi_WORLDID], true);
	}
	return 1;
}

timer OnPlayerDrivingSchoolUpdate[DRIVING_SCHOOL_UPDATE_INTERVAL](playerid)
{
	if(pInDrivingSchoolVehicleTest[playerid])
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
			pDrivingSchoolCancelSeconds[playerid] --;
			if(pDrivingSchoolCancelSeconds[playerid] <= 0)
			{
				CancelDrivingSchoolTest(playerid);
				PlayerDrivingSchoolMsg(playerid, 0);

				PI[playerid][pi_X] = Driving_School_Ext_Pos[0];
				PI[playerid][pi_Y] = Driving_School_Ext_Pos[1];
				PI[playerid][pi_Z] = Driving_School_Ext_Pos[2];
				PI[playerid][pi_ANGLE] = Driving_School_Ext_Pos[3];
				PI[playerid][pi_INTERIORID] = 0;
				PI[playerid][pi_WORLDID] = VC_WORLD;
				SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
				SetPlayerPosEx(playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], PI[playerid][pi_INTERIORID], PI[playerid][pi_WORLDID], true);
			}
			else PlayerDrivingSchoolCancelMsg(playerid);
		}
		else
		{
			if(IsPlayerInRoute(playerid) && GetPlayerRouteCP(playerid) != -1)
			{
				new Float:speed = Vehicle_Speed(VehicleInfo[pDrivingSchoolVehicleIndex[playerid]][vinfo_VEHICLE_ID]);
				if(speed > Driving_School_Points[GetPlayerRouteCP(playerid)][dsp_SPEED_LIMIT] + 5)
				{
					CancelDrivingSchoolTest(playerid);
					PlayerDrivingSchoolMsg(playerid, 2);

					PI[playerid][pi_X] = Driving_School_Ext_Pos[0];
					PI[playerid][pi_Y] = Driving_School_Ext_Pos[1];
					PI[playerid][pi_Z] = Driving_School_Ext_Pos[2];
					PI[playerid][pi_ANGLE] = Driving_School_Ext_Pos[3];
					PI[playerid][pi_INTERIORID] = 0;
					PI[playerid][pi_WORLDID] = VC_WORLD;
					SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
					SetPlayerPosEx(playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], PI[playerid][pi_INTERIORID], PI[playerid][pi_WORLDID], true);
				}
				else
				{
					new next_cp = GetPlayerRouteCP(playerid) + 1;
					if(next_cp >= sizeof Driving_School_Points) next_cp = (sizeof Driving_School_Points) - 1;
					ShowPlayerAuxTextDraw(playerid, GetSpeedLimitText(playerid, speed, Driving_School_Points[GetPlayerRouteCP(playerid)][dsp_SPEED_LIMIT], Driving_School_Points[GetPlayerRouteCP(playerid) + 1][dsp_SPEED_LIMIT]));
				}
			}
		}
	}
	else
	{
		if(pDrivingSchoolTest_Timer[playerid] != Timer:-1)
		{
			stop pDrivingSchoolTest_Timer[playerid];
			pDrivingSchoolTest_Timer[playerid] = Timer:-1;
		}
	}
	return 1;
}