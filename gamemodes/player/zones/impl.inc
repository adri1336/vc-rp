#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
	pCurrentZone[playerid] = INVALID_ZONE_ID;
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	new newzone = GetPlayerZoneId(playerid);
	CallRemoteFunction("OnPlayerZoneChange", "idd", playerid, pCurrentZone[playerid], newzone);
	pCurrentZone[playerid] = newzone;
	return 1;
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{
	if(GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == VC_WORLD)
	{
		new streamer_info[2];
		Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);
		if(streamer_info[0] == _:AREA_TYPE_ZONE)
		{
			new newzone = GetPlayerZoneId(playerid);
			CallRemoteFunction("OnPlayerZoneChange", "idd", playerid, pCurrentZone[playerid], newzone);
			pCurrentZone[playerid] = newzone;
		}
	}
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	if((pCurrentZone[playerid] == INVALID_ZONE_ID || g_Zones[ pCurrentZone[playerid] ][eZone_AREAID] != areaid) && GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == VC_WORLD)
	{
		new streamer_info[2];
		Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);
		if(streamer_info[0] == _:AREA_TYPE_ZONE)
		{
			new newzone = GetPlayerZoneId(playerid);
			CallRemoteFunction("OnPlayerZoneChange", "idd", playerid, pCurrentZone[playerid], newzone);
			pCurrentZone[playerid] = newzone;
		}
	}
	return 1;
}