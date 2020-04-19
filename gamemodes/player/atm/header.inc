#define MAX_ATM_MOVEMENT 10000

new bool:pUsingAtm[MAX_PLAYERS],
	PlayerText:PTD_Atm[MAX_PLAYERS][9] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...};

forward OnPlayerRequestAtm(playerid);