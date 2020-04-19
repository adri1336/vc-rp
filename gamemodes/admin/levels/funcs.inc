SetPlayerAdminLevel(playerid, level, bool:update = true)
{
	if(level < 0 || level >= MAX_ADMIN_LEVELS) return 0;
	for (new i = 1; i < MAX_ADMIN_LEVELS; i ++) Group_SetPlayer(Admin_Groups[i], playerid, false);

	PI[playerid][pi_ADMIN_LEVEL] = level;
	
	if(level) Group_SetPlayer(Admin_Groups[level], playerid, true);

	if(update) orm_update(PI[playerid][pi_ORM]);
	return 1;
}