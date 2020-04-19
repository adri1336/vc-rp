loadtext lang[real_estate];

FormatRealEstateDialogCaption(playerid)
{
	new str[64];
	Text_Format_Dialog(str, sizeof str, PI[playerid][pi_LANG_ID], $DIALOG_CAPTION);
	return str;
}

FormatRealEstateDialogHeader(playerid)
{
	new str[64];
	Text_Format_Dialog(str, sizeof str, PI[playerid][pi_LANG_ID], $DIALOG_HEADER);
	return str;
}

FormatRealEstateInfo(playerid, bool:property = true)
{
	new str[32];
    if(property) { Text_Format_Dialog(str, sizeof str, PI[playerid][pi_LANG_ID], $TYPE_PROPERTY); }
    else { Text_Format_Dialog(str, sizeof str, PI[playerid][pi_LANG_ID], $TYPE_BUSINESS); }
	return str;
}