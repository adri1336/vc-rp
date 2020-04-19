#define MAX_PLAYER_PROPERTIES 3
new Iterator:PlayerProperties<MAX_PLAYERS, MAX_PROPERTIES>;

#define PROPERTY_TOUR_TIME 60
#define MIN_TIME_BETWEEN_PROPERTY_TOUR 300
#define PROPERTY_TOUR_UPDATE_INTERVAL 1000

new pPropertyTourTime[MAX_PLAYERS],
	Timer:pPropertyTourTimer[MAX_PLAYERS] = {Timer:-1, ...},
	pLastPropertyTour[MAX_PLAYERS];

forward OnPlayerEnterProperty(playerid);
forward OnPlayerExitProperty(playerid);