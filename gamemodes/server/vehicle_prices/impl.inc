#include <YSI\y_hooks>

hook OnScriptInit()
{
	inline OnVehiclePricesLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				new slot = Iter_Free(Vehicle_Prices);
				if(slot != cellmin)
				{
					cache_get_value_int(i, "modelid", Vehicle_Prices[slot][vehicle_price_MODELID]);
					cache_get_value_int(i, "price", Vehicle_Prices[slot][vehicle_price_PRICE]);
					cache_get_value_int(i, "level", Vehicle_Prices[slot][vehicle_price_LEVEL]);
					Iter_Add(Vehicle_Prices, slot);
				}
				else print("[ERROR]: Error al obtener espacio libre en OnVehiclePricesLoad");
			}
			CallRemoteFunction("OnVehiclesPricesLoad", "");
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnVehiclePricesLoad' (db error)");
		}
	}
	print("[INFO]: Cargando vehicle_prices...");
	mysql_tquery_inline(vcrp_db, "SELECT * FROM vehicle_prices;", using inline OnVehiclePricesLoad, "");
	return 1;
}

YCMD:vehprices(playerid, params[], help)
{
	pCurrentDialogPage[playerid] = 0;

	//
	new dialog_caption[64], count, dialog_str[64], dialog_message[64 * (DIALOG_PAGINATION_SIZE + DIALOG_PAGINATION_EXTRA_BUTTONS)]; 
	format(dialog_caption, sizeof dialog_caption, "Vehicle prices (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Vehicle_Prices)));
	foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
	{
		if(Iter_Contains(Vehicle_Prices, x))
		{
			format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(Vehicle_Prices[x][vehicle_price_MODELID]), Vehicle_Prices[x][vehicle_price_MODELID], Vehicle_Prices[x][vehicle_price_PRICE]);
			strcat(dialog_message, dialog_str);
			pExtraButtons[playerid][count++] = x;
		}
	}
	pExtraButtons[playerid][count++] = DIALOG_PAGINATION_ADD;
	strcat(dialog_message, "\t+ Add vehicle\n");
	pExtraButtons[playerid][count++] = DIALOG_PAGINATION_NEXT;
	strcat(dialog_message, "\tNext page\n");
	pExtraButtons[playerid][count++] = DIALOG_PAGINATION_PREVIOUS;
	strcat(dialog_message, "\tPrevious page\n");
	//

	inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, inputtext
		if(response)
		{
			switch(pExtraButtons[playerid][listitem])
			{
				case DIALOG_PAGINATION_ADD:
				{
					inline OnPlayerAddVehiclePrice(ex_pid, ex_dialogid, ex_response, ex_listitem, string:ex_inputtext[])
					{
						#pragma unused ex_pid, ex_dialogid, ex_listitem
						if(ex_response)
						{
							new modelid, price;
							if(sscanf(ex_inputtext, "p<,>dd", modelid, price))
							{
								SendClientMessage(playerid, -1, "Wrong format!");
								Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");	
							}
							else
							{
								if(IsValidVehicleModelId(modelid))
								{
									if(IsVehPriceModelFree(modelid))
									{
										new slot = Iter_Free(Vehicle_Prices);
										if(slot == cellmin)
										{
											new string[128];
											format(string, sizeof string, "No free slot, %d/%d!", Iter_Count(Vehicle_Prices), MAX_VEHICLE_MODELIDS);
											SendClientMessage(playerid, -1, string);
											Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
										}
										else
										{
											inline OnVehiclePriceInserted()
											{
												Vehicle_Prices[slot][vehicle_price_MODELID] = modelid;
												Vehicle_Prices[slot][vehicle_price_PRICE] = price;
												Iter_Add(Vehicle_Prices, slot);

												new string[128];
												format(string, sizeof string, "Vehicle price modelid %d (%s) added $%d, %d/%d!", modelid, GetVehicleNameByModelid(modelid), price, Iter_Count(Vehicle_Prices), MAX_VEHICLE_MODELIDS);
												SendClientMessage(playerid, -1, string);

												//
												pCurrentDialogPage[playerid] = GetLastDialogPage(Iter_Count(Vehicle_Prices));

												//
												dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
												format(dialog_caption, sizeof dialog_caption, "Vehicle prices (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Vehicle_Prices)));
												foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
												{
													if(Iter_Contains(Vehicle_Prices, x))
													{
														format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(Vehicle_Prices[x][vehicle_price_MODELID]), Vehicle_Prices[x][vehicle_price_MODELID], Vehicle_Prices[x][vehicle_price_PRICE]);
														strcat(dialog_message, dialog_str);
														pExtraButtons[playerid][count++] = x;
													}
												}
												pExtraButtons[playerid][count++] = DIALOG_PAGINATION_ADD;
												strcat(dialog_message, "\t+ Add vehicle\n");
												pExtraButtons[playerid][count++] = DIALOG_PAGINATION_NEXT;
												strcat(dialog_message, "\tNext page\n");
												pExtraButtons[playerid][count++] = DIALOG_PAGINATION_PREVIOUS;
												strcat(dialog_message, "\tPrevious page\n");
												//

												Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
											}

											mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO vehicle_prices (modelid, price) VALUES (%d, %d);", modelid, price);
											mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnVehiclePriceInserted, "");
										}
									}
									else
									{
										new string[64];
										format(string, sizeof string, "Modelid %d already exists in vehicle prices!", modelid);
										SendClientMessage(playerid, -1, string);
										Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
									}
								}
								else
								{
									SendClientMessage(playerid, -1, "Invalid vehicle modelid!");
									Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
								}
							}
						}
						else Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
					}
					Dialog_ShowCallback(playerid, using inline OnPlayerAddVehiclePrice, DIALOG_STYLE_INPUT, "Add vehicle price", "Format: modelid, price\nExample: 400, 100000", "Add", "X");
				}
				case DIALOG_PAGINATION_NEXT:
				{
					pCurrentDialogPage[playerid] = GetNextDialogPage(pCurrentDialogPage[playerid], Iter_Count(Vehicle_Prices));

					//
					dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
					format(dialog_caption, sizeof dialog_caption, "Vehicle prices (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Vehicle_Prices)));
					foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
					{
						if(Iter_Contains(Vehicle_Prices, x))
						{
							format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(Vehicle_Prices[x][vehicle_price_MODELID]), Vehicle_Prices[x][vehicle_price_MODELID], Vehicle_Prices[x][vehicle_price_PRICE]);
							strcat(dialog_message, dialog_str);
							pExtraButtons[playerid][count++] = x;
						}
					}
					pExtraButtons[playerid][count++] = DIALOG_PAGINATION_ADD;
					strcat(dialog_message, "\t+ Add vehicle\n");
					pExtraButtons[playerid][count++] = DIALOG_PAGINATION_NEXT;
					strcat(dialog_message, "\tNext page\n");
					pExtraButtons[playerid][count++] = DIALOG_PAGINATION_PREVIOUS;
					strcat(dialog_message, "\tPrevious page\n");
					//

					Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
				}
				case DIALOG_PAGINATION_PREVIOUS:
				{
					pCurrentDialogPage[playerid] = GetPreviousDialogPage(pCurrentDialogPage[playerid], Iter_Count(Vehicle_Prices));

					//
					dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
					format(dialog_caption, sizeof dialog_caption, "Vehicle prices (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Vehicle_Prices)));
					foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
					{
						if(Iter_Contains(Vehicle_Prices, x))
						{
							format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(Vehicle_Prices[x][vehicle_price_MODELID]), Vehicle_Prices[x][vehicle_price_MODELID], Vehicle_Prices[x][vehicle_price_PRICE]);
							strcat(dialog_message, dialog_str);
							pExtraButtons[playerid][count++] = x;
						}
					}
					pExtraButtons[playerid][count++] = DIALOG_PAGINATION_ADD;
					strcat(dialog_message, "\t+ Add vehicle\n");
					pExtraButtons[playerid][count++] = DIALOG_PAGINATION_NEXT;
					strcat(dialog_message, "\tNext page\n");
					pExtraButtons[playerid][count++] = DIALOG_PAGINATION_PREVIOUS;
					strcat(dialog_message, "\tPrevious page\n");
					//
					
					Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
				}
				default:
				{
					new edit_dialog_caption[64], edit_dialog_message[128];
					format(edit_dialog_caption, sizeof edit_dialog_caption, "Vehicle %d (%s)", Vehicle_Prices[ pExtraButtons[playerid][listitem] ][vehicle_price_MODELID], GetVehicleNameByModelid(Vehicle_Prices[ pExtraButtons[playerid][listitem] ][vehicle_price_MODELID]));
					format(edit_dialog_message, sizeof edit_dialog_message, "Price\t$%d\n- Delete", Vehicle_Prices[ pExtraButtons[playerid][listitem] ][vehicle_price_PRICE]);

					inline OnPlayerEditVehPriceDialog(ex_pid, ex_dialogid, ex_response, ex_listitem, string:ex_inputtext[])
					{
						#pragma unused ex_pid, ex_dialogid, ex_inputtext
						if(ex_response)
						{
							switch(ex_listitem)
							{
								case 0: //price
								{
									inline OnEditPriceVehPriceDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
									{
										#pragma unused in_pid, in_dialogid, in_listitem
										if(in_response)
										{
											new integer;
											if(sscanf(in_inputtext, "d", integer))
											{
												SendClientMessage(playerid, -1, "Wrong format!");
												Dialog_ShowCallback(playerid, using inline OnPlayerEditVehPriceDialog, DIALOG_STYLE_TABLIST, edit_dialog_caption, edit_dialog_message, ">>", "X");		
											}
											else
											{
												Vehicle_Prices[ pExtraButtons[playerid][listitem] ][vehicle_price_PRICE] = integer;
												UpdateVehiclePriceDb(pExtraButtons[playerid][listitem]);
												
												//
												format(edit_dialog_caption, sizeof edit_dialog_caption, "Vehicle %d (%s)", Vehicle_Prices[ pExtraButtons[playerid][listitem] ][vehicle_price_MODELID], GetVehicleNameByModelid(Vehicle_Prices[ pExtraButtons[playerid][listitem] ][vehicle_price_MODELID]));
												format(edit_dialog_message, sizeof edit_dialog_message, "Price\t$%d\n- Delete", Vehicle_Prices[ pExtraButtons[playerid][listitem] ][vehicle_price_PRICE]);
												//

												SendClientMessage(playerid, -1, "Price updated!");
												Dialog_ShowCallback(playerid, using inline OnPlayerEditVehPriceDialog, DIALOG_STYLE_TABLIST, edit_dialog_caption, edit_dialog_message, ">>", "X");		
											}
										}
										else Dialog_ShowCallback(playerid, using inline OnPlayerEditVehPriceDialog, DIALOG_STYLE_TABLIST, edit_dialog_caption, edit_dialog_message, ">>", "X");
									}

									new message_dialog[64];
									format(message_dialog, sizeof message_dialog, "Current price: $%d", Vehicle_Prices[ pExtraButtons[playerid][listitem] ][vehicle_price_PRICE]);
									Dialog_ShowCallback(playerid, using inline OnEditPriceVehPriceDialog, DIALOG_STYLE_INPUT, "Edit price", message_dialog, ">>", "X");
								}
								case 1: //delete
								{
									RemoveVehiclePrice(pExtraButtons[playerid][listitem], true);
									if(!IsValidPage(pCurrentDialogPage[playerid], Iter_Count(Vehicle_Prices))) pCurrentDialogPage[playerid] = GetLastDialogPage(Iter_Count(Vehicle_Prices));

									//
									dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
									format(dialog_caption, sizeof dialog_caption, "Vehicle prices (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Vehicle_Prices)));
									foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
									{
										if(Iter_Contains(Vehicle_Prices, x))
										{
											format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(Vehicle_Prices[x][vehicle_price_MODELID]), Vehicle_Prices[x][vehicle_price_MODELID], Vehicle_Prices[x][vehicle_price_PRICE]);
											strcat(dialog_message, dialog_str);
											pExtraButtons[playerid][count++] = x;
										}
									}
									pExtraButtons[playerid][count++] = DIALOG_PAGINATION_ADD;
									strcat(dialog_message, "\t+ Add vehicle\n");
									pExtraButtons[playerid][count++] = DIALOG_PAGINATION_NEXT;
									strcat(dialog_message, "\tNext page\n");
									pExtraButtons[playerid][count++] = DIALOG_PAGINATION_PREVIOUS;
									strcat(dialog_message, "\tPrevious page\n");
									//
									
									Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
								}
							}
						}
						else
						{
							//
							dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
							format(dialog_caption, sizeof dialog_caption, "Vehicle prices (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Vehicle_Prices)));
							foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
							{
								if(Iter_Contains(Vehicle_Prices, x))
								{
									format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(Vehicle_Prices[x][vehicle_price_MODELID]), Vehicle_Prices[x][vehicle_price_MODELID], Vehicle_Prices[x][vehicle_price_PRICE]);
									strcat(dialog_message, dialog_str);
									pExtraButtons[playerid][count++] = x;
								}
							}
							pExtraButtons[playerid][count++] = DIALOG_PAGINATION_ADD;
							strcat(dialog_message, "\t+ Add vehicle\n");
							pExtraButtons[playerid][count++] = DIALOG_PAGINATION_NEXT;
							strcat(dialog_message, "\tNext page\n");
							pExtraButtons[playerid][count++] = DIALOG_PAGINATION_PREVIOUS;
							strcat(dialog_message, "\tPrevious page\n");
							//

							Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
						}
					}

					Dialog_ShowCallback(playerid, using inline OnPlayerEditVehPriceDialog, DIALOG_STYLE_TABLIST, edit_dialog_caption, edit_dialog_message, ">>", "X");
				}
			}
		}
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
	return 1;
}