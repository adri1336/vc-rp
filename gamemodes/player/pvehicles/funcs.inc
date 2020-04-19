CountPlayerVehicles(playerid, bool:only_own_vehs = true)
{
	new c;
	if(only_own_vehs)
	{
		foreach(new i : PlayerVehicles[playerid])
		{	
			if(VehicleInfo[i][vinfo_TYPE] == VEHICLE_TYPE_PLAYER)
			{	
				if(VehicleInfo[i][vinfo_ID_PLAYER] == PI[playerid][pi_ID])
				c++;
			}
		}
	}
	else
	{
		c = Iter_Count(PlayerVehicles[playerid]);
	}
	return c;
}

GivePlayerPrivateVehicle(playerid, price, level, modelid, Float:x, Float:y, Float:z, Float:angle = 0.0, interiorid = 0, worldid = 0, color1 = 1, color2 = 1)
{
	inline OnVehicleInserted()
	{
		new id = cache_insert_id();
		
		//inv
		new inv_params[24];
		format(inv_params, sizeof inv_params, "%d,%d", id, modelid);
		AddPlayerInventoryItem(playerid, _:INV_ITEM_VEHICLE_MASTER_KEY, inv_params);

		new index = CreateVehicleEx
		(
			VEHICLE_TYPE_PLAYER,
			modelid,
			x,
			y,
			z,
			angle,
			color1,
			color2,
			.interiorid = interiorid,
			.worldid = worldid,
			.id = id,
			.id_player = PI[playerid][pi_ID],
			.price = price,
			.level = level,
			.distance = 0.0
		);
		Iter_Add(PlayerVehicles[playerid], index);
		PutPlayerInVehicle(playerid, VehicleInfo[index][vinfo_VEHICLE_ID], 0);
	}

	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO vehicles (modelid, type, fuel, distance, spawn_pos_x, spawn_pos_y, spawn_pos_z, spawn_angle, interiorid, worldid, color1, color2, id_player, price, level) VALUES (%d, %d, %f, %f, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d, %d);", modelid, _:VEHICLE_TYPE_PLAYER, GetVehicleMaxFuelByModelid(modelid), 0.0, x, y, z, angle, interiorid, worldid, color1, color2, PI[playerid][pi_ID], price, level);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnVehicleInserted, "");
	return 1;
}

LoadPlayerVehicles(playerid)
{
	new count, vids[MAX_VEHICLES] = {-1, ...}, string[24];
	QUERY_BUFFER[0] = EOS;
	format(QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM vehicles WHERE (");
	foreach(new i : PINV[playerid])
	{
		if(PINV[playerid][i][pinv_ITEM_ID] == _:INV_ITEM_VEHICLE_MASTER_KEY || PINV[playerid][i][pinv_ITEM_ID] == _:INV_ITEM_VEHICLE_KEY || PINV[playerid][i][pinv_ITEM_ID] == _:INV_ITEM_VEHICLE_RENT_KEY)
		{
			new vid, vmodelid;
			sscanf(PINV[playerid][i][pinv_PARAMS], "p<,>dd", vid, vmodelid);
			if(vid && vmodelid)
			{
				if(count == 0) format(string, 24, "id = %d", vid);
				else format(string, 24, " OR id = %d", vid);
				strcat(QUERY_BUFFER, string);
				vids[count] = vid;
				count ++;
			}
		}
	}
	strcat(QUERY_BUFFER, ") AND created = 0;");

	if(count > 0)
	{
		inline OnPlayerVehiclesLoad()
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				for(new i = 0; i != rows; i ++)
				{
					new 
						id,
						modelid,
						Float:fuel,
						addsiren,
						Float:health,
						Float:distance,
						Float:spawn_pos_x,
						Float:spawn_pos_y,
						Float:spawn_pos_z,
						Float:spawn_angle,
						interiorid,
						worldid,
						color1,
						color2,
						paintjob,
						damage_panels,
						damage_doors,
						damage_lights,
						damage_tires,
						params_engine,
						params_lights,
						params_alarm,
						params_doors,
						params_bonnet,
						params_boot,
						params_objective,
						radio,
						game_state,
						price,
						level;

					cache_get_value_name_int(i, "id", id);
					cache_get_value_name_int(i, "modelid", modelid);
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
					//cache_get_value_name_int(i, "params_engine", params_engine);
					//cache_get_value_name_int(i, "params_lights", params_lights);
					//cache_get_value_name_int(i, "params_alarm", params_alarm);
					cache_get_value_name_int(i, "params_doors", params_doors);
					//cache_get_value_name_int(i, "params_bonnet", params_bonnet);
					//cache_get_value_name_int(i, "params_boot", params_boot);
					//cache_get_value_name_int(i, "params_objective", params_objective);
					cache_get_value_name_int(i, "radio", radio);
					cache_get_value_name_int(i, "game_state", game_state);
					cache_get_value_name_int(i, "price", price);
					cache_get_value_name_int(i, "level", level);

					CreateVehicleEx
					(
						VEHICLE_TYPE_PLAYER,
						modelid,
						spawn_pos_x,
						spawn_pos_y,
						spawn_pos_z,
						spawn_angle,
						color1,
						color2,
						-1,
						addsiren,
						"random",
						fuel,
						health,
						interiorid,
						worldid,
						paintjob,
						damage_panels,
						damage_doors,
						damage_lights,
						damage_tires,
						params_engine,
						params_lights,
						params_alarm,
						params_doors,
						params_bonnet,
						params_boot,
						params_objective,
						distance,
						radio,
						VEHICLE_GAME_STATES:game_state,
						id,
						PI[playerid][pi_ID],
						price,
						level
					);

					//tune
					//SetVehicleComponents(index);
				}

				for(new i = 0; i < MAX_VEHICLES; i ++)
				{
					if(vids[i] == -1)
					break;

					new vehicle_index = GetVehicleIndexById(vids[i]);
					if(vehicle_index != INVALID_VEHICLE_INDEX)
					Iter_Add(PlayerVehicles[playerid], vehicle_index);
				}
			}
		}
		mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnPlayerVehiclesLoad, "");
	}
	return 1;
}

DestroyPlayerVehicles(playerid, bool:update)
{
	foreach(new i : PlayerVehicles[playerid])
	{
		if(VehicleInfo[i][vinfo_TYPE] == VEHICLE_TYPE_PLAYER)
		{
			new count;
			foreach(new j : Player)
			{
				if(j == playerid) continue;
				if(Iter_Contains(PlayerVehicles[j], i))
				{
					count ++;
					break;
				}
			}
			if(count == 0)
			{
				if(update)
				{
					UpdateVehicleInfo(i, true);
					UpdateVehicleInfoDb(i);
				}
				DestroyVehicleEx(i);
			}
		}
	}
	return 1;
}