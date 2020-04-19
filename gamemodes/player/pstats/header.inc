#define THIRST_HOURS 9 //horas si sed esta a 0 va a 100
#define HUNGRY_HOURS 12 //horas si hambre esta a 0 va a 100
#define REP_MULTIPLIER 10 //6 rep para pasar al nivel2
#define MINUTES_FOR_REP 60
#define MIN_SECONDS_BETWEEN_INFO_MSG 120
#define KEY_SHOW_PSTATS KEY_NO
#define KEY_SHOW_PSTATS_STR "~k~~CONVERSATION_NO~"

new bool:pStatsMenu[MAX_PLAYERS],
	PlayerText:PTD_PLAYER_STATS[MAX_PLAYERS][4] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...};

new PROGRESSBAR_REPUTATION[MAX_PLAYERS] = {INVALID_PROGRESS_BAR_ID, ...},
	PROGRESSBAR_HUNGRY[MAX_PLAYERS] = {INVALID_PROGRESS_BAR_ID, ...},
	PROGRESSBAR_THIRST[MAX_PLAYERS] = {INVALID_PROGRESS_BAR_ID, ...};

forward OnPlayerOpenStatsTds(playerid);
forward OnPlayerCloseStatsTds(playerid);