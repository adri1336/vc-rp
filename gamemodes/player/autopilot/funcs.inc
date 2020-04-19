loadtext lang[autopilot];

PlayerAutopilotCancelMsg(playerid, bool:canceled = false)
{
    new str[256];
    if(canceled)
    {
        Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_DESTROYED);
        ShowPlayerInfoMessage(playerid, str);
    }
    else
    {
        Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_WARNING, pAutoPilotSecondsLeft[playerid]);
        ShowPlayerInfoMessage(playerid, str, 0, false);
    }
    return 1;
}