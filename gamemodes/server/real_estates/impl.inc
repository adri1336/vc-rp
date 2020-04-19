#include <YSI\y_hooks>

hook OnScriptInit()
{
	for(new i = 0; i < sizeof Real_State_Points; i ++)
	{
		new objid = CreateDynamicObject(CUSTOM_PICKUP_MODELID, Real_State_Points[i][0], Real_State_Points[i][1], Real_State_Points[i][2], 0.0, 0.0, 0.0);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objid, E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_PICKUP_REAL_ESTATE);

		new tmpareaid = CreateDynamicCylinder(Real_State_Points[i][0], Real_State_Points[i][1], Real_State_Points[i][2] - 1.0, Real_State_Points[i][2] + 3.0, 2.0);
		Streamer_SetIntData(STREAMER_TYPE_AREA, tmpareaid, E_STREAMER_EXTRA_ID, _:AREA_TYPE_REAL_ESTATE);
	}
	return 1;
}