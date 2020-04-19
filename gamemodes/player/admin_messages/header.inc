enum
{
	PUNISHMENT_TYPE_PERM_BAN,
	PUNISHMENT_TYPE_TEMP_BAN,
	PUNISHMENT_TYPE_KICK,
	PUNISHMENT_TYPE_AC_KICK,
	PUNISHMENT_TYPE_AC_WARN
};
forward OnPlayerGetAdminPunishment(playerid, player_name[], adminid, type, reason[]);