#define MENU_LOGO_SIZE 150.0
#define MENU_PADDING 5.0

forward OnPlayerOpenMenu(playerid);

new PlayerText:Menu_PTD[MAX_PLAYERS][6] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	bool:pInMenu[MAX_PLAYERS],
	bool:pSpawnFromMenu[MAX_PLAYERS];