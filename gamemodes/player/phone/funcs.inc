loadtext lang[phone];

DestroyPlayerPhone(playerid)
{
	if(pPhone_HourSignal_Timer[playerid] != Timer:-1)
	{
		stop pPhone_HourSignal_Timer[playerid];
		pPhone_HourSignal_Timer[playerid] = Timer:-1;
	}
	if(pPhone_Dialling_Timer[playerid] != Timer:-1)
	{
		stop pPhone_Dialling_Timer[playerid];
		pPhone_Dialling_Timer[playerid] = Timer:-1;
	}
	if(pPhone_Call_Timer[playerid] != Timer:-1)
	{
		stop pPhone_Call_Timer[playerid];
		pPhone_Call_Timer[playerid] = Timer:-1;
	}
	
	
	DestroyPlayerPhoneBaseTD(playerid);
	DestroyPlayerPhoneOptionsTD(playerid);
	DestroyPlayerPhoneAuxTD(playerid);
	DestroyPlayerPhoneKeyboardTD(playerid);

	pPhoneEnabled[playerid] = false;
	pPhonePage[playerid] = PHONE_PAGE_OFF;
	pPhoneOptionSelected[playerid] = 0;
	pPhoneEnableOPU[playerid] = false;
	pPhone_CallNumber_Str[playerid][0] = EOS;
	pPhone_Call_Time[playerid] = 0;
	pPhone_CallInfo[playerid][0] = 0;
	pPhone_CallInfo[playerid][1] = 0;
	pPhone_CallInfo[playerid][2] = 0;
	pPhoneBook_Offset[playerid] = 0;
	pPhoneBook_SelectedIndex[playerid] = 0;
	pPhoneBook_AddContact[playerid][0] = EOS;
	pPhoneBook_AddNumber[playerid] = 0;
	return 1;
}

DestroyPlayerPhoneBaseTD(playerid)
{
	for(new i = 0; i < sizeof pPhone_PTD_Base[]; i ++)
	{
		if(pPhone_PTD_Base[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pPhone_PTD_Base[playerid][i]);
			pPhone_PTD_Base[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

CreatePlayerPhoneBaseTds(playerid)
{
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], PHONE_TD_X, PHONE_TD_SIZE_X, true, pPhone_TD_X[playerid], pPhone_TD_SX[playerid]);
	pPhone_PTD_Base[playerid][0] = CreatePlayerTextDraw(playerid, pPhone_TD_X[playerid], PHONE_TD_Y, ""TEXTDRAW_CUSTOM_PATH"phone");
	PlayerTextDrawTextSize(playerid, pPhone_PTD_Base[playerid][0], pPhone_TD_SX[playerid], PHONE_TD_SIZE_Y);
	PlayerTextDrawColor(playerid, pPhone_PTD_Base[playerid][0], -1);
	PlayerTextDrawFont(playerid, pPhone_PTD_Base[playerid][0], 4);
	SetPlayerTextDrawLayer(playerid, pPhone_PTD_Base[playerid][0], LAYER_PHONE);

	new Float:result_x, Float:icon_size_x;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, PHONE_TD_SIGNAL_ICON_SIZE, false, result_x, icon_size_x);
	pPhone_PTD_Base[playerid][1] = CreatePlayerTextDraw(playerid, pPhone_TD_X[playerid] + PHONE_TD_HOUR_SIGNAL_OFFSET_X, PHONE_TD_Y + PHONE_TD_HOUR_SIGNAL_OFFSET_Y, " "); //señal
	PlayerTextDrawTextSize(playerid, pPhone_PTD_Base[playerid][1], icon_size_x, PHONE_TD_SIGNAL_ICON_SIZE);
	PlayerTextDrawAlignment(playerid, pPhone_PTD_Base[playerid][1], 1);
	PlayerTextDrawColor(playerid, pPhone_PTD_Base[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, pPhone_PTD_Base[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, pPhone_PTD_Base[playerid][1], 255);
	PlayerTextDrawFont(playerid, pPhone_PTD_Base[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, pPhone_PTD_Base[playerid][1], 0);
	SetPlayerTextDrawLayer(playerid, pPhone_PTD_Base[playerid][1], LAYER_PHONE);

	pPhone_PTD_Base[playerid][2] = CreatePlayerTextDraw(playerid, (pPhone_TD_X[playerid] + pPhone_TD_SX[playerid]) - PHONE_TD_HOUR_SIGNAL_OFFSET_X, PHONE_TD_Y + PHONE_TD_HOUR_SIGNAL_OFFSET_Y, " "); //hora
	PlayerTextDrawLetterSize(playerid, pPhone_PTD_Base[playerid][2], 0.185000, 0.832592);
	PlayerTextDrawAlignment(playerid, pPhone_PTD_Base[playerid][2], 3);
	PlayerTextDrawColor(playerid, pPhone_PTD_Base[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, pPhone_PTD_Base[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, pPhone_PTD_Base[playerid][2], 255);
	PlayerTextDrawFont(playerid, pPhone_PTD_Base[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, pPhone_PTD_Base[playerid][2], 1);
	SetPlayerTextDrawLayer(playerid, pPhone_PTD_Base[playerid][2], LAYER_PHONE);

	pPhone_PTD_Base[playerid][3] = CreatePlayerTextDraw(playerid, pPhone_TD_X[playerid] + PHONE_TD_HOUR_SIGNAL_OFFSET_X, PHONE_TD_Y + PHONE_TD_BUTTONS_OFFSET_Y, " "); // Verde
	PlayerTextDrawLetterSize(playerid, pPhone_PTD_Base[playerid][3], 0.159333, 0.832592);
	PlayerTextDrawAlignment(playerid, pPhone_PTD_Base[playerid][3], 1);
	PlayerTextDrawColor(playerid, pPhone_PTD_Base[playerid][3], 10813695);
	PlayerTextDrawSetShadow(playerid, pPhone_PTD_Base[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, pPhone_PTD_Base[playerid][3], 255);
	PlayerTextDrawFont(playerid, pPhone_PTD_Base[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, pPhone_PTD_Base[playerid][3], 1);
	PlayerTextDrawTextSize(playerid, pPhone_PTD_Base[playerid][3], pPhone_TD_X[playerid] + (pPhone_TD_SX[playerid] / 2.0), 9.0);
	SetPlayerTextDrawLayer(playerid, pPhone_PTD_Base[playerid][3], LAYER_PHONE);

	pPhone_PTD_Base[playerid][4] = CreatePlayerTextDraw(playerid, (pPhone_TD_X[playerid] + pPhone_TD_SX[playerid]) - PHONE_TD_HOUR_SIGNAL_OFFSET_X, PHONE_TD_Y + PHONE_TD_BUTTONS_OFFSET_Y, " "); // Rojo
	PlayerTextDrawLetterSize(playerid, pPhone_PTD_Base[playerid][4], 0.159333, 0.832592);
	PlayerTextDrawAlignment(playerid, pPhone_PTD_Base[playerid][4], 3);
	PlayerTextDrawColor(playerid, pPhone_PTD_Base[playerid][4], -1526726401);
	PlayerTextDrawSetShadow(playerid, pPhone_PTD_Base[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, pPhone_PTD_Base[playerid][4], 255);
	PlayerTextDrawFont(playerid, pPhone_PTD_Base[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, pPhone_PTD_Base[playerid][4], 1);
	PlayerTextDrawTextSize(playerid, pPhone_PTD_Base[playerid][4], (pPhone_TD_X[playerid] + pPhone_TD_SX[playerid]) + 25.0, 9.0);
	SetPlayerTextDrawLayer(playerid, pPhone_PTD_Base[playerid][4], LAYER_PHONE);
	return 1;
}

ShowPlayerPhoneTds(playerid)
{
	for(new i = 0; i < sizeof pPhone_PTD_Base[]; i ++)
	{
		if(pPhone_PTD_Base[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, pPhone_PTD_Base[playerid][i]);
	}
	return 1;
}

ShowPlayerPhone(playerid, page = PHONE_PAGE_MAIN, bool:freeze = true)
{
	CancelSelectTextDraw(playerid); //oculta todo
	if(freeze) TogglePlayerControllable(playerid, false);
	CreatePlayerPhoneBaseTds(playerid);
	pPhoneEnabled[playerid] = true;	
	pPhonePage[playerid] = page;

	ShowPlayerPhoneTds(playerid);
	ChangePhonePage(playerid, page);
	DisablePlayerLayers(playerid, LAYER_PHONE, true, LAYER_RADAR);
	if(page != PHONE_PAGE_CALL_DIALLING) CallRemoteFunction("OnPlayerOpenPhone", "ib", playerid, false);
	return 1;
}

HidePlayerPhone(playerid, bool:unfreeze = true)
{
	if(unfreeze) TogglePlayerControllable(playerid, true);
	DestroyPlayerPhone(playerid);
	EnablePlayerLayers(playerid);
	CallRemoteFunction("OnPlayerRequestAnimEnvStop", "i", playerid);
	CallRemoteFunction("OnPlayerClosePhone", "i", playerid);
	return 1;
}

GenerateUniquePhoneNumber(unique_id)
{
	new number_str[24];
	format(number_str, sizeof number_str, "%d%04d", random(999), unique_id);
	return strval(number_str);
}

DestroyPlayerPhoneOptionsTD(playerid)
{
	for(new i = 0; i < sizeof pPhone_PTD_Options[]; i ++)
	{
		if(pPhone_PTD_Options[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pPhone_PTD_Options[playerid][i]);
			pPhone_PTD_Options[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

CreatePlayerPhoneOptionsTD(playerid, amount, Float:offset_y = PHONE_TD_OPTION_OFFSET_BETWEEN, bool:show = true)
{
	if(amount < sizeof pPhone_PTD_Options[] + 1)
	{
		new Float:td_y = PHONE_TD_Y + PHONE_TD_OPTION_OFFSET_Y;
		for(new i = 0; i < amount; i ++)
		{
			pPhone_PTD_Options[playerid][i] = CreatePlayerTextDraw(playerid, pPhone_TD_X[playerid] + PHONE_TD_OPTION_OFFSET_X, td_y, " ", true);
			PlayerTextDrawLetterSize(playerid, pPhone_PTD_Options[playerid][i], 0.213000, 1.1);
			PlayerTextDrawTextSize(playerid, pPhone_PTD_Options[playerid][i], (pPhone_TD_X[playerid] + pPhone_TD_SX[playerid]) - PHONE_TD_OPTION_OFFSET_X, 0.000000);
			PlayerTextDrawAlignment(playerid, pPhone_PTD_Options[playerid][i], 1);
			PlayerTextDrawColor(playerid, pPhone_PTD_Options[playerid][i], -1);
			PlayerTextDrawUseBox(playerid, pPhone_PTD_Options[playerid][i], 1);
			PlayerTextDrawBoxColor(playerid, pPhone_PTD_Options[playerid][i], pPhoneOptionSelected[playerid] == i ? 557004799 : 1854244607);
			PlayerTextDrawSetShadow(playerid, pPhone_PTD_Options[playerid][i], 0);
			PlayerTextDrawBackgroundColor(playerid, pPhone_PTD_Options[playerid][i], 255);
			PlayerTextDrawFont(playerid, pPhone_PTD_Options[playerid][i], 1);
			PlayerTextDrawSetProportional(playerid, pPhone_PTD_Options[playerid][i], 1);
			SetPlayerTextDrawLayer(playerid, pPhone_PTD_Options[playerid][i], LAYER_PHONE);
			if(show) PlayerTextDrawShow(playerid, pPhone_PTD_Options[playerid][i]);
			td_y += offset_y;
		}
		pPhoneMaxOptions[playerid] = amount;
		return 1;
	}
	return 0;
}

ChangePhonePage(playerid, page)
{
	if(pPhoneEnabled[playerid])
	{
		if(pPhone_Dialling_Timer[playerid] != Timer:-1)
		{
			stop pPhone_Dialling_Timer[playerid];
			pPhone_Dialling_Timer[playerid] = Timer:-1;
		}
		DestroyPlayerPhoneOptionsTD(playerid);
		DestroyPlayerPhoneAuxTD(playerid);
		DestroyPlayerPhoneKeyboardTD(playerid);
		PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][3], " ");
		PlayerTextDrawSetSelectable(playerid, pPhone_PTD_Base[playerid][3], false);
		PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][4], " ");
		PlayerTextDrawSetSelectable(playerid, pPhone_PTD_Base[playerid][4], false);
		if(page != PHONE_PAGE_OFF)
		{
			new td_str[24];
			if(pCurrentZone[playerid] == INVALID_ZONE_ID && pRadarArea[playerid] == 0) format(td_str, sizeof td_str, ""TEXTDRAW_CUSTOM_PATH"phone_signal_0");
			else format(td_str, sizeof td_str, ""TEXTDRAW_CUSTOM_PATH"phone_signal_%d", minrand(1, 5));
			PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][1], td_str);
			format(td_str, sizeof td_str, "%02d:%02d", SERVER_TIME[0], SERVER_TIME[1]);	
			PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][2], td_str);

			if(pPhone_HourSignal_Timer[playerid] == Timer:-1)
			pPhone_HourSignal_Timer[playerid] = repeat OnPhoneRequestHSUpdate(playerid);
		}
		else
		{
			if(pPhone_HourSignal_Timer[playerid] != Timer:-1)
			{
				stop pPhone_HourSignal_Timer[playerid];
				pPhone_HourSignal_Timer[playerid] = Timer:-1;
			}
			PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][1], " ");
			PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][2], " ");
		}

		pPhonePage[playerid] = page;
		pPhoneOptionSelected[playerid] = 0;
		pPhoneMaxOptions[playerid] = 0;
		pPhoneEnableOPU[playerid] = true;
		pPhoneBook_Offset[playerid] = 0;
		switch(page)
		{
			case PHONE_PAGE_OFF: CreatePlayerPhoneOptionsTD(playerid, 1);
			case PHONE_PAGE_MAIN: CreatePlayerPhoneOptionsTD(playerid, 4);
			case PHONE_PAGE_SERVICES: CreatePlayerPhoneOptionsTD(playerid, 1);
			case PHONE_PAGE_BOOK:
			{
				pPhoneBook_AddContact[playerid][0] = EOS;
				pPhoneBook_AddNumber[playerid] = 0;
				//
				new options = Iter_Count(pPhoneBook[playerid]) + 1; //+1 (add)
				if(options > MAX_PHONE_OPTIONS) options = MAX_PHONE_OPTIONS;
				CreatePlayerPhoneOptionsTD(playerid, options);
				pPhoneBook_Offset[playerid] = -1;
				FormatPhoneBookTds(playerid);
			}
			case PHONE_PAGE_BOOK_CONTACT:
			{
				CreatePlayerPhoneOptionsTD(playerid, 2);
			}
			case PHONE_PAGE_BOOK_ADD:
			{
				CreatePlayerPhoneOptionsTD(playerid, 3, PHONE_TD_OPTION_OFFSET_BETWEEN * 2.0);
				FormatPhoneBookAddOptionsTd(playerid);
			}
			case PHONE_PAGE_BOOK_ADD_NUMBER:
			{
				pPhone_CallNumber_Str[playerid][0] = EOS;
				pPhoneEnableOPU[playerid] = false;
				CreatePlayerPhoneAuxTD(playerid);
				CreatePlayerPhoneKeyboardTD(playerid);
				PlayerTextDrawSetSelectable(playerid, pPhone_PTD_Base[playerid][3], true);
				PlayerTextDrawSetSelectable(playerid, pPhone_PTD_Base[playerid][4], true);
				SelectTextDraw(playerid, 0xFFFFFFAA);
			}
			case PHONE_PAGE_CALL_NUMBER:
			{
				pPhone_CallNumber_Str[playerid][0] = EOS;
				pPhoneEnableOPU[playerid] = false;
				CreatePlayerPhoneAuxTD(playerid);
				CreatePlayerPhoneKeyboardTD(playerid);
				PlayerTextDrawSetSelectable(playerid, pPhone_PTD_Base[playerid][3], true);
				PlayerTextDrawSetSelectable(playerid, pPhone_PTD_Base[playerid][4], true);
				SelectTextDraw(playerid, 0xFFFFFFAA);
			}
			case PHONE_PAGE_CALL_DIALLING:
			{
				pPhone_CallInfo[playerid][0] = strval(pPhone_CallNumber_Str[playerid]);
				pPhoneEnableOPU[playerid] = false;
				TogglePlayerControllable(playerid, true);
				CreatePlayerPhoneAuxTD(playerid);
				pPhone_DiallingPos[playerid] = 0;
				if(pPhone_Dialling_Timer[playerid] == Timer:-1)
				pPhone_Dialling_Timer[playerid] = repeat OnPhoneRequestDialling(playerid);
				CallRemoteFunction("OnPlayerOpenPhone", "ib", playerid, true);
			}
			case PHONE_PAGE_CALL_OUT:
			{
				pPhone_Call_TimeStarted[playerid] = GetTickCount();
				pPhoneEnableOPU[playerid] = false;
				CreatePlayerPhoneAuxTD(playerid);
				format(pPhone_CallNumber_Str[playerid], sizeof pPhone_CallNumber_Str[], "%s", resolvePhoneName(playerid, pPhone_CallInfo[playerid][0]));
				PlayerTextDrawSetString(playerid, pPhone_PTD_Aux[playerid][0], pPhone_CallNumber_Str[playerid]);
				pPhone_Call_Time[playerid] = 0;
				if(pPhone_Call_Timer[playerid] == Timer:-1)
				pPhone_Call_Timer[playerid] = repeat OnPhoneCallUpdate(playerid);
			}
			case PHONE_PAGE_CALL_IN:
			{
				pPhone_Call_TimeStarted[playerid] = GetTickCount();
				pPhone_Call_LastBeep[playerid] = GetTickCount();
				PlayerPlaySound(playerid, 20600, 0.0, 0.0, 0.0);
				pPhoneEnableOPU[playerid] = false;
				CreatePlayerPhoneAuxTD(playerid);
				format(pPhone_CallNumber_Str[playerid], sizeof pPhone_CallNumber_Str[], "%s", resolvePhoneName(playerid, pPhone_CallInfo[playerid][0]));
				PlayerTextDrawSetString(playerid, pPhone_PTD_Aux[playerid][0], pPhone_CallNumber_Str[playerid]);
				pPhone_Call_Time[playerid] = 0;
				if(pPhone_Call_Timer[playerid] == Timer:-1)
				pPhone_Call_Timer[playerid] = repeat OnPhoneCallUpdate(playerid);
				TogglePlayerControllable(playerid, true);
			}
			case PHONE_PAGE_CALL_ESTABLISHED:
			{
				PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
				pPhoneEnableOPU[playerid] = false;
				CreatePlayerPhoneAuxTD(playerid);
				PlayerTextDrawSetString(playerid, pPhone_PTD_Aux[playerid][0], pPhone_CallNumber_Str[playerid]);
			}
			case PHONE_PAGE_CALL_ENDED:
			{
				pPhone_CallInfo[playerid][1] = 0;
				pPhone_CallInfo[playerid][2] = 0;
				pPhoneEnableOPU[playerid] = false;
				if(pPhone_Call_Timer[playerid] == Timer:-1)
				pPhone_Call_Timer[playerid] = repeat OnPhoneCallUpdate(playerid);	

				PlayerPlaySound(playerid, 5205, 0.0, 0.0, 0.0);
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
				CreatePlayerPhoneAuxTD(playerid);
				PlayerTextDrawSetString(playerid, pPhone_PTD_Aux[playerid][0], pPhone_CallNumber_Str[playerid]);
			}
		}
		PlayerTextDrawShow(playerid, pPhone_PTD_Base[playerid][3]);
		PlayerTextDrawShow(playerid, pPhone_PTD_Base[playerid][4]);
		FormatPlayerPhoneTDS(playerid, page);
		return 1;
	}
	return 0;
}

ChangePhoneStatus(playerid, status, bool:update = true)
{
	PI[playerid][pi_PHONE_ON] = status;
	if(update)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player SET phone_on = %d WHERE id = %d;", PI[playerid][pi_PHONE_ON], PI[playerid][pi_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}
	return 1;
}

DestroyPlayerPhoneAuxTD(playerid)
{
	for(new i = 0; i < sizeof pPhone_PTD_Aux[]; i ++)
	{
		if(pPhone_PTD_Aux[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pPhone_PTD_Aux[playerid][i]);
			pPhone_PTD_Aux[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

CreatePlayerPhoneAuxTD(playerid, bool:show = true)
{
	pPhone_PTD_Aux[playerid][0] = CreatePlayerTextDraw(playerid, pPhone_TD_X[playerid] + PHONE_TD_AUX_OFFSET_X, PHONE_TD_Y + PHONE_TD_AUX0_OFFSET_Y, "_", true);
	PlayerTextDrawLetterSize(playerid, pPhone_PTD_Aux[playerid][0], 0.213000, 1.1);
	PlayerTextDrawAlignment(playerid, pPhone_PTD_Aux[playerid][0], 1);
	PlayerTextDrawColor(playerid, pPhone_PTD_Aux[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, pPhone_PTD_Aux[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, pPhone_PTD_Aux[playerid][0], 255);
	PlayerTextDrawFont(playerid, pPhone_PTD_Aux[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, pPhone_PTD_Aux[playerid][0], 1);
	SetPlayerTextDrawLayer(playerid, pPhone_PTD_Aux[playerid][0], LAYER_PHONE);
	
	pPhone_PTD_Aux[playerid][1] = CreatePlayerTextDraw(playerid, (pPhone_TD_X[playerid] + pPhone_TD_SX[playerid]) - PHONE_TD_AUX_OFFSET_X, PHONE_TD_Y + PHONE_TD_AUX1_OFFSET_Y, "_", true);
	PlayerTextDrawLetterSize(playerid, pPhone_PTD_Aux[playerid][1], 0.213000, 1.1);
	PlayerTextDrawAlignment(playerid, pPhone_PTD_Aux[playerid][1], 3);
	PlayerTextDrawColor(playerid, pPhone_PTD_Aux[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, pPhone_PTD_Aux[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, pPhone_PTD_Aux[playerid][1], 255);
	PlayerTextDrawFont(playerid, pPhone_PTD_Aux[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, pPhone_PTD_Aux[playerid][1], 1);
	SetPlayerTextDrawLayer(playerid, pPhone_PTD_Aux[playerid][1], LAYER_PHONE);

	if(show)
	{
		PlayerTextDrawShow(playerid, pPhone_PTD_Aux[playerid][0]);
		PlayerTextDrawShow(playerid, pPhone_PTD_Aux[playerid][1]);
	}
	return 1;
}

DestroyPlayerPhoneKeyboardTD(playerid)
{
	for(new i = 0; i < sizeof pPhone_PTD_Keyboard[]; i ++)
	{
		if(pPhone_PTD_Keyboard[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pPhone_PTD_Keyboard[playerid][i]);
			pPhone_PTD_Keyboard[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

CreatePlayerPhoneKeyboardTD(playerid, bool:show = true)
{
	new Float:td_x = (PHONE_TD_X - (pPhone_TD_SX[playerid] / 2.0)) + PHONE_TD_KEYBOARD_OFFSET_X, Float:td_y = PHONE_TD_Y + PHONE_TD_KEYBOARD_OFFSET_Y,
		cur_xpos;
	for(new i = 0; i < sizeof pPhone_PTD_Keyboard[]; i ++)
	{
		pPhone_PTD_Keyboard[playerid][i] = CreatePlayerTextDraw(playerid, td_x, td_y, "_", true);
		PlayerTextDrawTextSize(playerid, pPhone_PTD_Keyboard[playerid][i], td_x + PHONE_TD_KEYBOARD_SIZE_X, PHONE_TD_KEYBOARD_SIZE_Y);
		PlayerTextDrawAlignment(playerid, pPhone_PTD_Keyboard[playerid][i], 1);
		PlayerTextDrawColor(playerid, pPhone_PTD_Keyboard[playerid][i], 0xFFFFFF00);
		PlayerTextDrawSetShadow(playerid, pPhone_PTD_Keyboard[playerid][i], 0);
		PlayerTextDrawBackgroundColor(playerid, pPhone_PTD_Keyboard[playerid][i], 255);
		PlayerTextDrawFont(playerid, pPhone_PTD_Keyboard[playerid][i], 1);
		PlayerTextDrawSetProportional(playerid, pPhone_PTD_Keyboard[playerid][i], 0);
		PlayerTextDrawSetSelectable(playerid, pPhone_PTD_Keyboard[playerid][i], true);
		SetPlayerTextDrawLayer(playerid, pPhone_PTD_Keyboard[playerid][i], LAYER_PHONE);
		if(show) PlayerTextDrawShow(playerid, pPhone_PTD_Keyboard[playerid][i]);
		td_x += PHONE_TD_KEYBOARD_OFFSET_BT_X;
		cur_xpos ++;
		if(cur_xpos > 2)
		{
			cur_xpos = 0;
			td_x = (PHONE_TD_X - (pPhone_TD_SX[playerid] / 2.0)) + PHONE_TD_KEYBOARD_OFFSET_X;
			td_y += PHONE_TD_KEYBOARD_OFFSET_BT_Y;
		}
	}
	return 1;
}

DestroyPhoneBook(playerid, bool:update = false)
{
	if(update)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_phone_book WHERE id_player = %d;", PI[playerid][pi_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}
	new tmp_pPhoneBook[E_pPhoneBook];
	for(new i = 0; i < sizeof pPhoneBook[]; i ++)
	{
		pPhoneBook[playerid][i] = tmp_pPhoneBook;
	}
	Iter_Clear(pPhoneBook[playerid]);
	return 1;
}

FormatPhoneBookTds(playerid)
{
	new first_index, count;
	if(pPhoneBook_Offset[playerid] == -1)
	{
		FormatPhoneBookAddTd(playerid, count);
		pPhoneBook_Indexs[playerid][count] = -1;
		count ++;
	}
	if(pPhoneBook_Offset[playerid] <= 0) first_index = Iter_First(pPhoneBook[playerid]);
	else
	{
		new count_index;
		first_index = Iter_First(pPhoneBook[playerid]);
		while(count_index <= pPhoneBook_Offset[playerid] - 1)
		{
			first_index = Iter_Next(pPhoneBook[playerid], first_index);
			count_index ++;
		}
	}
	for(new i = first_index; i != Iter_End(pPhoneBook[playerid]); i = Iter_Next(pPhoneBook[playerid], i))
	{
		if(count >= MAX_PHONE_OPTIONS) break;
		else if(pPhone_PTD_Options[playerid][count] == PlayerText:INVALID_TEXT_DRAW) break;
		else
		{
			pPhoneBook_Indexs[playerid][count] = i;
			PlayerTextDrawSetString(playerid, pPhone_PTD_Options[playerid][count], pPhoneBook[playerid][i][pb_CONTACT]);
			count ++;
		}
	}
	return 1;
}

resolvePhoneName(playerid, number)
{
	new string[MAX_PHONE_NUMBER_LENGTH + 1];
	format(string, sizeof string, "%d", number);
	foreach(new i : pPhoneBook[playerid])
	{
		if(pPhoneBook[playerid][i][pb_NUMBER] == number)
		{
			format(string, sizeof string, "%s", pPhoneBook[playerid][i][pb_CONTACT]);
			break;
		}
	}
	return string;
}

GetSpecialNumberName(playerid, number, bool:up_first_letter = false)
{
	new name[32];
	switch(number)
	{
		case SPECIAL_PHONE_NUMBER_TAXI: Text_Format_TD(name, sizeof name, PI[playerid][pi_LANG_ID], $PHONE_NUMBER_TAXI);
	}
	if(up_first_letter) name[0] = toupper(name[0]);
	return name;
}

FormatPlayerPhoneTDS(playerid, page)
{
	switch(page)
	{
		case PHONE_PAGE_OFF: { PlayerTD_Text(playerid, pPhone_PTD_Options[playerid][0], $PHONE_1_OPTION); }
		case PHONE_PAGE_MAIN:
		{
			PlayerTD_Text(playerid, pPhone_PTD_Options[playerid][0], $PHONE_2_OPTION);
			PlayerTD_Text(playerid, pPhone_PTD_Options[playerid][1], $PHONE_3_OPTION);
			PlayerTD_Text(playerid, pPhone_PTD_Options[playerid][2], $PHONE_4_OPTION);
			PlayerTD_Text(playerid, pPhone_PTD_Options[playerid][3], $PHONE_5_OPTION);
			//botones
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][3], $PHONE_6_OPTION);
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][4], $PHONE_7_OPTION);
		}
		case PHONE_PAGE_SERVICES:
		{
			PlayerTextDrawSetString(playerid, pPhone_PTD_Options[playerid][0], GetSpecialNumberName(playerid, SPECIAL_PHONE_NUMBER_TAXI, true));
			//
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][3], $PHONE_3_OPTION);
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][4], $PHONE_8_OPTION);
		}
		case PHONE_PAGE_BOOK:
		{
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][3], $PHONE_6_OPTION);
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][4], $PHONE_8_OPTION);
		}
		case PHONE_PAGE_BOOK_CONTACT:
		{
			PlayerTD_Text(playerid, pPhone_PTD_Options[playerid][0], $PHONE_3_OPTION);
			PlayerTD_Text(playerid, pPhone_PTD_Options[playerid][1], $PHONE_9_OPTION);
			//botones
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][3], $PHONE_6_OPTION);
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][4], $PHONE_8_OPTION);
		}
		case PHONE_PAGE_BOOK_ADD:
		{
			PlayerTD_Text(playerid, pPhone_PTD_Options[playerid][2], $PHONE_10_OPTION);
			//botones
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][3], $PHONE_6_OPTION);
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][4], $PHONE_8_OPTION);
		}
		case PHONE_PAGE_BOOK_ADD_NUMBER:
		{
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][3], $PHONE_11_OPTION);
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][4], $PHONE_8_OPTION);
		}
		case PHONE_PAGE_CALL_NUMBER:
		{
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][3], $PHONE_3_OPTION);
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][4], $PHONE_8_OPTION);
		}
		case PHONE_PAGE_CALL_DIALLING, PHONE_PAGE_CALL_OUT:
		{
			PlayerTD_Text(playerid, pPhone_PTD_Aux[playerid][1], $PHONE_12_OPTION);
			PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][3], " ");
			
			new str[64];
			Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $PHONE_13_OPTION, "~k~~CONVERSATION_NO~");
			PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][4], str);
		}
		case PHONE_PAGE_CALL_IN:
		{
			PlayerTD_Text(playerid, pPhone_PTD_Aux[playerid][1], $PHONE_17_OPTION);
			
			new str[64];
			Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $PHONE_14_OPTION, "~k~~CONVERSATION_YES~");
			PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][3], str);
			
			Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $PHONE_13_OPTION, "~k~~CONVERSATION_NO~");
			PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][4], str);
		}
		case PHONE_PAGE_CALL_ESTABLISHED:
		{
			new str[64];
			Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $PHONE_13_OPTION, "~k~~CONVERSATION_NO~");
			PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][4], str);
		}
		case PHONE_PAGE_CALL_ENDED:
		{
			new days, hours, minutes, seconds, str[32];
			TimeConvert(pPhone_Call_Time[playerid], days, hours, minutes, seconds);
			Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $PHONE_15_OPTION, minutes, seconds);
			PlayerTextDrawSetString(playerid, pPhone_PTD_Aux[playerid][1], str);
			PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][3], " ");
			PlayerTD_Text(playerid, pPhone_PTD_Base[playerid][4], $PHONE_16_OPTION);
		}
	}
	return 1;
}

FormatPhoneBookAddTd(playerid, pos)
{
	PlayerTD_Text(playerid, pPhone_PTD_Options[playerid][pos], $PHONE_18_OPTION);
	return 1;
}

FormatPhoneBookAddOptionsTd(playerid)
{
	new str[32];
	if(isnull(pPhoneBook_AddContact[playerid])) Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $PHONE_19_OPTION, "_");
	else Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $PHONE_19_OPTION, pPhoneBook_AddContact[playerid]);
	PlayerTextDrawSetString(playerid, pPhone_PTD_Options[playerid][0], str);
	if(pPhoneBook_AddNumber[playerid] == 0) Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $PHONE_20_OPTION);
	else Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $PHONE_21_OPTION, pPhoneBook_AddNumber[playerid]);
	PlayerTextDrawSetString(playerid, pPhone_PTD_Options[playerid][1], str);
	return 1;
}