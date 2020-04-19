#include <YSI\y_hooks>

YCMD:iboombox(playerid, params[], help)
{
    if(!sscanf(params, "d", params[0]))
    {
        if(IsValidBoombox(params[0]))
        {
            new string[128], pid = INVALID_PLAYER_ID;
            if(Boombox[params[0]][boombox_ACCOUNT_ID] != 0)
            {
                pid = GetPlayeridFromId(Boombox[params[0]][boombox_ACCOUNT_ID]);
            }
            format(string, sizeof string, "ACCOUNT ID: %d, PLAYERID: %d", Boombox[params[0]][boombox_ACCOUNT_ID], pid);
            SendClientMessage(playerid, -1, string);
        }
        else SendClientMessage(playerid, -1, "invalid boombox id");
    }
    else SendClientMessage(playerid, -1, "syntax error");
    return 1;
}

YCMD:dboombox(playerid, params[], help)
{
    if(!sscanf(params, "d", params[0]))
    {
        if(IsValidBoombox(params[0]))
        {
            if(DestroyBoombox(params[0])) SendClientMessage(playerid, -1, "destroyed");
            else SendClientMessage(playerid, -1, "error");
        }
        else SendClientMessage(playerid, -1, "invalid boombox id");
    }
    else SendClientMessage(playerid, -1, "syntax error");
    return 1;
}