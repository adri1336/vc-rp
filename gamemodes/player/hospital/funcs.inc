SetPlayerInBed(playerid, index)
{
	SetPlayerPos(playerid, Hospital_Beds[index][hbed_X], Hospital_Beds[index][hbed_Y], Hospital_Beds[index][hbed_Z]);
	if(random(2))
	{
		SetPlayerFacingAngle(playerid, Hospital_Beds[index][hbed_RZ] + 90.0);
		ApplyAnimation(playerid, "INT_HOUSE", "BED_Loop_L", 4.1, 1, 1, 1, 0, 0, 1);
	}
	else
	{
		SetPlayerFacingAngle(playerid, Hospital_Beds[index][hbed_RZ] - 90.0);
		ApplyAnimation(playerid, "INT_HOUSE", "BED_Loop_R", 4.1, 1, 1, 1, 0, 0, 1);
	}
	return 1;
}

CancelPlayerHospitalBed(playerid)
{
	if(hopitalbed_timer[playerid] != Timer:-1)
	{
		stop hopitalbed_timer[playerid];
		hopitalbed_timer[playerid] = Timer:-1;
	}
	if(pInHospitalBed[playerid])
	{
		Hospital_Beds[pHospitalBedIndex[playerid]][hbed_IN_USE] = false;
		pInHospitalBed[playerid] = false;
		pHospitalBedIndex[playerid] = 0;
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, true);
		ClearAnimations(playerid);
	}
	return 1;
}