#include <YSI\y_hooks>

loadtext lang[phone];

hook OnScriptInit()
{
	Iter_Init(pPhoneBook);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	DestroyPlayerPhone(playerid);
	DestroyPhoneBook(playerid);
	return 1;
}

hook OnPlayerLogin(playerid)
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_PHONE_BOOK_CONTACTS)
				{
					printf("[ERROR]: Límite rebasado en pPhoneBook (pid: %d)", PI[playerid][pi_ID]);
					break;
				}

				cache_get_value_name_int(i, "id", pPhoneBook[playerid][i][pb_ID]);
				cache_get_value_name(i, "contact", pPhoneBook[playerid][i][pb_CONTACT]);
				cache_get_value_name_int(i, "number", pPhoneBook[playerid][i][pb_NUMBER]);
				Iter_Add(pPhoneBook[playerid], i);
			}
		}
	}

	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM player_phone_book WHERE id_player = '%d';", PI[playerid][pi_ID]);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	DestroyPlayerPhone(playerid);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_SPECTATING)
	DestroyPlayerPhone(playerid);
	return 1;
}

YCMD:call(playerid, params[], help)
{
	if(!pPhoneEnabled[playerid])
	{
		new number;
		if(sscanf(params, "d", number)) Text_Send(playerid, $MESSAGE_ERROR_CALL_SYNTAX);
		else
		{
			if(number <= 0) Text_Send(playerid, $MESSAGE_ERROR_CALL_SYNTAX);
			else
			{
				format(pPhone_CallNumber_Str[playerid], sizeof pPhone_CallNumber_Str, "%d", number);
				ShowPlayerPhone(playerid, PHONE_PAGE_CALL_DIALLING);			
			}
		}
	}
	return 1;
}

YCMD:phone(playerid, params[], help)
{
	if(PlayerInvContainsItemType(playerid, _:INV_ITEM_TYPE_PHONE) && PI[playerid][pi_PHONE_NUMBER] != 0)
	{
		if(pPhoneEnabled[playerid]) HidePlayerPhone(playerid);
		else
		{
			if(PI[playerid][pi_PHONE_ON]) ShowPlayerPhone(playerid);
			else ShowPlayerPhone(playerid, PHONE_PAGE_OFF);
		}
	}
	else Text_Send(playerid, $MESSAGE_ERROR_NO_PHONE);
	return 1;
}

timer OnPhoneRequestHSUpdate[UPDATE_PHONE_HOUR_SIGNAL_INTERVAL](playerid)
{
	if(pPhone_PTD_Base[playerid][1] != PlayerText:INVALID_TEXT_DRAW && pPhone_PTD_Base[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
	{
		new td_str[24];
		if(pCurrentZone[playerid] == INVALID_ZONE_ID && pRadarArea[playerid] == 0) format(td_str, sizeof td_str, ""TEXTDRAW_CUSTOM_PATH"phone_signal_0");
		else format(td_str, sizeof td_str, ""TEXTDRAW_CUSTOM_PATH"phone_signal_%d", minrand(1, 5));
		PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][1], td_str);
		format(td_str, sizeof td_str, "%02d:%02d", SERVER_TIME[0], SERVER_TIME[1]);	
		PlayerTextDrawSetString(playerid, pPhone_PTD_Base[playerid][2], td_str);
	}
	return 1;
}

hook OnPlayerUpdate(playerid)
{
	if(pPhoneEnabled[playerid] && pPhoneEnableOPU[playerid])
	{
		if(pPhoneMaxOptions[playerid] > 0)
		{
			new Keys, ud, lr;
			GetPlayerKeys(playerid, Keys, ud, lr);
			if(ud == KEY_UP)
			{
				PlayerTextDrawBoxColor(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]], 1854244607);
				PlayerTextDrawShow(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]]);
				pPhoneOptionSelected[playerid] --;
				if(pPhoneOptionSelected[playerid] < 0)
				{
					if(pPhonePage[playerid] == PHONE_PAGE_BOOK)
					{
						pPhoneOptionSelected[playerid] ++;
						pPhoneBook_Offset[playerid] --;
						if(pPhoneBook_Offset[playerid] < -1)
						{
							pPhoneBook_Offset[playerid] = Iter_Count(pPhoneBook[playerid]) - pPhoneMaxOptions[playerid];
							if(pPhoneBook_Offset[playerid] < 0) pPhoneBook_Offset[playerid] = -1;
							pPhoneOptionSelected[playerid] = pPhoneMaxOptions[playerid] - 1;
							PlayerTextDrawBoxColor(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]], 557004799);
							PlayerTextDrawShow(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]]);
						}
						else
						{
							PlayerTextDrawBoxColor(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]], 557004799);
							PlayerTextDrawShow(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]]);
						}
						FormatPhoneBookTds(playerid);
						PlayerPlaySound(playerid, 17006, 0.0, 0.0, 0.0);
						return 1;
					}
					else pPhoneOptionSelected[playerid] = pPhoneMaxOptions[playerid] - 1;
				}
				PlayerTextDrawBoxColor(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]], 557004799);
				PlayerTextDrawShow(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]]);
				PlayerPlaySound(playerid, 17006, 0.0, 0.0, 0.0);
			}
			else if(ud == KEY_DOWN)
			{
				PlayerTextDrawBoxColor(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]], 1854244607);
				PlayerTextDrawShow(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]]);
				pPhoneOptionSelected[playerid] ++;
				if(pPhoneOptionSelected[playerid] > pPhoneMaxOptions[playerid] - 1)
				{
					if(pPhonePage[playerid] == PHONE_PAGE_BOOK)
					{
						pPhoneOptionSelected[playerid] --;
						pPhoneBook_Offset[playerid] ++;
						if(pPhoneBook_Offset[playerid] + pPhoneOptionSelected[playerid] >= Iter_Count(pPhoneBook[playerid]))
						{
							pPhoneBook_Offset[playerid] = -1;
							pPhoneOptionSelected[playerid] = 0;
							PlayerTextDrawBoxColor(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]], 557004799);
							PlayerTextDrawShow(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]]);
						}
						else
						{
							PlayerTextDrawBoxColor(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]], 557004799);
							PlayerTextDrawShow(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]]);
						}
						FormatPhoneBookTds(playerid);
						PlayerPlaySound(playerid, 17006, 0.0, 0.0, 0.0);
						return 1;
					}
					else pPhoneOptionSelected[playerid] = 0;
				}
				PlayerTextDrawBoxColor(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]], 557004799);
				PlayerTextDrawShow(playerid, pPhone_PTD_Options[playerid][pPhoneOptionSelected[playerid]]);
				PlayerPlaySound(playerid, 17006, 0.0, 0.0, 0.0);
			}
		}
	}
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(pPhoneEnabled[playerid])
	{
		if(clickedid == Text:INVALID_TEXT_DRAW)
		{
			switch(pPhonePage[playerid])
			{
				case PHONE_PAGE_CALL_NUMBER:
				{
					ChangePhonePage(playerid, PHONE_PAGE_MAIN);
					PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
				}
				case PHONE_PAGE_BOOK_ADD_NUMBER:
				{
					ChangePhonePage(playerid, PHONE_PAGE_BOOK_ADD);
					PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);	
				}
			}
			return 1;
		}
	}
	return 0;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	if(pPhoneEnabled[playerid])
	{
		if(playertextid == pPhone_PTD_Base[playerid][3]) //verde
		{
			switch(pPhonePage[playerid])
			{
				case PHONE_PAGE_CALL_NUMBER:
				{
					new length = strlen(pPhone_CallNumber_Str[playerid]);
					if(length == 0) PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
					else
					{
						ChangePhonePage(playerid, PHONE_PAGE_CALL_DIALLING);
						CancelSelectTextDraw(playerid);
						PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
					}
				}
				case PHONE_PAGE_BOOK_ADD_NUMBER:
				{
					new length = strlen(pPhone_CallNumber_Str[playerid]);
					if(length == 0) PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
					else
					{
						pPhoneBook_AddNumber[playerid] = strval(pPhone_CallNumber_Str[playerid]);
						ChangePhonePage(playerid, PHONE_PAGE_BOOK_ADD);
						CancelSelectTextDraw(playerid);
						PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
					}	
				}
			}
			return 1;
		}
		else if(playertextid == pPhone_PTD_Base[playerid][4]) //rojo
		{
			switch(pPhonePage[playerid])
			{
				case PHONE_PAGE_CALL_NUMBER, PHONE_PAGE_BOOK_ADD_NUMBER: CancelSelectTextDraw(playerid);
			}
			return 1;
		}
		else
		{
			for(new i = 0; i < sizeof pPhone_PTD_Keyboard[]; i ++)
			{
				if(playertextid == pPhone_PTD_Keyboard[playerid][i])
				{
					if(pPhonePage[playerid] == PHONE_PAGE_CALL_NUMBER || pPhonePage[playerid] == PHONE_PAGE_BOOK_ADD_NUMBER)
					{
						new length = strlen(pPhone_CallNumber_Str[playerid]);
						if(i <= 8)
						{
							if(length >= MAX_PHONE_NUMBER_LENGTH) PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
							else
							{
								format(pPhone_CallNumber_Str[playerid], sizeof pPhone_CallNumber_Str[], "%s%d", pPhone_CallNumber_Str[playerid], i + 1);
								PlayerTextDrawSetString(playerid, pPhone_PTD_Aux[playerid][0], pPhone_CallNumber_Str[playerid]);
								PlayerPlaySound(playerid, 17006, 0.0, 0.0, 0.0);
							}
						}
						else if(i == 9) //retroceso
						{
							if(length == 0) PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
							else
							{
								strdel(pPhone_CallNumber_Str[playerid], length - 1, length);
								PlayerTextDrawSetString(playerid, pPhone_PTD_Aux[playerid][0], pPhone_CallNumber_Str[playerid]);
								PlayerPlaySound(playerid, 17006, 0.0, 0.0, 0.0);
							}
						}
						else //0
						{
							if(length >= MAX_PHONE_NUMBER_LENGTH) PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
							else
							{
								format(pPhone_CallNumber_Str[playerid], sizeof pPhone_CallNumber_Str[], "%s0", pPhone_CallNumber_Str[playerid]);
								PlayerTextDrawSetString(playerid, pPhone_PTD_Aux[playerid][0], pPhone_CallNumber_Str[playerid]);
								PlayerPlaySound(playerid, 17006, 0.0, 0.0, 0.0);
							}
						}
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

hook OnPlayerItemAdded(playerid, index, item_id, amount)
{
	if(item_id == _:INV_ITEM_PHONE)
	{
		if(PI[playerid][pi_PHONE_NUMBER] == 0)
		{
			PI[playerid][pi_PHONE_ON] = 1;
			PI[playerid][pi_PHONE_NUMBER] = GenerateUniquePhoneNumber(PI[playerid][pi_ID]);
			format(PINV[playerid][index][pinv_PARAMS], 128, "%d", PI[playerid][pi_PHONE_NUMBER]);
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player SET phone_number = %d WHERE id = %d;", PI[playerid][pi_PHONE_NUMBER], PI[playerid][pi_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET params = '%e' WHERE id = %d;", PINV[playerid][index][pinv_PARAMS], PINV[playerid][index][pinv_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);
		}
	}
	return 1;
}

hook OnPlayerItemDeleted(playerid, index, inv_id, itemid, params[], bool:player_action, amount)
{
	if(itemid == _:INV_ITEM_PHONE)
	{
		PI[playerid][pi_PHONE_NUMBER] = 0;
	}
	return 1;
}

timer OnPhoneRequestDialling[PHONE_DIALLING_INTERVAL](playerid)
{
	if(pPhone_DiallingPos[playerid] == -1)
	{
		pPhone_Dialling_Timer[playerid] = Timer:-1;
		if(pPhone_CallInfo[playerid][0] < -1)
		{
			switch(pPhone_CallInfo[playerid][0])
			{
				case SPECIAL_PHONE_NUMBER_TAXI: CallRemoteFunction("OnPlayerRequestTaxi", "i", playerid);
			}
			ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
		}
		else
		{
			inline OnQueryLoad()
			{
				new rows;
				if(cache_get_row_count(rows))
				{
					if(rows)
					{
						new connected, call_playerid;
						cache_get_value_index_int(0, 0, connected);
						cache_get_value_index_int(0, 1, call_playerid);
						if(!connected || !IsPlayerConnected(call_playerid))
						{
							Text_Send(playerid, $MESSAGE_ERROR_NUMBER_OCCUPIED, pPhone_CallNumber_Str[playerid]);
							ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
						}
						else if(GetPlayerGameState(call_playerid) != GAME_STATE_SPAWNED || PI[call_playerid][pi_PHONE_NUMBER] != pPhone_CallInfo[playerid][0] || !PI[call_playerid][pi_PHONE_ON] || pPhone_CallInfo[call_playerid][0] != 0 || pCurrentZone[call_playerid] == INVALID_ZONE_ID)
						{
							Text_Send(playerid, $MESSAGE_ERROR_NUMBER_OCCUPIED, pPhone_CallNumber_Str[playerid]);
							ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
						}
						else
						{
							pPhone_CallInfo[playerid][0] = PI[call_playerid][pi_PHONE_NUMBER];
							pPhone_CallInfo[playerid][1] = call_playerid;
							pPhone_CallInfo[playerid][2] = PI[call_playerid][pi_ID];
							pPhone_CallInfo[call_playerid][0] = PI[playerid][pi_PHONE_NUMBER];
							pPhone_CallInfo[call_playerid][1] = playerid;
							pPhone_CallInfo[call_playerid][2] = PI[playerid][pi_ID];
							format(pPhone_CallNumber_Str[call_playerid], sizeof pPhone_CallNumber_Str[], "%d", PI[playerid][pi_PHONE_NUMBER]);
							if(pPhoneEnabled[call_playerid])
							{
								ChangePhonePage(call_playerid, PHONE_PAGE_CALL_IN);
							}
							else ShowPlayerPhone(call_playerid, PHONE_PAGE_CALL_IN, false);
							ChangePhonePage(playerid, PHONE_PAGE_CALL_OUT);
						}
					}
					else
					{
						Text_Send(playerid, $MESSAGE_ERROR_NUMBER_NO_EXISTS, pPhone_CallNumber_Str[playerid]);
						ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
					}
				}
				else
				{
					Text_Send(playerid, $MESSAGE_ERROR_NUMBER_NO_EXISTS, pPhone_CallNumber_Str[playerid]);
					ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
				}
			}
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT connected, playerid FROM player WHERE phone_number = %d LIMIT 1;", pPhone_CallInfo[playerid][0]);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
		}
	}
	else
	{
		if(pPhone_DiallingPos[playerid] == 0) PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

		new length = 1;
		if(pPhone_CallInfo[playerid][0] > 0) //no special
		{
			new str[MAX_PHONE_NUMBER_LENGTH + 1];
			length = strlen(pPhone_CallNumber_Str[playerid]);
			format(str, sizeof str, "%s", pPhone_CallNumber_Str[playerid]);
			pPhone_DiallingPos[playerid] ++;
			strdel(str, pPhone_DiallingPos[playerid], length);
			PlayerTextDrawSetString(playerid, pPhone_PTD_Aux[playerid][0], str);
		}

		if(pPhone_DiallingPos[playerid] >= length || pPhone_CallInfo[playerid][0] < -1)
		{
			if(pPhone_Dialling_Timer[playerid] != Timer:-1)
			{
				stop pPhone_Dialling_Timer[playerid];
				pPhone_Dialling_Timer[playerid] = Timer:-1;
			}
			if(pPhone_CallInfo[playerid][0] < -1)
			{
				format(pPhone_CallNumber_Str[playerid], sizeof pPhone_CallNumber_Str[], "%s", GetSpecialNumberName(playerid, pPhone_CallInfo[playerid][0]));
				PlayerTextDrawSetString(playerid, pPhone_PTD_Aux[playerid][0], pPhone_CallNumber_Str[playerid]);
				pPhone_DiallingPos[playerid] = -1;
				pPhone_Dialling_Timer[playerid] = defer OnPhoneRequestDialling[PHONE_SPECIAL_DIALLING_TIME](playerid);
			}
			else
			{
				pPhone_DiallingPos[playerid] = -1;
				pPhone_Dialling_Timer[playerid] = defer OnPhoneRequestDialling[PHONE_DIALLING_TIME](playerid);
			}
		}
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(pPhoneEnabled[playerid])
	{
		if(pPhoneEnableOPU[playerid])
		{
			if(newkeys & KEY_SPRINT) //seleccionar
			{
				switch(pPhonePage[playerid])
				{
					case PHONE_PAGE_OFF:
					{
						if(pPhoneOptionSelected[playerid] == 0) //encender
						{
							ChangePhoneStatus(playerid, 1);
							ChangePhonePage(playerid, PHONE_PAGE_MAIN);
						}
					}
					case PHONE_PAGE_MAIN:
					{
						switch(pPhoneOptionSelected[playerid])
						{
							case 0: //agenda
							{
								ChangePhonePage(playerid, PHONE_PAGE_BOOK);
							}
							case 1: //llamar
							{
								if(pCurrentZone[playerid] == INVALID_ZONE_ID && pRadarArea[playerid] == 0)
								{
									PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
									Text_Send(playerid, $MESSAGE_ERROR_NO_SIGNAL);
								}
								else ChangePhonePage(playerid, PHONE_PAGE_CALL_NUMBER);
							}
							case 2: //servicios
							{
								if(pCurrentZone[playerid] == INVALID_ZONE_ID && pRadarArea[playerid] == 0)
								{
									PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
									Text_Send(playerid, $MESSAGE_ERROR_NO_SIGNAL);
								}
								else ChangePhonePage(playerid, PHONE_PAGE_SERVICES);
							}
							case 3: //apagar
							{
								ChangePhoneStatus(playerid, 0);
								ChangePhonePage(playerid, PHONE_PAGE_OFF);
							}
						}
					}
					case PHONE_PAGE_SERVICES:
					{
						switch(pPhoneOptionSelected[playerid])
						{
							case 0: //taxi
							{
								format(pPhone_CallNumber_Str[playerid], sizeof pPhone_CallNumber_Str[], "%d", SPECIAL_PHONE_NUMBER_TAXI);
								ChangePhonePage(playerid, PHONE_PAGE_CALL_DIALLING);
								PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
							}
						}
					}
					case PHONE_PAGE_BOOK:
					{
						pPhoneBook_SelectedIndex[playerid] = pPhoneBook_Indexs[playerid][ pPhoneOptionSelected[playerid] ];
						if(pPhoneBook_SelectedIndex[playerid] == -1)
						{
							//add
							if(Iter_Count(pPhoneBook[playerid]) >= MAX_PHONE_BOOK_CONTACTS)
							{
								PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
								Text_Send(playerid, $MESSAGE_ERROR_PB_FULL);
								return 1;	
							}
							else ChangePhonePage(playerid, PHONE_PAGE_BOOK_ADD);
						}
						else
						{
							//contact
							ChangePhonePage(playerid, PHONE_PAGE_BOOK_CONTACT);
						}
					}
					case PHONE_PAGE_BOOK_CONTACT:
					{
						switch(pPhoneOptionSelected[playerid])
						{
							case 0:
							{
								format(pPhone_CallNumber_Str[playerid], sizeof pPhone_CallNumber_Str, "%d", pPhoneBook[playerid][ pPhoneBook_SelectedIndex[playerid] ][pb_NUMBER]);
								ChangePhonePage(playerid, PHONE_PAGE_CALL_DIALLING);
							}
							case 1:
							{
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_phone_book WHERE id = %d;", pPhoneBook[playerid][ pPhoneBook_SelectedIndex[playerid] ][pb_ID]);
								mysql_tquery(vcrp_db, QUERY_BUFFER);
								pPhoneBook[playerid][ pPhoneBook_SelectedIndex[playerid] ][pb_ID] = 0;
								pPhoneBook[playerid][ pPhoneBook_SelectedIndex[playerid] ][pb_CONTACT][0] = EOS;
								pPhoneBook[playerid][ pPhoneBook_SelectedIndex[playerid] ][pb_NUMBER] = 0;
								Iter_Remove(pPhoneBook[playerid], pPhoneBook_SelectedIndex[playerid]);
								Text_Send(playerid, $MESSAGE_INFO_CONTACT_DELETED);
								ChangePhonePage(playerid, PHONE_PAGE_BOOK);	
							}
						}
					}
					case PHONE_PAGE_BOOK_ADD:
					{
						switch(pPhoneOptionSelected[playerid])
						{
							case 0: //nombre
							{
								//Aa-Zz max length, not null
								inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
								{
									#pragma unused pid, dialogid, listitem
									if(response)
									{
										if(isnull(inputtext) || strlen(inputtext) > MAX_PHONE_NUMBER_LENGTH || !isTextAlphanumeric(inputtext))
										{
											PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
											Text_Send(playerid, $MESSAGE_ERROR_PB_NAME_FORMAT);
										}
										else
										{
											PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
											format(pPhoneBook_AddContact[playerid], MAX_PHONE_NUMBER_LENGTH + 1, "%s", inputtext);
											FormatPhoneBookAddOptionsTd(playerid);
										}
									}
									else PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
								}
								Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnPlayerDialog, $DIALOG_PB_CONTACT_CAPTION, $DIALOG_PB_CONTACT_BODY, $DIALOG_PB_CONTACT_YES, $DIALOG_PB_CONTACT_NO, MAX_PHONE_NUMBER_LENGTH);
							}
							case 1: //numero
							{
								ChangePhonePage(playerid, PHONE_PAGE_BOOK_ADD_NUMBER);
							}
							case 2: //add
							{
								if(isnull(pPhoneBook_AddContact[playerid]) || pPhoneBook_AddNumber[playerid] == 0)
								{
									PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
									Text_Send(playerid, $MESSAGE_ERROR_PB_ADD);
									return 1;
								}
								else
								{
									inline OnContactInserted()
									{
										new index = Iter_Free(pPhoneBook[playerid]);
										if(index != cellmin)
										{
											pPhoneBook[playerid][index][pb_ID] = cache_insert_id();
											format(pPhoneBook[playerid][index][pb_CONTACT], MAX_PHONE_NUMBER_LENGTH + 1, "%s", pPhoneBook_AddContact[playerid]);
											pPhoneBook[playerid][index][pb_NUMBER] = pPhoneBook_AddNumber[playerid];
											Iter_Add(pPhoneBook[playerid], index);
											Text_Send(playerid, $MESSAGE_INFO_CONTACT_ADDED);
											ChangePhonePage(playerid, PHONE_PAGE_BOOK);
										}
									}
									mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_phone_book (id_player, contact, number) VALUES (%d, '%e', %d);", PI[playerid][pi_ID], pPhoneBook_AddContact[playerid], pPhoneBook_AddNumber[playerid]); 
									mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnContactInserted, "");
								}
							}
						}
					}
				}
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
			}
			else if(newkeys & KEY_SECONDARY_ATTACK) //atras
			{
				switch(pPhonePage[playerid])
				{
					case PHONE_PAGE_OFF, PHONE_PAGE_MAIN: HidePlayerPhone(playerid);
					case PHONE_PAGE_BOOK, PHONE_PAGE_SERVICES: ChangePhonePage(playerid, PHONE_PAGE_MAIN);
					case PHONE_PAGE_BOOK_CONTACT: ChangePhonePage(playerid, PHONE_PAGE_BOOK);
					case PHONE_PAGE_BOOK_ADD: ChangePhonePage(playerid, PHONE_PAGE_BOOK);
				}
				PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
			}
		}
		else
		{
			if(newkeys & KEY_YES) //verde
			{
				if(pPhonePage[playerid] == PHONE_PAGE_CALL_IN)
				{
					CallRemoteFunction("OnPlayerOpenPhone", "ib", playerid, true);
					ChangePhonePage(playerid, PHONE_PAGE_CALL_ESTABLISHED);
					ChangePhonePage(pPhone_CallInfo[playerid][1], PHONE_PAGE_CALL_ESTABLISHED);
				}
			}
			else if(newkeys & KEY_NO) //rojo
			{
				if(	pPhonePage[playerid] == PHONE_PAGE_CALL_DIALLING || 
					pPhonePage[playerid] == PHONE_PAGE_CALL_IN || 
					pPhonePage[playerid] == PHONE_PAGE_CALL_OUT ||
					pPhonePage[playerid] == PHONE_PAGE_CALL_ESTABLISHED)
				{
					ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
				}
			}
		}
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return 1;
}

timer OnPhoneCallUpdate[PHONE_CALL_UPDATE_INTERVAL](playerid)
{
	if(pPhoneEnabled[playerid])
	{
		if(pPhone_CallInfo[playerid][0] == -1)
		{
			pPhone_Call_Timer[playerid] = Timer:-1;
			HidePlayerPhone(playerid, false);
		}
		else
		{
			switch(pPhonePage[playerid])
			{
				case PHONE_PAGE_CALL_OUT:
				{
					if(GetTickCount() - pPhone_Call_TimeStarted[playerid] >= PHONE_MAX_WAIT_TIME)
					{
						//max tiempo de espera
						ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
					}
					else
					{
						if(GetTickCount() - pPhone_Call_LastBeep[playerid] > 4000)
						{
							PlayerPlaySound(playerid, 16001, 0.0, 0.0, 0.0);
							pPhone_Call_LastBeep[playerid] = GetTickCount();
						}
						//comprobaciones
						if(IsPlayerConnected(pPhone_CallInfo[playerid][1]))
						{
							if(!pPhoneEnabled[pPhone_CallInfo[playerid][1]] || pPhone_CallInfo[playerid][2] != PI[ pPhone_CallInfo[playerid][1] ][pi_ID])
							{
								ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
							}
						}
						else ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);

					}
				}
				case PHONE_PAGE_CALL_IN:
				{
					if(GetTickCount() - pPhone_Call_LastBeep[playerid] > 4000)
					{
						PlayerPlaySound(playerid, 20600, 0.0, 0.0, 0.0);
						pPhone_Call_LastBeep[playerid] = GetTickCount();
					}
					if(IsPlayerConnected(pPhone_CallInfo[playerid][1]))
					{
						if(!pPhoneEnabled[pPhone_CallInfo[playerid][1]] || pPhone_CallInfo[playerid][2] != PI[ pPhone_CallInfo[playerid][1] ][pi_ID])
						{
							ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
						}
					}
					else ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
				}
				case PHONE_PAGE_CALL_ESTABLISHED:
				{
					//comprobaciones
					if(IsPlayerConnected(pPhone_CallInfo[playerid][1]))
					{
						if(!pPhoneEnabled[pPhone_CallInfo[playerid][1]] || pPhone_CallInfo[playerid][2] != PI[ pPhone_CallInfo[playerid][1] ][pi_ID])
						{
							ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
						}
						else
						{
							pPhone_Call_Time[playerid] ++;
							if(pPhone_PTD_Aux[playerid][1] != PlayerText:INVALID_TEXT_DRAW)
							{
								new td_str[24], days, hours, minutes, seconds;
								TimeConvert(pPhone_Call_Time[playerid], days, hours, minutes, seconds);
								format(td_str, sizeof td_str, "%d:%02d", minutes, seconds);
								PlayerTextDrawSetString(playerid, pPhone_PTD_Aux[playerid][1], td_str);
							}
						}
					}
					else ChangePhonePage(playerid, PHONE_PAGE_CALL_ENDED);
				}
				case PHONE_PAGE_CALL_ENDED:
				{
					if(pPhone_Call_Timer[playerid] != Timer:-1)
					{
						stop pPhone_Call_Timer[playerid];
						pPhone_Call_Timer[playerid] = Timer:-1;
					}
					pPhone_CallInfo[playerid][0] = -1;
					pPhone_Call_Timer[playerid] = defer OnPhoneCallUpdate[PHONE_ENDED_TIME](playerid);
				}
				default:
				{
					if(pPhone_Call_Timer[playerid] != Timer:-1)
					{
						stop pPhone_Call_Timer[playerid];
						pPhone_Call_Timer[playerid] = Timer:-1;
					}
				}
			}
		}
	}
	else
	{
		if(pPhone_Call_Timer[playerid] != Timer:-1)
		{
			stop pPhone_Call_Timer[playerid];
			pPhone_Call_Timer[playerid] = Timer:-1;
		}
	}
	return 1;
}

hook OnPlayerText(playerid, text[])
{
	if(pPhoneEnabled[playerid] && pPhonePage[playerid] == PHONE_PAGE_CALL_ESTABLISHED)
	{
		if(pPhonePage[ pPhone_CallInfo[playerid][1] ] == PHONE_PAGE_CALL_ESTABLISHED)
		{
			Text_Send(pPhone_CallInfo[playerid][1], $MESSAGE_PHONE_CHAT, pPhone_CallNumber_Str[ pPhone_CallInfo[playerid][1] ], text);
		}
		ChatMsg(playerid, 15.0, text, true);
		SetPlayerChatBubble(playerid, text, 0xFFFFFFFF, 15.0, 5000);
		return Y_HOOKS_BREAK_RETURN_0;
	}
	return Y_HOOKS_CONTINUE_RETURN_0;
}