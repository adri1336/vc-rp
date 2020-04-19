#define MAX_NEARS_PLAYERS_DIALOG 10
#define NEARS_PLAYERS_VALID_DISTANCE 3.0

enum
{
	NEAR_PLAYER_DIALOG_INV_GIVE,
	NEAR_PLAYER_DIALOG_INV_SHOW
};

new pNearsPlayersId[MAX_PLAYERS][MAX_NEARS_PLAYERS_DIALOG][2];

forward OnSelectNearPlayer(playerid, id, selected_playerid);