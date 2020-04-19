#include <YSI\y_hooks>

YCMD:gvc(playerid, params[], help)
{
	new toplayerid = playerid;
	if(!sscanf(params, "u", params[0])) toplayerid = params[0];

	PI[toplayerid][pi_X] = New_User_Pos[0];
	PI[toplayerid][pi_Y] = New_User_Pos[1];
	PI[toplayerid][pi_Z] = New_User_Pos[2];
	PI[toplayerid][pi_ANGLE] = New_User_Pos[3];
	PI[toplayerid][pi_INTERIORID] = 0;
	PI[toplayerid][pi_WORLDID] = VC_WORLD;
	SetPlayerWorldState(toplayerid, PLAYER_WORLD_STATE_STREET);
	SetPlayerPosEx(toplayerid, PI[toplayerid][pi_X], PI[toplayerid][pi_Y], PI[toplayerid][pi_Z], PI[toplayerid][pi_ANGLE], PI[toplayerid][pi_INTERIORID], PI[toplayerid][pi_WORLDID], true);
	return 1;
}

YCMD:std(playerid, params[], help)
{
	//SelectTextDraw(playerid, 0xFF00CCFF);
	TogglePlayerControllable(playerid, false);
	return 1;
}

YCMD:radar(playerid, params[], help)
{
	if(pRadarEnabled[playerid]) DisablePlayerRadar(playerid);
	else EnablePlayerRadar(playerid);
	return 1;
}

YCMD:gpos(playerid, params[], help)
{	
	new Float:pos[4];
	if(IsPlayerInAnyVehicle(playerid))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
		GetVehicleZAngle(vehicleid, pos[3]);
	}
	else
	{
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		GetPlayerFacingAngle(playerid, pos[3]);
	}

	new msg[128];
	format(msg, sizeof msg, "X: %f Y: %f Z: %f A: %f INT: %d VW: %d", pos[0], pos[1], pos[2], pos[3], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	SendClientMessage(playerid, -1, msg);
	if(isnull(params)) print(msg);
	else printf("%s //%s", msg, params);
	return 1;
}

YCMD:gcpos(playerid, params[], help)
{
	new Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz;
	GetPlayerCameraPos(playerid, x, y, z);
	GetPlayerCameraLookAt(playerid, rx, ry, rz);
	if(isnull(params)) printf("%f, %f, %f, %f, %f, %f", x, y, z, rx, ry, rz);
	else printf("%f, %f, %f, %f, %f, %f //%s", x, y, z, rx, ry, rz, params);
	return 1;
}

YCMD:ls(playerid, params[], help)
{
	SetPlayerPos(playerid, 1555.400390, -1675.611694, 16.195312);
	return 1;
}

YCMD:setint(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Syntax: /setint [id]");
	SetPlayerInterior(playerid, params[0]);
	return 1;
}

YCMD:setvw(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Syntax: /setvw [id]");
	SetPlayerVirtualWorld(playerid, params[0]);
	return 1;
}

YCMD:setpos(playerid, params[], help)
{
	new Float:pos[3];
	if(sscanf(params, "fff", pos[0], pos[1], pos[2])) return SendClientMessage(playerid, -1, "Syntax: /setpos [x] [y] [z]");
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	return 1;
}

YCMD:vcsetpos(playerid, params[], help)
{
	new Float:pos[3];
	if(sscanf(params, "fff", pos[0], pos[1], pos[2])) return SendClientMessage(playerid, -1, "Syntax: /vcsetpos [x] [y] [z]");
	SetPlayerPos(playerid, pos[0] + 4000.0, pos[1] + 2000.0, pos[2]);
	return 1;
}

YCMD:sound(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Syntax: /sound [id]");
	PlayerPlaySound(playerid, params[0], 0.0, 0.0, 0.0);
	return 1;
}

YCMD:gotoint(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Syntax: /gotoint [id]");
	if(!IsValidInteriorIndex(params[0])) return SendClientMessage(playerid, -1, "Index no válido.");

	SetPlayerPosEx(playerid, Interiors[params[0]][interior_X], Interiors[params[0]][interior_Y], Interiors[params[0]][interior_Z], Interiors[params[0]][interior_ANGLE], Interiors[params[0]][interior_INTERIORID], -1, true);
	return 1;
}

YCMD:gotonode(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Syntax: /gotonode [id]");
	new MapNode:node = MapNode:params[0];
	new Float:x, Float:y, Float:z;
	GetMapNodePos(node, x, y, z);
	SetPlayerPos(playerid, x, y, z);
	return 1;
}

YCMD:devanim(playerid, params[], help)
{
	new animlib[24], animname[24], loop, lockx, locky, freeze, time;
	if(sscanf(params, "s[24]s[24]ddddd", animlib, animname, loop, lockx, locky, freeze, time)) return SendClientMessage(playerid, -1, "Syntax: /devanim [animlib] [animname] [loop] [lockx] [locky] [freeze] [time]");
	ApplyAnimation(playerid, animlib, animname, 4.1, loop, lockx, locky, freeze, time, 1);
	return 1;
}

YCMD:cobject(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Syntax: /cobject [modelid]");

	new Float:pos[3], Float:angle;
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, angle);

	pos[0] += (5.0 * floatsin(-angle, degrees));
	pos[1] += (5.0 * floatcos(-angle, degrees));

	new objid = CreateDynamicObject(params[0], pos[0], pos[1], pos[2], 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objid, E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_TEST);
	EditDynamicObject(playerid, objid);

	new str[128];
	format(str, sizeof str, "Object created, modelid: %d, objectid: %d", params[0], objid);
	SendClientMessage(playerid, -1, str);
	return 1;
}

YCMD:eobject(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Syntax: /eobject [objectid]");
	if(IsValidDynamicObject(params[0])) EditDynamicObject(playerid, params[0]);
	else SendClientMessage(playerid, -1, "Invalid object id!");
	return 1;
}

YCMD:dtobject(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Syntax: /dtobject [objectid]");
	if(IsValidDynamicObject(params[0]))
	{
		new modelid, Float:pos[3], Float:rot[3];
		modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, params[0], E_STREAMER_MODEL_ID);
		GetDynamicObjectPos(params[0], pos[0], pos[1], pos[2]);
		GetDynamicObjectRot(params[0], rot[0], rot[1], rot[2]);

		new objid = CreateDynamicObject(modelid, pos[0], pos[1], pos[2], rot[0], rot[1], rot[2], GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objid, E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_TEST);
		EditDynamicObject(playerid, objid);

		new str[128];
		format(str, sizeof str, "Object duplicated, modelid: %d, objectid: %d", modelid, objid);
		SendClientMessage(playerid, -1, str);
	}
	else SendClientMessage(playerid, -1, "Invalid object id!");
	return 1;
}

YCMD:dobject(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Syntax: /dobject [objectid]");
	if(IsValidDynamicObject(params[0]))
	{
		DestroyDynamicObject(params[0]);

		new str[128];
		format(str, sizeof str, "Objectid %d deleted!", params[0]);
		SendClientMessage(playerid, -1, str);
	}
	else SendClientMessage(playerid, -1, "Invalid object id!");
	return 1;
}

YCMD:hud(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Syntax: /hud [int]");
	TogglePlayerWideScreen(playerid, params[0]);
	return 1;
}

hook OnPlayerEditDynObj(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(response == EDIT_RESPONSE_FINAL && Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID) == _:OBJECT_TYPE_TEST)
	{
		SetDynamicObjectPos(objectid, x, y, z);
		SetDynamicObjectRot(objectid, rx, ry, rz);

		new str[128];
		format(str, sizeof str, "Objectid %d: %f, %f, %f, %f, %f, %f", objectid, x, y, z, rx, ry, rz);
		SendClientMessage(playerid, -1, str);
		print(str);
	}
	return 1;
}

YCMD:audio(playerid, params[], help)
{
	if(isnull(params)) return SendClientMessage(playerid, -1, "Syntax: /audio [url]");
	PlayAudioStreamForPlayer(playerid, params);
	return 1;
}

YCMD:fs(playerid, params[], help)
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Syntax: /fs [int]");
	SetPlayerFightingStyle(playerid, params[0]);
	return 1;
}