#include <YSI\y_hooks>

loadtext lang[atm];

hook OnPlayerDisconnect(playerid, reason)
{
	DestroyPlayerAtmTds(playerid);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(pUsingAtm[playerid]) CancelSelectTextDraw(playerid);
	return 1;
}

public OnPlayerRequestAtm(playerid)
{
	if(pUsingAtm[playerid]) return 0;
	ShowPlayerAtm(playerid);
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(pUsingAtm[playerid])
	{
		if(clickedid == Text:INVALID_TEXT_DRAW)
		{
			HidePlayerAtm(playerid);
			return 1;
		}
	}
	return 0;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	if(pUsingAtm[playerid])
	{	
		if(playertextid == PTD_Atm[playerid][3]) //retirar
		{
			inline OnAtmDialogResponse(pid, dialogid, response, listitem, string:inputtext[])
			{
				#pragma unused pid, dialogid, listitem
				if(response)
				{
					if(sscanf(inputtext, "d", inputtext[0])) Text_Send(playerid, $MESSAGE_ERROR_WRONG_FORMAT);
					else
					{
						if(inputtext[0] <= 0) Text_Send(playerid, $MESSAGE_ERROR_NEGATIVE);
						else if(inputtext[0] > MAX_ATM_MOVEMENT) Text_Send(playerid, $MESSAGE_ERROR_MAX_TRANSACTION, MAX_ATM_MOVEMENT);
						else if(inputtext[0] > PI[playerid][pi_BANK_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NOBANKMONEY, inputtext[0]);
						else
						{
							PI[playerid][pi_BANK_MONEY] -= inputtext[0];
							GivePlayerMoneyEx(playerid, inputtext[0], true);
							FormatPlayerAtmInfoTds(playerid);
							Text_Send(playerid, $MESSAGE_INFO_WITHDRAW, inputtext[0]);
							orm_update(PI[playerid][pi_ORM]);
							RegisterBankMovement(PI[playerid][pi_ID], PI[playerid][pi_ID], PI[playerid][pi_NAME], PI[playerid][pi_NAME], -inputtext[0]);
							CallRemoteFunction("OnPlayerAtmWithdraw", "i", playerid);
						}
					}
				}

				PlayerTextDrawShow(playerid, PTD_Atm[playerid][3]);
				PlayerTextDrawShow(playerid, PTD_Atm[playerid][4]);
				PlayerTextDrawShow(playerid, PTD_Atm[playerid][5]);
				PlayerTextDrawShow(playerid, PTD_Atm[playerid][6]);
				PlayerTextDrawShow(playerid, PTD_Atm[playerid][7]);
				PlayerTextDrawShow(playerid, PTD_Atm[playerid][8]);
			}

			PlayerTextDrawHide(playerid, PTD_Atm[playerid][3]);
			PlayerTextDrawHide(playerid, PTD_Atm[playerid][4]);
			PlayerTextDrawHide(playerid, PTD_Atm[playerid][5]);
			PlayerTextDrawHide(playerid, PTD_Atm[playerid][6]);
			PlayerTextDrawHide(playerid, PTD_Atm[playerid][7]);
			PlayerTextDrawHide(playerid, PTD_Atm[playerid][8]);
			Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnAtmDialogResponse, $DIALOG_ATM_WITHDRAW_CAPTION, $DIALOG_ATM_WITHDRAW_BODY, $DIALOG_ATM_WITHDRAW_YES, $DIALOG_ATM_WITHDRAW_NO, PI[playerid][pi_BANK_MONEY]);
			return 1;
		}
		else if(playertextid == PTD_Atm[playerid][4]) //depositar
		{
			inline OnAtmDialogResponse(pid, dialogid, response, listitem, string:inputtext[])
			{
				#pragma unused pid, dialogid, listitem
				if(response)
				{
					if(sscanf(inputtext, "d", inputtext[0])) Text_Send(playerid, $MESSAGE_ERROR_WRONG_FORMAT);
					else
					{
						if(inputtext[0] <= 0) Text_Send(playerid, $MESSAGE_ERROR_NEGATIVE);
						else if(inputtext[0] > MAX_ATM_MOVEMENT) Text_Send(playerid, $MESSAGE_ERROR_MAX_TRANSACTION, MAX_ATM_MOVEMENT);
						else if(inputtext[0] > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NOMONEY, inputtext[0]);
						else
						{
							GivePlayerMoneyEx(playerid, -inputtext[0], true);
							PI[playerid][pi_BANK_MONEY] += inputtext[0];
							FormatPlayerAtmInfoTds(playerid);
							Text_Send(playerid, $MESSAGE_INFO_DEPOSIT, inputtext[0]);
							orm_update(PI[playerid][pi_ORM]);
							RegisterBankMovement(PI[playerid][pi_ID], PI[playerid][pi_ID], PI[playerid][pi_NAME], PI[playerid][pi_NAME], inputtext[0]);
							CallRemoteFunction("OnPlayerAtmDeposit", "i", playerid);
						}
					}
				}

				PlayerTextDrawShow(playerid, PTD_Atm[playerid][3]);
				PlayerTextDrawShow(playerid, PTD_Atm[playerid][4]);
				PlayerTextDrawShow(playerid, PTD_Atm[playerid][5]);
				PlayerTextDrawShow(playerid, PTD_Atm[playerid][6]);
				PlayerTextDrawShow(playerid, PTD_Atm[playerid][7]);
				PlayerTextDrawShow(playerid, PTD_Atm[playerid][8]);
			}

			PlayerTextDrawHide(playerid, PTD_Atm[playerid][3]);
			PlayerTextDrawHide(playerid, PTD_Atm[playerid][4]);
			PlayerTextDrawHide(playerid, PTD_Atm[playerid][5]);
			PlayerTextDrawHide(playerid, PTD_Atm[playerid][6]);
			PlayerTextDrawHide(playerid, PTD_Atm[playerid][7]);
			PlayerTextDrawHide(playerid, PTD_Atm[playerid][8]);
			Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnAtmDialogResponse, $DIALOG_ATM_DEPOSIT_CAPTION, $DIALOG_ATM_DEPOSIT_BODY, $DIALOG_ATM_DEPOSIT_YES, $DIALOG_ATM_DEPOSIT_NO, PI[playerid][pi_MONEY]);
			return 1;
		}
		else if(playertextid == PTD_Atm[playerid][5]) //salir
		{
			CancelSelectTextDraw(playerid);
			return 1;
		}
	}
	return 0;
}