#define ROUTE_PERCENTAGE_UPDATE_MS 1000

forward OnPlayerRouteCalculated(Path:pathid, playerid, Float:destX, Float:destY, Float:destZ, bool:gps);

new bool:pInRoute[MAX_PLAYERS],
	pRoute_ProgressBar[MAX_PLAYERS] = {INVALID_PROGRESS_BAR_ID, ...},
	PlayerText:pRoute_Percentage_TD[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
	Timer:pRoute_Timer[MAX_PLAYERS] = {Timer:-1, ...};