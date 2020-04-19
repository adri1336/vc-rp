loadtext lang[label_render];

GetPlayerEntranceName(playerid, id)
{
	new name[45];
    switch(id)
    {
        case 1: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_1_NAME);
        case 2: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_2_NAME);
        case 3: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_3_NAME);
        case 4: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_4_NAME);
        case 5: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_5_NAME);
        case 6: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_6_NAME);
        case 7: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_7_NAME);
        case 9: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_8_NAME);
        case 10: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_9_NAME);
        case 11: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_10_NAME);
        case 12: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_11_NAME);
        case 13: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $ENTRANCE_12_NAME);
	}
	return name;
}

FormatEntranceLabel(playerid, index)
{
	new label_str[256];
	Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_ENTRANCE, Entrances[index][entrance_ID], GetPlayerEntranceName(playerid, Entrances[index][entrance_ID_ENTRANCE]));
	CreatePlayerLabel(playerid, label_str, -1, Entrances[index][entrance_X], Entrances[index][entrance_Y], Entrances[index][entrance_Z], PLAYER_LABEL_DISTANCE, true);
	return 1;
}

FormatIntEntranceLabel(playerid, index)
{
	new label_str[45];
	Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_INTERIOR);
	CreatePlayerLabel(playerid, label_str, 0xADD8E6FF, Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_X], Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_Y], Interiors[Entrances[index][entrance_INTERIOR_INDEX]][interior_Z], PLAYER_LABEL_DISTANCE, true);
	return 1;
}

FormatPropertyDoorLabel(playerid, property_index, door_index)
{
	new label_str[256];
    if(IsPropertyOccupied(property_index))
    {
        if(IsPropertyForRent(property_index)) Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_1_PROPERTY, PropertyInfo[property_index][property_ID], PropertyInfo[property_index][property_PLAYER_NAME], PropertyInfo[property_index][property_RENT_EXPIRE_DATE]);
        else Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_2_PROPERTY, PropertyInfo[property_index][property_ID], PropertyInfo[property_index][property_PLAYER_NAME]);
    }
    else
    {
        if(IsPropertyForRent(property_index)) Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_3_PROPERTY, PropertyInfo[property_index][property_ID], PropertyInfo[property_index][property_LEVEL], PropertyInfo[property_index][property_PRICE]);
        else Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_4_PROPERTY, PropertyInfo[property_index][property_ID], PropertyInfo[property_index][property_LEVEL], PropertyInfo[property_index][property_PRICE]);
    }
	CreatePlayerLabel(playerid, label_str, -1, PropertyDoor[property_index][door_index][prop_door_EXT_X], PropertyDoor[property_index][door_index][prop_door_EXT_Y], PropertyDoor[property_index][door_index][prop_door_EXT_Z], PLAYER_LABEL_DISTANCE, true);
	return 1;
}

FormatIntPropertyDoorLabel(playerid, property_index, door_index)
{
	new label_str[45];
    Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_INTERIOR_PROPERTY);
	CreatePlayerLabel(playerid, label_str, 0xADD8E6FF, Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_X], Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_Y], Interiors[ PropertyDoor[property_index][door_index][prop_door_ID_INTERIOR_INDEX] ][interior_Z], PLAYER_LABEL_DISTANCE, true);
	return 1;
}

FormatRentVehicleLabel(playerid, vehindex)
{
	new Float:v_size[3];
	GetVehicleModelInfo(VehicleInfo[vehindex][vinfo_MODELID], VEHICLE_MODEL_INFO_SIZE, v_size[0], v_size[1], v_size[2]);

	new label_str[256];
	Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_RENT_VEHICLE, VehicleInfo[vehindex][vinfo_ID], GetVehicleNameByModelid(VehicleInfo[vehindex][vinfo_MODELID]), VehicleInfo[vehindex][vinfo_PRICE], VehicleInfo[vehindex][vinfo_LEVEL]);
	CreatePlayerLabel(playerid, label_str, -1, 0.0, 0.0, v_size[2] - 0.7, PLAYER_LABEL_DISTANCE, true, .attachedvehicle = VehicleInfo[vehindex][vinfo_VEHICLE_ID]);
	return 1;
}

FormatUsedVehicleLabel(playerid, vehindex)
{
	new Float:v_size[3];
	GetVehicleModelInfo(VehicleInfo[vehindex][vinfo_MODELID], VEHICLE_MODEL_INFO_SIZE, v_size[0], v_size[1], v_size[2]);

	new label_str[256];
	if(!PI[playerid][pi_MPH]) Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_USED_VEH, vehindex, GetVehicleNameByModelid(VehicleInfo[vehindex][vinfo_MODELID]), VehicleInfo[vehindex][vinfo_PRICE], VehicleInfo[vehindex][vinfo_LEVEL], VehicleInfo[vehindex][vinfo_DISTANCE] / 1000.0);
	else Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_USED_VEH_MPH, vehindex, GetVehicleNameByModelid(VehicleInfo[vehindex][vinfo_MODELID]), VehicleInfo[vehindex][vinfo_PRICE], VehicleInfo[vehindex][vinfo_LEVEL], KMHtoMPH(VehicleInfo[vehindex][vinfo_DISTANCE] / 1000.0));
	CreatePlayerLabel(playerid, label_str, -1, 0.0, 0.0, v_size[2] - 0.7, PLAYER_LABEL_DISTANCE, true, .attachedvehicle = VehicleInfo[vehindex][vinfo_VEHICLE_ID]);
	return 1;
}

FormatBSalePointLabel(playerid, index)
{
	new label_str[45];
	format(label_str, sizeof label_str, "%s", GetBusinessSaleTypeNameFromId(playerid, BSales_Points[index][bsale_point_ID_TYPE]));
	format(label_str, sizeof label_str, "%c%s", toupper(label_str[0]), label_str[1]);
	CreatePlayerLabel(playerid, label_str, 0xADD8E6FF, BSales_Points[index][bsale_point_X], BSales_Points[index][bsale_point_Y], BSales_Points[index][bsale_point_Z], PLAYER_LABEL_DISTANCE, true);
	return 1;
}

FormatIntBusinessDoorLabel(playerid, business_index, door_index)
{
	new label_str[45];
    Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_INTERIOR_BUSINESS);
	CreatePlayerLabel(playerid, label_str, 0xADD8E6FF, Interiors[ BusinessDoors[business_index][door_index][bdoor_INDEX_INTERIOR] ][interior_X], Interiors[ BusinessDoors[business_index][door_index][bdoor_INDEX_INTERIOR] ][interior_Y], Interiors[ BusinessDoors[business_index][door_index][bdoor_INDEX_INTERIOR] ][interior_Z], PLAYER_LABEL_DISTANCE, true);
	return 1;
}

FormatBusinessDoorLabel(playerid, business_index, door_index)
{
	new label_str[256];
    new business_name[32];
    format(business_name, sizeof business_name, "%s", GetBusinessTypeNameFromId(playerid, BusinessData[business_index][bdata_ID_TYPE]));
    format(business_name, sizeof business_name, "%c%s", toupper(business_name[0]), business_name[1]);
    if(IsBusinessOccupied(business_index)) Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_1_BUSINESS, BusinessData[business_index][bdata_ID], business_name, BusinessData[business_index][bdata_PLAYER_NAME]);
    else Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_2_BUSINESS, BusinessData[business_index][bdata_ID], business_name, BusinessData[business_index][bdata_LEVEL], BusinessData[business_index][bdata_PRICE]);
	CreatePlayerLabel(playerid, label_str, -1, BusinessDoors[business_index][door_index][bdoor_EXT_X], BusinessDoors[business_index][door_index][bdoor_EXT_Y], BusinessDoors[business_index][door_index][bdoor_EXT_Z], PLAYER_LABEL_DISTANCE, true);
}

FormatJobPointLabel(playerid, job_index, job_point_index)
{
	new label_str[256];
    new job_name[64];
    format(job_name, sizeof job_name, "%s", GetJobName(playerid, Jobs[job_index][job_ID]));
    format(job_name, sizeof job_name, "%c%s", toupper(job_name[0]), job_name[1]);
    if(job_point_index == 0)
    {
        if(Jobs_Points[job_index][job_point_index][job_point_MIN_JOB_LEVEL] > 1) Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_1_JOB, Jobs[job_index][job_ID], job_name, Jobs[job_index][job_MIN_LEVEL], Jobs_Points[job_index][job_point_index][job_point_MIN_JOB_LEVEL]);
        else Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_2_JOB, Jobs[job_index][job_ID], job_name, Jobs[job_index][job_MIN_LEVEL]);
    }
    else
    {
        if(Jobs_Points[job_index][job_point_index][job_point_MIN_JOB_LEVEL] > 1) Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_3_JOB, Jobs[job_index][job_ID], job_name, Jobs_Points[job_index][job_point_index][job_point_ID], Jobs[job_index][job_MIN_LEVEL], Jobs_Points[job_index][job_point_index][job_point_MIN_JOB_LEVEL]);
        else Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_4_JOB, Jobs[job_index][job_ID], job_name, Jobs_Points[job_index][job_point_index][job_point_ID], Jobs[job_index][job_MIN_LEVEL]);
    }
	CreatePlayerLabel(playerid, label_str, -1, Jobs_Points[job_index][job_point_index][job_point_X], Jobs_Points[job_index][job_point_index][job_point_Y], Jobs_Points[job_index][job_point_index][job_point_Z], PLAYER_LABEL_DISTANCE, true);
	return 1;
}

FormatInterestPointsLabel(playerid, index)
{
	new label_str[256];
    Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_INTEREST_POINTS);
	CreatePlayerLabel(playerid, label_str, -1, Interest_Points[index][0], Interest_Points[index][1], Interest_Points[index][2], PLAYER_LABEL_DISTANCE, true);
	return 1;
}

FormatCarWorkShopLabel(playerid, index)
{
	new label_str[256];
    Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_CARWORKSHOP);
	CreatePlayerLabel(playerid, label_str, -1, Car_Workshop_Points[index][0], Car_Workshop_Points[index][1], Car_Workshop_Points[index][2], PLAYER_LABEL_DISTANCE, true);
	return 1;
}

FormatBoomboxLabel(playerid, index)
{
	new label_str[256];
	if(isnull(Boombox[index][boombox_URL])) Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_BOOMBOX_OFF, index);
    else Text_Format_Dialog(label_str, sizeof label_str, PI[playerid][pi_LANG_ID], $LABEL_BOOMBOX, index, Boombox[index][boombox_PLAYING]);
	CreatePlayerLabel(playerid, label_str, -1, Boombox[index][boombox_X], Boombox[index][boombox_Y], Boombox[index][boombox_Z] + 0.3, PLAYER_LABEL_DISTANCE, false);
	return 1;
}