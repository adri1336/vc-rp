loadtext lang[player_task];

FormatPtaskInfoMessage(playerid, id)
{
    new str[128];
    switch(id)
    {
        case 0:
        {
            Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $MESSAGE_LEVEL_UP, PI[playerid][pi_LEVEL]);
            ShowPlayerInfoMessage(playerid, str, 5);
        }
        case 1:
        {
            Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $MESSAGE_1_PTASK);
            ShowPlayerInfoMessage(playerid, str, 5);
        }
        case 2:
        {
            Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $MESSAGE_2_PTASK);
            ShowPlayerInfoMessage(playerid, str, 5);
        }
        case 3:
        {
            Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $MESSAGE_3_PTASK);
            ShowPlayerInfoMessage(playerid, str, 5);
        }
    }
	return 1;
}