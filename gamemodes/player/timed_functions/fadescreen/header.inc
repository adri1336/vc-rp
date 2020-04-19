forward OnPlayerFadeScreenStart(playerid);

new Timer:fadescreen_timer[MAX_PLAYERS] = {Timer:-1, ...},
	pFadeScreenColor[MAX_PLAYERS];