ToggleEntrancesInfoLabels(bool:toggle)
{
	entrancesInfoLabels = toggle;
	if(toggle) CreateEntrancesInfoLabels();
	else DestroyEntrancesInfoLabels();
	return 1;
}

CreateEntrancesInfoLabels()
{
	foreach(new i : Entrances)
	{
		if(Entrances[i][entrance_EXT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
		{
			DestroyDynamic3DTextLabel(Entrances[i][entrance_EXT_DEBUG_LABEL]);
			Entrances[i][entrance_EXT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
		}
		if(Entrances[i][entrance_INT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
		{
			DestroyDynamic3DTextLabel(Entrances[i][entrance_INT_DEBUG_LABEL]);
			Entrances[i][entrance_INT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
		}
		
		new label_str[128];
		format(label_str, sizeof label_str, "Ext\nID Entrance: %d ID Door: %d", Entrances[i][entrance_ID_ENTRANCE], Entrances[i][entrance_ID]);

		if(Entrances[i][entrance_SUB_ID_INDEX] != -1) Entrances[i][entrance_EXT_DEBUG_LABEL] = CreateDynamic3DTextLabel(label_str, -1, Entrances[i][entrance_X], Entrances[i][entrance_Y], Entrances[i][entrance_Z] + ENTRANCE_INFO_LABEL_OFFSETZ, ENTRANCE_INFO_LABEL_DISTANCE, .testlos = true, .worldid = Entrances[ Entrances[i][entrance_SUB_ID_INDEX] ][entrance_ID_ENTRANCE], .interiorid = Interiors[Entrances[ Entrances[i][entrance_SUB_ID_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
		else Entrances[i][entrance_EXT_DEBUG_LABEL] = CreateDynamic3DTextLabel(label_str, -1, Entrances[i][entrance_X], Entrances[i][entrance_Y], Entrances[i][entrance_Z] + ENTRANCE_INFO_LABEL_OFFSETZ, ENTRANCE_INFO_LABEL_DISTANCE, .testlos = true, .worldid = VC_WORLD, .interiorid = 0);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, Entrances[i][entrance_EXT_DEBUG_LABEL], E_STREAMER_EXTRA_ID, _:LABEL_TYPE_DEBUG_ENTRANCES);

		format(label_str, sizeof label_str, "Int\nID Entrance: %d ID Door: %d", Entrances[i][entrance_ID_ENTRANCE], Entrances[i][entrance_ID]);
		Entrances[i][entrance_INT_DEBUG_LABEL] = CreateDynamic3DTextLabel(label_str, -1, Interiors[ Entrances[i][entrance_INTERIOR_INDEX] ][interior_X], Interiors[ Entrances[i][entrance_INTERIOR_INDEX] ][interior_Y], Interiors[ Entrances[i][entrance_INTERIOR_INDEX] ][interior_Z] + ENTRANCE_INFO_LABEL_OFFSETZ, ENTRANCE_INFO_LABEL_DISTANCE, .testlos = true, .worldid = Entrances[i][entrance_ID_ENTRANCE], .interiorid = Interiors[ Entrances[i][entrance_INTERIOR_INDEX] ][interior_INTERIORID]);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, Entrances[i][entrance_INT_DEBUG_LABEL], E_STREAMER_EXTRA_ID, _:LABEL_TYPE_DEBUG_ENTRANCES);
	}
	return 1;
}

DestroyEntrancesInfoLabels()
{
	foreach(new i : Entrances)
	{
		if(Entrances[i][entrance_EXT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
		{
			DestroyDynamic3DTextLabel(Entrances[i][entrance_EXT_DEBUG_LABEL]);
			Entrances[i][entrance_EXT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
		}
		if(Entrances[i][entrance_INT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
		{
			DestroyDynamic3DTextLabel(Entrances[i][entrance_INT_DEBUG_LABEL]);
			Entrances[i][entrance_INT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
		}
	}
	return 1;
}