#include <YSI\y_hooks>

hook OnEntrancesLoad()
{
	for(new i = 0; i != sizeof Hospital_Beds; i ++)
	{
		new entrance_index = GetEntranceIndexByEntranceId(Hospital_Beds[i][hbed_ID_ENTRANCE]);
		if(entrance_index != -1)
		{
			new tmpobjid = CreateDynamicObject(1771, Hospital_Beds[i][hbed_X], Hospital_Beds[i][hbed_Y], Hospital_Beds[i][hbed_Z], 0.0, 0.0, Hospital_Beds[i][hbed_RZ], Entrances[entrance_index][entrance_ID_ENTRANCE], Interiors[Entrances[entrance_index][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
			SetDynamicObjectMaterial(tmpobjid, 0, 14665, "genintint711_1", "interiorwindowglow", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 1, 1560, "7_11_door", "CJ_CHROME2", 0x00000000);

			new streamer_info[2];
			new tmp_areaid = CreateDynamicCylinder(Hospital_Beds[i][hbed_X], Hospital_Beds[i][hbed_Y], Hospital_Beds[i][hbed_Z] - 1.0, Hospital_Beds[i][hbed_Z] + 3.0, 2.0, Entrances[entrance_index][entrance_ID_ENTRANCE], Interiors[Entrances[entrance_index][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
			streamer_info[0] = _:AREA_TYPE_HOSPITAL_BED;
			streamer_info[1] = i;
			Streamer_SetArrayData(STREAMER_TYPE_AREA, tmp_areaid, E_STREAMER_EXTRA_ID, streamer_info);
		}
	}
	return 1;
}

hook OnEntranceLoad(index)
{
	if(strfind(Entrances[index][entrance_NAME], "hospital", true) != -1)
	{
		new slot = Iter_Free(HospitalsEntrances);
		if(slot == cellmin)
		{
			printf("[ERROR]: Límite superado en 'OnEntranceLoad', 'HospitalsEntrances', max: %d", MAX_HOSPITALS);
			return 0;
		}

		HospitalsEntrances[slot] = index;
		Iter_Add(HospitalsEntrances, slot);
	}
	return 1;
}