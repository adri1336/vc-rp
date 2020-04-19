CreateConnectionTextdraws()
{
	TD_VCRP_INTRO_WATERMARK = TextDrawCreate(635.000000, 2.000000, ""SERVER_NAME_SHORT" "SERVER_VERSION" "RELEASE_VERSION"");
	TextDrawLetterSize(TD_VCRP_INTRO_WATERMARK, 0.199666, 0.969481);
	TextDrawAlignment(TD_VCRP_INTRO_WATERMARK, 3);
	TextDrawFont(TD_VCRP_INTRO_WATERMARK, 1);
	TextDrawColor(TD_VCRP_INTRO_WATERMARK, -1);
	TextDrawSetShadow(TD_VCRP_INTRO_WATERMARK, 0);
	TextDrawBackgroundColor(TD_VCRP_INTRO_WATERMARK, 255);
	TextDrawSetProportional(TD_VCRP_INTRO_WATERMARK, 1);
	return 1;
}

DestroyConnectionTextdraws()
{
	if(TD_VCRP_INTRO_WATERMARK != Text:INVALID_TEXT_DRAW)
	{
		TextDrawDestroy(TD_VCRP_INTRO_WATERMARK);
		TD_VCRP_INTRO_WATERMARK = Text:INVALID_TEXT_DRAW;
	}
	return 1;
}

ShowConnectionTdsForPlayer(playerid)
{
	TextDrawShowForPlayer(playerid, TD_VCRP_INTRO_WATERMARK);
	return 1;
}

HideConnectionTdsForPlayer(playerid)
{
	TextDrawHideForPlayer(playerid, TD_VCRP_INTRO_WATERMARK);
	return 1;
}