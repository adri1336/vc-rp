#include <YSI\y_hooks>

hook OnScriptInit()
{
	new streamer_info[2];
	for(new i = 0, j = sizeof g_Zones; i != j; i ++)
	{
		g_Zones[i][eZone_MINX] += 6000.0;
		g_Zones[i][eZone_MAXX] += 6000.0;
		
		g_Zones[i][eZone_MINY] += 1100.0;
		g_Zones[i][eZone_MAXY] += 1100.0;

		g_Zones[i][eZone_AREAID] = CreateDynamicRectangle(g_Zones[i][eZone_MINX], g_Zones[i][eZone_MINY], g_Zones[i][eZone_MAXX], g_Zones[i][eZone_MAXY], VC_WORLD, 0);
		streamer_info[0] = _:AREA_TYPE_ZONE;
		streamer_info[1] = i;
		Streamer_SetArrayData(STREAMER_TYPE_AREA, g_Zones[i][eZone_AREAID], E_STREAMER_EXTRA_ID, streamer_info);
	}
	return 1;
}