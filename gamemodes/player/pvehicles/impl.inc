#include <YSI\y_hooks>

hook OnScriptInit()
{
	Iter_Init(PlayerVehicles);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	DestroyPlayerVehicles(playerid, true);
	Iter_Clear(PlayerVehicles[playerid]);
	return 1;
}

public OnPlayerInvDataLoaded(playerid)
{
	LoadPlayerVehicles(playerid);
	return 1;
}

hook OnVehicleSpawnEx(vehindex)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_PLAYER)
	{
		if(VehicleInfo[vehindex][vinfo_GAME_STATE] == VEHICLE_GAME_STATE_POUNDED)
		{
			new r = random(sizeof VehiclePoundPositions);
			VehicleInfo[vehindex][vinfo_SPAWN_POS][0] = VehiclePoundPositions[r][0];
			VehicleInfo[vehindex][vinfo_SPAWN_POS][1] = VehiclePoundPositions[r][1];
			VehicleInfo[vehindex][vinfo_SPAWN_POS][2] = VehiclePoundPositions[r][2];
			VehicleInfo[vehindex][vinfo_SPAWN_ANGLE] = VehiclePoundPositions[r][3];
			SetVehicleZAngleEx(vehindex, VehiclePoundPositions[r][3], true, VehiclePoundPositions[r][0], VehiclePoundPositions[r][1], VehiclePoundPositions[r][2]);
			
		}
	}
	return 1;
}

hook OnVehicleDeathEx(vehindex, killerid)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_PLAYER)
	{
		if(IsValidVehicleModelidPound(VehicleInfo[vehindex][vinfo_MODELID]))
		{
			VehicleInfo[vehindex][vinfo_GAME_STATE] = VEHICLE_GAME_STATE_POUNDED;
			VehicleInfo[vehindex][vinfo_INTERIORID] = 0;
			VehicleInfo[vehindex][vinfo_WORLDID] = 0;
		}
	}
	return 1;
}

hook OnPlGiveItemToPlayer(playerid, toplayerid, itemid, params[])
{
	if(itemid == _:INV_ITEM_VEHICLE_KEY)
	{
		new veh_id, veh_modelid;
		#pragma unused veh_modelid
		if(!sscanf(params, "p<,>dd", veh_id, veh_modelid))
		{
			new veh_index = GetVehicleIndexById(veh_id);
			if(veh_index != INVALID_VEHICLE_INDEX)
			{
				if(!PlayerInvContainsItemEx(playerid, _:INV_ITEM_VEHICLE_MASTER_KEY, _:INV_ITEM_VEHICLE_KEY, _:INV_ITEM_VEHICLE_RENT_KEY, params))
				Iter_Remove(PlayerVehicles[playerid], veh_index);

				if(!Iter_Contains(PlayerVehicles[toplayerid], veh_index))
				Iter_Add(PlayerVehicles[toplayerid], veh_index);
			}
		}
	}
	return 1;
}

hook OnPlayerItemDeleted(playerid, index, inv_id, itemid, params[], bool:player_action, amount)
{
	if(itemid == _:INV_ITEM_VEHICLE_KEY)
	{
		new veh_id, veh_modelid;
		#pragma unused veh_modelid
		if(!sscanf(params, "p<,>dd", veh_id, veh_modelid))
		{
			new veh_index = GetVehicleIndexById(veh_id);
			if(veh_index != INVALID_VEHICLE_INDEX)
			{
				if(!PlayerInvContainsItemEx(playerid, _:INV_ITEM_VEHICLE_MASTER_KEY, _:INV_ITEM_VEHICLE_KEY, _:INV_ITEM_VEHICLE_RENT_KEY, params))
				Iter_Remove(PlayerVehicles[playerid], veh_index);
			}
		}
	}
	return 1;
}