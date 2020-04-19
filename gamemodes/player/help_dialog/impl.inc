#include <YSI\y_hooks>

loadtext lang[help];

public OnPlayerRequestHelpDialog(playerid)
{
	inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, inputtext
		if(response)
		{
			switch(listitem)
			{
				case 0: //general
				{
					inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
					{
						#pragma unused in_pid, in_dialogid, in_response, in_listitem, in_inputtext
					}
					Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline in_OnPlayerDialog, $DIALOG_HELP_GENERAL_CAPTION, $DIALOG_HELP_GENERAL_BODY, $DIALOG_HELP_GENERAL_YES, "", SERVER_WEBSITE);
				}
				case 1:
				{
					inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
					{
						#pragma unused in_pid, in_dialogid, in_response, in_listitem, in_inputtext
					}
					Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline in_OnPlayerDialog, $DIALOG_HELP_CHARACTER_CAPTION, $DIALOG_HELP_CHARACTER_BODY, $DIALOG_HELP_CHARACTER_YES, "");
				}
				case 2:
				{
					inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
					{
						#pragma unused in_pid, in_dialogid, in_response, in_listitem, in_inputtext
					}
					Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline in_OnPlayerDialog, $DIALOG_HELP_PROPERTIES_CAPTION, $DIALOG_HELP_PROPERTIES_BODY, $DIALOG_HELP_PROPERTIES_YES, "", MAX_PLAYER_PROPERTIES);
				}
				case 3:
				{
					inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
					{
						#pragma unused in_pid, in_dialogid, in_response, in_listitem, in_inputtext
					}
					Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline in_OnPlayerDialog, $DIALOG_HELP_VEHICLES_CAPTION, $DIALOG_HELP_VEHICLES_BODY, $DIALOG_HELP_VEHICLES_YES, "", MAX_PLAYER_VEHICLES);
				}
				case 4:
				{
					inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
					{
						#pragma unused in_pid, in_dialogid, in_response, in_listitem, in_inputtext
					}
					Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline in_OnPlayerDialog, $DIALOG_HELP_BUSINESS_CAPTION, $DIALOG_HELP_BUSINESS_BODY, $DIALOG_HELP_BUSINESS_YES, "", MAX_PLAYER_BUSINESS);
				}
				case 5:
				{
					inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
					{
						#pragma unused in_pid, in_dialogid, in_response, in_listitem, in_inputtext
					}
					Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline in_OnPlayerDialog, $DIALOG_HELP_JOBS_CAPTION, $DIALOG_HELP_JOBS_BODY, $DIALOG_HELP_JOBS_YES, "");
				}
			}
		}
	}
	Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_HELP_CAPTION, $DIALOG_HELP_BODY, $DIALOG_HELP_YES, $DIALOG_HELP_NO);
	return 1;
}

YCMD:help(playerid, params[], help)
{
	OnPlayerRequestHelpDialog(playerid);
	return 1;
}