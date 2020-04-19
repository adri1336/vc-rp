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
		case AREA_TYPE_ENTRANCE: FormatEntranceMessage(playerid, streamer_info[1]);
		case AREA_TYPE_INT_ENTRANCE: FormatIntEntranceMessage(playerid);
		case AREA_TYPE_HOSPITAL_BED: if(!Hospital_Beds[streamer_info[1]][hbed_IN_USE]) FormatPlayerHospitalBedMsg(playerid);
		case AREA_TYPE_ATM: FormatAtmMessage(playerid);
		case AREA_TYPE_BANK: FormatBankPointMessage(playerid);
		case AREA_TYPE_SALE_VEHS: FormatSaleVehsMessage(playerid);
		case AREA_TYPE_GAS_STATION:
		{
			if(GetPlayerVehicleIndex(playerid) != INVALID_VEHICLE_INDEX && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				if(VehicleModelHasEngine(VehicleInfo[GetPlayerVehicleIndex(playerid)][vinfo_MODELID])) FormatGasStationMessage(playerid);
			}
		}
		case AREA_TYPE_DRIVING_SCHOOL: FormatDrivingSchoolMessage(playerid);
		case AREA_TYPE_EXT_PROPERTY_DOOR: FormatPropertyDoorMessage(playerid);
		case AREA_TYPE_INT_PROPERTY_DOOR: FormatIntEntranceMessage(playerid); //msg salir
		case AREA_TYPE_BSALE_POINT:
		{
			if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_BUSINESS)
			FormatBSalePointMsg(playerid);
		}
		case AREA_TYPE_BDOOR_EXT: FormatBusinessMessage(playerid, streamer_info[1]);
		case AREA_TYPE_BDOOR_INT: FormatIntEntranceMessage(playerid); //msg salir
		case AREA_TYPE_JOB_POINT: FormatJobPointMessage(playerid, streamer_info[1], streamer_info[2]);
		case AREA_TYPE_INTEREST_POINT: FormatInterestPointMessage(playerid);
		case AREA_TYPE_GUNSMITH: FormatGunSmithPointMessage(playerid);
		case AREA_TYPE_GUN_LICENSE: FormatGunLicenseMessage(playerid);
		case AREA_TYPE_REAL_ESTATE: FormatActionMessage(playerid);
		case AREA_TYPE_CARWORKSHOP: if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) FormatActionMessage(playerid);
		case AREA_TYPE_ENV_AREA: if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) FormatEnvAreaMessage(playerid, streamer_info[1]);
		case AREA_TYPE_PLAY_BOOMBOX:
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && !isnull(Boombox[streamer_info[1]][boombox_URL]))
			{
				FormatEnvAreaMessage(playerid, ENV_AREA_TYPE_DANCE);
			}
		}
		case AREA_TYPE_BOOMBOX:
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && Boombox[streamer_info[1]][boombox_ACCOUNT_ID] == PI[playerid][pi_ID])
			FormatBoomboxAreaMessage(playerid);
		}
		case AREA_TYPE_VINV:
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && HasPlayerAccessToVehicle(playerid, streamer_info[1]))
			{
				if(Vehicle_Speed(VehicleInfo[streamer_info[1]][vinfo_VEHICLE_ID]) <= 1.0)
				FormatVinvAreaMessage(playerid);
			}
		}
	}
	return 1;
}