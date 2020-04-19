#include <YSI\y_hooks>

loadtext lang[menu];

hook OnPlayerConnect(playerid)
{
	pInMenu[playerid] = false;
	pSpawnFromMenu[playerid] = false;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(pInMenu[playerid]) DestroyMenuPTextdraws(playerid);
	return 1;
}

hook OnPlayerARLoad(playerid, width, height)
{
	ShowPlayerMenu(playerid);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(pSpawnFromMenu[playerid])
	{
		TogglePlayerControllable(playerid, false);
		loadscreen_timer[playerid] = defer OnLoadScreenFinish[2000](playerid);
		pSpawnFromMenu[playerid] = false;
	}
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(pInMenu[playerid])
	{
		if(clickedid == Text:INVALID_TEXT_DRAW)
		{
			SelectTextDraw(playerid, 0xFFFFFFFF);
			return 1;
		}
	}
	return 0;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	if(pInMenu[playerid])
	{
		if(playertextid == Menu_PTD[playerid][1]) //jugar
		{
			HidePlayerMenu(playerid);
			return 1;
		}
		else if(playertextid == Menu_PTD[playerid][2]) //info
		{
			inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
			{
				#pragma unused pid, dialogid, inputtext
				if(response)
				{
					switch(listitem)
					{
						case 0:
						{
							HidePlayerMenu(playerid, false);
							StartPlayerIntro(playerid);
						}
						case 1:
						{
							CallRemoteFunction("OnPlayerRequestHelpDialog", "i", playerid);
						}
					}
				}
			}
			Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_INFO_CAPTION, $DIALOG_INFO_BODY, $DIALOG_INFO_YES, $DIALOG_INFO_NO);
		}
		else if(playertextid == Menu_PTD[playerid][3]) //ajustes
		{
			inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
			{
				#pragma unused pid, dialogid, inputtext
				if(response)
				{
					switch(listitem)
					{
						case 0: //idioma
						{
							inline OnPlayerSelectLang(in_pid, did, res, lis, string:inp[])
							{
								#pragma unused in_pid, did, inp
								if(res)
								{
									Langs_SetPlayerLanguage(playerid, Language:lis);
									format(PI[playerid][pi_LANG], 3, "%s", Langs_GetCode(Language:lis));
									SetPlayerLanguageGroup(playerid);
									Text_Send(playerid, $GAMETEXT_INFO_LANG_CHANGED);
									FormatPlayerMenuTds(playerid);
								}
								else
								{
									new unit_str[24];
									if(!PI[playerid][pi_MPH]) Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_KM);
									else  Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_MILES);
									Text_DialogBox(playerid, DIALOG_STYLE_TABLIST, using inline OnPlayerDialog, $DIALOG_SETTINGS_CAPTION, $DIALOG_SETTINGS_BODY, $DIALOG_SETTINGS_YES, $DIALOG_SETTINGS_NO, PI[playerid][pi_LANG], PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], PI[playerid][pi_HELP_CHANNEL], PI[playerid][pi_ADMIN_MESSAGES], unit_str);
								}
							}
							Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerSelectLang, $DIALOG_LANG_CAPTION, $DIALOG_LANG_BODY, $DIALOG_LANG_YES, $DIALOG_LANG_NO, Lang_Dialog_String);
						}
						case 1: //ar
						{
							inline OnPlayerArDialog(in_pid, did, res, lis, string:inp[])
							{
								#pragma unused in_pid, did, lis
								if(res)
								{
									new width, height;
									if(sscanf(inp, "p<,>dd", width, height)) Text_Send(playerid, $MESSAGE_ERROR_WRONG_FORMAT);
									else
									{
										PI[playerid][pi_AR_WIDTH] = width;
										PI[playerid][pi_AR_HEIGHT] = height;
										Text_Send(playerid, $GAMETEXT_INFO_AR_RESTART);
									}
								}
								else
								{
									new unit_str[24];
									if(!PI[playerid][pi_MPH]) Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_KM);
									else  Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_MILES);
									Text_DialogBox(playerid, DIALOG_STYLE_TABLIST, using inline OnPlayerDialog, $DIALOG_SETTINGS_CAPTION, $DIALOG_SETTINGS_BODY, $DIALOG_SETTINGS_YES, $DIALOG_SETTINGS_NO, PI[playerid][pi_LANG], PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], PI[playerid][pi_HELP_CHANNEL], PI[playerid][pi_ADMIN_MESSAGES], unit_str);
								}
							}
							Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnPlayerArDialog, $DIALOG_AR_CAPTION, $DIALOG_AR_BODY, $DIALOG_AR_YES, $DIALOG_AR_NO);
						}
						case 2: //personaje
						{
							CallRemoteFunction("OnPlayerRequestCharacterChange", "i", playerid);
						}
						case 3: //canal de dudas
						{
							PI[playerid][pi_HELP_CHANNEL] = !PI[playerid][pi_HELP_CHANNEL];

							new unit_str[24];
							if(!PI[playerid][pi_MPH]) Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_KM);
							else  Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_MILES);
							Text_DialogBox(playerid, DIALOG_STYLE_TABLIST, using inline OnPlayerDialog, $DIALOG_SETTINGS_CAPTION, $DIALOG_SETTINGS_BODY, $DIALOG_SETTINGS_YES, $DIALOG_SETTINGS_NO, PI[playerid][pi_LANG], PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], PI[playerid][pi_HELP_CHANNEL], PI[playerid][pi_ADMIN_MESSAGES], unit_str);
						}
						case 4: // mensajs admin
						{
							PI[playerid][pi_ADMIN_MESSAGES] = !PI[playerid][pi_ADMIN_MESSAGES];
							
							new unit_str[24];
							if(!PI[playerid][pi_MPH]) Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_KM);
							else  Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_MILES);
							Text_DialogBox(playerid, DIALOG_STYLE_TABLIST, using inline OnPlayerDialog, $DIALOG_SETTINGS_CAPTION, $DIALOG_SETTINGS_BODY, $DIALOG_SETTINGS_YES, $DIALOG_SETTINGS_NO, PI[playerid][pi_LANG], PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], PI[playerid][pi_HELP_CHANNEL], PI[playerid][pi_ADMIN_MESSAGES], unit_str);
						}
						case 5: // unidad medida km miles
						{
							PI[playerid][pi_MPH] = !PI[playerid][pi_MPH];

							new unit_str[24];
							if(!PI[playerid][pi_MPH]) Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_KM);
							else  Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_MILES);
							Text_DialogBox(playerid, DIALOG_STYLE_TABLIST, using inline OnPlayerDialog, $DIALOG_SETTINGS_CAPTION, $DIALOG_SETTINGS_BODY, $DIALOG_SETTINGS_YES, $DIALOG_SETTINGS_NO, PI[playerid][pi_LANG], PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], PI[playerid][pi_HELP_CHANNEL], PI[playerid][pi_ADMIN_MESSAGES], unit_str);
						}
					}
				}
			}
			
			new unit_str[24];
			if(!PI[playerid][pi_MPH]) Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_KM);
			else  Text_Format_Dialog(unit_str, sizeof unit_str, PI[playerid][pi_LANG_ID], $DIALOG_SETTINGS_MILES);
			Text_DialogBox(playerid, DIALOG_STYLE_TABLIST, using inline OnPlayerDialog, $DIALOG_SETTINGS_CAPTION, $DIALOG_SETTINGS_BODY, $DIALOG_SETTINGS_YES, $DIALOG_SETTINGS_NO, PI[playerid][pi_LANG], PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], PI[playerid][pi_HELP_CHANNEL], PI[playerid][pi_ADMIN_MESSAGES], unit_str);
			return 1;
		}
		else if(playertextid == Menu_PTD[playerid][4]) //salir
		{
			Kick(playerid);
		}
	}
	return 0;
}

YCMD:menu(playerid, params[], help)
{
	ShowPlayerMenu(playerid);
	return 1;
}