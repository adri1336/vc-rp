#include <YSI\y_hooks>

loadtext lang[shared_commands];

YCMD:puerta(playerid, params[], help)
{
	if(pLastAreaId[playerid] != INVALID_STREAMER_ID)
	{
		if(IsPlayerInDynamicArea(playerid, pLastAreaId[playerid]))
		{
			new streamer_info[3];
			Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
			switch(streamer_info[0])
			{
				case AREA_TYPE_EXT_PROPERTY_DOOR, AREA_TYPE_INT_PROPERTY_DOOR, AREA_TYPE_LABEL_EXT_PROP_DOOR, AREA_TYPE_LABEL_INT_PROP_DOOR:
				{
					if(IsPropertyOccupied(streamer_info[1]))
					{
						new inv_params[24];
						format(inv_params, sizeof inv_params, "%d", PropertyInfo[streamer_info[1]][property_ID]);
						if(PlayerInvContainsItemEx(playerid, _:INV_ITEM_PROPERTY_MASTER_KEY, _:INV_ITEM_PROPERTY_KEY, _:INV_ITEM_PROPERTY_RENT_KEY, inv_params))
						{
							if(PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_CLOSED])
							{
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_CLOSED] = false;
								Text_Send(playerid, $GAMETEXT_INFO_DOOR_OPENED);
								CallRemoteFunction("OnPlayerOpenProperty", "i", playerid);
							}
							else
							{
								PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_CLOSED] = true;	
								Text_Send(playerid, $GAMETEXT_INFO_DOOR_CLOSED);
								CallRemoteFunction("OnPlayerCloseProperty", "i", playerid);
							}
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties_doors SET closed = %d WHERE id = %d;", PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_CLOSED], PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_ID]);
							mysql_tquery(vcrp_db, QUERY_BUFFER);
						}
						else Text_Send(playerid, $MESSAGE_ERROR_NO_PKEYS);
					}
					else Text_Send(playerid, $MESSAGE_ERROR_NO_PKEYS);
				}
				case AREA_TYPE_BDOOR_EXT, AREA_TYPE_LABEL_BDOOR_EXT, AREA_TYPE_BDOOR_INT, AREA_TYPE_LABEL_BDOOR_INT:
				{
					if(IsBusinessOccupied(streamer_info[1]))
					{
						new inv_params[24];
						format(inv_params, sizeof inv_params, "%d", BusinessData[streamer_info[1]][bdata_ID]);
						if(PlayerInvContainsItemEx(playerid, _:INV_ITEM_BUSINESS_MASTER_KEY, _:INV_ITEM_BUSINESS_KEY, _:INV_ITEM_BUSINESS_KEY, inv_params))
						{
							if(BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_CLOSED])
							{
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_CLOSED] = false;
								Text_Send(playerid, $GAMETEXT_INFO_DOOR_OPENED);
							}
							else
							{
								BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_CLOSED] = true;	
								Text_Send(playerid, $GAMETEXT_INFO_DOOR_CLOSED);
							}
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business_doors SET closed = %d WHERE id = %d;", BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_CLOSED], BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_ID]);
							mysql_tquery(vcrp_db, QUERY_BUFFER);
						}
						else Text_Send(playerid, $MESSAGE_ERROR_NO_BKEYS);
					}
					else Text_Send(playerid, $MESSAGE_ERROR_NO_BKEYS);
				}
				default: Text_Send(playerid, $MESSAGE_ERROR_POSITION);
			}
		}
		else Text_Send(playerid, $MESSAGE_ERROR_POSITION);
	}
	else Text_Send(playerid, $MESSAGE_ERROR_POSITION);
	return 1;
}

YCMD:comprar(playerid, params[], help)
{
	if(pLastAreaId[playerid] != INVALID_STREAMER_ID)
	{
		if(IsPlayerInDynamicArea(playerid, pLastAreaId[playerid]))
		{
			new streamer_info[3];
			Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
			switch(streamer_info[0])
			{
				case AREA_TYPE_EXT_PROPERTY_DOOR:
				{
					if(!IsPropertyOccupied(streamer_info[1]) && !IsPropertyForRent(streamer_info[1]))
					{
						if(PropertyInfo[streamer_info[1]][property_PRICE] > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_P_NO_MONEY);
						else if(PropertyInfo[streamer_info[1]][property_LEVEL] > PI[playerid][pi_LEVEL]) Text_Send(playerid, $MESSAGE_ERROR_P_NO_LEVEL, PropertyInfo[streamer_info[1]][property_LEVEL]);
						else if(CountPlayerProperties(playerid) >= MAX_PLAYER_PROPERTIES) Text_Send(playerid, $MESSAGE_ERROR_MAX_PROP, MAX_PLAYER_PROPERTIES);
						else if(GetPlayerInvFreeItemSlot(playerid) == cellmin) Text_Send(playerid, $MESSAGE_ERROR_P_INV_SLOT);
						else
						{
							new inv_params[24];
							format(inv_params, sizeof inv_params, "%d", PropertyInfo[streamer_info[1]][property_ID]);
							if(AddPlayerInventoryItem(playerid, _:INV_ITEM_PROPERTY_MASTER_KEY, inv_params))
							{
								//set var
								PropertyInfo[streamer_info[1]][property_ID_PLAYER] = PI[playerid][pi_ID];
								format(PropertyInfo[streamer_info[1]][property_PLAYER_NAME], 24, "%s", PI[playerid][pi_NAME]);
								//cerramos todas las puertas
								foreach(new i : PropertyDoor[streamer_info[1]])
								{
									PropertyDoor[streamer_info[1]][i][prop_door_CLOSED] = true;
								}

								//db
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties SET id_player = %d WHERE id = %d;", PI[playerid][pi_ID], PropertyInfo[streamer_info[1]][property_ID]);
								mysql_tquery(vcrp_db, QUERY_BUFFER);

								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties_doors SET closed = 1 WHERE id_property = %d;", PropertyInfo[streamer_info[1]][property_ID]);
								mysql_tquery(vcrp_db, QUERY_BUFFER);

								//ok
								Iter_Add(PlayerProperties<playerid>, streamer_info[1]);
								GivePlayerMoneyEx(playerid, -PropertyInfo[streamer_info[1]][property_PRICE], true);
								orm_update(PI[playerid][pi_ORM]);
								Text_Send(playerid, $GAMETEXT_INFO_PROPERTY_PURCHASED);
								CallRemoteFunction("OnPlayerPurchaseProp", "i", playerid);
								DestroyPlayerLabel(playerid);
							}
						}
					}
					else Text_Send(playerid, $MESSAGE_ERROR_NO_PSELL);
				}
				case AREA_TYPE_BDOOR_EXT:
				{
					if(!IsBusinessOccupied(streamer_info[1]))
					{
						if(BusinessData[streamer_info[1]][bdata_PRICE] > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_B_NO_MONEY);
						else if(BusinessData[streamer_info[1]][bdata_LEVEL] > PI[playerid][pi_LEVEL]) Text_Send(playerid, $MESSAGE_ERROR_B_NO_LEVEL, BusinessData[streamer_info[1]][bdata_LEVEL]);
						else if(CountPlayerBusiness(playerid) >= MAX_PLAYER_BUSINESS) Text_Send(playerid, $MESSAGE_ERROR_MAX_BIZZ, MAX_PLAYER_BUSINESS);
						else if(GetPlayerInvFreeItemSlot(playerid) == cellmin) Text_Send(playerid, $MESSAGE_ERROR_B_INV_SLOT);
						else
						{
							new inv_params[24];
							format(inv_params, sizeof inv_params, "%d", BusinessData[streamer_info[1]][bdata_ID]);
							if(AddPlayerInventoryItem(playerid, _:INV_ITEM_BUSINESS_MASTER_KEY, inv_params))
							{
								//set var
								BusinessData[streamer_info[1]][bdata_ID_PLAYER] = PI[playerid][pi_ID];
								format(BusinessData[streamer_info[1]][bdata_PLAYER_NAME], 24, "%s", PI[playerid][pi_NAME]);
								//abrimos todas las puertas
								foreach(new i : BusinessDoors[streamer_info[1]])
								{
									BusinessDoors[streamer_info[1]][i][bdoor_CLOSED] = false;
								}
								//money reset
								BusinessData[streamer_info[1]][bdata_MONEY] = BUSINESS_DEFAULT_MONEY;

								//db
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business SET id_player = %d, money = %d WHERE id = %d;", PI[playerid][pi_ID], BusinessData[streamer_info[1]][bdata_MONEY], BusinessData[streamer_info[1]][bdata_ID]);
								mysql_tquery(vcrp_db, QUERY_BUFFER);

								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business_doors SET closed = 0 WHERE id_business = %d;", BusinessData[streamer_info[1]][bdata_ID]);
								mysql_tquery(vcrp_db, QUERY_BUFFER);

								//productos reset
								ResetBusinessProducts(streamer_info[1]);

								//ok
								Iter_Add(PlayerBusiness<playerid>, streamer_info[1]);
								GivePlayerMoneyEx(playerid, -BusinessData[streamer_info[1]][bdata_PRICE], true);
								orm_update(PI[playerid][pi_ORM]);
								Text_Send(playerid, $GAMETEXT_INFO_BUSINESS_PURCHASED);
								CallRemoteFunction("OnPlayerPurchaseBizz", "i", playerid);
								DestroyPlayerLabel(playerid);
							}
						}
					}
					else Text_Send(playerid, $MESSAGE_ERROR_NO_BSELL);
				}
				default: Text_Send(playerid, $MESSAGE_ERROR_POSITION);
			}
		}
		else Text_Send(playerid, $MESSAGE_ERROR_POSITION);
	}
	else Text_Send(playerid, $MESSAGE_ERROR_POSITION);
	return 1;
}

YCMD:alquilar(playerid, params[], help)
{
	if(pLastAreaId[playerid] != INVALID_STREAMER_ID)
	{
		if(IsPlayerInDynamicArea(playerid, pLastAreaId[playerid]))
		{
			new streamer_info[3];
			Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
			switch(streamer_info[0])
			{
				case AREA_TYPE_EXT_PROPERTY_DOOR:
				{
					if(IsPropertyForRent(streamer_info[1]))
					{
						if(IsPropertyOccupied(streamer_info[1]))
						{
							if(PropertyInfo[streamer_info[1]][property_ID_PLAYER] == PI[playerid][pi_ID])
							{
								inline OnQueryInfoLoad()
								{
									new rows;
									if(cache_get_row_count(rows))
									{
										if(rows)
										{
											new rent_days, max_rentdays;
											cache_get_value_index_int(0, 0, rent_days);
											max_rentdays = PROPERTY_RENT_MAX_DAYS - rent_days;
											if(!max_rentdays) Text_Send(playerid, $MESSAGE_ERROR_PROPERTY_RENTED_DAYS);
											else
											{
												inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
												{
													#pragma unused pid, dialogid, listitem
													if(response)
													{
														new days;
														if(sscanf(inputtext, "d", days)) Text_Send(playerid, $MESSAGE_ERROR_FORMAT);
														{
															if(days < PROPERTY_RENT_MIN_DAYS || days > max_rentdays) Text_Send(playerid, $MESSAGE_ERROR_PRENT_DAYS);
															else
															{
																new rent_price = PropertyInfo[streamer_info[1]][property_PRICE] * days;
																if(PropertyInfo[streamer_info[1]][property_PRICE] > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_PRENT_NO_MONEY, rent_price, days);
																else
																{
																	inline OnQueryLoad()
																	{
																		if(cache_get_row_count(rows))
																		{
																			if(rows)
																			{
																				new expire_date[24];
																				cache_get_value_index(0, 0, expire_date);
																				//set var
																				format(PropertyInfo[streamer_info[1]][property_RENT_EXPIRE_DATE], 24, "%s", expire_date);

																				//db
																				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties SET rent_expire_date = '%e' WHERE id = %d;", PropertyInfo[streamer_info[1]][property_RENT_EXPIRE_DATE], PropertyInfo[streamer_info[1]][property_ID]);
																				mysql_tquery(vcrp_db, QUERY_BUFFER);

																				//ok
																				GivePlayerMoneyEx(playerid, -rent_price, true);
																				orm_update(PI[playerid][pi_ORM]);
																				Text_Send(playerid, $GAMETEXT_INFO_PROPERTY_RENT_ADD);
																				DestroyPlayerLabel(playerid);
																			}
																		}
																	}
																	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT DATE_ADD(rent_expire_date, INTERVAL %d DAY) FROM properties WHERE id = %d;", days, PropertyInfo[streamer_info[1]][property_ID]);
																	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
																}
															}
														}
													}
												}
												Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnPlayerDialog, $DIALOG_RENT_ADD_PROPERTY_CAPTION, $DIALOG_RENT_ADD_PROPERTY_BODY, $DIALOG_RENT_ADD_PROPERTY_YES, $DIALOG_RENT_ADD_PROPERTY_NO, rent_days, PropertyInfo[streamer_info[1]][property_PRICE], PROPERTY_RENT_MIN_DAYS, max_rentdays);
											}
										}
									}
								}
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT TIMESTAMPDIFF(DAY, NOW(), rent_expire_date) FROM properties WHERE id = %d;", PropertyInfo[streamer_info[1]][property_ID]);
								mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryInfoLoad, "");
							}
							else Text_Send(playerid, $MESSAGE_ERROR_NO_PSELL);
						}
						else
						{
							if(PropertyInfo[streamer_info[1]][property_LEVEL] > PI[playerid][pi_LEVEL]) Text_Send(playerid, $MESSAGE_ERROR_P_NO_LEVEL, PropertyInfo[streamer_info[1]][property_LEVEL]);
							else if(PlayerInvContainsItem(playerid, _:INV_ITEM_PROPERTY_RENT_KEY)) Text_Send(playerid, $MESSAGE_ERROR_PROPERTY_RENTED);
							else if(GetPlayerInvFreeItemSlot(playerid) == cellmin) Text_Send(playerid, $MESSAGE_ERROR_P_INV_SLOT);
							else
							{
								inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
								{
									#pragma unused pid, dialogid, listitem
									if(response)
									{
										new days;
										if(sscanf(inputtext, "d", days)) Text_Send(playerid, $MESSAGE_ERROR_FORMAT);
										{
											if(days < PROPERTY_RENT_MIN_DAYS || days > PROPERTY_RENT_MAX_DAYS) Text_Send(playerid, $MESSAGE_ERROR_PRENT_DAYS);
											else
											{
												new rent_price = PropertyInfo[streamer_info[1]][property_PRICE] * days;
												if(PropertyInfo[streamer_info[1]][property_PRICE] > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_PRENT_NO_MONEY, rent_price, days);
												else
												{
													inline OnQueryLoad()
													{
														new rows;
														if(cache_get_row_count(rows))
														{
															if(rows)
															{
																new expire_date[24];
																cache_get_value_index(0, 0, expire_date);
																//
																new inv_params[24];
																format(inv_params, sizeof inv_params, "%d", PropertyInfo[streamer_info[1]][property_ID]);
																if(AddPlayerInventoryItem(playerid, _:INV_ITEM_PROPERTY_RENT_KEY, inv_params))
																{
																	//set var
																	PropertyInfo[streamer_info[1]][property_ID_PLAYER] = PI[playerid][pi_ID];
																	format(PropertyInfo[streamer_info[1]][property_PLAYER_NAME], 24, "%s", PI[playerid][pi_NAME]);
																	format(PropertyInfo[streamer_info[1]][property_RENT_EXPIRE_DATE], 24, "%s", expire_date);
																	//cerramos todas las puertas
																	foreach(new i : PropertyDoor[streamer_info[1]])
																	{
																		PropertyDoor[streamer_info[1]][i][prop_door_CLOSED] = true;
																	}

																	//db
																	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties SET id_player = %d, rent_expire_date = '%e' WHERE id = %d;", PI[playerid][pi_ID], PropertyInfo[streamer_info[1]][property_RENT_EXPIRE_DATE], PropertyInfo[streamer_info[1]][property_ID]);
																	mysql_tquery(vcrp_db, QUERY_BUFFER);

																	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties_doors SET closed = 1 WHERE id_property = %d;", PropertyInfo[streamer_info[1]][property_ID]);
																	mysql_tquery(vcrp_db, QUERY_BUFFER);

																	//ok
																	Iter_Add(PlayerProperties<playerid>, streamer_info[1]);
																	GivePlayerMoneyEx(playerid, -rent_price, true);
																	orm_update(PI[playerid][pi_ORM]);
																	Text_Send(playerid, $GAMETEXT_INFO_PROPERTY_RENTED);
																	CallRemoteFunction("OnPlayerRentProp", "i", playerid);
																	DestroyPlayerLabel(playerid);
																}
															}
														}
													}
													mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT DATE_ADD(NOW(), INTERVAL %d DAY);", days);
													mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
												}
											}
										}
									}
								}
								Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnPlayerDialog, $DIALOG_RENT_PROPERTY_CAPTION, $DIALOG_RENT_PROPERTY_BODY, $DIALOG_RENT_PROPERTY_YES, $DIALOG_RENT_PROPERTY_NO, PropertyInfo[streamer_info[1]][property_PRICE], PROPERTY_RENT_MIN_DAYS, PROPERTY_RENT_MAX_DAYS);
							}
						}
					}
					else Text_Send(playerid, $MESSAGE_ERROR_NO_PSELL);
				}
				default: Text_Send(playerid, $MESSAGE_ERROR_POSITION);
			}
		}
		else Text_Send(playerid, $MESSAGE_ERROR_POSITION);
	}
	else Text_Send(playerid, $MESSAGE_ERROR_POSITION);
	return 1;
}

YCMD:responder(playerid, params[], help)
{
	new to_playerid = INVALID_PLAYER_ID;
	if(sscanf(params, "u", to_playerid)) Text_Send(playerid, $MESSAGE_ERROR_RESPOND_CSYNTAX);
	else
	{
		if(!IsPlayerConnected(to_playerid)) Text_Send(playerid, $MESSAGE_ERROR_PDISCONNECTED);
		else
		{
			switch(GetPlayerJobId(playerid))
			{
				case JOB_TAXI:
				{
					if(pTaxiDriverInJob[playerid]) Text_Send(playerid, $MESSAGE_ERROR_ALREADY_TAXI_JOB);
					else
					{
						if(pWaitingTaxiResponse[to_playerid])
						{
							Text_Send(to_playerid, $MESSAGE_WARNING_TAXI_RESPONSE, PI[playerid][pi_RP_NAME]);
							Text_Send(playerid, $MESSAGE_INFO_TAXI_RESPONSE);
							pWaitingTaxiResponse[to_playerid] = false;
							if(pTaxiAutopilotRequest[to_playerid] != Timer:-1)
							{
								stop pTaxiAutopilotRequest[to_playerid];
								pTaxiAutopilotRequest[to_playerid] = Timer:-1;
							}
							//ruta
							new Float:pos[3], Float:angle, interiorid, worldid;
							GetPlayerExteriorPos(to_playerid, pos[0], pos[1], pos[2], angle, interiorid, worldid);
							DestroyPlayerRoute(playerid, 1);
							CalcRoute(playerid, pos[0], pos[1], pos[2]);
						}
						else Text_Send(playerid, $MESSAGE_ERROR_NO_TAXI_REQUEST);
					}
				}
				default: Text_Send(playerid, $MESSAGE_ERROR_COMMAND);
			}
		}
	}
	return 1;
}