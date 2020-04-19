#include <YSI\y_hooks>

hook OnScriptInit()
{
	for(new i = 0, j = sizeof Fuel_Stations; i != j; i++)
	{
		new objid = CreateDynamicObject(CUSTOM_PICKUP_MODELID, Fuel_Stations[i][0], Fuel_Stations[i][1], Fuel_Stations[i][2], 0.0, 0.0, 0.0);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objid, E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_PICKUP_GAS_STATION);

		new tmpareaid = CreateDynamicCylinder(Fuel_Stations[i][0], Fuel_Stations[i][1], Fuel_Stations[i][2] - 2.0, Fuel_Stations[i][2] + 5.0, 3.0, 0, 0);
		Streamer_SetIntData(STREAMER_TYPE_AREA, tmpareaid, E_STREAMER_EXTRA_ID, _:AREA_TYPE_GAS_STATION);
	}
	return 1;
}