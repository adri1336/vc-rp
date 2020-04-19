#define DRIVING_SCHOOL_UPDATE_INTERVAL 350
#define DRIVING_SCHOOL_CANCEL_SECONDS 20

new pDrivingSchoolPoints[MAX_PLAYERS],
	pDrivingSchoolQuestion[MAX_PLAYERS],
	
	bool:pInDrivingSchoolVehicleTest[MAX_PLAYERS],
	pDrivingSchoolVehicleIndex[MAX_PLAYERS] = {INVALID_VEHICLE_INDEX, ...},
	Timer:pDrivingSchoolTest_Timer[MAX_PLAYERS] = {Timer:-1, ...},
	pDrivingSchoolCancelSeconds[MAX_PLAYERS],
	pDrivingSchoolValidQuestion[MAX_PLAYERS];

forward OnPlayerRequestDrivingSchool(playerid);
forward OnPlayerDrivingSchoolTestDialog(playerid, dialogid, response, listitem, inputtext[]);
forward OnPlayerDrivingSchoolUpdate(playerid);