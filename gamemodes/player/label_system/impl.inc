#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
	PlayerLabel[playerid] = Text3D:INVALID_STREAMER_ID;
	SetPVarInt(playerid, "playerLabel", _:PlayerLabel[playerid]);
	return 1;
}

hook OnPlayerDisconnect(playerid)
{
	DestroyPlayerLabel(playerid);
	return 1;
}