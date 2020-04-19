loadtext lang[properties];

CountPlayerProperties(playerid, bool:rents = false)
{
	new c;
	foreach(new i : PlayerProperties<playerid>)
	{
		if(!IsPropertyForRent(i)) c++;
		else { if(rents) c++; }
	}
	return c;
}

PlayerPropertyTourMessage(playerid)
{
	new str[128];	
	Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXTDRAW_TOUR_MESSAGE, pPropertyTourTime[playerid]);
	ShowPlayerInfoMessage(playerid, str, 0, false);
	return 1;
}

PlayerPropertyTourCancelMessage(playerid)
{
	new str[128];	
	Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXTDRAW_TOUR_ENDED);
	ShowPlayerInfoMessage(playerid, str);
	return 1;
}