#define MAX_PLAYER_CREDITS_OBJECTS 10

forward OnPlayerCompleteIntro(playerid);

new bool:pInIntro[MAX_PLAYERS],
	bool:pIntroExiting[MAX_PLAYERS],
	bool:pIntroFinished[MAX_PLAYERS],
	pIntroStep[MAX_PLAYERS],
	Timer:pIntro_Timer[MAX_PLAYERS] = {Timer:-1, ...},
	PlayerText:pIntro_PTD[MAX_PLAYERS][3] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},

	pCreditsObjects[MAX_PLAYERS][MAX_PLAYER_CREDITS_OBJECTS],
	Iterator:pCreditsObjects[MAX_PLAYERS]<MAX_PLAYER_CREDITS_OBJECTS>;