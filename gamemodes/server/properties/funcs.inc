loadtext lang[server_properties];

GetPropertyIndexFromId(id)
{
	foreach(new i : PropertyInfo)
	{
		if(PropertyInfo[i][property_ID] == id)
		{
			return i;
		}
	}
	return -1;
}

GetPropertyDoorIndexFromId(index_property, id)
{
	foreach(new i : PropertyDoor[index_property])
	{
		if(PropertyDoor[index_property][i][prop_door_ID] == id)
		{
			return i;
		}
	}
	return -1;
}

#define IsPropertyForRent(%0) PropertyInfo[%0][property_RENT]
#define IsPropertyOccupied(%0) PropertyInfo[%0][property_ID_PLAYER]
#define IsPropertyDoorClosed(%0,%1) PropertyDoor[%0][%1][prop_door_CLOSED]
#define GetPropertyOwner(%0) PropertyInfo[%0][property_ID_PLAYER]


CreatePropertyDoorInfo(property_index, door_index)
{
	#if CUSTOM_PICKUPS == true
		if(PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicObject(PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID]);
			PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#else
		if(PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicPickup(PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID]);
			PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#endif

	if(PropertyDoor[property_index][door_index][prop_door_EXT_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(PropertyDoor[property_index][door_index][prop_door_EXT_AREA_ID]);
		PropertyDoor[property_index][door_index][prop_door_EXT_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(PropertyDoor[property_index][door_index][prop_door_EXT_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(PropertyDoor[property_index][door_index][prop_door_EXT_LABEL_AREA_ID]);
		PropertyDoor[property_index][door_index][prop_door_EXT_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(PropertyDoor[property_index][door_index][prop_door_INT_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(PropertyDoor[property_index][door_index][prop_door_INT_AREA_ID]);
		PropertyDoor[property_index][door_index][prop_door_INT_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(PropertyDoor[property_index][door_index][prop_door_INT_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(PropertyDoor[property_index][door_index][prop_door_INT_LABEL_AREA_ID]);
		PropertyDoor[property_index][door_index][prop_door_INT_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}
	
	//
	#if CUSTOM_PICKUPS == true
		if(PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] != -1) PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] = CreateDynamicObject(CUSTOM_PICKUP_MODELID, PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z], 0.0, 0.0, 0.0, .worldid = Entrances[ PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_ID_ENTRANCE], .interiorid = Interiors[Entrances[ PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID], .streamdistance = PICKUP_DISTANCE, .drawdistance = PICKUP_DISTANCE, .priority = 10);	
		else if(PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] != -1) PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] = CreateDynamicObject(CUSTOM_PICKUP_MODELID, PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z], 0.0, 0.0, 0.0, PropertyDoor[property_index][door_index][prop_door_ID_PROPERTY], Interiors[ PropertyDoor[property_index][ PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] ][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID], .streamdistance = PICKUP_DISTANCE, .drawdistance = PICKUP_DISTANCE, .priority = 10);	
		else PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] = CreateDynamicObject(CUSTOM_PICKUP_MODELID, PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z], 0.0, 0.0, 0.0, VC_WORLD, 0, .streamdistance = PICKUP_DISTANCE, .drawdistance = PICKUP_DISTANCE, .priority = 10);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID], E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_PICKUP_PROP_DOOR);
	#else
		new pickup_model = 1273;
		if(IsPropertySold(property_index)) pickup_model = 1318;

		if(PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] != -1) PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] = CreateDynamicPickup(pickup_model, 1, PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z], Entrances[ PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_ID_ENTRANCE], Interiors[Entrances[ PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID], .streamdistance = PICKUP_DISTANCE, .priority = 10);
		else if(PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] != -1) PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] = CreateDynamicPickup(pickup_model, 1, PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z], PropertyDoor[property_index][door_index][prop_door_ID_PROPERTY], Interiors[ PropertyDoor[property_index][ PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] ][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID], .streamdistance = PICKUP_DISTANCE, .priority = 10);
		else PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] = CreateDynamicPickup(pickup_model, 1, PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z], VC_WORLD, 0, .streamdistance = PICKUP_DISTANCE, .priority = 10);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID], E_STREAMER_EXTRA_ID, _:PICKUP_TYPE_PICKUP_PROP_DOOR);
	#endif

	new streamer_info[3];
	if(PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] != -1) PropertyDoor[property_index][door_index][prop_door_EXT_AREA_ID] = CreateDynamicCylinder(PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z] - 1.0, PropertyDoor[property_index][door_index][prop_door_EXT_Z] + 3.0, 1.0, Entrances[ PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_ID_ENTRANCE], Interiors[Entrances[ PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
	else if(PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] != -1) PropertyDoor[property_index][door_index][prop_door_EXT_AREA_ID] = CreateDynamicCylinder(PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z] - 1.0, PropertyDoor[property_index][door_index][prop_door_EXT_Z] + 3.0, 1.0, PropertyDoor[property_index][door_index][prop_door_ID_PROPERTY], Interiors[ PropertyDoor[property_index][ PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] ][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID]);
	else PropertyDoor[property_index][door_index][prop_door_EXT_AREA_ID] = CreateDynamicCylinder(PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z] - 1.0, PropertyDoor[property_index][door_index][prop_door_EXT_Z] + 3.0, 1.0, VC_WORLD, 0);
	streamer_info[0] = _:AREA_TYPE_EXT_PROPERTY_DOOR;
	streamer_info[1] = property_index;
	streamer_info[2] = door_index;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, PropertyDoor[property_index][door_index][prop_door_EXT_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);

	//if(door_index == 0)
	//{
	if(PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] != -1) PropertyDoor[property_index][door_index][prop_door_EXT_LABEL_AREA_ID] = CreateDynamicCylinder(PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z] - PLAYER_LABEL_DISTANCE, PropertyDoor[property_index][door_index][prop_door_EXT_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, Entrances[ PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_ID_ENTRANCE], Interiors[Entrances[ PropertyDoor[property_index][door_index][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
	else if(PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] != -1) PropertyDoor[property_index][door_index][prop_door_EXT_LABEL_AREA_ID] = CreateDynamicCylinder(PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z] - PLAYER_LABEL_DISTANCE, PropertyDoor[property_index][door_index][prop_door_EXT_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, PropertyDoor[property_index][door_index][prop_door_ID_PROPERTY], Interiors[ PropertyDoor[property_index][ PropertyDoor[property_index][door_index][prop_door_EXT_SUB_INDEX] ][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID]);
	else PropertyDoor[property_index][door_index][prop_door_EXT_LABEL_AREA_ID] = CreateDynamicCylinder(PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z] - PLAYER_LABEL_DISTANCE, PropertyDoor[property_index][door_index][prop_door_EXT_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, VC_WORLD, 0);
	streamer_info[0] = _:AREA_TYPE_LABEL_EXT_PROP_DOOR;
	streamer_info[1] = property_index;
	streamer_info[2] = door_index;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, PropertyDoor[property_index][door_index][prop_door_EXT_LABEL_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);
	//}

	PropertyDoor[property_index][door_index][prop_door_INT_AREA_ID] = CreateDynamicCylinder(Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_X], Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_Y], Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_Z] - 1.0, Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_Z] + 3.0, 1.0, PropertyDoor[property_index][door_index][prop_door_ID_PROPERTY], Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID]);
	streamer_info[0] = _:AREA_TYPE_INT_PROPERTY_DOOR;
	streamer_info[1] = property_index;
	streamer_info[2] = door_index;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, PropertyDoor[property_index][door_index][prop_door_INT_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);
	PropertyDoor[property_index][door_index][prop_door_INT_LABEL_AREA_ID] = CreateDynamicCylinder(Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_X], Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_Y], Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_Z] - PLAYER_LABEL_DISTANCE, Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, PropertyDoor[property_index][door_index][prop_door_ID_PROPERTY], Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID]);
	streamer_info[0] = _:AREA_TYPE_LABEL_INT_PROP_DOOR;
	streamer_info[1] = property_index;
	streamer_info[2] = door_index;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, PropertyDoor[property_index][door_index][prop_door_INT_LABEL_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);
	return 1;
}

DeletePropertyKeys(id, bool:expired_rent_message = false, pindex = -1)
{
	new params[24];
	format(params, sizeof params, "%d", id);

	//player
	foreach(new i : Player)
	{
		if(pindex != -1)
		{
			if(Iter_Contains(PlayerProperties<i>, pindex))
			Iter_Remove(PlayerProperties<i>, pindex);
		}
		foreach(new x : PINV[i])
		{
			if(PINV[i][x][pinv_ITEM_ID] == _:INV_ITEM_PROPERTY_KEY || PINV[i][x][pinv_ITEM_ID] == _:INV_ITEM_PROPERTY_MASTER_KEY || PINV[i][x][pinv_ITEM_ID] == _:INV_ITEM_PROPERTY_RENT_KEY)
			{
				if(!strcmp(PINV[i][x][pinv_PARAMS], params))
				{
					new tmp_PINV[enum_PINV], prev;
					PINV[i][x] = tmp_PINV;

					Iter_SafeRemove(PINV[i], x, prev); 
					x = prev;

					if(expired_rent_message) SendMessage_PropertyRentExpire(i, id);
				}
			}
		}
	}

	//db
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_inv WHERE (item_id = %d OR item_id = %d OR item_id = %d) AND params = '%e';", _:INV_ITEM_PROPERTY_KEY, _:INV_ITEM_PROPERTY_MASTER_KEY, _:INV_ITEM_PROPERTY_RENT_KEY, params);
	mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	return 1;
}

CountProperties(option = 0)
{
	switch(option)
	{
		case 0: return Iter_Count(PropertyInfo);
		case 1: //libres
		{
			new c;
			foreach(new i : PropertyInfo)
			{
				if(!IsPropertyOccupied(i))
				{
					c ++;
				}
			}
			return c;
		}
		case 2: //venta libres
		{
			new c;
			foreach(new i : PropertyInfo)
			{
				if(!IsPropertyOccupied(i) && !IsPropertyForRent(i))
				{
					c ++;
				}
			}
			return c;
		}
		case 3: //alquiler libres
		{
			new c;
			foreach(new i : PropertyInfo)
			{
				if(!IsPropertyOccupied(i) && IsPropertyForRent(i))
				{
					c ++;
				}
			}
			return c;
		}
		case 4: //ocupadas
		{
			new c;
			foreach(new i : PropertyInfo)
			{
				if(IsPropertyOccupied(i))
				{
					c ++;
				}
			}
			return c;
		}
		case 5: //ocupadas vendidas
		{
			new c;
			foreach(new i : PropertyInfo)
			{
				if(IsPropertyOccupied(i) && !IsPropertyForRent(i))
				{
					c ++;
				}
			}
			return c;
		}
		case 6: //ocupadas alquiladas
		{
			new c;
			foreach(new i : PropertyInfo)
			{
				if(IsPropertyOccupied(i) && IsPropertyForRent(i))
				{
					c ++;
				}
			}
			return c;
		}
		case 7: //sin puerta
		{
			new c;
			foreach(new i : PropertyInfo)
			{
				if(Iter_Count(PropertyDoor[i]) == 0)
				{
					c ++;
				}
			}
			return c;
		}
	}
	return 0;
}

DeletePropertyDoor(property_index, door_index, bool:db = false, bool:iter_remove = true)
{
	if(db)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM properties_doors WHERE id = %d;", PropertyDoor[property_index][door_index][prop_door_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}

	#if CUSTOM_PICKUPS == true
		if(PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicObject(PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID]);
			PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#else
		if(PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicPickup(PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID]);
			PropertyDoor[property_index][door_index][prop_door_EXT_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#endif

	if(PropertyDoor[property_index][door_index][prop_door_EXT_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(PropertyDoor[property_index][door_index][prop_door_EXT_AREA_ID]);
		PropertyDoor[property_index][door_index][prop_door_EXT_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(PropertyDoor[property_index][door_index][prop_door_EXT_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(PropertyDoor[property_index][door_index][prop_door_EXT_LABEL_AREA_ID]);
		PropertyDoor[property_index][door_index][prop_door_EXT_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(PropertyDoor[property_index][door_index][prop_door_INT_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(PropertyDoor[property_index][door_index][prop_door_INT_AREA_ID]);
		PropertyDoor[property_index][door_index][prop_door_INT_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(PropertyDoor[property_index][door_index][prop_door_INT_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(PropertyDoor[property_index][door_index][prop_door_INT_LABEL_AREA_ID]);
		PropertyDoor[property_index][door_index][prop_door_INT_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(PropertyDoor[property_index][door_index][prop_door_EXT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
	{
		DestroyDynamic3DTextLabel(PropertyDoor[property_index][door_index][prop_door_EXT_DEBUG_LABEL]);
		PropertyDoor[property_index][door_index][prop_door_EXT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
	}

	if(PropertyDoor[property_index][door_index][prop_door_INT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
	{
		DestroyDynamic3DTextLabel(PropertyDoor[property_index][door_index][prop_door_INT_DEBUG_LABEL]);
		PropertyDoor[property_index][door_index][prop_door_INT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
	}
	
	new tmp_PropertyDoor[enum_PropertyDoor];
	PropertyDoor[property_index][door_index] = tmp_PropertyDoor;
	if(iter_remove) Iter_Remove(PropertyDoor[property_index], door_index);
	return 1;
}

SendMessage_PropertyRentExpire(playerid, property_id)
{
	Text_Send(playerid, $MESSAGE_INFO_PROPERTY_RENT_EXPIRED, property_id);
	return 1;
}