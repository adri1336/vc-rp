#include <YSI\y_hooks>

hook OnVehicleLoaded(vehindex)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_RENT)
	{
		if(VehicleInfo[vehindex][vinfo_ID_PLAYER])
		{
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET id_player = NULL WHERE id = %d;", VehicleInfo[vehindex][vinfo_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);
			VehicleInfo[vehindex][vinfo_ID_PLAYER] = 0;
			DeleteVehicleKeys(VehicleInfo[vehindex][vinfo_ID], VehicleInfo[vehindex][vinfo_MODELID], vehindex);
		}
		new streamer_info[2];
		Rent_VehicleInfo[vehindex][vrent_AREAID] = CreateDynamicCylinder(0.0, 0.0, 0.0, VehicleInfo[vehindex][vinfo_SPAWN_POS][2] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, VehicleInfo[vehindex][vinfo_WORLDID], VehicleInfo[vehindex][vinfo_INTERIORID]);
		AttachDynamicAreaToVehicle(Rent_VehicleInfo[vehindex][vrent_AREAID], VehicleInfo[vehindex][vinfo_VEHICLE_ID], 0.0, 0.0, 0.0 - PLAYER_LABEL_DISTANCE);
		streamer_info[0] = _:AREA_TYPE_LABEL_RENT_VEHICLE;
		streamer_info[1] = vehindex;
		Streamer_SetArrayData(STREAMER_TYPE_AREA, Rent_VehicleInfo[vehindex][vrent_AREAID], E_STREAMER_EXTRA_ID, streamer_info);	
	}
	return 1;
}

hook OnVehicleSpawnEx(vehindex)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_RENT)
	{
		if(VehicleInfo[vehindex][vinfo_ID_PLAYER])
		{
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET id_player = NULL WHERE id = %d;", VehicleInfo[vehindex][vinfo_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);
			VehicleInfo[vehindex][vinfo_ID_PLAYER] = 0;
			DeleteVehicleKeys(VehicleInfo[vehindex][vinfo_ID], VehicleInfo[vehindex][vinfo_MODELID], vehindex);
		}
		if(Rent_VehicleInfo[vehindex][vrent_AREAID] == INVALID_STREAMER_ID)
		{
			new streamer_info[2];
			Rent_VehicleInfo[vehindex][vrent_AREAID] = CreateDynamicCylinder(0.0, 0.0, 0.0, VehicleInfo[vehindex][vinfo_SPAWN_POS][2] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, VehicleInfo[vehindex][vinfo_WORLDID], VehicleInfo[vehindex][vinfo_INTERIORID]);
			AttachDynamicAreaToVehicle(Rent_VehicleInfo[vehindex][vrent_AREAID], VehicleInfo[vehindex][vinfo_VEHICLE_ID], 0.0, 0.0, 0.0 - PLAYER_LABEL_DISTANCE);
			streamer_info[0] = _:AREA_TYPE_LABEL_RENT_VEHICLE;
			streamer_info[1] = vehindex;
			Streamer_SetArrayData(STREAMER_TYPE_AREA, Rent_VehicleInfo[vehindex][vrent_AREAID], E_STREAMER_EXTRA_ID, streamer_info);
		}
	}
	return 1;
}

hook OnVehicleDestroyedEx(vehindex, vehicleid)
{
	if(Rent_VehicleInfo[vehindex][vrent_AREAID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(Rent_VehicleInfo[vehindex][vrent_AREAID]);
		Rent_VehicleInfo[vehindex][vrent_AREAID] = INVALID_STREAMER_ID;
	}
	return 1;
}