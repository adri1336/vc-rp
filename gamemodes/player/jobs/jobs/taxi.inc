#include <YSI\y_hooks>

loadtext lang[taxi];

enum E_Taxi_VehicleInfo
{
	bool:vtaxi_OCCUPIED,
	Timer:vtaxi_TIMER,
	Float:vtaxi_DISTANCE,
	Float:vtaxi_OLD_POS[3],
};
new Taxi_VehicleInfo[MAX_VEHICLES][E_Taxi_VehicleInfo];

#define TAXI_UPDATE_INTERVAL 4000
#define TAXI_AUTOPILOT_SECONDS 30

new bool:pTaxiRequested[MAX_PLAYERS],
	bool:pWaitingTaxiResponse[MAX_PLAYERS],
	bool:pTaxiDriverInJob[MAX_PLAYERS],
	pTaxiInfo[MAX_PLAYERS] = {INVALID_PLAYER_ID, ...},
	Timer:pTaxiAutopilotRequest[MAX_PLAYERS] = {Timer:-1, ...};

forward OnPlayerRequestTaxi(playerid);
forward OnPlayerGpsToTaxiDriver(playerid, taxi_driver);

hook OnVehicleLoaded(vehindex)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_JOB && VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TAXI)
	{
		Taxi_VehicleInfo[vehindex][vtaxi_TIMER] = Timer:-1;
	}
	return 1;
}

hook OnVehicleSpawnEx(vehindex)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_JOB && VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TAXI)
	{
		Taxi_VehicleInfo[vehindex][vtaxi_OCCUPIED] = false;
		Taxi_VehicleInfo[vehindex][vtaxi_DISTANCE] = 0.0;
		Taxi_VehicleInfo[vehindex][vtaxi_OLD_POS][0] = 0.0;
		Taxi_VehicleInfo[vehindex][vtaxi_OLD_POS][1] = 0.0;
		Taxi_VehicleInfo[vehindex][vtaxi_OLD_POS][2] = 0.0;
		if(Taxi_VehicleInfo[vehindex][vtaxi_TIMER] != Timer:-1)
		{
			stop Taxi_VehicleInfo[vehindex][vtaxi_TIMER];
			Taxi_VehicleInfo[vehindex][vtaxi_TIMER] = Timer:-1;
		}
	}
	return 1;
}

hook OnVehicleDeathEx(vehindex, killerid)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_JOB && VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TAXI)
	{
		Taxi_VehicleInfo[vehindex][vtaxi_OCCUPIED] = false;
		Taxi_VehicleInfo[vehindex][vtaxi_DISTANCE] = 0.0;
		Taxi_VehicleInfo[vehindex][vtaxi_OLD_POS][0] = 0.0;
		Taxi_VehicleInfo[vehindex][vtaxi_OLD_POS][1] = 0.0;
		Taxi_VehicleInfo[vehindex][vtaxi_OLD_POS][2] = 0.0;
		if(Taxi_VehicleInfo[vehindex][vtaxi_TIMER] != Timer:-1)
		{
			stop Taxi_VehicleInfo[vehindex][vtaxi_TIMER];
			Taxi_VehicleInfo[vehindex][vtaxi_TIMER] = Timer:-1;
		}
	}
	return 1;
}

hook OnVehicleDestroyedEx(vehindex, vehicleid)
{
	Taxi_VehicleInfo[vehindex][vtaxi_OCCUPIED] = false;
	Taxi_VehicleInfo[vehindex][vtaxi_DISTANCE] = 0.0;
	Taxi_VehicleInfo[vehindex][vtaxi_OLD_POS][0] = 0.0;
	Taxi_VehicleInfo[vehindex][vtaxi_OLD_POS][1] = 0.0;
	Taxi_VehicleInfo[vehindex][vtaxi_OLD_POS][2] = 0.0;
	if(Taxi_VehicleInfo[vehindex][vtaxi_TIMER] != Timer:-1)
	{
		stop Taxi_VehicleInfo[vehindex][vtaxi_TIMER];
		Taxi_VehicleInfo[vehindex][vtaxi_TIMER] = Timer:-1;
	}
	return 1;
}

hook OnPlayerConnect(playerid)
{
	pTaxiRequested[playerid] = false;
	pWaitingTaxiResponse[playerid] = false;
	pTaxiDriverInJob[playerid] = false;
	pTaxiInfo[playerid] = INVALID_PLAYER_ID;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	pTaxiRequested[playerid] = false;
	pWaitingTaxiResponse[playerid] = false;
	pTaxiDriverInJob[playerid] = false;
	pTaxiInfo[playerid] = INVALID_PLAYER_ID;
	if(pTaxiAutopilotRequest[playerid] != Timer:-1)
	{
		stop pTaxiAutopilotRequest[playerid];
		pTaxiAutopilotRequest[playerid] = Timer:-1;
	}
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	pTaxiRequested[playerid] = false;
	pWaitingTaxiResponse[playerid] = false;
	pTaxiDriverInJob[playerid] = false;
	pTaxiInfo[playerid] = INVALID_PLAYER_ID;
	if(pTaxiAutopilotRequest[playerid] != Timer:-1)
	{
		stop pTaxiAutopilotRequest[playerid];
		pTaxiAutopilotRequest[playerid] = Timer:-1;
	}
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_SPECTATING)
	{
		pTaxiRequested[playerid] = false;
		pWaitingTaxiResponse[playerid] = false;
		pTaxiDriverInJob[playerid] = false;
		pTaxiInfo[playerid] = INVALID_PLAYER_ID;
		if(pTaxiAutopilotRequest[playerid] != Timer:-1)
		{
			stop pTaxiAutopilotRequest[playerid];
			pTaxiAutopilotRequest[playerid] = Timer:-1;
		}
	}
	return 1;
}

hook OnPlayerGetVehicleIndex(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
	{
		new vehicle_index = pVehicleIndex[playerid];
		if(VehicleInfo[vehicle_index][vinfo_TYPE] == VEHICLE_TYPE_JOB && VehicleInfo[vehicle_index][vinfo_ID_JOB_POINT] == JOB_POINT_TAXI)
		{ //taxi
			if(VehicleInfo[vehicle_index][vinfo_DRIVER] != INVALID_PLAYER_ID && !Taxi_VehicleInfo[vehicle_index][vtaxi_OCCUPIED])
			{
				new taxi_driver = VehicleInfo[vehicle_index][vinfo_DRIVER];
				if(GetPlayerJobId(taxi_driver) == JOB_TAXI)
				{
					//pVars
					pTaxiRequested[playerid] = false;
					pWaitingTaxiResponse[playerid] = false;
					if(pTaxiAutopilotRequest[playerid] != Timer:-1)
					{
						stop pTaxiAutopilotRequest[playerid];
						pTaxiAutopilotRequest[playerid] = Timer:-1;
					}
					pTaxiDriverInJob[taxi_driver] = true;
					pTaxiInfo[playerid] = taxi_driver;
					pTaxiInfo[taxi_driver] = playerid;
					DestroyPlayerRoute(taxi_driver);

					//vVars
					Taxi_VehicleInfo[vehicle_index][vtaxi_OCCUPIED] = true;
					Taxi_VehicleInfo[vehicle_index][vtaxi_DISTANCE] = 0.0;
					GetVehiclePos(VehicleInfo[vehicle_index][vinfo_VEHICLE_ID], Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][0], Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][1], Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][2]);					
					
					//tds
					ShowPlayerAuxTextDraw(playerid, GetLangTaximeterTD(playerid));
					ShowPlayerAuxTextDraw(taxi_driver, GetLangTaximeterTD(taxi_driver));
					
					//timer
					if(Taxi_VehicleInfo[vehicle_index][vtaxi_TIMER] != Timer:-1)
					{
						stop Taxi_VehicleInfo[vehicle_index][vtaxi_TIMER];
						Taxi_VehicleInfo[vehicle_index][vtaxi_TIMER] = Timer:-1;
					}
					Taxi_VehicleInfo[vehicle_index][vtaxi_TIMER] = repeat OnTaxiUpdate(vehicle_index, taxi_driver, playerid, PI[taxi_driver][pi_ID], PI[playerid][pi_ID], Jobs_Points[ pCurrentJobIndex[taxi_driver][0] ][ pCurrentJobIndex[taxi_driver][1] ][job_point_BASE_PAYMENT]);
				}
			}
		}
	}
	return 1;
}

hook OnPlayerRequestJob(playerid, job_index, job_point_index)
{
	if(Jobs[job_index][job_ID] == JOB_TAXI && pTaxiRequested[playerid])
	{
		pTaxiRequested[playerid] = false;
		pWaitingTaxiResponse[playerid] = false;
		if(pTaxiAutopilotRequest[playerid] != Timer:-1)
		{
			stop pTaxiAutopilotRequest[playerid];
			pTaxiAutopilotRequest[playerid] = Timer:-1;
		}
	}
	return 1;
}

public OnPlayerRequestTaxi(playerid)
{
	if(pTaxiRequested[playerid])
	{
		pTaxiRequested[playerid] = false;
		pWaitingTaxiResponse[playerid] = false;
		if(pTaxiAutopilotRequest[playerid] != Timer:-1)
		{
			stop pTaxiAutopilotRequest[playerid];
			pTaxiAutopilotRequest[playerid] = Timer:-1;
		}
		Text_Send(playerid, $GAMETEXT_INFO_TAXI_CANCELLED);
	}
	else
	{
		if(pTaxiDriverInJob[playerid]) Text_Send(playerid, $MESSAGE_ERROR_TAXI_REQUEST);
		else
		{
			pTaxiRequested[playerid] = true;
			pWaitingTaxiResponse[playerid] = true;
			if(pTaxiAutopilotRequest[playerid] != Timer:-1)
			{
				stop pTaxiAutopilotRequest[playerid];
				pTaxiAutopilotRequest[playerid] = Timer:-1;
			}
			pTaxiAutopilotRequest[playerid] = defer OnPlayerRequestApTaxi(playerid);
			Text_Send(playerid, $GAMETEXT_INFO_TAXI_REQUESTED);

			new zone_name[32], Float:pos[3], Float:angle, interiorid, worldid, Float:distance;
			format(zone_name, sizeof zone_name, "%s", GetPlayerZoneName(playerid));
			GetPlayerExteriorPos(playerid, pos[0], pos[1], pos[2], angle, interiorid, worldid);
			foreach(new i : Player)
			{
				if(GetPlayerJobId(i) == JOB_TAXI)
				{
					distance = GetPlayerDistanceFromPoint(i, pos[0], pos[1], pos[2]) / 1000.0;
					if(!PI[playerid][pi_MPH]) Text_Send(i, $MESSAGE_WARNING_TAXI_CUSTOMER, zone_name, distance, playerid);
					else Text_Send(i, $MESSAGE_WARNING_TAXI_CUSTOMER_MPH, zone_name, distance * 0.621371, playerid);
				}
			}
		}
	}
	return 1;
}

timer OnPlayerRequestApTaxi[TAXI_AUTOPILOT_SECONDS * 1000](playerid)
{
	if(pTaxiRequested[playerid] && pWaitingTaxiResponse[playerid])
	{
		CallRemoteFunction("OnPlayerRequestedApTaxi", "i", playerid);
	}
	pTaxiAutopilotRequest[playerid] = Timer:-1;
}

timer OnTaxiUpdate[TAXI_UPDATE_INTERVAL](vehicle_index, driver, passenger, driver_dbid, passenger_dbid, Float:base_payment)
{
	if(
		!Iter_Contains(VehicleInfo, vehicle_index) || //veh destruido
		pVehicleIndex[driver] != vehicle_index || pVehicleIndex[passenger] != vehicle_index || //taxista o pasajero ya no esta en el taxi
		!Taxi_VehicleInfo[vehicle_index][vtaxi_OCCUPIED]) //taxi ha sido destruido
	{
		//timer
		if(Taxi_VehicleInfo[vehicle_index][vtaxi_TIMER] != Timer:-1)
		{
			stop Taxi_VehicleInfo[vehicle_index][vtaxi_TIMER];
			Taxi_VehicleInfo[vehicle_index][vtaxi_TIMER] = Timer:-1;
		}
		//player
		if(IsPlayerConnected(driver) && PI[driver][pi_ID] == driver_dbid)
		{
			//ptd
			HidePlayerAuxTextDraw(driver);
			//money
			new Float:pay_percentage = Taxi_VehicleInfo[vehicle_index][vtaxi_DISTANCE] / 1000.0;
			CallRemoteFunction("OnPlayerCompleteJob", "iddf", driver, pCurrentJobIndex[driver][0], pCurrentJobIndex[driver][1], pay_percentage);
			//pVars
			pTaxiDriverInJob[driver] = false;
			pTaxiInfo[driver] = INVALID_PLAYER_ID;
		}
		if(IsPlayerConnected(passenger) && PI[passenger][pi_ID] == passenger_dbid)
		{
			//ptd
			HidePlayerAuxTextDraw(passenger);
			//money
			new price = floatround(floatmul(base_payment, Taxi_VehicleInfo[vehicle_index][vtaxi_DISTANCE] / 1000.0));
			GivePlayerMoneyEx(passenger, -price);
			//pVars
			pTaxiDriverInJob[passenger] = false;
			pTaxiInfo[passenger] = INVALID_PLAYER_ID;
		}
		//vVars
		Taxi_VehicleInfo[vehicle_index][vtaxi_OCCUPIED] = false;
		Taxi_VehicleInfo[vehicle_index][vtaxi_DISTANCE] = 0.0;
		Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][0] = 0.0;
		Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][1] = 0.0;
		Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][2] = 0.0;
	}
	else
	{
		Taxi_VehicleInfo[vehicle_index][vtaxi_DISTANCE] += GetVehicleDistanceFromPoint(VehicleInfo[vehicle_index][vinfo_VEHICLE_ID], Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][0], Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][1], Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][2]);
		GetVehiclePos(VehicleInfo[vehicle_index][vinfo_VEHICLE_ID], Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][0], Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][1], Taxi_VehicleInfo[vehicle_index][vtaxi_OLD_POS][2]);
		new total_price = floatround(floatmul(base_payment, Taxi_VehicleInfo[vehicle_index][vtaxi_DISTANCE] / 1000.0));
		if(total_price > PI[passenger][pi_MONEY])
		{
			Text_Send(passenger, $MESSAGE_ERROR_NO_MONEY);
			RemovePlayerFromVehicle(passenger);
		}
		ShowPlayerAuxTextDraw(driver, GetLangTaximeterTD(driver, total_price));
		ShowPlayerAuxTextDraw(passenger, GetLangTaximeterTD(passenger, total_price));
	}
	return 1;
}

hook OnPlayerGpsRouteCalc(playerid, bool:gps)
{
	if(gps)
	{
		if(pTaxiInfo[playerid] != INVALID_PLAYER_ID && !pTaxiDriverInJob[playerid])
		{
			CopyPlayerRouteFromPlayer(pTaxiInfo[playerid], playerid);
			StartRoute(pTaxiInfo[playerid]);
			CallRemoteFunction("OnPlayerGpsToTaxiDriver", "ii", playerid, pTaxiInfo[playerid]);
		}
	}
	return 1;
}

GetLangTaximeterTD(playerid, amount = 0)
{
	new td_str[32];
	Text_Format_TD(td_str, sizeof td_str, PI[playerid][pi_LANG_ID], $TEXTDRAW_TAXIMETER, amount);
	format(td_str, sizeof td_str, "%s", td_str);
	return td_str;
}