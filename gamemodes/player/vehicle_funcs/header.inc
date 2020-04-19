#define UPDATE_VEHFUNCS_INTERVAL 200

new bool:pPlayerVehFuncs[MAX_PLAYERS],
	Timer:pPlayerVehFuncsTimer[MAX_PLAYERS] = {Timer:-1, ...};

new PlayerText:PTD_VehicleSpeedo[MAX_PLAYERS][5] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PlayerText:PTD_VehiclePbarIcons[MAX_PLAYERS][2] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PROGRESSBAR_VEHICLE_HEALTH[MAX_PLAYERS] = {INVALID_PROGRESS_BAR_ID, ...},
	PROGRESSBAR_VEHICLE_FUEL[MAX_PLAYERS] = {INVALID_PROGRESS_BAR_ID, ...};

forward OnPlayerChangeVRadio(playerid, vehindex, radio);