#include <YSI\y_hooks>

loadtext lang[clothing];

hook OnScriptInit()
{
	Iter_Init(pClothes);
	return 1;
}

hook OnPlayerDisconnect(playerid)
{
	if(pClothesMenu[playerid] != INVALID_MENU_ID)
	{
		DeletePreviewMenu(pClothesMenu[playerid]);
		pClothesMenu[playerid] = INVALID_MENU_ID;
	}
	foreach(new i : pClothes[playerid])
	{
		pClothes[playerid][i] = CLOTHES_TYPES:0;
	}
	Iter_Clear(pClothes[playerid]);
	return 1;
}

hook OnPlayerLogin(playerid)
{
	//load pclothes
	inline OnPlayerClothesLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i < rows; i ++)
			{
				cache_get_value_int(i, 0, _:pClothes[playerid][i]);
				Iter_Add(pClothes[playerid], i);
			}
			CallRemoteFunction("OnPlayerClothesLoaded", "i", playerid);
		}
	}
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT id_clothe FROM player_clothes WHERE id_player = %d LIMIT %d;", PI[playerid][pi_ID], MAX_CLOTHING_CLOTHES_PER_CHAR);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnPlayerClothesLoad, "");

	//setting
	SetPlayerClothingInfo(playerid, PI[playerid][pi_CLOTHING_CHARACTER], PI[playerid][pi_CLOTHING_CLOTHE]);
	return 1;
}

public OnPlayerRequestCharacterChange(playerid)
{
	inline OnMinDaysTimeCheck()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			if(rows)
			{
				new days_since_last_change, change_date[24];
				cache_get_value_int(0, 0, days_since_last_change);
				cache_get_value(0, 1, change_date);
				if(days_since_last_change >= MIN_DAYS_BETWEEN_CHAR_CHANGE)
				{
					HideMenuPTextdraws(playerid);
					inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
					{
						#pragma unused pid, dialogid, listitem, inputtext
						if(response)
						{
							if(CHARACTER_CHANGE_PRICE > PI[playerid][pi_MONEY])
							{
								Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY, CHARACTER_CHANGE_PRICE);
								ShowMenuPTextdraws(playerid);
							}
							else
							{
								if(PI[playerid][pi_GENDER] == CLOTHING_GENDER_MALE) ShowPreviewMenuForPlayer(playerid, maleCharactersMenu, 0xFFFFFFFF, GetCharacterMenuTitle(playerid));
								else ShowPreviewMenuForPlayer(playerid, femaleCharactersMenu, 0xFFFFFFFF, GetCharacterMenuTitle(playerid));
							}
						}
						else ShowMenuPTextdraws(playerid);
					}
					Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_CHAR_INFO_CAPTION, $DIALOG_CHAR_INFO_BODY, $DIALOG_CHAR_INFO_YES, $DIALOG_CHAR_INFO_NO, MIN_DAYS_BETWEEN_CHAR_CHANGE, CHARACTER_CHANGE_PRICE);
				}
				else Text_Send(playerid, $MESSAGE_ERROR_CHAR_TIME, change_date, (MIN_DAYS_BETWEEN_CHAR_CHANGE - days_since_last_change));
			}
		}
	}
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT TIMESTAMPDIFF(DAY, last_character_change, NOW()), DATE_ADD(last_character_change, INTERVAL %d DAY) FROM player WHERE id = %d;", MIN_DAYS_BETWEEN_CHAR_CHANGE, PI[playerid][pi_ID]);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnMinDaysTimeCheck, "");
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(pClothesMenu[playerid] != INVALID_MENU_ID)
	{
		if(newstate == PLAYER_STATE_SPECTATING || newstate == PLAYER_STATE_WASTED)
		{
			HidePreviewMenuForPlayer(playerid);
			DeletePreviewMenu(pClothesMenu[playerid]);
			pClothesMenu[playerid] = INVALID_MENU_ID;
		}
	}
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(pClothesMenu[playerid] != INVALID_MENU_ID)
	{
		HidePreviewMenuForPlayer(playerid);
		DeletePreviewMenu(pClothesMenu[playerid]);
		pClothesMenu[playerid] = INVALID_MENU_ID;
	}
	return 1;
}

hook OnPreviewMenuResponse(playerid, menu_id, menu_model_id, response, modelid, price)
{
	if(pClothesMenu[playerid] != INVALID_MENU_ID)
	{
		if(menu_id == pClothesMenu[playerid])
		{
			if(response)
			{
				GetClothingInfoFromModelid(PI[playerid][pi_CLOTHING_CHARACTER], modelid, pClothesInfo[playerid][0], pClothesInfo[playerid][1]);
				if(pClothesInfo[playerid][0] != -1)
				{
					inline OnPlayerDialog(pid, dialogid, in_response, listitem, string:inputtext[])
					{
						#pragma unused pid, dialogid, inputtext
						if(in_response)
						{
							switch(listitem)
							{
								case 0: //vestir
								{
									if(GetPlayerClothingSkinModel(playerid) == modelid) Text_Send(playerid, $MESSAGE_ERROR_SAME_CLOTHE);
									else
									{
										if(pClothesInfo[playerid][1] == -1) PI[playerid][pi_CLOTHING_CLOTHE] = CLOTHE_TYPE_DEFAULT;
										else PI[playerid][pi_CLOTHING_CLOTHE] = CL_CharacterClothes[ pClothesInfo[playerid][0] ][ pClothesInfo[playerid][1] ][cl_char_clothe_CLOTHE_TYPE];
										SetPlayerClothingInfo(playerid, PI[playerid][pi_CLOTHING_CHARACTER], PI[playerid][pi_CLOTHING_CLOTHE]);
										Text_Send(playerid, $GAMETEXT_INFO_CLOTHES_CHANGED);
										CallRemoteFunction("OnPlayerClothesChange", "id", playerid, pClothesInfo[playerid][1]);
									}
								}
								case 1: //tirar
								{
									if(pClothesInfo[playerid][1] == -1) Text_Send(playerid, $MESSAGE_ERROR_DEFAULT_CLOTHES);
									else
									{
										if(PI[playerid][pi_CLOTHING_CLOTHE] == CL_CharacterClothes[ pClothesInfo[playerid][0] ][ pClothesInfo[playerid][1] ][cl_char_clothe_CLOTHE_TYPE])
										{
											PI[playerid][pi_CLOTHING_CLOTHE] = CLOTHE_TYPE_DEFAULT;
											SetPlayerClothingInfo(playerid, PI[playerid][pi_CLOTHING_CHARACTER], PI[playerid][pi_CLOTHING_CLOTHE]);
										}
										DeletePlayerClothe(playerid, CL_CharacterClothes[ pClothesInfo[playerid][0] ][ pClothesInfo[playerid][1] ][cl_char_clothe_CLOTHE_TYPE]);
										Text_Send(playerid, $GAMETEXT_INFO_CLOTHES_DELETED);
										CallRemoteFunction("OnPlayerRemoveClothes", "idd", playerid, pClothesInfo[playerid][1], _:CL_CharacterClothes[ pClothesInfo[playerid][0] ][ pClothesInfo[playerid][1] ][cl_char_clothe_CLOTHE_TYPE]);
										CallRemoteFunction("OnPlayerClothesChange", "id", playerid, -1);
									}
								}
							}							
						}
					}
					Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_CLOTHES_CAPTION, $DIALOG_CLOTHES_BODY, $DIALOG_CLOTHES_YES, $DIALOG_CLOTHES_NO);
				}
				HidePreviewMenuForPlayer(playerid);
			}
			DeletePreviewMenu(pClothesMenu[playerid]);
			pClothesMenu[playerid] = INVALID_MENU_ID;
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	else
	{
		if(menu_id == maleCharactersMenu || menu_id == femaleCharactersMenu)
		{
			if(response)
			{
				new character_id = GetCharacterIdByModelid(modelid);
				if(character_id != 0)
				{
					PI[playerid][pi_CLOTHING_CHARACTER] = character_id;
					PI[playerid][pi_CLOTHING_CLOTHE] = CLOTHE_TYPE_DEFAULT;
					getDateTime(PI[playerid][pi_LAST_CHARACTER_CHANGE]);
					SetPlayerClothingInfo(playerid, character_id);
					GivePlayerMoneyEx(playerid, -CHARACTER_CHANGE_PRICE);
					Text_Send(playerid, $GAMETEXT_INFO_CHAR_CHANGED);
					orm_update(PI[playerid][pi_ORM]);
					//delete clothes
					Iter_Clear(pClothes[playerid]);
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_clothes WHERE id_player = %d;", PI[playerid][pi_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER);
					CallRemoteFunction("OnPlayerCharacterChange", "i", playerid);
				}
			}
			HidePreviewMenuForPlayer(playerid);
			ShowMenuPTextdraws(playerid);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return 1;
}

YCMD:clothes(playerid, params[], help)
{
	if(pClothesMenu[playerid] == INVALID_MENU_ID)
	{
		pClothesMenu[playerid] = CreatePreviewMenu("Clothes");
		if(pClothesMenu[playerid] != INVALID_MENU_ID)
		{
			new character_index = GetCharacterIndexById(PI[playerid][pi_CLOTHING_CHARACTER]);
			if(character_index != -1)
			{
				AddModelToPreviewMenu(pClothesMenu[playerid], CL_Character[character_index][cl_char_MODELID], 0, 0.0, 0.0, 0.0);
				foreach(new i : pClothes[playerid])
				{
					new clothe_index = GetCharacterClotheIndexById(character_index, pClothes[playerid][i]);
					if(clothe_index != -1)
					{
						new modelid = CL_CharacterClothes[character_index][clothe_index][cl_char_clothe_MODELID];
						AddModelToPreviewMenu(pClothesMenu[playerid], modelid, 0, 0.0, 0.0, 0.0);
					}
				}
				ShowPreviewMenuForPlayer(playerid, pClothesMenu[playerid], 0xFFFFFFFF, GetClotheMenuTitle(playerid));
			}
		}
	}
	return 1;
}