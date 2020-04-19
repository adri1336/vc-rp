#include <YSI\y_hooks>

YCMD:svehs(playerid, params[], help)
{
	pCurrentDialogPage[playerid] = 0;

	//
	new dialog_caption[64], count, dialog_str[64], dialog_message[64 * (DIALOG_PAGINATION_SIZE + DIALOG_PAGINATION_EXTRA_BUTTONS)]; 
	format(dialog_caption, sizeof dialog_caption, "Sale Vehicles (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(saleVehicles)));
	foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
	{
		if(Iter_Contains(saleVehicles, x))
		{
			format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\t%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(saleVehicles[x][saleVeh_MODELID]), saleVehicles[x][saleVeh_MODELID], GetVehiclePriceByModelid(saleVehicles[x][saleVeh_MODELID]), GetVehicleLevelByModelid(saleVehicles[x][saleVeh_MODELID]));
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
					inline OnPlayerAddSaleVehDialog(ex_pid, ex_dialogid, ex_response, ex_listitem, string:ex_inputtext[])
					{
						#pragma unused ex_pid, ex_dialogid, ex_listitem
						if(ex_response)
						{
							new modelid;
							if(sscanf(ex_inputtext, "d", modelid))
							{
								SendClientMessage(playerid, -1, "Wrong format!");
								Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");	
							}
							else
							{
								if(IsValidVehicleModelId(modelid))
								{
									if(IsVehSaleModelFree(modelid))
									{
										new slot = GetFreeSaleVehicleSlot();
										if(slot == cellmin)
										{
											new string[128];
											format(string, sizeof string, "No free slot, %d/%d!", Iter_Count(saleVehicles), MAX_SALE_VEHICLES);
											SendClientMessage(playerid, -1, string);
											Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
										}
										else
										{
											inline OnSaleVehicleInserted()
											{
												saleVehicles[slot][saleVeh_ID] = cache_insert_id();
												saleVehicles[slot][saleVeh_MODELID] = modelid;
												saleVehicles[slot][saleVeh_SLOTID] = INVALID_MENU_ID;
												AddSaleVehicle(slot);

												new string[128];
												format(string, sizeof string, "Vehicle modelid %d (%s) added for sale, %d/%d!", modelid, GetVehicleNameByModelid(modelid), Iter_Count(saleVehicles), MAX_SALE_VEHICLES);
												SendClientMessage(playerid, -1, string);

												//
												pCurrentDialogPage[playerid] = GetLastDialogPage(Iter_Count(saleVehicles));

												//
												dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
												format(dialog_caption, sizeof dialog_caption, "Sale Vehicles (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(saleVehicles)));
												foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
												{
													if(Iter_Contains(saleVehicles, x))
													{
														format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\t%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(saleVehicles[x][saleVeh_MODELID]), saleVehicles[x][saleVeh_MODELID], GetVehiclePriceByModelid(saleVehicles[x][saleVeh_MODELID]), GetVehicleLevelByModelid(saleVehicles[x][saleVeh_MODELID]));
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

											mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO vehicles_shop_sunshine (modelid) VALUES (%d);", modelid);
											mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnSaleVehicleInserted, "");
										}
									}
									else
									{
										new string[64];
										format(string, sizeof string, "Modelid %d already exists in sale vehicles!", modelid);
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
					Dialog_ShowCallback(playerid, using inline OnPlayerAddSaleVehDialog, DIALOG_STYLE_INPUT, "Add sale vehicle", "Format: modelid\nExample: 400", "Add", "X");
				}
				case DIALOG_PAGINATION_NEXT:
				{
					pCurrentDialogPage[playerid] = GetNextDialogPage(pCurrentDialogPage[playerid], Iter_Count(saleVehicles));

					//
					dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
					format(dialog_caption, sizeof dialog_caption, "Sale Vehicles (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(saleVehicles)));
					foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
					{
						if(Iter_Contains(saleVehicles, x))
						{
							format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\t%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(saleVehicles[x][saleVeh_MODELID]), saleVehicles[x][saleVeh_MODELID], GetVehiclePriceByModelid(saleVehicles[x][saleVeh_MODELID]), GetVehicleLevelByModelid(saleVehicles[x][saleVeh_MODELID]));
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
					pCurrentDialogPage[playerid] = GetPreviousDialogPage(pCurrentDialogPage[playerid], Iter_Count(saleVehicles));

					//
					dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
					format(dialog_caption, sizeof dialog_caption, "Sale Vehicles (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(saleVehicles)));
					foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
					{
						if(Iter_Contains(saleVehicles, x))
						{
							format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\t%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(saleVehicles[x][saleVeh_MODELID]), saleVehicles[x][saleVeh_MODELID], GetVehiclePriceByModelid(saleVehicles[x][saleVeh_MODELID]), GetVehicleLevelByModelid(saleVehicles[x][saleVeh_MODELID]));
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
					format(edit_dialog_caption, sizeof edit_dialog_caption, "Vehicle %d (%s)", saleVehicles[ pExtraButtons[playerid][listitem] ][saleVeh_MODELID], GetVehicleNameByModelid(saleVehicles[ pExtraButtons[playerid][listitem] ][saleVeh_MODELID]));
					format(edit_dialog_message, sizeof edit_dialog_message, "Modelid\t%d\n- Delete", saleVehicles[ pExtraButtons[playerid][listitem] ][saleVeh_MODELID]);

					inline OnPlayerEditSaleVehDialog(ex_pid, ex_dialogid, ex_response, ex_listitem, string:ex_inputtext[])
					{
						#pragma unused ex_pid, ex_dialogid, ex_inputtext
						if(ex_response)
						{
							switch(ex_listitem)
							{
								case 0: //modelid
								{
									inline OnEditModelidSaleVehDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
									{
										#pragma unused in_pid, in_dialogid, in_listitem
										if(in_response)
										{
											new integer;
											if(sscanf(in_inputtext, "d", integer))
											{
												SendClientMessage(playerid, -1, "Wrong format!");
												Dialog_ShowCallback(playerid, using inline OnPlayerEditSaleVehDialog, DIALOG_STYLE_TABLIST, edit_dialog_caption, edit_dialog_message, ">>", "X");		
											}
											else
											{
												if(IsValidVehicleModelId(integer))
												{
													if(IsVehSaleModelFree(integer))
													{
														saleVehicles[ pExtraButtons[playerid][listitem] ][saleVeh_MODELID] = integer;
														SetPreviewMenuModel(saleVehiclesMenu, saleVehicles[ pExtraButtons[playerid][listitem] ][saleVeh_SLOTID], saleVehicles[ pExtraButtons[playerid][listitem] ][saleVeh_MODELID]);
														UpdateSaleVehicleDb(pExtraButtons[playerid][listitem]);
														
														//
														format(edit_dialog_caption, sizeof edit_dialog_caption, "Vehicle %d (%s)", saleVehicles[ pExtraButtons[playerid][listitem] ][saleVeh_MODELID], GetVehicleNameByModelid(saleVehicles[ pExtraButtons[playerid][listitem] ][saleVeh_MODELID]));
														format(edit_dialog_message, sizeof edit_dialog_message, "Modelid\t%d\n- Delete", saleVehicles[ pExtraButtons[playerid][listitem] ][saleVeh_MODELID]);
														//

														SendClientMessage(playerid, -1, "Modelid updated!");
														Dialog_ShowCallback(playerid, using inline OnPlayerEditSaleVehDialog, DIALOG_STYLE_TABLIST, edit_dialog_caption, edit_dialog_message, ">>", "X");		
													}
													else
													{
														new string[64];
														format(string, sizeof string, "Modelid %d already exists in sale vehicles!", integer);
														SendClientMessage(playerid, -1, string);
														Dialog_ShowCallback(playerid, using inline OnPlayerEditSaleVehDialog, DIALOG_STYLE_TABLIST, edit_dialog_caption, edit_dialog_message, ">>", "X");		
													}
												}
												else
												{
													SendClientMessage(playerid, -1, "Invalid vehicle modelid!");
													Dialog_ShowCallback(playerid, using inline OnPlayerEditSaleVehDialog, DIALOG_STYLE_TABLIST, edit_dialog_caption, edit_dialog_message, ">>", "X");		
												}
											}
										}
										else Dialog_ShowCallback(playerid, using inline OnPlayerEditSaleVehDialog, DIALOG_STYLE_TABLIST, edit_dialog_caption, edit_dialog_message, ">>", "X");
									}

									new message_dialog[64];
									format(message_dialog, sizeof message_dialog, "Current modelid: %d", saleVehicles[ pExtraButtons[playerid][listitem] ][saleVeh_MODELID]);
									Dialog_ShowCallback(playerid, using inline OnEditModelidSaleVehDialog, DIALOG_STYLE_INPUT, "Edit modelid", message_dialog, ">>", "X");
								}
								case 1: //delete
								{
									RemoveSaleVehicle(pExtraButtons[playerid][listitem], true);
									if(!IsValidPage(pCurrentDialogPage[playerid], Iter_Count(saleVehicles))) pCurrentDialogPage[playerid] = GetLastDialogPage(Iter_Count(saleVehicles));

									//
									dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
									format(dialog_caption, sizeof dialog_caption, "Sale Vehicles (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(saleVehicles)));
									foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
									{
										if(Iter_Contains(saleVehicles, x))
										{
											format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\t%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(saleVehicles[x][saleVeh_MODELID]), GetVehiclePriceByModelid(saleVehicles[x][saleVeh_MODELID]), GetVehicleLevelByModelid(saleVehicles[x][saleVeh_MODELID]));
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
							format(dialog_caption, sizeof dialog_caption, "Sale Vehicles (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(saleVehicles)));
							foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
							{
								if(Iter_Contains(saleVehicles, x))
								{
									format(dialog_str, sizeof dialog_str, "%d. %s [%d]\t$%d\t%d\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), GetVehicleNameByModelid(saleVehicles[x][saleVeh_MODELID]), GetVehiclePriceByModelid(saleVehicles[x][saleVeh_MODELID]), GetVehicleLevelByModelid(saleVehicles[x][saleVeh_MODELID]));
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

					Dialog_ShowCallback(playerid, using inline OnPlayerEditSaleVehDialog, DIALOG_STYLE_TABLIST, edit_dialog_caption, edit_dialog_message, ">>", "X");
				}
			}
		}
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, dialog_caption, dialog_message, ">>", "X");
	return 1;
}

YCMD:setoldvehprice(playerid, params[], help)
{
	if(sscanf(params, "dd", params[0], params[1])) SendClientMessage(playerid, -1, "Syntax: /setoldvehprice [vindex] [price]");
	else
	{
		if(!IsValidVehicle(params[0])) SendClientMessage(playerid, -1, "Invalid vindex!");
		else
		{
			if(VehicleInfo[params[0]][vinfo_TYPE] == VEHICLE_TYPE_SELL)
			{
				VehicleInfo[params[0]][vinfo_PRICE] = params[1];
				UpdateSaleOldVehicleDb(params[0]);
				UpdateSaleOldVehicleLabel(params[0]);
			}
			else SendClientMessage(playerid, -1, "Not a sell vehicle!");
		}
	}
	return 1;
}

YCMD:setoldvehlevel(playerid, params[], help)
{
	if(sscanf(params, "dd", params[0], params[1])) SendClientMessage(playerid, -1, "Syntax: /setoldvehlevel [vindex] [level]");
	else
	{
		if(!IsValidVehicle(params[0])) SendClientMessage(playerid, -1, "Invalid vindex!");
		else
		{
			if(VehicleInfo[params[0]][vinfo_TYPE] == VEHICLE_TYPE_SELL)
			{
				VehicleInfo[params[0]][vinfo_LEVEL] = params[1];
				UpdateSaleOldVehicleDb(params[0]);
				UpdateSaleOldVehicleLabel(params[0]);
			}
			else SendClientMessage(playerid, -1, "Not a sell vehicle!");
		}
	}
	return 1;
}