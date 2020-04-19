ToggleInteriorsInfoLabels(bool:toggle)
{
	interiorsInfoLabels = toggle;
	if(toggle) CreateInteriorsInfoLabels();
	else DestroyInteriorsInfoLabels();
	return 1;
}

CreateInteriorsInfoLabels()
{
	foreach(new i : Interiors)
	{
		if(Interiors[i][interior_INFO_LABEL] != Text3D:INVALID_STREAMER_ID)
		{
			DestroyDynamic3DTextLabel(Interiors[i][interior_INFO_LABEL]);
			Interiors[i][interior_INFO_LABEL] = Text3D:INVALID_STREAMER_ID;
		}
		
		new label_str[128];
		format(label_str, sizeof label_str, "ID Interior: %d Name: %s InteriorID: %d", Interiors[i][interior_ID], Interiors[i][interior_NAME], Interiors[i][interior_INTERIORID]);
		Interiors[i][interior_INFO_LABEL] = CreateDynamic3DTextLabel(label_str, -1, Interiors[i][interior_X], Interiors[i][interior_Y], Interiors[i][interior_Z] + INTERIOR_INFO_LABEL_OFFSETZ, INTERIOR_INFO_LABEL_DISTANCE, .testlos = true, .worldid = -1, .interiorid = Interiors[i][interior_INTERIORID]);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, Interiors[i][interior_INFO_LABEL], E_STREAMER_EXTRA_ID, _:LABEL_TYPE_DEBUG_INTERIORS);
	}
	return 1;
}

DestroyInteriorsInfoLabels()
{
	foreach(new i : Interiors)
	{
		if(Interiors[i][interior_INFO_LABEL] != Text3D:INVALID_STREAMER_ID)
		{
			DestroyDynamic3DTextLabel(Interiors[i][interior_INFO_LABEL]);
			Interiors[i][interior_INFO_LABEL] = Text3D:INVALID_STREAMER_ID;
		}
	}
	return 1;
}