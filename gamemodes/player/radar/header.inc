#define RADAR_POS_X 70.0
#define RADAR_POS_Y 330.0
#define RADAR_SIZE_X 115.0
#define RADAR_SEPARATION 2.0
#define RADAR_SIZE_Y_SITE 20.0
#define RADAR_LSIZE_Y_SITE 1.135406
#define RADAR_SIZE_Y 71.0
#define RADAR_POINT_SIZE 8.0

#define RADAR_UPDATE_INTERVAL 500
#define MAX_RADAR_MAPICONS 20

#define MAX_OBJECTIVES_IN_RADAR 10

new PlayerText:pRadarTextdraws[MAX_PLAYERS][4] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	Float:pRadarPosInfo[MAX_PLAYERS][5],
	pRadarArea[MAX_PLAYERS],
	bool:pRadarEnabled[MAX_PLAYERS],
	Timer:pRadarTimer[MAX_PLAYERS] = {Timer:-1, ...},

	PlayerText:pRadarVehicles_PTD[MAX_PLAYERS][MAX_PLAYER_VEHICLES] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PlayerText:pRadarObjectives_PTD[MAX_PLAYERS][MAX_OBJECTIVES_IN_RADAR] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PlayerText:pRadarMapIcons_PTD[MAX_PLAYERS][MAX_RADAR_MAPICONS] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PlayerText:pRadarRoute_PTD[MAX_PLAYERS][MAX_RADAR_MAPICONS] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},

	bool:pWasInRoute[MAX_PLAYERS];