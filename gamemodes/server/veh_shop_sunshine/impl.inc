#include <YSI\y_hooks>

hook OnVehiclesPricesLoad()
{
	sunshineAutos_Area = CreateDynamicCircle(sunshineAutos_AreaPos[0], sunshineAutos_AreaPos[1], sunshineAutos_AreaPos[2], 0, 0);
	//

	saleVehiclesMenu = CreatePreviewMenu("Sunshine Autos");
	if(saleVehiclesMenu != INVALID_MENU_ID)
	{
		inline OnSaleVehiclesLoad()
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				for(new i = 0; i != rows; i ++)
				{
					if(i >= MAX_SALE_VEHICLES)
					{
						printf("[WARNING]: Limite 'saleVehicles' superado (%d)", MAX_SALE_VEHICLES);
						break;
					}

					cache_get_value_name_int(i, "id", saleVehicles[i][saleVeh_ID]);
					cache_get_value_name_int(i, "modelid", saleVehicles[i][saleVeh_MODELID]);
					saleVehicles[i][saleVeh_SLOTID] = INVALID_MENU_ID;
					AddSaleVehicle(i);
				}
				printf("[OK]: vehicles_shop_sunshine cargado (%d/%d)", rows, MAX_SALE_VEHICLES);
			}
			else
			{
				print("[ERROR]: No se pudo cargar en 'OnSaleVehiclesLoad' (db error)");
			}
		}
		print("[INFO]: Cargando vehicles_shop_sunshine...");
		mysql_tquery_inline(vcrp_db, "SELECT * FROM vehicles_shop_sunshine;", using inline OnSaleVehiclesLoad, "");
	}

	CreateDynamicObject(CUSTOM_PICKUP_MODELID, SaleVeh_Pos[0], SaleVeh_Pos[1], SaleVeh_Pos[2], 0.0, 0.0, 0.0, VC_WORLD, 0, .streamdistance = PICKUP_DISTANCE, .drawdistance = PICKUP_DISTANCE, .priority = 10);
	Streamer_SetIntData(STREAMER_TYPE_AREA, CreateDynamicCylinder(SaleVeh_Pos[0], SaleVeh_Pos[1], SaleVeh_Pos[2] - 1.0, SaleVeh_Pos[2] + 3.0, 2.0, VC_WORLD, 0), E_STREAMER_EXTRA_ID, _:AREA_TYPE_SALE_VEHS);
	return 1;
}

hook OnVehicleLoaded(vehindex)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_SELL)
	{
		new slot = Iter_Free(sOldVehs);
		if(slot != cellmin)
		{
			VehicleInfo[vehindex][vinfo_SPAWN_POS][0] = sOldVehPositions[slot][0];
			VehicleInfo[vehindex][vinfo_SPAWN_POS][1] = sOldVehPositions[slot][1];
			VehicleInfo[vehindex][vinfo_SPAWN_POS][2] = sOldVehPositions[slot][2];
			VehicleInfo[vehindex][vinfo_SPAWN_ANGLE] = sOldVehPositions[slot][3];
			VehShop_VehicleInfo[vehindex][vshop_SLOT] = slot;
			UpdateSaleOldVehicleLabel(vehindex);
			Iter_Add(sOldVehs, slot);
		}
		else
		{
			DestroyVehicleEx(vehindex);
			print("[ERROR]: sOldVehs free slot");
		}
	}
	return 1;
}

hook OnVehicleDestroyedEx(vehindex, vehicleid)
{
	if(VehShop_VehicleInfo[vehindex][vshop_AREAID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(VehShop_VehicleInfo[vehindex][vshop_AREAID]);
		VehShop_VehicleInfo[vehindex][vshop_AREAID] = INVALID_STREAMER_ID;
	}
	VehShop_VehicleInfo[vehindex][vshop_SLOT] = 0;
	return 1;
}