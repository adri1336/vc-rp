#include <YSI\y_hooks>

hook OnScriptInit()
{
    TutorialBoxLetterSizeX = TUTORIAL_BOX_SX - (TUTORIAL_BOX_MARGIN + 7.0 + TUTORIAL_BOX_PADDING) - TUTORIAL_BOX_MARGIN;
}

hook OnPlayerConnect(playerid)
{
    pTutorialCheck[playerid] = false;
    pInTutorial[playerid] = TutorialFlags:0;

    for(new i = 0; i < MAX_TUTORIAL_BOX_STEPS; i ++)
    {
        pTutorialStepTd[playerid][i][0] = PlayerText:INVALID_TEXT_DRAW;
        pTutorialStepTd[playerid][i][1] = PlayerText:INVALID_TEXT_DRAW;
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    DestroyTutorialTds(playerid);
    if(pTutorialTimer[playerid] != Timer:-1)
	{
		stop pTutorialTimer[playerid];
		pTutorialTimer[playerid] = Timer:-1;
	}
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    DestroyTutorial(playerid);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_SPECTATING || newstate == PLAYER_STATE_WASTED)
    {
        DestroyTutorial(playerid);
    }
    else if(oldstate == PLAYER_STATE_DRIVER)
    {
        if(pInTutorial[playerid] == TUTORIAL_7)
        DestroyTutorial(playerid);
    }
	return 1;
}


hook OnPlayerSpawn(playerid)
{
    pTutorialCheck[playerid] = true;
    return 1;
}

hook OnPlayerLoadScreenFin(playerid)
{
    if(pTutorialCheck[playerid])
    {
        pTutorialCheck[playerid] = false;
        if(!(PI[playerid][pi_TUTORIAL] & TUTORIAL_1))
        {
            SetPlayerPos(playerid, New_User_Pos[0], New_User_Pos[1], New_User_Pos[2]);
            SetPlayerFacingAngle(playerid, New_User_Pos[3]);

            pInTutorial[playerid] = TUTORIAL_1;
            TogglePlayerControllable(playerid, false);
            CreateTutorialTds(playerid, 3);
            FormatTutorialTds(playerid, TUTORIAL_1);
            SetCameraBehindPlayer(playerid);
        }
        else if(!(PI[playerid][pi_TUTORIAL] & TUTORIAL_2))
        {
            if(!pTutorialSteps[playerid][0] && !pTutorialSteps[playerid][1])
            {
                SetPlayerPos(playerid, New_User_Pos[0], New_User_Pos[1], New_User_Pos[2]);
                SetPlayerFacingAngle(playerid, New_User_Pos[3]);

                pInTutorial[playerid] = TUTORIAL_2;
                CreateTutorialTds(playerid, 2);
                FormatTutorialTds(playerid, TUTORIAL_2);
                SetCameraBehindPlayer(playerid);
            }
            else if(!pTutorialSteps[playerid][1])
            {
                TogglePlayerControllable(playerid, false);
                //cp
                if(pNewuserCP[playerid] != INVALID_STREAMER_ID)
                {
                    DestroyDynamicCP(pNewuserCP[playerid]);
                    pNewuserCP[playerid] = INVALID_STREAMER_ID;
                }
                pNewuserCP[playerid] = CreateDynamicCP(6471.015625, 2173.599121, 1219.028442, 1.0, .playerid = playerid, .streamdistance = 500.0);
                Streamer_SetIntData(STREAMER_TYPE_CP, pNewuserCP[playerid], E_STREAMER_EXTRA_ID, _:CHECKPOINT_TYPE_NEWUSER);
                Streamer_Update(playerid, STREAMER_TYPE_CP);

                SetPlayerCameraPos(playerid, 6420.463867, 2151.202636, 1224.878051);
                SetPlayerCameraLookAt(playerid, 6421.342285, 2151.639892, 1224.685302);
                DisablePlayerLayers(playerid, LAYER_MESSAGES);
                FormatTutorialMsg(playerid, 3);
                PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

                pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 2);
            }
            else if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1])
            {
                TogglePlayerControllable(playerid, false);
                PlayerTextDrawShow(playerid, pTutorialBoxTd[playerid]);
                PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][0][0]);
                PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][0][1]);
                PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][1][0]);
                PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][1][1]);
                PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

                pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 4);
            }
        }
    }
	return 1;
}

hook OnPlayerOpenInventory(playerid)
{
    if(pInTutorial[playerid] == TUTORIAL_1)
    {
        if(!pTutorialSteps[playerid][0])
        {
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][0] = true;

            if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2])
            pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 0);
        }
    }
    return 1;
}

hook OnPlayerCloseInventory(playerid)
{
    if(pInTutorial[playerid] == TUTORIAL_1)
    {
        if(!pTutorialSteps[playerid][1])
        {
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][1] = true;

            if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2])
            pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 0);
        }
    }
    return 1;
}

hook OnPlayerCloseStatsTds(playerid)
{
    if(pInTutorial[playerid] == TUTORIAL_1)
    {
        if(!pTutorialSteps[playerid][2])
        {
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][2][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][2] = true;
            
            if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2])
            pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 0);
        }
    }
    return 1;
}

hook OnPlayerGetVehicleIndex(playerid)
{
    if(pInTutorial[playerid] == TUTORIAL_2 && !pTutorialSteps[playerid][0])
    {
        if(VehicleInfo[pVehicleIndex[playerid]][vinfo_TYPE] == VEHICLE_TYPE_FREE)
        {
            if(Model_IsBike(VehicleInfo[pVehicleIndex[playerid]][vinfo_MODELID]))
            {
                PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
                pTutorialSteps[playerid][0] = true;

                DestroyPlayerRoute(playerid, 1);
				CalcRoute(playerid, Interest_Coords[2][0], Interest_Coords[2][1], Interest_Coords[2][2], true);
                FormatTutorialMsg(playerid, 1);
            }
        }
        else if(VehicleInfo[pVehicleIndex[playerid]][vinfo_TYPE] == VEHICLE_TYPE_AUTOPILOT)
        {
            if(Model_IsTaxi(VehicleInfo[pVehicleIndex[playerid]][vinfo_MODELID]))
            {
                new vehicleid = VehicleInfo[pVehicleIndex[playerid]][vinfo_VEHICLE_ID];
                if(!ApVehicleInfo[vehicleid][apv_InPath] && (pAutoPilotVehicleId[playerid] == INVALID_VEHICLE_ID || pAutoPilotVehicleId[playerid] == vehicleid) && (ApVehicleInfo[vehicleid][apv_CreatedBy] == INVALID_PLAYER_ID || ApVehicleInfo[vehicleid][apv_CreatedBy] == playerid))
                {
                    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                    PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
                    pTutorialSteps[playerid][0] = true;

                    AutoPilotVehicleGoTo(playerid, vehicleid, Interest_Coords[2][0], Interest_Coords[2][1], Interest_Coords[2][2]);
                    FormatTutorialMsg(playerid, 2);

                    //cp north point
                    if(pNewuserCP[playerid] != INVALID_STREAMER_ID)
                    {
                        DestroyDynamicCP(pNewuserCP[playerid]);
                        pNewuserCP[playerid] = INVALID_STREAMER_ID;
                    }
                    pNewuserCP[playerid] = CreateDynamicCP(6478.805175, 2174.357421, 11.998143, 1.0, .playerid = playerid, .streamdistance = 500.0);
                    Streamer_SetIntData(STREAMER_TYPE_CP, pNewuserCP[playerid], E_STREAMER_EXTRA_ID, _:CHECKPOINT_TYPE_NEWUSER);
                    Streamer_Update(playerid, STREAMER_TYPE_CP);
                }   
            }
        }
    }
    else
    {
        CheckAndStartVehicleTutorial(playerid, pVehicleIndex[playerid]);
    }
    return 1;
}

hook OnPlayerWStateChange(playerid, PLAYER_WORLD_STATES:worldstate, index, extra_index)
{
    if(pInTutorial[playerid] == TUTORIAL_2 && !pTutorialSteps[playerid][1])
    {
        if(worldstate == PLAYER_WORLD_STATE_ENTRANCE && Entrances[index][entrance_ID_ENTRANCE] == 7) //north point
        {
            PlayerTextDrawHide(playerid, pTutorialBoxTd[playerid]);
            PlayerTextDrawHide(playerid, pTutorialStepTd[playerid][0][0]);
            PlayerTextDrawHide(playerid, pTutorialStepTd[playerid][0][1]);
            PlayerTextDrawHide(playerid, pTutorialStepTd[playerid][1][0]);
            PlayerTextDrawHide(playerid, pTutorialStepTd[playerid][1][1]);
            pTutorialSteps[playerid][0] = true;
            pTutorialCheck[playerid] = true;
        }
        else if(worldstate == PLAYER_WORLD_STATE_BUSINESS && BusinessData[index][bdata_ID_TYPE] == BUSINESS_TYPE_ELECTRONICS)
        {
            PlayerTextDrawHide(playerid, pTutorialBoxTd[playerid]);
            PlayerTextDrawHide(playerid, pTutorialStepTd[playerid][0][0]);
            PlayerTextDrawHide(playerid, pTutorialStepTd[playerid][0][1]);
            PlayerTextDrawHide(playerid, pTutorialStepTd[playerid][1][0]);
            PlayerTextDrawHide(playerid, pTutorialStepTd[playerid][1][1]);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][0] = true;
            pTutorialSteps[playerid][1] = true;
            pTutorialCheck[playerid] = true;
        }
    }
    return 1;
}

hook OnPlayerItemAdded(playerid, index, item_id, amount)
{
    if(pInTutorial[playerid] == TUTORIAL_3)
    {
        if(item_id == _:INV_ITEM_PHONE && !pTutorialSteps[playerid][0])
        {
            FormatTutorialMsg(playerid, 5);
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][0] = true;

            if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1])
            {
                TogglePlayerControllable(playerid, false);
                pTutorialTimer[playerid] = defer ContinuePlayerTutorial[6000](playerid, 5);
            }
        }
        else if(item_id == _:INV_ITEM_GPS && !pTutorialSteps[playerid][1])
        {
            FormatTutorialMsg(playerid, 4);
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][1] = true;

            if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1])
            {
                TogglePlayerControllable(playerid, false);
                pTutorialTimer[playerid] = defer ContinuePlayerTutorial[6000](playerid, 5);
            }
        }
    }
    else
    {
        if(item_id == _:INV_ITEM_VEHICLE_RENT_KEY)
        CheckAndStartVehicleTutorial(playerid, pVehicleIndex[playerid]);
    }
    return 1;
}

hook OnPlayerOpenPhone(playerid, bool:calling)
{
    if(!calling)
    {
        if((PI[playerid][pi_TUTORIAL] & TUTORIAL_1) && (PI[playerid][pi_TUTORIAL] & TUTORIAL_2) && (PI[playerid][pi_TUTORIAL] & TUTORIAL_3)) //inicial completado
        {
            if(!(PI[playerid][pi_TUTORIAL] & TUTORIAL_4) && pInTutorial[playerid] == TutorialFlags:0)
            {
                pInTutorial[playerid] = TUTORIAL_4;
                CreateTutorialTds(playerid, 3);
                FormatTutorialTds(playerid, TUTORIAL_4);
            }
        }
    }
    return 1;
}

hook OnPlayerClosePhone(playerid)
{
    if(pInTutorial[playerid] == TUTORIAL_4)
    DestroyTutorial(playerid);
    return 1;
}

hook OnPlayerUpdate(playerid)
{
    if(pInTutorial[playerid] == TUTORIAL_4)
    {
        new Keys, ud, lr;
        GetPlayerKeys(playerid, Keys, ud, lr);
        if(!pTutorialSteps[playerid][0])
        {
            if(ud == KEY_UP || ud == KEY_DOWN)
            {
                PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
                pTutorialSteps[playerid][0] = true;

                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_4;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 8);
                }
            }
        }
        if(!pTutorialSteps[playerid][1] && Keys == KEY_SPRINT)
        {
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][1] = true;

            if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2])
            {
                PI[playerid][pi_TUTORIAL] |= TUTORIAL_4;
                pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 8);
            }
        }
        if(!pTutorialSteps[playerid][2] && Keys == KEY_SECONDARY_ATTACK)
        {
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][2][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][2] = true;

            if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2])
            {
                PI[playerid][pi_TUTORIAL] |= TUTORIAL_4;
                pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 8);
            }
        }
    }
    return 1;
}

hook OnPlayerOpenGps(playerid)
{
    if((PI[playerid][pi_TUTORIAL] & TUTORIAL_1) && (PI[playerid][pi_TUTORIAL] & TUTORIAL_2) && (PI[playerid][pi_TUTORIAL] & TUTORIAL_3)) //inicial completado
    {
        if(!(PI[playerid][pi_TUTORIAL] & TUTORIAL_5) && pInTutorial[playerid] == TutorialFlags:0)
        {
            pInTutorial[playerid] = TUTORIAL_5;
            CreateTutorialTds(playerid, 2);
            FormatTutorialTds(playerid, TUTORIAL_5);
        }
    }
}

hook OnPlayerToggleMinimap(playerid, bool:toogle)
{
    if(pInTutorial[playerid] == TUTORIAL_5 && !pTutorialSteps[playerid][0])
    {
        if(toogle)
        {
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][0] = true;
        }
    }
    return 1;
}

hook OnPlayerCloseGps(playerid)
{
    if(pInTutorial[playerid] == TUTORIAL_5)
    {
        if(!pTutorialSteps[playerid][1])
        {
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][1] = true;

            if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1])
            PI[playerid][pi_TUTORIAL] |= TUTORIAL_5;

            pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 8);
        }
    }
    return 1;
}

hook OnPlayerGetClothes(playerid)
{
    if((PI[playerid][pi_TUTORIAL] & TUTORIAL_1) && (PI[playerid][pi_TUTORIAL] & TUTORIAL_2) && (PI[playerid][pi_TUTORIAL] & TUTORIAL_3)) //inicial completado
    {
        if(!(PI[playerid][pi_TUTORIAL] & TUTORIAL_6) && pInTutorial[playerid] == TutorialFlags:0)
        {
            FormatTutorialMsg(playerid, 8);
            PI[playerid][pi_TUTORIAL] |= TUTORIAL_6;
        }
    }
    return 1;
}

hook OnPlayerOpenVehicle(playerid, modelid)
{
    if(pInTutorial[playerid] == TUTORIAL_7)
    {
        if(pCarTutorialDoors[playerid])
        {
            if(!pTutorialSteps[playerid][1])
            {
                PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
                pTutorialSteps[playerid][1] = true;

                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2] && pTutorialSteps[playerid][3])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 8);
                }
            }
        }
    }
    return 1;
}

hook OnPlayerCloseVehicle(playerid, modelid)
{
    if(pInTutorial[playerid] == TUTORIAL_7)
    {
        if(pCarTutorialDoors[playerid])
        {
            if(!pTutorialSteps[playerid][1])
            {
                PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
                pTutorialSteps[playerid][1] = true;

                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2] && pTutorialSteps[playerid][3])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 8);
                }
            }
        }
    }
    return 1;
}

hook OnPlayerStartVehicle(playerid, modelid)
{
    if(pInTutorial[playerid] == TUTORIAL_7)
    {
        if(!pTutorialSteps[playerid][0])
        {
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][0] = true;

            if(pCarTutorialDoors[playerid])
            {
                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2] && pTutorialSteps[playerid][3])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 8);
                }
            }
            else
            {
                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 9);
                }
            }
        }
    }
    return 1;
}

hook OnPlayerStopVehicle(playerid, modelid)
{
    if(pInTutorial[playerid] == TUTORIAL_7)
    {
        if(!pTutorialSteps[playerid][0])
        {
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
            pTutorialSteps[playerid][0] = true;

            if(pCarTutorialDoors[playerid])
            {
                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2] && pTutorialSteps[playerid][3])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 8);
                }
            }
            else
            {
                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 9);
                }
            }
        }
    }
    return 1;
}

hook OnPlayerVehicleLightsOn(playerid, modelid)
{
    if(pInTutorial[playerid] == TUTORIAL_7)
    {
        if(pCarTutorialDoors[playerid])
        {
            if(!pTutorialSteps[playerid][2])
            {
                PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][2][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
                pTutorialSteps[playerid][2] = true;

                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2] && pTutorialSteps[playerid][3])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 8);
                }
            }
        }
        else
        {
            if(!pTutorialSteps[playerid][1])
            {
                PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
                pTutorialSteps[playerid][1] = true;

                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 9);
                }
            } 
        }
    }
    return 1;
}

hook OnPlayerVehicleLiOff(playerid, modelid)
{
    if(pInTutorial[playerid] == TUTORIAL_7)
    {
        if(pCarTutorialDoors[playerid])
        {
            if(!pTutorialSteps[playerid][2])
            {
                PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][2][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
                pTutorialSteps[playerid][2] = true;

                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2] && pTutorialSteps[playerid][3])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 8);
                }
            }
        }
        else
        {
            if(!pTutorialSteps[playerid][1])
            {
                PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
                pTutorialSteps[playerid][1] = true;

                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 9);
                }
            } 
        }
    }
    return 1;
}

hook OnPlayerChangeVRadio(playerid, vehindex, radio)
{
    if(pInTutorial[playerid] == TUTORIAL_7)
    {
        if(pCarTutorialDoors[playerid])
        {
            if(!pTutorialSteps[playerid][3])
            {
                PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][3][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
                pTutorialSteps[playerid][3] = true;

                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2] && pTutorialSteps[playerid][3])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 8);
                }
            }
        }
        else
        {
            if(!pTutorialSteps[playerid][2])
            {
                PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][2][0], ""TEXTDRAW_CUSTOM_PATH"tick_yes");
                pTutorialSteps[playerid][2] = true;

                if(pTutorialSteps[playerid][0] && pTutorialSteps[playerid][1] && pTutorialSteps[playerid][2])
                {
                    PI[playerid][pi_TUTORIAL] |= TUTORIAL_7;
                    pTutorialTimer[playerid] = defer ContinuePlayerTutorial[2000](playerid, 9);
                }
            } 
        }
    }
    return 1;
}

timer ContinuePlayerTutorial[2000](playerid, id)
{
	pTutorialTimer[playerid] = Timer:-1;
    switch(id)
    {
        case 0:
        {
            DestroyTutorialTds(playerid);
            DisablePlayerLayers(playerid, LAYER_MESSAGES);
            SetPlayerCameraPos(playerid, 4600.012207, 242.379348, 10.473366);
            SetPlayerCameraLookAt(playerid, 4599.289550, 241.699630, 10.347148);
            FormatTutorialMsg(playerid, 0);
            PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
            pTutorialTimer[playerid] = defer ContinuePlayerTutorial[4000](playerid, 1);
        }
        case 1:
        {
            EnablePlayerLayers(playerid);
            HidePlayerAuxTextDraw(playerid);
            SetCameraBehindPlayer(playerid);

            PI[playerid][pi_TUTORIAL] |= TUTORIAL_1;
            
            pInTutorial[playerid] = TUTORIAL_2;
            TogglePlayerControllable(playerid, true);
            CreateTutorialTds(playerid, 2);
            FormatTutorialTds(playerid, TUTORIAL_2);
        }
        case 2:
        {
            //cam
            new Float:pos[3], Float:angle;
            GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
            GetPlayerFacingAngle(playerid, angle);
            angle += float(random(15));

            new Float:cam_pos[3];
            cam_pos[0] = pos[0] + (10.0 * floatsin(-angle, degrees));
            cam_pos[1] = pos[1] + (10.0 * floatcos(-angle, degrees));
            cam_pos[2] = pos[2] + float(random(3));

            InterpolateCameraPos(playerid, 6420.463867, 2151.202636, 1224.878051, cam_pos[0], cam_pos[1], cam_pos[2], 5000, CAMERA_MOVE);
            InterpolateCameraLookAt(playerid, 6421.342285, 2151.639892, 1224.685302, pos[0], pos[1], pos[2], 5000, CAMERA_MOVE);
            
            pTutorialTimer[playerid] = defer ContinuePlayerTutorial[7000](playerid, 3);
        }
        case 3:
        {
            EnablePlayerLayers(playerid);
            HidePlayerAuxTextDraw(playerid);
            SetCameraBehindPlayer(playerid);
            PlayerTextDrawShow(playerid, pTutorialBoxTd[playerid]);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][0][0]);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][0][1]);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][1][0]);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][1][1]);
            TogglePlayerControllable(playerid, true);
        }
        case 4:
        {
            PI[playerid][pi_TUTORIAL] |= TUTORIAL_2;
            
            pInTutorial[playerid] = TUTORIAL_3;
            TogglePlayerControllable(playerid, true);
            CreateTutorialTds(playerid, 2);
            FormatTutorialTds(playerid, TUTORIAL_3);
        }
        case 5:
        {
            PI[playerid][pi_TUTORIAL] |= TUTORIAL_3;

            HidePlayerInfoMessage(playerid);
            pInTutorial[playerid] = TutorialFlags:0;
            DestroyTutorialTds(playerid);
            FormatTutorialMsg(playerid, 6);
            PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
            pTutorialTimer[playerid] = defer ContinuePlayerTutorial[10000](playerid, 6);
        }
        case 6:
        {
            FormatTutorialMsg(playerid, 7);
            pTutorialTimer[playerid] = defer ContinuePlayerTutorial[7000](playerid, 7);
        }
        case 7:
        {
            HidePlayerAuxTextDraw(playerid);
            TogglePlayerControllable(playerid, true);
            orm_update(PI[playerid][pi_ORM]);
        }
        case 8: DestroyTutorial(playerid);
        case 9:
        {
            DestroyTutorial(playerid);
            FormatTutorialMsg(playerid, 9);
        }
    }
}