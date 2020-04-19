#include <YSI\y_hooks>

loadtext lang[register];

hook OnPlayerConnect(playerid)
{
	register_player_passwd[playerid][0] = EOS;
	pNewUser[playerid] = false;
	pSelectedCharacter[playerid] = -1;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(pSelectedCharacter[playerid] != -1)
	{
		DestroyPlayerRegisterTextdraws(playerid);
	}
	return 1;
}

public OnPlayerRequestRegister(playerid)
{
	pNewUser[playerid] = true;
	
	if(Total_Loaded_Languages > 1)
	{
		inline OnPlayerSelectLang(pid, dialogid, response, listitem, string:inputtext[])
		{
			#pragma unused pid, dialogid, inputtext
			if(response)
			{
				Langs_SetPlayerLanguage(playerid, Language:listitem);
				format(PI[playerid][pi_LANG], 3, "%s", Langs_GetCode(Language:listitem));
				PI[playerid][pi_LANG_ID] = Language:listitem;
				Text_DialogBox(playerid, DIALOG_STYLE_PASSWORD, using callback OnPlayerRegisterDialog, $DIALOG_REGISTER_PASSWD_CAPTION, $DIALOG_REGISTER_PASSWD_BODY, $DIALOG_REGISTER_PASSWD_YES, $DIALOG_REGISTER_PASSWD_NO, MIN_PASSWD_LENGHT, MAX_PASSWD_LENGHT);
			}
			else Kick(playerid);
		}
		Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerSelectLang, $DIALOG_REGISTER_LANG_CAPTION, $DIALOG_REGISTER_LANG_BODY, $DIALOG_REGISTER_LANG_YES, $DIALOG_REGISTER_LANG_NO, Lang_Dialog_String);
	}
	else
	{
		Langs_SetPlayerLanguage(playerid, Language:0);
		format(PI[playerid][pi_LANG], 3, "%s", Langs_GetCode(Language:0));
		PI[playerid][pi_LANG_ID] = Language:0;
		Text_DialogBox(playerid, DIALOG_STYLE_PASSWORD, using callback OnPlayerRegisterDialog, $DIALOG_REGISTER_PASSWD_CAPTION, $DIALOG_REGISTER_PASSWD_BODY, $DIALOG_REGISTER_PASSWD_YES, $DIALOG_REGISTER_PASSWD_NO, MIN_PASSWD_LENGHT, MAX_PASSWD_LENGHT);
	}
	return 1;
}

public OnPlayerRegisterDialog(playerid, dialogid, response, listitem, inputtext[])
{
	if(response)
	{
		new passwd_lenght = strlen(inputtext);
		if(passwd_lenght >= MIN_PASSWD_LENGHT && passwd_lenght <= MAX_PASSWD_LENGHT)
		{
			inline OnPlayerCheckPasswdDialog(pid, did, res, lis, string:inp[])
			{
				#pragma unused pid, did, lis
				if(res)
				{
					if(!strcmp(register_player_passwd[playerid], inp, false))
					{
						new salt[16];
						format(salt, sizeof salt, "%s", getRandomString(16));
						format(PI[playerid][pi_SALT], 16, "%s", salt);
						SHA256_PassHash(register_player_passwd[playerid], PI[playerid][pi_SALT], PI[playerid][pi_PASSWD], 64 + 1);
						//register_player_passwd[playerid][0] = EOS;

						Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using callback OnPlayerEmailRegister, $DIALOG_REGISTER_MAIL_CAPTION, $DIALOG_REGISTER_MAIL_BODY, $DIALOG_REGISTER_MAIL_YES, $DIALOG_REGISTER_MAIL_NO);
					}
					else
					{
						Text_Send(playerid, $MESSAGE_ERROR_WRONG_REG_REPASSWD);
						Text_DialogBox(playerid, DIALOG_STYLE_PASSWORD, using callback OnPlayerRegisterDialog, $DIALOG_REGISTER_PASSWD_CAPTION, $DIALOG_REGISTER_PASSWD_BODY, $DIALOG_REGISTER_PASSWD_YES, $DIALOG_REGISTER_PASSWD_NO, MIN_PASSWD_LENGHT, MAX_PASSWD_LENGHT);
					}
				}
				else Text_DialogBox(playerid, DIALOG_STYLE_PASSWORD, using callback OnPlayerRegisterDialog, $DIALOG_REGISTER_PASSWD_CAPTION, $DIALOG_REGISTER_PASSWD_BODY, $DIALOG_REGISTER_PASSWD_YES, $DIALOG_REGISTER_PASSWD_NO, MIN_PASSWD_LENGHT, MAX_PASSWD_LENGHT);
			}

			format(register_player_passwd[playerid], MAX_PASSWD_LENGHT + 1, "%s", inputtext);
			Text_DialogBox(playerid, DIALOG_STYLE_PASSWORD, using inline OnPlayerCheckPasswdDialog, $DIALOG_REGISTER_REPASSWD_CAPTION, $DIALOG_REGISTER_REPASSWD_BODY, $DIALOG_REGISTER_REPASSWD_YES, $DIALOG_REGISTER_REPASSWD_NO);
		}
		else
		{
			Text_Send(playerid, $MESSAGE_ERROR_WRONG_REG_PASSWD);
			Text_DialogBox(playerid, DIALOG_STYLE_PASSWORD, using callback OnPlayerRegisterDialog, $DIALOG_REGISTER_PASSWD_CAPTION, $DIALOG_REGISTER_PASSWD_BODY, $DIALOG_REGISTER_PASSWD_YES, $DIALOG_REGISTER_PASSWD_NO, MIN_PASSWD_LENGHT, MAX_PASSWD_LENGHT);
		}
	}
	else Kick(playerid);
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(pSelectedCharacter[playerid] != -1)
	{
		if(clickedid == Text:INVALID_TEXT_DRAW)
		{
			SelectTextDraw(playerid, 0xFFCCFFFF);
			Text_Send(playerid, $MESSAGE_INFO_REGISTER);
			return 1;
		}
	}
	return 0;
}

public OnPlayerEmailRegister(playerid, dialogid, response, listitem, inputtext[])
{
	if(response)
	{
		if(IsValidEmail(inputtext))
		{
			//check
			inline CheckAvaibleMail(mail[])
			{
				new rows;
				if(cache_get_row_count(rows))
				{
					if(rows)
					{ 
						//error (en uso)
						Text_Send(playerid, $MESSAGE_WARNING_EMAIL_EXISTS);
						Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using callback OnPlayerEmailRegister, $DIALOG_REGISTER_MAIL_CAPTION, $DIALOG_REGISTER_MAIL_BODY, $DIALOG_REGISTER_MAIL_YES, $DIALOG_REGISTER_MAIL_NO);
					}
					else
					{
						format(PI[playerid][pi_EMAIL], 64, "%s", mail);
						pSelectedCharacter[playerid] = 0;
						PI[playerid][pi_CLOTHING_CHARACTER] = Intro_Characters[ PI[playerid][pi_GENDER] ][ pSelectedCharacter[playerid] ];
						PI[playerid][pi_CLOTHING_CLOTHE] = CLOTHE_TYPE_DEFAULT;
						SetPlayerClothingInfo(playerid, Intro_Characters[ PI[playerid][pi_GENDER] ][ pSelectedCharacter[playerid] ]);
						CreatePlayerRegisterTextdraws(playerid);
						FormatRegisterPlayerTextDraws(playerid, pSelectedCharacter[playerid] + 1, sizeof Intro_Characters[], PTD_VCRP_REGISTER[playerid], false);
						ShowPlayerRegisterTextdraws(playerid);
						SelectTextDraw(playerid, 0xFFCCFFFF);
					}
				}
			}

			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT id FROM player WHERE email = '%e';", inputtext);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline CheckAvaibleMail, "s", inputtext);
		}
		else
		{
			Text_Send(playerid, $MESSAGE_ERROR_WRONG_MAIL_FORMAT);
			Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using callback OnPlayerEmailRegister, $DIALOG_REGISTER_MAIL_CAPTION, $DIALOG_REGISTER_MAIL_BODY, $DIALOG_REGISTER_MAIL_YES, $DIALOG_REGISTER_MAIL_NO);
		}
	}
	else Kick(playerid);
	return 1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	if(pSelectedCharacter[playerid] != -1)
	{
		if(playertextid == PTD_VCRP_REGISTER[playerid][3])
		{
			if(PI[playerid][pi_GENDER]) PI[playerid][pi_GENDER] = 0;
			else PI[playerid][pi_GENDER] = 1;

			PI[playerid][pi_CLOTHING_CHARACTER] = Intro_Characters[ PI[playerid][pi_GENDER] ][ pSelectedCharacter[playerid] ];
			SetPlayerClothingInfo(playerid, Intro_Characters[ PI[playerid][pi_GENDER] ][ pSelectedCharacter[playerid] ]);
			FormatRegisterPlayerTextDraws(playerid, pSelectedCharacter[playerid] + 1, sizeof Intro_Characters[], PTD_VCRP_REGISTER[playerid]);
			return 1;
		}
		else if(playertextid == PTD_VCRP_REGISTER[playerid][5])
		{
			pSelectedCharacter[playerid] ++;
			if(pSelectedCharacter[playerid] >= sizeof Intro_Characters[]) pSelectedCharacter[playerid] = 0;

			PI[playerid][pi_CLOTHING_CHARACTER] = Intro_Characters[ PI[playerid][pi_GENDER] ][ pSelectedCharacter[playerid] ];
			SetPlayerClothingInfo(playerid, Intro_Characters[ PI[playerid][pi_GENDER] ][ pSelectedCharacter[playerid] ]);
			FormatRegisterPlayerTextDraws(playerid, pSelectedCharacter[playerid] + 1, sizeof Intro_Characters[], PTD_VCRP_REGISTER[playerid]);
			return 1;
		}
		else if(playertextid == PTD_VCRP_REGISTER[playerid][6])
		{
			DestroyPlayerRegisterTextdraws(playerid);
			pSelectedCharacter[playerid] = -1;
			CancelSelectTextDraw(playerid);
			getDateTime(PI[playerid][pi_REGISTER_DATE]);
			getDateTime(PI[playerid][pi_LAST_CONNECTION]);
			getDateTime(PI[playerid][pi_LAST_CHARACTER_CHANGE]);
			orm_insert(PI[playerid][pi_ORM], "OnPlayerRegister", "d", playerid);
			return 1;
		}
	}
	return 0;
}

public OnPlayerRegister(playerid)
{
	AddPlayerInventoryItem(playerid, _:INV_ITEM_CHARACTER_ID, PI[playerid][pi_REGISTER_DATE]);
	CallRemoteFunction("OnPlayerLogin", "i", playerid);
	return 1;
}