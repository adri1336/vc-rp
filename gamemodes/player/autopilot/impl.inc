#include <YSI\y_hooks>

loadtext lang[autopilot];

hook OnPlayerConnect(playerid)
{
    pAutoPilotVehicleId[playerid] = INVALID_VEHICLE_ID;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(pAutoPilotVehicleId[playerid] != INVALID_VEHICLE_ID)
    DestroyAutoPilotVehicle(pAutoPilotVehicleId[playerid]);
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(pAutoPilotVehicleId[playerid] != INVALID_VEHICLE_ID)
    DestroyAutoPilotVehicle(pAutoPilotVehicleId[playerid]);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_PASSENGER)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(Iter_Contains(ApVehicleInfo, vehicleid))
	    {
            if(ApVehicleInfo[vehicleid][apv_InPath])
            {
                if(ApVehicleInfo[vehicleid][apv_Paused] && pAutoPilotVehicleId[playerid] == vehicleid)
                {
                    pAutoPilotSecondsLeft[playerid] = DEFAULT_AUTOPILOT_SECONDS_LEFT;
                    ResumeVehicleAutoPilot(vehicleid);
                    HidePlayerInfoMessage(playerid);
                }
            }
            else
            {
                if(pInTutorial[playerid] == TUTORIAL_2) return 1;
                if(pAutoPilotVehicleId[playerid] == INVALID_VEHICLE_ID || pAutoPilotVehicleId[playerid] == vehicleid)
                {
                    if(ApVehicleInfo[vehicleid][apv_CreatedBy] == INVALID_PLAYER_ID || ApVehicleInfo[vehicleid][apv_CreatedBy] == playerid)
                    {
                        if(PI[playerid][pi_MONEY] <= 0)
                        {
                            Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
                            RemovePlayerFromVehicle(playerid);
                        }
                        else
                        {
                            inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
                            {
                                #pragma unused pid, dialogid, inputtext
                                if(response)
                                {
                                    if(listitem == 0)
                                    {
                                        if(PlayerInvContainsItemType(playerid, _:INV_ITEM_TYPE_GPS))
                                        {
                                            ShowPlayerGps(playerid, vehicleid);
                                        }
                                        else
                                        {
                                            Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_AUTOPILOT_PLACES_CAPTION, $DIALOG_AUTOPILOT_PLACES_BODY, $DIALOG_AUTOPILOT_PLACES_YES, $DIALOG_AUTOPILOT_PLACES_NO);
                                            Text_Send(playerid, $MESSAGE_ERROR_NO_GPS);
                                        }
                                    }
                                    else AutoPilotVehicleGoTo(playerid, vehicleid, Interest_Coords[listitem - 1][0], Interest_Coords[listitem - 1][1], Interest_Coords[listitem - 1][2]);
                                }
                            }
                            Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_AUTOPILOT_PLACES_CAPTION, $DIALOG_AUTOPILOT_PLACES_BODY, $DIALOG_AUTOPILOT_PLACES_YES, $DIALOG_AUTOPILOT_PLACES_NO);
                        }
                    }
                    else Text_Send(playerid, $MESSAGE_ERROR_NO_VEHICLE);
                }
            }
        }
    }
    else if(oldstate == PLAYER_STATE_PASSENGER)
    {
        if(pAutoPilotVehicleId[playerid] != INVALID_VEHICLE_ID)
        {
            PauseVehicleAutoPilot(pAutoPilotVehicleId[playerid]);
            HidePlayerAuxTextDraw(playerid);
        }
    }
    else if(newstate == PLAYER_STATE_SPECTATING)
    {
        if(pAutoPilotVehicleId[playerid] != INVALID_VEHICLE_ID)
        DestroyAutoPilotVehicle(pAutoPilotVehicleId[playerid]);
    }
    return 1;
}

timer OnPlayerCheckAutopilotVeh[1000](playerid, vehicleid)
{
    if(pAutoPilotVehicleId[playerid] == INVALID_VEHICLE_ID)
    {
        HidePlayerInfoMessage(playerid);
        if(pAutoPilotTimerLeft[playerid] != Timer:-1)
        {
            stop pAutoPilotTimerLeft[playerid];
            pAutoPilotTimerLeft[playerid] = Timer:-1;
        }
    }
    else
    {
        if(GetPlayerVehicleID(playerid) == vehicleid)
        {
            //taximetro
            if(ApVehicleInfo[ pAutoPilotVehicleId[playerid] ][apv_Taximeter])
            {
                ApVehicleInfo[vehicleid][apv_Distance] += GetVehicleDistanceFromPoint(vehicleid, ApVehicleInfo[vehicleid][apv_OldPos][0], ApVehicleInfo[vehicleid][apv_OldPos][1], ApVehicleInfo[vehicleid][apv_OldPos][2]);
                GetVehiclePos(vehicleid, ApVehicleInfo[vehicleid][apv_OldPos][0], ApVehicleInfo[vehicleid][apv_OldPos][1], ApVehicleInfo[vehicleid][apv_OldPos][2]);
                pAutoPilotPrice[playerid] = floatround(floatmul(TAXIMETER_BASE_PAYMENT, ApVehicleInfo[vehicleid][apv_Distance] / 1000.0));
                if(pAutoPilotPrice[playerid] > PI[playerid][pi_MONEY])
                {
                    Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
                    RemovePlayerFromVehicle(playerid);

                    stop ApVehicleInfo[vehicleid][apv_Timer];
                    ApVehicleInfo[vehicleid][apv_Timer] = Timer:-1;
                    ApVehicleInfo[vehicleid][apv_InPath] = false;
                    ApVehicleInfo[vehicleid][apv_DestroyTimer] = defer OnAutopilotRequestDestroy(vehicleid);
                    
                    SetVehicleVelocity(vehicleid, 0.0, 0.0, 0.0);
                    if(ApVehicleInfo[vehicleid][apv_PathId] != Path:INVALID_PATH_ID)
                    {
                        DestroyPath(ApVehicleInfo[vehicleid][apv_PathId]);
                        ApVehicleInfo[vehicleid][apv_PathId] = Path:INVALID_PATH_ID;
                    }
                    CallRemoteFunction("OnAutopilotCompleted", "ii", playerid, vehicleid);
                }
                ShowPlayerAuxTextDraw(playerid, GetLangTaximeterTD(playerid, pAutoPilotPrice[playerid]));
            }
        }
        else
        {
            if(pAutoPilotSecondsLeft[playerid] <= 0)
            {
                GivePlayerMoneyEx(playerid, -pAutoPilotPrice[playerid]);
                HidePlayerInfoMessage(playerid);
                DestroyAutoPilotVehicle(vehicleid);
                PlayerAutopilotCancelMsg(playerid, true);
            }
            else
            {
                PlayerAutopilotCancelMsg(playerid);
                pAutoPilotSecondsLeft[playerid] --;
            }
        }
    }
}

public OnAutopilotCompleted(playerid, vehicleid)
{
    GivePlayerMoneyEx(playerid, -pAutoPilotPrice[playerid]);
    HidePlayerAuxTextDraw(playerid);
    pAutoPilotVehicleId[playerid] = INVALID_VEHICLE_ID;
    Text_Send(playerid, $GAMETEXT_INFO_ARRIVED);
    return 1;
}

hook OnAutopilotPathFailed(forplayerid, vehicleid)
{
	Text_Send(forplayerid, $MESSAGE_ERROR_PATH);
	return 1;
}

public OnPlayerRequestedApTaxi(playerid)
{
    if(pAutoPilotVehicleId[playerid] != INVALID_VEHICLE_ID) return 1;
    new Float:pos[3], Float:angle, interiorid, worldid;
	GetPlayerExteriorPos(playerid, pos[0], pos[1], pos[2], angle, interiorid, worldid);

    new modelid = 420, color1 = 6, color2 = 1;
    if(random(2) == 1)
    {
        modelid = 438;
        color1 = 6;
        color2 = 76;
    }
    if(CreateAutopilotVehicle(playerid, modelid, pos[0], pos[1], pos[2], color1, color2))
    {
        pTaxiRequested[playerid] = false;
		pWaitingTaxiResponse[playerid] = false;
        Text_Send(playerid, $MESSAGE_INFO_TAXI);

        new Float:x, Float:y, Float:z;
        GetVehiclePos(pAutoPilotVehicleId[playerid], x, y, z);
        DestroyPlayerRoute(playerid, 1);
        AddRouteCp(playerid, x, y, z, 3.0);
        StartRoute(playerid);
    }
    return 1;
}