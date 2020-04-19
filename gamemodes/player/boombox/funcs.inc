CreateBoombox(Float:x, Float:y, Float:z, url[] = "", playing[] = "", Float:distance = DEFAULT_BOOMBOX_DISTANCE, modelid = 2226, interiorid = 0, worldid = 0, playerid = INVALID_PLAYER_ID, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0)
{
    new index = Iter_Free(Boombox);
    if(index != cellmin)
    {
        if(playerid != INVALID_PLAYER_ID)
        {
            if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
            return INVALID_BOOMBOX_ID;
            
            if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_PROPERTY)
            {
                if(PropertyInfo[ PI[playerid][pi_WORLD_STATE_INDEX] ][property_ID_PLAYER] != PI[playerid][pi_ID])
                return INVALID_BOOMBOX_ID;
            }
            else if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_BUSINESS)
            {
                if(BusinessData[ PI[playerid][pi_WORLD_STATE_INDEX] ][bdata_ID_PLAYER] != PI[playerid][pi_ID])
                return INVALID_BOOMBOX_ID;
            }
            else if(PI[playerid][pi_WORLD_STATE] != PLAYER_WORLD_STATE_STREET)
            return INVALID_BOOMBOX_ID;
            
        }

        foreach(new i : Boombox)
        {
            if(Boombox[i][boombox_INTERIORID] != interiorid) continue;
            if(Boombox[i][boombox_WORLDID] != worldid) continue;
            
            new Float:distance2 = GetDistanceBetweenPoints3D(Boombox[i][boombox_X], Boombox[i][boombox_Y], Boombox[i][boombox_Z], x, y, z);
            if(distance2 <= (Boombox[i][boombox_DISTANCE] + MIN_DISTANCE_BETWEEN_BOOMBOXS + BOOMBOX_OFFSET_DISTANCE))
            return INVALID_BOOMBOX_ID;
        }

        format(Boombox[index][boombox_URL], 256, url);
        format(Boombox[index][boombox_PLAYING], 128, playing);
        if(playerid == INVALID_PLAYER_ID) Boombox[index][boombox_ACCOUNT_ID] = 0;
        else Boombox[index][boombox_ACCOUNT_ID] = PI[playerid][pi_ID];
        Boombox[index][boombox_MODELID] = modelid;
        Boombox[index][boombox_X] = x;
        Boombox[index][boombox_Y] = y;
        Boombox[index][boombox_Z] = z;
        Boombox[index][boombox_RX] = rx;
        Boombox[index][boombox_RY] = ry;
        Boombox[index][boombox_RZ] = rz;
        Boombox[index][boombox_DISTANCE] = distance;
        Boombox[index][boombox_INTERIORID] = interiorid;
        Boombox[index][boombox_WORLDID] = worldid;

        new streamer_info[2];
        Boombox[index][boombox_OBJECTID] = CreateDynamicObject(modelid, x, y, z, rx, ry, rz, worldid, interiorid);
        streamer_info[0] = _:OBJECT_TYPE_BOOMBOX;
        streamer_info[1] = index;
        Streamer_SetArrayData(STREAMER_TYPE_OBJECT, Boombox[index][boombox_OBJECTID], E_STREAMER_EXTRA_ID, streamer_info);

        Boombox[index][boombox_PLAY_AREAID] = CreateDynamicSphere(x, y, z, distance + BOOMBOX_OFFSET_DISTANCE, worldid, interiorid);
        streamer_info[0] = _:AREA_TYPE_PLAY_BOOMBOX;
        streamer_info[1] = index;
        Streamer_SetArrayData(STREAMER_TYPE_AREA, Boombox[index][boombox_PLAY_AREAID], E_STREAMER_EXTRA_ID, streamer_info);

        Boombox[index][boombox_LABEL_AREAID] = CreateDynamicCylinder(x, y, z - PLAYER_LABEL_DISTANCE, z + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, worldid, interiorid);
        streamer_info[0] = _:AREA_TYPE_LABEL_BOOMBOX;
        streamer_info[1] = index;
        Streamer_SetArrayData(STREAMER_TYPE_AREA, Boombox[index][boombox_LABEL_AREAID], E_STREAMER_EXTRA_ID, streamer_info);

        Boombox[index][boombox_AREAID] = CreateDynamicCylinder(x, y, z - 1.0, z + 3.0, 1.0, worldid, interiorid);
        streamer_info[0] = _:AREA_TYPE_BOOMBOX;
        streamer_info[1] = index;
        Streamer_SetArrayData(STREAMER_TYPE_AREA, Boombox[index][boombox_AREAID], E_STREAMER_EXTRA_ID, streamer_info);

        Boombox[index][boombox_DESTROY_TIMER] = Timer:-1;
        Iter_Add(Boombox, index);
        return index;
    }
    return INVALID_BOOMBOX_ID;
}

SetBoomboxPos(index, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0)
{
    if(IsValidBoombox(index))
    {
        if(!isnull(Boombox[index][boombox_URL]))
        return 0;

        foreach(new i : Boombox)
        {
            if(i == index) continue;
            if(Boombox[i][boombox_INTERIORID] != Boombox[index][boombox_INTERIORID]) continue;
            if(Boombox[i][boombox_WORLDID] != Boombox[index][boombox_WORLDID]) continue;
            
            new Float:distance2 = GetDistanceBetweenPoints3D(Boombox[i][boombox_X], Boombox[i][boombox_Y], Boombox[i][boombox_Z], x, y, z);
            if(distance2 <= (Boombox[i][boombox_DISTANCE] + MIN_DISTANCE_BETWEEN_BOOMBOXS + BOOMBOX_OFFSET_DISTANCE))
            return 0;
        }

        Boombox[index][boombox_X] = x;
        Boombox[index][boombox_Y] = y;
        Boombox[index][boombox_Z] = z;
        Boombox[index][boombox_RX] = rx;
        Boombox[index][boombox_RY] = ry;
        Boombox[index][boombox_RZ] = rz;
        SetDynamicObjectPos(Boombox[index][boombox_OBJECTID], Boombox[index][boombox_X], Boombox[index][boombox_Y], Boombox[index][boombox_Z]);
        SetDynamicObjectRot(Boombox[index][boombox_OBJECTID], Boombox[index][boombox_RX], Boombox[index][boombox_RY], Boombox[index][boombox_RZ]);

        Streamer_SetFloatData(STREAMER_TYPE_AREA, Boombox[index][boombox_PLAY_AREAID], E_STREAMER_X, x);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, Boombox[index][boombox_PLAY_AREAID], E_STREAMER_Y, y);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, Boombox[index][boombox_PLAY_AREAID], E_STREAMER_Z, z);

        Streamer_SetFloatData(STREAMER_TYPE_AREA, Boombox[index][boombox_LABEL_AREAID], E_STREAMER_X, x);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, Boombox[index][boombox_LABEL_AREAID], E_STREAMER_Y, y);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, Boombox[index][boombox_LABEL_AREAID], E_STREAMER_Z, z);

        Streamer_SetFloatData(STREAMER_TYPE_AREA, Boombox[index][boombox_AREAID], E_STREAMER_X, x);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, Boombox[index][boombox_AREAID], E_STREAMER_Y, y);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, Boombox[index][boombox_AREAID], E_STREAMER_Z, z);
        return 1;
    }
    return 0;
}

SetBoomboxAudio(index, audio[] = "", playing[] = "")
{
    if(IsValidBoombox(index))
    {
        new bool:was_off = false;
        if(isnull(Boombox[index][boombox_URL]) && !isnull(audio))
        was_off = true;

        format(Boombox[index][boombox_URL], 256, "%s", audio);
        format(Boombox[index][boombox_PLAYING], 128, "%s", playing);

        foreach(new i : Player)
        {
            if(IsPlayerInDynamicArea(i, Boombox[index][boombox_PLAY_AREAID], 1))
            {
                if(GetPlayerVehicleIndex(i) != INVALID_VEHICLE_INDEX && VehicleModelHasEngine(VehicleInfo[GetPlayerVehicleIndex(i)][vinfo_MODELID]))
                {
                    if(VehicleInfo[GetPlayerVehicleIndex(i)][vinfo_RADIO] != 0)
                    continue;
                }

                if(IsPlayerInDynamicArea(i, Boombox[index][boombox_LABEL_AREAID]))
                {
                    FormatBoomboxLabel(i, index);
                    Streamer_Update(i, STREAMER_TYPE_3D_TEXT_LABEL);
                }

                if(was_off)
                FormatEnvAreaMessage(i, ENV_AREA_TYPE_DANCE);

                if(isnull(audio)) StopAudioStreamForPlayer(i);
                else PlayAudioStreamForPlayer(i, audio, Boombox[index][boombox_X], Boombox[index][boombox_Y], Boombox[index][boombox_Z], Boombox[index][boombox_DISTANCE], 1);
            }
        }
        return 1;
    }
    return 0;
}

DestroyBoombox(index)
{
    if(IsValidBoombox(index))
    {
        foreach(new i : Player)
        {
            if(IsPlayerInDynamicArea(i, Boombox[index][boombox_PLAY_AREAID], 1))
            {
                if(GetPlayerVehicleIndex(i) != INVALID_VEHICLE_INDEX && VehicleModelHasEngine(VehicleInfo[GetPlayerVehicleIndex(i)][vinfo_MODELID]))
                {
                    if(VehicleInfo[GetPlayerVehicleIndex(i)][vinfo_RADIO] != 0)
                    continue;
                }

                StopAudioStreamForPlayer(i);
            }
        }

        if(Boombox[index][boombox_OBJECTID] != INVALID_STREAMER_ID)
        DestroyDynamicObject(Boombox[index][boombox_OBJECTID]);

        if(Boombox[index][boombox_PLAY_AREAID] != INVALID_STREAMER_ID)
        DestroyDynamicArea(Boombox[index][boombox_PLAY_AREAID]);

        if(Boombox[index][boombox_LABEL_AREAID] != INVALID_STREAMER_ID)
        DestroyDynamicArea(Boombox[index][boombox_LABEL_AREAID]);

        if(Boombox[index][boombox_AREAID] != INVALID_STREAMER_ID)
        DestroyDynamicArea(Boombox[index][boombox_AREAID]);

        if(Boombox[index][boombox_DESTROY_TIMER] != Timer:-1)
        stop Boombox[index][boombox_DESTROY_TIMER];

        new tmp_Boombox[E_Boombox];
        Boombox[index] = tmp_Boombox;

        Iter_Remove(Boombox, index);
        return 1;
    }
    return 0;
}