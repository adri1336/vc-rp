new bool:pSpawnInHospital[MAX_PLAYERS],
	bool:pInHospitalBed[MAX_PLAYERS],
	pHospitalBedIndex[MAX_PLAYERS],
	Timer:hopitalbed_timer[MAX_PLAYERS] = {Timer:-1, ...};

forward OnPlayerRequestHospitalBedMsg(playerid);
forward OnPlayerRequestHospitalBed(playerid, index);