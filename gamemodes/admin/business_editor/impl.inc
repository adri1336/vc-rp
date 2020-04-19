#include <YSI\y_hooks>

YCMD:ibusiness(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new index = GetBusinessIndexFromId(params[0]);
		if(index == -1) SendClientMessage(playerid, -1, "Invalid ID!");
		else
		{
			new dialog_message[256];
			format(dialog_message, sizeof dialog_message, 
				"ID: %d\nPrice: %d\nLevel: %d\nID player: %d\nName player: %s\nDoors: %d",
				BusinessData[index][bdata_ID], BusinessData[index][bdata_PRICE], BusinessData[index][bdata_LEVEL],
				BusinessData[index][bdata_ID_PLAYER], BusinessData[index][bdata_PLAYER_NAME], Iter_Count(BusinessDoors[index])
			);

			inline OnPlayerDialog(pid, did, res, lis, string:inp)
			{
				#pragma unused pid, did, res, lis, inp
			}
			Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "Business info", dialog_message, "X", "");
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /ibusiness <id>");
	return 1;
}

YCMD:itbusiness(playerid, params[], help)
{
	new dialog_message[256];
	format(dialog_message, sizeof dialog_message, 
		"Business: %d\nLimit: %d\nBusiness unsold: %d\nBusiness sold: %d\nBusiness no door: %d",
		CountBusiness(), MAX_BUSINESS, CountBusiness(1), CountBusiness(2), CountBusiness(3)
	);

	inline OnPlayerDialog(pid, did, res, lis, string:inp)
	{
		#pragma unused pid, did, res, lis, inp
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "Total business info", dialog_message, "X", "");
	return 1;
}

YCMD:lbusiness(playerid, params[], help)
{
	ToggleBusinessInfoLabels(!businessInfoLabels);
	if(businessInfoLabels) SendClientMessage(playerid, -1, "Business info labels on!");
	else SendClientMessage(playerid, -1, "Business info labels off!");
	return 1;
}

YCMD:abusiness(playerid, params[], help)
{
	new price, level, type, hour_open, hour_close, radio;
	if(!sscanf(params, "dddddd", price, level, type, hour_open, hour_close, radio))
	{
		if(type < 1 || type >= BUSINESS_TYPE_SIZE) SendClientMessage(playerid, -1, "Invalid type ID!");
		else
		{
			if(radio < 0 || radio >= sizeof Radios) SendClientMessage(playerid, -1, "Invalid radio ID!");
			else
			{
				new index = Iter_Free(BusinessData);
				if(index != cellmin)
				{
					inline OnBusinessInserted()
					{
						BusinessData[index][bdata_ID] = cache_insert_id();
						BusinessData[index][bdata_PRICE] = price;
						BusinessData[index][bdata_LEVEL] = level;
						BusinessData[index][bdata_ID_TYPE] = type;
						BusinessData[index][bdata_HOUR_OPEN] = hour_open;
						BusinessData[index][bdata_HOUR_CLOSE] = hour_close;
						BusinessData[index][bdata_MONEY] = BUSINESS_DEFAULT_MONEY;
						BusinessData[index][bdata_RADIO] = radio;
						Iter_Add(BusinessData, index);
						ResetBusinessProducts(index);

						new msg[128];
						format(msg, sizeof msg, "Business added (ID: %d)", BusinessData[index][bdata_ID]);
						SendClientMessage(playerid, -1, msg);
					}
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO business (id_type, price, level, money, hour_open, hour_close, radio) VALUES (%d, %d, %d, %d, %d, %d, %d);", type, price, level, BUSINESS_DEFAULT_MONEY, hour_open, hour_close, radio);
					mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnBusinessInserted, "");
				}
				else SendClientMessage(playerid, -1, "Array full!");
			}
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /abusiness <price> <level> <type> <hour_open> <hour_close> <radio>");
	return 1;
}

YCMD:abdoor(playerid, params[], help)
{
	if(!sscanf(params, "dd", params[0], params[1]))
	{
		new business_index = GetBusinessIndexFromId(params[0]);
		if(business_index == -1) SendClientMessage(playerid, -1, "Invalid business ID!");
		else
		{
			new interior_index = GetInteriorIndexByInteriorId(params[1]);
			if(interior_index == -1) SendClientMessage(playerid, -1, "Invalid interior ID!");
			else
			{
				new door_index = Iter_Free(BusinessDoors[business_index]);
				if(door_index != cellmin)
				{
					new Float:ext_pos[3], Float:ext_angle, entrance_index = -1, sub_id_index = -1;
					GetPlayerPos(playerid, ext_pos[0], ext_pos[1], ext_pos[2]);
					GetPlayerFacingAngle(playerid, ext_angle);
					if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_ENTRANCE) entrance_index = PI[playerid][pi_WORLD_STATE_INDEX];
					else if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_BUSINESS)
					{
						if(PI[playerid][pi_WORLD_STATE_INDEX] != business_index) return SendClientMessage(playerid, -1, "cmd businessID != current businessID");
						else sub_id_index = PI[playerid][pi_WORLD_STATE_EXTRA_INDEX];
					}

					inline OnBusinessDoorInserted()
					{
						BusinessDoors[business_index][door_index][bdoor_ID] = cache_insert_id();
						BusinessDoors[business_index][door_index][bdoor_EXT_X] = ext_pos[0];
						BusinessDoors[business_index][door_index][bdoor_EXT_Y] = ext_pos[1];
						BusinessDoors[business_index][door_index][bdoor_EXT_Z] = ext_pos[2];
						BusinessDoors[business_index][door_index][bdoor_EXT_ANGLE] = ext_angle;
						if(entrance_index == -1) BusinessDoors[business_index][door_index][bdoor_EXT_ENTRANCE_DOOR_ID] = 0;
						else BusinessDoors[business_index][door_index][bdoor_EXT_ENTRANCE_DOOR_ID] = Entrances[entrance_index][entrance_ID];
						if(sub_id_index == -1) BusinessDoors[business_index][door_index][bdoor_EXT_SUB_ID] = 0;
						else BusinessDoors[business_index][door_index][bdoor_EXT_SUB_ID] = BusinessDoors[business_index][sub_id_index][bdoor_ID];
						BusinessDoors[business_index][door_index][bdoor_ID_INTERIOR] = Interiors[interior_index][interior_ID];
						BusinessDoors[business_index][door_index][bdoor_INDEX_INTERIOR] = interior_index;
	
						if(BusinessDoors[business_index][door_index][bdoor_EXT_ENTRANCE_DOOR_ID]) BusinessDoors[business_index][door_index][bdoor_EXT_ENTRANCE_DOOR_INDEX] = entrance_index;
						else BusinessDoors[business_index][door_index][bdoor_EXT_ENTRANCE_DOOR_INDEX] = -1;

						if(BusinessDoors[business_index][door_index][bdoor_EXT_SUB_ID]) BusinessDoors[business_index][door_index][bdoor_EXT_SUB_INDEX] = sub_id_index;
						else BusinessDoors[business_index][door_index][bdoor_EXT_SUB_INDEX] = -1;

						Iter_Add(BusinessDoors[business_index], door_index);
						CreateBusinessDoorInfo(business_index, door_index);

						new msg[128];
						format(msg, sizeof msg, "Business door created (ID: %d)", BusinessDoors[business_index][door_index][bdoor_ID]);
						SendClientMessage(playerid, -1, msg);
					}

					new ext_entrance_door_id_Str[24] = "NULL",
						ext_sub_id_Str[24] = "NULL";
					if(entrance_index != -1) format(ext_entrance_door_id_Str, sizeof ext_entrance_door_id_Str, "%d", Entrances[entrance_index][entrance_ID]);
					if(sub_id_index != -1) format(ext_sub_id_Str, sizeof ext_sub_id_Str, "%d", BusinessDoors[business_index][sub_id_index][bdoor_ID]);
					mysql_format
					(
						vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, 
							"\
								INSERT INTO business_doors (id_business, ext_x, ext_y, ext_z, ext_angle, ext_entrance_door_id, ext_sub_id, id_interior) \
								VALUES (%d, %f, %f, %f, %f, %s, %s, %d);\
							",
							BusinessData[business_index][bdata_ID], ext_pos[0], ext_pos[1], ext_pos[2], ext_angle, ext_entrance_door_id_Str, ext_sub_id_Str, params[1]
					);
					mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnBusinessDoorInserted, "");
				}
				else SendClientMessage(playerid, -1, "Array full!");
			}
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /abdoor <ID Business> <ID Interior>");
	return 1;
}

YCMD:gbdoor(playerid, params[], help)
{
	if(!sscanf(params, "ddd", params[0], params[1], params[2]))
	{
		new business_index = GetBusinessIndexFromId(params[0]);
		if(business_index == -1) SendClientMessage(playerid, -1, "Invalid business ID!");
		else
		{
			new door_index = params[1];
			if(!Iter_Contains(BusinessDoors[business_index], door_index)) SendClientMessage(playerid, -1, "Invalid business ID!");
			else
			{
				if(params[2]) //ext
				{
					if(BusinessDoors[business_index][door_index][bdoor_EXT_ENTRANCE_DOOR_INDEX] != -1)
					{
						SetPlayerPosEx
						(
							playerid,
							BusinessDoors[business_index][door_index][bdoor_EXT_X],
							BusinessDoors[business_index][door_index][bdoor_EXT_Y],
							BusinessDoors[business_index][door_index][bdoor_EXT_Z],
							BusinessDoors[business_index][door_index][bdoor_EXT_ANGLE],
							Interiors[Entrances[ BusinessDoors[business_index][door_index][bdoor_EXT_ENTRANCE_DOOR_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID],
							Entrances[ BusinessDoors[business_index][door_index][bdoor_EXT_ENTRANCE_DOOR_INDEX] ][entrance_ID_ENTRANCE],
							false,
							true,
							true
						);
						SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_ENTRANCE, BusinessDoors[business_index][door_index][bdoor_EXT_ENTRANCE_DOOR_INDEX]);
					}
					else if(BusinessDoors[business_index][door_index][bdoor_EXT_SUB_INDEX] != -1)
					{
						SetPlayerPosEx
						(
							playerid,
							BusinessDoors[business_index][door_index][bdoor_EXT_X],
							BusinessDoors[business_index][door_index][bdoor_EXT_Y],
							BusinessDoors[business_index][door_index][bdoor_EXT_Z],
							BusinessDoors[business_index][door_index][bdoor_EXT_ANGLE],
							Interiors[ BusinessDoors[business_index][ BusinessDoors[business_index][door_index][bdoor_EXT_SUB_INDEX] ][bdoor_INDEX_INTERIOR] ][interior_INTERIORID],
							BusinessDoors[business_index][ BusinessDoors[business_index][door_index][bdoor_EXT_SUB_INDEX] ][bdoor_ID_BUSINESS],
							false,
							true,
							true
						);
						SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_BUSINESS, business_index, BusinessDoors[business_index][door_index][bdoor_EXT_SUB_INDEX]);
					}
					else
					{
						SetPlayerPosEx
						(
							playerid,
							BusinessDoors[business_index][door_index][bdoor_EXT_X],
							BusinessDoors[business_index][door_index][bdoor_EXT_Y],
							BusinessDoors[business_index][door_index][bdoor_EXT_Z],
							BusinessDoors[business_index][door_index][bdoor_EXT_ANGLE],
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
						Interiors[ BusinessDoors[business_index][door_index][bdoor_INDEX_INTERIOR] ][interior_X],
						Interiors[ BusinessDoors[business_index][door_index][bdoor_INDEX_INTERIOR] ][interior_Y],
						Interiors[ BusinessDoors[business_index][door_index][bdoor_INDEX_INTERIOR] ][interior_Z],
						Interiors[ BusinessDoors[business_index][door_index][bdoor_INDEX_INTERIOR] ][interior_ANGLE],
						Interiors[ BusinessDoors[business_index][door_index][bdoor_INDEX_INTERIOR] ][interior_INTERIORID],
						BusinessDoors[business_index][door_index][bdoor_ID_BUSINESS],
						false,
						true,
						true
					);
					SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_BUSINESS, business_index, door_index);
				}
			}
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /gbdoor <BusinessID> <DoorID> <0-int,1-ext>");
	return 1;
}

YCMD:ebusiness(playerid, params[], help)
{
	new id_business, price, level, type, hour_open, hour_close, radio;
	if(!sscanf(params, "ddddddd", id_business, price, level, type, hour_open, hour_close, radio))
	{
		new business_index = GetBusinessIndexFromId(params[0]);
		if(business_index == -1) SendClientMessage(playerid, -1, "Invalid business ID!");
		else
		{
			new old_type = BusinessData[business_index][bdata_ID_TYPE];
			BusinessData[business_index][bdata_PRICE] = price;
			BusinessData[business_index][bdata_LEVEL] = level;
			BusinessData[business_index][bdata_ID_TYPE] = type;
			BusinessData[business_index][bdata_HOUR_OPEN] = hour_open;
			BusinessData[business_index][bdata_HOUR_CLOSE] = hour_close;
			BusinessData[business_index][bdata_RADIO] = radio;
			UpdateBusinessData(business_index);
			if(old_type != BusinessData[business_index][bdata_ID_TYPE]) ResetBusinessProducts(business_index);
			SendClientMessage(playerid, -1, "Business edited!");
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /ebusiness <BusinessID> <price> <level> <type> <hour_open> <hour_close> <radio>");
	return 1;
}

YCMD:dbowner(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new business_index = GetBusinessIndexFromId(params[0]);
		if(business_index == -1) SendClientMessage(playerid, -1, "Invalid business ID!");
		else
		{
			if(!IsBusinessOccupied(business_index)) SendClientMessage(playerid, -1, "Business not occupied!");
			else
			{
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business SET id_player = NULL WHERE id = %d;", BusinessData[business_index][bdata_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
				BusinessData[business_index][bdata_ID_PLAYER] = 0;
				BusinessData[business_index][bdata_PLAYER_NAME][0] = EOS;
				DeleteBusinessKeys(BusinessData[business_index][bdata_ID], business_index);
				ResetBusinessProducts(business_index);
				SendClientMessage(playerid, -1, "Business owner deleted!");
			}
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /dbowner <BusinessID>");
	return 1;
}

YCMD:dbdoor(playerid, params[], help)
{
	if(!sscanf(params, "dd", params[0], params[1]))
	{
		new business_index = GetBusinessIndexFromId(params[0]);
		if(business_index == -1) SendClientMessage(playerid, -1, "Invalid business ID!");
		else
		{
			new door_index = GetBusinessDoorIndexFromId(business_index, params[1]);
			if(door_index == -1) SendClientMessage(playerid, -1, "Invalid door ID!");
			else
			{
				DeleteBusinessDoor(business_index, door_index, true, true);
				SendClientMessage(playerid, -1, "Business door deleted!");
			}
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /dbdoor <BusinessID> <DoorID>");
	return 1;
}

YCMD:dbusiness(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new business_index = GetBusinessIndexFromId(params[0]);
		if(business_index == -1) SendClientMessage(playerid, -1, "Invalid business ID!");
		else
		{
			//db
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM business WHERE id = %d;", BusinessData[business_index][bdata_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);

			//var
			foreach(new i : BusinessDoors[business_index])
			{
				DeletePropertyDoor(business_index, i, false, false);
			}
			Iter_Clear(BusinessDoors[business_index]);
			Iter_Remove(BusinessData, business_index);
			DeleteBusinessKeys(params[0], business_index);
			SendClientMessage(playerid, -1, "Business deleted!");
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /dbusiness <BusinessID>");
	return 1;
}