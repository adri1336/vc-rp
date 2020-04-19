#include <YSI\y_hooks>

loadtext lang[inv];

hook OnScriptInit()
{
	Iter_Init(PINV);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	pInvDisableInv[playerid] = false;
	pInvGivePlayerid[playerid] = INVALID_PLAYER_ID;
	pLastDrink[playerid] = 0;
	pLastEat[playerid] = 0;
	pEatVomit[playerid] = 0;
	pLastVomit[playerid] = 0;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(pInvDisableInv[playerid])
	{
		if(pInvGivePlayerid[playerid] != INVALID_PLAYER_ID)
		{
			Text_Send(pInvGivePlayerid[playerid], $MESSAGE_ERROR_GIVE_DISCONNECTED);
			pInvDisableInv[ pInvGivePlayerid[playerid] ] = false;
			pInvGivePlayerid[ pInvGivePlayerid[playerid] ] = INVALID_PLAYER_ID;
		}
	}

	new tmp_PINV[enum_PINV];
	for(new i = 0; i != PLAYER_INV_MAX_SLOTS; i ++)
	{
		PINV[playerid][i] = tmp_PINV;
	}
	
	pInvetory[playerid] = false;
	pInvSelected[playerid] = -1;

	DestroyPlayerInvetoryTextdraws(playerid);
	Iter_Clear(PINV[playerid]);
	return 1;
}

hook OnPlayerLogin(playerid)
{
	if(!pNewUser[playerid])
	LoadPlayerInvData(playerid);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(pInvetory[playerid]) CancelSelectTextDraw(playerid);
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(pInvetory[playerid])
	{
		if(clickedid == Text:INVALID_TEXT_DRAW)
		{
			HidePlayerInvetory(playerid);
			return 1;
		}
	}
	return 0;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	if(pInvetory[playerid])
	{
		for(new i = 0; i != PLAYER_INV_MAX_SLOTS; i ++)
		{
			if(playertextid == PTD_INV_ITEMS_BOX[playerid][i])
			{
				Dialog_Hide(playerid);
				if(pInvSelected[playerid] == i) pInvSelected[playerid] = -1;
				else pInvSelected[playerid] = i;
				if(pInvMoving[playerid])
				{
					MoveInventoryItem(playerid, pInvMove_Index[playerid], pInvSelected[playerid]);
					pInvMoving[playerid] = false;
					pInvMove_Index[playerid] = -1;
					pInvSelected[playerid] = -1;
				}
				if(pVInv[playerid])
				{
					new params[128];
					format(params, sizeof params, "%s", PINV[playerid][ pInvSelected[playerid] ][pinv_PARAMS]);
					switch(INV_ITEMS_Info[ PINV[playerid][ pInvSelected[playerid] ][pinv_ITEM_ID] ][inv_item_TYPE])
					{
						case INV_ITEM_TYPE_WEAPON:
						{
							new weapon_id = strval(params),
								weapon_index = GetPlayerWeaponIndexFromId(playerid, weapon_id);
							if(weapon_index != -1)
							{
								new weaponid, ammo;
								if(pWeapons[playerid][weapon_index][pweapon_CARRIED])
								{
									if(HasWeaponAmmo(pWeapons[playerid][weapon_index][pweapon_WEAPONID]))
									GetPlayerWeaponData(playerid, GetWeaponSlot(pWeapons[playerid][weapon_index][pweapon_WEAPONID]), weaponid, pWeapons[playerid][weapon_index][pweapon_AMMO]);
								}
								
								weaponid = pWeapons[playerid][weapon_index][pweapon_WEAPONID];
								ammo = pWeapons[playerid][weapon_index][pweapon_AMMO];
								format(params, sizeof params, "%d, %d", weaponid, ammo);
							}
						}
						case INV_ITEM_TYPE_TOY:
						{
							new toy_id = strval(params),
								toy_index = GetPlayerToyIndexFromId(playerid, toy_id);
							if(toy_index != -1)
							{
								new modelid, color1, color2;
								modelid = pToys[playerid][toy_index][ptoy_MODELID];
								color1 = pToys[playerid][toy_index][ptoy_COLOR1];
								color2 = pToys[playerid][toy_index][ptoy_COLOR2];
								format(params, sizeof params, "%d, %d, %d", modelid, color1, color2);
							}
						}
					}

					if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[ PINV[playerid][ pInvSelected[playerid] ][pinv_ITEM_ID] ][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
					{
						new tmp_pinv_index = pInvSelected[playerid];
						HidePlayerInvetory(playerid);
						
						inline OnPlayerAmountDialog(pid2, dialogid2, response2, listitem2, string:inputtext2[])
						{
							#pragma unused pid2, dialogid2, listitem2
							if(response2)
							{
								new amount;
								if(!sscanf(inputtext2, "d", amount))
								{
									if(amount < 1 || amount > PINV[playerid][tmp_pinv_index][pinv_AMOUNT]) Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
									else
									{
										if(AddVehicleInventoryItem(pVInvVehIndex[playerid], PINV[playerid][tmp_pinv_index][pinv_ITEM_ID], params, amount)) RemovePlayerInvetoryItem(playerid, tmp_pinv_index, false, amount);
										else Text_Send(playerid, $MESSAGE_ERROR_VINV);
									}
								}
								else Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
							}
						}
						Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnPlayerAmountDialog, $DIALOG_MOVE_ITEM_TO_VINV_CAPTION, $DIALOG_MOVE_ITEM_TO_VINV_BODY, $DIALOG_MOVE_ITEM_TO_VINV_YES, $DIALOG_MOVE_ITEM_TO_VINV_NO, PINV[playerid][tmp_pinv_index][pinv_AMOUNT]);
					}
					else
					{
						if(AddVehicleInventoryItem(pVInvVehIndex[playerid], PINV[playerid][ pInvSelected[playerid] ][pinv_ITEM_ID], params)) RemovePlayerInvetoryItem(playerid, pInvSelected[playerid]);
						else Text_Send(playerid, $MESSAGE_ERROR_VINV);
						HidePlayerInvetory(playerid);
					}
					UpdateVInventoryInvTd(playerid);
				}
				UpdatePlayerInventoryTextdraws(playerid);
				return 1;
			}
		}

		for(new i = 0; i != MAX_INV_BUTTONS; i ++)
		{
			if(playertextid == PTD_INV_BUTTONS[playerid][i])
			{
				InvButtonAction(playerid, pInvButtonAction[playerid][i], i, pInvExtraId[playerid]);
				return 1;
			}
		}
	}
	return 0;
}

public DB_OnPlayerInvItemAdded(playerid, index, item_id, params[], amount)
{
	if(Iter_Contains(PINV[playerid], index)) PINV[playerid][index][pinv_AMOUNT] += amount;
	else
	{
		PINV[playerid][index][pinv_ID] = cache_insert_id();
		PINV[playerid][index][pinv_ITEM_ID] = item_id;
		PINV[playerid][index][pinv_AMOUNT] = amount;
		format(PINV[playerid][index][pinv_PARAMS], 128, "%s", params);
		Iter_Add(PINV[playerid], index);
	}

	if(pInvetory[playerid]) UpdatePlayerInventoryTextdraws(playerid);
	CallRemoteFunction("OnPlayerItemAdded", "iddd", playerid, index, item_id, amount);
	return 1;
}

YCMD:inv(playerid, params[], help)
{
	if(!pInvetory[playerid]) ShowPlayerInventory(playerid);
	else CancelSelectTextDraw(playerid);
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(GetPlayerGameState(playerid) == GAME_STATE_SPAWNED)
	{
		if(PRESSED(ACTION_KEY) && !pInvetory[playerid])
		{
			ShowPlayerInventory(playerid);
		}
	}
	return 1;
}

hook OnSelectNearPlayer(playerid, id, selected_playerid)
{
	if(pInvSelected[playerid] != -1 && Iter_Contains(PINV[playerid], pInvSelected[playerid]))
	{
		if(pInvDisableInv[selected_playerid]) Text_Send(playerid, $MESSAGE_ERROR_PLAYER_INV_DISABLED);
		else
		{
			if(IsPlayerPaused(selected_playerid)) Text_Send(playerid, $MESSAGE_ERROR_GIVE_PLAYER_AFK);
			else
			{
				switch(id)
				{
					case NEAR_PLAYER_DIALOG_INV_SHOW:
					{
						new itemid = PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID], itemparams[128];
						format(itemparams, sizeof itemparams, "%s", PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]);
						if(isnull(itemparams)) itemparams = "null";
						
						new item_name1[64], item_name2[64];
						format(item_name1, sizeof item_name1, "%s", GetItemName(playerid, PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID], PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]));
						format(item_name2, sizeof item_name2, "%s", GetItemName(selected_playerid, PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID], PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]));
						if(playerid != selected_playerid)
						{
							Text_Send(playerid, $MESSAGE_INFO_ITEM_SHOWN, item_name1, PI[selected_playerid][pi_RP_NAME]);
							Text_Send(selected_playerid, $MESSAGE_INFO_ITEM_SHOW, PI[playerid][pi_RP_NAME], item_name2);
						}
						inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
						{
							#pragma unused pid, dialogid, response, listitem, inputtext
						}
						
						format(item_name2, sizeof item_name2, "%c%s", toupper(item_name2[0]), item_name2[1]);
						Text_DialogBox(selected_playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_SHOW_ITEM_CAPTION, $DIALOG_SHOW_ITEM_BODY, $DIALOG_SHOW_ITEM_YES, "", item_name2, PI[playerid][pi_RP_NAME], PINV[playerid][ pInvSelected[playerid] ][pinv_PARAMS]);
						CallRemoteFunction("OnPlShowItemToPlayer", "iids", playerid, selected_playerid, itemid, itemparams);
					}
					case NEAR_PLAYER_DIALOG_INV_GIVE:
					{
						if(INV_ITEMS_Info[ PINV[playerid][ pInvSelected[playerid] ][pinv_ITEM_ID] ][inv_item_TYPE] != _:INV_ITEM_TYPE_MASTER_KEY)
						{
							new item_index = pInvSelected[playerid],
								item_id = PINV[playerid][item_index][pinv_ID];

							inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
							{
								#pragma unused pid, dialogid, listitem, inputtext
								if(response)
								{
									if(!IsPlayerNearPlayer(selected_playerid, playerid)) Text_Send(selected_playerid, $MESSAGE_ERROR_SELECTED_PLAYER_GONE);
									else
									{
										if(!pInvDisableInv[playerid] || !pInvDisableInv[selected_playerid] || pInvGivePlayerid[playerid] != selected_playerid || pInvGivePlayerid[selected_playerid] != playerid) Text_Send(playerid, $MESSAGE_ERROR_SELECTED_PLAYER_GONE);
										else
										{
											new item_name_playerid[64], item_name_selected_playerid[64];
											format(item_name_playerid, sizeof item_name_playerid, "%s", GetItemName(playerid, PINV[playerid][item_index][pinv_ITEM_ID], PINV[playerid][item_index][pinv_PARAMS]));
											format(item_name_selected_playerid, sizeof item_name_selected_playerid, "%s", GetItemName(selected_playerid, PINV[playerid][item_index][pinv_ITEM_ID], PINV[playerid][item_index][pinv_PARAMS]));

											new itemid = PINV[playerid][item_index][pinv_ITEM_ID], itemparams[128];
											format(itemparams, sizeof itemparams, "%s", PINV[playerid][item_index][pinv_PARAMS]);
											if(isnull(itemparams)) itemparams = "null";

											if(PINV[playerid][item_index][pinv_ID] == item_id)
											{
												if(GivePlayerInvItem(playerid, item_index, selected_playerid, pInvGiveAmount[playerid]))
												{
													Text_Send(selected_playerid, $MESSAGE_INFO_GIVE_PLAYER, PI[playerid][pi_RP_NAME], item_name_selected_playerid);
													Text_Send(playerid, $MESSAGE_INFO_GIVE, item_name_playerid, PI[selected_playerid][pi_RP_NAME]);
													CallRemoteFunction("OnPlGiveItemToPlayer", "iids", playerid, selected_playerid, itemid, itemparams);
												}
												else
												{
													Text_Send(selected_playerid, $MESSAGE_ERROR_GIVE_ERROR_PLAYER);
													Text_Send(playerid, $MESSAGE_ERROR_GIVE_ERROR);
												}
											}
											else
											{
												Text_Send(selected_playerid, $MESSAGE_ERROR_GIVE_ERROR_ID);
												Text_Send(playerid, $MESSAGE_ERROR_GIVE_ERROR_ID);
											}
										}
									}
								}
								else Text_Send(playerid, $MESSAGE_INFO_GIVE_REJECT, PI[selected_playerid][pi_RP_NAME]);

								pInvDisableInv[ pInvGivePlayerid[playerid] ] = false;
								pInvGivePlayerid[ pInvGivePlayerid[playerid] ] = INVALID_PLAYER_ID;
								pInvDisableInv[playerid] = false;
								pInvGivePlayerid[playerid] = INVALID_PLAYER_ID;
							}

							pInvDisableInv[playerid] = true;
							pInvGivePlayerid[playerid] = selected_playerid;

							pInvDisableInv[selected_playerid] = true;
							pInvGivePlayerid[selected_playerid] = playerid;

							if(pInvetory[playerid]) CancelSelectTextDraw(playerid);
							if(pInvetory[selected_playerid]) CancelSelectTextDraw(selected_playerid);

							Text_Send(playerid, $MESSAGE_INFO_GIVE_WAIT, PI[selected_playerid][pi_RP_NAME]);
							Text_DialogBox(selected_playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_GIVE_ITEM_CAPTION, $DIALOG_GIVE_ITEM_BODY, $DIALOG_GIVE_ITEM_YES, $DIALOG_GIVE_ITEM_NO, PI[playerid][pi_RP_NAME], playerid, GetItemName(selected_playerid, PINV[playerid][item_index][pinv_ITEM_ID], PINV[playerid][item_index][pinv_PARAMS]), pInvGiveAmount[playerid]);
						}
					}
				}
			}
		}
	}
	return 1;
}