loadtext lang[car_workshop];

GetComponentPartName(playerid, part, bool:cl = true)
{
	new string[64];
    if(cl)
    {
        switch(part)
        {
            case 0: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_0_PART_CL);
            case 1: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_1_PART_CL);
            case 2: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_2_PART_CL);
            case 3: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_3_PART_CL);
            case 4: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_4_PART_CL);
            case 5: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_5_PART_CL);
            case 6: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_6_PART_CL);
            case 7: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_7_PART_CL);
            case 8: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_8_PART_CL);
            case 9: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_9_PART_CL);
            case 10: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_10_PART_CL);
            case 11: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_11_PART_CL);
            case 12: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_12_PART_CL);
            case 13: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_13_PART_CL);
            case 14: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_14_PART_CL);
            case 15: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_15_PART_CL);
            case 16: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_16_PART_CL);
            case 17: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_17_PART_CL);
            case 18: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_18_PART_CL);
        }
    }
    else
    {
        switch(part)
        {
            case 0: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_0_PART);
            case 1: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_1_PART);
            case 2: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_2_PART);
            case 3: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_3_PART);
            case 4: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_4_PART);
            case 5: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_5_PART);
            case 6: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_6_PART);
            case 7: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_7_PART);
            case 8: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_8_PART);
            case 9: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_9_PART);
            case 10: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_10_PART);
            case 11: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_11_PART);
            case 12: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_12_PART);
            case 13: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_13_PART);
            case 14: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_14_PART);
            case 15: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_15_PART);
            case 16: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_16_PART);
            case 17: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_17_PART);
            case 18: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $COMPONENT_18_PART);
        }
    }
	return string;
}