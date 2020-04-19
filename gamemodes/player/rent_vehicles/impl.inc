#include <YSI\y_hooks>

loadtext lang[rent_vehicles];

hook OnPlayerGetVehicleIndex(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new index = GetPlayerVehicleIndex(playerid);
		if(VehicleInfo[index][vinfo_TYPE] == VEHICLE_TYPE_RENT)
		{
			if(!VehicleInfo[index][vinfo_ID_PLAYER])
			{
				if(GetPlayerInvFreeItemSlot(playerid) == cellmin) Text_Send(playerid, $MESSAGE_ERROR_INV_SLOT);
				else if(!PlayerInvContainsItem(playerid, _:INV_ITEM_DRIVER_LICENSE)) Text_Send(playerid, $MESSAGE_ERROR_NO_LICENSE);
				else if(PlayerInvContainsItem(playerid, _:INV_ITEM_VEHICLE_RENT_KEY)) Text_Send(playerid, $MESSAGE_ERROR_VEHICLE_RENTED);
				else if(VehicleInfo[index][vinfo_PRICE] > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY, VehicleInfo[index][vinfo_PRICE]);
				else if(VehicleInfo[index][vinfo_LEVEL] > PI[playerid][pi_LEVEL]) Text_Send(playerid, $MESSAGE_ERROR_NO_LEVEL, VehicleInfo[index][vinfo_LEVEL]);
				else
				{
					inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
					{
						#pragma unused pid, dialogid, listitem, inputtext
						if(response)
						{
							new inv_params[24];
							format(inv_params, sizeof inv_params, "%d,%d", VehicleInfo[index][vinfo_ID], VehicleInfo[index][vinfo_MODELID]);
							if(AddPlayerInventoryItem(playerid, _:INV_ITEM_VEHICLE_RENT_KEY, inv_params))
							{
								DestroyPlayerLabel(playerid);
								GivePlayerMoneyEx(playerid, -VehicleInfo[index][vinfo_PRICE], true);

								VehicleInfo[index][vinfo_ID_PLAYER] = PI[playerid][pi_ID];
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET id_player = %d WHERE id = %d;", PI[playerid][pi_ID], VehicleInfo[index][vinfo_ID]);
								mysql_tquery(vcrp_db, QUERY_BUFFER);

								Iter_Add(PlayerVehicles[playerid], index);
								Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_RENTED);
								CallRemoteFunction("OnPlayerRentVehicle", "id", playerid, index);
							}
						}
						else RemovePlayerFromVehicle(playerid);
					}
					Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_RENT_VEHICLE_CAPTION, $DIALOG_RENT_VEHICLE_BODY, $DIALOG_RENT_VEHICLE_YES, $DIALOG_RENT_VEHICLE_NO, GetVehicleNameByModelid(VehicleInfo[index][vinfo_MODELID]), VehicleInfo[index][vinfo_PRICE]);
				}
			}
		}
	}
	return 1;
}

hook OnPlGiveItemToPlayer(playerid, toplayerid, itemid, params[])
{
	if(itemid == _:INV_ITEM_VEHICLE_RENT_KEY)
	{
		new veh_id, veh_modelid;
		#pragma unused veh_modelid
		if(!sscanf(params, "p<,>dd", veh_id, veh_modelid))
		{
			new veh_index = GetVehicleIndexById(veh_id);
			if(veh_index != INVALID_VEHICLE_INDEX)
			{
				if(VehicleInfo[veh_index][vinfo_ID_PLAYER])
				{
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET id_player = %d WHERE id = %d;", PI[toplayerid][pi_ID], VehicleInfo[veh_index][vinfo_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER);
					Iter_Remove(PlayerVehicles[playerid], veh_index);
					Iter_Add(PlayerVehicles[toplayerid], veh_index);
					VehicleInfo[veh_index][vinfo_ID_PLAYER] = PI[toplayerid][pi_ID];
				}
			}
		}
	}
	return 1;
}

hook OnPlayerItemDeleted(playerid, index, inv_id, itemid, params[], bool:player_action, amount)
{
	if(itemid == _:INV_ITEM_VEHICLE_RENT_KEY)
	{
		new veh_id, veh_modelid;
		#pragma unused veh_modelid
		if(!sscanf(params, "p<,>dd", veh_id, veh_modelid))
		{
			new veh_index = GetVehicleIndexById(veh_id);
			if(veh_index != INVALID_VEHICLE_INDEX)
			{
				if(VehicleInfo[veh_index][vinfo_ID_PLAYER])
				{
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET id_player = NULL WHERE id = %d;", VehicleInfo[veh_index][vinfo_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER);
					VehicleInfo[veh_index][vinfo_ID_PLAYER] = 0;
					DeleteVehicleKeys(VehicleInfo[veh_index][vinfo_ID], VehicleInfo[veh_index][vinfo_MODELID], veh_index);
				}
				if(Rent_VehicleInfo[veh_index][vrent_AREAID] == INVALID_STREAMER_ID)
				{
					new streamer_info[2];
					Rent_VehicleInfo[veh_index][vrent_AREAID] = CreateDynamicCylinder(0.0, 0.0, 0.0, VehicleInfo[veh_index][vinfo_SPAWN_POS][2] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, VehicleInfo[veh_index][vinfo_WORLDID], VehicleInfo[veh_index][vinfo_INTERIORID]);
					AttachDynamicAreaToVehicle(Rent_VehicleInfo[veh_index][vrent_AREAID], VehicleInfo[veh_index][vinfo_VEHICLE_ID], 0.0, 0.0, 0.0 - PLAYER_LABEL_DISTANCE);
					streamer_info[0] = _:AREA_TYPE_LABEL_RENT_VEHICLE;
					streamer_info[1] = veh_index;
					Streamer_SetArrayData(STREAMER_TYPE_AREA, Rent_VehicleInfo[veh_index][vrent_AREAID], E_STREAMER_EXTRA_ID, streamer_info);
				}
			}
		}
	}
	return 1;
}

hook OnPlayerRentVehicle(playerid, vehindex)
{
	if(Rent_VehicleInfo[vehindex][vrent_AREAID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(Rent_VehicleInfo[vehindex][vrent_AREAID]);
		Rent_VehicleInfo[vehindex][vrent_AREAID] = INVALID_STREAMER_ID;
	}
	return 1;
}