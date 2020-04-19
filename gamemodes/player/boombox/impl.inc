#include <YSI\y_hooks>

loadtext lang[boombox];

public OnPlayerRequestBoomboxCreation(playerid, inv_index)
{
    new Float:x, Float:y, Float:z, Float:angle, modelid, Float:distance;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, angle);
    x += (1.0 * floatsin(-angle, degrees));
    y += (1.0 * floatcos(-angle, degrees));
    sscanf(PINV[playerid][inv_index][pinv_PARAMS], "p<,>df", modelid, distance);
    if(CreateBoombox(x, y, z - 1.0, .distance = distance, .modelid = modelid, .interiorid = GetPlayerInterior(playerid), .worldid = GetPlayerVirtualWorld(playerid), .playerid = playerid, .rz = angle) == INVALID_BOOMBOX_ID) Text_Send(playerid, $MESSAGE_ERROR_POSITION);
    else
    {
        RemovePlayerInvetoryItem(playerid, inv_index);
        ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 1000, 1);
        Streamer_Update(playerid);
    }
    return 1;
}

public OnPlayerRequestBoomboxConfig(playerid, index)
{
    inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
    {
        #pragma unused pid, dialogid, inputtext
        if(response)
        {
            switch(listitem)
            {
                case 0: //emisora
                {
                    new dialog_message[512], line_str[45];
                    for(new i = 0, j = sizeof Radios; i != j; i ++)
                    {
                        if(isnull(Boombox[index][boombox_URL]))
                        {
                            if(i == 0) format(line_str, sizeof line_str, "{ec98f9}- %s\n", Radios[i][radio_NAME]);
                            else format(line_str, sizeof line_str, "{936c99}- %s\n", Radios[i][radio_NAME]);
                        }
                        else
                        {
                            if(!strcmp(Boombox[index][boombox_URL], Radios[i][radio_URL]) && i > 0) format(line_str, sizeof line_str, "{ec98f9}- %s\n", Radios[i][radio_NAME]);
                            else format(line_str, sizeof line_str, "{936c99}- %s\n", Radios[i][radio_NAME]);
                        }
                    
                        strcat(dialog_message, line_str);
                    }

                    inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
                    {
                        #pragma unused in_pid, in_dialogid, in_inputtext
                        if(in_response)
                        {
                            if(in_listitem == 0) SetBoomboxAudio(index);
                            else SetBoomboxAudio(index, Radios[in_listitem][radio_URL], Radios[in_listitem][radio_NAME]);
                        }
                    }
                    Dialog_ShowCallback(playerid, using inline in_OnPlayerDialog, DIALOG_STYLE_LIST, "Radio", dialog_message, ">", "X");
                }
                case 1: //mover
                {
                    if(!isnull(Boombox[index][boombox_URL])) Text_Send(playerid, $MESSAGE_ERROR_POWER);
                    else EditDynamicObject(playerid, Boombox[index][boombox_OBJECTID]);
                }
                case 2: //guardar
                {
                    new inv_params[64];
                    format(inv_params, sizeof inv_params, "%d, %f", Boombox[index][boombox_MODELID], Boombox[index][boombox_DISTANCE]);
                    if(AddPlayerInventoryItem(playerid, _:INV_ITEM_BOOMBOX, inv_params))
                    {
                        if(DestroyBoombox(index))
                        {
                            Streamer_Update(playerid);
                            DestroyPlayerLabel(playerid);
                            HidePlayerInfoMessage(playerid);
                            Text_Send(playerid, $GAMETEXT_INFO_TAKE);
                        }
                    }
                    else Text_Send(playerid, $MESSAGE_ERROR_INV);
                }
            }
        }
    }
    Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_BOOMBOX_CAPTION, $DIALOG_BOOMBOX_BODY, $DIALOG_BOOMBOX_YES, $DIALOG_BOOMBOX_NO);
    return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
    new streamer_info[2];
    Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);
    if(streamer_info[0] == _:AREA_TYPE_PLAY_BOOMBOX)
    {
        new index = streamer_info[1];
        if(!isnull(Boombox[index][boombox_URL]))
        {
            if(GetPlayerVehicleIndex(playerid) != INVALID_VEHICLE_INDEX && VehicleModelHasEngine(VehicleInfo[GetPlayerVehicleIndex(playerid)][vinfo_MODELID]))
            {
                if(VehicleInfo[GetPlayerVehicleIndex(playerid)][vinfo_RADIO] != 0)
                return Y_HOOKS_CONTINUE_RETURN_1;
            }

            PlayAudioStreamForPlayer(playerid, Boombox[index][boombox_URL], Boombox[index][boombox_X], Boombox[index][boombox_Y], Boombox[index][boombox_Z], Boombox[index][boombox_DISTANCE], 1);
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{
    new streamer_info[2];
    Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);
    if(streamer_info[0] == _:AREA_TYPE_PLAY_BOOMBOX)
    {
        new index = streamer_info[1];
        if(!isnull(Boombox[index][boombox_URL]))
        {
            if(GetPlayerVehicleIndex(playerid) != INVALID_VEHICLE_INDEX && VehicleModelHasEngine(VehicleInfo[GetPlayerVehicleIndex(playerid)][vinfo_MODELID]))
            {
                if(VehicleInfo[GetPlayerVehicleIndex(playerid)][vinfo_RADIO] != 0)
                return Y_HOOKS_CONTINUE_RETURN_1;
            }

            StopAudioStreamForPlayer(playerid);
        }
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_ONFOOT && (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER))
    {
        foreach(new i : Boombox)
        {
            if(IsPlayerInDynamicArea(playerid, Boombox[i][boombox_PLAY_AREAID], 1))
            {
                if(!isnull(Boombox[i][boombox_URL]))
                PlayAudioStreamForPlayer(playerid, Boombox[i][boombox_URL], Boombox[i][boombox_X], Boombox[i][boombox_Y], Boombox[i][boombox_Z], Boombox[i][boombox_DISTANCE], 1);
                return 1;
            }
        }
    }
    return 1;
}

hook OnPlayerEditDynObj(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(response != EDIT_RESPONSE_UPDATE)
	{
		new streamer_info[2];
        Streamer_GetArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, streamer_info);
        if(streamer_info[0] == _:OBJECT_TYPE_BOOMBOX)
        {
            new index = streamer_info[1];
            if(response == EDIT_RESPONSE_CANCEL)
            {
                SetDynamicObjectPos(objectid, Boombox[index][boombox_X], Boombox[index][boombox_Y], Boombox[index][boombox_Z]);
                SetDynamicObjectRot(objectid, Boombox[index][boombox_RX], Boombox[index][boombox_RY], Boombox[index][boombox_RZ]);
            }
            else
            {
                if(!SetBoomboxPos(index, x, y, z, rx, ry, rz))
                {
                    SetDynamicObjectPos(objectid, Boombox[index][boombox_X], Boombox[index][boombox_Y], Boombox[index][boombox_Z]);
                    SetDynamicObjectRot(objectid, Boombox[index][boombox_RX], Boombox[index][boombox_RY], Boombox[index][boombox_RZ]);
                    Text_Send(playerid, $MESSAGE_ERROR_POSITION);
                }
                else Streamer_Update(playerid);
            }
        }
	}
	return 1;
}

hook OnPlayerLogin(playerid)
{
    foreach(new i : Boombox)
    {
        if(Boombox[i][boombox_ACCOUNT_ID] == PI[playerid][pi_ID])
        {
            if(Boombox[i][boombox_DESTROY_TIMER] != Timer:-1)
            {
                stop Boombox[i][boombox_DESTROY_TIMER];
                Boombox[i][boombox_DESTROY_TIMER] = Timer:-1;
            }
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    foreach(new i : Boombox)
    {
        if(Boombox[i][boombox_ACCOUNT_ID] == PI[playerid][pi_ID])
        Boombox[i][boombox_DESTROY_TIMER] = defer DestroyBoombox_Timer(i);
    }
    return 1;
}

timer DestroyBoombox_Timer[DISCONNECTED_PLAYER_BOOMBOX_TIME](index)
{
    Boombox[index][boombox_DESTROY_TIMER] = Timer:-1;
    DestroyBoombox(index);
}