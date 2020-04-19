#include <YSI\y_hooks>

hook OnScriptInit()
{
	inline OnVehiclesLoading()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i > MAX_SERVER_VEHICLES)
				{
					printf("[ERROR]: MAX_SERVER_VEHICLES superado en 'OnVehiclesLoading', max: %d", MAX_SERVER_VEHICLES);
					break;
				}

				new bool:isnull_id_player, bool:isnull_id_job_point,
					id, modelid, type, number_plate[32], Float:fuel, addsiren,
					Float:health, Float:distance, Float:spawn_pos_x, Float:spawn_pos_y,
					Float:spawn_pos_z, Float:spawn_angle, interiorid, worldid, color1, color2,
					paintjob, damage_panels, damage_doors, damage_lights, damage_tires,
					params_engine, params_lights, params_alarm, params_doors, params_bonnet,
					params_boot, params_objective, radio, game_state, id_player, price, level, id_job_point;

				cache_get_value_name_int(i, "id", id);
				cache_get_value_name_int(i, "modelid", modelid);
				cache_get_value_name_int(i, "type", type);
				cache_get_value_name(i, "number_plate", number_plate);
				cache_get_value_name_float(i, "fuel", fuel);
				cache_get_value_name_int(i, "addsiren", addsiren);
				cache_get_value_name_float(i, "health", health);
				cache_get_value_name_float(i, "distance", distance);
				cache_get_value_name_float(i, "spawn_pos_x", spawn_pos_x);
				cache_get_value_name_float(i, "spawn_pos_y", spawn_pos_y);
				cache_get_value_name_float(i, "spawn_pos_z", spawn_pos_z);
				cache_get_value_name_float(i, "spawn_angle", spawn_angle);
				cache_get_value_name_int(i, "interiorid", interiorid);
				cache_get_value_name_int(i, "worldid", worldid);
				cache_get_value_name_int(i, "color1", color1);
				cache_get_value_name_int(i, "color2", color2);
				cache_get_value_name_int(i, "paintjob", paintjob);
				cache_get_value_name_int(i, "damage_panels", damage_panels);
				cache_get_value_name_int(i, "damage_doors", damage_doors);
				cache_get_value_name_int(i, "damage_lights", damage_lights);
				cache_get_value_name_int(i, "damage_tires", damage_tires);
				cache_get_value_name_int(i, "params_engine", params_engine);
				cache_get_value_name_int(i, "params_lights", params_lights);
				cache_get_value_name_int(i, "params_alarm", params_alarm);
				cache_get_value_name_int(i, "params_doors", params_doors);
				cache_get_value_name_int(i, "params_bonnet", params_bonnet);
				cache_get_value_name_int(i, "params_boot", params_boot);
				cache_get_value_name_int(i, "params_objective", params_objective);
				cache_get_value_name_int(i, "radio", radio);
				cache_get_value_name_int(i, "game_state", game_state);
				cache_is_value_name_null(i, "id_player", isnull_id_player);
				if(!isnull_id_player) cache_get_value_name_int(i, "id_player", id_player);
				cache_get_value_name_int(i, "price", price);
				cache_get_value_name_int(i, "level", level);
				cache_is_value_name_null(i, "id_job_point", isnull_id_job_point);
				if(!isnull_id_job_point) cache_get_value_name_int(i, "id_job_point", id_job_point);
				
				damage_panels = 0;
				damage_doors = 0;
				damage_lights = 0;
				damage_tires = 0;
				params_engine = 0;
				params_lights = 0;
				params_alarm = 0;
				params_doors = 0;
				params_bonnet = 0;
				params_boot = 0;
				fuel = GetVehicleMaxFuelByModelid(modelid);
				health = 1000.0;
				game_state = _:VEHICLE_GAME_STATE_NORMAL;

				if(isnull(number_plate)) number_plate = "random";

				//
				new slot = Iter_Free(VehicleInfo);
				if(slot != cellmin)
				{
					VehicleInfo[slot][vinfo_STATE] = VEHICLE_STATE_SPAWNED;
					VehicleInfo[slot][vinfo_MODELID] = modelid;
					VehicleInfo[slot][vinfo_TYPE] = VEHICLE_TYPES:type;
					VehicleInfo[slot][vinfo_DRIVER] = INVALID_PLAYER_ID;
					format(VehicleInfo[slot][vinfo_NUMBER_PLATE], 32, "%s", number_plate);
					if(!strcmp(VehicleInfo[slot][vinfo_NUMBER_PLATE], "random")) format(VehicleInfo[slot][vinfo_NUMBER_PLATE], 32, "%c%c%d-%05d", getRandomLetter(), getRandomLetter(), getRandomLetter(), random(1000000));
					VehicleInfo[slot][vinfo_FUEL] = fuel;
					if(VehicleInfo[slot][vinfo_FUEL] == -1 || VehicleInfo[slot][vinfo_FUEL] > GetVehicleMaxFuelByModelid(modelid)) VehicleInfo[slot][vinfo_FUEL] = GetVehicleMaxFuelByModelid(modelid);
					VehicleInfo[slot][vinfo_RESPAWN_DELAY] = DEFAULT_VEHICLE_RESPAWN_DELAY;
					VehicleInfo[slot][vinfo_ADDSIREN] = addsiren;
					VehicleInfo[slot][vinfo_HEALTH] = health;
					if(VehicleInfo[slot][vinfo_HEALTH] < MIN_VEHICLE_HEALTH) VehicleInfo[slot][vinfo_HEALTH] = MIN_VEHICLE_HEALTH;
					VehicleInfo[slot][vinfo_DISTANCE] = distance;
					if(VehicleInfo[slot][vinfo_DISTANCE] == -1.0) VehicleInfo[slot][vinfo_DISTANCE] = float(minrand(50000, 200000) * 1000);
					VehicleInfo[slot][vinfo_RADIO] = radio;
					if(VehicleInfo[slot][vinfo_RADIO] == -1) VehicleInfo[slot][vinfo_RADIO] = random(sizeof Radios);
					VehicleInfo[slot][vinfo_GAME_STATE] = VEHICLE_GAME_STATES:game_state;

					VehicleInfo[slot][vinfo_SPAWN_POS][0] = spawn_pos_x;
					VehicleInfo[slot][vinfo_SPAWN_POS][1] = spawn_pos_y;
					VehicleInfo[slot][vinfo_SPAWN_POS][2] = spawn_pos_z;
					VehicleInfo[slot][vinfo_SPAWN_ANGLE] = spawn_angle;
					VehicleInfo[slot][vinfo_POS][0] = spawn_pos_x;
					VehicleInfo[slot][vinfo_POS][1] = spawn_pos_y;
					VehicleInfo[slot][vinfo_POS][2] = spawn_pos_z;
					VehicleInfo[slot][vinfo_ANGLE] = spawn_angle;
					VehicleInfo[slot][vinfo_INTERIORID] = interiorid;
					VehicleInfo[slot][vinfo_WORLDID] = worldid;

					VehicleInfo[slot][vinfo_COLOR1] = color1;
					if(VehicleInfo[slot][vinfo_COLOR1] == -1) VehicleInfo[slot][vinfo_COLOR1] = random(255);
					VehicleInfo[slot][vinfo_COLOR2] = color2;
					if(VehicleInfo[slot][vinfo_COLOR2] == -1) VehicleInfo[slot][vinfo_COLOR2] = random(255);
					VehicleInfo[slot][vinfo_PAINTJOB] = paintjob;

					VehicleInfo[slot][vinfo_DAMAGE_PANELS] = damage_panels;
					VehicleInfo[slot][vinfo_DAMAGE_DOORS] = damage_doors;
					VehicleInfo[slot][vinfo_DAMAGE_LIGHTS] = damage_lights;
					VehicleInfo[slot][vinfo_DAMAGE_TIRES] = damage_tires;

					VehicleInfo[slot][vinfo_PARAMS_ENGINE] = params_engine;
					VehicleInfo[slot][vinfo_PARAMS_LIGHTS] = params_lights;
					VehicleInfo[slot][vinfo_PARAMS_ALARM] = params_alarm;
					VehicleInfo[slot][vinfo_PARAMS_DOORS] = params_doors;
					VehicleInfo[slot][vinfo_PARAMS_BONNET] = params_bonnet;
					VehicleInfo[slot][vinfo_PARAMS_BOOT] = params_boot;
					VehicleInfo[slot][vinfo_PARAMS_OBJECTIVE] = params_objective;

					if(!VehicleModelHasEngine(VehicleInfo[slot][vinfo_MODELID])) VehicleInfo[slot][vinfo_PARAMS_ENGINE] = 1;
					if(!VehicleModelHasDoors(VehicleInfo[slot][vinfo_MODELID])) VehicleInfo[slot][vinfo_PARAMS_DOORS] = 0;

					VehicleInfo[slot][vinfo_ID] = id;
					VehicleInfo[slot][vinfo_ID_PLAYER] = id_player;
					VehicleInfo[slot][vinfo_PRICE] = price;
					VehicleInfo[slot][vinfo_LEVEL] = level;
					VehicleInfo[slot][vinfo_ID_JOB_POINT] = id_job_point;
					VehicleInfo[slot][vinfo_VEHICLE_ID] = INVALID_VEHICLE_ID;

					Iter_Add(VehicleInfo, slot);
					CallRemoteFunction("OnVehicleInfoLoad", "d", slot);
				}
			}
			printf("[OK]: vehicles info cargado (%d, max: %d)", rows, MAX_SERVER_VEHICLES);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnVehiclesLoading' (db error)");
		}
	}
	print("[INFO]: Cargando vehicles info...");
	mysql_tquery_inline(vcrp_db, "SELECT vehicles.* FROM vehicles INNER JOIN vehicle_types ON vehicles.type = vehicle_types.id WHERE vehicle_types.load_init = 1;", using inline OnVehiclesLoading, "");
	return 1;
}

hook OnVehicleInfoLoad(vehindex)
{
	if(!CreateVehicleFromInfo(vehindex))
	DestroyVehicleEx(vehindex);
	return 1;
}

hook OnVehicleSpawn(vehicleid)
{
	new vehicle_index = GetVehicleIndexByVehicleid(vehicleid);
	if(vehicle_index != INVALID_VEHICLE_INDEX)
	{
		
		VehicleInfo[vehicle_index][vinfo_PARAMS_ENGINE] = 0;
		VehicleInfo[vehicle_index][vinfo_PARAMS_LIGHTS] = 0;
		VehicleInfo[vehicle_index][vinfo_PARAMS_ALARM] = 0;
		VehicleInfo[vehicle_index][vinfo_PARAMS_BONNET] = 0;
		VehicleInfo[vehicle_index][vinfo_PARAMS_BOOT] = 0;
		VehicleInfo[vehicle_index][vinfo_PARAMS_OBJECTIVE] = 0;
		if(VehicleInfo[vehicle_index][vinfo_TYPE] != VEHICLE_TYPE_PLAYER)
		{
			VehicleInfo[vehicle_index][vinfo_HEALTH] = 1000.0;
			VehicleInfo[vehicle_index][vinfo_PARAMS_DOORS] = 0;
			VehicleInfo[vehicle_index][vinfo_FUEL] = GetVehicleMaxFuelByModelid(VehicleInfo[vehicle_index][vinfo_MODELID]);
		}
		else
		{
			if(VehicleInfo[vehicle_index][vinfo_HEALTH] < MIN_VEHICLE_HEALTH) VehicleInfo[vehicle_index][vinfo_HEALTH] = MIN_VEHICLE_HEALTH;
		}
		SetVehicleWorldSpawnInfo(vehicle_index);
		SetVehicleVariables(vehicle_index);
		VehicleInfo[vehicle_index][vinfo_STATE] = VEHICLE_STATE_SPAWNED;
		CallRemoteFunction("OnVehicleSpawnEx", "i", vehicle_index);
	}
	return 1;
}

hook OnVehicleDeath(vehicleid, killerid)
{
	new vehicle_index = GetVehicleIndexByVehicleid(vehicleid);
	if(vehicle_index != INVALID_VEHICLE_INDEX)
	{
		VehicleInfo[vehicle_index][vinfo_STATE] = VEHICLE_STATE_DEAD;
		CallRemoteFunction("OnVehicleDeathEx", "ii", vehicle_index, killerid);
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(pVehicleIndex[playerid] != INVALID_VEHICLE_INDEX)
	{
		if(VehicleInfo[pVehicleIndex[playerid]][vinfo_DRIVER] == playerid) VehicleInfo[pVehicleIndex[playerid]][vinfo_DRIVER] = INVALID_PLAYER_ID;
		pVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
	}
	pLastVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		new vehicle_index = GetVehicleIndexByVehicleid(GetPlayerVehicleID(playerid));
		if(newstate == PLAYER_STATE_DRIVER) VehicleInfo[vehicle_index][vinfo_DRIVER] = playerid;
		pVehicleIndex[playerid] = vehicle_index;
		pLastVehicleIndex[playerid] = vehicle_index;
		CallRemoteFunction("OnPlayerGetVehicleIndex", "i", playerid);
	}
	else
	{
		if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
		{
			if(VehicleInfo[pVehicleIndex[playerid]][vinfo_DRIVER] == playerid) VehicleInfo[pVehicleIndex[playerid]][vinfo_DRIVER] = INVALID_PLAYER_ID;
			pVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
		}
	}
	return 1;
}

hook OnPlayerVehicleChange(playerid, from_vehicleid, to_vehicleid)
{
	if(to_vehicleid != INVALID_OPVC_VEHICLE_ID && GetPlayerVehicleIndex(playerid) != INVALID_VEHICLE_INDEX)
	{
		if(VehicleInfo[GetPlayerVehicleIndex(playerid)][vinfo_VEHICLE_ID] != to_vehicleid)
		{
			if(VehicleInfo[GetPlayerVehicleIndex(playerid)][vinfo_DRIVER] == playerid)
			{
				VehicleInfo[GetPlayerVehicleIndex(playerid)][vinfo_DRIVER] = INVALID_PLAYER_ID;
			}
			new vehicle_index = GetVehicleIndexByVehicleid(GetPlayerVehicleID(playerid));
			VehicleInfo[vehicle_index][vinfo_DRIVER] = playerid;
			pVehicleIndex[playerid] = vehicle_index;
			pLastVehicleIndex[playerid] = vehicle_index;
		}
	}
	return 1;
}