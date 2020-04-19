#define IsValidVehicle(%0) Iter_Contains(VehicleInfo,%0)
#define GetVehicleDriver(%0) VehicleInfo[%0][vinfo_DRIVER]
#define GetPlayerVehicleIndex(%0) pVehicleIndex[%0]

#define GetVehicleNameByModelid(%0) VehicleData[%0-400][vdata_NAME]
//#define GetVehicleGroupByModelid(%0) VehicleData[%0-400][vdata_GROUP]
//#define GetVehicleMaxSpeedByModelid(%0) VehicleData[%0-400][vdata_MAX_SPEED]
#define GetVehicleMaxFuelByModelid(%0) VehicleData[%0-400][vdata_MAX_FUEL]
#define GetVehicleSeatsByModelid(%0) VehicleData[%0-400][vdata_SEATS]

#define GetVehicleName(%0) VehicleData[GetVehicleModel(%0)-400][vdata_NAME]
//#define GetVehicleGroup(%0) VehicleData[GetVehicleModel(%0)-400][vdata_GROUP]
//#define GetVehicleMaxSpeed(%0) VehicleData[GetVehicleModel(%0)-400][vdata_MAX_SPEED]
#define GetVehicleMaxFuel(%0) VehicleData[GetVehicleModel(%0)-400][vdata_MAX_FUEL]
#define GetVehicleSeats(%0) VehicleData[GetVehicleModel(%0)-400][vdata_SEATS]

IsVehicleOccupied(index)
{
	if(VehicleInfo[index][vinfo_DRIVER] == INVALID_PLAYER_ID) return false;
	else return true;
}

GetVehicleModelidByName(vehicle_name[])
{
	for(new i = 0, j = sizeof VehicleData; i != j; i ++)
	{
		if(!strcmp(vehicle_name, VehicleData[i][vdata_NAME], true, 24))
		{
			return i + 400;
		}
	}
	return -1;
}

IsValidVehicleModelId(modelid)
{
	if(modelid >= 400 && modelid <= 611) return true;
	else return false;
}

IsValidVehiclePaintjob(paintjobid)
{
	if(paintjobid >= 0 && paintjobid <= 3) return true;
	else return false;
}

DestroyUnusedVehicles()
{
	new c;
	foreach(new i : VehicleInfo)
	{
		if(VehicleInfo[i][vinfo_ID] == 0 && VehicleInfo[i][vinfo_TYPE] == VEHICLE_TYPE_NONE)
		{
			if(VehicleInfo[i][vinfo_VEHICLE_ID] != INVALID_VEHICLE_ID) DestroyVehicle(VehicleInfo[i][vinfo_VEHICLE_ID]);
			if(VehicleInfo[i][vinfo_INFO_LABEL] != Text3D:INVALID_STREAMER_ID)
			{
				DestroyDynamic3DTextLabel(VehicleInfo[i][vinfo_INFO_LABEL]);
				VehicleInfo[i][vinfo_INFO_LABEL] = Text3D:INVALID_STREAMER_ID;
			}

			new vehicleid = VehicleInfo[i][vinfo_VEHICLE_ID];
			new tmp_VehicleInfo[enum_VehicleInfo];
			VehicleInfo[i] = tmp_VehicleInfo;
			
			new prev;
			Iter_SafeRemove(VehicleInfo, i, prev); 
			i = prev;
			c++;
			CallRemoteFunction("OnVehicleDestroyedEx", "ii", i, vehicleid);
		}
	}
	return c;
}

DestroyVehicleEx(index, bool:db = false)
{
	if(IsValidVehicle(index))
	{
		if(db && VehicleInfo[index][vinfo_ID])
		{
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM vehicles WHERE id = %d;", VehicleInfo[index][vinfo_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);
			DeleteVehicleKeys(VehicleInfo[index][vinfo_ID], VehicleInfo[index][vinfo_MODELID], index);
		}
		if(!db && VehicleInfo[index][vinfo_ID])
		{
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET created = 0 WHERE id = %d;", VehicleInfo[index][vinfo_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);
		}

		if(VehicleInfo[index][vinfo_VEHICLE_ID] != INVALID_VEHICLE_ID) DestroyVehicle(VehicleInfo[index][vinfo_VEHICLE_ID]);
		if(VehicleInfo[index][vinfo_INFO_LABEL] != Text3D:INVALID_STREAMER_ID)
		{
			DestroyDynamic3DTextLabel(VehicleInfo[index][vinfo_INFO_LABEL]);
			VehicleInfo[index][vinfo_INFO_LABEL] = Text3D:INVALID_STREAMER_ID;
		}

		new vehicleid = VehicleInfo[index][vinfo_VEHICLE_ID];
		new tmp_VehicleInfo[enum_VehicleInfo];
		VehicleInfo[index] = tmp_VehicleInfo;
		Iter_Remove(VehicleInfo, index);

		CallRemoteFunction("OnVehicleDestroyedEx", "ii", index, vehicleid);
		return 1;
	}
	return 0;
}

CreateVehicleEx
(
	VEHICLE_TYPES:type,
	modelid,
	Float:x,
	Float:y,
	Float:z,
	Float:rotation = 0.0,
	color1 = -1,
	color2 = -1,
	respawn_delay = -1,
	addsiren = 0,
	number_plate[] = "random",
	Float:fuel = -1.0, //max
	Float:health = 1000.0,
	interiorid = 0,
	worldid = 0,
	paintjob = 3,
	damage_panels = 0,
	damage_doors = 0,
	damage_lights = 0,
	damage_tires = 0,
	params_engine = 0,
	params_lights = 0,
	params_alarm = 0,
	params_doors = 0,
	params_bonnet = 0,
	params_boot = 0,
	params_objective = 0,
	Float:distance = -1.0,
	radio = -1,
	VEHICLE_GAME_STATES:game_state = VEHICLE_GAME_STATE_NORMAL,
	id = 0,
	id_player = 0,
	price = 0,
	level = 0,
	dslot = 0,
	id_job_point = 0
)
{
	new slot = Iter_Free(VehicleInfo);
	if(slot != cellmin)
	{
		VehicleInfo[slot][vinfo_STATE] = VEHICLE_STATE_SPAWNED;
		VehicleInfo[slot][vinfo_MODELID] = modelid;
		VehicleInfo[slot][vinfo_TYPE] = type;
		VehicleInfo[slot][vinfo_DRIVER] = INVALID_PLAYER_ID;
		format(VehicleInfo[slot][vinfo_NUMBER_PLATE], 32, "%s", number_plate);
		if(!strcmp(VehicleInfo[slot][vinfo_NUMBER_PLATE], "random")) format(VehicleInfo[slot][vinfo_NUMBER_PLATE], 32, "%c%c%d-%05d", getRandomLetter(), getRandomLetter(), getRandomLetter(), random(1000000));
		VehicleInfo[slot][vinfo_FUEL] = fuel;
		if(VehicleInfo[slot][vinfo_FUEL] == -1 || VehicleInfo[slot][vinfo_FUEL] > GetVehicleMaxFuelByModelid(modelid)) VehicleInfo[slot][vinfo_FUEL] = GetVehicleMaxFuelByModelid(modelid);
		VehicleInfo[slot][vinfo_RESPAWN_DELAY] = respawn_delay;
		VehicleInfo[slot][vinfo_ADDSIREN] = addsiren;
		VehicleInfo[slot][vinfo_HEALTH] = health;
		if(VehicleInfo[slot][vinfo_HEALTH] < MIN_VEHICLE_HEALTH) VehicleInfo[slot][vinfo_HEALTH] = MIN_VEHICLE_HEALTH;
		VehicleInfo[slot][vinfo_DISTANCE] = distance;
		if(VehicleInfo[slot][vinfo_DISTANCE] == -1.0) VehicleInfo[slot][vinfo_DISTANCE] = float(minrand(50000, 200000) * 1000);
		VehicleInfo[slot][vinfo_RADIO] = radio;
		if(VehicleInfo[slot][vinfo_RADIO] == -1) VehicleInfo[slot][vinfo_RADIO] = random(sizeof Radios);
		VehicleInfo[slot][vinfo_GAME_STATE] = game_state;

		VehicleInfo[slot][vinfo_SPAWN_POS][0] = x;
		VehicleInfo[slot][vinfo_SPAWN_POS][1] = y;
		VehicleInfo[slot][vinfo_SPAWN_POS][2] = z;
		VehicleInfo[slot][vinfo_SPAWN_ANGLE] = rotation;
		VehicleInfo[slot][vinfo_POS][0] = x;
		VehicleInfo[slot][vinfo_POS][1] = y;
		VehicleInfo[slot][vinfo_POS][2] = z;
		VehicleInfo[slot][vinfo_ANGLE] = rotation;
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
		VehShop_VehicleInfo[slot][vshop_SLOT] = dslot;

		VehicleInfo[slot][vinfo_VEHICLE_ID] = CreateVehicle(modelid, x, y, z, rotation, color1, color2, respawn_delay, addsiren);
		
		Iter_Add(VehicleInfo, slot);

		SetVehicleWorldSpawnInfo(slot);
		SetVehicleVariables(slot);

		if(id)
		{
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET created = 1 WHERE id = %d;", id);
			mysql_tquery(vcrp_db, QUERY_BUFFER);
		}

		CallRemoteFunction("OnVehicleLoaded", "i", slot);
		return slot;
	}
	return INVALID_VEHICLE_INDEX;
}

SetVehNumberPlate(index)
{
	switch(VehicleInfo[index][vinfo_TYPE])
	{
		case VEHICLE_TYPE_PLAYER, VEHICLE_TYPE_SELL: format(VehicleInfo[index][vinfo_NUMBER_PLATE], 32, "VEH-%05d", VehicleInfo[index][vinfo_ID]);
	}
	SetVehicleNumberPlate(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_NUMBER_PLATE]);
	return 1;
}

SetVehHealth(index)
{
	SetVehicleHealth(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_HEALTH]);
	return 1;
}

SetVehicleWorldSpawnInfo(index)
{
	SetVehiclePos(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_SPAWN_POS][0], VehicleInfo[index][vinfo_SPAWN_POS][1], VehicleInfo[index][vinfo_SPAWN_POS][2]);
	SetVehicleZAngle(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_SPAWN_ANGLE]);
	LinkVehicleToInterior(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_INTERIORID]);
	SetVehicleVirtualWorld(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_WORLDID]);
	return 1;
}

stock SetVehicleWorldInfo(index)
{
	SetVehiclePos(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_POS][0], VehicleInfo[index][vinfo_POS][1], VehicleInfo[index][vinfo_POS][2]);
	SetVehicleZAngle(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_ANGLE]);
	LinkVehicleToInterior(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_INTERIORID]);
	SetVehicleVirtualWorld(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_WORLDID]);
	return 1;
}

SetVehicleColors(index)
{
	ChangeVehicleColor(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_COLOR1], VehicleInfo[index][vinfo_COLOR2]);
	ChangeVehiclePaintjob(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_PAINTJOB]);
	return 1;
}

SetVehicleDamageStatus(index)
{
	UpdateVehicleDamageStatus(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_DAMAGE_PANELS], VehicleInfo[index][vinfo_DAMAGE_DOORS], VehicleInfo[index][vinfo_DAMAGE_LIGHTS], VehicleInfo[index][vinfo_DAMAGE_TIRES]);
	return 1;
}

SetVehicleParams(index)
{
	if(!VehicleModelHasEngine(VehicleInfo[index][vinfo_MODELID])) VehicleInfo[index][vinfo_PARAMS_ENGINE] = 1;
	if(!VehicleModelHasDoors(VehicleInfo[index][vinfo_MODELID])) VehicleInfo[index][vinfo_PARAMS_DOORS] = 0;
	
	SetVehicleParamsEx(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_PARAMS_ENGINE], VehicleInfo[index][vinfo_PARAMS_LIGHTS], VehicleInfo[index][vinfo_PARAMS_ALARM], VehicleInfo[index][vinfo_PARAMS_DOORS], VehicleInfo[index][vinfo_PARAMS_BONNET], VehicleInfo[index][vinfo_PARAMS_BOOT], VehicleInfo[index][vinfo_PARAMS_OBJECTIVE]);
	return 1;
}

UpdateVehicleInfo(index, bool:update_spawn_pos = false, bool:update_params = true)
{
	GetVehicleHealth(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_HEALTH]);
	VehicleInfo[index][vinfo_WORLDID] = GetVehicleVirtualWorld(VehicleInfo[index][vinfo_VEHICLE_ID]);
	GetVehiclePos(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_POS][0], VehicleInfo[index][vinfo_POS][1], VehicleInfo[index][vinfo_POS][2]);
	GetVehicleZAngle(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_ANGLE]);
	GetVehicleDamageStatus(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_DAMAGE_PANELS], VehicleInfo[index][vinfo_DAMAGE_DOORS], VehicleInfo[index][vinfo_DAMAGE_LIGHTS], VehicleInfo[index][vinfo_DAMAGE_TIRES]);
	if(update_params) GetVehicleParamsEx(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_PARAMS_ENGINE], VehicleInfo[index][vinfo_PARAMS_LIGHTS], VehicleInfo[index][vinfo_PARAMS_ALARM], VehicleInfo[index][vinfo_PARAMS_DOORS], VehicleInfo[index][vinfo_PARAMS_BONNET], VehicleInfo[index][vinfo_PARAMS_BOOT], VehicleInfo[index][vinfo_PARAMS_OBJECTIVE]);

	if(update_spawn_pos)
	{
		VehicleInfo[index][vinfo_SPAWN_POS][0] = VehicleInfo[index][vinfo_POS][0];
		VehicleInfo[index][vinfo_SPAWN_POS][1] = VehicleInfo[index][vinfo_POS][1];
		VehicleInfo[index][vinfo_SPAWN_POS][2] = VehicleInfo[index][vinfo_POS][2];
		VehicleInfo[index][vinfo_SPAWN_ANGLE] = VehicleInfo[index][vinfo_ANGLE];
	}
	return 1;
}

UpdateVehicleInfoDb(index)
{
	if(!VehicleInfo[index][vinfo_ID]) return 0;

	mysql_format
	(
		vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER,
		"\
			UPDATE vehicles SET \
				modelid = %d,\
				type = %d,\
				number_plate = '%e',\
				fuel = %f,\
				addsiren = %d,\
				health = %f,\
				distance = %f,\
				spawn_pos_x = %f,\
				spawn_pos_y = %f,\
				spawn_pos_z = %f,\
				spawn_angle = %f,\
				interiorid = %d,\
				worldid = %d,\
				color1 = %d,\
				color2 = %d,\
				paintjob = %d,\
				damage_panels = %d,\
				damage_doors = %d,\
				damage_lights = %d,\
				damage_tires = %d,\
				params_engine = %d,\
				params_lights = %d,\
				params_alarm = %d,\
				params_doors = %d,\
				params_bonnet = %d,\
				params_boot = %d,\
				params_objective = %d,\
				radio = %d,\
				game_state = %d \
			WHERE id = %d;\
		",
			VehicleInfo[index][vinfo_MODELID],
			_:VehicleInfo[index][vinfo_TYPE],
			VehicleInfo[index][vinfo_NUMBER_PLATE],
			VehicleInfo[index][vinfo_FUEL],
			VehicleInfo[index][vinfo_ADDSIREN],
			VehicleInfo[index][vinfo_HEALTH],
			VehicleInfo[index][vinfo_DISTANCE],
			VehicleInfo[index][vinfo_SPAWN_POS][0],
			VehicleInfo[index][vinfo_SPAWN_POS][1],
			VehicleInfo[index][vinfo_SPAWN_POS][2],
			VehicleInfo[index][vinfo_SPAWN_ANGLE],
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
			VehicleInfo[index][vinfo_PARAMS_OBJECTIVE],
			VehicleInfo[index][vinfo_RADIO],
			_:VehicleInfo[index][vinfo_GAME_STATE],
			VehicleInfo[index][vinfo_ID]
	);
	mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	return 1;
}

UpdateVehicleModifications(index)
{
	if(!VehicleInfo[index][vinfo_ID]) return 0;
	if(VehicleInfo[index][vinfo_VEHICLE_ID] == INVALID_VEHICLE_ID) return 0;

	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM vehicle_components WHERE id_vehicle = %d;", VehicleInfo[index][vinfo_ID]);
	mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

	new components[MAX_VEHICLE_COMPONENTS], total;
	GetVehComponents(VehicleInfo[index][vinfo_VEHICLE_ID], components, total);
	for(new i = 0; i < total; i ++)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO vehicle_components VALUES (%d, %d);", VehicleInfo[index][vinfo_ID], components[i]);
		mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	}
	return 1;
}

SetVehicleComponents(index)
{
	if(!VehicleInfo[index][vinfo_ID]) return 0;
	if(VehicleInfo[index][vinfo_VEHICLE_ID] == INVALID_VEHICLE_ID) return 0;

	inline OnVehicleComponentsLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				new componentid;
				cache_get_value_name_int(i, "componentid", componentid);
				AddVehicleMod(VehicleInfo[index][vinfo_VEHICLE_ID], componentid);
			}
		}
	}
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM vehicle_components WHERE id_vehicle = %d;", VehicleInfo[index][vinfo_ID]);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnVehicleComponentsLoad, "");
	return 1;
}

Float:GetVehicleFuelPercent(index)
{
	new Float:percent;
	percent = floatdiv(floatmul(VehicleInfo[index][vinfo_FUEL], 100.0), GetVehicleMaxFuelByModelid(VehicleInfo[index][vinfo_MODELID]));
	return percent;
}

GetVehicleIndexByVehicleid(vehicleid)
{
	foreach(new i : VehicleInfo)
	{
		if(VehicleInfo[i][vinfo_VEHICLE_ID] == vehicleid)
		{
			return i;
		}
	}
	return INVALID_VEHICLE_INDEX;
}

GetVehicleIndexById(id)
{
	if(id != 0)
	{
		foreach(new i : VehicleInfo)
		{
			if(VehicleInfo[i][vinfo_ID] == id)
			{
				return i;
			}
		}
	}
	return INVALID_VEHICLE_INDEX;
}

RecreateVehicle(index, bool:change_angle = false, Float:angle = 0.0, bool:use_pos = false, Float:x = 0.0, Float:y = 0.0, Float:z = 0.0)
{
	if(IsValidVehicle(index))
	{
		if(VehicleInfo[index][vinfo_VEHICLE_ID] != INVALID_VEHICLE_ID)
		{
			UpdateVehicleInfo(index, false, false);
			DestroyVehicle(VehicleInfo[index][vinfo_VEHICLE_ID]);
			VehicleInfo[index][vinfo_VEHICLE_ID] = INVALID_VEHICLE_ID;

			if(change_angle) VehicleInfo[index][vinfo_ANGLE] = angle;

			if(use_pos) VehicleInfo[index][vinfo_VEHICLE_ID] = CreateVehicle(VehicleInfo[index][vinfo_MODELID], x, y, z, VehicleInfo[index][vinfo_ANGLE], VehicleInfo[index][vinfo_COLOR1], VehicleInfo[index][vinfo_COLOR2], VehicleInfo[index][vinfo_RESPAWN_DELAY], VehicleInfo[index][vinfo_ADDSIREN]);
			else VehicleInfo[index][vinfo_VEHICLE_ID] = CreateVehicle(VehicleInfo[index][vinfo_MODELID], VehicleInfo[index][vinfo_POS][0], VehicleInfo[index][vinfo_POS][1], VehicleInfo[index][vinfo_POS][2], VehicleInfo[index][vinfo_ANGLE], VehicleInfo[index][vinfo_COLOR1], VehicleInfo[index][vinfo_COLOR2], VehicleInfo[index][vinfo_RESPAWN_DELAY], VehicleInfo[index][vinfo_ADDSIREN]);

			VehicleInfo[index][vinfo_STATE] = VEHICLE_STATE_SPAWNED;
			SetVehicleVariables(index);
		}
		return 1;
	}
	return 0;
}

CreateVehicleFromInfo(index)
{
	if(IsValidVehicle(index))
	{
		if(VehicleInfo[index][vinfo_VEHICLE_ID] == INVALID_VEHICLE_ID)
		{
			VehicleInfo[index][vinfo_VEHICLE_ID] = CreateVehicle(VehicleInfo[index][vinfo_MODELID], VehicleInfo[index][vinfo_SPAWN_POS][0], VehicleInfo[index][vinfo_SPAWN_POS][1], VehicleInfo[index][vinfo_SPAWN_POS][2], VehicleInfo[index][vinfo_SPAWN_ANGLE], VehicleInfo[index][vinfo_COLOR1], VehicleInfo[index][vinfo_COLOR2], VehicleInfo[index][vinfo_RESPAWN_DELAY], VehicleInfo[index][vinfo_ADDSIREN]);
			if(VehicleInfo[index][vinfo_VEHICLE_ID] != INVALID_VEHICLE_ID)
			{
				VehicleInfo[index][vinfo_STATE] = VEHICLE_STATE_SPAWNED;
				SetVehicleVariables(index);

				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET created = 1 WHERE id = %d;", VehicleInfo[index][vinfo_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);

				CallRemoteFunction("OnVehicleLoaded", "i", index);
				return 1;
			}
		}
	}
	return 0;
}

SetVehicleZAngleEx(index, Float:zangle, bool:use_pos = false, Float:x = 0.0, Float:y = 0.0, Float:z = 0.0)
{
	if(IsVehicleOccupied(index))
	{
		VehicleInfo[index][vinfo_ANGLE] = zangle;
		SetVehicleZAngle(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_ANGLE]);
	}
	else RecreateVehicle(index, true, zangle, use_pos, x, y, z);
	return 1;
}

VehicleModelHasEngine(modelid)
{
	if(Model_IsManual(modelid)) return false;
	else return true;
}

VehicleModelHasDoors(modelid)
{
	new vehicle_cat = Model_GetCategory(modelid);
	switch(vehicle_cat)
	{
		case CATEGORY_BIKE, CATEGORY_BOAT, CATEGORY_TRAILER, CATEGORY_RC:
		{
			return false;
		}
	}
	return true;
}

SetVehicleVariables(vehicleindex)
{
	SetVehNumberPlate(vehicleindex);
	SetVehHealth(vehicleindex);
	SetVehicleColors(vehicleindex);
	SetVehicleComponents(vehicleindex);
	SetVehicleDamageStatus(vehicleindex);
	SetVehicleParams(vehicleindex);
	return 1;
}


DeleteVehicleKeys(id, modelid, vindex = -1)
{
	new params[24];
	format(params, sizeof params, "%d,%d", id, modelid);

	//player
	foreach(new i : Player)
	{
		if(vindex != -1)
		{
			if(Iter_Contains(PlayerVehicles[i], vindex))
			Iter_Remove(PlayerVehicles[i], vindex);
		}
		foreach(new x : PINV[i])
		{
			if(PINV[i][x][pinv_ITEM_ID] == _:INV_ITEM_VEHICLE_KEY || PINV[i][x][pinv_ITEM_ID] == _:INV_ITEM_VEHICLE_MASTER_KEY || PINV[i][x][pinv_ITEM_ID] == _:INV_ITEM_VEHICLE_RENT_KEY)
			{
				if(!strcmp(PINV[i][x][pinv_PARAMS], params))
				{
					new tmp_PINV[enum_PINV], prev;
					PINV[i][x] = tmp_PINV;

					Iter_SafeRemove(PINV[i], x, prev); 
					x = prev;
				}
			}
		}
	}

	//db
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_inv WHERE (item_id = %d OR item_id = %d OR item_id = %d) AND params = '%e';", _:INV_ITEM_VEHICLE_KEY, _:INV_ITEM_VEHICLE_MASTER_KEY, _:INV_ITEM_VEHICLE_RENT_KEY, params);
	mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	return 1;
}

GetVehicleModelIcon(modelid)
{
	new icon[32];
	if(Model_IsTaxi(modelid)) icon = ""TEXTDRAW_CUSTOM_PATH"icon_taxi";
	else if(Model_IsTruck(modelid) || Model_IsVan(modelid)) icon = ""TEXTDRAW_CUSTOM_PATH"icon_truck";
	else if(Model_IsBike(modelid)) icon = ""TEXTDRAW_CUSTOM_PATH"icon_bike";
	else if(Model_IsPlane(modelid)) icon = ""TEXTDRAW_CUSTOM_PATH"icon_plane";
	else if(Model_IsHelicopter(modelid)) icon = ""TEXTDRAW_CUSTOM_PATH"icon_heli";
	else if(Model_IsBoat(modelid)) icon = ""TEXTDRAW_CUSTOM_PATH"icon_boat";
	else icon = ""TEXTDRAW_CUSTOM_PATH"icon_car";
	return icon;
}

GetPlayerVehicleIconColor(playerid, vehicle_index)
{
	if(Iter_Contains(PlayerVehicles[playerid], vehicle_index))
	{
		switch(VehicleInfo[vehicle_index][vinfo_TYPE])
		{
			case VEHICLE_TYPE_PLAYER:
			{
				if(VehicleInfo[vehicle_index][vinfo_ID_PLAYER] == PI[playerid][pi_ID]) return 0xffd467ff;
				else return 0xdededeff;
			}
			case VEHICLE_TYPE_RENT: return 0xcd7e33ff;
		}	
	}
	return 0xFFFFFFFF;
}