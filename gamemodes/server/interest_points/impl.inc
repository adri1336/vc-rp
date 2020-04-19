#include <YSI\y_hooks>

hook OnScriptInit()
{
	new streamer_info[2], areaid;
	for(new i = 0; i < sizeof Interest_Points; i ++)
	{
		areaid = CreateDynamicCylinder(Interest_Points[i][0], Interest_Points[i][1], Interest_Points[i][2] - PLAYER_LABEL_DISTANCE, Interest_Points[i][2] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE);
		streamer_info[0] = _:AREA_TYPE_LABEL_INTEREST_POINT;
		streamer_info[1] = i;
		Streamer_SetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);

		areaid = CreateDynamicCylinder(Interest_Points[i][0], Interest_Points[i][1], Interest_Points[i][2] - 1.0, Interest_Points[i][2] + 3.0, 1.0);
		streamer_info[0] = _:AREA_TYPE_INTEREST_POINT;
		streamer_info[1] = i;
		Streamer_SetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);

		areaid = CreateDynamicObject(CUSTOM_PICKUP_MODELID, Interest_Points[i][0], Interest_Points[i][1], Interest_Points[i][2], 0.0, 0.0, 0.0, .streamdistance = PICKUP_DISTANCE, .drawdistance = PICKUP_DISTANCE, .priority = 10);	
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, areaid, E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_PICKUP_IPOINT);
	}
	return 1;
}