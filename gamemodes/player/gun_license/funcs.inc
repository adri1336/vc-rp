loadtext lang[gun_license];

ShowPlayerGunLicenseTestDlg(playerid)
{
	new question[64], valid_question_str[24], asnwer[3][128], valid_question;
	switch(pGunLicenseQuestion[playerid])
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
	}
	sscanf(valid_question_str, "d", valid_question);
	pGunLicenseValidQuestion[playerid] = valid_question;

	new dialog_message[128 * 3];
	format(dialog_message, sizeof dialog_message, "%s\n%s\n%s", asnwer[0], asnwer[1], asnwer[2]);
	Dialog_ShowCallback(playerid, using callback OnPlayerGunLicenseTestDialog, DIALOG_STYLE_LIST, question, dialog_message, ">>", "");
	return 1;
}