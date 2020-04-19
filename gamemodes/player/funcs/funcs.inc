SetRolePlayNames(playerid)
{
	new name[24], bool:underscore;
	format(name, 24, "%s", PI[playerid][pi_NAME]);
	format(PI[playerid][pi_RP_NAME], 24, "%s", name);
	for(new i = 0; i < 24; i++)
	{
		if(name[i] == '_')
		{
			PI[playerid][pi_RP_NAME][i] = ' ';
			if(!underscore)
			{
				strmid(PI[playerid][pi_FIRST_NAME], name, 0, i);
				strmid(PI[playerid][pi_SUB_NAME], name, i + 1, 24);
				underscore = true;
			}
		}
	}
	return 1;
}

SavePlayerWorldInfo(playerid, bool:update = false)
{
	GetPlayerPos(playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z]);
	GetPlayerFacingAngle(playerid, PI[playerid][pi_ANGLE]);
	PI[playerid][pi_WORLDID] = GetPlayerVirtualWorld(playerid);
	PI[playerid][pi_INTERIORID] = GetPlayerInterior(playerid);
	GetPlayerHealth(playerid, PI[playerid][pi_HEALTH]);
	GetPlayerArmour(playerid, PI[playerid][pi_ARMOUR]);

	if(update)
	{
		if(PI[playerid][pi_ID]) orm_update(PI[playerid][pi_ORM]);
	}
	return 1;
}

CleanPlayerChat(playerid, messages = 32)
{
	for(new i = 0; i != messages; i ++) SendClientMessage(playerid, -1, " ");
	return 1;
}

GivePlayerMoneyEx(playerid, amount, bool:info = true)
{
	#pragma unused info
	PI[playerid][pi_MONEY] += amount;
	
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, PI[playerid][pi_MONEY]);

	if(info && amount != 0)
	{
		new string[32];
		if(amount >= 0) format(string, sizeof string, "~g~+$%d", amount);
		else format(string, sizeof string, "~r~-$%d", amount * -1);
		GameTextForPlayer(playerid, string, 1, 1);
	}
	return 1;
}

SetPlayerMoney(playerid)
{
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, PI[playerid][pi_MONEY]);
	return 1;
}

Float:GetPlayerRepPercent(playerid, rep_mul)
{
	new Float:percent;
	percent = floatdiv(PI[playerid][pi_REPUTATION], floatmul(float(PI[playerid][pi_LEVEL]), float(rep_mul))) * 100.0;
	return percent;
}

SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, Float:angle = -1.0, interiorid = -1, worldid = -1, bool:freeze = false, bool:offset = false, bool:hidemsg = false)
{
	if(offset)
	{
		x += (1.5 * floatsin(-angle, degrees));
		y += (1.5 * floatcos(-angle, degrees));
	}

	SetPlayerPos(playerid, x, y, z);
	if(angle != -1.0) SetPlayerFacingAngle(playerid, angle);
	if(interiorid != -1) SetPlayerInterior(playerid, interiorid);
	if(worldid != -1) SetPlayerVirtualWorld(playerid, worldid);
	if(freeze) FreezePlayerTimed(playerid);
	if(hidemsg) HidePlayerInfoMessage(playerid);
	SetCameraBehindPlayer(playerid);
	return 1;
}

GetPlayerExteriorPos(playerid, &Float:X, &Float:Y, &Float:Z, &Float:Angle, &interiorid, &worldid, bool:radar = false)
{
	switch(PI[playerid][pi_WORLD_STATE])
	{
		case PLAYER_WORLD_STATE_ENTRANCE:
		{
			new real_index = GetRealEntranceIndex(PI[playerid][pi_WORLD_STATE_INDEX]);
			if(radar && Entrances[real_index][entrance_ID_ENTRANCE] == 7) //north point
			{
				GetPlayerPos(playerid, X, Y, Z);
				GetPlayerFacingAngle(playerid, Angle);
			}
			else
			{
				X = Entrances[real_index][entrance_X];
				Y = Entrances[real_index][entrance_Y];
				Z = Entrances[real_index][entrance_Z];
				Angle = Entrances[real_index][entrance_ANGLE];
			}
			interiorid = 0;
			worldid = VC_WORLD;
		}
		case PLAYER_WORLD_STATE_PROPERTY:
		{
			new property_index = PI[playerid][pi_WORLD_STATE_INDEX], door_index = PI[playerid][pi_WORLD_STATE_EXTRA_INDEX];
			if(PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] != -1)
			{
				new real_index = GetRealPropertyDoorIndex(property_index, door_index);
				if(PropertyDoor[property_index][real_index][prop_door_EXT_ENTR_DOOR_INDEX] != -1)
				{
					real_index = GetRealEntranceIndex(PropertyDoor[property_index][real_index][prop_door_EXT_ENTR_DOOR_INDEX]);
					X = Entrances[real_index][entrance_X];
					Y = Entrances[real_index][entrance_Y];
					Z = Entrances[real_index][entrance_Z];
					Angle = Entrances[real_index][entrance_ANGLE];
					interiorid = 0;
					worldid = VC_WORLD;
				}
				else
				{
					X = PropertyDoor[property_index][real_index][prop_door_EXT_X];
					Y = PropertyDoor[property_index][real_index][prop_door_EXT_Y];
					Z = PropertyDoor[property_index][real_index][prop_door_EXT_Z];
					Angle = PropertyDoor[property_index][real_index][prop_door_EXT_ANGLE];
					interiorid = 0;
					worldid = VC_WORLD;
				}
			}
			else if(PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] != -1)
			{
				new real_index = GetRealEntranceIndex(PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX]);
				X = Entrances[real_index][entrance_X];
				Y = Entrances[real_index][entrance_Y];
				Z = Entrances[real_index][entrance_Z];
				Angle = Entrances[real_index][entrance_ANGLE];
				interiorid = 0;
				worldid = VC_WORLD;
			}
			else
			{
				X = PropertyDoor[property_index][door_index][prop_door_EXT_X];
				Y = PropertyDoor[property_index][door_index][prop_door_EXT_Y];
				Z = PropertyDoor[property_index][door_index][prop_door_EXT_Z];
				Angle = PropertyDoor[property_index][door_index][prop_door_EXT_ANGLE];
				interiorid = 0;
				worldid = VC_WORLD;
			}
		}
		case PLAYER_WORLD_STATE_BUSINESS:
		{
			new business_index = PI[playerid][pi_WORLD_STATE_INDEX], door_index = PI[playerid][pi_WORLD_STATE_EXTRA_INDEX];
			if(BusinessDoors[business_index][door_index][bdoor_EXT_SUB_INDEX] != -1)
			{
				new real_index = GetRealBusinessDoorIndex(business_index, door_index);
				if(BusinessDoors[business_index][real_index][bdoor_EXT_ENTRANCE_DOOR_INDEX] != -1)
				{
					new entrance_real_index = GetRealEntranceIndex(BusinessDoors[business_index][real_index][bdoor_EXT_ENTRANCE_DOOR_INDEX]);
					if(radar && Entrances[entrance_real_index][entrance_ID_ENTRANCE] == 7) //north point
					{
						X = BusinessDoors[business_index][real_index][bdoor_EXT_X];
						Y = BusinessDoors[business_index][real_index][bdoor_EXT_Y];
						Z = BusinessDoors[business_index][real_index][bdoor_EXT_Z];
						Angle = BusinessDoors[business_index][real_index][bdoor_EXT_ANGLE];
					}
					else
					{
						X = Entrances[entrance_real_index][entrance_X];
						Y = Entrances[entrance_real_index][entrance_Y];
						Z = Entrances[entrance_real_index][entrance_Z];
						Angle = Entrances[entrance_real_index][entrance_ANGLE];
					}
					interiorid = 0;
					worldid = VC_WORLD;
				}
				else
				{
					X = BusinessDoors[business_index][real_index][bdoor_EXT_X];
					Y = BusinessDoors[business_index][real_index][bdoor_EXT_Y];
					Z = BusinessDoors[business_index][real_index][bdoor_EXT_Z];
					Angle = BusinessDoors[business_index][real_index][bdoor_EXT_ANGLE];
					interiorid = 0;
					worldid = VC_WORLD;
				}
			}
			else if(BusinessDoors[business_index][door_index][bdoor_EXT_ENTRANCE_DOOR_INDEX] != -1)
			{
				new entrance_real_index = GetRealEntranceIndex(BusinessDoors[business_index][door_index][bdoor_EXT_ENTRANCE_DOOR_INDEX]);
				if(radar && Entrances[entrance_real_index][entrance_ID_ENTRANCE] == 7) //north point
				{
					X = BusinessDoors[business_index][door_index][bdoor_EXT_X];
					Y = BusinessDoors[business_index][door_index][bdoor_EXT_Y];
					Z = BusinessDoors[business_index][door_index][bdoor_EXT_Z];
					Angle = BusinessDoors[business_index][door_index][bdoor_EXT_ANGLE];
				}
				else
				{
					X = Entrances[entrance_real_index][entrance_X];
					Y = Entrances[entrance_real_index][entrance_Y];
					Z = Entrances[entrance_real_index][entrance_Z];
					Angle = Entrances[entrance_real_index][entrance_ANGLE];
				}
				interiorid = 0;
				worldid = VC_WORLD;
			}
			else
			{
				X = BusinessDoors[business_index][door_index][bdoor_EXT_X];
				Y = BusinessDoors[business_index][door_index][bdoor_EXT_Y];
				Z = BusinessDoors[business_index][door_index][bdoor_EXT_Z];
				Angle = BusinessDoors[business_index][door_index][bdoor_EXT_ANGLE];
				interiorid = 0;
				worldid = VC_WORLD;
			}
		}
		case PLAYER_WORLD_STATE_OTHER:
		{
			switch(PI[playerid][pi_WORLD_STATE_INDEX])
			{
				case 0: //Autoescuela
				{
					if(radar)
					{
						GetPlayerPos(playerid, X, Y, Z);
						GetPlayerFacingAngle(playerid, Angle);
						interiorid = GetPlayerInterior(playerid);
						worldid = GetPlayerVirtualWorld(playerid);
					}
					else
					{
						X = Driving_School_Ext_Pos[0];
						Y = Driving_School_Ext_Pos[1];
						Z = Driving_School_Ext_Pos[2];
						Angle = Driving_School_Ext_Pos[3];
						interiorid = 0;
						worldid = VC_WORLD;
					}
				}
			}
		}
		default:
		{
			GetPlayerPos(playerid, X, Y, Z);
			GetPlayerFacingAngle(playerid, Angle);
			interiorid = GetPlayerInterior(playerid);
			worldid = GetPlayerVirtualWorld(playerid);
		}
	}
	return 1;
}

GetNearestHospitalForPlayer(playerid)
{
	new
		Float:player_pos[4], player_interiorid, player_worldid,
		Float:distance = 99999.0,
		Float:tmp_distance,
		closest = 0;

	GetPlayerExteriorPos(playerid, player_pos[0], player_pos[1], player_pos[2], player_pos[3], player_interiorid, player_worldid);
	foreach(new i : HospitalsEntrances)
	{ 
		tmp_distance = GetDistanceBetweenPoints3D(player_pos[0], player_pos[1], player_pos[2], Entrances[HospitalsEntrances[i]][entrance_X], Entrances[HospitalsEntrances[i]][entrance_Y], Entrances[HospitalsEntrances[i]][entrance_Z]);
		if (tmp_distance < distance) 
		{ 
			distance = tmp_distance; 
			closest = i;
		} 
	}
	return closest;
}

SetPlayerLanguageGroup(playerid)
{

	format(PI[playerid][pi_LANG], 3, "ES");
	Langs_SetPlayerLanguage(playerid, Language:LANGUAGE_SPANISH);
	Group_SetPlayer(g_lang_groups[LANGUAGE_SPANISH], playerid, true);
	PI[playerid][pi_LANG_ID] = Language:LANGUAGE_SPANISH;

/*	Group_SetPlayer(g_lang_groups[LANGUAGE_SPANISH], playerid, false);
	Group_SetPlayer(g_lang_groups[LANGUAGE_ENGLISH], playerid, false);
	Group_SetPlayer(g_lang_groups[LANGUAGE_PORTUGUESE], playerid, false);

	if(!strcmp(PI[playerid][pi_LANG], "EN"))
	{
		Langs_SetPlayerLanguage(playerid, Language:LANGUAGE_ENGLISH);
		Group_SetPlayer(g_lang_groups[LANGUAGE_ENGLISH], playerid, true);
		PI[playerid][pi_LANG_ID] = Language:LANGUAGE_ENGLISH;
	}
	else if(!strcmp(PI[playerid][pi_LANG], "PT"))
	{
		Langs_SetPlayerLanguage(playerid, Language:LANGUAGE_PORTUGUESE);
		Group_SetPlayer(g_lang_groups[LANGUAGE_PORTUGUESE], playerid, true);
		PI[playerid][pi_LANG_ID] = Language:LANGUAGE_PORTUGUESE;
	}
	else
	{
		format(PI[playerid][pi_LANG], 3, "ES");
		Langs_SetPlayerLanguage(playerid, Language:LANGUAGE_SPANISH);
		Group_SetPlayer(g_lang_groups[LANGUAGE_SPANISH], playerid, true);
		PI[playerid][pi_LANG_ID] = Language:LANGUAGE_SPANISH;
	}*/
	return 1;
}

GetPlayeridFromId(id)
{
	if(id)
	{
		foreach(new i : Player)
		{
			if(PI[i][pi_ID] == id)
			{
				return i;
			}
		}
	}
	return INVALID_PLAYER_ID;
}

stock TogglePlayerWideScreen(playerid, toggle)
{
	#pragma unused playerid, toggle
/*	new BitStream:bs = BS_New();
	BS_WriteValue(bs, PR_BOOL, toggle);

	BS_RPC(bs, playerid, 111);
	BS_Delete(bs);*/
	return 1;
}

GetRealEntranceIndex(entranceindex)
{
	if(entranceindex == -1) return -1;

	new buffer = entranceindex,
		real_index;

	while(buffer != -1)
	{
		real_index = buffer;
		buffer = Entrances[real_index][entrance_SUB_ID_INDEX];
	}
	return real_index;
}

GetRealPropertyDoorIndex(property_index, door_index)
{
	if(property_index == -1 || door_index == -1) return -1;

	new buffer = door_index,
		real_index;

	while(buffer != -1)
	{
		real_index = buffer;
		buffer = PropertyDoor[property_index][real_index][prop_door_EXT_SUB_INDEX];
	}
	return real_index;
}

GetRealBusinessDoorIndex(business_index, door_index)
{
	if(business_index == -1 || door_index == -1) return -1;

	new buffer = door_index,
		real_index;

	while(buffer != -1)
	{
		real_index = buffer;
		buffer = BusinessDoors[business_index][real_index][bdoor_EXT_SUB_INDEX];
	}
	return real_index;
}

GivePlayerHealth(playerid, Float:amount)
{
	GetPlayerHealth(playerid, PI[playerid][pi_HEALTH]);
	PI[playerid][pi_HEALTH] += amount;
	return SetPlayerHealth(playerid, PI[playerid][pi_HEALTH]);
}

SetPlayerHealthEx(playerid, Float:health)
{
	PI[playerid][pi_HEALTH] = health;
	return SetPlayerHealth(playerid, health);
}

SetPlayerArmourEx(playerid, Float:armour)
{
	PI[playerid][pi_ARMOUR] = armour;
	return SetPlayerArmour(playerid, armour);
}

SavePlayerWorldInfo_DB(playerid)
{
	SavePlayerWorldInfo(playerid);
	if(PI[playerid][pi_WORLD_STATE] != PLAYER_WORLD_STATE_STREET)
	{
		if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_PROPERTY)
		{
			if(GetPropertyOwner(PI[playerid][pi_WORLD_STATE_INDEX]) == PI[playerid][pi_ID]) return 1;
		}
		if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_BUSINESS)
		{
			if(GetBusinessOwner(PI[playerid][pi_WORLD_STATE_INDEX]) == PI[playerid][pi_ID]) return 1;
		}
		GetPlayerExteriorPos(playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], PI[playerid][pi_INTERIORID], PI[playerid][pi_WORLDID]);
		SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
	}
	return 1;
}

SetPlayerWorldDefaultInfo(playerid)
{
	PI[playerid][pi_X] = New_User_Pos[0];
	PI[playerid][pi_Y] = New_User_Pos[1];
	PI[playerid][pi_Z] = New_User_Pos[2];
	PI[playerid][pi_ANGLE] = New_User_Pos[3];
	PI[playerid][pi_WORLDID] = VC_WORLD;
	PI[playerid][pi_INTERIORID] = 0;
	PI[playerid][pi_WORLD_STATE_INDEX] = -1;
	PI[playerid][pi_WORLD_STATE_EXTRA_INDEX] = -1;
	PI[playerid][pi_WORLD_STATE_ID] = 0;
	PI[playerid][pi_WORLD_STATE_EXTRA_ID] = 0;
	PI[playerid][pi_WORLD_STATE] = PLAYER_WORLD_STATE_STREET;
	return 1;
}

GetPlayerObjectiveColor(playerid)
{
	switch(GetPlayerJobId(playerid))
	{
		case JOB_TAXI: return 0xfb9403FF;
	}
	return -1;
}