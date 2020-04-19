#define MAX_BANK_MOVEMENT 1000000000

forward OnPlayerRequestBankPoint(playerid);
forward OnBankDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
forward OnAmountTranferBankDialog(playerid, dialogid, response, listitem, inputtext[]);
forward OnConfirmTranferBankDialog(playerid, dialogid, response, listitem, inputtext[]);

new 
	pBankTransferAmount[MAX_PLAYERS],
	pBankTransferName[MAX_PLAYERS][24],
	pBankTransferPlayerID[MAX_PLAYERS];