#include <YSI\y_hooks>

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(pAnimEnv[playerid]) RemovePlayerAnimEnv(playerid);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(pAnimEnv[playerid])
	{
		if(oldstate == PLAYER_STATE_ONFOOT)
		{
			RemovePlayerAnimEnv(playerid, false);
		}
	}
	return 1;
}

hook OnPlayerOpenGps(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	SetPlayerAnimEnv(playerid, "CASINO", "cards_loop", true, 18875, 6, 0.077999, 0.016000, 0.082999, -17.399991, -12.199999, -176.500137);
	return 1;
}

hook OnPlayerOpenPhone(playerid, bool:calling)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(!calling) SetPlayerAnimEnv(playerid, "CASINO", "cards_loop", false, -1001, 6, 0.112999, 0.023000, 0.102000, -48.599987, -12.799999, 0.000000);
		else SetPlayerAnimEnv(playerid, "", "", false, -1001, 6, 0.100000, 0.032999, 0.018999, -90.299789, -4.200017, 0.000000, .specialaction = SPECIAL_ACTION_USECELLPHONE);
	}
	return 1;
}

hook OnPlayerCheckTime(playerid)
{
	new string[24];
	format(string, sizeof string, "%02d:%02d", SERVER_TIME[0], SERVER_TIME[1]);
	GameTextForPlayer(playerid, string, 1, 1);
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		ApplyAnimation(playerid, "COP_AMBIENT", "Coplook_watch", 4.1, false, false, false, 0, 0, 1);
	}
	return 1;
}

public OnPlayerRequestAnimEnvStop(playerid)
{
	if(pAnimEnv[playerid]) RemovePlayerAnimEnv(playerid);
	return 1;
}

timer OnPlayerAnimStopTimer[5000](playerid)
{
	if(pAnimEnv[playerid]) RemovePlayerAnimEnv(playerid);
	return 1;
}

timer OnPlayerAnimDelayed[5000](playerid, modelid, bone, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:sx, Float:sy, Float:sz, soundid)
{
	if(pAnimEnv[playerid])
	{
		if(modelid > 0) SetPlayerAttachedObject(playerid, ATTACHED_OBJECT_ANIM_SLOT, modelid, bone, x, y, z, rx, ry, rz, sx, sy, sz);
		if(soundid > 0) PlayerPlaySound(playerid, soundid, 0.0, 0.0, 0.0);
	}
	return 1;
}