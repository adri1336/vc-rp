new pAutoPilotVehicleId[MAX_PLAYERS] = {INVALID_VEHICLE_ID, ...},
    pAutoPilotPrice[MAX_PLAYERS];
forward OnAutopilotCompleted(playerid, vehicleid);
forward OnPlayerRequestedApTaxi(playerid);

#define DEFAULT_AUTOPILOT_SECONDS_LEFT 20
new pAutoPilotSecondsLeft[MAX_PLAYERS],
    Timer:pAutoPilotTimerLeft[MAX_PLAYERS] = {Timer:-1, ...};