#define GetPlayerGameState(%0) player_game_state[%0]

SetPlayerGameState(playerid, GAME_STATES:game_state)
{
	CallRemoteFunction("OnPlayerGameStateChange", "idd", playerid, _:game_state, _:player_game_state[playerid]);
	player_game_state[playerid] = game_state;
	return 1;
}