loadtext lang[tutorial];

DestroyTutorialTds(playerid)
{
    if(pTutorialBoxTd[playerid] != PlayerText:INVALID_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, pTutorialBoxTd[playerid]);
        pTutorialBoxTd[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    for(new i = 0; i < MAX_TUTORIAL_BOX_STEPS; i ++)
    {
        pTutorialSteps[playerid][i] = false;
        if(pTutorialStepTd[playerid][i][0] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, pTutorialStepTd[playerid][i][0]);
            pTutorialStepTd[playerid][i][0] = PlayerText:INVALID_TEXT_DRAW;
        }
        if(pTutorialStepTd[playerid][i][1] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, pTutorialStepTd[playerid][i][1]);
            pTutorialStepTd[playerid][i][1] = PlayerText:INVALID_TEXT_DRAW;
        }
    }
    return 1;
}

DestroyTutorial(playerid)
{
    if(pTutorialTimer[playerid] != Timer:-1)
	{
		stop pTutorialTimer[playerid];
		pTutorialTimer[playerid] = Timer:-1;
	}
	HidePlayerAuxTextDraw(playerid);
    HidePlayerInfoMessage(playerid);
    pTutorialCheck[playerid] = false;
    pInTutorial[playerid] = TutorialFlags:0;
    DestroyTutorialTds(playerid);
    return 1;
}

CreateTutorialTds(playerid, steps)
{
    if(steps > MAX_TUTORIAL_BOX_STEPS) return 0;
    DestroyTutorialTds(playerid);

    new Float:size_y = TUTORIAL_BOX_MARGIN * 2;
    for(new i = 0; i < steps; i ++)
    size_y += (TUTORIAL_BOX_LY * 10.0) + TUTORIAL_BOX_PADDING;
    size_y -= TUTORIAL_BOX_PADDING;

    pTutorialBoxTd[playerid] = CreatePlayerTextDraw(playerid, TUTORIAL_BOX_X, TUTORIAL_BOX_Y, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, pTutorialBoxTd[playerid], TUTORIAL_BOX_SX, size_y);
    PlayerTextDrawAlignment(playerid, pTutorialBoxTd[playerid], 1);
    PlayerTextDrawColor(playerid, pTutorialBoxTd[playerid], 255);
    PlayerTextDrawSetShadow(playerid, pTutorialBoxTd[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, pTutorialBoxTd[playerid], 255);
    PlayerTextDrawFont(playerid, pTutorialBoxTd[playerid], 4);
    PlayerTextDrawSetProportional(playerid, pTutorialBoxTd[playerid], 0);
    SetPlayerTextDrawLayer(playerid, pTutorialBoxTd[playerid], LAYER_TUTORIAL);
    PlayerTextDrawShow(playerid, pTutorialBoxTd[playerid]);

    new Float:pos_y = TUTORIAL_BOX_Y + TUTORIAL_BOX_MARGIN;
    for(new i = 0; i < steps; i ++)
    {
        pTutorialStepTd[playerid][i][0] = CreatePlayerTextDraw(playerid, TUTORIAL_BOX_X + TUTORIAL_BOX_MARGIN, pos_y, ""TEXTDRAW_CUSTOM_PATH"tick_no");
        PlayerTextDrawTextSize(playerid, pTutorialStepTd[playerid][i][0], 7.0, 9.0);
        PlayerTextDrawAlignment(playerid, pTutorialStepTd[playerid][i][0], 1);
        PlayerTextDrawColor(playerid, pTutorialStepTd[playerid][i][0], -1);
        PlayerTextDrawSetShadow(playerid, pTutorialStepTd[playerid][i][0], 0);
        PlayerTextDrawBackgroundColor(playerid, pTutorialStepTd[playerid][i][0], 255);
        PlayerTextDrawFont(playerid, pTutorialStepTd[playerid][i][0], 4);
        PlayerTextDrawSetProportional(playerid, pTutorialStepTd[playerid][i][0], 0);
        SetPlayerTextDrawLayer(playerid, pTutorialStepTd[playerid][i][0], LAYER_TUTORIAL);

        pTutorialStepTd[playerid][i][1] = CreatePlayerTextDraw(playerid, TUTORIAL_BOX_X + TUTORIAL_BOX_MARGIN + 7.0 + TUTORIAL_BOX_PADDING, pos_y, "_");
        PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][i][1], 0.1, TUTORIAL_BOX_LY);
        PlayerTextDrawTextSize(playerid, pTutorialStepTd[playerid][i][1], TUTORIAL_BOX_X + TUTORIAL_BOX_MARGIN + 7.0 + TUTORIAL_BOX_PADDING + TutorialBoxLetterSizeX, 0.000000);
        PlayerTextDrawAlignment(playerid, pTutorialStepTd[playerid][i][1], 1);
        PlayerTextDrawColor(playerid, pTutorialStepTd[playerid][i][1], -1);
        PlayerTextDrawSetShadow(playerid, pTutorialStepTd[playerid][i][1], 0);
        PlayerTextDrawBackgroundColor(playerid, pTutorialStepTd[playerid][i][1], 255);
        PlayerTextDrawFont(playerid, pTutorialStepTd[playerid][i][1], 1);
        PlayerTextDrawSetProportional(playerid, pTutorialStepTd[playerid][i][1], 1);
        SetPlayerTextDrawLayer(playerid, pTutorialStepTd[playerid][i][1], LAYER_TUTORIAL);

        PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][i][0]);
        PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][i][1]);
        pos_y += (TUTORIAL_BOX_LY * 10.0) + TUTORIAL_BOX_PADDING;
    }
    return 1;
}

CheckAndStartVehicleTutorial(playerid, vehindex)
{
    if(vehindex == INVALID_VEHICLE_INDEX) return 0;
    if((PI[playerid][pi_TUTORIAL] & TUTORIAL_1) && (PI[playerid][pi_TUTORIAL] & TUTORIAL_2) && (PI[playerid][pi_TUTORIAL] & TUTORIAL_3)) //inicial completado
    {
        if(!(PI[playerid][pi_TUTORIAL] & TUTORIAL_7) && pInTutorial[playerid] == TutorialFlags:0)
        {
            if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && HasPlayerAccessToVehicle(playerid, vehindex) && VehicleModelHasEngine(VehicleInfo[vehindex][vinfo_MODELID]))
            {
                pInTutorial[playerid] = TUTORIAL_7;
                if(VehicleModelHasDoors(VehicleInfo[vehindex][vinfo_MODELID]))
                {
                    CreateTutorialTds(playerid, 4);
                    pCarTutorialDoors[playerid] = true;
                }
                else
                {
                    CreateTutorialTds(playerid, 3);
                    pCarTutorialDoors[playerid] = false;
                }
                FormatTutorialTds(playerid, TUTORIAL_7);
            }
        }
    }
    return 1;
}

FormatTutorialTds(playerid, TutorialFlags:step)
{
    new string[256], Float:letterX;
    switch(step)
    {
        case TUTORIAL_1:
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_1_OBJECTIVE, ACTION_KEY_STR);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][0][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][0][1]);

            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_2_OBJECTIVE);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][1][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][1][1]);

            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_3_OBJECTIVE, KEY_SHOW_PSTATS_STR);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][2][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][2][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][2][1]);
        }
        case TUTORIAL_2:
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_4_OBJECTIVE);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][0][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][0][1]);

            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_5_OBJECTIVE);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][1][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][1][1]);
        }
        case TUTORIAL_3:
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_6_OBJECTIVE);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][0][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][0][1]);

            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_7_OBJECTIVE);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][1][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][1][1]);
        }
        case TUTORIAL_4:
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_8_OBJECTIVE);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][0][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][0][1]);

            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_9_OBJECTIVE, "~k~~PED_SPRINT~");
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][1][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][1][1]);

            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_10_OBJECTIVE, "~k~~VEHICLE_ENTER_EXIT~");
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][2][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][2][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][2][1]);
        }
        case TUTORIAL_5:
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_11_OBJECTIVE);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][0][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][0][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][0][1]);

            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_12_OBJECTIVE);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][1][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][1][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][1][1]);
        }
        case TUTORIAL_7:
        {
            new count;

            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_13_OBJECTIVE);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][count][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][count][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][count][1]);
            count ++;

            if(pCarTutorialDoors[playerid])
            {
                Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_14_OBJECTIVE);
                letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
                if(letterX > 0.23) letterX = 0.23;
                PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][count][1], letterX, TUTORIAL_BOX_LY);
                PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][count][1], string);
                PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][count][1]);
                count ++;
            }

            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_15_OBJECTIVE);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][count][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][count][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][count][1]);
            count ++;

            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_16_OBJECTIVE);
            letterX = GetTdTextFontX(1, string, true, 0.0, TutorialBoxLetterSizeX);
            if(letterX > 0.23) letterX = 0.23;
            PlayerTextDrawLetterSize(playerid, pTutorialStepTd[playerid][count][1], letterX, TUTORIAL_BOX_LY);
            PlayerTextDrawSetString(playerid, pTutorialStepTd[playerid][count][1], string);
            PlayerTextDrawShow(playerid, pTutorialStepTd[playerid][count][1]);
            count ++;
        }
    }
    PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
	return 1;
}

FormatTutorialMsg(playerid, id)
{
    new string[256];
    switch(id)
    {
        case 0:
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_1_MESSAGE);
            ShowPlayerAuxTextDraw(playerid, string);
        }
        case 1: 
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_2_MESSAGE);
            ShowPlayerInfoMessage(playerid, string, 5, false);
        }
        case 2: 
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_3_MESSAGE);
            ShowPlayerInfoMessage(playerid, string, 5, false);
        }
        case 3: 
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_4_MESSAGE);
            ShowPlayerAuxTextDraw(playerid, string);
        }
        case 4: 
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_5_MESSAGE);
            ShowPlayerInfoMessage(playerid, string, 5, false);
        }
        case 5: 
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_6_MESSAGE);
            ShowPlayerInfoMessage(playerid, string, 5, false);
        }
        case 6: 
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_7_MESSAGE);
            ShowPlayerAuxTextDraw(playerid, string);
        }
        case 7: 
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_8_MESSAGE);
            ShowPlayerAuxTextDraw(playerid, string);
        }
        case 8: 
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_9_MESSAGE);
            ShowPlayerInfoMessage(playerid, string);
        }
        case 9: 
        {
            Text_Format_TD(string, sizeof string, PI[playerid][pi_LANG_ID], $TUTORIAL_10_MESSAGE);
            ShowPlayerInfoMessage(playerid, string, 10);
        }
    }
    return 1;
}