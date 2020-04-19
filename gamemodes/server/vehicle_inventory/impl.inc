#include <YSI\y_hooks>

hook OnScriptInit()
{
	Iter_Init(VehicleInventory);
	return 1;
}

hook OnVehicleLoaded(vehindex)
{
	if(VehicleModelHasInventory(VehicleInfo[vehindex][vinfo_MODELID]))
	{
		inline OnQueryLoad()
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				for(new i = 0; i != rows; i ++)
				{
					new bool:isnull_params, id, position;
					cache_get_value_name_int(i, "id", id);
					cache_get_value_name_int(i, "position", position);
					if((position < 0 || position >= MAX_VEHICLE_INVENTORY_SLOTS) || Iter_Contains(VehicleInventory[vehindex], position))
					{
						position = Iter_Free(VehicleInventory[vehindex]);
						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicle_inventory SET position = %d WHERE id = %d;", position, id);
						mysql_tquery(vcrp_db, QUERY_BUFFER);
					}
					VehicleInventory[vehindex][position][vinv_ID] = id;
					cache_get_value_name_int(i, "item_id", VehicleInventory[vehindex][position][vinv_ITEM_ID]);
					cache_get_value_name_int(i, "amount", VehicleInventory[vehindex][position][vinv_AMOUNT]);
					cache_is_value_name_null(i, "params", isnull_params);
					if(!isnull_params) cache_get_value_name(i, "params", VehicleInventory[vehindex][position][vinv_PARAMS], 128);
					Iter_Add(VehicleInventory[vehindex], position);
				}
			}
		}
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM vehicle_inventory WHERE vehicle_id = %d LIMIT "#MAX_VEHICLE_INVENTORY_SLOTS";", VehicleInfo[vehindex][vinfo_ID]);
		mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");

		//Area
		if(vInvArea[vehindex] != INVALID_STREAMER_ID)
		DestroyDynamicArea(vInvArea[vehindex]);

		new Float:vSize[3];
		GetVehicleModelInfo(VehicleInfo[vehindex][vinfo_MODELID], VEHICLE_MODEL_INFO_SIZE, vSize[0], vSize[1], vSize[2]);

		vInvArea[vehindex] = CreateDynamicCylinder(0.0, 0.0, 0.0, 3.0, 0.5);
		AttachDynamicAreaToVehicle(vInvArea[vehindex], VehicleInfo[vehindex][vinfo_VEHICLE_ID], 0.0, -(vSize[1] / 2.0), -(vSize[2] / 2.0));
		
		new streamer_info[2];
		streamer_info[0] = _:AREA_TYPE_VINV;
        streamer_info[1] = vehindex;
        Streamer_SetArrayData(STREAMER_TYPE_AREA, vInvArea[vehindex], E_STREAMER_EXTRA_ID, streamer_info);
	}
	return 1;
}

hook OnVehicleDestroyedEx(vehindex, vehicleid)
{
	new tmp_VehicleInventory[E_VehicleInventory];
	for(new i = 0; i < MAX_VEHICLE_INVENTORY_SLOTS; i ++)
	VehicleInventory[vehindex][i] = tmp_VehicleInventory;

	if(vInvArea[vehindex] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(vInvArea[vehindex]);
		vInvArea[vehindex] = INVALID_STREAMER_ID;
	}

	Iter_Clear(VehicleInventory[vehindex]);
	return 1;
}

public OnVehicleInvItemDBAdded(vehindex, index, item_id, params[], amount)
{
	if(Iter_Contains(VehicleInventory[vehindex], index)) VehicleInventory[vehindex][index][vinv_AMOUNT] += amount;
	else
	{
		VehicleInventory[vehindex][index][vinv_ID] = cache_insert_id();
		VehicleInventory[vehindex][index][vinv_ITEM_ID] = item_id;
		VehicleInventory[vehindex][index][vinv_AMOUNT] = amount;
		format(VehicleInventory[vehindex][index][vinv_PARAMS], 128, "%s", params);
		Iter_Add(VehicleInventory[vehindex], index);
	}
	CallRemoteFunction("OnVehicleInvItemAdded", "idd", vehindex, index, amount);
	return 1;
}