#include <YSI\y_hooks>

hook OnScriptInit()
{
	Iter_Init(PlayerLabels);
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	new streamer_info[3];
	Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);

	switch(streamer_info[0])
	{
		case AREA_TYPE_LABEL_ENTRANCE: FormatEntranceLabel(playerid, streamer_info[1]);
		case AREA_TYPE_LABEL_INT_ENTRANCE: FormatIntEntranceLabel(playerid, streamer_info[1]);
		case AREA_TYPE_LABEL_EXT_PROP_DOOR: if(streamer_info[2] == 0) {FormatPropertyDoorLabel(playerid, streamer_info[1], streamer_info[2]);}
		case AREA_TYPE_LABEL_INT_PROP_DOOR: FormatIntPropertyDoorLabel(playerid, streamer_info[1], streamer_info[2]);
		case AREA_TYPE_LABEL_RENT_VEHICLE:
		{
			if(!VehicleInfo[streamer_info[1]][vinfo_ID_PLAYER])
			FormatRentVehicleLabel(playerid, streamer_info[1]);
		}
		case AREA_TYPE_LABEL_SALE_OLD_VEH: FormatUsedVehicleLabel(playerid, streamer_info[1]);
		case AREA_TYPE_LABEL_BSALE_POINT:
		{
			if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_BUSINESS)
			FormatBSalePointLabel(playerid, streamer_info[1]);
		}
		case AREA_TYPE_LABEL_BDOOR_INT: FormatIntBusinessDoorLabel(playerid, streamer_info[1], streamer_info[2]);
		case AREA_TYPE_LABEL_BDOOR_EXT: if(streamer_info[2] == 0) {FormatBusinessDoorLabel(playerid, streamer_info[1], streamer_info[2]);}
		case AREA_TYPE_LABEL_JOB_POINT: FormatJobPointLabel(playerid, streamer_info[1], streamer_info[2]);
		case AREA_TYPE_LABEL_INTEREST_POINT: FormatInterestPointsLabel(playerid, streamer_info[1]);
		case AREA_TYPE_LABEL_CARWORKSHOP: FormatCarWorkShopLabel(playerid, streamer_info[1]);
		case AREA_TYPE_LABEL_BOOMBOX: FormatBoomboxLabel(playerid, streamer_info[1]);
	}
	return 1;
}