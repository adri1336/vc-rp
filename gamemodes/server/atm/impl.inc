#include <YSI\y_hooks>

hook OnScriptInit()
{
	for(new i = 0; i != sizeof AtmInfo; i ++)
	{
		new tmpobjid = CreateDynamicObject(2942, AtmInfo[i][atm_X], AtmInfo[i][atm_Y], AtmInfo[i][atm_Z], 0.0, 0.0, AtmInfo[i][atm_RZ]);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, tmpobjid, E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_ATM);
		
		AtmInfo[i][atm_X] += (-0.5 * floatsin(-(AtmInfo[i][atm_RZ] - 90.0), degrees));
		AtmInfo[i][atm_Y] += (-0.5 * floatcos(-(AtmInfo[i][atm_RZ] - 90.0), degrees));
		new tmpareaid = CreateDynamicCylinder(AtmInfo[i][atm_X], AtmInfo[i][atm_Y], AtmInfo[i][atm_Z] - 1.0, AtmInfo[i][atm_Z] + 3.0, 2.0);
		Streamer_SetIntData(STREAMER_TYPE_AREA, tmpareaid, E_STREAMER_EXTRA_ID, _:AREA_TYPE_ATM);
	}
	return 1;
}