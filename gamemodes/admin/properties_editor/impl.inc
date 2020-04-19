#include <YSI\y_hooks>

YCMD:iproperty(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new index = GetPropertyIndexFromId(params[0]);
		if(index == -1) SendClientMessage(playerid, -1, "Invalid ID!");
		else
		{
			new dialog_message[256];
			format(dialog_message, sizeof dialog_message, 
				"ID: %d\nPrice: %d\nLevel: %d\nRent: %d\nRent expire date: %s\nID player: %d\nName player: %s\nDoors: %d",
				PropertyInfo[index][property_ID], PropertyInfo[index][property_PRICE], PropertyInfo[index][property_LEVEL],
				PropertyInfo[index][property_RENT], PropertyInfo[index][property_RENT_EXPIRE_DATE], PropertyInfo[index][property_ID_PLAYER],
				PropertyInfo[index][property_PLAYER_NAME], Iter_Count(PropertyDoor[index])
			);

			inline OnPlayerDialog(pid, did, res, lis, string:inp)
			{
				#pragma unused pid, did, res, lis, inp
			}
			Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "Property info", dialog_message, "X", "");
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /iproperty <id>");
	return 1;
}

YCMD:iproperties(playerid, params[], help)
{
	new dialog_message[256];
	format(dialog_message, sizeof dialog_message, 
		"Properties: %d\nLimit: %d\nProperties unsold: %d\nProperties for sale unsold: %d\nProperties for rent unsold: %d\nProperties sold: %d\nProperties for sale sold: %d\nProperties for rent sold: %d\nProperties no door: %d",
		CountProperties(), MAX_PROPERTIES, CountProperties(1), CountProperties(2), CountProperties(3), CountProperties(4),
		CountProperties(5), CountProperties(6), CountProperties(7)
	);

	inline OnPlayerDialog(pid, did, res, lis, string:inp)
	{
		#pragma unused pid, did, res, lis, inp
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "Properties info", dialog_message, "X", "");
	return 1;
}

YCMD:lproperties(playerid, params[], help)
{
	TogglePropertiesInfoLabels(!propertiesInfoLabels);
	if(propertiesInfoLabels) SendClientMessage(playerid, -1, "Properties info labels on!");
	else SendClientMessage(playerid, -1, "Properties info labels off!");
	return 1;
}

YCMD:aproperty(playerid, params[], help)
{
	new price, level, rent;
	if(!sscanf(params, "ddd", price, level, rent))
	{
		new index = Iter_Free(PropertyInfo);
		if(index != cellmin)
		{
			inline OnPropertyInserted()
			{
				PropertyInfo[index][property_ID] = cache_insert_id();
				PropertyInfo[index][property_PRICE] = price;
				PropertyInfo[index][property_LEVEL] = level;
				PropertyInfo[index][property_RENT] = rent;
				Iter_Add(PropertyInfo, index);

				new msg[128];
				format(msg, sizeof msg, "Property added (ID: %d)", PropertyInfo[index][property_ID]);
				SendClientMessage(playerid, -1, msg);
			}
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO properties (price, level, rent) VALUES (%d, %d, %d);", price, level, rent);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnPropertyInserted, "");
		}
		else SendClientMessage(playerid, -1, "Array full!");
	}
	else SendClientMessage(playerid, -1, "Syntax: /aproperty <price> <level> <rent>");
	return 1;
}

YCMD:apdoor(playerid, params[], help)
{
	if(!sscanf(params, "dd", params[0], params[1]))
	{
		new property_index = GetPropertyIndexFromId(params[0]);
		if(property_index == -1) SendClientMessage(playerid, -1, "Invalid property ID!");
		else
		{
			new interior_index = GetInteriorIndexByInteriorId(params[1]);
			if(interior_index == -1) SendClientMessage(playerid, -1, "Invalid interior ID!");
			else
			{
				new door_index = Iter_Free(PropertyDoor[property_index]);
				if(door_index != cellmin)
				{
					new Float:ext_pos[3], Float:ext_angle, entrance_index = -1, sub_id_index = -1;
					GetPlayerPos(playerid, ext_pos[0], ext_pos[1], ext_pos[2]);
					GetPlayerFacingAngle(playerid, ext_angle);
					if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_ENTRANCE) entrance_index = PI[playerid][pi_WORLD_STATE_INDEX];
					else if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_PROPERTY)
					{
						if(PI[playerid][pi_WORLD_STATE_INDEX] != property_index) return SendClientMessage(playerid, -1, "cmd propertyID != current propertyID");
						else sub_id_index = PI[playerid][pi_WORLD_STATE_EXTRA_INDEX];
					}

					inline OnPropertyDoorInserted()
					{
						PropertyDoor[property_index][door_index][prop_door_ID] = cache_insert_id();
						PropertyDoor[property_index][door_index][prop_door_EXT_X] = ext_pos[0];
						PropertyDoor[property_index][door_index][prop_door_EXT_Y] = ext_pos[1];
						PropertyDoor[property_index][door_index][prop_door_EXT_Z] = ext_pos[2];
						PropertyDoor[property_index][door_index][prop_door_EXT_ANGLE] = ext_angle;
						if(entrance_index == -1) PropertyDoor[property_index][door_index][prop_door_EXT_ENTRANCE_DOOR_ID] = 0;
						else PropertyDoor[property_index][door_index][prop_door_EXT_ENTRANCE_DOOR_ID] = Entrances[entrance_index][entrance_ID];
						if(sub_id_index == -1) PropertyDoor[property_index][door_index][prop_door_EXT_SUB_ID] = 0;
						else PropertyDoor[property_index][door_index][prop_door_EXT_SUB_ID] = PropertyDoor[property_index][sub_id_index][prop_door_ID];
						PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR] = Interiors[interior_index][interior_ID];
						PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] = interior_index;
	
						if(PropertyDoor[property_index][door_index][prop_door_EXT_ENTRANCE_DOOR_ID]) PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] = entrance_index;
						else PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] = -1;

						if(PropertyDoor[property_index][door_index][prop_door_EXT_SUB_ID]) PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] = sub_id_index;
						else PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] = -1;

						Iter_Add(PropertyDoor[property_index], door_index);
						CreatePropertyDoorInfo(property_index, door_index);

						new msg[128];
						format(msg, sizeof msg, "Property door created (ID: %d)", PropertyDoor[property_index][door_index][prop_door_ID]);
						SendClientMessage(playerid, -1, msg);
					}

					new ext_entrance_door_id_Str[24] = "NULL",
						ext_sub_id_Str[24] = "NULL";
					if(entrance_index != -1) format(ext_entrance_door_id_Str, sizeof ext_entrance_door_id_Str, "%d", Entrances[entrance_index][entrance_ID]);
					if(sub_id_index != -1) format(ext_sub_id_Str, sizeof ext_sub_id_Str, "%d", PropertyDoor[property_index][sub_id_index][prop_door_ID]);
					mysql_format
					(
						vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, 
							"\
								INSERT INTO properties_doors (id_property, ext_x, ext_y, ext_z, ext_angle, ext_entrance_door_id, ext_sub_id, id_interior) \
								VALUES (%d, %f, %f, %f, %f, %s, %s, %d);\
							",
							PropertyInfo[property_index][property_ID], ext_pos[0], ext_pos[1], ext_pos[2], ext_angle, ext_entrance_door_id_Str, ext_sub_id_Str, params[1]
					);
					mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnPropertyDoorInserted, "");
				}
				else SendClientMessage(playerid, -1, "Array full!");
			}
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /apdoor <ID Property> <ID Interior>");
	return 1;
}

YCMD:gpdoor(playerid, params[], help)
{
	if(!sscanf(params, "ddd", params[0], params[1], params[2]))
	{
		new property_index = GetPropertyIndexFromId(params[0]);
		if(property_index == -1) SendClientMessage(playerid, -1, "Invalid property ID!");
		else
		{
			new door_index = params[1]; /*GetPropertyDoorIndexFromId(property_index, params[1]);*/
			if(!Iter_Contains(PropertyDoor[property_index], door_index)) SendClientMessage(playerid, -1, "Invalid door ID!");
			else
			{
				if(params[2]) //ext
				{
					if(PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] != -1)
					{
						SetPlayerPosEx
						(
							playerid,
							PropertyDoor[property_index][door_index][prop_door_EXT_X],
							PropertyDoor[property_index][door_index][prop_door_EXT_Y],
							PropertyDoor[property_index][door_index][prop_door_EXT_Z],
							PropertyDoor[property_index][door_index][prop_door_EXT_ANGLE],
							Interiors[Entrances[ PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID],
							Entrances[ PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_ID_ENTRANCE],
							false,
							true,
							true
						);
						SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_ENTRANCE, PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX]);
					}
					else if(PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] != -1)
					{
						SetPlayerPosEx
						(
							playerid,
							PropertyDoor[property_index][door_index][prop_door_EXT_X],
							PropertyDoor[property_index][door_index][prop_door_EXT_Y],
							PropertyDoor[property_index][door_index][prop_door_EXT_Z],
							PropertyDoor[property_index][door_index][prop_door_EXT_ANGLE],
							Interiors[ PropertyDoor[property_index][ PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] ][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID],
							PropertyDoor[property_index][ PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] ][prop_door_ID_PROPERTY],
							false,
							true,
							true
						);
						SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_PROPERTY, property_index, PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX]);
					}
					else
					{
						SetPlayerPosEx
						(
							playerid,
							PropertyDoor[property_index][door_index][prop_door_EXT_X],
							PropertyDoor[property_index][door_index][prop_door_EXT_Y],
							PropertyDoor[property_index][door_index][prop_door_EXT_Z],
							PropertyDoor[property_index][door_index][prop_door_EXT_ANGLE],
							0,
							VC_WORLD,
							false,
							true,
							true
						);
						SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
					}
				}
				else //int
				{
					SetPlayerPosEx
					(
						playerid,
						Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_X],
						Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_Y],
						Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_Z],
						Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_ANGLE],
						Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID],
						PropertyDoor[property_index][door_index][prop_door_ID_PROPERTY],
						false,
						true,
						true
					);
					SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_PROPERTY, property_index, door_index);
				}
			}
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /gpdoor <PropertyID> <DoorID> <0-int,1-ext>");
	return 1;
}

YCMD:eproperty(playerid, params[], help)
{
	if(!sscanf(params, "dddd", params[0], params[1], params[2], params[3]))
	{
		new property_index = GetPropertyIndexFromId(params[0]);
		if(property_index == -1) SendClientMessage(playerid, -1, "Invalid property ID!");
		else
		{
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties SET price = %d, level = %d, rent = %d WHERE id = %d;", params[1], params[2], params[3], PropertyInfo[property_index][property_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);

			PropertyInfo[property_index][property_PRICE] = params[1];
			PropertyInfo[property_index][property_LEVEL] = params[2];
			PropertyInfo[property_index][property_RENT] = params[3];
			SendClientMessage(playerid, -1, "Property edited!");
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /eproperty <PropertyID> <price> <level> <rent>");
	return 1;
}

YCMD:dpowner(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new property_index = GetPropertyIndexFromId(params[0]);
		if(property_index == -1) SendClientMessage(playerid, -1, "Invalid property ID!");
		else
		{
			if(!IsPropertyOccupied(property_index)) SendClientMessage(playerid, -1, "Property not occupied!");
			else
			{
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties SET id_player = NULL WHERE id = %d;", PropertyInfo[property_index][property_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
				PropertyInfo[property_index][property_ID_PLAYER] = 0;
				PropertyInfo[property_index][property_PLAYER_NAME][0] = EOS;
				DeletePropertyKeys(PropertyInfo[property_index][property_ID], false, property_index);
				SendClientMessage(playerid, -1, "Property owner deleted!");
			}
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /dpowner <PropertyID>");
	return 1;
}

YCMD:dpdoor(playerid, params[], help)
{
	if(!sscanf(params, "dd", params[0], params[1]))
	{
		new property_index = GetPropertyIndexFromId(params[0]);
		if(property_index == -1) SendClientMessage(playerid, -1, "Invalid property ID!");
		else
		{
			new door_index = GetPropertyDoorIndexFromId(property_index, params[1]);
			if(door_index == -1) SendClientMessage(playerid, -1, "Invalid door ID!");
			else
			{
				DeletePropertyDoor(property_index, door_index, true, true);
				SendClientMessage(playerid, -1, "Property door deleted!");
			}
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /dpdoor <PropertyID> <DoorID>");
	return 1;
}

YCMD:dproperty(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new property_index = GetPropertyIndexFromId(params[0]);
		if(property_index == -1) SendClientMessage(playerid, -1, "Invalid property ID!");
		else
		{
			//db
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM properties WHERE id = %d;", PropertyInfo[property_index][property_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);

			//var
			foreach(new i : PropertyDoor[property_index])
			{
				DeletePropertyDoor(property_index, i, false, false);
			}
			Iter_Clear(PropertyDoor[property_index]);
			Iter_Remove(PropertyInfo, property_index);
			DeletePropertyKeys(params[0], false, property_index);
			SendClientMessage(playerid, -1, "Property deleted!");
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /dproperty <PropertyID>");
	return 1;
}