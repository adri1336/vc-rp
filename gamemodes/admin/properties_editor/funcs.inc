TogglePropertiesInfoLabels(bool:toggle)
{
	propertiesInfoLabels = toggle;
	if(toggle) CreatePropertiesInfoLabels();
	else DestroyPropertiesInfoLabels();
	return 1;
}

CreatePropertiesInfoLabels()
{
	foreach(new i : PropertyInfo)
	{
		foreach(new j : PropertyDoor[i])
		{
			if(PropertyDoor[i][j][prop_door_EXT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
			{
				DestroyDynamic3DTextLabel(PropertyDoor[i][j][prop_door_EXT_DEBUG_LABEL]);
				PropertyDoor[i][j][prop_door_EXT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
			}
			if(PropertyDoor[i][j][prop_door_INT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
			{
				DestroyDynamic3DTextLabel(PropertyDoor[i][j][prop_door_INT_DEBUG_LABEL]);
				PropertyDoor[i][j][prop_door_INT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
			}
			
			new label_str[128];
			format(label_str, sizeof label_str, "Ext\nPropertyID: %d PropertyDoorID: %d", PropertyDoor[i][j][prop_door_ID_PROPERTY], PropertyDoor[i][j][prop_door_ID]);

			if(PropertyDoor[i][j][prop_door_EXT_ENTR_DOOR_INDEX] != -1) PropertyDoor[i][j][prop_door_EXT_DEBUG_LABEL] = CreateDynamic3DTextLabel(label_str, -1, PropertyDoor[i][j][prop_door_EXT_X], PropertyDoor[i][j][prop_door_EXT_Y], PropertyDoor[i][j][prop_door_EXT_Z] + PROPERTY_INFO_LABEL_OFFSETZ, PROPERTY_INFO_LABEL_DISTANCE, .testlos = true, .worldid = Entrances[ PropertyDoor[i][j][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_ID_ENTRANCE], .interiorid = Interiors[Entrances[ PropertyDoor[i][j][prop_door_EXT_ENTR_DOOR_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
			else if(PropertyDoor[i][j][prop_door_EXT_SUB_INDEX] != -1) PropertyDoor[i][j][prop_door_EXT_DEBUG_LABEL] = CreateDynamic3DTextLabel(label_str, -1, PropertyDoor[i][j][prop_door_EXT_X], PropertyDoor[i][j][prop_door_EXT_Y], PropertyDoor[i][j][prop_door_EXT_Z] + PROPERTY_INFO_LABEL_OFFSETZ, PROPERTY_INFO_LABEL_DISTANCE, .testlos = true, .worldid = PropertyDoor[i][j][prop_door_ID_PROPERTY], .interiorid = Interiors[ PropertyDoor[i][ PropertyDoor[i][j][prop_door_EXT_SUB_INDEX] ][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID]);
			else PropertyDoor[i][j][prop_door_EXT_DEBUG_LABEL] = CreateDynamic3DTextLabel(label_str, -1, PropertyDoor[i][j][prop_door_EXT_X], PropertyDoor[i][j][prop_door_EXT_Y], PropertyDoor[i][j][prop_door_EXT_Z] + PROPERTY_INFO_LABEL_OFFSETZ, PROPERTY_INFO_LABEL_DISTANCE, .testlos = true, .worldid = VC_WORLD, .interiorid = 0);
			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, PropertyDoor[i][j][prop_door_EXT_DEBUG_LABEL], E_STREAMER_EXTRA_ID, _:LABEL_TYPE_DEBUG_PROPERTIES);

			format(label_str, sizeof label_str, "Int\nPropertyID: %d PropertyDoorID: %d", PropertyDoor[i][j][prop_door_ID_PROPERTY], PropertyDoor[i][j][prop_door_ID]);
			PropertyDoor[i][j][prop_door_INT_DEBUG_LABEL] = CreateDynamic3DTextLabel(label_str, -1, Interiors[ PropertyDoor[i][j][prop_door_ID_INTERIOR_INDEX] ][interior_X], Interiors[ PropertyDoor[i][j][prop_door_ID_INTERIOR_INDEX] ][interior_Y], Interiors[ PropertyDoor[i][j][prop_door_ID_INTERIOR_INDEX] ][interior_Z] + PROPERTY_INFO_LABEL_OFFSETZ, PROPERTY_INFO_LABEL_DISTANCE, .testlos = true, .worldid = PropertyDoor[i][j][prop_door_ID_PROPERTY], .interiorid = Interiors[ PropertyDoor[i][j][prop_door_ID_INTERIOR_INDEX] ][interior_INTERIORID]);
			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, PropertyDoor[i][j][prop_door_INT_DEBUG_LABEL], E_STREAMER_EXTRA_ID, _:LABEL_TYPE_DEBUG_PROPERTIES);
		}
	}
	return 1;
}

DestroyPropertiesInfoLabels()
{
	foreach(new i : PropertyInfo)
	{
		foreach(new j : PropertyDoor[i])
		{
			if(PropertyDoor[i][j][prop_door_EXT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
			{
				DestroyDynamic3DTextLabel(PropertyDoor[i][j][prop_door_EXT_DEBUG_LABEL]);
				PropertyDoor[i][j][prop_door_EXT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
			}
			if(PropertyDoor[i][j][prop_door_INT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
			{
				DestroyDynamic3DTextLabel(PropertyDoor[i][j][prop_door_INT_DEBUG_LABEL]);
				PropertyDoor[i][j][prop_door_INT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
			}
		}
	}
	return 1;
}