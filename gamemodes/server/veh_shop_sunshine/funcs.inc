#define GetFreeSaleVehicleSlot() Iter_Free(saleVehicles)

AddSaleVehicle(index)
{
	if(index >= MAX_SALE_VEHICLES || Iter_Contains(saleVehicles, index)) return 0;
	if(saleVehicles[index][saleVeh_SLOTID] != INVALID_MENU_ID) return 0;

	saleVehicles[index][saleVeh_SLOTID] = AddModelToPreviewMenu(saleVehiclesMenu, saleVehicles[index][saleVeh_MODELID], GetVehiclePriceByModelid(saleVehicles[index][saleVeh_MODELID]), -16.0, 0.0, -55.0);
	if(saleVehicles[index][saleVeh_SLOTID] != INVALID_MENU_ID) Iter_Add(saleVehicles, index);
	return 1;
}

RemoveSaleVehicle(index, bool:db = false)
{
	if(!Iter_Contains(saleVehicles, index)) return 0;
	
	if(db)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM vehicles_shop_sunshine WHERE id = %d;", saleVehicles[index][saleVeh_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	}

	RemovePreviewMenuModel(saleVehiclesMenu, saleVehicles[index][saleVeh_SLOTID]);
	
	saleVehicles[index][saleVeh_ID] = 0;
	saleVehicles[index][saleVeh_MODELID] = 0;
	saleVehicles[index][saleVeh_SLOTID] = INVALID_MENU_ID;
	Iter_Remove(saleVehicles, index);
	return 1;
}

UpdateSaleVehicleDb(index)
{
	if(!Iter_Contains(saleVehicles, index)) return 0;
	
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles_shop_sunshine SET modelid = %d WHERE id = %d;", saleVehicles[index][saleVeh_MODELID]);
	mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	return 1;
}

IsVehSaleModelFree(modelid)
{
	foreach(new i : saleVehicles)
	{
		if(saleVehicles[i][saleVeh_MODELID] == modelid)
		{
			return 0;
		}
	}
	return 1;
}

GetSaleVehicleIndexBySlotId(slotid)
{
	foreach(new i : saleVehicles)
	{
		if(saleVehicles[i][saleVeh_SLOTID] == slotid)
		{
			return i;
		}
	}
	return -1;
}

UpdateSaleOldVehicleLabel(slot)
{
	if(VehShop_VehicleInfo[slot][vshop_AREAID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(VehShop_VehicleInfo[slot][vshop_AREAID]);
		VehShop_VehicleInfo[slot][vshop_AREAID] = INVALID_STREAMER_ID;
	}

	new streamer_info[2];
	VehShop_VehicleInfo[slot][vshop_AREAID] = CreateDynamicCylinder(0.0, 0.0, 0.0, VehicleInfo[slot][vinfo_SPAWN_POS][2] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, VehicleInfo[slot][vinfo_WORLDID], VehicleInfo[slot][vinfo_INTERIORID]);
	AttachDynamicAreaToVehicle(VehShop_VehicleInfo[slot][vshop_AREAID], VehicleInfo[slot][vinfo_VEHICLE_ID], 0.0, 0.0, 0.0 - PLAYER_LABEL_DISTANCE);
	streamer_info[0] = _:AREA_TYPE_LABEL_SALE_OLD_VEH;
	streamer_info[1] = slot;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, VehShop_VehicleInfo[slot][vshop_AREAID], E_STREAMER_EXTRA_ID, streamer_info);
	return 1;
}

IsValidSellVehicleModelid(modelid)
{
	if(Model_IsCar(modelid) || Model_IsBike(modelid) && !Model_IsManual(modelid))
	{
		return true;
	}
	return false;
}

AddOldSaleVehicle(vehicleindex, price, slot, level = 1)
{
	//player
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET type = %d, id_player = NULL, price = %d, level = %d WHERE id = %d;", _:VEHICLE_TYPE_SELL, price, level, VehicleInfo[vehicleindex][vinfo_ID]);
	mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	DeleteVehicleKeys(VehicleInfo[vehicleindex][vinfo_ID], VehicleInfo[vehicleindex][vinfo_MODELID], vehicleindex);

	//vehicle
	VehicleInfo[vehicleindex][vinfo_TYPE] = VEHICLE_TYPE_SELL;
	VehicleInfo[vehicleindex][vinfo_ID_PLAYER] = 0;
	VehShop_VehicleInfo[vehicleindex][vshop_SLOT] = slot;
	VehicleInfo[vehicleindex][vinfo_GAME_STATE] = VEHICLE_GAME_STATE_NORMAL;
	VehicleInfo[vehicleindex][vinfo_FUEL] = 0.0;
	VehicleInfo[vehicleindex][vinfo_HEALTH] = 1000.0;
	VehicleInfo[vehicleindex][vinfo_INTERIORID] = 0;
	VehicleInfo[vehicleindex][vinfo_WORLDID] = 0;
	VehicleInfo[vehicleindex][vinfo_SPAWN_POS][0] = sOldVehPositions[slot][0];
	VehicleInfo[vehicleindex][vinfo_SPAWN_POS][1] = sOldVehPositions[slot][1];
	VehicleInfo[vehicleindex][vinfo_SPAWN_POS][2] = sOldVehPositions[slot][2];
	VehicleInfo[vehicleindex][vinfo_SPAWN_ANGLE] = sOldVehPositions[slot][3];
	VehicleInfo[vehicleindex][vinfo_DAMAGE_PANELS] = 0;
	VehicleInfo[vehicleindex][vinfo_DAMAGE_DOORS] = 0;
	VehicleInfo[vehicleindex][vinfo_DAMAGE_TIRES] = 0;
	VehicleInfo[vehicleindex][vinfo_PARAMS_ENGINE] = 0;
	VehicleInfo[vehicleindex][vinfo_PARAMS_LIGHTS] = 0;
	VehicleInfo[vehicleindex][vinfo_PARAMS_ALARM] = 0;
	VehicleInfo[vehicleindex][vinfo_PARAMS_DOORS] = 0;
	VehicleInfo[vehicleindex][vinfo_PARAMS_BONNET] = 0;
	VehicleInfo[vehicleindex][vinfo_PARAMS_BOOT] = 0;
	VehicleInfo[vehicleindex][vinfo_PARAMS_OBJECTIVE] = 0;

	//sOldVehs
	VehicleInfo[vehicleindex][vinfo_PRICE] = price;
	VehicleInfo[vehicleindex][vinfo_LEVEL] = level;
	Iter_Add(sOldVehs, slot);

	// recreate		
	DestroyVehicle(VehicleInfo[vehicleindex][vinfo_VEHICLE_ID]);
	VehicleInfo[vehicleindex][vinfo_VEHICLE_ID] = CreateVehicle(VehicleInfo[vehicleindex][vinfo_MODELID], VehicleInfo[vehicleindex][vinfo_SPAWN_POS][0], VehicleInfo[vehicleindex][vinfo_SPAWN_POS][1], VehicleInfo[vehicleindex][vinfo_SPAWN_POS][2], VehicleInfo[vehicleindex][vinfo_SPAWN_ANGLE], VehicleInfo[vehicleindex][vinfo_COLOR1], VehicleInfo[vehicleindex][vinfo_COLOR2], VehicleInfo[vehicleindex][vinfo_RESPAWN_DELAY], VehicleInfo[vehicleindex][vinfo_ADDSIREN]);

	VehicleInfo[vehicleindex][vinfo_STATE] = VEHICLE_STATE_SPAWNED;
	SetVehicleVariables(vehicleindex);
	UpdateSaleOldVehicleLabel(slot);

	//update veh db
	UpdateVehicleInfoDb(vehicleindex);
	return 1;
}

UpdateSaleOldVehicleDb(index)
{
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET price = %d, level = %d WHERE id = %d;", VehicleInfo[index][vinfo_PRICE], VehicleInfo[index][vinfo_LEVEL], VehicleInfo[index][vinfo_ID]);
	mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	return 1;
}