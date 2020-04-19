#include <YSI\y_hooks>

hook OnPlayerCheatDetected(playerid, cheat)
{
	if(PI[playerid][pi_ADMIN_LEVEL] != ADMIN_LEVEL_DEVELOPER)
	{
		if(IsKickCheat(cheat))
		{
			new cheat_name[24];
			format(cheat_name, sizeof cheat_name, "%s", GetCheatName(cheat));
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_admin_history (id_player, type, reason, date) VALUES (%d, %d, '%e', '%e');", PI[playerid][pi_ID], RESTRICTION_TYPE_KICK, cheat_name, getDateTimeDB());
			mysql_tquery(vcrp_db, QUERY_BUFFER);
			//player
			CallRemoteFunction("OnPlayerGetAdminPunishment", "isids", playerid, PI[playerid][pi_NAME], INVALID_PLAYER_ID, PUNISHMENT_TYPE_AC_KICK, cheat_name);
			Kick(playerid);			
		}
		else CallRemoteFunction("OnPlayerGetAdminPunishment", "isids", playerid, PI[playerid][pi_NAME], INVALID_PLAYER_ID, PUNISHMENT_TYPE_AC_WARN, GetCheatName(cheat));
	}
	return 1;
}