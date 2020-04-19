ToggleBusinessInfoLabels(bool:toggle)
{
	businessInfoLabels = toggle;
	if(toggle) CreateBusinessInfoLabels();
	else DestroyBusinessInfoLabels();
	return 1;
}

CreateBusinessInfoLabels()
{
	foreach(new i : BusinessData)
	{
		foreach(new j : BusinessDoors[i])
		{
			if(BusinessDoors[i][j][bdoor_EXT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
			{
				DestroyDynamic3DTextLabel(BusinessDoors[i][j][bdoor_EXT_DEBUG_LABEL]);
				BusinessDoors[i][j][bdoor_EXT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
			}
			if(BusinessDoors[i][j][bdoor_INT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
			{
				DestroyDynamic3DTextLabel(BusinessDoors[i][j][bdoor_INT_DEBUG_LABEL]);
				BusinessDoors[i][j][bdoor_INT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
			}
			
			new label_str[128];
			format(label_str, sizeof label_str, "Ext\nBusinessID: %d BusinessDoorsID: %d", BusinessDoors[i][j][bdoor_ID_BUSINESS], BusinessDoors[i][j][bdoor_ID]);

			if(BusinessDoors[i][j][bdoor_EXT_ENTRANCE_DOOR_INDEX] != -1) BusinessDoors[i][j][bdoor_EXT_DEBUG_LABEL] = CreateDynamic3DTextLabel(label_str, -1, BusinessDoors[i][j][bdoor_EXT_X], BusinessDoors[i][j][bdoor_EXT_Y], BusinessDoors[i][j][bdoor_EXT_Z] + BUSINESS_INFO_LABEL_OFFSETZ, BUSINESS_INFO_LABEL_DISTANCE, .testlos = true, .worldid = Entrances[ BusinessDoors[i][j][bdoor_EXT_ENTRANCE_DOOR_INDEX] ][entrance_ID_ENTRANCE], .interiorid = Interiors[Entrances[ BusinessDoors[i][j][bdoor_EXT_ENTRANCE_DOOR_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
			else if(BusinessDoors[i][j][bdoor_EXT_SUB_INDEX] != -1) BusinessDoors[i][j][bdoor_EXT_DEBUG_LABEL] = CreateDynamic3DTextLabel(label_str, -1, BusinessDoors[i][j][bdoor_EXT_X], BusinessDoors[i][j][bdoor_EXT_Y], BusinessDoors[i][j][bdoor_EXT_Z] + BUSINESS_INFO_LABEL_OFFSETZ, BUSINESS_INFO_LABEL_DISTANCE, .testlos = true, .worldid = BusinessDoors[i][j][bdoor_ID_BUSINESS], .interiorid = Interiors[ BusinessDoors[i][ BusinessDoors[i][j][bdoor_EXT_SUB_INDEX] ][bdoor_INDEX_INTERIOR] ][interior_INTERIORID]);
			else BusinessDoors[i][j][bdoor_EXT_DEBUG_LABEL] = CreateDynamic3DTextLabel(label_str, -1, BusinessDoors[i][j][bdoor_EXT_X], BusinessDoors[i][j][bdoor_EXT_Y], BusinessDoors[i][j][bdoor_EXT_Z] + BUSINESS_INFO_LABEL_OFFSETZ, BUSINESS_INFO_LABEL_DISTANCE, .testlos = true, .worldid = VC_WORLD, .interiorid = 0);
			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, BusinessDoors[i][j][bdoor_EXT_DEBUG_LABEL], E_STREAMER_EXTRA_ID, _:LABEL_TYPE_DEBUG_PROPERTIES);

			format(label_str, sizeof label_str, "Int\nBusinessID: %d BusinessDoorsID: %d", BusinessDoors[i][j][bdoor_ID_BUSINESS], BusinessDoors[i][j][bdoor_ID]);
			BusinessDoors[i][j][bdoor_INT_DEBUG_LABEL] = CreateDynamic3DTextLabel(label_str, -1, Interiors[ BusinessDoors[i][j][bdoor_INDEX_INTERIOR] ][interior_X], Interiors[ BusinessDoors[i][j][bdoor_INDEX_INTERIOR] ][interior_Y], Interiors[ BusinessDoors[i][j][bdoor_INDEX_INTERIOR] ][interior_Z] + BUSINESS_INFO_LABEL_OFFSETZ, BUSINESS_INFO_LABEL_DISTANCE, .testlos = true, .worldid = BusinessDoors[i][j][bdoor_ID_BUSINESS], .interiorid = Interiors[ BusinessDoors[i][j][bdoor_INDEX_INTERIOR] ][interior_INTERIORID]);
			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, BusinessDoors[i][j][bdoor_INT_DEBUG_LABEL], E_STREAMER_EXTRA_ID, _:LABEL_TYPE_DEBUG_PROPERTIES);
		}
	}
	return 1;
}

DestroyBusinessInfoLabels()
{
	foreach(new i : BusinessData)
	{
		foreach(new j : BusinessDoors[i])
		{
			if(BusinessDoors[i][j][bdoor_EXT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
			{
				DestroyDynamic3DTextLabel(BusinessDoors[i][j][bdoor_EXT_DEBUG_LABEL]);
				BusinessDoors[i][j][bdoor_EXT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
			}
			if(BusinessDoors[i][j][bdoor_INT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
			{
				DestroyDynamic3DTextLabel(BusinessDoors[i][j][bdoor_INT_DEBUG_LABEL]);
				BusinessDoors[i][j][bdoor_INT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
			}
		}
	}
	return 1;
}