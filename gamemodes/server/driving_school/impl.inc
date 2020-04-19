#include <YSI\y_hooks>

hook OnScriptInit()
{
	new objid = CreateDynamicObject(CUSTOM_PICKUP_MODELID, Driving_School_Pos[0], Driving_School_Pos[1], Driving_School_Pos[2], 0.0, 0.0, 0.0);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objid, E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_PICKUP_DRIVING_SL);

	new tmpareaid = CreateDynamicCylinder(Driving_School_Pos[0], Driving_School_Pos[1], Driving_School_Pos[2] - 1.0, Driving_School_Pos[2] + 3.0, 2.0);
	Streamer_SetIntData(STREAMER_TYPE_AREA, tmpareaid, E_STREAMER_EXTRA_ID, _:AREA_TYPE_DRIVING_SCHOOL);
	return 1;
}