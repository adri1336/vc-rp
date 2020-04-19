#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerConnect(%d);", playerid);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerDisconnect(%d, %d);", playerid, reason);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerRequestClass(%d, %d);", playerid, classid);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerRequestSpawn(playerid)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerRequestSpawn(%d);", playerid);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerSpawn(%d);", playerid);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerDeath(%d, %d, %d);", playerid, killerid, reason);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerFinishedDL(playerid, virtualworld)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerFinishedDownloading(%d, %d);", playerid, virtualworld);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerStateChange(%d, %s, %s);", playerid, Player_States_String[newstate], Player_States_String[oldstate]);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerTakeDamage(%d, %d, %.4f, %d, %d);", playerid, issuerid, amount, weaponid, bodypart);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerVehicleChange(playerid, from_vehicleid, to_vehicleid)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerVehicleChange(%d, %d, %d);", playerid, from_vehicleid, to_vehicleid);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerEnterDynArea(%d, %d);", playerid, areaid);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerLeaveDynArea(%d, %d);", playerid, areaid);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new debug_message[145];
	format(debug_message, sizeof debug_message, "Debug: OnPlayerKeyStateChange(%d, %d, %d);", playerid, newkeys, oldkeys);
	SendClientMessage(playerid, -1, debug_message);
	print(debug_message);
	return 1;
}

/*new panimidx[MAX_PLAYERS],
	pspecialAction[MAX_PLAYERS];
hook OnPlayerUpdate(playerid)
{
	new animidx = GetPlayerAnimationIndex(playerid);
	if(animidx != panimidx[playerid])
    {
        new animlib[32];
        new animname[32];
        new msg[128];
        GetAnimationName(animidx,animlib,32,animname,32);
		format(msg, 128, "idx: %d || libary: %s || name: %s || index: %d", animidx, animlib, animname, animidx);
		SendClientMessage(playerid, 0xFFFFFFFF, msg);
		panimidx[playerid] = animidx;
    }

	new specialAction = GetPlayerSpecialAction(playerid);
	if(specialAction != pspecialAction[playerid])
	{
		new string[128];
		format(string, 128, "special action: %d", specialAction);
		SendClientMessage(playerid, -1, string);
		pspecialAction[playerid] = specialAction;
	}
	return 1;
}*/