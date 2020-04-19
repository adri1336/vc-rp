#include <YSI\y_hooks>

loadtext lang[business];

hook OnPlayerConnect(playerid)
{
	for(new i = 0; i < sizeof pBProducts_Products_PTD[]; i ++)
	{
		for(new j = 0; j < sizeof pBProducts_Products_PTD[][]; j ++)
		{
			pBProducts_Products_PTD[playerid][i][j] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	Iter_Clear(PlayerBusiness<playerid>);
	if(pBusinessTmpMenu[playerid] != INVALID_MENU_ID)
	{
		DeletePreviewMenu(pBusinessTmpMenu[playerid]);
		pBusinessTmpMenu[playerid] = INVALID_MENU_ID;
	}
	DestroyBProducts(playerid);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_SPECTATING || newstate == PLAYER_STATE_WASTED)
	{
		if(pBusinessTmpMenu[playerid] != INVALID_MENU_ID)
		{
			HidePreviewMenuForPlayer(playerid);
			DeletePreviewMenu(pBusinessTmpMenu[playerid]);
			pBusinessTmpMenu[playerid] = INVALID_MENU_ID;
		}
		if(pBProducts_Enabled[playerid])
		CancelSelectTextDraw(playerid);
	}
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(pBusinessTmpMenu[playerid] != INVALID_MENU_ID)
	{
		HidePreviewMenuForPlayer(playerid);
		DeletePreviewMenu(pBusinessTmpMenu[playerid]);
		pBusinessTmpMenu[playerid] = INVALID_MENU_ID;
	}
	if(pBProducts_Enabled[playerid])
	CancelSelectTextDraw(playerid);
	return 1;
}

hook OnPlayerLogin(playerid)
{
	foreach(new i : BusinessData)
	{
		if(BusinessData[i][bdata_ID_PLAYER] == PI[playerid][pi_ID])
		{
			Iter_Add(PlayerBusiness<playerid>, i);
		}
	}
	return 1;
}

hook OnPlayerRequestBSPoint(playerid, bsale_type, index_business)
{
	if((bsale_type == BUSINESS_SALE_TYPE_WEAPONS || bsale_type == BUSINESS_SALE_TYPE_AMMO) && !PlayerInvContainsItem(playerid, _:INV_ITEM_GUN_LICENSE)) Text_Send(playerid, $MESSAGE_ERROR_GUN_LICENSE);
	else
	{
		new	total_products = CountBusinessProducts(index_business, bsale_type);
		if(total_products == 0) Text_Send(playerid, $MESSAGE_ERROR_NO_PRODUCTS);
		else
		{
			switch(bsale_type)
			{
				case BUSINESS_SALE_TYPE_ALL:
				{
					new line_str[32], dialog[32 * BUSINESS_SALE_TYPE_SIZE],
						count, listitems_ids[BUSINESS_SALE_TYPE_SIZE];
					foreach(new i : BTypes_STypes)
					{
						if(BTypes_STypes[i][btype_stype_ID_BUSINESS_TYPE] == BusinessData[index_business][bdata_ID_TYPE])
						{
							new bsale_name[32];
							format(bsale_name, sizeof bsale_name, "%s", GetBusinessSaleTypeNameFromId(playerid, BTypes_STypes[i][btype_stype_ID_BSALES_TYPE]));
							format(line_str, sizeof line_str, "%c%s\n", toupper(bsale_name[0]), bsale_name[1]);
							strcat(dialog, line_str);
							listitems_ids[count++] = BTypes_STypes[i][btype_stype_ID_BSALES_TYPE];
						}
					}

					inline OnPlayerDialog(pid, did, res, lis, string:inp[])
					{
						#pragma unused pid, did, inp
						if(res)
						{
							CallRemoteFunction("OnPlayerRequestBSPoint", "idd", playerid, listitems_ids[lis], index_business);
						}
					}
					Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_LIST, GetProductsDialogCaption(playerid), dialog, ">", "X");
				}
				case BUSINESS_SALE_TYPE_CLOTHES:
				{
					if(pBusinessTmpMenu[playerid] == INVALID_MENU_ID)
					{
						pBusinessTmpMenu[playerid] = CreatePreviewMenu("Clothes");
						if(pBusinessTmpMenu[playerid] != INVALID_MENU_ID)
						{
							new character_index = GetCharacterIndexById(PI[playerid][pi_CLOTHING_CHARACTER]);
							if(character_index != -1)
							{
								new count;
								foreach(new i : BProducts[index_business])
								{
									if(PI[playerid][pi_LEVEL] >= BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_LEVEL])
									{
										new gender, CLOTHES_TYPES:clotheid;
										if(!sscanf(BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_PARAMS], "p<,>dd", gender, _:clotheid))
										{
											if(gender == PI[playerid][pi_GENDER])
											{
												if(GetPlayerClotheIndexById(playerid, clotheid) == -1)
												{
													new clothe_index = GetCharacterClotheIndexById(character_index, clotheid);
													if(clothe_index != -1)
													{
														new modelid = CL_CharacterClothes[character_index][clothe_index][cl_char_clothe_MODELID];
														AddModelToPreviewMenu(pBusinessTmpMenu[playerid], modelid, BProducts[index_business][i][bproduct_PRICE], 0.0, 0.0, 0.0);
														pBusinessTmpProductIndex[playerid][count++] = i;
													}
												}
											}
										}
									}
								}
								if(count > 0)
								{
									pBusinessTmpMenu_Toys[playerid] = false;
									pBusinessTmpMenu_Clothes[playerid] = true;
									ShowPreviewMenuForPlayer(playerid, pBusinessTmpMenu[playerid], 0xFFFFFFFF, GetClotheMenuTitle(playerid));
								}
								else
								{
									DeletePreviewMenu(pBusinessTmpMenu[playerid]);
									pBusinessTmpMenu[playerid] = INVALID_MENU_ID;
									Text_Send(playerid, $MESSAGE_ERROR_CLOTHES);
								}
							}
						}
					}
				}
				case BUSINESS_SALE_TYPE_TOYS:
				{
					if(pBusinessTmpMenu[playerid] == INVALID_MENU_ID)
					{
						pBusinessTmpMenu[playerid] = CreatePreviewMenu("Toys");
						if(pBusinessTmpMenu[playerid] != INVALID_MENU_ID)
						{
							new count;
							foreach(new i : BProducts[index_business])
							{
								if(PI[playerid][pi_LEVEL] >= BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_LEVEL])
								{
									new modelid, color1, color2;
									if(!sscanf(BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_PARAMS], "p<,>ddd", modelid, color1, color2))
									{	
										if(GetPlayerToyIndexFromModelid(playerid, modelid) == -1)
										{
											AddModelToPreviewMenu(pBusinessTmpMenu[playerid], modelid, BProducts[index_business][i][bproduct_PRICE], 0.0, 0.0, 0.0);
											pBusinessTmpProductIndex[playerid][count++] = i;
										}
									}
								}
							}
							if(count > 0)
							{
								pBusinessTmpMenu_Clothes[playerid] = false;
								pBusinessTmpMenu_Toys[playerid] = true;
								ShowPreviewMenuForPlayer(playerid, pBusinessTmpMenu[playerid], 0xFFFFFFFF, GetToysMenuTitle(playerid));
							}
							else
							{
								DeletePreviewMenu(pBusinessTmpMenu[playerid]);
								pBusinessTmpMenu[playerid] = INVALID_MENU_ID;
								Text_Send(playerid, $MESSAGE_ERROR_TOYS);
							}
						}
					}
				}
				default:
				{
					//dialog pagination default
					pCurrentDialogPage[playerid] = 0;
					pDialogPagination_LastIndex[playerid] = -1;
					
					//dialog
					new dialog[128 * (DIALOG_PAGINATION_SIZE + 3)];
					GetPlayerDialogBusinessInfo(playerid, index_business, bsale_type, dialog);

					//action
					inline OnPlayerDialog(pid, did, res, lis, string:inp[])
					{
						#pragma unused pid, did, inp
						if(res)
						{
							switch(pExtraButtons[playerid][lis])
							{
								case DIALOG_PAGINATION_NEXT:
								{
									GetPlayerDialogBusinessInfo(playerid, index_business, bsale_type, dialog);
									Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST_HEADERS, GetProductsDialogCaption(playerid), dialog, ">", "X");
								}
								default:
								{
									if(BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_STOCK] <= 0) Text_Send(playerid, $MESSAGE_ERROR_NO_STOCK);
									else
									{
										if(BProducts_Info[ BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_INDEX_PRODUCT] ][bproduct_info_LEVEL] > PI[playerid][pi_LEVEL]) Text_Send(playerid, $MESSAGE_ERROR_LEVEL, BProducts_Info[ BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_INDEX_PRODUCT] ][bproduct_info_LEVEL]);
										else
										{
											new inv_itemid = BProducts_Info[ BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_INDEX_PRODUCT] ][bproduct_info_ID_INVITEM];
											if(inv_itemid != 0)
											{
												new total_price = BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_PRICE],
													amount = 1;
												
												if(INV_ITEMS_TYPES_Info[ INV_ITEMS_Info[inv_itemid][inv_item_TYPE] ][inv_item_type_MULTIPLIABLE])
												{
													new inv_params[128];
													format(inv_params, sizeof inv_params, "%s", BProducts_Info[ BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_INDEX_PRODUCT] ][bproduct_info_PARAMS]);

													new max_amount, inv_index = GetPlayerInvIndexByItem(playerid, inv_itemid, inv_params);
													if(inv_index == -1) max_amount = INV_ITEMS_TYPES_Info[ INV_ITEMS_Info[inv_itemid][inv_item_TYPE] ][inv_item_type_MAX_MULTIPLIED];
													else max_amount = INV_ITEMS_TYPES_Info[ INV_ITEMS_Info[inv_itemid][inv_item_TYPE] ][inv_item_type_MAX_MULTIPLIED] - PINV[playerid][inv_index][pinv_AMOUNT];

													if(max_amount <= 0) Text_Send(playerid, $MESSAGE_ERROR_INV);
													else
													{
														inline in_OnPlayerDialog(in_pid, in_did, in_res, in_lis, string:in_inp[])
														{
															#pragma unused in_pid, in_did, in_lis
															if(in_res)
															{
																if(!sscanf(in_inp, "d", amount))
																{
																	if(amount < 1 || amount > max_amount) Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
																	else
																	{
																		total_price *= amount;

																		if(total_price > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY_AMOUNT, total_price);
																		else
																		{
																			if(AddPlayerInventoryItem(playerid, inv_itemid, inv_params, amount))
																			{
																				GivePlayerMoneyEx(playerid, -total_price);
																				Text_Send(playerid, $GAMETEXT_INFO_PRODUCT_BOUGHT);
																				if(IsBusinessOccupied(index_business))
																				SellBusinessProductInfo(index_business, pExtraButtons[playerid][lis], playerid);
																			}
																			else Text_Send(playerid, $MESSAGE_ERROR_INV);
																		}
																	}
																}
																else Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
															}
														}
														Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline in_OnPlayerDialog, $DIALOG_BIZZ_BUY_AMOUNT_CAPTION, $DIALOG_BIZZ_BUY_AMOUNT_BODY, $DIALOG_BIZZ_BUY_AMOUNT_YES, $DIALOG_BIZZ_BUY_AMOUNT_NO, max_amount);
													}
												}
												else
												{
													if(total_price > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
													else
													{
														new inv_params[128];
														format(inv_params, sizeof inv_params, "%s", BProducts_Info[ BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_INDEX_PRODUCT] ][bproduct_info_PARAMS]);
														if(AddPlayerInventoryItem(playerid, inv_itemid, inv_params))
														{
															GivePlayerMoneyEx(playerid, -total_price);
															Text_Send(playerid, $GAMETEXT_INFO_PRODUCT_BOUGHT);
															if(IsBusinessOccupied(index_business))
															SellBusinessProductInfo(index_business, pExtraButtons[playerid][lis], playerid);
														}
														else Text_Send(playerid, $MESSAGE_ERROR_INV);
													}
												}
											}
											else
											{
												if(BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_PRICE] > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
												else
												{
													switch(bsale_type)
													{
														case BUSINESS_SALE_TYPE_BAR:
														{
															new special_action;
															special_action = strval(BProducts_Info[ BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_INDEX_PRODUCT] ][bproduct_info_PARAMS]);
															GivePlayerMoneyEx(playerid, -BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_PRICE]);
															Text_Send(playerid, $GAMETEXT_INFO_PRODUCT_BOUGHT);
															SetPlayerSpecialAction(playerid, special_action);
															if(IsBusinessOccupied(index_business))
															SellBusinessProductInfo(index_business, pExtraButtons[playerid][lis], playerid);
														}
														case BUSINESS_SALE_TYPE_HARDWARE:
														{
															if(BProducts_Info[ BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_INDEX_PRODUCT] ][bproduct_info_ID] == 53)
															{
																//duplicado llaves
																new count, listitems_ids[MAX_PLAYER_BUSINESS + MAX_PLAYER_PROPERTIES + MAX_PLAYER_VEHICLES],
																	line_str[70], dialog_key_duplicate[70 * (MAX_PLAYER_BUSINESS + MAX_PLAYER_PROPERTIES + MAX_PLAYER_VEHICLES)];
																foreach(new i : PINV[playerid])
																{
																	if(INV_ITEMS_Info[ PINV[playerid][i][pinv_ITEM_ID] ][inv_item_TYPE] == _:INV_ITEM_TYPE_MASTER_KEY)
																	{
																		new item_name[64];
																		format(item_name, sizeof item_name, "%s", GetItemName(playerid, PINV[playerid][i][pinv_ITEM_ID], PINV[playerid][i][pinv_PARAMS]));
																		format(line_str, sizeof line_str, "%c%s\n", toupper(item_name[0]), item_name[1]);
																		strcat(dialog_key_duplicate, line_str);
																		listitems_ids[count++] = i;
																	}
																}

																//action
																if(count == 0) Text_Send(playerid, $MESSAGE_ERROR_NO_MASTER_KEYS);
																else
																{
																	inline in_OnPlayerDialog(in_pid, in_did, in_res, in_lis, string:in_inp[])
																	{
																		#pragma unused in_pid, in_did, in_inp
																		if(in_res)
																		{
																			new inv_index = listitems_ids[in_lis],
																				in_inv_itemid = -1;
																			switch(PINV[playerid][inv_index][pinv_ITEM_ID])
																			{
																				case INV_ITEM_PROPERTY_MASTER_KEY: in_inv_itemid = _:INV_ITEM_PROPERTY_KEY;
																				case INV_ITEM_VEHICLE_MASTER_KEY: in_inv_itemid = _:INV_ITEM_VEHICLE_KEY;
																				case INV_ITEM_BUSINESS_MASTER_KEY: in_inv_itemid = _:INV_ITEM_BUSINESS_KEY;
																			}
																			if(in_inv_itemid != -1)
																			{
																				new inv_params[128];
																				format(inv_params, sizeof inv_params, "%s", PINV[playerid][inv_index][pinv_PARAMS]);
																				if(AddPlayerInventoryItem(playerid, in_inv_itemid, inv_params))
																				{
																					GivePlayerMoneyEx(playerid, -BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_PRICE]);
																					Text_Send(playerid, $GAMETEXT_INFO_PRODUCT_BOUGHT);
																					if(IsBusinessOccupied(index_business))
																					SellBusinessProductInfo(index_business, pExtraButtons[playerid][lis], playerid);
																				}
																				else Text_Send(playerid, $MESSAGE_ERROR_INV);
																			}
																		}
																	}

																	new dialog_caption[64];
																	Text_Format_Dialog(dialog_caption, sizeof dialog_caption, PI[playerid][pi_LANG_ID], $DIALOG_DUPLICATE_KEYS_CAPTION);
																	Dialog_ShowCallback(playerid, using inline in_OnPlayerDialog, DIALOG_STYLE_LIST, dialog_caption, dialog_key_duplicate, ">", "X");
																}
															}
														}
														case BUSINESS_SALE_TYPE_AMMO:
														{
															new count, listitems_ids[MAX_PLAYER_WEAPONS],
																line_str[70], dialog_weapons[70 * MAX_PLAYER_WEAPONS];
															foreach(new i : pWeapons[playerid])
															{
																if(HasWeaponAmmo(pWeapons[playerid][i][pweapon_WEAPONID]))
																{
																	new item_name[64];
																	format(item_name, sizeof item_name, "%s", GetItemName(playerid, GetInvItemIdFromWeaponID(pWeapons[playerid][i][pweapon_WEAPONID])));
																	format(line_str, sizeof line_str, "%c%s\n", toupper(item_name[0]), item_name[1]);
																	strcat(dialog_weapons, line_str);
																	listitems_ids[count++] = i;
																}
															}

															//action
															if(count == 0) Text_Send(playerid, $MESSAGE_ERROR_NO_WEAPONS);
															else
															{
																inline in_OnPlayerDialog(in_pid, in_did, in_res, in_lis, string:in_inp[])
																{
																	#pragma unused in_pid, in_did, in_inp
																	if(in_res)
																	{
																		new weapon_index = listitems_ids[in_lis], ammo = strval(BProducts_Info[ BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_INDEX_PRODUCT] ][bproduct_info_PARAMS]);
																		pWeapons[playerid][weapon_index][pweapon_AMMO] += ammo;
																		if(pWeapons[playerid][weapon_index][pweapon_CARRIED]) SetPlayerWeapons(playerid);
																		UpdatePlayerWeapon(playerid, weapon_index);
																		
																		GivePlayerMoneyEx(playerid, -BProducts[index_business][ pExtraButtons[playerid][lis] ][bproduct_PRICE]);
																		Text_Send(playerid, $GAMETEXT_INFO_PRODUCT_BOUGHT);
																		if(IsBusinessOccupied(index_business))
																		SellBusinessProductInfo(index_business, pExtraButtons[playerid][lis], playerid);
																	}
																}

																new dialog_caption[64];
																Text_Format_Dialog(dialog_caption, sizeof dialog_caption, PI[playerid][pi_LANG_ID], $DIALOG_AMMO_CAPTION);
																Dialog_ShowCallback(playerid, using inline in_OnPlayerDialog, DIALOG_STYLE_LIST, dialog_caption, dialog_weapons, ">", "X");
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
					Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST_HEADERS, GetProductsDialogCaption(playerid), dialog, ">", "X");
				}
			}
		}
	}
	return 1;
}

hook OnPreviewMenuResponse(playerid, menu_id, menu_model_id, response, modelid, price)
{
	if(menu_id == pBusinessTmpMenu[playerid])
	{
		if(response)
		{
			if(pBusinessTmpMenu_Clothes[playerid])
			{
				new CLOTHES_TYPES:id_clothe = GetClotheIdByModelid(PI[playerid][pi_CLOTHING_CHARACTER], modelid);
				if(id_clothe != CLOTHES_TYPES:-1)
				{
					if(PI[playerid][pi_MONEY] >= price)
					{
						if(AddPlayerClothe(playerid, id_clothe))
						{
							GivePlayerMoneyEx(playerid, -price);
							Text_Send(playerid, $GAMETEXT_INFO_PRODUCT_BOUGHT);
							new index_business = PI[playerid][pi_WORLD_STATE_INDEX],
								index_product = pBusinessTmpProductIndex[playerid][menu_model_id];
							if(IsBusinessOccupied(index_business))
							SellBusinessProductInfo(index_business, index_product, playerid);
						}
						else Text_Send(playerid, $MESSAGE_ERROR_CLOTHES_ADD);
					}
					else Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
				}
			}
			else if(pBusinessTmpMenu_Toys[playerid])
			{
				if(PI[playerid][pi_MONEY] >= price)
				{
					if(Iter_Count(pToys[playerid]) >= MAX_PLAYER_TOYS) Text_Send(playerid, $MESSAGE_ERROR_TOY_ADD);
					else
					{
						new index_business = PI[playerid][pi_WORLD_STATE_INDEX],
							index_product = pBusinessTmpProductIndex[playerid][menu_model_id],
							inv_itemid = BProducts_Info[ BProducts[index_business][index_product][bproduct_INDEX_PRODUCT] ][bproduct_info_ID_INVITEM];
						if(inv_itemid != 0)
						{
							new inv_params[128];
							format(inv_params, sizeof inv_params, "%s", BProducts_Info[ BProducts[index_business][index_product][bproduct_INDEX_PRODUCT] ][bproduct_info_PARAMS]);
							if(AddPlayerInventoryItem(playerid, inv_itemid, inv_params))
							{
								GivePlayerMoneyEx(playerid, -BProducts[index_business][index_product][bproduct_PRICE]);
								Text_Send(playerid, $GAMETEXT_INFO_PRODUCT_BOUGHT);
								if(IsBusinessOccupied(index_business))
								SellBusinessProductInfo(index_business, index_product, playerid);
							}
							else Text_Send(playerid, $MESSAGE_ERROR_INV);
						}
					}
				}
				else Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
			}
			HidePreviewMenuForPlayer(playerid);
		}
		DeletePreviewMenu(pBusinessTmpMenu[playerid]);
		pBusinessTmpMenu[playerid] = INVALID_MENU_ID;
	}
	return 1;
}

YCMD:business(playerid, params[], help)
{
	if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_BUSINESS)
	{
		new index_business = PI[playerid][pi_WORLD_STATE_INDEX];
		if(GetBusinessOwner(index_business) == PI[playerid][pi_ID])
		{
			inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
			{
				#pragma unused pid, dialogid, inputtext
				if(response)
				{
					switch(listitem)
					{
						case 0: //horario
						{
							inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
							{
								#pragma unused in_pid, in_dialogid, in_listitem
								if(in_response)
								{
									new hour_open, hour_close;
									if(!sscanf(in_inputtext, "dd", hour_open, hour_close))
									{
										if(hour_open < 0 || hour_open > 24 || hour_close < 0 || hour_close > 24) Text_Send(playerid, $MESSAGE_ERROR_INVALID_FORMAT);
										else
										{
											BusinessData[index_business][bdata_HOUR_OPEN] = hour_open;
											BusinessData[index_business][bdata_HOUR_CLOSE] = hour_close;
											UpdateBusinessData(index_business);
											Text_Send(playerid, $GAMETEXT_INFO_CHANGES_SAVED);
										}
									}
									else Text_Send(playerid, $MESSAGE_ERROR_INVALID_FORMAT);
								}
								else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_BUSINESS_CAPTION, $DIALOG_BUSINESS_BODY, $DIALOG_BUSINESS_YES, $DIALOG_BUSINESS_NO);						
							}
							Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline in_OnPlayerDialog, $DIALOG_BUSINESS_SCHEDULE_CAPTION, $DIALOG_BUSINESS_SCHEDULE_BODY, $DIALOG_BUSINESS_SCHEDULE_YES, $DIALOG_BUSINESS_SCHEDULE_NO, BusinessData[index_business][bdata_HOUR_OPEN], BusinessData[index_business][bdata_HOUR_CLOSE]);
						}
						case 1: //caja fuerte
						{
							inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
							{
								#pragma unused in_pid, in_dialogid, in_inputtext
								if(in_response)
								{
									switch(in_listitem)
									{
										case 0: //ingresar
										{
											inline in2_OnPlayerDialog(in2_pid, in2_dialogid, in2_response, in2_listitem, string:in2_inputtext[])
											{
												#pragma unused in2_pid, in2_dialogid, in2_listitem
												if(in2_response)
												{
													new amount;
													if(!sscanf(in2_inputtext, "d", amount))
													{
														if(amount <= 0) Text_Send(playerid, $MESSAGE_ERROR_INVALID_FORMAT);
														else
														{
															if(amount > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_DEPOSIT_NO_MONEY);
															else
															{
																BusinessData[index_business][bdata_MONEY] += amount;
																GivePlayerMoneyEx(playerid, -amount);
																UpdateBusinessData(index_business);
															}
														}
													}
													else Text_Send(playerid, $MESSAGE_ERROR_INVALID_FORMAT); 
												}
											}
											Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline in2_OnPlayerDialog, $DIALOG_BUSINESS_DEPOSIT_CAPTION, $DIALOG_BUSINESS_DEPOSIT_BODY, $DIALOG_BUSINESS_DEPOSIT_YES, $DIALOG_BUSINESS_DEPOSIT_NO, BusinessData[index_business][bdata_MONEY]);
										}
										case 1: //depositar
										{
											inline in2_OnPlayerDialog(in2_pid, in2_dialogid, in2_response, in2_listitem, string:in2_inputtext[])
											{
												#pragma unused in2_pid, in2_dialogid, in2_listitem
												if(in2_response)
												{
													new amount;
													if(!sscanf(in2_inputtext, "d", amount))
													{
														if(amount <= 0) Text_Send(playerid, $MESSAGE_ERROR_INVALID_FORMAT);
														else
														{
															if(amount > BusinessData[index_business][bdata_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_WITHDRAW_NO_MONEY);
															else
															{
																BusinessData[index_business][bdata_MONEY] -= amount;
																GivePlayerMoneyEx(playerid, amount);
																UpdateBusinessData(index_business);
															}
														}
													}
													else Text_Send(playerid, $MESSAGE_ERROR_INVALID_FORMAT); 
												}
											}
											Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline in2_OnPlayerDialog, $DIALOG_BUSINESS_WITHDRAW_CAPTION, $DIALOG_BUSINESS_WITHDRAW_BODY, $DIALOG_BUSINESS_WITHDRAW_YES, $DIALOG_BUSINESS_WITHDRAW_NO, BusinessData[index_business][bdata_MONEY]);
										}
									}
								}
								else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_BUSINESS_CAPTION, $DIALOG_BUSINESS_BODY, $DIALOG_BUSINESS_YES, $DIALOG_BUSINESS_NO);
							}
							Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline in_OnPlayerDialog, $DIALOG_BUSINESS_MONEY_CAPTION, $DIALOG_BUSINESS_MONEY_BODY, $DIALOG_BUSINESS_MONEY_YES, $DIALOG_BUSINESS_MONEY_NO);
						}
						case 2: //radio
						{
							new line_str[35], dialog_radio[35 * sizeof Radios];
							for(new i = 0; i < sizeof Radios; i ++)
							{
								if(BusinessData[index_business][bdata_RADIO] == i) format(line_str, sizeof line_str, "{ec98f9}- %s\n", Radios[i][radio_NAME]);
								else format(line_str, sizeof line_str, "{936c99}- %s\n", Radios[i][radio_NAME]);
								strcat(dialog_radio, line_str);
							}

							inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
							{
								#pragma unused in_pid, in_dialogid, in_inputtext
								if(in_response)
								{
									if(BusinessData[index_business][bdata_RADIO] != in_listitem)
									{
										BusinessData[index_business][bdata_RADIO] = in_listitem;
										UpdateBusinessData(index_business);
										//audio
										foreach(new i : Player)
										{
											if(PI[i][pi_WORLD_STATE] == PLAYER_WORLD_STATE_BUSINESS && PI[i][pi_WORLD_STATE_INDEX] == index_business)
											{
												if(BusinessData[index_business][bdata_RADIO] == 0) StopAudioStreamForPlayer(i);
												else PlayAudioStreamForPlayer(i, Radios[ BusinessData[index_business][bdata_RADIO] ][radio_URL]);
											}
										}
									}
									Text_Send(playerid, $GAMETEXT_INFO_CHANGES_SAVED);
								}
							}
							Dialog_ShowCallback(playerid, using inline in_OnPlayerDialog, DIALOG_STYLE_LIST, "Radio", dialog_radio, ">", "X");
						}
						case 3: //productos
						{
							if(!pBProducts_Enabled[playerid])
							ShowBProducts(playerid);
						}
					}
				}
			}
			Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_BUSINESS_CAPTION, $DIALOG_BUSINESS_BODY, $DIALOG_BUSINESS_YES, $DIALOG_BUSINESS_NO);
		}
		else Text_Send(playerid, $MESSAGE_ERROR_LOCATION);
	}
	else Text_Send(playerid, $MESSAGE_ERROR_LOCATION);
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(pBProducts_Enabled[playerid])
	{
		if(clickedid == Text:INVALID_TEXT_DRAW)
		{
			DestroyBProducts(playerid);
			return 1;
		}
	}
	return 0;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	if(pBProducts_Enabled[playerid])
	{	
		if(playertextid == pBProducts_Base_PTD[playerid][2]) //order by: id
		{
			pBProducts_Order[playerid][0] = !pBProducts_Order[playerid][0];
			//set
			new order[24];
			if(pBProducts_Order[playerid][0]) order = "id_product DESC";
			else order = "id_product ASC";
			FormatBProductsTds(playerid);
			UpdateBusinessProductsTds(playerid, order);
			return 1;
		}
		else if(playertextid == pBProducts_Base_PTD[playerid][4]) //order by: price
		{
			pBProducts_Order[playerid][2] = !pBProducts_Order[playerid][2];
			//set
			new order[24];
			if(pBProducts_Order[playerid][2]) order = "price DESC";
			else order = "price ASC";
			FormatBProductsTds(playerid);
			UpdateBusinessProductsTds(playerid, order);
			return 1;
		}
		else if(playertextid == pBProducts_Base_PTD[playerid][5]) //order by: stock
		{
			pBProducts_Order[playerid][3] = !pBProducts_Order[playerid][3];
			//set
			new order[24];
			if(pBProducts_Order[playerid][3]) order = "stock DESC";
			else order = "stock ASC";
			FormatBProductsTds(playerid);
			UpdateBusinessProductsTds(playerid, order);
			return 1;
		}
		else if(playertextid == pBProducts_Base_PTD[playerid][6]) //order by: sales
		{
			pBProducts_Order[playerid][4] = !pBProducts_Order[playerid][4];
			//set
			new order[24];
			if(pBProducts_Order[playerid][4]) order = "sales DESC";
			else order = "sales ASC";
			FormatBProductsTds(playerid);
			UpdateBusinessProductsTds(playerid, order);
			return 1;
		}
		else if(playertextid == pBProducts_Base_PTD[playerid][9]) //next page
		{
			pCurrentDialogPage[playerid] = GetNextDialogPage(pCurrentDialogPage[playerid], Iter_Count(BProducts[pBProducts_IndexBusiness[playerid]]));
			UpdateBusinessProductsTds(playerid);
			return 1;
		}
		else if(playertextid == pBProducts_Base_PTD[playerid][8]) //añadir producto
		{
			CancelSelectTextDraw(playerid);
			//counts
			new count, line_str[128], dialog[128 * (DIALOG_PAGINATION_SIZE + 3)];
			foreach(new i : BProducts_Info)
			{
				foreach(new j : BTypes_STypes)
				{
					if(BTypes_STypes[j][btype_stype_ID_BUSINESS_TYPE] == BusinessData[pBProducts_IndexBusiness[playerid]][bdata_ID_TYPE])
					{
						if(BProducts_Info[i][bproduct_info_ID_TYPE] == BTypes_STypes[j][btype_stype_ID_BSALES_TYPE])
						{
							new product_index = GetBusinessProductIndexById(pBProducts_IndexBusiness[playerid], BProducts_Info[i][bproduct_info_ID]);
							if(product_index == -1)
							{
								if(count >= DIALOG_PAGINATION_SIZE) break;
								else
								{
									format(line_str, sizeof line_str, "%s", GetBusinessProductName(playerid, i));
									format(line_str, sizeof line_str, "%c%s\t%d$\n", toupper(line_str[0]), line_str[1], BProducts_Info[i][bproduct_info_PRICE]);
									strcat(dialog, line_str);
									pExtraButtons[playerid][count++] = i;
								}
							}
						}
					}
				}
			}
			//acts
			if(count == 0) Text_Send(playerid, $MESSAGE_ERROR_ADD_NO_PRODUCTS);
			else
			{
				inline OnPlayerDialog(pid, did, res, lis, string:inp[])
				{
					#pragma unused pid, did, inp
					if(res)
					{
						new bproduct_info_index = pExtraButtons[playerid][lis],
							bproduct_index = Iter_Free(BProducts[pBProducts_IndexBusiness[playerid]]);
						if(bproduct_index != cellmin)
						{
							new index_business = pBProducts_IndexBusiness[playerid];
							BProducts[index_business][bproduct_index][bproduct_ID_PRODUCT] = BProducts_Info[bproduct_info_index][bproduct_info_ID];
							BProducts[index_business][bproduct_index][bproduct_ID_BUSINESS] = BusinessData[index_business][bdata_ID];
							BProducts[index_business][bproduct_index][bproduct_PRICE] = BProducts_Info[bproduct_info_index][bproduct_info_PRICE];
							BProducts[index_business][bproduct_index][bproduct_STOCK] = 0;
							BProducts[index_business][bproduct_index][bproduct_INDEX_PRODUCT] = bproduct_info_index;
							Iter_Add(BProducts[index_business], bproduct_index);
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO business_sales_products VALUES (%d, %d, %d, %d);", BProducts[index_business][bproduct_index][bproduct_ID_PRODUCT], BProducts[index_business][bproduct_index][bproduct_ID_BUSINESS], BProducts[index_business][bproduct_index][bproduct_PRICE], BProducts[index_business][bproduct_index][bproduct_STOCK]);
							mysql_tquery(vcrp_db, QUERY_BUFFER);
							Text_Send(playerid, $GAMETEXT_INFO_CHANGES_SAVED);
						}
					}
				}
				Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, GetProductsDialogCaption(playerid), dialog, ">", "X");
			}
		}
		else
		{
			for(new i = 0; i < sizeof pBProducts_Products_PTD[]; i ++)
			{
				if(playertextid == pBProducts_Products_PTD[playerid][i][0])
				{
					CancelSelectTextDraw(playerid);
					if(pExtraButtons[playerid][i] != -1)
					{
						inline OnPlayerDialog(pid, did, res, lis, string:inp[])
						{
							#pragma unused pid, did, inp
							if(res)
							{
								new index_business = pBProducts_IndexBusiness[playerid], index_product = pExtraButtons[playerid][i];
								switch(lis)
								{
									case 0: //price
									{
										inline in_OnPlayerDialog(in_pid, in_did, in_res, in_lis, string:in_inp[])
										{
											#pragma unused in_pid, in_did, in_lis
											if(in_res)
											{
												new price;
												if(!sscanf(in_inp, "d", price))
												{
													if(price < 0 || price > floatround(floatmul(float(BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_PRICE]), BPRODUCT_PRICE_MAX_MUL))) Text_Send(playerid, $MESSAGE_ERROR_BP_EDIT_PRICE);
													else
													{
														BProducts[index_business][index_product][bproduct_PRICE] = price;
														mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business_sales_products SET price = %d WHERE id_product = %d AND id_business = %d;", BProducts[index_business][index_product][bproduct_PRICE], BProducts[index_business][index_product][bproduct_ID_PRODUCT], BProducts[index_business][index_product][bproduct_ID_BUSINESS]);
														mysql_tquery(vcrp_db, QUERY_BUFFER);
														Text_Send(playerid, $GAMETEXT_INFO_CHANGES_SAVED);
													}
												}
												else Text_Send(playerid, $MESSAGE_ERROR_INVALID_FORMAT);
											}
											else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_BUSINESS_EPRODUCT_CAPTION, $DIALOG_BUSINESS_EPRODUCT_BODY, $DIALOG_BUSINESS_EPRODUCT_YES, $DIALOG_BUSINESS_EPRODUCT_NO);
										}
										Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline in_OnPlayerDialog, $DIALOG_BP_EDIT_PRICE_CAPTION, $DIALOG_BP_EDIT_PRICE_BODY, $DIALOG_BP_EDIT_PRICE_YES, $DIALOG_BP_EDIT_PRICE_NO, BProducts[index_business][index_product][bproduct_PRICE], floatround(floatmul(float(BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_PRICE]), BPRODUCT_PRICE_MUL)));
									}
									case 1: //add stock
									{
										//MAX_PRODUCTS_STOCK
										inline in_OnPlayerDialog(in_pid, in_did, in_res, in_lis, string:in_inp[])
										{
											#pragma unused in_pid, in_did, in_lis
											if(in_res)
											{
												new a_stock;
												if(!sscanf(in_inp, "d", a_stock))
												{
													if(a_stock <= 0 || a_stock > 10000 || BProducts[index_business][index_product][bproduct_STOCK] + a_stock >= MAX_PRODUCTS_STOCK) Text_Send(playerid, $MESSAGE_ERROR_BP_STOCK);
													else
													{
														new cost = a_stock * (floatround(floatmul(float(BProducts_Info[ BProducts[index_business][index_product][bproduct_INDEX_PRODUCT] ][bproduct_info_PRICE]), BPRODUCT_PRICE_MUL)));
														inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
														{
															#pragma unused in2_pid, in2_did, in2_lis, in2_inp
															if(in2_res)
															{
																if(BusinessData[index_business][bdata_MONEY] >= cost)
																{
																	BusinessData[index_business][bdata_MONEY] -= cost;
																	UpdateBusinessData(index_business);
																	BProducts[index_business][index_product][bproduct_STOCK] += a_stock;
																	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business_sales_products SET stock = %d WHERE id_product = %d AND id_business = %d;", BProducts[index_business][index_product][bproduct_STOCK], BProducts[index_business][index_product][bproduct_ID_PRODUCT], BProducts[index_business][index_product][bproduct_ID_BUSINESS]);
																	mysql_tquery(vcrp_db, QUERY_BUFFER);
																	Text_Send(playerid, $GAMETEXT_INFO_CHANGES_SAVED);
																}
																else Text_Send(playerid, $MESSAGE_ERROR_ASTOCK_NO_MONEY);
															}
														}
														Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline in2_OnPlayerDialog, $DIALOG_BPASTOCK_CONFIRM_CAPTION, $DIALOG_BPASTOCK_CONFIRM_BODY, $DIALOG_BPASTOCK_CONFIRM_YES, $DIALOG_BPASTOCK_CONFIRM_NO, a_stock, cost, BusinessData[index_business][bdata_MONEY]);
													}
												}
												else Text_Send(playerid, $MESSAGE_ERROR_INVALID_FORMAT);
											}
											else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_BUSINESS_EPRODUCT_CAPTION, $DIALOG_BUSINESS_EPRODUCT_BODY, $DIALOG_BUSINESS_EPRODUCT_YES, $DIALOG_BUSINESS_EPRODUCT_NO);
										}
										Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline in_OnPlayerDialog, $DIALOG_BP_ADD_STOCK_CAPTION, $DIALOG_BP_ADD_STOCK_BODY, $DIALOG_BP_ADD_STOCK_YES, $DIALOG_BP_ADD_STOCK_NO, floatround(floatmul(float(BProducts_Info[ BProducts[index_business][index_product][bproduct_INDEX_PRODUCT] ][bproduct_info_PRICE]), BPRODUCT_PRICE_MUL)));
									}
									case 2: //delete
									{
										inline in_OnPlayerDialog(in_pid, in_did, in_res, in_lis, string:in_inp[])
										{
											#pragma unused in_pid, in_did, in_lis, in_inp
											if(in_res)
											{
												mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM business_sales_products WHERE id_product = %d AND id_business = %d;", BProducts[index_business][index_product][bproduct_ID_PRODUCT], BProducts[index_business][index_product][bproduct_ID_BUSINESS]);
												mysql_tquery(vcrp_db, QUERY_BUFFER);
												BProducts[index_business][index_product][bproduct_ID_PRODUCT] = 0;
												BProducts[index_business][index_product][bproduct_ID_BUSINESS] = 0;
												BProducts[index_business][index_product][bproduct_PRICE] = 0;
												BProducts[index_business][index_product][bproduct_STOCK] = 0;
												BProducts[index_business][index_product][bproduct_INDEX_PRODUCT] = 0;
												Iter_Remove(BProducts[index_business], index_product);
												Text_Send(playerid, $GAMETEXT_INFO_CHANGES_SAVED);
											}
											else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_BUSINESS_EPRODUCT_CAPTION, $DIALOG_BUSINESS_EPRODUCT_BODY, $DIALOG_BUSINESS_EPRODUCT_YES, $DIALOG_BUSINESS_EPRODUCT_NO);
										}
										Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline in_OnPlayerDialog, $DIALOG_BP_DELETE_CAPTION, $DIALOG_BP_DELETE_BODY, $DIALOG_BP_DELETE_YES, $DIALOG_BP_DELETE_NO);
									}
								}
							}
						}
						Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_BUSINESS_EPRODUCT_CAPTION, $DIALOG_BUSINESS_EPRODUCT_BODY, $DIALOG_BUSINESS_EPRODUCT_YES, $DIALOG_BUSINESS_EPRODUCT_NO);
					}
					return 1;
				}
			}
		}
	}
	return 0;
}