#include <YSI\y_hooks>

loadtext lang[interest_points];

public OnPlayerRequestInterestPoint(playerid)
{
	HidePlayerInfoMessage(playerid);
	inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, inputtext
		if(response)
		{
			DestroyPlayerRoute(playerid, 1);
			AddRouteCp(playerid, Interest_Coords[listitem][0], Interest_Coords[listitem][1], Interest_Coords[listitem][2], 5.0);
			StartRoute(playerid);
			Text_Send(playerid, $MESSAGE_INFO_INTEREST_POINT);
		}
	}
	Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_INTEREST_POINT_CAPTION, $DIALOG_INTEREST_POINT_BODY, $DIALOG_INTEREST_POINT_YES, $DIALOG_INTEREST_POINT_NO);
	return 1;
}