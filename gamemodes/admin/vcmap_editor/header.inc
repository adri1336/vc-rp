new pCurrentVcObjectIndex[MAX_PLAYERS],
	pVcMdlTypeSelected[MAX_PLAYERS],
	bool:SaveVcEditorChanges = false;

forward OnVcSsDialog(playerid, dialogid, response, listitem, inputtext[]);
forward OnPlayerViceCityObjectAdded(playerid, index);