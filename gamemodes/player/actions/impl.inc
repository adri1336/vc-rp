#include <YSI\y_hooks>

loadtext lang[actions];

hook OnPlayerOpenVehicle(playerid, modelid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_OPEN_VEHICLE, PI[playerid][pi_RP_NAME], GetVehicleNameByModelid(modelid));
		}
	}
	return 1;
}

hook OnPlayerCloseVehicle(playerid, modelid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_CLOSE_VEHICLE, PI[playerid][pi_RP_NAME], GetVehicleNameByModelid(modelid));
		}
	}
	return 1;
}

hook OnPlayerStartVehicle(playerid, modelid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_START_VEHICLE, PI[playerid][pi_RP_NAME], GetVehicleNameByModelid(modelid));
		}
	}
	return 1;
}

hook OnPlayerStopVehicle(playerid, modelid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_STOP_VEHICLE, PI[playerid][pi_RP_NAME], GetVehicleNameByModelid(modelid));
		}
	}
	return 1;
}

hook OnPlGiveItemToPlayer(playerid, toplayerid, itemid, params[])
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_INV_GIVE, PI[playerid][pi_RP_NAME], GetItemName(i, itemid, params), PI[toplayerid][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlShowItemToPlayer(playerid, toplayerid, itemid, params[])
{
	if(playerid == toplayerid) return 1;
	
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_INV_SHOW, PI[playerid][pi_RP_NAME], GetItemName(i, itemid, params), PI[toplayerid][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlayerItemDeleted(playerid, index, inv_id, itemid, params[], bool:player_action, amount)
{
	if(player_action)
	{
		new 
			Float:x, Float:y, Float:z,
			current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

		GetPlayerPos(playerid, x, y, z);
		foreach(new i : Player)
		{
			if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
			if(GetPlayerVirtualWorld(i) != current_vw) continue;
			if(GetPlayerInterior(i) != current_int) continue;
			
			if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
			{
				if(amount > 1) Text_Send(i, $MESSAGE_ACTION_INV_DELETE_AMOUNT, PI[playerid][pi_RP_NAME], GetItemName(i, itemid, params), amount);
				else Text_Send(i, $MESSAGE_ACTION_INV_DELETE, PI[playerid][pi_RP_NAME], GetItemName(i, itemid, params));
			}
		}
	}
	return 1;
}

hook OnPlayerHospitalBed(playerid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_HOSPITAL_BED, PI[playerid][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlayerAtmWithdraw(playerid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_ATM_WITHDRAW, PI[playerid][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlayerAtmDeposit(playerid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_ATM_DEPOSIT, PI[playerid][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlayerVehicleLightsOn(playerid, modelid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_LIGHTS_VEHICLE_ON, PI[playerid][pi_RP_NAME], GetVehicleNameByModelid(modelid));
		}
	}
	return 1;
}

hook OnPlayerVehicleLiOff(playerid, modelid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_LIGHTS_VEHICLE_OFF, PI[playerid][pi_RP_NAME], GetVehicleNameByModelid(modelid));
		}
	}
	return 1;
}

hook OnPlayerOpenProperty(playerid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_OPEN_PDOOR, PI[playerid][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlayerCloseProperty(playerid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_OPEN_PDOOR, PI[playerid][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlayerCarryWeapon(playerid, weaponid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid),
		itemid = GetInvItemIdFromWeaponID(weaponid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_CARRY_WEAPON, PI[playerid][pi_RP_NAME], GetItemName(i, itemid));
		}
	}
	return 1;
}

hook OnPlayerUncarryWeapon(playerid, weaponid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid),
		itemid = GetInvItemIdFromWeaponID(weaponid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_UNCARRY_WEAPON, PI[playerid][pi_RP_NAME], GetItemName(i, itemid));
		}
	}
	return 1;
}

hook OnPlayerOpenGps(playerid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_OPEN_GPS, PI[playerid][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlayerCloseGps(playerid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_CLOSE_GPS, PI[playerid][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlayerOpenPhone(playerid, bool:calling)
{
	if(!calling)
	{
		new 
			Float:x, Float:y, Float:z,
			current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

		GetPlayerPos(playerid, x, y, z);
		foreach(new i : Player)
		{
			if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
			if(GetPlayerVirtualWorld(i) != current_vw) continue;
			if(GetPlayerInterior(i) != current_int) continue;
			
			if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
			{
				Text_Send(i, $MESSAGE_ACTION_OPEN_PHONE, PI[playerid][pi_RP_NAME]);
			}
		}
	}
	return 1;
}

hook OnPlayerClosePhone(playerid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_CLOSE_PHONE, PI[playerid][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlayerAttachToy(playerid, toy_index)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_TOY_ATTACH, PI[playerid][pi_RP_NAME], GetItemName(i, pToys[playerid][toy_index][ptoy_INV_ITEMID]));
		}
	}
	return 1;
}

hook OnPlayerRemoveToy(playerid, toy_index)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_TOY_REMOVE, PI[playerid][pi_RP_NAME], GetItemName(i, pToys[playerid][toy_index][ptoy_INV_ITEMID]));
		}
	}
	return 1;
}

hook OnPlayerEat(playerid, itemid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_EAT, PI[playerid][pi_RP_NAME], GetItemName(i, itemid));
		}
	}
	return 1;
}

hook OnPlayerDrink(playerid, itemid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_DRINK, PI[playerid][pi_RP_NAME], GetItemName(i, itemid));
		}
	}
	return 1;
}

hook OnPlayerClothesChange(playerid, index)
{
	if(index != -1)
	{
		new 
			Float:x, Float:y, Float:z,
			current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

		GetPlayerPos(playerid, x, y, z);
		foreach(new i : Player)
		{
			if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
			if(GetPlayerVirtualWorld(i) != current_vw) continue;
			if(GetPlayerInterior(i) != current_int) continue;
			
			if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
			{
				Text_Send(i, $MESSAGE_ACTION_CLOTHES_CHANGE, PI[playerid][pi_RP_NAME]);
			}
		}
	}
	return 1;
}

hook OnPlayerRemoveClothes(playerid, index, CLOTHES_TYPES:id_clothe)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_CLOTHES_DELETE, PI[playerid][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlayerGpsToTaxiDriver(playerid, taxi_driver)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_GPS_TAXI_SHOW, PI[playerid][pi_RP_NAME], PI[taxi_driver][pi_RP_NAME]);
		}
	}
	return 1;
}

hook OnPlayerCheckTime(playerid)
{
	new 
		Float:x, Float:y, Float:z,
		current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
		if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
		if(GetPlayerVirtualWorld(i) != current_vw) continue;
		if(GetPlayerInterior(i) != current_int) continue;
		
		if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
		{
			Text_Send(i, $MESSAGE_ACTION_WATCH, PI[playerid][pi_RP_NAME]);
		}
	}
	return 1;
}

YCMD:me(playerid, params[], help)
{
	new action[145];
	if(!sscanf(params, "s[145]", action))
	{
		new 
			Float:x, Float:y, Float:z,
			current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

		GetPlayerPos(playerid, x, y, z);
		foreach(new i : Player)
		{
			if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
			if(GetPlayerVirtualWorld(i) != current_vw) continue;
			if(GetPlayerInterior(i) != current_int) continue;
			
			if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
			{
				Text_Send(i, $MESSAGE_ACTION_ACTION, PI[playerid][pi_RP_NAME], action);
			}
		}
	}
	else Text_Send(playerid, $MESSAGE_ERROR_SYNTAX);
	return 1;
}

YCMD:do(playerid, params[], help)
{
	new action[145];
	if(!sscanf(params, "s[145]", action))
	{
		new 
			Float:x, Float:y, Float:z,
			current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

		GetPlayerPos(playerid, x, y, z);
		foreach(new i : Player)
		{
			if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
			if(GetPlayerVirtualWorld(i) != current_vw) continue;
			if(GetPlayerInterior(i) != current_int) continue;
			
			if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
			{
				Text_Send(i, $MESSAGE_ACTION_DO, PI[playerid][pi_RP_NAME], action);
			}
		}
	}
	else Text_Send(playerid, $MESSAGE_ERROR_SYNTAX);
	return 1;
}

YCMD:b(playerid, params[], help)
{
	new action[145];
	if(!sscanf(params, "s[145]", action))
	{
		new 
			Float:x, Float:y, Float:z,
			current_vw = GetPlayerVirtualWorld(playerid), current_int = GetPlayerInterior(playerid);

		GetPlayerPos(playerid, x, y, z);
		foreach(new i : Player)
		{
			if(GetPlayerGameState(i) < GAME_STATE_SPAWNED) continue;
			if(GetPlayerVirtualWorld(i) != current_vw) continue;
			if(GetPlayerInterior(i) != current_int) continue;
			
			if(IsPlayerInRangeOfPoint(i, ACTION_DISTANCE, x, y, z))
			{
				Text_Send(i, $MESSAGE_ACTION_BCHANNEL, PI[playerid][pi_NAME], playerid, action);
			}
		}
	}
	else Text_Send(playerid, $MESSAGE_ERROR_SYNTAX);
	return 1;
}