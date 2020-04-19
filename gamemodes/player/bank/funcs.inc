loadtext lang[bank];

RegisterBankMovement(from_id, to_id, from_name[], to_name[], amount)
{
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_bank_movements (date, from_id, to_id, from_name, to_name, amount) VALUES (%s, %d, %d, '%e', '%e', %d);", getDateTimeDB(), from_id, to_id, from_name, to_name, amount);
	mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	return 1;
}

GetMovementHeaderDialog(playerid)
{
	new header[45];
	Text_Format_Dialog(header, sizeof header, PI[playerid][pi_LANG_ID], $DIALOG_BANK_MOVEMENTS_HEADER);
	return header;
}

GetPlayerBankMovementName(playerid, movement)
{
	new movement_name[24];
	switch(movement)
	{
		case 0: Text_Format_Dialog(movement_name, sizeof movement_name, PI[playerid][pi_LANG_ID], $BANK_MOVEMENT_WITHDRAW);
		case 1: Text_Format_Dialog(movement_name, sizeof movement_name, PI[playerid][pi_LANG_ID], $BANK_MOVEMENT_DEPOSIT);
		case 2: Text_Format_Dialog(movement_name, sizeof movement_name, PI[playerid][pi_LANG_ID], $BANK_MOVEMENT_TRANSFER_TO);
		case 3: Text_Format_Dialog(movement_name, sizeof movement_name, PI[playerid][pi_LANG_ID], $BANK_MOVEMENT_TRANSFER_FROM);
	}
	return movement_name;
}