GetZoneName(zone)
{
	new name[32] = ""SERVER_MAPNAME"";
	if(zone != INVALID_ZONE_ID) format(name, sizeof name, "%s", g_Zones[zone][eZone_NAME]);
	return name;
}

/*GetPointZoneName(Float:x, Float:y, Float:z)
{
	new name[32] = ""SERVER_MAPNAME"";
	for(new i = 0, j = sizeof g_Zones; i != j; i ++)
	{
		if(IsPointInDynamicArea(g_Zones[i][eZone_AREAID], x, y, z))
		{
			format(name, sizeof name, "%s", g_Zones[i][eZone_NAME]);
			break;
		}
	}
	return name;
}*/