#define ATTACHED_OBJECT_ANIM_SLOT 9

new bool:pAnimEnv[MAX_PLAYERS],
	Timer:pAnimEnv_Timer[MAX_PLAYERS] = {Timer:-1, ...},
	Timer:pAnimEnv_Delay_Timer[MAX_PLAYERS] = {Timer:-1, ...};

forward OnPlayerRequestAnimEnvStop(playerid);