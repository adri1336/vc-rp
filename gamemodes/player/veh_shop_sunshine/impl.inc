#include <YSI\y_hooks>

loadtext lang[veh_shop_sunshine];

public OnPlayerRequestSalesVehMenu(playerid)
{
	inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, inputtext
		if(response)
		{
			switch(listitem)
			{
				case 0: ShowPreviewMenuForPlayer(playerid, saleVehiclesMenu, 0xfda3ffff);
				case 1:
				{
					new slot = Iter_Free(sOldVehs);
					if(slot == cellmin) Text_Send(playerid, $MESSAGE_ERROR_VEHICLE_SELL);
					else
					{
						if(!CountPlayerVehicles(playerid)) Text_Send(playerid, $MESSAGE_ERROR_NO_VEHICLES);
						else
						{
							new indexs[MAX_PLAYER_VEHICLES] = {INVALID_VEHICLE_INDEX, ...};
							inline OnPlayerSelectVehicle(ex_pid, ex_dialogid, ex_response, ex_listitem, string:ex_inputtext[])
							{
								#pragma unused ex_pid, ex_dialogid, ex_inputtext
								if(ex_response)
								{
									if(VehicleInfo[indexs[ex_listitem]][vinfo_GAME_STATE] != VEHICLE_GAME_STATE_NORMAL) Text_Send(playerid, $MESSAGE_ERROR_VEHICLE_STATE);
									else
									{
										UpdateVehicleInfo(indexs[ex_listitem]);
										if(IsPointInDynamicArea(sunshineAutos_Area, VehicleInfo[indexs[ex_listitem]][vinfo_POS][0], VehicleInfo[indexs[ex_listitem]][vinfo_POS][1], VehicleInfo[indexs[ex_listitem]][vinfo_POS][2]))
										{
											new price = GetOldVehiclePrice(indexs[ex_listitem]);
											if(price < oldvehicle_min_price) price = oldvehicle_min_price;

											inline OnPlayerConfirmDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
											{
												#pragma unused in_pid, in_dialogid, in_listitem, in_inputtext
												if(in_response)
												{
													slot = Iter_Free(sOldVehs);
													if(slot == cellmin) Text_Send(playerid, $MESSAGE_ERROR_VEHICLE_SELL);
													else
													{
														GivePlayerMoneyEx(playerid, price, true);
														orm_update(PI[playerid][pi_ORM]);
														Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_SOLD);

														AddOldSaleVehicle(indexs[ex_listitem], price, slot);
													}
												}
											}
											Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerConfirmDialog, $DIALOG_SELL_CONFIRM_CAPTION, $DIALOG_SELL_CONFIRM_BODY, $DIALOG_SELL_CONFIRM_YES, $DIALOG_SELL_CONFIRM_NO, GetVehicleNameByModelid(VehicleInfo[indexs[ex_listitem]][vinfo_MODELID]), VehicleInfo[indexs[ex_listitem]][vinfo_NUMBER_PLATE], price);
										}
										else Text_Send(playerid, $MESSAGE_ERROR_VEHICLE_AREA);
									}
								}
							}

							new dialog_message[64 * MAX_PLAYER_VEHICLES], line_str[64], count;
							foreach(new i : PlayerVehicles[playerid])
							{
								if(IsValidSellVehicleModelid(VehicleInfo[i][vinfo_MODELID]) && VehicleInfo[i][vinfo_TYPE] == VEHICLE_TYPE_PLAYER && VehicleInfo[i][vinfo_ID_PLAYER] == PI[playerid][pi_ID])
								{
									new price = GetOldVehiclePrice(i);
									if(price < oldvehicle_min_price) price = oldvehicle_min_price;

									format(line_str, sizeof line_str, "{c4c4c4}%s [%s]\t{79b259}%d$\n", GetVehicleNameByModelid(VehicleInfo[i][vinfo_MODELID]), VehicleInfo[i][vinfo_NUMBER_PLATE], price);
									strcat(dialog_message, line_str);
									indexs[count++] = i;
								}
							}
							if(count) Dialog_ShowCallback(playerid, using inline OnPlayerSelectVehicle, DIALOG_STYLE_TABLIST, " ", dialog_message, ">>", "X");
							else Text_Send(playerid, $MESSAGE_ERROR_NO_VEHICLES);
						}
					}
				}
			}
		}
	}

	HidePlayerInfoMessage(playerid);
	Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_SELECT_OPTION_CAPTION, $DIALOG_SELECT_OPTION_BODY, $DIALOG_SELECT_OPTION_YES, $DIALOG_SELECT_OPTION_NO);
	return 1;
}

hook OnPreviewMenuResponse(playerid, menu_id, menu_model_id, response, modelid, price)
{
	if(menu_id == saleVehiclesMenu && menu_model_id != -1)
	{
		if(response)
		{
			HidePreviewMenuForPlayer(playerid);
			
			new index = GetSaleVehicleIndexBySlotId(menu_model_id),
				gprice = GetVehiclePriceByModelid(saleVehicles[index][saleVeh_MODELID]), level = GetVehicleLevelByModelid(saleVehicles[index][saleVeh_MODELID]);

			if(index != -1)
			{
				inline OnPlayerDialog(pid, did, res, lis, string:inp[])
				{
					#pragma unused pid, did, lis, inp
					if(res)
					{
						if(gprice > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY, gprice - PI[playerid][pi_MONEY]);
						else if(level > PI[playerid][pi_LEVEL]) Text_Send(playerid, $MESSAGE_ERROR_NO_LEVEL, level);
						else if(CountPlayerVehicles(playerid) >= MAX_PLAYER_VEHICLES) Text_Send(playerid, $MESSAGE_ERROR_MAX_VEHS, MAX_PLAYER_VEHICLES);
						else if(GetPlayerInvFreeItemSlot(playerid) == cellmin) Text_Send(playerid, $MESSAGE_ERROR_INV_SLOT);
						else if(!PlayerInvContainsItem(playerid, _:INV_ITEM_DRIVER_LICENSE)) Text_Send(playerid, $MESSAGE_ERROR_NO_LICENSE);
						else
						{
							GivePlayerMoneyEx(playerid, -gprice, true);
							orm_update(PI[playerid][pi_ORM]);
							GivePlayerPrivateVehicle(playerid, gprice, level, saleVehicles[index][saleVeh_MODELID], newSaleVeh_Pos[0], newSaleVeh_Pos[1], newSaleVeh_Pos[2], newSaleVeh_Pos[3]);
							CallRemoteFunction("OnPlayerPurchaseCar", "i", playerid);
						}
					}
				}
				if(!PI[playerid][pi_MPH]) Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_SVEH_INFO_CAPTION, $DIALOG_SVEH_INFO_BODY, $DIALOG_SVEH_INFO_YES, $DIALOG_SVEH_INFO_NO, GetVehicleNameByModelid(saleVehicles[index][saleVeh_MODELID]), gprice, level, Model_TopSpeed(saleVehicles[index][saleVeh_MODELID]), GetVehicleMaxFuelByModelid(saleVehicles[index][saleVeh_MODELID]), GetVehicleSeatsByModelid(saleVehicles[index][saleVeh_MODELID]));
				else Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_SVEH_INFO_CAPTION, $DIALOG_SVEH_INFO_BODY_MPH, $DIALOG_SVEH_INFO_YES, $DIALOG_SVEH_INFO_NO, GetVehicleNameByModelid(saleVehicles[index][saleVeh_MODELID]), gprice, level, floatround(KMHtoMPH(float(Model_TopSpeed(saleVehicles[index][saleVeh_MODELID])))), GetVehicleMaxFuelByModelid(saleVehicles[index][saleVeh_MODELID]), GetVehicleSeatsByModelid(saleVehicles[index][saleVeh_MODELID]));
			}
		}
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return 1;
}

//hook OnPlayerVehicleChange(playerid, from_vehicleid, to_vehicleid)
//if(to_vehicleid != INVALID_OPVC_VEHICLE_ID)
hook OnPlayerGetVehicleIndex(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new index = GetPlayerVehicleIndex(playerid);
		if(VehicleInfo[index][vinfo_TYPE] == VEHICLE_TYPE_SELL)
		{
			inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
			{
				#pragma unused pid, dialogid, listitem, inputtext
				if(response)
				{
					if(VehicleInfo[index][vinfo_PRICE] > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY, VehicleInfo[index][vinfo_PRICE] - PI[playerid][pi_MONEY]);
					else if(VehicleInfo[index][vinfo_LEVEL] > PI[playerid][pi_LEVEL]) Text_Send(playerid, $MESSAGE_ERROR_NO_LEVEL, VehicleInfo[index][vinfo_PRICE]);
					else if(CountPlayerVehicles(playerid) >= MAX_PLAYER_VEHICLES) Text_Send(playerid, $MESSAGE_ERROR_MAX_VEHS, MAX_PLAYER_VEHICLES);
					else if(GetPlayerInvFreeItemSlot(playerid) == cellmin) Text_Send(playerid, $MESSAGE_ERROR_INV_SLOT);
					else if(!PlayerInvContainsItem(playerid, _:INV_ITEM_DRIVER_LICENSE)) Text_Send(playerid, $MESSAGE_ERROR_NO_LICENSE);
					else
					{
						//player
						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE vehicles SET type = %d, id_player = %d WHERE id = %d;", _:VEHICLE_TYPE_PLAYER, PI[playerid][pi_ID], VehicleInfo[index][vinfo_ID]);
						mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

						//money
						GivePlayerMoneyEx(playerid, -VehicleInfo[index][vinfo_PRICE], true);
						orm_update(PI[playerid][pi_ORM]);

						//sOldVehs
						if(VehShop_VehicleInfo[index][vshop_AREAID] != INVALID_STREAMER_ID)
						{
							DestroyDynamicArea(VehShop_VehicleInfo[index][vshop_AREAID]);
							VehShop_VehicleInfo[index][vshop_AREAID] = INVALID_STREAMER_ID;
						}
						Iter_Remove(sOldVehs, VehShop_VehicleInfo[index][vshop_SLOT]);

						//vehicle
						VehicleInfo[index][vinfo_TYPE] = VEHICLE_TYPE_PLAYER;
						VehicleInfo[index][vinfo_ID_PLAYER] = PI[playerid][pi_ID];
						VehShop_VehicleInfo[index][vshop_SLOT] = 0;
						VehicleInfo[index][vinfo_FUEL] = GetVehicleMaxFuelByModelid(VehicleInfo[index][vinfo_MODELID]);
						UpdateVehicleInfoDb(index);

						//player
						new inv_params[24];
						format(inv_params, sizeof inv_params, "%d,%d", VehicleInfo[index][vinfo_ID], VehicleInfo[index][vinfo_MODELID]);
						AddPlayerInventoryItem(playerid, _:INV_ITEM_VEHICLE_MASTER_KEY, inv_params);
						Iter_Add(PlayerVehicles[playerid], index);

						Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_BOUGHT);
						CallRemoteFunction("OnPlayerPurchaseUsedCar", "i", playerid);
						DestroyPlayerLabel(playerid);
					}
				}
			}
			if(!PI[playerid][pi_MPH]) Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_BUY_VEHICLE_INFO_CAPTION, $DIALOG_BUY_VEHICLE_INFO_BODY, $DIALOG_BUY_VEHICLE_INFO_YES, $DIALOG_BUY_VEHICLE_INFO_NO, GetVehicleNameByModelid(VehicleInfo[index][vinfo_MODELID]), VehicleInfo[index][vinfo_DISTANCE] / 1000.0, VehicleInfo[index][vinfo_PRICE], VehicleInfo[index][vinfo_LEVEL]);
			else Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_BUY_VEHICLE_INFO_CAPTION, $DIALOG_BUY_VEHICLE_INFO_BODY_MPH, $DIALOG_BUY_VEHICLE_INFO_YES, $DIALOG_BUY_VEHICLE_INFO_NO, GetVehicleNameByModelid(VehicleInfo[index][vinfo_MODELID]), KMHtoMPH(VehicleInfo[index][vinfo_DISTANCE] / 1000.0), VehicleInfo[index][vinfo_PRICE], VehicleInfo[index][vinfo_LEVEL]);
		}
	}
	return 1;
}