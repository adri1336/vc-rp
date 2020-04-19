enum GAME_STATES
{
	GAME_STATE_NONE,
	GAME_STATE_CONNECTED,
	GAME_STATE_SPECTATING,
	GAME_STATE_SPAWNED,
	GAME_STATE_DEAD
};
new
	bool:pFirstSpawn[MAX_PLAYERS],
	GAME_STATES:player_game_state[MAX_PLAYERS],
	Group:global_group;

forward OnGlobalGroupCreated();
forward OnPlayerGameStateChange(playerid, newstate, oldstate);