DestroyPlayerLabel(playerid)
{
	if(PlayerLabel[playerid] != Text3D:INVALID_STREAMER_ID)
	{
		DestroyDynamic3DTextLabel(PlayerLabel[playerid]);
		PlayerLabel[playerid] = Text3D:INVALID_STREAMER_ID;
		SetPVarInt(playerid, "playerLabel", _:PlayerLabel[playerid]);
	}
	return 1;
}

CreatePlayerLabel(playerid, text[], color, Float:x, Float:y, Float:z, Float:drawdistance, bool:testlos = false, bool:zfix = true, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID)
{
	DestroyPlayerLabel(playerid);
	if(zfix) z += 0.5;

	PlayerLabel[playerid] = CreateDynamic3DTextLabel(text, color, x, y, z, drawdistance, .testlos = testlos, .playerid = playerid, .attachedplayer = attachedplayer, .attachedvehicle = attachedvehicle);
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, PlayerLabel[playerid], E_STREAMER_EXTRA_ID, _:LABEL_TYPE_PLAYER_LABEL);
	SetPVarInt(playerid, "playerLabel", _:PlayerLabel[playerid]);
	return 1;
}