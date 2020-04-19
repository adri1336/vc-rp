GetPlayerZoneName(playerid)
{
	new name[32] = ""SERVER_MAPNAME"";
	if(pCurrentZone[playerid] != INVALID_ZONE_ID)
	{
		format(name, sizeof name, "%s", g_Zones[pCurrentZone[playerid]][eZone_NAME]);
	}
	return name;
}

GetPlayerZoneId(playerid)
{
	new Float:pos[3], Float:angle, interiorid, worldid;
	GetPlayerExteriorPos(playerid, pos[0], pos[1], pos[2], angle, interiorid, worldid);
	for(new i = 0; i < sizeof g_Zones; i ++)
	{
		if(IsPointInDynamicArea(g_Zones[i][eZone_AREAID], pos[0], pos[1], pos[2]))
		{
			return i;
		}
	}
	return INVALID_ZONE_ID;
}