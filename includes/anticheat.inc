/*
	By adri1
*/
#if defined _inc_anticheat
	#endinput
#endif
#define _inc_anticheat

#include <YSI\y_hooks>

new MySQL:anticheat_db;

enum CHEATS
{
	CHEAT_WEAPONS = 1,
	CHEAT_AMMO,
	CHEAT_POSITION,
	CHEAT_TELEPORT,
	CHEAT_PLAYER_SPEED,
	CHEAT_SPECIAL_ACTION,
	CHEAT_ENTER_CLOSED_VEHICLE,
	CHEAT_STATE_CHANGE_FLOODER,
	CHEAT_VEHICLE_SPEED,
	CHEAT_TEXT_FLOODER,
	CHEAT_COMMAND_FLOODER,
	CHEAT_VEHICLE_MOD,
	CHEAT_HEALTH,
	CHEAT_ARMOUR,
	CHEAT_VEHICLE_HEALTH
};
enum E_AcInfo
{
	ac_NAME[24],
	ac_ENABLED,
	ac_DETECTIONS,	//llamar cuando se detecten X detecciones
	ac_IN_SECONDS,	//en Y segundos
	ac_MIN_SECONDS,	//min seconds between detections
	ac_KICK
};
new AcInfo[_:CHEATS][E_AcInfo];
new Float:ac_Teleport_Distance = 80.0,
	Float:ac_Position_Distance_Foot = 8.0,
	Float:ac_Position_Distance_Vehicle = 10.0,
	Float:ac_Position_Distance_Vehicle_mS = 20.0,
	ac_PlayerSpeed_MaxValue = 1000,
	ac_VehicleSpeed_MaxValue = 1000,
	ac_VehicleSpeed_Offset_MaxValue = 100,
	ac_Default_Protection_Seconds = 3,
	ac_Default_Flooder_MaxInterval = 50;
enum E_pAcInfo
{
	pac_DETECTIONS,
	pac_LAST_DETECTION,
	pac_PROTECT_TIME
};
new pAcInfo[MAX_PLAYERS][_:CHEATS][E_pAcInfo],
	bool:pAcKicked[MAX_PLAYERS];

forward OnPlayerCheatPredetected(playerid, cheat);
forward OnPlayerCheatDetected(playerid, cheat);
#define GetCheatName(%0) AcInfo[%0][ac_NAME]
#define IsKickCheat(%0) AcInfo[%0][ac_KICK]

new ac_pWeapons[MAX_PLAYERS][13][2],
	Float:ac_pPosition[MAX_PLAYERS][3],
	ac_pSpecialAction[MAX_PLAYERS] = {SPECIAL_ACTION_NONE, ...},
	ac_vLast_CloseDoors[MAX_VEHICLES],
	ac_pLast_StateChange[MAX_PLAYERS],
	ac_pLast_Text[MAX_PLAYERS],
	ac_pLast_Command[MAX_PLAYERS],
	Float:ac_pHealth[MAX_PLAYERS] = {100.0, ...},
	Float:ac_pArmour[MAX_PLAYERS],
	Float:ac_vHealth[MAX_VEHICLES] = {1000.0, ...},
	ac_vLast_SetHealth[MAX_VEHICLES];

hook OnScriptInit()
{
	print("--- anticheat --- [MySQL] Conectando con la base de datos...");
	anticheat_db = mysql_connect_file("anticheat_db.ini");
	if(mysql_errno(anticheat_db) == 0)
	{
		printf("--- anticheat --- [MySQL] Base de datos conectada (anticheat) (%d)", _:anticheat_db);
		inline OnAnticheatsLoad()
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				for(new i = 0; i < rows; i ++)
				{
					new id;
					cache_get_value_name_int(i, "id", id);
					cache_get_value_name_int(i, "enabled", AcInfo[id][ac_ENABLED]);
					cache_get_value_name(i, "name", AcInfo[id][ac_NAME]);
					cache_get_value_name_int(i, "detections", AcInfo[id][ac_DETECTIONS]);
					cache_get_value_name_int(i, "in_seconds", AcInfo[id][ac_IN_SECONDS]);
					cache_get_value_name_int(i, "min_seconds", AcInfo[id][ac_MIN_SECONDS]);
					cache_get_value_name_int(i, "kick", AcInfo[id][ac_KICK]);
				}
			}
		}
		mysql_tquery_inline(anticheat_db, "SELECT * FROM anticheats;", using inline OnAnticheatsLoad, "");

		inline OnVariablesLoad()
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				for(new i = 0; i < rows; i ++)
				{
					new varname[32], value[24];
					cache_get_value_name(i, "varname", varname);
					cache_get_value_name(i, "value", value);

					if(!strcmp(varname, "position_distance_foot")) ac_Position_Distance_Foot = floatstr(value);
					else if(!strcmp(varname, "position_distance_vehicle")) ac_Position_Distance_Vehicle = floatstr(value);
					else if(!strcmp(varname, "position_distance_vehicle_ms")) ac_Position_Distance_Vehicle_mS = floatstr(value);
					else if(!strcmp(varname, "default_protection_seconds")) ac_Default_Protection_Seconds = strval(value);
					else if(!strcmp(varname, "teleport_distance")) ac_Teleport_Distance = floatstr(value);
					else if(!strcmp(varname, "playerspeed_maxvalue")) ac_PlayerSpeed_MaxValue = strval(value);
					else if(!strcmp(varname, "vehiclespeed_maxvalue")) ac_VehicleSpeed_MaxValue = strval(value);
					else if(!strcmp(varname, "vehiclespeed_offset_maxvalue")) ac_VehicleSpeed_Offset_MaxValue = strval(value);
					else if(!strcmp(varname, "default_flooder_maxinterval")) ac_Default_Flooder_MaxInterval = strval(value);
				}
			}
		}
		mysql_tquery_inline(anticheat_db, "SELECT * FROM variables;", using inline OnVariablesLoad, "");
	}
	else
	{
		printf("--- anticheat --- [MySQL] No se pudo conectar con la base de datos (anticheat) (%d)", mysql_errno(anticheat_db));
		SendRconCommand("exit");
	}
	return 1;
}

hook OnScriptExit()
{
	mysql_close(anticheat_db);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	pAcKicked[playerid] = false;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	for(new i = 0; i < sizeof ac_pWeapons[]; i ++)
	{
		ac_pWeapons[playerid][i][0] = 0;
		ac_pWeapons[playerid][i][1] = 0;
	}
	ac_pSpecialAction[playerid] = SPECIAL_ACTION_NONE;
	ac_pHealth[playerid] = 100.0;
	ac_pArmour[playerid] = 0.0;
	return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
	new timestamp = gettime();
	pAcInfo[playerid][_:CHEAT_POSITION][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	pAcInfo[playerid][_:CHEAT_TELEPORT][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	new timestamp = gettime();
	pAcInfo[playerid][_:CHEAT_POSITION][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	pAcInfo[playerid][_:CHEAT_TELEPORT][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	return 1;
}

public e_COMMAND_ERRORS:OnPlayerCommandPerformed(playerid, cmdtext[], e_COMMAND_ERRORS:success) 
{
	new timestamp_tc = GetTickCount(),
		interval = ac_GetTickDiff(timestamp_tc, ac_pLast_Command[playerid]);
	if(interval < ac_Default_Flooder_MaxInterval)
	OnPlayerCheatPredetected(playerid, _:CHEAT_COMMAND_FLOODER);
	ac_pLast_Command[playerid] = timestamp_tc;
	return e_COMMAND_ERRORS:Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerText(playerid, text[])
{
	new timestamp_tc = GetTickCount(),
		interval = ac_GetTickDiff(timestamp_tc, ac_pLast_Text[playerid]);
	if(interval < ac_Default_Flooder_MaxInterval)
	OnPlayerCheatPredetected(playerid, _:CHEAT_TEXT_FLOODER);
	ac_pLast_Text[playerid] = timestamp_tc;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	new timestamp = gettime(),
		timestamp_tc = GetTickCount();
	pAcInfo[playerid][_:CHEAT_POSITION][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	pAcInfo[playerid][_:CHEAT_TELEPORT][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	pAcInfo[playerid][_:CHEAT_HEALTH][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	pAcInfo[playerid][_:CHEAT_ARMOUR][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CHEAT_STATE_CHANGE_FLOODER
	new interval = ac_GetTickDiff(timestamp_tc, ac_pLast_StateChange[playerid]);
	if(interval < ac_Default_Flooder_MaxInterval)
	OnPlayerCheatPredetected(playerid, _:CHEAT_STATE_CHANGE_FLOODER);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CHEAT_ENTER_CLOSED_VEHICLE
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(vehicleid != 0 && ac_VehicleModelHasDoors(GetVehicleModel(vehicleid)))
		{
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			if(doors == 1)
			{
				if(timestamp - ac_vLast_CloseDoors[vehicleid] > ac_Default_Protection_Seconds + 2)
				OnPlayerCheatPredetected(playerid, _:CHEAT_ENTER_CLOSED_VEHICLE);
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ac_pLast_StateChange[playerid] = timestamp_tc;
	return 1;
}

hook OnVehicleMod(playerid, vehicleid, componentid)
{
	OnPlayerCheatPredetected(playerid, _:CHEAT_VEHICLE_MOD);
	return Y_HOOKS_BREAK_RETURN_0;
}

hook OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	if(!(-1 < paintjobid < 3) && paintjobid != 255)
	OnPlayerCheatPredetected(playerid, _:CHEAT_VEHICLE_MOD);
	return 1;
}

hook OnPlayerUpdate(playerid)
{
	//vars
	new weaponid = GetPlayerWeapon(playerid),
		playerstate = GetPlayerState(playerid),
		vehicleid = GetPlayerVehicleID(playerid),
		player_action = GetPlayerSpecialAction(playerid),
		Float:vehicle_speed = 0.0,
		Float:player_health,
		Float:player_armour,
		timestamp = gettime();
	GetPlayerHealth(playerid, player_health);
	GetPlayerArmour(playerid, player_armour);
	if(vehicleid != 0) vehicle_speed = Vehicle_Speed(vehicleid);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CHEAT_WEAPONS, CHEAT_AMMO
	if(weaponid != 0)
	{
		new slot = GetWeaponSlot(weaponid),
			tmp_weaponID, tmp_ammo;
		GetPlayerWeaponData(playerid, slot, tmp_weaponID, tmp_ammo);
		if(ac_pWeapons[playerid][slot][0] == tmp_weaponID)
		{
			if(HasWeaponAmmo(weaponid))
			{
				if(tmp_ammo > ac_pWeapons[playerid][slot][1]) OnPlayerCheatPredetected(playerid, _:CHEAT_AMMO);
				else ac_pWeapons[playerid][slot][1] = tmp_ammo;
			}
		}
		else OnPlayerCheatPredetected(playerid, _:CHEAT_WEAPONS);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CHEAT_POSITION, CHEAT_TELEPORT
	if(playerstate == PLAYER_STATE_ONFOOT || playerstate == PLAYER_STATE_DRIVER)
	{
		if(ac_pPosition[playerid][2] > -97.0)
		{
			new Float:distance;
			if(vehicleid == 0)
			{
				if(GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID && GetPlayerSurfingObjectID(playerid) == INVALID_OBJECT_ID && player_action != SPECIAL_ACTION_ENTER_VEHICLE && player_action != SPECIAL_ACTION_EXIT_VEHICLE)
				{
					distance = floatabs(GetPlayerDistanceFromPoint(playerid, ac_pPosition[playerid][0], ac_pPosition[playerid][1], ac_pPosition[playerid][2]));
					if(distance > ac_Teleport_Distance) OnPlayerCheatPredetected(playerid, _:CHEAT_TELEPORT);
					else if(distance > ac_Position_Distance_Foot) OnPlayerCheatPredetected(playerid, _:CHEAT_POSITION);
				}
				GetPlayerPos(playerid, ac_pPosition[playerid][0], ac_pPosition[playerid][1], ac_pPosition[playerid][2]);
			}
			else
			{
				if(vehicle_speed < ac_Position_Distance_Vehicle_mS)
				{
					distance = floatabs(GetVehicleDistanceFromPoint(vehicleid, ac_pPosition[playerid][0], ac_pPosition[playerid][1], ac_pPosition[playerid][2]));
					if(distance > ac_Teleport_Distance) OnPlayerCheatPredetected(playerid, _:CHEAT_TELEPORT);
					else if(distance > ac_Position_Distance_Vehicle) OnPlayerCheatPredetected(playerid, _:CHEAT_POSITION);
				}
				GetVehiclePos(vehicleid, ac_pPosition[playerid][0], ac_pPosition[playerid][1], ac_pPosition[playerid][2]);
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CHEAT_PLAYER_SPEED
	if(playerstate == PLAYER_STATE_ONFOOT && !ac_IsPlayerJumping(playerid) && GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID && player_action != SPECIAL_ACTION_JETPACK)
	{
		new Float:playerspeed_X, Float:playerspeed_Y, Float:playerspeed_Z;
		GetPlayerVelocity(playerid, playerspeed_X, playerspeed_Y, playerspeed_Z);
		
		// Si esta agachado (GUNCROUCHFWD) y la velocidad en ambos ejes (x, y) es superior a 0.08
		if(GetPlayerAnimationIndex(playerid) == 1159 && (floatabs(playerspeed_X) > 0.08 || floatabs(playerspeed_Y) > 0.08)) OnPlayerCheatPredetected(playerid, _:CHEAT_PLAYER_SPEED);
		
		// Si ambas velocidades son superiores a 0.30, excepto la de caída
		if(floatabs(playerspeed_X) > 0.30 || floatabs(playerspeed_Y) > 0.30) OnPlayerCheatPredetected(playerid, _:CHEAT_PLAYER_SPEED);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CHEAT_VEHICLE_SPEED
	if(playerstate == PLAYER_STATE_DRIVER)
	{
		if(vehicle_speed > Model_TopSpeed(GetVehicleModel(vehicleid)) + ac_VehicleSpeed_Offset_MaxValue) OnPlayerCheatPredetected(playerid, _:CHEAT_VEHICLE_SPEED);
		else if(vehicle_speed > ac_VehicleSpeed_MaxValue) OnPlayerCheatPredetected(playerid, _:CHEAT_VEHICLE_SPEED);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CHEAT_SPECIAL_ACTION
	if(player_action != SPECIAL_ACTION_NONE && player_action != SPECIAL_ACTION_DUCK && player_action != SPECIAL_ACTION_ENTER_VEHICLE && player_action != SPECIAL_ACTION_EXIT_VEHICLE && player_action != ac_pSpecialAction[playerid])
	OnPlayerCheatPredetected(playerid, _:CHEAT_SPECIAL_ACTION);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CHEAT_HEALTH
	if(player_health > ac_pHealth[playerid]) OnPlayerCheatPredetected(playerid, _:CHEAT_HEALTH);
	else
	{
		if(timestamp > pAcInfo[playerid][_:CHEAT_HEALTH][pac_PROTECT_TIME])
		ac_pHealth[playerid] = player_health;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CHEAT_ARMOUR
	if(player_armour > ac_pArmour[playerid]) OnPlayerCheatPredetected(playerid, _:CHEAT_ARMOUR);
	else
	{
		if(timestamp > pAcInfo[playerid][_:CHEAT_ARMOUR][pac_PROTECT_TIME])
		ac_pArmour[playerid] = player_armour;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CHEAT_VEHICLE_HEALTH
	if(playerstate == PLAYER_STATE_DRIVER && vehicleid != 0)
	{
		new Float:vehicle_health;
		GetVehicleHealth(vehicleid, vehicle_health);
		if(vehicle_health > ac_vHealth[vehicleid]) OnPlayerCheatPredetected(playerid, _:CHEAT_VEHICLE_HEALTH);
		else
		{
			if(timestamp - ac_vLast_SetHealth[vehicleid] > ac_Default_Protection_Seconds)
			ac_vHealth[vehicleid] = vehicle_health;
		}
	}
	return 1;
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	if(Model_GetCategory(GetVehicleModel(vehicleid)) != CATEGORY_TRAILER)
	{ 
		if(GetVehicleDistanceFromPoint(vehicleid, new_x, new_y, new_z) > 50.0)
		{
			SetVehicleVelocity(vehicleid, 0.0, 0.0, 0.0);
			return Y_HOOKS_BREAK_RETURN_0;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

public OnPlayerCheatPredetected(playerid, cheat)
{
	if(AcInfo[cheat][ac_ENABLED] && !pAcKicked[playerid])
	{
		new timestamp = gettime();
		if(timestamp > pAcInfo[playerid][cheat][pac_PROTECT_TIME] && (AcInfo[cheat][ac_MIN_SECONDS] == 0 || timestamp - pAcInfo[playerid][cheat][pac_LAST_DETECTION] >= AcInfo[cheat][ac_MIN_SECONDS]))
		{
			if(AcInfo[cheat][ac_IN_SECONDS] == 0) CallRemoteFunction("OnPlayerCheatDetected", "id", playerid, cheat);
			else
			{
				if(timestamp - pAcInfo[playerid][cheat][pac_LAST_DETECTION] > AcInfo[cheat][ac_IN_SECONDS]) pAcInfo[playerid][cheat][pac_DETECTIONS] = 0;
				else pAcInfo[playerid][cheat][pac_DETECTIONS] ++;
				if(pAcInfo[playerid][cheat][pac_DETECTIONS] >= AcInfo[cheat][ac_DETECTIONS])
				{
					CallRemoteFunction("OnPlayerCheatDetected", "id", playerid, cheat);
				}
			}
			pAcInfo[playerid][cheat][pac_LAST_DETECTION] = timestamp;
		}
	}
	return 1;
}

stock ac_GivePlayerWeapon(playerid, weaponid, ammo)
{
	new timestamp = gettime();
	pAcInfo[playerid][_:CHEAT_WEAPONS][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	pAcInfo[playerid][_:CHEAT_AMMO][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	new slot = GetWeaponSlot(weaponid);
	ac_pWeapons[playerid][slot][0] = weaponid;
	ac_pWeapons[playerid][slot][1] = ammo;
	return GivePlayerWeapon(playerid, weaponid, ammo);
}

#if defined _ALS_GivePlayerWeapon
	#undef GivePlayerWeapon
#else
	#define _ALS_GivePlayerWeapon
#endif
#define GivePlayerWeapon ac_GivePlayerWeapon

stock ac_ResetPlayerWeapons(playerid)
{
	new timestamp = gettime();
	pAcInfo[playerid][_:CHEAT_WEAPONS][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	pAcInfo[playerid][_:CHEAT_AMMO][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	for(new i = 0; i < sizeof ac_pWeapons[]; i ++)
	{
		ac_pWeapons[playerid][i][0] = 0;
		ac_pWeapons[playerid][i][1] = 0;
	}
	return ResetPlayerWeapons(playerid);
}

#if defined _ALS_ResetPlayerWeapons
	#undef ResetPlayerWeapons
#else
	#define _ALS_ResetPlayerWeapons
#endif
#define ResetPlayerWeapons ac_ResetPlayerWeapons

stock ac_SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
	new timestamp = gettime();
	pAcInfo[playerid][_:CHEAT_POSITION][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	pAcInfo[playerid][_:CHEAT_TELEPORT][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
	return SetPlayerPos(playerid, x, y, z);
}

#if defined _ALS_SetPlayerPos
	#undef SetPlayerPos
#else
	#define _ALS_SetPlayerPos
#endif
#define SetPlayerPos ac_SetPlayerPos

stock ac_SetVehiclePos(vehicleid, Float:x, Float:y, Float:z)
{
	new timestamp = gettime();
	foreach(new i : Player)
	{
		if(GetPlayerVehicleID(i) == vehicleid)
		{
			pAcInfo[i][_:CHEAT_POSITION][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
			pAcInfo[i][_:CHEAT_TELEPORT][pac_PROTECT_TIME] = timestamp + ac_Default_Protection_Seconds;
		}
	}
	return SetVehiclePos(vehicleid, x, y, z);
}

#if defined _ALS_SetVehiclePos
	#undef SetVehiclePos
#else
	#define _ALS_SetVehiclePos
#endif
#define SetVehiclePos ac_SetVehiclePos

stock ac_SetPlayerSpecialAction(playerid, actionid)
{
	pAcInfo[playerid][_:CHEAT_SPECIAL_ACTION][pac_PROTECT_TIME] = gettime() + ac_Default_Protection_Seconds;
	ac_pSpecialAction[playerid] = actionid;
	return SetPlayerSpecialAction(playerid, actionid);
}

#if defined _ALS_SetPlayerSpecialAction
	#undef SetPlayerSpecialAction
#else
	#define _ALS_SetPlayerSpecialAction
#endif
#define SetPlayerSpecialAction ac_SetPlayerSpecialAction

stock ac_PutPlayerInVehicle(playerid, vehicleid, seatid)
{
	pAcInfo[playerid][_:CHEAT_ENTER_CLOSED_VEHICLE][pac_PROTECT_TIME] = gettime() + ac_Default_Protection_Seconds;
	return PutPlayerInVehicle(playerid, vehicleid, seatid);
}

#if defined _ALS_PutPlayerInVehicle
	#undef PutPlayerInVehicle
#else
	#define _ALS_PutPlayerInVehicle
#endif
#define PutPlayerInVehicle ac_PutPlayerInVehicle

stock ac_SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
{
	if(doors == 1) ac_vLast_CloseDoors[vehicleid] = gettime();
	return SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
}

#if defined _ALS_SetVehicleParamsEx
	#undef SetVehicleParamsEx
#else
	#define _ALS_SetVehicleParamsEx
#endif
#define SetVehicleParamsEx ac_SetVehicleParamsEx

stock ac_SetPlayerHealth(playerid, Float:health)
{
	pAcInfo[playerid][_:CHEAT_HEALTH][pac_PROTECT_TIME] = gettime() + ac_Default_Protection_Seconds;
	ac_pHealth[playerid] = health;
	return SetPlayerHealth(playerid, health);
}

#if defined _ALS_SetPlayerHealth
	#undef SetPlayerHealth
#else
	#define _ALS_SetPlayerHealth
#endif
#define SetPlayerHealth ac_SetPlayerHealth

stock ac_SetPlayerArmour(playerid, Float:armour)
{
	pAcInfo[playerid][_:CHEAT_ARMOUR][pac_PROTECT_TIME] = gettime() + ac_Default_Protection_Seconds;
	ac_pArmour[playerid] = armour;
	return SetPlayerArmour(playerid, armour);
}

#if defined _ALS_SetPlayerArmour
	#undef SetPlayerArmour
#else
	#define _ALS_SetPlayerArmour
#endif
#define SetPlayerArmour ac_SetPlayerArmour

stock ac_SetVehicleHealth(vehicleid, Float:health)
{
	ac_vLast_SetHealth[vehicleid] = gettime();
	ac_vHealth[vehicleid] = health;
	return SetVehicleHealth(vehicleid, health);
}

#if defined _ALS_SetVehicleHealth
	#undef SetVehicleHealth
#else
	#define _ALS_SetVehicleHealth
#endif
#define SetVehicleHealth ac_SetVehicleHealth

stock ac_RepairVehicle(vehicleid)
{
	ac_vLast_SetHealth[vehicleid] = gettime();
	ac_vHealth[vehicleid] = 1000.0;
	return RepairVehicle(vehicleid);
}

#if defined _ALS_RepairVehicle
	#undef RepairVehicle
#else
	#define _ALS_RepairVehicle
#endif
#define RepairVehicle ac_RepairVehicle

stock ac_Kick(playerid)
{
	pAcKicked[playerid] = true;
	return Kick(playerid);
}

#if defined _ALS_Kick
	#undef Kick
#else
	#define _ALS_Kick
#endif
#define Kick ac_Kick

stock ac_GetPlayerSpeed(vehicleid)
{
	new Float:xPos[3];
	GetPlayerVelocity(vehicleid, xPos[0], xPos[1], xPos[2]);
	return floatround(floatsqroot(xPos[0] * xPos[0] + xPos[1] * xPos[1] + xPos[2] * xPos[2]) * 170.00);
}

stock bool:ac_IsPlayerJumping(playerid)
{
	switch(GetPlayerAnimationIndex(playerid))
	{
		case 1195 .. 1198, 1438 .. 1440, 1061 .. 1064: return true;
	}

	return false;
}

stock ac_VehicleModelHasDoors(modelid)
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

stock ac_GetTickDiff(newtick, oldtick)
{
	if (oldtick < 0 && newtick >= 0) {
		return newtick - oldtick;
	} else if (oldtick >= 0 && newtick < 0 || oldtick > newtick) {
		return (cellmax - oldtick + 1) - (cellmin - newtick);
	}
	return newtick - oldtick;
}

stock ac_UpdateCheatDB(cheat)
{
	new query[128];
	mysql_format(anticheat_db, query, sizeof query, "UPDATE anticheats SET enabled = %d, detections = %d, in_seconds = %d, min_seconds = %d, kick = %d WHERE id = %d;", AcInfo[cheat][ac_ENABLED], AcInfo[cheat][ac_DETECTIONS], AcInfo[cheat][ac_IN_SECONDS], AcInfo[cheat][ac_MIN_SECONDS], AcInfo[cheat][ac_KICK], cheat);
	mysql_tquery(anticheat_db, query);
	return 1;
}

stock ac_UpdateVariablesDB()
{
	new query[128];
	mysql_format(anticheat_db, query, sizeof query, "UPDATE variables SET value = '%f' WHERE varname = 'teleport_distance';", ac_Teleport_Distance);
	mysql_tquery(anticheat_db, query);

	mysql_format(anticheat_db, query, sizeof query, "UPDATE variables SET value = '%f' WHERE varname = 'position_distance_foot';", ac_Position_Distance_Foot);
	mysql_tquery(anticheat_db, query);

	mysql_format(anticheat_db, query, sizeof query, "UPDATE variables SET value = '%f' WHERE varname = 'position_distance_vehicle';", ac_Position_Distance_Vehicle);
	mysql_tquery(anticheat_db, query);

	mysql_format(anticheat_db, query, sizeof query, "UPDATE variables SET value = '%f' WHERE varname = 'position_distance_vehicle_ms';", ac_Position_Distance_Vehicle_mS);
	mysql_tquery(anticheat_db, query);

	mysql_format(anticheat_db, query, sizeof query, "UPDATE variables SET value = '%d' WHERE varname = 'playerspeed_maxvalue';", ac_PlayerSpeed_MaxValue);
	mysql_tquery(anticheat_db, query);

	mysql_format(anticheat_db, query, sizeof query, "UPDATE variables SET value = '%d' WHERE varname = 'vehiclespeed_maxvalue';", ac_VehicleSpeed_MaxValue);
	mysql_tquery(anticheat_db, query);

	mysql_format(anticheat_db, query, sizeof query, "UPDATE variables SET value = '%d' WHERE varname = 'vehiclespeed_offset_maxvalue';", ac_VehicleSpeed_Offset_MaxValue);
	mysql_tquery(anticheat_db, query);

	mysql_format(anticheat_db, query, sizeof query, "UPDATE variables SET value = '%d' WHERE varname = 'default_protection_seconds';", ac_Default_Protection_Seconds);
	mysql_tquery(anticheat_db, query);

	mysql_format(anticheat_db, query, sizeof query, "UPDATE variables SET value = '%d' WHERE varname = 'default_flooder_maxinterval';", ac_Default_Flooder_MaxInterval);
	mysql_tquery(anticheat_db, query);
	return 1;
}
