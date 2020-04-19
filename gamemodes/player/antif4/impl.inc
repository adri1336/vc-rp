#include <YSI\y_hooks>

hook OnPlayerRequestClass(playerid, classid)
{
	if(GetPlayerGameState(playerid) != GAME_STATE_CONNECTED)
	{
		SetSpawnInfo(playerid, NO_TEAM, GetPlayerClothingSkinModel(playerid), PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], 0, 0, 0, 0, 0, 0);
		SpawnPlayer(playerid);
	}
	return 1;
}