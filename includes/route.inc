/*
	By adri1
*/
#if defined _inc_route
	#endinput
#endif
#define _inc_route

#include <YSI\y_hooks>

forward OnPlayerRouteCp(playerid, cp);
forward OnPlayerRouteFinish(playerid);

#define MAX_ROUTE_CHECKPOINTS 100
#define CHECKPOINT_TYPE_ROUTE 100

#define GetPlayerRouteCP(%0) Route[%0][route_PLAYER_CP]
#define GetPlayerRouteTotalCP(%0) Iter_Count(RouteCps[%0])
#define GetPlayerRouteDistance(%0) Route[%0][route_DISTANCE]

enum enum_Route
{
	Float:route_DISTANCE,
	Float:route_DISTANCE_TRAVELED,
	route_PLAYER_CP,
	route_TYPE
};
new Route[MAX_PLAYERS][enum_Route];

enum enum_RouteCps
{
	routecp_CPID,
	Float:routecp_X,
	Float:routecp_Y,
	Float:routecp_Z,
	Float:routecp_ANGLE,
	Float:routecp_SIZE,
	Float:routecp_PREV_CP_DISTANCE,
	Float:routecp_DISTANCE
};
new RouteCps[MAX_PLAYERS][MAX_ROUTE_CHECKPOINTS][enum_RouteCps],
	Iterator:RouteCps[MAX_PLAYERS]<MAX_ROUTE_CHECKPOINTS>;

hook OnScriptInit()
{
	Iter_Init(RouteCps);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	ResetPlayerRoute(playerid);
	return 1;
}

stock Float:Route_GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
	return VectorSize(x1 - x2, y1 - y2, z1 - z2);
}

stock Float:GetPlayerRouteDistanceTraveled(playerid)
{
	new Float:pDistance = Route[playerid][route_DISTANCE_TRAVELED];
	if(GetPlayerRouteCP(playerid) > -1)
	{
		if(pDistance > GetPlayerRouteDistance(playerid)) pDistance = GetPlayerRouteDistance(playerid);
		else
		{
			new next_cp = Iter_Next(RouteCps[playerid], GetPlayerRouteCP(playerid));
			if(next_cp == Iter_End(RouteCps[playerid])) pDistance = GetPlayerRouteDistance(playerid);
			else
			{
				new Float:tdis = RouteCps[playerid][next_cp][routecp_PREV_CP_DISTANCE] - GetPlayerDistanceFromPoint(playerid, RouteCps[playerid][next_cp][routecp_X], RouteCps[playerid][next_cp][routecp_Y], RouteCps[playerid][next_cp][routecp_Z]);
				pDistance += tdis;
				if(pDistance < 0.0) pDistance = 0.0;
			}
		}
	}
	else pDistance = 0.0;
	return pDistance;
}

stock Float:GetPlayerRoutePercentage(playerid)
{
	new Float:percentage,
		Float:pDistance = GetPlayerRouteDistanceTraveled(playerid);

	percentage = floatdiv(floatmul(pDistance, 100.0), GetPlayerRouteDistance(playerid));
	return percentage;
}

stock Float:GetAngleBetweenPoints(Float:x1, Float:y1, Float:x2, Float:y2) //By Babul
{
	new Float:angle = 90.0 + (atan2(y1 - y2, x1 - x2));
	//new Float:angle = atan2(y1 - y2, x1 - x2) * 180.0 / 3.141592653;
	return angle;
}

stock AddRouteCp(playerid, Float:x, Float:y, Float:z, Float:size = 5.0)
{
	new slot = Iter_Free(RouteCps[playerid]);
	if(slot != cellmin)
	{
		RouteCps[playerid][slot][routecp_CPID] = INVALID_STREAMER_ID;
		RouteCps[playerid][slot][routecp_X] = x;
		RouteCps[playerid][slot][routecp_Y] = y;
		RouteCps[playerid][slot][routecp_Z] = z;
		RouteCps[playerid][slot][routecp_ANGLE] = 0.0;
		RouteCps[playerid][slot][routecp_SIZE] = size;
		Iter_Add(RouteCps[playerid], slot);

		//Contar distancia
		new prev_slot = Iter_Prev(RouteCps[playerid], slot);
		if(prev_slot != Iter_Begin(RouteCps[playerid]))
		{
			RouteCps[playerid][prev_slot][routecp_ANGLE] = GetAngleBetweenPoints(RouteCps[playerid][prev_slot][routecp_X], RouteCps[playerid][prev_slot][routecp_Y], RouteCps[playerid][slot][routecp_X], RouteCps[playerid][slot][routecp_Y]);
			RouteCps[playerid][slot][routecp_PREV_CP_DISTANCE] = Route_GetDistanceBetweenPoints(x, y, z, RouteCps[playerid][prev_slot][routecp_X], RouteCps[playerid][prev_slot][routecp_Y], RouteCps[playerid][prev_slot][routecp_Z]);
			Route[playerid][route_DISTANCE] += RouteCps[playerid][slot][routecp_PREV_CP_DISTANCE];
			RouteCps[playerid][slot][routecp_DISTANCE] = Route[playerid][route_DISTANCE];
		}
		return 1;
	}
	return 0;
}

hook OnPlayerEnterDynRaceCP(playerid, checkpointid)
{
	new array_info[2];
	Streamer_GetArrayData(STREAMER_TYPE_RACE_CP, checkpointid, E_STREAMER_EXTRA_ID, array_info);
	if(array_info[0] == CHECKPOINT_TYPE_ROUTE)
	{
		Route[playerid][route_PLAYER_CP] = array_info[1];
		DestroyDynamicRaceCP(RouteCps[playerid][array_info[1]][routecp_CPID]);
		PlayerPlaySound(playerid, 1138, 0.0, 0.0, 0.0);

		if(array_info[1] == Iter_Last(RouteCps[playerid]))
		{
			Route[playerid][route_DISTANCE_TRAVELED] = GetPlayerRouteDistance(playerid);
			DestroyPlayerRouteCps(playerid);
			CallRemoteFunction("OnPlayerRouteFinish", "i", playerid);
		}
		else
		{
			Route[playerid][route_DISTANCE_TRAVELED] = RouteCps[playerid][array_info[1]][routecp_DISTANCE];
			SetPlayerRouteCps(playerid);
			CallRemoteFunction("OnPlayerRouteCp", "id", playerid, array_info[1]);
		}
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return 1;
}

SetPlayerRouteCps(playerid)
{
	new cp;
	if(GetPlayerRouteCP(playerid) == -1) cp = Iter_First(RouteCps[playerid]);
	else cp = Iter_Next(RouteCps[playerid], GetPlayerRouteCP(playerid));

	if(cp != Iter_End(RouteCps[playerid]))
	{
		if(Route[playerid][route_TYPE])
		{
			DestroyPlayerRouteCps(playerid);
			//for(new i = cp; i <= Iter_Last(RouteCps[playerid]); i = Iter_Next(RouteCps[playerid], i))
			for(new i = cp; i != Iter_End(RouteCps[playerid]); i = Iter_Next(RouteCps[playerid], i))
			{
				if(i == Iter_Last(RouteCps[playerid]))
				{
					RouteCps[playerid][i][routecp_CPID] = CreateDynamicRaceCP(1, RouteCps[playerid][i][routecp_X], RouteCps[playerid][i][routecp_Y], RouteCps[playerid][i][routecp_Z], 0.0, 0.0, 0.0, RouteCps[playerid][i][routecp_SIZE], .playerid = playerid, .streamdistance = 5000);
					SetRouteCpInfo(RouteCps[playerid][i][routecp_CPID], i);
				}
				else
				{
					new next_cp = Iter_Next(RouteCps[playerid], i);
					RouteCps[playerid][i][routecp_CPID] = CreateDynamicRaceCP(0, RouteCps[playerid][i][routecp_X], RouteCps[playerid][i][routecp_Y], RouteCps[playerid][i][routecp_Z], RouteCps[playerid][next_cp][routecp_X], RouteCps[playerid][next_cp][routecp_Y], RouteCps[playerid][next_cp][routecp_Z], RouteCps[playerid][i][routecp_SIZE], .playerid = playerid, .streamdistance = 5000);
					SetRouteCpInfo(RouteCps[playerid][i][routecp_CPID], i);
				}
			}
		}
		else
		{
			DestroyPlayerRouteCps(playerid);
			if(cp == Iter_Last(RouteCps[playerid]))
			{
				RouteCps[playerid][cp][routecp_CPID] = CreateDynamicRaceCP(1, RouteCps[playerid][cp][routecp_X], RouteCps[playerid][cp][routecp_Y], RouteCps[playerid][cp][routecp_Z], 0.0, 0.0, 0.0, RouteCps[playerid][cp][routecp_SIZE], .playerid = playerid, .streamdistance = 5000);
				SetRouteCpInfo(RouteCps[playerid][cp][routecp_CPID], cp);
			}
			else
			{
				new next_cp = Iter_Next(RouteCps[playerid], cp);
				RouteCps[playerid][cp][routecp_CPID] = CreateDynamicRaceCP(0, RouteCps[playerid][cp][routecp_X], RouteCps[playerid][cp][routecp_Y], RouteCps[playerid][cp][routecp_Z], RouteCps[playerid][next_cp][routecp_X], RouteCps[playerid][next_cp][routecp_Y], RouteCps[playerid][next_cp][routecp_Z], RouteCps[playerid][cp][routecp_SIZE], .playerid = playerid, .streamdistance = 5000);
				SetRouteCpInfo(RouteCps[playerid][cp][routecp_CPID], cp);
			}
		}
	}
	return 1;
}

DestroyPlayerRouteCps(playerid)
{
	foreach(new i : RouteCps[playerid])
	{
		if(RouteCps[playerid][i][routecp_CPID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicRaceCP(RouteCps[playerid][i][routecp_CPID]);
			RouteCps[playerid][i][routecp_CPID] = INVALID_STREAMER_ID;
		}
	}
	return 1;
}

ResetPlayerRoute(playerid, type = 0)
{
	DestroyPlayerRouteCps(playerid);
	Iter_Clear(RouteCps[playerid]);

	new tmp_Route[enum_Route];
	Route[playerid] = tmp_Route;
	Route[playerid][route_TYPE] = type;
	Route[playerid][route_PLAYER_CP] = -1;
	return 1;
}

SetRouteCpInfo(checkpointid, slot)
{
	new array_info[2];
	array_info[0] = CHECKPOINT_TYPE_ROUTE;
	array_info[1] = slot;
	Streamer_SetArrayData(STREAMER_TYPE_RACE_CP, checkpointid, E_STREAMER_EXTRA_ID, array_info);
	return 1;
}

CopyPlayerRouteFromPlayer(playerid, from_playerid)
{
	ResetPlayerRoute(playerid, Route[from_playerid][route_TYPE]);
	foreach(new i : RouteCps[from_playerid])
	{
		AddRouteCp(playerid, RouteCps[from_playerid][i][routecp_X], RouteCps[from_playerid][i][routecp_Y], RouteCps[from_playerid][i][routecp_Z], RouteCps[from_playerid][i][routecp_SIZE]);
	}
	return 1;
}