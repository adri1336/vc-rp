loadtext lang[admin_chat];

SendAdminChat(playerid, text[])
{
	foreach(new i : Player)
	{
		if(PI[i][pi_ADMIN_LEVEL])
		{
			switch(PI[playerid][pi_ADMIN_LEVEL])
			{
				case ADMIN_LEVEL_DEVELOPER: Text_Send(i, $MESSAGE_CHAT_DEVELOPER, PI[playerid][pi_ADMIN_LEVEL], PI[playerid][pi_NAME], playerid, text);
				case ADMIN_LEVEL_MODERATOR: Text_Send(i, $MESSAGE_CHAT_ADMIN, PI[playerid][pi_ADMIN_LEVEL], PI[playerid][pi_NAME], playerid, text);
				case ADMIN_LEVEL_ADMINISTRATOR: Text_Send(i, $MESSAGE_CHAT_MODERATOR, PI[playerid][pi_ADMIN_LEVEL], PI[playerid][pi_NAME], playerid, text);
			}
		}
	}
	return 1;
}