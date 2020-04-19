#define TRUCK_HEALTH_GOOD 900.0
#define TRUCK_HEALTH_MODERATE 700.0
#include <YSI\y_hooks>

loadtext lang[trucker];

enum E_Truck_VehicleInfo
{
	bool:vtruck_LOADING,
	vtruck_LOADING_SECONDS,
	vtruck_DRIVER_ID,
	vtruck_LOAD_POINT,
	vtruck_UNLOAD_POINT,
	Float:vtruck_JOB_DISTANCE,
	vtruck_TRAILER_INDEX
};
new Truck_VehicleInfo[MAX_VEHICLES][E_Truck_VehicleInfo];

enum E_Job_Truck_Points
{
	Float:ptruck_POS[4],
	bool:ptruck_GATE,
	ptruck_GATE_MDL,
	Float:ptruck_GATE_POS[6],
	Float:ptruck_GATE_OPEN_POS[6],
	ptruck_GATE_OBJECTID,
	Timer:ptruck_GATE_TIMER
};
new Job_Truck1_LoadPoints[][E_Job_Truck_Points] =
{
	{{4944.071777, 771.243103, 5.863918, 270.364746}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1},
	{{4943.475097, 804.857543, 5.993471, 270.364746}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1}
};
new Job_Truck1_UnloadPoints[][E_Job_Truck_Points] =
{
	{{6146.139160, -430.986633, 5.228319, 245.0}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1},
	{{6046.561523, 1920.073852, 5.303111, 180.0}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1},
	{{4688.147460, 2209.823242, 3.286853, 180.0}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1},
	{{4991.976074, 212.4212340, 1.924901, 0.0}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1}
};
new Job_Truck2_LoadPoints[][E_Job_Truck_Points] =
{
	{{5078.213378, -337.531738, 6.700835, 156.998016}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1},
	{{5068.813964, -333.542968, 6.707439, 157.041503}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1},
	{{5058.747558, -329.279205, 6.722369, 157.045104}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1},
	{{5045.401855, -323.633819, 6.814512, 157.052307}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1}
};
new Job_Truck2_UnloadPoints[][E_Job_Truck_Points] =
{
	{{4688.606933, 2553.812988, 3.824343, 0.55256}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1},
	{{6414.920898, 2034.293579, 7.489838, 183.877}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1},
	{{5731.558593, 2460.977050, 6.493690, 269.844}, false, 0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, INVALID_STREAMER_ID, Timer:-1}
};


#define TRUCK_TIMER_INTERVAL 1000
#define TRUCK_CANCEL_SECONDS 20
#define TRUCK1_LOAD_SECONDS 10
#define TRUCK2_LOAD_SECONDS 20
new pTruckVehicleIndex[MAX_PLAYERS] = {INVALID_VEHICLE_INDEX, ...},
	Timer:pTruckTimer[MAX_PLAYERS] = {Timer:-1, ...},
	pTruckCancelSeconds[MAX_PLAYERS];

hook OnScriptInit()
{
	for(new i = 0; i < sizeof Job_Truck1_LoadPoints; i ++)
	{
		if(Job_Truck1_LoadPoints[i][ptruck_GATE])
		{
			Job_Truck1_LoadPoints[i][ptruck_GATE_OBJECTID] = CreateDynamicObject(Job_Truck1_LoadPoints[i][ptruck_GATE_MDL], Job_Truck1_LoadPoints[i][ptruck_GATE_POS][0], Job_Truck1_LoadPoints[i][ptruck_GATE_POS][1], Job_Truck1_LoadPoints[i][ptruck_GATE_POS][2], Job_Truck1_LoadPoints[i][ptruck_GATE_POS][3], Job_Truck1_LoadPoints[i][ptruck_GATE_POS][4], Job_Truck1_LoadPoints[i][ptruck_GATE_POS][5], .interiorid = 0, .worldid = VC_WORLD);
			Streamer_SetIntData(STREAMER_TYPE_OBJECT, Job_Truck1_LoadPoints[i][ptruck_GATE_OBJECTID], E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_TRUCK1_GATE);
		}
	}
	return 1;
}

ResetTruckInfo(vehindex, bool:respawn = false)
{
	Truck_VehicleInfo[vehindex][vtruck_LOADING] = false;
	Truck_VehicleInfo[vehindex][vtruck_DRIVER_ID] = 0;
	Truck_VehicleInfo[vehindex][vtruck_LOAD_POINT] = -1;
	Truck_VehicleInfo[vehindex][vtruck_UNLOAD_POINT] = -1;
	Truck_VehicleInfo[vehindex][vtruck_JOB_DISTANCE] = 0.0;
	if(respawn)
	{
		if(Truck_VehicleInfo[vehindex][vtruck_TRAILER_INDEX] != INVALID_VEHICLE_INDEX)
		{
			SetVehicleToRespawn(VehicleInfo[ Truck_VehicleInfo[vehindex][vtruck_TRAILER_INDEX] ][vinfo_VEHICLE_ID]);
		}
		SetVehicleToRespawn(VehicleInfo[vehindex][vinfo_VEHICLE_ID]);
	}
	Truck_VehicleInfo[vehindex][vtruck_TRAILER_INDEX] = INVALID_VEHICLE_INDEX;
	return 1;
}

hook OnVehicleLoaded(vehindex)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_JOB && (VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_1 || VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_2))
	{
		Truck_VehicleInfo[vehindex][vtruck_TRAILER_INDEX] = INVALID_VEHICLE_INDEX;
		ResetTruckInfo(vehindex);
	}
	return 1;
}

hook OnVehicleSpawnEx(vehindex)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_JOB && (VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_1 || VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_2))
	{
		ResetTruckInfo(vehindex);
	}
	return 1;
}

hook OnVehicleDeathEx(vehindex, killerid)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_JOB && (VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_1 || VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_2))
	{
		ResetTruckInfo(vehindex);
	}
	return 1;
}

hook OnVehicleDestroyedEx(vehindex, vehicleid)
{
	ResetTruckInfo(vehindex);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(pTruckTimer[playerid] != Timer:-1)
	{
		stop pTruckTimer[playerid];
		pTruckTimer[playerid] = Timer:-1;
	}
	if(pTruckVehicleIndex[playerid] != INVALID_VEHICLE_INDEX)
	{
		ResetTruckInfo(pTruckVehicleIndex[playerid], true);
	}
	pTruckVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
	pTruckCancelSeconds[playerid] = 0;
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(pTruckTimer[playerid] != Timer:-1)
	{
		stop pTruckTimer[playerid];
		pTruckTimer[playerid] = Timer:-1;
	}
	if(pTruckVehicleIndex[playerid] != INVALID_VEHICLE_INDEX)
	{
		ResetTruckInfo(pTruckVehicleIndex[playerid], true);
	}
	pTruckVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
	pTruckCancelSeconds[playerid] = 0;
	return 1;
}

hook OnPlayerGetVehicleIndex(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new vehindex = pVehicleIndex[playerid];
		if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_JOB)
		{
			if(VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_1 && GetPlayerJobPointId(playerid) == JOB_POINT_TRUCKER_1)
			{
				if(Truck_VehicleInfo[vehindex][vtruck_DRIVER_ID] == 0 && pTruckVehicleIndex[playerid] == INVALID_VEHICLE_INDEX) //no tiene conductor y el player no tiene camion asociado
				{
					if(Truck_VehicleInfo[vehindex][vtruck_LOAD_POINT] == -1)
					Truck_VehicleInfo[vehindex][vtruck_LOAD_POINT] = random(sizeof Job_Truck1_LoadPoints);
					//Route a Load Point
					new load_point_index = Truck_VehicleInfo[vehindex][vtruck_LOAD_POINT];
					DestroyPlayerRoute(playerid, 1);
					AddRouteCp(playerid, Job_Truck1_LoadPoints[load_point_index][ptruck_POS][0], Job_Truck1_LoadPoints[load_point_index][ptruck_POS][1], Job_Truck1_LoadPoints[load_point_index][ptruck_POS][2], 5.0);
					StartRoute(playerid);
					Text_Send(playerid, $MESSAGE_WARNING_LOAD_TRUCK);
				}
				else if(Truck_VehicleInfo[vehindex][vtruck_DRIVER_ID] == PI[playerid][pi_ID])
				{
					//tiene conductor
					ShowPlayerRoute(playerid);
					HidePlayerInfoMessage(playerid);
				}
				//timer
				if(pTruckTimer[playerid] != Timer:-1)
				{
					stop pTruckTimer[playerid];
					pTruckTimer[playerid] = Timer:-1;
				}
				pTruckTimer[playerid] = repeat OnPlayerTruckCheck(playerid, GetPlayerJobPointId(playerid));
			}
			else if(VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_2 && GetPlayerJobPointId(playerid) == JOB_POINT_TRUCKER_2)
			{
				//truck grande
				if(Truck_VehicleInfo[vehindex][vtruck_DRIVER_ID] == 0 && pTruckVehicleIndex[playerid] == INVALID_VEHICLE_INDEX) //no tiene conductor y el player no tiene camion asociado
				{
					if(Truck_VehicleInfo[vehindex][vtruck_TRAILER_INDEX] != INVALID_VEHICLE_INDEX)
					{
						pTruckCancelSeconds[playerid] = TRUCK_CANCEL_SECONDS;
						if(Truck_VehicleInfo[vehindex][vtruck_LOAD_POINT] == -1)
						Truck_VehicleInfo[vehindex][vtruck_LOAD_POINT] = random(sizeof Job_Truck2_LoadPoints);
						//Route a Load Point
						new load_point_index = Truck_VehicleInfo[vehindex][vtruck_LOAD_POINT];
						DestroyPlayerRoute(playerid, 1);
						AddRouteCp(playerid, Job_Truck2_LoadPoints[load_point_index][ptruck_POS][0], Job_Truck2_LoadPoints[load_point_index][ptruck_POS][1], Job_Truck2_LoadPoints[load_point_index][ptruck_POS][2], 5.0);
						StartRoute(playerid);
						Text_Send(playerid, $MESSAGE_WARNING_LOAD_TRUCK);
					}
					else Text_Send(playerid, $MESSAGE_WARNING_NEED_TRAILER);
				}
				else if(Truck_VehicleInfo[vehindex][vtruck_DRIVER_ID] == PI[playerid][pi_ID])
				{
					//tiene conductor
					if(GetVehicleTrailer(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID]) == VehicleInfo[Truck_VehicleInfo[vehindex][vtruck_TRAILER_INDEX]][vinfo_VEHICLE_ID])
					{
						ShowPlayerRoute(playerid);
						HidePlayerInfoMessage(playerid);
					}
				}
				//timer
				if(pTruckTimer[playerid] != Timer:-1)
				{
					stop pTruckTimer[playerid];
					pTruckTimer[playerid] = Timer:-1;
				}
				pTruckTimer[playerid] = repeat OnPlayerTruckCheck(playerid, GetPlayerJobPointId(playerid));
			}
		}
	}
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(oldstate == PLAYER_STATE_DRIVER && GetPlayerJobId(playerid) == JOB_TRUCKER) // se ha bajado de su camion
	{
		if(pTruckVehicleIndex[playerid] != INVALID_VEHICLE_INDEX)
		{
			pTruckCancelSeconds[playerid] = TRUCK_CANCEL_SECONDS;
			HidePlayerRoute(playerid);
		}
		HidePlayerAuxTextDraw(playerid);
	}
	else if(newstate == PLAYER_STATE_SPECTATING)
	{
		if(pTruckTimer[playerid] != Timer:-1)
		{
			stop pTruckTimer[playerid];
			pTruckTimer[playerid] = Timer:-1;
		}
		if(pTruckVehicleIndex[playerid] != INVALID_VEHICLE_INDEX)
		{
			ResetTruckInfo(pTruckVehicleIndex[playerid], true);
		}
		pTruckVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
		pTruckCancelSeconds[playerid] = 0;
	}
	return 1;
}

timer OnPlayerTruckCheck[TRUCK_TIMER_INTERVAL](playerid, job_point_id)
{
	new player_state = GetPlayerState(playerid);
	switch(job_point_id)
	{
		case JOB_POINT_TRUCKER_1:
		{
			if(pTruckVehicleIndex[playerid] != INVALID_VEHICLE_INDEX) //tiene camion asociado
			{
				if(Truck_VehicleInfo[pTruckVehicleIndex[playerid]][vtruck_DRIVER_ID] != PI[playerid][pi_ID])
				{
					stop pTruckTimer[playerid];
					pTruckTimer[playerid] = Timer:-1;
					ResetTruckInfo(pTruckVehicleIndex[playerid], true);
					pTruckVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
					pTruckCancelSeconds[playerid] = 0;
					Text_Send(playerid, $MESSAGE_ERROR_TRUCK_CANCELED);
				}
				else
				{
					if(pTruckVehicleIndex[playerid] != pVehicleIndex[playerid])
					{
						//tienes x segundos
						pTruckCancelSeconds[playerid] --;
						if(pTruckCancelSeconds[playerid] <= 0)
						{
							stop pTruckTimer[playerid];
							pTruckTimer[playerid] = Timer:-1;
							ResetTruckInfo(pTruckVehicleIndex[playerid], true);
							pTruckVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
							pTruckCancelSeconds[playerid] = 0;
							HidePlayerInfoMessage(playerid);
							Text_Send(playerid, $MESSAGE_ERROR_TRUCK_CANCELED);
						}
						else PlayerTruckCancelMsg(playerid, pTruckCancelSeconds[playerid]);
					}
					else
					{
						//check estado
						if(pInRoute[playerid])
						{
							new Float:vehicle_health;
							GetVehicleHealth(VehicleInfo[pTruckVehicleIndex[playerid]][vinfo_VEHICLE_ID], vehicle_health);
							PlayerTruckStateAux(playerid, vehicle_health);
						}
						else
						{
							new load_point_index = Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT];
							if(GetVehicleDistanceFromPoint(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID], Job_Truck1_UnloadPoints[load_point_index][ptruck_POS][0], Job_Truck1_UnloadPoints[load_point_index][ptruck_POS][1], Job_Truck1_UnloadPoints[load_point_index][ptruck_POS][2]) <= 5.0)
							{
								new Float:angle;
								GetVehicleZAngle(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID], angle);
								if( (angle > (Job_Truck1_UnloadPoints[load_point_index][ptruck_POS][3] - 15.0)) && (angle < (Job_Truck1_UnloadPoints[load_point_index][ptruck_POS][3] + 15.0)) )
								{
									Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] ++;
									if(Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] >= TRUCK1_LOAD_SECONDS)
									{
										pTruckVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_DRIVER_ID] = 0;
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] = -1;
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT] = -1;
										HidePlayerAuxTextDraw(playerid);
										VehicleInfo[pVehicleIndex[playerid]][vinfo_PARAMS_ENGINE] = 1;
										SetVehicleParams(pVehicleIndex[playerid]);
										if(Job_Truck1_UnloadPoints[load_point_index][ptruck_GATE] && Job_Truck1_UnloadPoints[load_point_index][ptruck_GATE_OBJECTID] != INVALID_STREAMER_ID)
										MoveDynamicObject(Job_Truck1_UnloadPoints[load_point_index][ptruck_GATE_OBJECTID], Job_Truck1_UnloadPoints[load_point_index][ptruck_GATE_POS][0], Job_Truck1_UnloadPoints[load_point_index][ptruck_GATE_POS][1], Job_Truck1_UnloadPoints[load_point_index][ptruck_GATE_POS][2], 3.0, Job_Truck1_UnloadPoints[load_point_index][ptruck_GATE_POS][3], Job_Truck1_UnloadPoints[load_point_index][ptruck_GATE_POS][4], Job_Truck1_UnloadPoints[load_point_index][ptruck_GATE_POS][5]);
										//job complete
										new Float:vehicle_health, Float:pay_percentage = Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_JOB_DISTANCE] / 1000.0;
										GetVehicleHealth(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID], vehicle_health);
										if(vehicle_health < TRUCK_HEALTH_GOOD) pay_percentage = (90.0 * pay_percentage) / 100.0;
										else if(vehicle_health < TRUCK_HEALTH_MODERATE) pay_percentage = (80.0 * pay_percentage) / 100.0;
										CallRemoteFunction("OnPlayerCompleteJob", "iddf", playerid, pCurrentJobIndex[playerid][0], pCurrentJobIndex[playerid][1], pay_percentage);
										//route
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] = random(sizeof Job_Truck1_LoadPoints);
										DestroyPlayerRoute(playerid, 1);
										CalcRoute(playerid, Job_Truck1_LoadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] ][ptruck_POS][0], Job_Truck1_LoadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] ][ptruck_POS][1], Job_Truck1_LoadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] ][ptruck_POS][2]);
										Text_Send(playerid, $MESSAGE_WARNING_TRUCK_COMPLETE);
									}
									else
									{
										VehicleInfo[pVehicleIndex[playerid]][vinfo_PARAMS_ENGINE] = 0;
										SetVehicleParams(pVehicleIndex[playerid]);
										PlayerTruckStateAux(playerid, 1000.0, false, true, TRUCK1_LOAD_SECONDS - Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS]);
										if(Job_Truck1_UnloadPoints[load_point_index][ptruck_GATE] && Job_Truck1_UnloadPoints[load_point_index][ptruck_GATE_OBJECTID] != INVALID_STREAMER_ID)
										MoveDynamicObject(Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OBJECTID], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][0], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][1], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][2], 3.0, Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][3], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][4], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][5]);
									}
								}
								else
								{
									if(Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING])
									{
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] = 0;
										HidePlayerAuxTextDraw(playerid);
									}
								}
							}
							else
							{
								Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
								Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] = 0;
								HidePlayerAuxTextDraw(playerid);
							}
						}
					}
				}
			}
			else
			{
				if(player_state == PLAYER_STATE_DRIVER)
				{
					//check load point
					if(VehicleInfo[pVehicleIndex[playerid]][vinfo_TYPE] == VEHICLE_TYPE_JOB && VehicleInfo[pVehicleIndex[playerid]][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_1 && Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_DRIVER_ID] == 0)
					{
						new load_point_index = Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT];
						if(GetVehicleDistanceFromPoint(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID], Job_Truck1_LoadPoints[load_point_index][ptruck_POS][0], Job_Truck1_LoadPoints[load_point_index][ptruck_POS][1], Job_Truck1_LoadPoints[load_point_index][ptruck_POS][2]) <= 5.0)
						{
							new Float:angle;
							GetVehicleZAngle(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID], angle);
							if( (angle > (Job_Truck1_LoadPoints[load_point_index][ptruck_POS][3] - 15.0)) && (angle < (Job_Truck1_LoadPoints[load_point_index][ptruck_POS][3] + 15.0)) )
							{
								Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] ++;
								if(Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] >= TRUCK1_LOAD_SECONDS)
								{
									pTruckVehicleIndex[playerid] = pVehicleIndex[playerid];
									Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
									Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] = 0;
									Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] = -1;
									Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_DRIVER_ID] = PI[playerid][pi_ID];
									Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT] = random(sizeof Job_Truck1_UnloadPoints);
									Text_Send(playerid, $MESSAGE_INFO_TRUCK_LOADED);
									HidePlayerAuxTextDraw(playerid);
									VehicleInfo[pVehicleIndex[playerid]][vinfo_PARAMS_ENGINE] = 1;
									SetVehicleParams(pVehicleIndex[playerid]);
									if(Job_Truck1_LoadPoints[load_point_index][ptruck_GATE] && Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OBJECTID] != INVALID_STREAMER_ID)
									MoveDynamicObject(Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OBJECTID], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_POS][0], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_POS][1], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_POS][2], 3.0, Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_POS][3], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_POS][4], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_POS][5]);
									//route
									DestroyPlayerRoute(playerid, 1);
									CalcRoute(playerid, Job_Truck1_UnloadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT] ][ptruck_POS][0], Job_Truck1_UnloadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT] ][ptruck_POS][1], Job_Truck1_UnloadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT] ][ptruck_POS][2]);
									RepairVehicle(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID]);
								}
								else
								{
									VehicleInfo[pVehicleIndex[playerid]][vinfo_PARAMS_ENGINE] = 0;
									SetVehicleParams(pVehicleIndex[playerid]);
									PlayerTruckStateAux(playerid, 1000.0, true, false, TRUCK1_LOAD_SECONDS - Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS]);
									if(Job_Truck1_LoadPoints[load_point_index][ptruck_GATE] && Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OBJECTID] != INVALID_STREAMER_ID)
									MoveDynamicObject(Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OBJECTID], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][0], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][1], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][2], 3.0, Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][3], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][4], Job_Truck1_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][5]);
								}
							}
							else
							{
								if(Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING])
								{
									Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
									Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] = 0;
									HidePlayerAuxTextDraw(playerid);
								}
							}
						}
						else
						{
							Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
							Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] = 0;
							HidePlayerAuxTextDraw(playerid);
						}
					}
				}
				else
				{
					stop pTruckTimer[playerid];
					pTruckTimer[playerid] = Timer:-1;
				}
			}
		}
		case JOB_POINT_TRUCKER_2:
		{
			if(pTruckVehicleIndex[playerid] != INVALID_VEHICLE_INDEX) //tiene camion asociado
			{
				if(Truck_VehicleInfo[pTruckVehicleIndex[playerid]][vtruck_DRIVER_ID] != PI[playerid][pi_ID])
				{
					stop pTruckTimer[playerid];
					pTruckTimer[playerid] = Timer:-1;
					ResetTruckInfo(pTruckVehicleIndex[playerid], true);
					pTruckVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
					pTruckCancelSeconds[playerid] = 0;
					Text_Send(playerid, $MESSAGE_ERROR_TRUCK_CANCELED);
				}
				else
				{
					if(pTruckVehicleIndex[playerid] != pVehicleIndex[playerid])
					{
						//tienes x segundos
						pTruckCancelSeconds[playerid] --;
						if(pTruckCancelSeconds[playerid] <= 0)
						{
							stop pTruckTimer[playerid];
							pTruckTimer[playerid] = Timer:-1;
							ResetTruckInfo(pTruckVehicleIndex[playerid], true);
							pTruckVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
							pTruckCancelSeconds[playerid] = 0;
							HidePlayerInfoMessage(playerid);
							Text_Send(playerid, $MESSAGE_ERROR_TRUCK_CANCELED);
						}
						else PlayerTruckCancelMsg(playerid, pTruckCancelSeconds[playerid]);
					}
					else if(GetVehicleTrailer(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID]) != VehicleInfo[Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_TRAILER_INDEX]][vinfo_VEHICLE_ID])
					{
						//tienes x segundos
						pTruckCancelSeconds[playerid] --;
						if(pTruckCancelSeconds[playerid] <= 0)
						{
							stop pTruckTimer[playerid];
							pTruckTimer[playerid] = Timer:-1;
							ResetTruckInfo(pTruckVehicleIndex[playerid], true);
							pTruckCancelSeconds[playerid] = 0;
							HidePlayerInfoMessage(playerid);
							Text_Send(playerid, $MESSAGE_ERROR_TRUCK_CANCELED);
						}
						else PlayerTruckCancelMsg(playerid, pTruckCancelSeconds[playerid], true, true);
					}
					else
					{
						HidePlayerInfoMessage(playerid);
						//check estado
						if(pInRoute[playerid])
						{
							new Float:vehicle_health;
							GetVehicleHealth(VehicleInfo[ Truck_VehicleInfo[ pTruckVehicleIndex[playerid]  ][vtruck_TRAILER_INDEX] ][vinfo_VEHICLE_ID], vehicle_health);
							PlayerTruckStateAux(playerid, vehicle_health);
						}
						else
						{
							new load_point_index = Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT];
							if(GetVehicleDistanceFromPoint(VehicleInfo[ Truck_VehicleInfo[ pTruckVehicleIndex[playerid] ][vtruck_TRAILER_INDEX] ][vinfo_VEHICLE_ID], Job_Truck2_UnloadPoints[load_point_index][ptruck_POS][0], Job_Truck2_UnloadPoints[load_point_index][ptruck_POS][1], Job_Truck2_UnloadPoints[load_point_index][ptruck_POS][2]) <= 8.0)
							{
								new Float:angle;
								GetVehicleZAngle(VehicleInfo[ Truck_VehicleInfo[ pTruckVehicleIndex[playerid] ][vtruck_TRAILER_INDEX] ][vinfo_VEHICLE_ID], angle);
								if( (angle > (Job_Truck2_UnloadPoints[load_point_index][ptruck_POS][3] - 20.0)) && (angle < (Job_Truck2_UnloadPoints[load_point_index][ptruck_POS][3] + 20.0)) )
								{
									Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] ++;
									if(Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] >= TRUCK2_LOAD_SECONDS)
									{
										pTruckVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_DRIVER_ID] = 0;
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] = -1;
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT] = -1;
										HidePlayerAuxTextDraw(playerid);
										VehicleInfo[pVehicleIndex[playerid]][vinfo_PARAMS_ENGINE] = 1;
										SetVehicleParams(pVehicleIndex[playerid]);
										if(Job_Truck2_UnloadPoints[load_point_index][ptruck_GATE] && Job_Truck2_UnloadPoints[load_point_index][ptruck_GATE_OBJECTID] != INVALID_STREAMER_ID)
										MoveDynamicObject(Job_Truck2_UnloadPoints[load_point_index][ptruck_GATE_OBJECTID], Job_Truck2_UnloadPoints[load_point_index][ptruck_GATE_POS][0], Job_Truck2_UnloadPoints[load_point_index][ptruck_GATE_POS][1], Job_Truck2_UnloadPoints[load_point_index][ptruck_GATE_POS][2], 3.0, Job_Truck2_UnloadPoints[load_point_index][ptruck_GATE_POS][3], Job_Truck2_UnloadPoints[load_point_index][ptruck_GATE_POS][4], Job_Truck2_UnloadPoints[load_point_index][ptruck_GATE_POS][5]);
										//job complete
										new Float:vehicle_health, Float:pay_percentage = Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_JOB_DISTANCE] / 1000.0;
										GetVehicleHealth(VehicleInfo[ Truck_VehicleInfo[ pVehicleIndex[playerid] ][vtruck_TRAILER_INDEX] ][vinfo_VEHICLE_ID], vehicle_health);
										if(vehicle_health < TRUCK_HEALTH_GOOD) pay_percentage = (90.0 * pay_percentage) / 100.0;
										else if(vehicle_health < TRUCK_HEALTH_MODERATE) pay_percentage = (80.0 * pay_percentage) / 100.0;
										CallRemoteFunction("OnPlayerCompleteJob", "iddf", playerid, pCurrentJobIndex[playerid][0], pCurrentJobIndex[playerid][1], pay_percentage);
										//route
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] = random(sizeof Job_Truck2_LoadPoints);
										DestroyPlayerRoute(playerid, 1);
										CalcRoute(playerid, Job_Truck2_LoadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] ][ptruck_POS][0], Job_Truck2_LoadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] ][ptruck_POS][1], Job_Truck2_LoadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] ][ptruck_POS][2]);
										Text_Send(playerid, $MESSAGE_WARNING_TRUCK_COMPLETE);
									}
									else
									{
										VehicleInfo[pVehicleIndex[playerid]][vinfo_PARAMS_ENGINE] = 0;
										SetVehicleParams(pVehicleIndex[playerid]);
										PlayerTruckStateAux(playerid, 1000.0, false, true, TRUCK2_LOAD_SECONDS - Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS]);
										if(Job_Truck2_LoadPoints[load_point_index][ptruck_GATE] && Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OBJECTID] != INVALID_STREAMER_ID)
										MoveDynamicObject(Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OBJECTID], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][0], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][1], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][2], 3.0, Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][3], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][4], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][5]);
									}
								}
								else
								{
									if(Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING])
									{
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] = 0;
										HidePlayerAuxTextDraw(playerid);
									}
								}
							}
							else
							{
								Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
								Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] = 0;
								HidePlayerAuxTextDraw(playerid);
							}
						}
					}
				}
			}
			else
			{
				if(player_state == PLAYER_STATE_DRIVER)
				{
					//check load point
					if(VehicleInfo[pVehicleIndex[playerid]][vinfo_TYPE] == VEHICLE_TYPE_JOB && VehicleInfo[pVehicleIndex[playerid]][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_2 && Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_DRIVER_ID] == 0)
					{
						if(Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_TRAILER_INDEX] == INVALID_VEHICLE_INDEX)
						{
							new trailerid = GetVehicleTrailer(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID]);
							if(trailerid != 0)
							{
								new trailer_index = GetVehicleIndexByVehicleid(trailerid);
								if(trailer_index != INVALID_VEHICLE_INDEX)
								{
									if(VehicleInfo[trailer_index][vinfo_TYPE] == VEHICLE_TYPE_JOB && VehicleInfo[trailer_index][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_2)
									{
										pTruckCancelSeconds[playerid] = TRUCK_CANCEL_SECONDS;
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_TRAILER_INDEX] = trailer_index;
										if(Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] == -1)
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] = random(sizeof Job_Truck2_LoadPoints);
										//Route a Load Point
										new load_point_index = Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT];
										DestroyPlayerRoute(playerid, 1);
										AddRouteCp(playerid, Job_Truck2_LoadPoints[load_point_index][ptruck_POS][0], Job_Truck2_LoadPoints[load_point_index][ptruck_POS][1], Job_Truck2_LoadPoints[load_point_index][ptruck_POS][2], 5.0);
										StartRoute(playerid);
										Text_Send(playerid, $MESSAGE_WARNING_LOAD_TRUCK);
										Text_Send(playerid, $GAMETEXT_INFO_TRAILER_ATTACHED);
									}
									else DetachTrailerFromVehicle(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID]);
								}
							}
						}
						else
						{
							if(Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_TRAILER_INDEX] != INVALID_VEHICLE_INDEX && GetVehicleTrailer(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID]) != VehicleInfo[Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_TRAILER_INDEX]][vinfo_VEHICLE_ID])
							{
								//tienes x segundos
								pTruckCancelSeconds[playerid] --;
								if(pTruckCancelSeconds[playerid] <= 0)
								{
									stop pTruckTimer[playerid];
									pTruckTimer[playerid] = Timer:-1;
									ResetTruckInfo(pVehicleIndex[playerid], true);
									pTruckCancelSeconds[playerid] = 0;
									HidePlayerInfoMessage(playerid);
									Text_Send(playerid, $MESSAGE_ERROR_TRUCK_CANCELED);
								}
								else PlayerTruckCancelMsg(playerid, pTruckCancelSeconds[playerid], true);
							}
							else
							{
								HidePlayerInfoMessage(playerid);
								new load_point_index = Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT];
								if(GetVehicleDistanceFromPoint(VehicleInfo[ Truck_VehicleInfo[ pVehicleIndex[playerid] ][vtruck_TRAILER_INDEX] ][vinfo_VEHICLE_ID], Job_Truck2_LoadPoints[load_point_index][ptruck_POS][0], Job_Truck2_LoadPoints[load_point_index][ptruck_POS][1], Job_Truck2_LoadPoints[load_point_index][ptruck_POS][2]) <= 8.0)
								{
									new Float:angle;
									GetVehicleZAngle(VehicleInfo[ Truck_VehicleInfo[ pVehicleIndex[playerid] ][vtruck_TRAILER_INDEX] ][vinfo_VEHICLE_ID], angle);
									if( (angle > (Job_Truck2_LoadPoints[load_point_index][ptruck_POS][3] - 20.0)) && (angle < (Job_Truck2_LoadPoints[load_point_index][ptruck_POS][3] + 20.0)) )
									{
										Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] ++;
										if(Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] >= TRUCK2_LOAD_SECONDS)
										{
											pTruckVehicleIndex[playerid] = pVehicleIndex[playerid];
											Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
											Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] = 0;
											Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOAD_POINT] = -1;
											Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_DRIVER_ID] = PI[playerid][pi_ID];
											Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT] = random(sizeof Job_Truck2_UnloadPoints);
											Text_Send(playerid, $MESSAGE_INFO_TRUCK_LOADED);
											HidePlayerAuxTextDraw(playerid);
											VehicleInfo[pVehicleIndex[playerid]][vinfo_PARAMS_ENGINE] = 1;
											SetVehicleParams(pVehicleIndex[playerid]);
											if(Job_Truck2_LoadPoints[load_point_index][ptruck_GATE] && Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OBJECTID] != INVALID_STREAMER_ID)
											MoveDynamicObject(Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OBJECTID], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_POS][0], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_POS][1], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_POS][2], 3.0, Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_POS][3], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_POS][4], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_POS][5]);
											//route
											DestroyPlayerRoute(playerid, 1);
											CalcRoute(playerid, Job_Truck2_UnloadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT] ][ptruck_POS][0], Job_Truck2_UnloadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT] ][ptruck_POS][1], Job_Truck2_UnloadPoints[ Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_UNLOAD_POINT] ][ptruck_POS][2]);
											RepairVehicle(VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID]);
										}
										else
										{
											VehicleInfo[pVehicleIndex[playerid]][vinfo_PARAMS_ENGINE] = 0;
											SetVehicleParams(pVehicleIndex[playerid]);
											PlayerTruckStateAux(playerid, 1000.0, true, false, TRUCK2_LOAD_SECONDS - Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS]);
											if(Job_Truck2_LoadPoints[load_point_index][ptruck_GATE] && Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OBJECTID] != INVALID_STREAMER_ID)
											MoveDynamicObject(Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OBJECTID], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][0], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][1], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][2], 3.0, Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][3], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][4], Job_Truck2_LoadPoints[load_point_index][ptruck_GATE_OPEN_POS][5]);
										}
									}
									else
									{
										if(Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING])
										{
											Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
											Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] = 0;
											HidePlayerAuxTextDraw(playerid);
										}
									}
								}
								else
								{
									Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING] = false;
									Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_LOADING_SECONDS] = 0;
									HidePlayerAuxTextDraw(playerid);
								}
							}
						}
					}
				}
				else
				{
					stop pTruckTimer[playerid];
					pTruckTimer[playerid] = Timer:-1;
				}
			}
		}
	}
	return 1;
}

hook OnPlayerRouteFinish(playerid)
{
	if(GetPlayerJobId(playerid) == JOB_TRUCKER)
	{
		new vehindex = pVehicleIndex[playerid];
		if(pVehicleIndex[playerid] != INVALID_VEHICLE_INDEX && VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_JOB)
		{
			if(VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_1 || VehicleInfo[vehindex][vinfo_ID_JOB_POINT] == JOB_POINT_TRUCKER_2)
			{
				Text_Send(playerid, $MESSAGE_WARNING_TRUCK_POSITION);
			}
		}
	}
	return 1;
}

hook OnPlayerGpsRouteCalc(playerid, bool:gps)
{
	if(GetPlayerJobId(playerid) == JOB_TRUCKER && !gps)
	Truck_VehicleInfo[pVehicleIndex[playerid]][vtruck_JOB_DISTANCE] = GetPlayerRouteDistance(playerid);
	return 1;
}

PlayerTruckCancelMsg(playerid, sec, bool:trailer = false, bool:auxtd = false)
{
	new str[128];
	if(trailer)
	{
		Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXTDRAW_1_CANCEL, sec);
	}
	else
	{
		Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXTDRAW_2_CANCEL, sec);
	}
	
	if(auxtd) ShowPlayerAuxTextDraw(playerid, str);
	else ShowPlayerInfoMessage(playerid, str, 0, false);
	return 1;
}

PlayerTruckStateAux(playerid, Float:health, bool:loading = false, bool:unloading = false, seconds = 0)
{
	new str[128];	
	if(loading)
	{
		Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXTDRAW_1_AUX, seconds);
	}
	else if(unloading)
	{
		Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXTDRAW_2_AUX, seconds);
	}
	else
	{
		if(health >= TRUCK_HEALTH_GOOD)
		{
			Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXTDRAW_3_AUX);
		}
		else if(health >= TRUCK_HEALTH_MODERATE)
		{
			Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXTDRAW_4_AUX);
		}
		else
		{
			Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXTDRAW_5_AUX);
		}
	}
	ShowPlayerAuxTextDraw(playerid, str);
	return 1;
}