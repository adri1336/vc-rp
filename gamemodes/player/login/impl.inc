#include <YSI\y_hooks>

loadtext lang[login];

hook OnPlayerConnect(playerid)
{
	player_bad_logins[playerid] = 0;
	return 1;
}

public OnPlayerRequestLogin(playerid)
{
	inline OnPlayerLoginDialog(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, listitem

		if(response)
		{
			new tmp_passwd[64 + 1];
			SHA256_PassHash(inputtext, PI[playerid][pi_SALT], tmp_passwd, 64 + 1);

			if(!strcmp(tmp_passwd, PI[playerid][pi_PASSWD], false))
			{
				player_bad_logins[playerid] = 0;
				CallRemoteFunction("OnPlayerLogin", "i", playerid);
			}
			else
			{
				if(player_bad_logins[playerid] >= MAX_PLAYER_LOGIN_ATTEMPS) BlockIpAddress(PI[playerid][pi_IP], WRONG_LOGIN_BLOCK_MINUTES * 1000);
				else
				{
					player_bad_logins[playerid] ++;
					Text_Send(playerid, $MESSAGE_ERROR_WRONG_LOGIN, player_bad_logins[playerid], MAX_PLAYER_LOGIN_ATTEMPS, WRONG_LOGIN_BLOCK_MINUTES);
					Text_DialogBox(playerid, DIALOG_STYLE_PASSWORD, using inline OnPlayerLoginDialog, $DIALOG_LOGIN_CAPTION, $DIALOG_LOGIN_BODY, $DIALOG_LOGIN_YES, $DIALOG_LOGIN_NO, PI[playerid][pi_FIRST_NAME]);
				}
			}
		}
		else Kick(playerid);
	}
	Text_DialogBox(playerid, DIALOG_STYLE_PASSWORD, using inline OnPlayerLoginDialog, $DIALOG_LOGIN_CAPTION, $DIALOG_LOGIN_BODY, $DIALOG_LOGIN_YES, $DIALOG_LOGIN_NO, PI[playerid][pi_FIRST_NAME]);
	return 1;
}