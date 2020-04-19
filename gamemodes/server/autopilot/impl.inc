#include <YSI\y_hooks>

hook OnVehicleLoaded(vehindex)
{
	if(VehicleInfo[vehindex][vinfo_TYPE] == VEHICLE_TYPE_AUTOPILOT)
	{
		new vehicleid = VehicleInfo[vehindex][vinfo_VEHICLE_ID];
		ApVehicleInfo[vehicleid][apv_Timer] = Timer:-1;
		ApVehicleInfo[vehicleid][apv_DestroyTimer] = Timer:-1;
		ApVehicleInfo[vehicleid][apv_CreatedBy] = INVALID_PLAYER_ID;
		ApVehicleInfo[vehicleid][apv_PathId] = Path:INVALID_PATH_ID;
		ApVehicleInfo[vehicleid][apv_VehIndex] = vehindex;
		
		//fake driver
		ApVehicleInfo[vehicleid][apv_FakeDriver] = CreateDynamicObject(FAKE_DRIVER_MODELID, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, ApVehicleInfo[vehicleid][apv_FakeDriver], E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_FAKE_DRIVER);

		new Float:x, Float:y, Float:z;
		GetVehicleModelInfo(VehicleInfo[vehindex][vinfo_MODELID], VEHICLE_MODEL_INFO_FRONTSEAT, x, y, z);
		AttachDynamicObjectToVehicle(ApVehicleInfo[vehicleid][apv_FakeDriver], vehicleid, -x, y, z, 0.0, 0.0, 0.0);

		//taximeter
		if(VehicleInfo[vehindex][vinfo_MODELID] == 420 || VehicleInfo[vehindex][vinfo_MODELID] == 438)
		{
			ApVehicleInfo[vehicleid][apv_Taximeter] = true;
		}
		Iter_Add(ApVehicleInfo, vehicleid);
	}
	return 1;
}

hook OnUnoccupiedVehicleUpd(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	if(Iter_Contains(ApVehicleInfo, vehicleid))
	{
		if(!ApVehicleInfo[vehicleid][apv_InPath] || ApVehicleInfo[vehicleid][apv_Paused])
		{
			RepairVehicle(vehicleid);
			SetVehicleHealth(vehicleid, 1000.0);
			SetVehicleVelocity(vehicleid, 0.0, 0.0, 0.0);
			return Y_HOOKS_BREAK_RETURN_0;
		}
	}
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehicleDestroyedEx(vehindex, vehicleid)
{
	if(Iter_Contains(ApVehicleInfo, vehicleid))
	{
		DestroyAutoPilotVehicleInfo(vehicleid);
	}
	return 1;
}

public OnAutopilotPathCalculated(Path:pathid, vehicleid)
{
	if(!IsValidPath(pathid))
	{
		DestroyPath(pathid);
		CallRemoteFunction("OnAutopilotPathFailed", "ii", ApVehicleInfo[vehicleid][apv_Passenger], vehicleid);
		return 1;
	}

	GetPathSize(pathid, ApVehicleInfo[vehicleid][apv_PathSize]);
	if(ApVehicleInfo[vehicleid][apv_PathSize] <= 3)
	{
		DestroyPath(pathid);
		CallRemoteFunction("OnAutopilotPathFailed", "ii", ApVehicleInfo[vehicleid][apv_Passenger], vehicleid);
		return 1;
	}

	ApVehicleInfo[vehicleid][apv_PathId] = pathid;
	ApVehicleInfo[vehicleid][apv_CurrentPathIndex] = 0;
	ApVehicleInfo[vehicleid][apv_CurrSpeed] = 0.0;
	UpdateAutopilotGoCoords(vehicleid);
	ApVehicleInfo[vehicleid][apv_Timer] = repeat OnAutopilotUpdate(vehicleid);
	return 1;
}

timer OnAutopilotUpdate[100](vehicleid)
{
	if(GetVehicleDistanceFromPoint(vehicleid, ApVehicleInfo[vehicleid][apv_GoX], ApVehicleInfo[vehicleid][apv_GoY], ApVehicleInfo[vehicleid][apv_GoZ]) <= 5.0)
	{
		ApVehicleInfo[vehicleid][apv_CurrentPathIndex] ++;
		if(ApVehicleInfo[vehicleid][apv_CurrentPathIndex] >= ApVehicleInfo[vehicleid][apv_PathSize])
		{
			if(Vehicle_Speed(vehicleid) <= 1.0)
			{
				stop ApVehicleInfo[vehicleid][apv_Timer];
				ApVehicleInfo[vehicleid][apv_Timer] = Timer:-1;
				ApVehicleInfo[vehicleid][apv_InPath] = false;
				ApVehicleInfo[vehicleid][apv_DestroyTimer] = defer OnAutopilotRequestDestroy(vehicleid);
				
				SetVehicleVelocity(vehicleid, 0.0, 0.0, 0.0);
				DestroyPath(ApVehicleInfo[vehicleid][apv_PathId]);
				CallRemoteFunction("OnAutopilotCompleted", "ii", ApVehicleInfo[vehicleid][apv_Passenger], vehicleid);
			}
		}
		else UpdateAutopilotGoCoords(vehicleid);
	}
	RepairVehicle(vehicleid);
	SetVehicleHealth(vehicleid, 1000.0);

	if(ApVehicleInfo[vehicleid][apv_SpeedLimit] > ApVehicleInfo[vehicleid][apv_CurrSpeed]) ApVehicleInfo[vehicleid][apv_CurrSpeed] += 0.01;
	else if(ApVehicleInfo[vehicleid][apv_SpeedLimit] < ApVehicleInfo[vehicleid][apv_CurrSpeed]) ApVehicleInfo[vehicleid][apv_CurrSpeed] -= 0.01;
	
	PullVehicleIntoDirection(vehicleid, ApVehicleInfo[vehicleid][apv_GoX], ApVehicleInfo[vehicleid][apv_GoY], ApVehicleInfo[vehicleid][apv_GoZ], ApVehicleInfo[vehicleid][apv_CurrSpeed]);
}

timer OnAutopilotRequestDestroy[10000](vehicleid)
{
	if(!ApVehicleInfo[vehicleid][apv_InPath]) DestroyAutoPilotVehicle(vehicleid);
	else ApVehicleInfo[vehicleid][apv_DestroyTimer] = Timer:-1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(vehicleid != 0)
		{
			if(Iter_Contains(ApVehicleInfo, vehicleid))
			{
				new Float:x, Float:y, Float:z;
				GetPlayerPos(playerid, x, y, z);
				RemovePlayerFromVehicle(playerid);
				SetPlayerPos(playerid, x, y, z + 1.5);
			}
		}
	}
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
		if(Iter_Contains(ApVehicleInfo, vehicleid))
		{
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
			RemovePlayerFromVehicle(playerid);
			SetPlayerPos(playerid, x, y, z);
		}
	}
	return 1;	
}

public OnAutopilotPathFailed(forplayerid, vehicleid)
{
	DestroyAutoPilotVehicle(vehicleid);
	return 1;
}