#define FUELING_UP_INTERVAL 3000
#define FUELING_UP_LITERS 5

new bool:pGasStation[MAX_PLAYERS],
	Timer:pGasStation_Timer[MAX_PLAYERS] = {Timer:-1, ...};

forward OnPlayerRequestGasStation(playerid, vehicle_index);