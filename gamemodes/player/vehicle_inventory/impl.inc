#include <YSI\y_hooks>

loadtext lang[vinv];

hook OnPlayerDisconnect(playerid, reason)
{
	DestroyPlayerVInventory(playerid);
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(pVInv[playerid])
	{
		if(clickedid == Text:INVALID_TEXT_DRAW)
		{
			DestroyPlayerVInventory(playerid);
			return 1;
		}
	}
	return 0;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	if(pVInv[playerid] && pVInvVehIndex[playerid] != INVALID_VEHICLE_INDEX)
	{
		if(!IsPlayerInDynamicArea(playerid, pVInvArea[playerid], 1) || Vehicle_Speed(VehicleInfo[ pVInvVehIndex[playerid] ][vinfo_VEHICLE_ID]) >= 1.0)
		{
			Text_Send(playerid, $MESSAGE_ERROR_VEH_GONE);
			CancelSelectTextDraw(playerid);
			return Y_HOOKS_BREAK_RETURN_1;
		}

		if(playertextid == pVInvTd_BASE[playerid][3])
		{
			//Add
			pVInvSelected[playerid] = -1;
			UpdateVInventoryTdsForPlayer(pVInvVehIndex[playerid], playerid);
			if(!pInvetory[playerid])
			{
				ShowPlayerInventory(playerid);
				PlayerTD_Text(playerid, pVInvTd_BASE[playerid][3], $TEXTDRAW_CLOSE_INV);
			}
			else
			{
				HidePlayerInvetory(playerid);
				PlayerTD_Text(playerid, pVInvTd_BASE[playerid][3], $TEXTDRAW_ADD_BUTTON);
			}
		}

		for(new i = 0; i != MAX_VEHICLE_INVENTORY_SLOTS; i ++)
		{
			if(playertextid == pVInvTd_ITEMS_BOX[playerid][i])
			{
				if(pInvetory[playerid])
				{
					HidePlayerInvetory(playerid);
					PlayerTD_Text(playerid, pVInvTd_BASE[playerid][3], $TEXTDRAW_ADD_BUTTON);
				}

				Dialog_Hide(playerid);
				if(pVInvSelected[playerid] == i) pVInvSelected[playerid] = -1;
				else pVInvSelected[playerid] = i;
				if(pVInvMoving[playerid])
				{
					MoveVInventoryItem(pVInvVehIndex[playerid], pVInvMove_Index[playerid], pVInvSelected[playerid]);
					pVInvMoving[playerid] = false;
					pVInvMove_Index[playerid] = -1;
					pVInvSelected[playerid] = -1;
				}
				UpdateVInventoryTdsForPlayer(pVInvVehIndex[playerid], playerid);
				return 1;
			}
		}

		for(new i = 0; i != MAX_VINV_BUTTONS; i ++)
		{
			if(playertextid == pVInvTd_BUTTONS[playerid][i])
			{
				VInvButtonAction(playerid, i);
				return 1;
			}
		}
	}
	return 0;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_SPECTATING || newstate == PLAYER_STATE_WASTED)
	{
		if(pVInv[playerid]) CancelSelectTextDraw(playerid);
	}
	return 1;
}

public OnPlayerOpenVehicleInventory(playerid, vehindex)
{
	if(vehindex != INVALID_VEHICLE_INDEX)
	{
		vInvInUse[vehindex] = true;
		VehicleInfo[vehindex][vinfo_PARAMS_BOOT] = 1;
		SetVehicleParams(vehindex);

		new Float:angle;
		GetVehicleZAngle(VehicleInfo[vehindex][vinfo_VEHICLE_ID], angle);
		SetPlayerFacingAngle(playerid, angle);
		ApplyAnimation(playerid, "SHOP", "SHP_Serve_Idle", 4.1, 1, 0, 0, 1, 0, 1);
	}
	return 1;
}

public OnPlayerCloseVehicleInventory(playerid, vehindex)
{
	if(vehindex != INVALID_VEHICLE_INDEX)
	{
		vInvInUse[vehindex] = false;
		VehicleInfo[vehindex][vinfo_PARAMS_BOOT] = 0;
		SetVehicleParams(vehindex);

		ClearAnimations(playerid, 1);
	}
	return 1;
}

YCMD:trunk(playerid, params[], help)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) Text_Send(playerid, $MESSAGE_ERROR_NO_ONFOOT);
	else
	{
		if(pLastActionAreaId[playerid] != INVALID_STREAMER_ID && IsPlayerInDynamicArea(playerid, pLastActionAreaId[playerid]))
		{
			new streamer_info[3];
			Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastActionAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
			if(streamer_info[0] == _:AREA_TYPE_VINV)
			{
				if(Vehicle_Speed(VehicleInfo[streamer_info[1]][vinfo_VEHICLE_ID]) <= 1.0)
				{
					if(vInvInUse[streamer_info[1]]) Text_Send(playerid, $MESSAGE_ERROR_VINV_IN_USE);
					else ShowVehicleInventoryForPlayer(streamer_info[1], playerid, pLastActionAreaId[playerid]);
				}
			}
		}
		Text_Send(playerid, $MESSAGE_ERROR_TRUNK_POSITION);
	}
	return 1;
}

public OnVehicleInvItemAdded(vehindex, index, amount)
{
	foreach(new i : Player)
	{
		if(pVInv[i] && pVInvVehIndex[i] == vehindex)
		{
			UpdateVInventoryTdsForPlayer(vehindex, i);
			PlayerTD_Text(i, pVInvTd_BASE[i][3], $TEXTDRAW_ADD_BUTTON);
		}
	}
	return 1;
}