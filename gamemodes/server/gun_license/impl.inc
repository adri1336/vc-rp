#include <YSI\y_hooks>

hook OnScriptInit()
{
	for(new i = 0; i < sizeof Get_Gunlicense_Points; i ++)
	{
		new objid = CreateDynamicObject(CUSTOM_PICKUP_MODELID, Get_Gunlicense_Points[i][0], Get_Gunlicense_Points[i][1], Get_Gunlicense_Points[i][2], 0.0, 0.0, 0.0);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objid, E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_PICKUP_GUN_LICENSE);

		new tmpareaid = CreateDynamicCylinder(Get_Gunlicense_Points[i][0], Get_Gunlicense_Points[i][1], Get_Gunlicense_Points[i][2] - 1.0, Get_Gunlicense_Points[i][2] + 3.0, 2.0);
		Streamer_SetIntData(STREAMER_TYPE_AREA, tmpareaid, E_STREAMER_EXTRA_ID, _:AREA_TYPE_GUN_LICENSE);
	}
	return 1;
}