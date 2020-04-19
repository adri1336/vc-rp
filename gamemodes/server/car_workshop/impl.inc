#include <YSI\y_hooks>

hook OnScriptInit()
{
	new streamer_info[2], areaid;
	for(new i = 0; i < sizeof Car_Workshop_Points; i ++)
	{
		areaid = CreateDynamicCylinder(Car_Workshop_Points[i][0], Car_Workshop_Points[i][1], Car_Workshop_Points[i][2] - PLAYER_LABEL_DISTANCE, Car_Workshop_Points[i][2] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE);
		streamer_info[0] = _:AREA_TYPE_LABEL_CARWORKSHOP;
		streamer_info[1] = i;
		Streamer_SetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);

		areaid = CreateDynamicCylinder(Car_Workshop_Points[i][0], Car_Workshop_Points[i][1], Car_Workshop_Points[i][2] - 1.0, Car_Workshop_Points[i][2] + 3.0, 1.0);
		streamer_info[0] = _:AREA_TYPE_CARWORKSHOP;
		streamer_info[1] = i;
		Streamer_SetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);
	}
	return 1;
}