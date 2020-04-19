#include <YSI\y_hooks>

YCMD:vtypes(playerid, params[], help)
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			new dialog_message[256], line_str[45];
			for(new i = 0; i != rows; i ++)
			{
				new id, name[24];	
				cache_get_value_name_int(i, "id", id);
				cache_get_value_name(i, "name", name, 24);
				format(line_str, sizeof line_str, "ID: %d Type: %s\n", id, name);
				strcat(dialog_message, line_str);
			}
			inline OnPlayerDialog(pid, did, res, lis, string:inp)
			{
				#pragma unused pid, did, res, lis, inp
			}
			Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "Vehicle types", dialog_message, "X", "");
		}
	}
	mysql_tquery_inline(vcrp_db, "SELECT * FROM vehicle_types;", using inline OnQueryLoad, "");
	return 1;
}

YCMD:aveh(playerid, params[], help)
{
	new model_name[24], modelid = -1, type = -1, siren, Float:distance = -1.0, color1 = -1, color2 = -1, paintjob = 3, price, level;
	if(sscanf(params, "dddfddddd", modelid, type, siren, distance, color1, color2, paintjob, price, level))
	sscanf(params, "s[24]ddfddddd", model_name, type, siren, distance, color1, color2, paintjob, price, level);
	if(modelid == -1 && type == -1) return SendClientMessage(playerid, -1, "Syntax: /aveh <modelid/modelname> <type> <siren=0> <distance=-1> <color1=-1> <color2=-1> <paintjob=3> <price=0> <level=0>");

	if(!isnull(model_name)) modelid = GetVehicleModelidByName(model_name);
	if(IsValidVehicleModelId(modelid))
	{
		new index = Iter_Free(VehicleInfo);
		if(index != cellmin)
		{
			inline OnQueryLoad()
			{
				new rows;
				if(cache_get_row_count(rows))
				{
					if(rows)
					{
						if(IsValidVehiclePaintjob(paintjob))
						{
							new Float:pos[3], Float:angle, worldid = GetPlayerVirtualWorld(playerid), interiorid = GetPlayerInterior(playerid);
							GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
							GetPlayerFacingAngle(playerid, angle);

							inline OnVehicleInserted()
							{
								VehicleInfo[index][vinfo_ID] = cache_insert_id();
								VehicleInfo[index][vinfo_STATE] = VEHICLE_STATE_SPAWNED;
								VehicleInfo[index][vinfo_MODELID] = modelid;
								VehicleInfo[index][vinfo_TYPE] = VEHICLE_TYPES:type;
								VehicleInfo[index][vinfo_DRIVER] = INVALID_PLAYER_ID;
								format(VehicleInfo[index][vinfo_NUMBER_PLATE], 32, "%c%c%d-%05d", getRandomLetter(), getRandomLetter(), getRandomLetter(), random(1000000));
								VehicleInfo[index][vinfo_FUEL] = GetVehicleMaxFuelByModelid(modelid);
								VehicleInfo[index][vinfo_RESPAWN_DELAY] = DEFAULT_VEHICLE_RESPAWN_DELAY;
								VehicleInfo[index][vinfo_ADDSIREN] = siren;
								VehicleInfo[index][vinfo_HEALTH] = 1000.0;
								VehicleInfo[index][vinfo_DISTANCE] = distance;
								if(VehicleInfo[index][vinfo_DISTANCE] == -1.0) VehicleInfo[index][vinfo_DISTANCE] = float(minrand(50000, 200000) * 1000);
								VehicleInfo[index][vinfo_RADIO] = random(sizeof Radios);
								VehicleInfo[index][vinfo_GAME_STATE] = VEHICLE_GAME_STATE_NORMAL;

								VehicleInfo[index][vinfo_SPAWN_POS][0] = pos[0];
								VehicleInfo[index][vinfo_SPAWN_POS][1] = pos[1];
								VehicleInfo[index][vinfo_SPAWN_POS][2] = pos[2];
								VehicleInfo[index][vinfo_SPAWN_ANGLE] = angle;
								VehicleInfo[index][vinfo_POS][0] = pos[0];
								VehicleInfo[index][vinfo_POS][1] = pos[1];
								VehicleInfo[index][vinfo_POS][2] = pos[2];
								VehicleInfo[index][vinfo_ANGLE] = angle;
								VehicleInfo[index][vinfo_INTERIORID] = interiorid;
								VehicleInfo[index][vinfo_WORLDID] = worldid;

								VehicleInfo[index][vinfo_COLOR1] = color1;
								if(VehicleInfo[index][vinfo_COLOR1] == -1) VehicleInfo[index][vinfo_COLOR1] = random(255);
								VehicleInfo[index][vinfo_COLOR2] = color2;
								if(VehicleInfo[index][vinfo_COLOR2] == -1) VehicleInfo[index][vinfo_COLOR2] = random(255);
								VehicleInfo[index][vinfo_PAINTJOB] = paintjob;

								VehicleInfo[index][vinfo_DAMAGE_PANELS] = 0;
								VehicleInfo[index][vinfo_DAMAGE_DOORS] = 0;
								VehicleInfo[index][vinfo_DAMAGE_LIGHTS] = 0;
								VehicleInfo[index][vinfo_DAMAGE_TIRES] = 0;

								VehicleInfo[index][vinfo_PARAMS_ENGINE] = 0;
								VehicleInfo[index][vinfo_PARAMS_LIGHTS] = 0;
								VehicleInfo[index][vinfo_PARAMS_ALARM] = 0;
								VehicleInfo[index][vinfo_PARAMS_DOORS] = 0;
								VehicleInfo[index][vinfo_PARAMS_BONNET] = 0;
								VehicleInfo[index][vinfo_PARAMS_BOOT] = 0;
								VehicleInfo[index][vinfo_PARAMS_OBJECTIVE] = 0;

								if(!VehicleModelHasEngine(VehicleInfo[index][vinfo_MODELID])) VehicleInfo[index][vinfo_PARAMS_ENGINE] = 1;
								if(!VehicleModelHasDoors(VehicleInfo[index][vinfo_MODELID])) VehicleInfo[index][vinfo_PARAMS_DOORS] = 0;
								
								VehicleInfo[index][vinfo_ID_PLAYER] = 0;
								VehicleInfo[index][vinfo_PRICE] = price;
								VehicleInfo[index][vinfo_LEVEL] = level;
								VehicleInfo[index][vinfo_VEHICLE_ID] = INVALID_VEHICLE_ID;

								Iter_Add(VehicleInfo, index);
								CallRemoteFunction("OnVehicleInfoLoad", "d", index);
								
								//
								new msg[128];
								format(msg, sizeof msg, "Vehicle added (ID: %d)!", VehicleInfo[index][vinfo_ID]);
								SendClientMessage(playerid, -1, msg);
							}
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, 
								"\
									INSERT INTO vehicles (modelid, type, fuel, addsiren, distance, spawn_pos_x, spawn_pos_y, spawn_pos_z, spawn_angle, interiorid, worldid, color1, color2, paintjob, price, level) \
									VALUES (%d, %d, %f, %d, %f, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d, %d);\
								",
									modelid, type, GetVehicleMaxFuelByModelid(modelid), siren, distance, pos[0], pos[1], pos[2], angle, interiorid, worldid, color1, color2, paintjob, price, level
							);
							mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnVehicleInserted, "");
						}
						else SendClientMessage(playerid, -1, "Invalid paintjob ID!");
					}
					else SendClientMessage(playerid, -1, "Invalid type ID!");
				}			
			}
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT COUNT(*) FROM vehicle_types WHERE id = %d;", type);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
		}
		else SendClientMessage(playerid, -1, "Array full!");
	}
	else SendClientMessage(playerid, -1, "Invalid vehicle modelid!");
	return 1;
}

YCMD:uvehpos(playerid, params[], help)
{
	new vid = 0;
	if(!sscanf(params, "d", params[0])) vid = params[0];
	else
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new index = GetPlayerVehicleIndex(playerid);
			if(index != INVALID_VEHICLE_INDEX) vid = VehicleInfo[index][vinfo_ID];
		}
	}

	new index = GetVehicleIndexById(vid);
	if(index == INVALID_VEHICLE_INDEX) SendClientMessage(playerid, -1, "Invalid vehicle ID!");
	else
	{
		if(VehicleInfo[index][vinfo_VEHICLE_ID] != INVALID_VEHICLE_ID)
		{
			GetVehiclePos(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_POS][0], VehicleInfo[index][vinfo_POS][1], VehicleInfo[index][vinfo_POS][2]);
			GetVehicleZAngle(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_ANGLE]);
			VehicleInfo[index][vinfo_WORLDID] = GetVehicleVirtualWorld(VehicleInfo[index][vinfo_VEHICLE_ID]);
			VehicleInfo[index][vinfo_SPAWN_POS] = VehicleInfo[index][vinfo_POS];
			VehicleInfo[index][vinfo_SPAWN_ANGLE] = VehicleInfo[index][vinfo_ANGLE];

			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET spawn_pos_x = %f, spawn_pos_y = %f, spawn_pos_z = %f, spawn_angle = %f, worldid = %d WHERE id = %d;", VehicleInfo[index][vinfo_SPAWN_POS][0], VehicleInfo[index][vinfo_SPAWN_POS][1], VehicleInfo[index][vinfo_SPAWN_POS][2], VehicleInfo[index][vinfo_SPAWN_ANGLE], VehicleInfo[index][vinfo_WORLDID], VehicleInfo[index][vinfo_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);
			SendClientMessage(playerid, -1, "Vehicle position updated!");
		}
		else SendClientMessage(playerid, -1, "Vehicle not created!");
	}
	return 1;
}

YCMD:atveh(playerid, params[], help)
{
	if(isnull(params)) SendClientMessage(playerid, -1, "Syntax: /atveh [modelid/name]");
	else
	{
		if(!sscanf(params, "d", params[0]))
		{
			if(IsValidVehicleModelId(params[0]))
			{
				SavePlayerWorldInfo(playerid);
				new index = CreateVehicleEx(VEHICLE_TYPE_NONE, params[0], PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], .interiorid = PI[playerid][pi_INTERIORID], .worldid = PI[playerid][pi_WORLDID], .params_engine = 1);
				if(index == INVALID_VEHICLE_INDEX) SendClientMessage(playerid, -1, "Error: INVALID_VEHICLE_INDEX");
				else
				{
					new string[128];
					format(string, sizeof string, "Test vehicle created (ID: %d)!", VehicleInfo[index][vinfo_ID]);
					SendClientMessage(playerid, -1, string);
					PutPlayerInVehicle(playerid, VehicleInfo[index][vinfo_VEHICLE_ID], 0);
				}
			}
			else
			{
				new string[64];
				format(string, sizeof string, "Invalid modelid %d!", params[0]);
				SendClientMessage(playerid, -1, string);
			}
		}
		else
		{
			new modelid = GetVehicleModelidByName(params);
			if(modelid == -1)
			{
				new string[64];
				format(string, sizeof string, "Invalid modelid %s!", params);
				SendClientMessage(playerid, -1, string);
			}
			else
			{
				SavePlayerWorldInfo(playerid);
				new index = CreateVehicleEx(VEHICLE_TYPE_NONE, modelid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], .interiorid = PI[playerid][pi_INTERIORID], .worldid = PI[playerid][pi_WORLDID], .params_engine = 1, .distance = 0.0);
				if(index == INVALID_VEHICLE_INDEX) SendClientMessage(playerid, -1, "Error: INVALID_VEHICLE_INDEX");
				else
				{
					new string[128];
					format(string, sizeof string, "Test vehicle created (ID: %d)!", VehicleInfo[index][vinfo_ID]);
					SendClientMessage(playerid, -1, string);
					PutPlayerInVehicle(playerid, VehicleInfo[index][vinfo_VEHICLE_ID], 0);
				}
			}
		}
	}
	return 1;
}

YCMD:iveh(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) SendClientMessage(playerid, -1, "Syntax: /iveh [ID]");
	else
	{
		new index = GetVehicleIndexById(params[0]);
		if(index == INVALID_VEHICLE_INDEX) SendClientMessage(playerid, -1, "Invalid vehicle ID!");
		else
		{
			inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
			{
				#pragma unused pid, dialogid, response, listitem, inputtext
			}

			UpdateVehicleInfo(index);

			new dialog_message[1024];
			format
			(
				dialog_message,
				sizeof dialog_message,
				"\
					ID: %d\n\
					--- MODEL INFO ---\n\
					vehicleid: %d\n\
					modelid: %d\n\
					name: %s\n\
					group: %d\n\
					max_speed: %d\n\
					max_fuel: %.2f\n\
					seats: %d\n\
					\n\
					--- VEHICLE INFO ---\n\
					index: %d\n\
					type: %d\n\
					state: %d\n\
					driver: %d\n\
					number_plate: %s\n\
					fuel: %.2f\n\
					respawn_delay: %d\n\
					addsiren: %d\n\
					health: %.2f\n\
					distance: %.2f\n\
					spawn_pos_x: %.2f\n\
					spawn_pos_y: %.2f\n\
					spawn_pos_z: %.2f\n\
					spawn_angle: %.2f\n\
					pos_x: %.2f\n\
					pos_y: %.2f\n\
					pos_z: %.2f\n\
					angle: %.2f\n\
					interiorid: %d\n\
					worldid: %d\n\
					color1: %d\n\
					color2: %d\n\
					paintjob: %d\n\
					panels damage: %d\n\
					doors damage: %d\n\
					lights damage: %d\n\
					tires damage: %d\n\
					engine params: %d\n\
					lights params: %d\n\
					alarm params: %d\n\
					doors params: %d\n\
					bonnet params: %d\n\
					boot params: %d\n\
					objective params: %d\
				",
					VehicleInfo[index][vinfo_ID],
					VehicleInfo[index][vinfo_VEHICLE_ID],
					GetVehicleModel(VehicleInfo[index][vinfo_VEHICLE_ID]),
					GetVehicleNameByModelid(VehicleInfo[index][vinfo_MODELID]),
					Model_GetCategory(VehicleInfo[index][vinfo_MODELID]),
					Model_TopSpeed(VehicleInfo[index][vinfo_MODELID]),
					GetVehicleMaxFuelByModelid(VehicleInfo[index][vinfo_MODELID]),
					GetVehicleSeatsByModelid(VehicleInfo[index][vinfo_MODELID]),

					index,
					_:VehicleInfo[index][vinfo_TYPE],
					_:VehicleInfo[index][vinfo_STATE],
					VehicleInfo[index][vinfo_DRIVER],
					VehicleInfo[index][vinfo_NUMBER_PLATE],
					VehicleInfo[index][vinfo_FUEL],
					VehicleInfo[index][vinfo_RESPAWN_DELAY],
					VehicleInfo[index][vinfo_ADDSIREN],
					VehicleInfo[index][vinfo_HEALTH],
					VehicleInfo[index][vinfo_DISTANCE],
					VehicleInfo[index][vinfo_SPAWN_POS][0],
					VehicleInfo[index][vinfo_SPAWN_POS][1],
					VehicleInfo[index][vinfo_SPAWN_POS][2],
					VehicleInfo[index][vinfo_SPAWN_ANGLE],
					VehicleInfo[index][vinfo_POS][0],
					VehicleInfo[index][vinfo_POS][1],
					VehicleInfo[index][vinfo_POS][2],
					VehicleInfo[index][vinfo_ANGLE],
					VehicleInfo[index][vinfo_INTERIORID],
					VehicleInfo[index][vinfo_WORLDID],
					VehicleInfo[index][vinfo_COLOR1],
					VehicleInfo[index][vinfo_COLOR2],
					VehicleInfo[index][vinfo_PAINTJOB],
					VehicleInfo[index][vinfo_DAMAGE_PANELS],
					VehicleInfo[index][vinfo_DAMAGE_DOORS],
					VehicleInfo[index][vinfo_DAMAGE_LIGHTS],
					VehicleInfo[index][vinfo_DAMAGE_TIRES],
					VehicleInfo[index][vinfo_PARAMS_ENGINE],
					VehicleInfo[index][vinfo_PARAMS_LIGHTS],
					VehicleInfo[index][vinfo_PARAMS_ALARM],
					VehicleInfo[index][vinfo_PARAMS_DOORS],
					VehicleInfo[index][vinfo_PARAMS_BONNET],
					VehicleInfo[index][vinfo_PARAMS_BOOT],
					VehicleInfo[index][vinfo_PARAMS_OBJECTIVE]
			);
			Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "Vehicle Info", dialog_message, "X");
		}
	}
	return 1;
}

YCMD:ivehs(playerid, params[], help)
{
	new dialog_message[256];
	format(dialog_message, sizeof dialog_message, 
		"Total: %d\nLimit: %d",
		Iter_Count(VehicleInfo), MAX_VEHICLES
	);

	inline OnPlayerDialog(pid, did, res, lis, string:inp)
	{
		#pragma unused pid, did, res, lis, inp
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "Vehicles info", dialog_message, "X", "");
	return 1;
}

YCMD:dtvehs(playerid, params[], help)
{
	new total = DestroyUnusedVehicles();
	new msg[128];
	format(msg, sizeof msg, "Test vehicles destroyed (%d)!", total);
	SendClientMessage(playerid, -1, msg);
	return 1;
}

YCMD:dveh(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) SendClientMessage(playerid, -1, "Syntax: /dveh [ID]");
	else
	{
		new index = GetVehicleIndexById(params[0]);
		if(index == INVALID_VEHICLE_INDEX) SendClientMessage(playerid, -1, "Invalid vehicle ID!");
		else
		{
			DestroyVehicleEx(index, true);
			SendClientMessage(playerid, -1, "Vehicle destroyed!");
		}
	}
	return 1;
}

YCMD:setvehfuel(playerid, params[], help)
{
	new id, Float:fuel;
	if(sscanf(params, "df", id, fuel)) SendClientMessage(playerid, -1, "Syntax: /setvehfuel [ID] [fuel]");
	else
	{
		new index = GetVehicleIndexById(id);
		if(index != INVALID_VEHICLE_INDEX)
		{
			if(fuel < 0.0) fuel = 0.0;
			else if(fuel > GetVehicleMaxFuelByModelid(VehicleInfo[index][vinfo_MODELID])) fuel = GetVehicleMaxFuelByModelid(VehicleInfo[index][vinfo_MODELID]);

			VehicleInfo[index][vinfo_FUEL] = fuel;
		}
		else SendClientMessage(playerid, -1, "Invalid vehicle ID!");
	}
	return 1;
}

YCMD:repairveh(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) SendClientMessage(playerid, -1, "Syntax: /repairveh [ID]");
	else
	{
		new index = GetVehicleIndexById(params[0]);
		if(index != INVALID_VEHICLE_INDEX) RepairVehicle(VehicleInfo[index][vinfo_VEHICLE_ID]);
		else SendClientMessage(playerid, -1, "Invalid vehicle ID!"); 
	}
	return 1;
}

YCMD:gveh(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) SendClientMessage(playerid, -1, "Syntax: /gveh [ID]");
	else
	{
		new index = GetVehicleIndexById(params[0]);
		if(index != INVALID_VEHICLE_INDEX)
		{
			if(VehicleInfo[index][vinfo_VEHICLE_ID] != INVALID_VEHICLE_ID)
			{
				new Float:pos[3];
				GetVehiclePos(VehicleInfo[index][vinfo_VEHICLE_ID], pos[0], pos[1], pos[2]);
				SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
				SetPlayerInterior(playerid, VehicleInfo[index][vinfo_INTERIORID]);
				SetPlayerVirtualWorld(playerid, VehicleInfo[index][vinfo_WORLDID]);
			}
			else SendClientMessage(playerid, -1, "Vehicle not created!");
		}
		else SendClientMessage(playerid, -1, "Invalid vehicle ID!"); 
	}
	return 1;
}

YCMD:getveh(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) SendClientMessage(playerid, -1, "Syntax: /getveh [ID]");
	else
	{
		new index = GetVehicleIndexById(params[0]);
		if(index != INVALID_VEHICLE_INDEX)
		{
			if(VehicleInfo[index][vinfo_VEHICLE_ID] != INVALID_VEHICLE_ID)
			{
				GetPlayerPos(playerid, VehicleInfo[index][vinfo_POS][0], VehicleInfo[index][vinfo_POS][1], VehicleInfo[index][vinfo_POS][2]);
				GetPlayerFacingAngle(playerid, VehicleInfo[index][vinfo_ANGLE]);
				VehicleInfo[index][vinfo_INTERIORID] = GetPlayerInterior(playerid);
				VehicleInfo[index][vinfo_WORLDID] = GetPlayerVirtualWorld(playerid);
				SetVehicleWorldInfo(index);
			}
			else SendClientMessage(playerid, -1, "Vehicle not created!");
		}
		else SendClientMessage(playerid, -1, "Invalid vehicle ID!"); 
	}
	return 1;
}

YCMD:vparams(playerid, params[], help)
{
	new vid, engine, lights, alarm, doors, bonnet, boot, objective;
	if(sscanf(params, "dddddddd", vid, engine, lights, alarm, doors, bonnet, boot, objective)) SendClientMessage(playerid, -1, "Syntax: /vparams [ID] [engine] [lights] [alarm] [doors] [bonnet] [boot] [objective]");
	else
	{
		new index = GetVehicleIndexById(vid);
		if(index != INVALID_VEHICLE_INDEX)
		{
			if(VehicleInfo[index][vinfo_VEHICLE_ID] != INVALID_VEHICLE_ID)
			{
				VehicleInfo[index][vinfo_PARAMS_ENGINE] = engine;
				VehicleInfo[index][vinfo_PARAMS_LIGHTS] = lights;
				VehicleInfo[index][vinfo_PARAMS_ALARM] = alarm;
				VehicleInfo[index][vinfo_PARAMS_DOORS] = doors;
				VehicleInfo[index][vinfo_PARAMS_BONNET] = bonnet;
				VehicleInfo[index][vinfo_PARAMS_BOOT] = boot;
				VehicleInfo[index][vinfo_PARAMS_OBJECTIVE] = objective;
				SetVehicleParams(index);
			}
			else SendClientMessage(playerid, -1, "Vehicle not created!");
		}
		else SendClientMessage(playerid, -1, "Invalid vehicle ID!"); 
	}
	return 1;
}

YCMD:lvehs(playerid, params[], help)
{
	ToggleVehiclesInfoLabels(!vehiclesInfoLabels);
	if(vehiclesInfoLabels) SendClientMessage(playerid, -1, "Vehicles info labels on!");
	else SendClientMessage(playerid, -1, "Vehicles info labels off!");
	return 1;
}