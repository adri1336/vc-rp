CreateEntranceInfo(index, sub_index)
{
	DestroyDoorEntranceObjects(index);
	if(Entrances[index][entrance_MAPICON_MODEL] != -1) Entrances[index][entrance_MAPICON_ID] = CreateDynamicMapIcon(Entrances[index][entrance_X], Entrances[index][entrance_Y], Entrances[index][entrance_Z], Entrances[index][entrance_MAPICON_MODEL], -1, VC_WORLD, 0, .streamdistance = PICKUP_DISTANCE);
	
	#if CUSTOM_PICKUPS == true
		if(sub_index == -1) Entrances[index][entrance_PICKUP_ID] = CreateDynamicObject(CUSTOM_PICKUP_MODELID, Entrances[index][entrance_X], Entrances[index][entrance_Y], Entrances[index][entrance_Z], 0.0, 0.0, 0.0, VC_WORLD, 0, .streamdistance = PICKUP_DISTANCE, .drawdistance = PICKUP_DISTANCE, .priority = 10);
		else Entrances[index][entrance_PICKUP_ID] = CreateDynamicObject(CUSTOM_PICKUP_MODELID, Entrances[index][entrance_X], Entrances[index][entrance_Y], Entrances[index][entrance_Z], 0.0, 0.0, 0.0, Entrances[index][entrance_ID_ENTRANCE], Interiors[Entrances[sub_index][entrance_INTERIOR_INDEX]][interior_INTERIORID], .streamdistance = PICKUP_DISTANCE, .drawdistance = PICKUP_DISTANCE, .priority = 10);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, Entrances[index][entrance_PICKUP_ID], E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_PICKUP_ENTRANCE);
	#else
		if(sub_index == -1) Entrances[index][entrance_PICKUP_ID] = CreateDynamicPickup(Entrances[index][entrance_PICKUP_MODEL], 1, Entrances[index][entrance_X], Entrances[index][entrance_Y], Entrances[index][entrance_Z], VC_WORLD, 0, .streamdistance = PICKUP_DISTANCE, .priority = 10);
		else Entrances[index][entrance_PICKUP_ID] = CreateDynamicPickup(Entrances[index][entrance_PICKUP_MODEL], 1, Entrances[index][entrance_X], Entrances[index][entrance_Y], Entrances[index][entrance_Z], Entrances[index][entrance_ID_ENTRANCE], Interiors[Entrances[sub_index][entrance_INTERIOR_INDEX]][interior_INTERIORID], .streamdistance = PICKUP_DISTANCE, .priority = 10);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, Entrances[index][entrance_PICKUP_ID], E_STREAMER_EXTRA_ID, _:PICKUP_TYPE_ENTRANCE);
	#endif

	new streamer_info[2];
	if(sub_index == -1) Entrances[index][entrance_AREA_ID] = CreateDynamicCylinder(Entrances[index][entrance_X], Entrances[index][entrance_Y], Entrances[index][entrance_Z] - 1.0, Entrances[index][entrance_Z] + 3.0, 1.0, VC_WORLD, 0);
	else Entrances[index][entrance_AREA_ID] = CreateDynamicCylinder(Entrances[index][entrance_X], Entrances[index][entrance_Y], Entrances[index][entrance_Z] - 1.0, Entrances[index][entrance_Z] + 3.0, 1.0, Entrances[index][entrance_ID_ENTRANCE], Interiors[Entrances[sub_index][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
	streamer_info[0] = _:AREA_TYPE_ENTRANCE;
	streamer_info[1] = index;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, Entrances[index][entrance_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);
	if(sub_index == -1) Entrances[index][entrance_LABEL_AREA_ID] = CreateDynamicCylinder(Entrances[index][entrance_X], Entrances[index][entrance_Y], Entrances[index][entrance_Z] - PLAYER_LABEL_DISTANCE, Entrances[index][entrance_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, VC_WORLD, 0);
	else Entrances[index][entrance_LABEL_AREA_ID] = CreateDynamicCylinder(Entrances[index][entrance_X], Entrances[index][entrance_Y], Entrances[index][entrance_Z] - PLAYER_LABEL_DISTANCE, Entrances[index][entrance_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, Entrances[index][entrance_ID_ENTRANCE], Interiors[Entrances[sub_index][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
	streamer_info[0] = _:AREA_TYPE_LABEL_ENTRANCE;
	streamer_info[1] = index;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, Entrances[index][entrance_LABEL_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);

	Entrances[index][entrance_INT_AREA_ID] = CreateDynamicCylinder(Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_X], Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_Y], Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_Z] - 1.0, Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_Z] + 3.0, 1.0, Entrances[index][entrance_ID_ENTRANCE], Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
	streamer_info[0] = _:AREA_TYPE_INT_ENTRANCE;
	streamer_info[1] = index;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, Entrances[index][entrance_INT_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);
	Entrances[index][entrance_INT_LABEL_AREA_ID] = CreateDynamicCylinder(Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_X], Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_Y], Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_Z] - PLAYER_LABEL_DISTANCE, Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, Entrances[index][entrance_ID_ENTRANCE], Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
	streamer_info[0] = _:AREA_TYPE_LABEL_INT_ENTRANCE;
	streamer_info[1] = index;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, Entrances[index][entrance_INT_LABEL_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);
	return 1;
}

GetEntranceIndexByEntranceId(entranceid)
{
	foreach(new i : Entrances)
	{
		if(Entrances[i][entrance_ID_ENTRANCE] == entranceid)
		{
			return i;
		}
	}
	return -1;
}

GetEntranceIndexByEntranceDId(doorid)
{
	foreach(new i : Entrances)
	{
		if(Entrances[i][entrance_ID] == doorid)
		{
			return i;
		}
	}
	return -1;
}

DeleteDoorEntrance(index, bool:db = false)
{
	if(db)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM entrances_doors WHERE id = %d;", Entrances[index][entrance_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}
	DestroyDoorEntranceObjects(index);
	new tmp_Entrances[enum_Entrances];
	Entrances[index] = tmp_Entrances;
	Iter_Remove(Entrances, index);
	return 1;
}

DeleteEntrance(id_entrance, bool:db)
{
	if(db)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM entrances WHERE id = %d;", id_entrance);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}
	foreach(new i : Entrances)
	{
		DestroyDoorEntranceObjects(i);
		new tmp_Entrances[enum_Entrances];
		Entrances[i] = tmp_Entrances;

		new prev;
		Iter_SafeRemove(Entrances, i, prev); 
		i = prev;
	}
	return 1;
}

DestroyDoorEntranceObjects(index)
{
	if(Entrances[index][entrance_MAPICON_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicMapIcon(Entrances[index][entrance_MAPICON_ID]);
		Entrances[index][entrance_MAPICON_ID] = INVALID_STREAMER_ID;
	}

	#if CUSTOM_PICKUPS == true
		if(Entrances[index][entrance_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicObject(Entrances[index][entrance_PICKUP_ID]);
			Entrances[index][entrance_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#else
		if(Entrances[index][entrance_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicPickup(Entrances[index][entrance_PICKUP_ID]);
			Entrances[index][entrance_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#endif

	if(Entrances[index][entrance_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(Entrances[index][entrance_AREA_ID]);
		Entrances[index][entrance_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(Entrances[index][entrance_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(Entrances[index][entrance_LABEL_AREA_ID]);
		Entrances[index][entrance_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(Entrances[index][entrance_INT_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(Entrances[index][entrance_INT_AREA_ID]);
		Entrances[index][entrance_INT_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(Entrances[index][entrance_INT_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(Entrances[index][entrance_INT_LABEL_AREA_ID]);
		Entrances[index][entrance_INT_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}
	if(Entrances[index][entrance_EXT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
	{
		DestroyDynamic3DTextLabel(Entrances[index][entrance_EXT_DEBUG_LABEL]);
		Entrances[index][entrance_EXT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
	}
	if(Entrances[index][entrance_INT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
	{
		DestroyDynamic3DTextLabel(Entrances[index][entrance_INT_DEBUG_LABEL]);
		Entrances[index][entrance_INT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
	}
	return 1;
}