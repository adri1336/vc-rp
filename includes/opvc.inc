/*
	By adri1
*/
#if defined _inc_opvc
	#endinput
#endif
#define _inc_opvc

#include <YSI\y_hooks>

#define INVALID_OPVC_VEHICLE_ID 0

new pPlayerCurrentVehicle[MAX_PLAYERS] = {INVALID_OPVC_VEHICLE_ID, ...};

forward OnPlayerVehicleChange(playerid, from_vehicleid, to_vehicleid);

hook OnPlayerDisconnect(playerid, reason)
{
	pPlayerCurrentVehicle[playerid] = INVALID_OPVC_VEHICLE_ID;
	return 1;
}

hook OnPlayerUpdate(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(vehicleid != pPlayerCurrentVehicle[playerid])
	{
		CallRemoteFunction("OnPlayerVehicleChange", "idd", playerid, pPlayerCurrentVehicle[playerid], vehicleid);
		pPlayerCurrentVehicle[playerid] = vehicleid;
	}
	return 1;
}