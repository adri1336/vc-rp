YCMD:getadmin(playerid, params[], help)
{
	if(IsPlayerAdmin(playerid))
	{
		SetPlayerAdminLevel(playerid, MAX_ADMIN_LEVELS - 1);
		SendClientMessage(playerid, -1, "OK");
	}
	return 1;
}