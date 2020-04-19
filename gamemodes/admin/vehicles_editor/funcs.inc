ToggleVehiclesInfoLabels(bool:toggle)
{
	vehiclesInfoLabels = toggle;
	if(toggle) CreateVehiclesInfoLabels();
	else DestroyVehiclesInfoLabels();
	return 1;
}

CreateVehiclesInfoLabels()
{
	foreach(new i : VehicleInfo)
	{
		if(VehicleInfo[i][vinfo_VEHICLE_ID] != INVALID_VEHICLE_ID)
		{
			if(VehicleInfo[i][vinfo_INFO_LABEL] != Text3D:INVALID_STREAMER_ID)
			{
				DestroyDynamic3DTextLabel(VehicleInfo[i][vinfo_INFO_LABEL]);
				VehicleInfo[i][vinfo_INFO_LABEL] = Text3D:INVALID_STREAMER_ID;
			}
			
			new label_str[128];
			format(label_str, sizeof label_str, "ID: %d", VehicleInfo[i][vinfo_ID]);
			VehicleInfo[i][vinfo_INFO_LABEL] = CreateDynamic3DTextLabel(label_str, -1, 0.0, 0.0, VEHICLE_INFO_LABEL_OFFSETZ, VEHICLE_INFO_LABEL_DISTANCE, .testlos = true, .attachedvehicle = VehicleInfo[i][vinfo_VEHICLE_ID]);
			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, VehicleInfo[i][vinfo_INFO_LABEL], E_STREAMER_EXTRA_ID, _:LABEL_TYPE_DEBUG_VEHICLES);

		}
	}
	return 1;
}

DestroyVehiclesInfoLabels()
{
	foreach(new i : VehicleInfo)
	{
		if(VehicleInfo[i][vinfo_INFO_LABEL] != Text3D:INVALID_STREAMER_ID)
		{
			DestroyDynamic3DTextLabel(VehicleInfo[i][vinfo_INFO_LABEL]);
			VehicleInfo[i][vinfo_INFO_LABEL] = Text3D:INVALID_STREAMER_ID;
		}
	}
	return 1;
}