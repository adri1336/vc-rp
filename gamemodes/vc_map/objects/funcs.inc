CreateVCObject(id, modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, world = -1, interior = -1, type_id = 0, index = -1)
{
	if(!id) return 0;

	//world = VC_WORLD;
	new streamer_objectid, model_type_index = GetVCModelTypeIndexById(type_id);

	if(model_type_index == -1) streamer_objectid = CreateDynamicObject(modelid, x, y, z, rx, ry, rz, world, interior, .streamdistance = DEFAULT_VC_STREAM_DISTANCE + 50.0, .drawdistance = DEFAULT_VC_STREAM_DISTANCE);
	else streamer_objectid = CreateDynamicObject(modelid, x, y, z, rx, ry, rz, world, interior, .streamdistance = Vc_Models_Types[model_type_index][vc_model_type_STREAM_DISTANCE] + 50.0, .drawdistance = Vc_Models_Types[model_type_index][vc_model_type_STREAM_DISTANCE], .priority = Vc_Models_Types[model_type_index][vc_model_type_PRIORITY]);

	if(type_id == 1) Streamer_ToggleItemStatic(STREAMER_TYPE_OBJECT, streamer_objectid, true); //landmasses

	if(vcObjects_Debug)
	{
		new Text3D:streamer_labelid, label_str[128], type_str[32];

		if(model_type_index == -1) format(type_str, sizeof type_str, "null");
		else format(type_str, sizeof type_str, "%s", Vc_Models_Types[model_type_index][vc_model_type_NAME]);
		format(label_str, sizeof label_str, "ID: %d\nObjectID: %d | Modelid: %d | Type: %s", id, streamer_objectid, modelid, type_str);
		streamer_labelid = CreateDynamic3DTextLabel(label_str, -1, x, y, z, DEBUG_LABEL_STREAM_DISTANCE, .worldid = world, .interiorid = interior);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, streamer_labelid, E_STREAMER_EXTRA_ID, _:LABEL_TYPE_VCO_DEBUG); 
		if(index > -1)
		{
			Vc_Objects[index][vc_OBJECT_LABEL] = streamer_labelid;
		}
	}

	Streamer_SetIntData(STREAMER_TYPE_OBJECT, streamer_objectid, E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_VCO); 

	// Iterator
	if(index > -1)
	{
		Vc_Objects[index][vc_ID] = id;
		Vc_Objects[index][vc_OBJECTID] = streamer_objectid;
		Vc_Objects[index][vc_MODELID] = modelid;
		Vc_Objects[index][vc_X] = x;
		Vc_Objects[index][vc_Y] = y;
		Vc_Objects[index][vc_Z] = z;
		Vc_Objects[index][vc_RX] = rx;
		Vc_Objects[index][vc_RY] = ry;
		Vc_Objects[index][vc_RZ] = rz;
		Vc_Objects[index][vc_INTERIORID] = interior;
		Vc_Objects[index][vc_WORLDID] = world;
		Vc_Objects[index][vc_OBJECT_TYPE] = type_id;
		Vc_Objects[index][vc_OBJECT_TYPE_INDEX] = model_type_index;
		Iter_Add(Vc_Objects, index);
	}
	//
	return streamer_objectid;
}

GetVcObjectIndexById(id)
{
	foreach(new i : Vc_Objects)
	{
		if(Vc_Objects[i][vc_ID] == id)
		{
			return i;
		}
	}
	return -1;
}

UpdateVcObject(index, bool:update = false)
{
	if(!Iter_Contains(Vc_Objects, index)) return 0;
	if(!IsValidDynamicObject(Vc_Objects[index][vc_OBJECTID])) return 0;

	SetDynamicObjectPos(Vc_Objects[index][vc_OBJECTID], Vc_Objects[index][vc_X], Vc_Objects[index][vc_Y], Vc_Objects[index][vc_Z]);
	SetDynamicObjectRot(Vc_Objects[index][vc_OBJECTID], Vc_Objects[index][vc_RX], Vc_Objects[index][vc_RY], Vc_Objects[index][vc_RZ]);

	if(vcObjects_Debug)
	{
		if(IsValidDynamic3DTextLabel(Vc_Objects[index][vc_OBJECT_LABEL]))
		{
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, Vc_Objects[index][vc_OBJECT_LABEL], E_STREAMER_X, Vc_Objects[index][vc_X]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, Vc_Objects[index][vc_OBJECT_LABEL], E_STREAMER_Y, Vc_Objects[index][vc_Y]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, Vc_Objects[index][vc_OBJECT_LABEL], E_STREAMER_Z, Vc_Objects[index][vc_Z]);
		}
	}

	if(update)
	{
		mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE objects SET x = '%f', y = '%f', z = '%f', rx = '%f', ry = '%f', rz = '%f' WHERE id = '%d';", Vc_Objects[index][vc_X], Vc_Objects[index][vc_Y], Vc_Objects[index][vc_Z], Vc_Objects[index][vc_RX], Vc_Objects[index][vc_RY], Vc_Objects[index][vc_RZ], Vc_Objects[index][vc_ID]);
		mysql_tquery(vc_map_db, QUERY_BUFFER, "", "");
	}
	return 1;
}

DeleteVcObject(index, bool:update = false)
{
	if(!Iter_Contains(Vc_Objects, index)) return 0;
	if(!IsValidDynamicObject(Vc_Objects[index][vc_OBJECTID])) return 0;

	if(vcObjects_Debug)
	{
		if(IsValidDynamic3DTextLabel(Vc_Objects[index][vc_OBJECT_LABEL]))
		{
			DestroyDynamic3DTextLabel(Vc_Objects[index][vc_OBJECT_LABEL]);
			Vc_Objects[index][vc_OBJECT_LABEL] = Text3D:INVALID_STREAMER_ID;
		}
	}

	if(update)
	{
		mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM objects WHERE id = '%d';", Vc_Objects[index][vc_ID]);
		mysql_tquery(vc_map_db, QUERY_BUFFER, "", "");
	}

	DestroyDynamicObject(Vc_Objects[index][vc_OBJECTID]);
	Vc_Objects[index][vc_ID] = 0;
	Vc_Objects[index][vc_OBJECTID] = INVALID_STREAMER_ID;
	Vc_Objects[index][vc_MODELID] = 0;
	Vc_Objects[index][vc_X] = 0.0;
	Vc_Objects[index][vc_Y] = 0.0;
	Vc_Objects[index][vc_Z] = 0.0;
	Vc_Objects[index][vc_RX] = 0.0;
	Vc_Objects[index][vc_RY] = 0.0;
	Vc_Objects[index][vc_RZ] = 0.0;
	Vc_Objects[index][vc_INTERIORID] = 0;
	Vc_Objects[index][vc_WORLDID] = 0;
	Vc_Objects[index][vc_OBJECT_TYPE] = 0;
	Vc_Objects[index][vc_OBJECT_TYPE_INDEX] = 0;
	Iter_Remove(Vc_Objects, index);
	return 1;
}

DisableVcObject(index, bool:update = false)
{
	if(!Iter_Contains(Vc_Objects, index)) return 0;
	if(!IsValidDynamicObject(Vc_Objects[index][vc_OBJECTID])) return 0;

	if(vcObjects_Debug)
	{
		if(IsValidDynamic3DTextLabel(Vc_Objects[index][vc_OBJECT_LABEL]))
		{
			DestroyDynamic3DTextLabel(Vc_Objects[index][vc_OBJECT_LABEL]);
			Vc_Objects[index][vc_OBJECT_LABEL] = Text3D:INVALID_STREAMER_ID;
		}
	}

	if(update)
	{
		mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE objects SET enabled = '0' WHERE id = '%d';", Vc_Objects[index][vc_ID]);
		mysql_tquery(vc_map_db, QUERY_BUFFER, "", "");
	}

	DestroyDynamicObject(Vc_Objects[index][vc_OBJECTID]);
	Vc_Objects[index][vc_ID] = 0;
	Vc_Objects[index][vc_OBJECTID] = INVALID_STREAMER_ID;
	Vc_Objects[index][vc_MODELID] = 0;
	Vc_Objects[index][vc_X] = 0.0;
	Vc_Objects[index][vc_Y] = 0.0;
	Vc_Objects[index][vc_Z] = 0.0;
	Vc_Objects[index][vc_RX] = 0.0;
	Vc_Objects[index][vc_RY] = 0.0;
	Vc_Objects[index][vc_RZ] = 0.0;
	Vc_Objects[index][vc_INTERIORID] = 0;
	Vc_Objects[index][vc_WORLDID] = 0;
	Vc_Objects[index][vc_OBJECT_TYPE] = 0;
	Vc_Objects[index][vc_OBJECT_TYPE_INDEX] = 0;
	Iter_Remove(Vc_Objects, index);
	return 1;
}

UpdateVcObjectsSs()
{
	foreach(new i : Vc_Objects)
	{
		if(Vc_Objects[i][vc_OBJECT_TYPE_INDEX] != -1)
		{
			if(Vc_Objects[i][vc_OBJECT_TYPE_INDEX] == -1)
			{
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_STREAM_DISTANCE, DEFAULT_VC_STREAM_DISTANCE + 50.0);
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_DRAW_DISTANCE, DEFAULT_VC_STREAM_DISTANCE);
				Streamer_SetIntData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_PRIORITY, 0);
			}
			else
			{
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_STREAM_DISTANCE, Vc_Models_Types[ Vc_Objects[i][vc_OBJECT_TYPE_INDEX] ][vc_model_type_STREAM_DISTANCE] + 50.0);
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_DRAW_DISTANCE, Vc_Models_Types[ Vc_Objects[i][vc_OBJECT_TYPE_INDEX] ][vc_model_type_STREAM_DISTANCE]);
				Streamer_SetIntData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_PRIORITY, Vc_Models_Types[ Vc_Objects[i][vc_OBJECT_TYPE_INDEX] ][vc_model_type_PRIORITY]);
			}
		}
	}
	return 1;
}

stock SetVcModelidObjectType(modelid, type_index)
{
	foreach(new i : Vc_Objects)
	{
		if(Vc_Objects[i][vc_MODELID] == modelid)
		{
			if(type_index == -1)
			{
				Vc_Objects[i][vc_OBJECT_TYPE] = 0;
				Vc_Objects[i][vc_OBJECT_TYPE_INDEX] = type_index;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_STREAM_DISTANCE, DEFAULT_VC_STREAM_DISTANCE + 50.0);
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_DRAW_DISTANCE, DEFAULT_VC_STREAM_DISTANCE);
				Streamer_SetIntData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_PRIORITY, 0);
				if(vcObjects_Debug)  UpdateVcObjectLabelText(i);
			}
			else
			{
				Vc_Objects[i][vc_OBJECT_TYPE] = Vc_Models_Types[type_index][vc_model_type_ID];
				Vc_Objects[i][vc_OBJECT_TYPE_INDEX] = type_index;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_STREAM_DISTANCE, Vc_Models_Types[ Vc_Objects[i][vc_OBJECT_TYPE_INDEX] ][vc_model_type_STREAM_DISTANCE] + 50.0);
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_DRAW_DISTANCE, Vc_Models_Types[ Vc_Objects[i][vc_OBJECT_TYPE_INDEX] ][vc_model_type_STREAM_DISTANCE]);
				Streamer_SetIntData(STREAMER_TYPE_OBJECT, Vc_Objects[i][vc_OBJECTID], E_STREAMER_PRIORITY, Vc_Models_Types[ Vc_Objects[i][vc_OBJECT_TYPE_INDEX] ][vc_model_type_PRIORITY]);
				if(vcObjects_Debug) UpdateVcObjectLabelText(i);
			}
		}
	}
	return 1;
}

AddVcObject(playerid, modelid, duplicate = -1)
{
	new index = Iter_Free(Vc_Objects);
	if(index == cellmin) return 0;

	new Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, world = -1 /*GetPlayerVirtualWorld(playerid)*/, interior = -1 /*GetPlayerInterior(playerid)*/;
	if(modelid == -1 && duplicate != -1)
	{
		modelid = Vc_Objects[duplicate][vc_MODELID];
		x = Vc_Objects[duplicate][vc_X];
		y = Vc_Objects[duplicate][vc_Y];
		z = Vc_Objects[duplicate][vc_Z];
		rx = Vc_Objects[duplicate][vc_RX];
		ry = Vc_Objects[duplicate][vc_RY];
		rz = Vc_Objects[duplicate][vc_RZ];
	}
	else GetPlayerPos(playerid, x, y, z);

	mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO objects (modelid, x, y, z, rx, ry, rz, world, interior) VALUES ('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d');", modelid, x, y, z, rx, ry, rz, world, interior);
	mysql_tquery(vc_map_db, QUERY_BUFFER, "OnPlayerViceCityObjectAdding", "idffffffdd", playerid, modelid, x, y, z, rx, ry, rz, world, interior);
	return 1;
}

SetVcObjectModelType(index, type_index)
{
	if(type_index == -1)
	{
		Vc_Objects[index][vc_OBJECT_TYPE] = 0;
		Vc_Objects[index][vc_OBJECT_TYPE_INDEX] = type_index;

		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[index][vc_OBJECTID], E_STREAMER_STREAM_DISTANCE, DEFAULT_VC_STREAM_DISTANCE + 50.0);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[index][vc_OBJECTID], E_STREAMER_DRAW_DISTANCE, DEFAULT_VC_STREAM_DISTANCE);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, Vc_Objects[index][vc_OBJECTID], E_STREAMER_PRIORITY, 0);
	}
	else
	{
		Vc_Objects[index][vc_OBJECT_TYPE] = Vc_Models_Types[type_index][vc_model_type_ID];
		Vc_Objects[index][vc_OBJECT_TYPE_INDEX] = type_index;

		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[index][vc_OBJECTID], E_STREAMER_STREAM_DISTANCE, Vc_Models_Types[ Vc_Objects[index][vc_OBJECT_TYPE_INDEX] ][vc_model_type_STREAM_DISTANCE] + 50.0);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, Vc_Objects[index][vc_OBJECTID], E_STREAMER_DRAW_DISTANCE, Vc_Models_Types[ Vc_Objects[index][vc_OBJECT_TYPE_INDEX] ][vc_model_type_STREAM_DISTANCE]);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, Vc_Objects[index][vc_OBJECTID], E_STREAMER_PRIORITY, Vc_Models_Types[ Vc_Objects[index][vc_OBJECT_TYPE_INDEX] ][vc_model_type_PRIORITY]);
	}
	if(vcObjects_Debug) UpdateVcObjectLabelText(index);
	return 1;
}

UpdateVcObjectLabelText(index)
{
	if(!IsValidDynamic3DTextLabel(Vc_Objects[index][vc_OBJECT_LABEL])) return 0;

	new label_str[128], type_str[32];

	if(Vc_Objects[index][vc_OBJECT_TYPE_INDEX] == -1) format(type_str, sizeof type_str, "null");
	else format(type_str, sizeof type_str, "%s", Vc_Models_Types[ Vc_Objects[index][vc_OBJECT_TYPE_INDEX] ][vc_model_type_NAME]);
	format(label_str, sizeof label_str, "ID: %d\nObjectID: %d | Modelid: %d | Type: %s", Vc_Objects[index][vc_ID], Vc_Objects[index][vc_OBJECTID], Vc_Objects[index][vc_MODELID], type_str);

	UpdateDynamic3DTextLabelText(Vc_Objects[index][vc_OBJECT_LABEL], -1, label_str);
	return 1;
}

ToggleVcObjectsDebug(bool:toggle)
{
	if(toggle)
	{
		foreach(new i : Vc_Objects)
		{
			if(IsValidDynamic3DTextLabel(Vc_Objects[i][vc_OBJECT_LABEL]))
			{
				DestroyDynamic3DTextLabel(Vc_Objects[i][vc_OBJECT_LABEL]);
				Vc_Objects[i][vc_OBJECT_LABEL] = Text3D:INVALID_STREAMER_ID;
			}

			Vc_Objects[i][vc_OBJECT_LABEL] = CreateDynamic3DTextLabel("label_str", -1, Vc_Objects[i][vc_X], Vc_Objects[i][vc_Y], Vc_Objects[i][vc_Z], DEBUG_LABEL_STREAM_DISTANCE, .worldid = Vc_Objects[i][vc_WORLDID], .interiorid = Vc_Objects[i][vc_INTERIORID]);
			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, Vc_Objects[i][vc_OBJECT_LABEL], E_STREAMER_EXTRA_ID, _:LABEL_TYPE_VCO_DEBUG); 
			UpdateVcObjectLabelText(i);
		}
	}
	else
	{
		foreach(new i : Vc_Objects)
		{
			if(IsValidDynamic3DTextLabel(Vc_Objects[i][vc_OBJECT_LABEL]))
			{
				DestroyDynamic3DTextLabel(Vc_Objects[i][vc_OBJECT_LABEL]);
				Vc_Objects[i][vc_OBJECT_LABEL] = Text3D:INVALID_STREAMER_ID;
			}
		}
	}

	vcObjects_Debug = toggle;
	return 1;
}

CountVcObjectsWithNoType()
{
	new c;
	foreach(new i : Vc_Objects)
	{
		if(Vc_Objects[i][vc_OBJECT_TYPE] == 0)
		{
			c ++;
		}
	}
	return c;
}