#include <YSI\y_hooks>

hook OnScriptInit()
{
	AddSimpleModel(-1, 19379, -1010, "blank.dff", "textdraws/radar.txd");

	new streamer_info[2];
	radarAreaVc = CreateDynamicRectangle(vc_limit_X_WEST, vc_limit_Y_SOUTH, vc_limit_X_EAST, vc_limit_Y_NORTH, -1, 0);
	streamer_info[0] = _:AREA_TYPE_RADAR;
	streamer_info[1] = 0;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, radarAreaVc, E_STREAMER_EXTRA_ID, streamer_info);
	for(new i = 0, j = sizeof radarAreas; i != j; i ++)
	{
		radarAreas[i] = CreateDynamicRectangle(radarAreas_Coords[i][0], radarAreas_Coords[i][1], radarAreas_Coords[i][2], radarAreas_Coords[i][3], -1, 0);
		streamer_info[0] = _:AREA_TYPE_RADAR;
		streamer_info[1] = i + 1;
		Streamer_SetArrayData(STREAMER_TYPE_AREA, radarAreas[i], E_STREAMER_EXTRA_ID, streamer_info);
	}
	return 1;
}