#include <YSI\y_hooks>

loadtext lang[bank];

public OnPlayerRequestBankPoint(playerid)
{
	HidePlayerInfoMessage(playerid);
	Text_DialogBox(playerid, DIALOG_STYLE_LIST, using callback OnBankDialogResponse, $DIALOG_BANK_POINT_CAPTION, $DIALOG_BANK_POINT_BODY, $DIALOG_BANK_POINT_YES, $DIALOG_BANK_POINT_NO);
	return 1;
}

public OnBankDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0: //retirar
			{
				inline in_OnDialogResponse(pid, did, res, lis, string:inp[])
				{
					#pragma unused pid, did, lis
					if(res)
					{
						if(sscanf(inp, "d", inp[0])) Text_Send(playerid, $MESSAGE_ERROR_WRONG_FORMAT);
						else
						{
							if(inp[0] <= 0) Text_Send(playerid, $MESSAGE_ERROR_NEGATIVE);
							else if(inp[0] > MAX_BANK_MOVEMENT) Text_Send(playerid, $MESSAGE_ERROR_MAX_TRANSACTION, MAX_BANK_MOVEMENT);
							else if(inp[0] > PI[playerid][pi_BANK_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NOBANKMONEY, inp[0]);
							else
							{
								PI[playerid][pi_BANK_MONEY] -= inp[0];
								GivePlayerMoneyEx(playerid, inp[0], true);
								Text_Send(playerid, $MESSAGE_INFO_WITHDRAW, inp[0]);
								orm_update(PI[playerid][pi_ORM]);
								RegisterBankMovement(PI[playerid][pi_ID], PI[playerid][pi_ID], PI[playerid][pi_NAME], PI[playerid][pi_NAME], -inp[0]);
							}
						}
					}
					else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using callback OnBankDialogResponse, $DIALOG_BANK_POINT_CAPTION, $DIALOG_BANK_POINT_BODY, $DIALOG_BANK_POINT_YES, $DIALOG_BANK_POINT_NO);
				}
				Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline in_OnDialogResponse, $DIALOG_BANK_WITHDRAW_CAPTION, $DIALOG_BANK_WITHDRAW_BODY, $DIALOG_BANK_WITHDRAW_YES, $DIALOG_BANK_WITHDRAW_NO, PI[playerid][pi_BANK_MONEY]);
			}
			case 1: //depositar
			{
				inline in_OnDialogResponse(pid, did, res, lis, string:inp[])
				{
					#pragma unused pid, did, lis
					if(res)
					{
						if(sscanf(inp, "d", inp[0])) Text_Send(playerid, $MESSAGE_ERROR_WRONG_FORMAT);
						else
						{
							if(inp[0] <= 0) Text_Send(playerid, $MESSAGE_ERROR_NEGATIVE);
							else if(inp[0] > MAX_BANK_MOVEMENT) Text_Send(playerid, $MESSAGE_ERROR_MAX_TRANSACTION, MAX_BANK_MOVEMENT);
							else if(inp[0] > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NOMONEY, inp[0]);
							else
							{
								GivePlayerMoneyEx(playerid, -inp[0], true);
								PI[playerid][pi_BANK_MONEY] += inp[0];
								Text_Send(playerid, $MESSAGE_INFO_DEPOSIT, inp[0]);
								orm_update(PI[playerid][pi_ORM]);
								RegisterBankMovement(PI[playerid][pi_ID], PI[playerid][pi_ID], PI[playerid][pi_NAME], PI[playerid][pi_NAME], inp[0]);
							}
						}
					}
					else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using callback OnBankDialogResponse, $DIALOG_BANK_POINT_CAPTION, $DIALOG_BANK_POINT_BODY, $DIALOG_BANK_POINT_YES, $DIALOG_BANK_POINT_NO);
				}
				Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline in_OnDialogResponse, $DIALOG_BANK_DEPOSIT_CAPTION, $DIALOG_BANK_DEPOSIT_BODY, $DIALOG_BANK_DEPOSIT_YES, $DIALOG_BANK_DEPOSIT_NO, PI[playerid][pi_MONEY]);
			}
			case 2: //transferir
			{
				inline in_OnDialogResponse(pid, did, res, lis, string:inp[])
				{
					#pragma unused pid, did, lis
					if(res)
					{
						if(sscanf(inp, "d", inp[0])) Text_Send(playerid, $MESSAGE_ERROR_WRONG_FORMAT);
						else
						{
							if(inp[0] <= 0) Text_Send(playerid, $MESSAGE_ERROR_NEGATIVE);
							else if(inp[0] > MAX_BANK_MOVEMENT) Text_Send(playerid, $MESSAGE_ERROR_MAX_TRANSACTION, MAX_BANK_MOVEMENT);
							else if(inp[0] > PI[playerid][pi_BANK_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NOBANKMONEY, inp[0]);
							else
							{
								pBankTransferAmount[playerid] = inp[0];
								Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using callback OnAmountTranferBankDialog, $DIALOG_BANK_TRANSFER_NAME_CAPTION, $DIALOG_BANK_TRANSFER_NAME_BODY, $DIALOG_BANK_TRANSFER_NAME_YES, $DIALOG_BANK_TRANSFER_NAME_NO, pBankTransferAmount[playerid]);
							}
						}
					}
					else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using callback OnBankDialogResponse, $DIALOG_BANK_POINT_CAPTION, $DIALOG_BANK_POINT_BODY, $DIALOG_BANK_POINT_YES, $DIALOG_BANK_POINT_NO);
				}
				Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline in_OnDialogResponse, $DIALOG_BANK_TRANSFER_CAPTION, $DIALOG_BANK_TRANSFER_BODY, $DIALOG_BANK_TRANSFER_YES, $DIALOG_BANK_TRANSFER_NO, PI[playerid][pi_BANK_MONEY]);
			}
			case 3: //movimientos
			{
				inline OnMovementsLoad()
				{
					new rows;
					if(cache_get_row_count(rows))
					{
						if(!rows) Text_Send(playerid, $MESSAGE_ERROR_NO_MOVEMENTS);
						else
						{
							inline in_OnDialogResponse(pid, did, res, lis, string:inp[])
							{
								#pragma unused pid, did, lis, inp
								if(res) Text_DialogBox(playerid, DIALOG_STYLE_LIST, using callback OnBankDialogResponse, $DIALOG_BANK_POINT_CAPTION, $DIALOG_BANK_POINT_BODY, $DIALOG_BANK_POINT_YES, $DIALOG_BANK_POINT_NO);
							}

							new dialog_str[128 * 11], line_str[128];
							format(dialog_str, sizeof dialog_str, "%s", GetMovementHeaderDialog(playerid));
							for(new i = 0; i != rows; i ++)
							{
								new datetime[24], from_id, to_id, from_name[24], to_name[24], amount;
								cache_get_value_name(i, "date", datetime, 24);
								cache_get_value_name_int(i, "from_id", from_id);
								cache_get_value_name_int(i, "to_id", to_id);
								cache_get_value_name(i, "from_name", from_name, 24);
								cache_get_value_name(i, "to_name", to_name, 24);
								cache_get_value_name_int(i, "amount", amount);

								if(from_id == PI[playerid][pi_ID] && to_id == PI[playerid][pi_ID])
								{
									if(amount < 0) format(line_str, sizeof line_str, "%s\t%s\t-$%d\n", datetime, GetPlayerBankMovementName(playerid, 0), -amount);
									else format(line_str, sizeof line_str, "%s\t%s\t+$%d\n", datetime, GetPlayerBankMovementName(playerid, 1), amount);
								}
								else if(from_id == PI[playerid][pi_ID]) format(line_str, sizeof line_str, "%s\t%s %s\t-$%d\n", datetime, GetPlayerBankMovementName(playerid, 2), to_name, amount);
								else if(to_id == PI[playerid][pi_ID]) format(line_str, sizeof line_str, "%s\t%s %s\t+$%d\n", datetime, GetPlayerBankMovementName(playerid, 3), from_name, amount);
								strcat(dialog_str, line_str);
							}
							ShowPlayerDialog(playerid, 1, DIALOG_STYLE_TABLIST_HEADERS, " ", dialog_str, "X", "");
						}
					}
					else Text_Send(playerid, $MESSAGE_ERROR_NO_MOVEMENTS);
				}

				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM player_bank_movements WHERE from_id = %d OR to_id = %d ORDER BY date DESC LIMIT 10;", PI[playerid][pi_ID], PI[playerid][pi_ID]);
				mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnMovementsLoad, "");
			}
		}
	}
	return 1;
}

public OnAmountTranferBankDialog(playerid, dialogid, response, listitem, inputtext[])
{
	if(response)
	{
		if(sscanf(inputtext, "s[24]", pBankTransferName[playerid])) Text_Send(playerid, $MESSAGE_ERROR_TRANSFER_WRONG_FORMAT);
		else
		{
			inline CheckPlayerName()
			{
				new rows;
				if(cache_get_row_count(rows))
				{
					if(rows)
					{
						cache_get_value_index_int(0, 0, pBankTransferPlayerID[playerid]);
						Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using callback OnConfirmTranferBankDialog, $DIALOG_BANK_TRANSFER_CONFIRM_CAPTION, $DIALOG_BANK_TRANSFER_CONFIRM_BODY, $DIALOG_BANK_TRANSFER_CONFIRM_YES, $DIALOG_BANK_TRANSFER_CONFIRM_NO, pBankTransferName[playerid], pBankTransferAmount[playerid]);
					}
					else Text_Send(playerid, $MESSAGE_ERROR_TRANSFER_WRONG_NAME, pBankTransferName[playerid]);
				}
				else Text_Send(playerid, $MESSAGE_ERROR_TRANSFER_WRONG_NAME, pBankTransferName[playerid]);
			}

			space_rp_name(pBankTransferName[playerid]);
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT id FROM player WHERE name = '%e';", pBankTransferName[playerid]);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline CheckPlayerName, "");
		}
	}
	else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using callback OnBankDialogResponse, $DIALOG_BANK_POINT_CAPTION, $DIALOG_BANK_POINT_BODY, $DIALOG_BANK_POINT_YES, $DIALOG_BANK_POINT_NO);
	return 1;
}

public OnConfirmTranferBankDialog(playerid, dialogid, response, listitem, inputtext[])
{
	if(response)
	{
		//
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player SET bank_money = bank_money - %d WHERE id = %d;", pBankTransferAmount[playerid], PI[playerid][pi_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player SET bank_money = bank_money + %d WHERE id = %d;", pBankTransferAmount[playerid], pBankTransferPlayerID[playerid]);
		mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
		//
		new to_playerid = GetPlayeridFromId(pBankTransferPlayerID[playerid]);
		PI[playerid][pi_BANK_MONEY] -= pBankTransferAmount[playerid];
		Text_Send(playerid, $MESSAGE_INFO_TRANSFER, pBankTransferAmount[playerid], pBankTransferName[playerid]);
		if(to_playerid != INVALID_PLAYER_ID)
		{
			PI[to_playerid][pi_BANK_MONEY] += pBankTransferAmount[playerid];
			Text_Send(to_playerid, $MESSAGE_INFO_GOTTRANSFER, pBankTransferName[playerid], pBankTransferAmount[playerid]);
		}
		RegisterBankMovement(PI[playerid][pi_ID], pBankTransferPlayerID[playerid], PI[playerid][pi_NAME], pBankTransferName[playerid], pBankTransferAmount[playerid]);
	}
	else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using callback OnBankDialogResponse, $DIALOG_BANK_POINT_CAPTION, $DIALOG_BANK_POINT_BODY, $DIALOG_BANK_POINT_YES, $DIALOG_BANK_POINT_NO);
	return 1;
}