GetVehicleLevelByModelid(modelid)
{
	foreach(new i : Vehicle_Prices)
	{
		if(Vehicle_Prices[i][vehicle_price_MODELID] == modelid)
		{
			return Vehicle_Prices[i][vehicle_price_LEVEL];
		}
	}
	return 1;
}

GetVehiclePriceByModelid(modelid)
{
	foreach(new i : Vehicle_Prices)
	{
		if(Vehicle_Prices[i][vehicle_price_MODELID] == modelid)
		{
			return Vehicle_Prices[i][vehicle_price_PRICE];
		}
	}
	return vehicle_default_price;
}

GetOldVehiclePrice(vehicleindex)
{
	new price = GetVehiclePriceByModelid(VehicleInfo[vehicleindex][vinfo_MODELID]);
	price = floatround((float(price) * vehicle_depreciation) - (((VehicleInfo[vehicleindex][vinfo_DISTANCE] / 1000.0) / vehicle_depreciation_kms) * vehicle_depreciation_value));
	return price;
}

IsVehPriceModelFree(modelid)
{
	foreach(new i : Vehicle_Prices)
	{
		if(Vehicle_Prices[i][vehicle_price_MODELID] == modelid)
		{
			return 0;
		}
	}
	return 1;
}

UpdateVehiclePriceDb(index)
{
	if(!Iter_Contains(Vehicle_Prices, index)) return 0;
	
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicle_prices SET price = %d WHERE modelid = %d;", Vehicle_Prices[index][vehicle_price_PRICE], Vehicle_Prices[index][vehicle_price_MODELID]);
	mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	return 1;
}

RemoveVehiclePrice(index, bool:db = false)
{
	if(!Iter_Contains(Vehicle_Prices, index)) return 0;
	
	if(db)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM vehicle_prices WHERE modelid = %d;", Vehicle_Prices[index][vehicle_price_MODELID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	}

	Vehicle_Prices[index][vehicle_price_MODELID] = 0;
	Vehicle_Prices[index][vehicle_price_PRICE] = 0;
	Iter_Remove(Vehicle_Prices, index);
	return 1;
}