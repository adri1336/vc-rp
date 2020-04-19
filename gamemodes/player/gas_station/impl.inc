#include <YSI\y_hooks>

loadtext lang[gas_station];

hook OnPlayerDisconnect(playerid, reason)
{
	StopFueling(playerid);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	StopFueling(playerid);
	return 1;
}

public OnPlayerRequestGasStation(playerid, vehicle_index)
{
	if(!pGasStation[playerid])
	{
		HidePlayerInfoMessage(playerid);
		if(VehicleInfo[vehicle_index][vinfo_PARAMS_ENGINE]) Text_Send(playerid, $MESSAGE_ERROR_ENGINE_ON);
		else
		{
			if(VehicleInfo[vehicle_index][vinfo_FUEL] >= GetVehicleMaxFuelByModelid(VehicleInfo[vehicle_index][vinfo_MODELID]) - 1.0) Text_Send(playerid, $MESSAGE_ERROR_MAX_FUEL);
			else
			{
				new price = FUELING_UP_LITERS * FUEL_PRICE_PER_LITRE;
				if(PI[playerid][pi_MONEY] < price) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
				else
				{
					Text_Send(playerid, $MESSAGE_INFO_FUEL);
					StartFueling(playerid, vehicle_index);
				}
			}
		}
	}
	return 1;
}

timer OnFuelingUp[FUELING_UP_INTERVAL](playerid, vehicle_index)
{
	new price = FUELING_UP_LITERS * FUEL_PRICE_PER_LITRE;
	if(PI[playerid][pi_MONEY] < price)
	{
		Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
		StopFueling(playerid);
	}
	else
	{
		if(VehicleInfo[vehicle_index][vinfo_PARAMS_ENGINE]) StopFueling(playerid);
		else
		{
			GivePlayerMoneyEx(playerid, -price);
			VehicleInfo[vehicle_index][vinfo_FUEL] += float(FUELING_UP_LITERS);
			if(VehicleInfo[vehicle_index][vinfo_FUEL] >= GetVehicleMaxFuelByModelid(VehicleInfo[vehicle_index][vinfo_MODELID]))
			{
				StopFueling(playerid);
				VehicleInfo[vehicle_index][vinfo_FUEL] = GetVehicleMaxFuelByModelid(VehicleInfo[vehicle_index][vinfo_MODELID]);
				Text_Send(playerid, $GAMETEXT_INFO_FUELED, VehicleInfo[vehicle_index][vinfo_FUEL], GetVehicleMaxFuelByModelid(VehicleInfo[vehicle_index][vinfo_MODELID]));
			}
			else
			{
				Text_Send(playerid, $GAMETEXT_INFO_FUELING, VehicleInfo[vehicle_index][vinfo_FUEL], GetVehicleMaxFuelByModelid(VehicleInfo[vehicle_index][vinfo_MODELID]));

				//progressbar
				new Float:fuel_percent = GetVehicleFuelPercent(vehicle_index);
				SetPlayerProgressBarBarColor(playerid, PROGRESSBAR_VEHICLE_FUEL[playerid], GetGradientColor(0xc4a473ff, 0xffb441ff, fuel_percent));
				SetPlayerProgressBarValue(playerid, PROGRESSBAR_VEHICLE_FUEL[playerid], fuel_percent);
				if(!pInvetory[playerid]) ShowVehFuncProgressBars(playerid);
			}
		}
	}
}