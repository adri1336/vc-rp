forward OnPlayerLoadScreenStart(playerid);
forward OnPlayerLoadScreenFin(playerid);

#define LOGO_ORIGINAL_SIZE_X 2001.0
#define LOGO_ORIGINAL_SIZE_Y 1392.0
enum enum_LoadScreens
{
	loadscreen_NAME[24],
	Float:loadscreen_LOGO_X,
	Float:loadscreen_LOGO_Y,
	Float:loadscreen_LOGO_SIZE
};
new LoadScreens[][enum_LoadScreens] =
{
	{"loadsc1", 115.0, 240.0, 180.0},
	{"loadsc2", 100.0, 265.0, 180.0},
	{"loadsc3", 115.0, 235.0, 180.0},
	{"loadsc4", 115.0, 275.0, 180.0},
	{"loadsc5", 110.0, 275.0, 180.0},
	//{"loadsc6", 95.0, 245.0, 180.0},
	{"loadsc7", 120.0, 275.0, 180.0},
	{"loadsc8", 120.0, 275.0, 180.0},
	//{"loadsc9", 120.0, 275.0, 180.0},
	{"loadsc10", 105.0, 275.0, 180.0},
	{"loadsc11", 120.0, 275.0, 180.0},
	{"loadsc12", 105.0, 265.0, 180.0},
	{"loadsc13", 90.0, 295.0, 180.0}
};

new Timer:loadscreen_timer[MAX_PLAYERS] = {Timer:-1, ...},
	PlayerText:PTD_Load_Screen[MAX_PLAYERS][2] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...};