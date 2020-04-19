#include <YSI\y_hooks>

hook OnScriptInit()
{
	global_group = Group_Create();
	CallRemoteFunction("OnGlobalGroupCreated", "");
	return 1;
}

hook OnPlayerConnect(playerid)
{
	pFirstSpawn[playerid] = true;
	SetPlayerGameState(playerid, GAME_STATE_CONNECTED);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	Group_SetPlayer(global_group, playerid, false);
	return 1;
}

hook OnPlayerLogin(playerid)
{
	Group_SetPlayer(global_group, playerid, true);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(pFirstSpawn[playerid])
	{
		pFirstSpawn[playerid] = false;
		CallRemoteFunction("OnPlayerFirstSpawn", "ib", playerid, pNewUser[playerid]);
	}
	SetPlayerGameState(playerid, GAME_STATE_SPAWNED);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	SetPlayerGameState(playerid, GAME_STATE_DEAD);
	return 1;
}