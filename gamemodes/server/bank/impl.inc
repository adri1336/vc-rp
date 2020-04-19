#include <YSI\y_hooks>

hook OnScriptInit()
{
	for(new i = 0; i != sizeof BankPoints; i ++)
	{
		new objid = CreateDynamicObject(CUSTOM_PICKUP_MODELID, BankPoints[i][0], BankPoints[i][1], BankPoints[i][2], 0.0, 0.0, 0.0);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objid, E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_PICKUP_BANK_POINT);

		new tmpareaid = CreateDynamicCylinder(BankPoints[i][0], BankPoints[i][1], BankPoints[i][2] - 1.0, BankPoints[i][2] + 3.0, 2.0);
		Streamer_SetIntData(STREAMER_TYPE_AREA, tmpareaid, E_STREAMER_EXTRA_ID, _:AREA_TYPE_BANK);
	}
	return 1;
}