#include <YSI\y_hooks>

loadtext lang[forum];

hook OnPlayerRegister(playerid)
{
	new login_key[50], salt[8];
	format(login_key, sizeof login_key, "%s", getRandomString(50));
	format(salt, sizeof salt, "%s", getRandomString(8));
	inline OnQueryLoad()
	{
		mysql_tquery(vc_forum_db, "UPDATE mybb_stats SET numusers = numusers + 1;");
		Text_Send(playerid, $MESSAGE_WARNING_REGISTERED, SERVER_WEBSITE);
	}
	mysql_format(vc_forum_db, QUERY_BUFFER, sizeof QUERY_BUFFER, 
		"\
			INSERT INTO mybb_users (username, password, salt, loginkey, email, regdate, signature, buddylist, ignorelist, pmfolders, notepad, usernotes, usergroup) VALUES \
			('%e', MD5(CONCAT(MD5('%e'), MD5('%e'))), '%e', '%e', '%e', %d, '', '', '', '', '', '', 2);\
		", PI[playerid][pi_NAME], salt, register_player_passwd[playerid], salt, login_key, PI[playerid][pi_EMAIL], gettime());
	mysql_tquery_inline(vc_forum_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	return 1;
}