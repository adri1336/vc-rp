loadtext lang[driving_school];

ShowPlayerDrivingSchoolTestDlg(playerid)
{
	new question[64], valid_question_str[24], asnwer[3][128], valid_question;
	switch(pDrivingSchoolQuestion[playerid])
	{
		case 0:
		{
			Text_Format_Dialog(question, sizeof question, PI[playerid][pi_LANG_ID], $TEST_1_QUESTION);
			Text_Format_Dialog(valid_question_str, sizeof valid_question_str, PI[playerid][pi_LANG_ID], $TEST_1_VALID_ANSWER);
			Text_Format_Dialog(asnwer[0], 128, PI[playerid][pi_LANG_ID], $TEST_1_1_ANSWER);
			Text_Format_Dialog(asnwer[1], 128, PI[playerid][pi_LANG_ID], $TEST_1_2_ANSWER);
			Text_Format_Dialog(asnwer[2], 128, PI[playerid][pi_LANG_ID], $TEST_1_3_ANSWER);
		}
		case 1:
		{
			Text_Format_Dialog(question, sizeof question, PI[playerid][pi_LANG_ID], $TEST_2_QUESTION);
			Text_Format_Dialog(valid_question_str, sizeof valid_question_str, PI[playerid][pi_LANG_ID], $TEST_2_VALID_ANSWER);
			Text_Format_Dialog(asnwer[0], 128, PI[playerid][pi_LANG_ID], $TEST_2_1_ANSWER);
			Text_Format_Dialog(asnwer[1], 128, PI[playerid][pi_LANG_ID], $TEST_2_2_ANSWER);
			Text_Format_Dialog(asnwer[2], 128, PI[playerid][pi_LANG_ID], $TEST_2_3_ANSWER);
		}
		case 2:
		{
			Text_Format_Dialog(question, sizeof question, PI[playerid][pi_LANG_ID], $TEST_3_QUESTION);
			Text_Format_Dialog(valid_question_str, sizeof valid_question_str, PI[playerid][pi_LANG_ID], $TEST_3_VALID_ANSWER);
			Text_Format_Dialog(asnwer[0], 128, PI[playerid][pi_LANG_ID], $TEST_3_1_ANSWER);
			Text_Format_Dialog(asnwer[1], 128, PI[playerid][pi_LANG_ID], $TEST_3_2_ANSWER);
			Text_Format_Dialog(asnwer[2], 128, PI[playerid][pi_LANG_ID], $TEST_3_3_ANSWER);
		}
		case 3:
		{
			Text_Format_Dialog(question, sizeof question, PI[playerid][pi_LANG_ID], $TEST_4_QUESTION);
			Text_Format_Dialog(valid_question_str, sizeof valid_question_str, PI[playerid][pi_LANG_ID], $TEST_4_VALID_ANSWER);
			Text_Format_Dialog(asnwer[0], 128, PI[playerid][pi_LANG_ID], $TEST_4_1_ANSWER);
			Text_Format_Dialog(asnwer[1], 128, PI[playerid][pi_LANG_ID], $TEST_4_2_ANSWER);
			Text_Format_Dialog(asnwer[2], 128, PI[playerid][pi_LANG_ID], $TEST_4_3_ANSWER);
		}
		case 4:
		{
			Text_Format_Dialog(question, sizeof question, PI[playerid][pi_LANG_ID], $TEST_5_QUESTION);
			Text_Format_Dialog(valid_question_str, sizeof valid_question_str, PI[playerid][pi_LANG_ID], $TEST_5_VALID_ANSWER);
			Text_Format_Dialog(asnwer[0], 128, PI[playerid][pi_LANG_ID], $TEST_5_1_ANSWER);
			Text_Format_Dialog(asnwer[1], 128, PI[playerid][pi_LANG_ID], $TEST_5_2_ANSWER);
			Text_Format_Dialog(asnwer[2], 128, PI[playerid][pi_LANG_ID], $TEST_5_3_ANSWER);
		}
	}
	sscanf(valid_question_str, "d", valid_question);
	pDrivingSchoolValidQuestion[playerid] = valid_question;

	new dialog_message[128 * 3];
	format(dialog_message, sizeof dialog_message, "%s\n%s\n%s", asnwer[0], asnwer[1], asnwer[2]);
	Dialog_ShowCallback(playerid, using callback OnPlayerDrivingSchoolTestDialog, DIALOG_STYLE_LIST, question, dialog_message, ">>", "");
	return 1;
}

CancelDrivingSchoolTest(playerid)
{
	if(pDrivingSchoolTest_Timer[playerid] != Timer:-1)
	{
		stop pDrivingSchoolTest_Timer[playerid];
		pDrivingSchoolTest_Timer[playerid] = Timer:-1;
	}

	pDrivingSchoolPoints[playerid] = 0;
	pDrivingSchoolQuestion[playerid] = 0;
	pDrivingSchoolCancelSeconds[playerid] = 0;
	pInDrivingSchoolVehicleTest[playerid] = false;

	if(pDrivingSchoolVehicleIndex[playerid] != INVALID_VEHICLE_INDEX)
	{
		DestroyVehicleEx(pDrivingSchoolVehicleIndex[playerid]);
		pDrivingSchoolVehicleIndex[playerid] = INVALID_VEHICLE_INDEX;
	}
	HidePlayerAuxTextDraw(playerid);
	DestroyPlayerRoute(playerid);
	return 1;
}

PlayerDrivingSchoolCancelMsg(playerid)
{
	new str[128];	
	Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_CANCEL_1_MESSAGE, pDrivingSchoolCancelSeconds[playerid]);
	ShowPlayerInfoMessage(playerid, str, 0, false);
	return 1;
}

PlayerDrivingSchoolMsg(playerid, reason)
{
	new str[256];
	switch(reason)
	{
		case 0: { Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_CANCEL_2_MESSAGE); }
		case 1: { Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_CANCEL_3_MESSAGE); }
		case 2: { Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_CANCEL_4_MESSAGE); }
	}
	ShowPlayerInfoMessage(playerid, str, 5, false);
	return 1;
}

GetSpeedLimitText(playerid, Float:current_speed, Float:max_speed, Float:next_max_speed)
{
	new str[128];
	if(current_speed > max_speed)
	{
		if(current_speed > next_max_speed)
		{
			if(!PI[playerid][pi_MPH]) Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_SPEED_LIMIT, "~r~", floatround(max_speed), "~y~", floatround(next_max_speed));
			else  Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_SPEED_LIMIT_MPH, "~r~", floatround(KMHtoMPH(max_speed)), "~y~", floatround(KMHtoMPH(next_max_speed)));
		}
		else
		{
			if(!PI[playerid][pi_MPH]) Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_SPEED_LIMIT, "~r~", floatround(max_speed), "~g~", floatround(next_max_speed));
			else Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_SPEED_LIMIT_MPH, "~r~", floatround(KMHtoMPH(max_speed)), "~g~", floatround(KMHtoMPH(next_max_speed)));
		}
	}
	else
	{
		if(current_speed > next_max_speed)
		{
			if(!PI[playerid][pi_MPH]) Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_SPEED_LIMIT, "~g~", floatround(max_speed), "~y~", floatround(next_max_speed));
			else Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_SPEED_LIMIT_MPH, "~g~", floatround(KMHtoMPH(max_speed)), "~y~", floatround(KMHtoMPH(next_max_speed)));
		}
		else
		{
			if(!PI[playerid][pi_MPH]) Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_SPEED_LIMIT, "~g~", floatround(max_speed), "~g~", floatround(next_max_speed));
			else Text_Format_TD(str, sizeof(str), PI[playerid][pi_LANG_ID], $TEXTDRAW_SPEED_LIMIT_MPH, "~g~", floatround(KMHtoMPH(max_speed)), "~g~", floatround(KMHtoMPH(next_max_speed)));
		}
	}
	return str;
}