loadtext lang[infomsg_render];

FormatEntranceMessage(playerid, index)
{
	new msg[256];
    if(Entrances[index][entrance_TIME_OPEN] == 0 && Entrances[index][entrance_TIME_CLOSE] == 0) Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_ENTRANCE_1_MSG, ACTION_KEY_STR);
    else Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_ENTRANCE_2_MSG, Entrances[index][entrance_TIME_OPEN], Entrances[index][entrance_TIME_CLOSE], ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatIntEntranceMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_INTERIOR_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatAtmMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_ATM_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatPlayerHospitalBedMsg(playerid)
{
	new msg[256];
	Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_HOSPITAL_BED_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatBankPointMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_BANK_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatSaleVehsMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_SVEHS_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatGasStationMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_GAS_MSG, ACTION_KEY_STR, FUEL_PRICE_PER_LITRE);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatDrivingSchoolMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_DRIVING_SCHOOL_MSG, ACTION_KEY_STR, DRIVER_LICENSE_PRICE);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatPropertyDoorMessage(playerid)
{
	new msg[256];
	Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_PROPERTY_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatBSalePointMsg(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_BSALE_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatBusinessMessage(playerid, index)
{
	new msg[256];
    if(BusinessData[index][bdata_HOUR_OPEN] == 0 && BusinessData[index][bdata_HOUR_CLOSE] == 0) Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_BUSINESS_1_MSG, ACTION_KEY_STR);
    else Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_BUSINESS_2_MSG, BusinessData[index][bdata_HOUR_OPEN], BusinessData[index][bdata_HOUR_CLOSE], ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatJobPointMessage(playerid, job_index, job_point_index)
{
	new msg[256];	
    if(GetPlayerJobPointId(playerid) == Jobs_Points[job_index][job_point_index][job_point_ID]) Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_JOB_1_MSG, ACTION_KEY_STR);
    else Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_JOB_2_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);	
	return 1;
}

FormatInterestPointMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_INTEREST_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatGunSmithPointMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_GUNSMITH_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatGunLicenseMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_GUN_LICENSE_MSG, ACTION_KEY_STR, GUN_LICENSE_PRICE);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatActionMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_ACTION_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatEnvAreaMessage(playerid, type = -1)
{
	new msg[256];
    switch(type)
    {
        case ENV_AREA_TYPE_DANCE: Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_ENV_AREA_TYPE_DANCE, SECONDARY_ACTION_KEY_STR);
        case ENV_AREA_TYPE_BED: Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_ENV_AREA_TYPE_BED, SECONDARY_ACTION_KEY_STR);
        case ENV_AREA_TYPE_SEAT: Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_ENV_AREA_TYPE_SEAT, SECONDARY_ACTION_KEY_STR);
        case ENV_AREA_TYPE_PROSTITUTE_MONEY: Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_ENV_AREA_TYPE_PROSTITUTE_MONEY, SECONDARY_ACTION_KEY_STR);
        default: Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_ENV_DEFAULT, SECONDARY_ACTION_KEY_STR);
    }
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatBoomboxAreaMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_BOOMBOX_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}

FormatVinvAreaMessage(playerid)
{
	new msg[256];
    Text_Format_TD(msg, sizeof msg, PI[playerid][pi_LANG_ID], $TEXTDRAW_VINV_MSG, ACTION_KEY_STR);
	ShowPlayerInfoMessage(playerid, msg, 5, false);
	return 1;
}