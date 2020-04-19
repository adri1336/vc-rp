loadtext lang[inv];

DestroyPlayerInvetoryTextdraws(playerid)
{
	if(PTD_INV_BASE[playerid][0] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_INV_BASE[playerid][0]);
		PTD_INV_BASE[playerid][0] = PlayerText:INVALID_TEXT_DRAW;
	}	
	if(PTD_INV_BASE[playerid][1] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_INV_BASE[playerid][1]);
		PTD_INV_BASE[playerid][1] = PlayerText:INVALID_TEXT_DRAW;
	}
	if(PTD_INV_BASE[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_INV_BASE[playerid][2]);
		PTD_INV_BASE[playerid][2] = PlayerText:INVALID_TEXT_DRAW;
	}

	for(new i = 0; i != PLAYER_INV_MAX_SLOTS; i ++)
	{
		if(PTD_INV_ITEMS_BOX[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_INV_ITEMS_BOX[playerid][i]);
			PTD_INV_ITEMS_BOX[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		if(PTD_INV_ITEMS[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_INV_ITEMS[playerid][i]);
			PTD_INV_ITEMS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		if(PTD_INV_ITEMS_AMOUNT[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i]);
			PTD_INV_ITEMS_AMOUNT[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}

	if(PTD_INV_INFO_MESSAGE[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_INV_INFO_MESSAGE[playerid]);
		PTD_INV_INFO_MESSAGE[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
	DestroyPlayerInvButtons(playerid);
	return 1;
}

CreatePlayerInvetoryTextdraws(playerid)
{
	new Float:result_x, Float:result_size_x,
		Float:real_INVENTORY_ITEM_SIZE_X,
		Float:real_INVENTORY_ITEM_SPACE,
		Float:real_INV_TD_AMOUNT_OFFSET_X
	;

	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, INVENTORY_ITEM_SIZE_X, false, result_x, real_INVENTORY_ITEM_SIZE_X);
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, INVENTORY_ITEM_SPACE, false, result_x, real_INVENTORY_ITEM_SPACE);	
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, INV_TD_AMOUNT_OFFSET_X, false, result_x, real_INV_TD_AMOUNT_OFFSET_X);	

	//PTD_INV_BASE
	new Float:size_x = ((real_INVENTORY_ITEM_SIZE_X + real_INVENTORY_ITEM_SPACE) * INVENTORY_COLUMNS), Float:size_y = INVENTORY_TEXT_SIZE_Y + INVENTORY_MESSAGE_SPACE;
	PTD_INV_BASE[playerid][0] = CreatePlayerTextDraw(playerid, INVENTORY_POS_X - (size_x / 2) - real_INVENTORY_ITEM_SPACE, INVENTORY_POS_Y, "LD_SPAC:white");
	PlayerTextDrawColor(playerid, PTD_INV_BASE[playerid][0], 909588720);
	PlayerTextDrawFont(playerid, PTD_INV_BASE[playerid][0], 4);
	SetPlayerTextDrawLayer(playerid, PTD_INV_BASE[playerid][0], LAYER_INVENTORY);

	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], INVENTORY_POS_X, size_x, true, result_x, result_size_x);
	PTD_INV_BASE[playerid][1] = CreatePlayerTextDraw(playerid, INVENTORY_POS_X - (size_x / 2) - real_INVENTORY_ITEM_SPACE, INVENTORY_POS_Y, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, PTD_INV_BASE[playerid][1], size_x + (real_INVENTORY_ITEM_SPACE * 2), INVENTORY_TEXT_SIZE_Y);
	PlayerTextDrawColor(playerid, PTD_INV_BASE[playerid][1], 690563839);
	PlayerTextDrawFont(playerid, PTD_INV_BASE[playerid][1], 4);
	SetPlayerTextDrawLayer(playerid, PTD_INV_BASE[playerid][1], LAYER_INVENTORY);

	PTD_INV_BASE[playerid][2] = CreatePlayerTextDraw(playerid, INVENTORY_POS_X, INVENTORY_POS_Y, "TEXT");
	PlayerTextDrawLetterSize(playerid, PTD_INV_BASE[playerid][2], 0.262665, 1.345484);
	PlayerTextDrawTextSize(playerid, PTD_INV_BASE[playerid][2], 0.000000, size_x);
	PlayerTextDrawAlignment(playerid, PTD_INV_BASE[playerid][2], 2);
	PlayerTextDrawColor(playerid, PTD_INV_BASE[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, PTD_INV_BASE[playerid][2], 0);
	PlayerTextDrawFont(playerid, PTD_INV_BASE[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, PTD_INV_BASE[playerid][2], 1);
	SetPlayerTextDrawLayer(playerid, PTD_INV_BASE[playerid][2], LAYER_INVENTORY);

	//PTD_INV_ITEMS_BOX
	new Float:initial_item_pos_x = INVENTORY_POS_X - ((real_INVENTORY_ITEM_SIZE_X / 2) * INVENTORY_COLUMNS) - ((real_INVENTORY_ITEM_SPACE / 2) * (INVENTORY_COLUMNS - 1)),
		Float:initial_item_pos_y = INVENTORY_POS_Y + INVENTORY_TEXT_SIZE_Y + real_INVENTORY_ITEM_SPACE + INVENTORY_MESSAGE_SPACE,
		count_x, count_y,
		mid_column = floatround(floatdiv(INVENTORY_COLUMNS, 2), floatround_ceil), mid_row = floatround(floatdiv(floatdiv(PLAYER_INV_MAX_SLOTS, INVENTORY_COLUMNS), 2), floatround_ceil);

	size_y += INVENTORY_ITEM_SIZE_Y + (real_INVENTORY_ITEM_SPACE * 3); //1 columna, hay 2 espacios arriba y abajo
	for(new i = 0; i != PLAYER_INV_MAX_SLOTS; i ++)
	{
		pInvTextDrawPosition[playerid][i][0] = initial_item_pos_x + (real_INVENTORY_ITEM_SIZE_X + real_INVENTORY_ITEM_SPACE) * count_x;
		pInvTextDrawPosition[playerid][i][1] = initial_item_pos_y + ((INVENTORY_ITEM_SIZE_Y + real_INVENTORY_ITEM_SPACE) * count_y);

		if(count_x + 1 >= mid_column) pInvTextDrawInverted[playerid][i][0] = true;
		else pInvTextDrawInverted[playerid][i][0] = false;

		if(count_y + 1 >= mid_row) pInvTextDrawInverted[playerid][i][1] = true;
		else pInvTextDrawInverted[playerid][i][1] = false;

		PTD_INV_ITEMS_BOX[playerid][i] = CreatePlayerTextDraw(playerid, pInvTextDrawPosition[playerid][i][0], pInvTextDrawPosition[playerid][i][1], ""TEXTDRAW_CUSTOM_PATH"inv_box_null");
		PlayerTextDrawTextSize(playerid, PTD_INV_ITEMS_BOX[playerid][i], real_INVENTORY_ITEM_SIZE_X, INVENTORY_ITEM_SIZE_Y);
		PlayerTextDrawSetSelectable(playerid, PTD_INV_ITEMS_BOX[playerid][i], true);
		PlayerTextDrawFont(playerid, PTD_INV_ITEMS_BOX[playerid][i], 4);
		SetPlayerTextDrawLayer(playerid, PTD_INV_ITEMS_BOX[playerid][i], LAYER_INVENTORY);

		PTD_INV_ITEMS[playerid][i] = CreatePlayerTextDraw(playerid, pInvTextDrawPosition[playerid][i][0], pInvTextDrawPosition[playerid][i][1], ""TEXTDRAW_CUSTOM_PATH"icon_undefinied");
		PlayerTextDrawTextSize(playerid, PTD_INV_ITEMS[playerid][i], real_INVENTORY_ITEM_SIZE_X, INVENTORY_ITEM_SIZE_Y);
		PlayerTextDrawFont(playerid, PTD_INV_ITEMS[playerid][i], 4);
		SetPlayerTextDrawLayer(playerid, PTD_INV_ITEMS[playerid][i], LAYER_INVENTORY);

		PTD_INV_ITEMS_AMOUNT[playerid][i] = CreatePlayerTextDraw(playerid, pInvTextDrawPosition[playerid][i][0] + real_INV_TD_AMOUNT_OFFSET_X, pInvTextDrawPosition[playerid][i][1] + INV_TD_AMOUNT_OFFSET_Y, "0");
		PlayerTextDrawLetterSize(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i], 0.130331, 0.645925);
		PlayerTextDrawAlignment(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i], 3);
		PlayerTextDrawSetShadow(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i], 0);
		PlayerTextDrawFont(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i], 1);
		PlayerTextDrawSetProportional(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i], 1);
		SetPlayerTextDrawLayer(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i], LAYER_INVENTORY);

		count_x ++;
		if(count_x == INVENTORY_COLUMNS)
		{
			count_x = 0;
			count_y ++;
			if(i < PLAYER_INV_MAX_SLOTS - 1) size_y += INVENTORY_ITEM_SIZE_Y + real_INVENTORY_ITEM_SPACE;
		}
	}
	//
	PlayerTextDrawTextSize(playerid, PTD_INV_BASE[playerid][0], size_x + (real_INVENTORY_ITEM_SPACE * 2), size_y);

	//
	PTD_INV_INFO_MESSAGE[playerid] = CreatePlayerTextDraw(playerid, INVENTORY_POS_X, INVENTORY_POS_Y + INVENTORY_MESSAGE_OFFSET, "Mensaje de informacion");
	PlayerTextDrawLetterSize(playerid, PTD_INV_INFO_MESSAGE[playerid], 0.196999, 0.994369);
	PlayerTextDrawTextSize(playerid, PTD_INV_INFO_MESSAGE[playerid], 0.000000, size_x + (real_INVENTORY_ITEM_SPACE * 2));
	PlayerTextDrawAlignment(playerid, PTD_INV_INFO_MESSAGE[playerid], 2);
	PlayerTextDrawColor(playerid, PTD_INV_INFO_MESSAGE[playerid], -1);
	PlayerTextDrawSetShadow(playerid, PTD_INV_INFO_MESSAGE[playerid], 0);
	PlayerTextDrawFont(playerid, PTD_INV_INFO_MESSAGE[playerid], 1);
	PlayerTextDrawSetProportional(playerid, PTD_INV_INFO_MESSAGE[playerid], 1);
	SetPlayerTextDrawLayer(playerid, PTD_INV_INFO_MESSAGE[playerid], LAYER_INVENTORY);
	return 1;
}

ShowPlayerInventory(playerid)
{
	if(pInvDisableInv[playerid]) Text_Send(playerid, $MESSAGE_ERROR_INV_DISABLED, PI[ pInvGivePlayerid[playerid] ][pi_RP_NAME], pInvGivePlayerid[playerid]);
	else
	{
		pInvetory[playerid] = true;
		pInvMoving[playerid] = false;
		pInvMove_Index[playerid] = -1;
		pInvSelected[playerid] = -1;
		CreatePlayerInvetoryTextdraws(playerid);
		FormatPlayerInventoryTextdraws(playerid, PTD_INV_BASE[playerid][2]);
		UpdatePlayerInventoryTextdraws(playerid);
		DisablePlayerLayers(playerid, LAYER_INVENTORY, true, LAYER_RADAR);
		ShowPlayerInventoryTextdraws(playerid);
		SelectTextDraw(playerid, 0xFFFFFFFF);

		CallRemoteFunction("OnPlayerOpenInventory", "i", playerid);
	}
	return 1;
}

HidePlayerInvetory(playerid)
{
	pInvetory[playerid] = false;
	pInvSelected[playerid] = -1;
	//Dialog_Hide(playerid);
	DestroyPlayerInvetoryTextdraws(playerid);
	if(!pVInv[playerid]) EnablePlayerLayers(playerid);
	CallRemoteFunction("OnPlayerCloseInventory", "i", playerid);
	return 1;
}

ShowPlayerInventoryTextdraws(playerid)
{
	//
	PlayerTextDrawShow(playerid, PTD_INV_BASE[playerid][0]);
	PlayerTextDrawShow(playerid, PTD_INV_BASE[playerid][1]);
	PlayerTextDrawShow(playerid, PTD_INV_BASE[playerid][2]);

	//
	for(new i = 0; i != PLAYER_INV_MAX_SLOTS; i ++)
	{
		PlayerTextDrawShow(playerid, PTD_INV_ITEMS_BOX[playerid][i]);
	}
	//
	PlayerTextDrawShow(playerid, PTD_INV_INFO_MESSAGE[playerid]);
	return 1;
}

/*HidePlayerInventoryTextdraws(playerid)
{
	//
	PlayerTextDrawHide(playerid, PTD_INV_BASE[playerid][0]);
	PlayerTextDrawHide(playerid, PTD_INV_BASE[playerid][1]);
	PlayerTextDrawHide(playerid, PTD_INV_BASE[playerid][2]);

	//
	for(new i = 0; i != PLAYER_INV_MAX_SLOTS; i ++)
	{
		PlayerTextDrawHide(playerid, PTD_INV_ITEMS_BOX[playerid][i]);
		PlayerTextDrawHide(playerid, PTD_INV_ITEMS[playerid][i]);
		PlayerTextDrawHide(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i]);
	}
	//
	PlayerTextDrawHide(playerid, PTD_INV_INFO_MESSAGE[playerid]);
	//
	DestroyPlayerInvButtons(playerid);
	return 1;
}*/


UpdatePlayerInventoryTextdraws(playerid)
{
	PlayerTextDrawSetString(playerid, PTD_INV_INFO_MESSAGE[playerid], "_");

	for(new i = 0; i != PLAYER_INV_MAX_SLOTS; i ++)
	{
		if(Iter_Contains(PINV[playerid], i)) PlayerTextDrawSetString(playerid, PTD_INV_ITEMS_BOX[playerid][i], ""TEXTDRAW_CUSTOM_PATH"inv_box_item");
		else PlayerTextDrawSetString(playerid, PTD_INV_ITEMS_BOX[playerid][i], ""TEXTDRAW_CUSTOM_PATH"inv_box_null");
		PlayerTextDrawColor(playerid, PTD_INV_ITEMS_BOX[playerid][i], -1);
		if(pVInv[playerid]) PlayerTextDrawSetSelectable(playerid, PTD_INV_ITEMS_BOX[playerid][i], false);
		else PlayerTextDrawSetSelectable(playerid, PTD_INV_ITEMS_BOX[playerid][i], true);
		PlayerTextDrawShow(playerid, PTD_INV_ITEMS_BOX[playerid][i]);

		PlayerTextDrawSetString(playerid, PTD_INV_ITEMS[playerid][i], ""TEXTDRAW_CUSTOM_PATH"icon_undefinied");
		PlayerTextDrawColor(playerid, PTD_INV_ITEMS[playerid][i], -1);
		PlayerTextDrawHide(playerid, PTD_INV_ITEMS[playerid][i]);

		PlayerTextDrawSetString(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i], "0");
		PlayerTextDrawHide(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i]);
	}

	if(pInvSelected[playerid] != -1)
	{
		PlayerTextDrawSetString(playerid, PTD_INV_ITEMS_BOX[playerid][pInvSelected[playerid]], ""TEXTDRAW_CUSTOM_PATH"inv_box_selected");

		if(Iter_Contains(PINV[playerid], pInvSelected[playerid]))
		{
			pInvExtraId[playerid] = -1;
			switch(PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID])
			{
				case INV_ITEM_VEHICLE_MASTER_KEY, INV_ITEM_VEHICLE_KEY, INV_ITEM_VEHICLE_RENT_KEY:
				{
					new vid, modelid;
					sscanf(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS], "p<,>dd", vid, modelid);
					pInvExtraId[playerid] = GetVehicleIndexById(vid);
				}
				case INV_ITEM_PROPERTY_MASTER_KEY, INV_ITEM_PROPERTY_KEY, INV_ITEM_PROPERTY_RENT_KEY:
				{
					new pid;
					sscanf(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS], "d", pid);
					pInvExtraId[playerid] = GetPropertyIndexFromId(pid);
				}
				case INV_ITEM_BUSINESS_MASTER_KEY, INV_ITEM_BUSINESS_KEY:
				{
					new bid;
					sscanf(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS], "d", bid);
					pInvExtraId[playerid] = GetBusinessIndexFromId(bid);	
				}
			}
			FormatPlayerInvMsgTextdraw(playerid, PTD_INV_INFO_MESSAGE[playerid], PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID], PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]);

			for(new i = 0; i != MAX_INV_BUTTONS; i ++) pInvButtonAction[playerid][i] = INV_BUTTON_TYPE_NONE;
			CreateInvButtons(playerid, pInvButtonAction[playerid], pInvExtraId[playerid]);
			FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
		}
		else
		{
			FormatPlayerInvMsgTextdraw(playerid, PTD_INV_INFO_MESSAGE[playerid], -1);
			DestroyPlayerInvButtons(playerid);
		}
	}
	else DestroyPlayerInvButtons(playerid);

	foreach(new i : PINV[playerid])
	{
		new string[128];
		format(string, sizeof string, ""TEXTDRAW_CUSTOM_PATH"%s", INV_ITEMS_Info[PINV[playerid][i][pinv_ITEM_ID]][inv_item_ICON_NAME]);
		PlayerTextDrawSetString(playerid, PTD_INV_ITEMS[playerid][i], string);

		if(pVInv[playerid])
		{
			if(!IsItemTypeDynamic(INV_ITEMS_Info[ PINV[playerid][i][pinv_ITEM_ID] ][inv_item_TYPE]))
			{
				PlayerTextDrawColor(playerid, PTD_INV_ITEMS_BOX[playerid][i], 0x888888FF);
				PlayerTextDrawSetSelectable(playerid, PTD_INV_ITEMS_BOX[playerid][i], false);
				PlayerTextDrawShow(playerid, PTD_INV_ITEMS_BOX[playerid][i]);
				PlayerTextDrawColor(playerid, PTD_INV_ITEMS[playerid][i], 0x888888FF);
			}
			else
			{
				PlayerTextDrawSetSelectable(playerid, PTD_INV_ITEMS_BOX[playerid][i], true);
				PlayerTextDrawShow(playerid, PTD_INV_ITEMS_BOX[playerid][i]);
			}
		}

		PlayerTextDrawShow(playerid, PTD_INV_ITEMS[playerid][i]);

		if(pInvSelected[playerid] == -1 || i == pInvSelected[playerid] || !Iter_Contains(PINV[playerid], pInvSelected[playerid])) //para que no se sobrepongan los numeros a los botones
		{
			if(INV_ITEMS_TYPES_Info[ INV_ITEMS_Info[PINV[playerid][i][pinv_ITEM_ID]][inv_item_TYPE] ][inv_item_type_MULTIPLIABLE])
			{
				format(string, sizeof string, "%d", PINV[playerid][i][pinv_AMOUNT]);
				PlayerTextDrawSetString(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i], string);
				PlayerTextDrawShow(playerid, PTD_INV_ITEMS_AMOUNT[playerid][i]);			
			}
		}
	}
	return 1;
}

CreateInvButtons(playerid, INV_BUTTONS_TYPES:button_var_action[], extra_id = -1)
{
	if(pInvSelected[playerid] != -1)
	{
		DestroyPlayerInvButtons(playerid);

		new buttons;
		switch(INV_ITEMS_Info[PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID]][inv_item_TYPE])
		{
			case INV_ITEM_TYPE_KEY:
			{
				switch(PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID])
				{
					case INV_ITEM_VEHICLE_KEY:
					{
						if(extra_id == INVALID_VEHICLE_INDEX)
						{
							button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
						}
						else
						{
							if(IsPlayerInVehicle(playerid, VehicleInfo[extra_id][vinfo_VEHICLE_ID]))
							{
								if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
								{
									if(VehicleModelHasDoors(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_DOORS]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_CLOSE;
									}
									if(VehicleModelHasEngine(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_ENGINE]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_STOP;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_START;
									}
								}
								else
								{
									if(VehicleModelHasDoors(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_DOORS]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_CLOSE;
									}
								}
								button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
								button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
								button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
							}
							else
							{
								if(GetPlayerCameraTargetVehicle(playerid) == VehicleInfo[extra_id][vinfo_VEHICLE_ID])
								{
									if(VehicleModelHasDoors(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_DOORS]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_CLOSE;
									}
								}
								button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
								button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
								button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
							}
						}
					}
					case INV_ITEM_PROPERTY_KEY:
					{
						if(extra_id == -1)
						{
							button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
						}
						else
						{
							if(pLastAreaId[playerid] != INVALID_STREAMER_ID)
							{
								if(IsPlayerInDynamicArea(playerid, pLastAreaId[playerid]))
								{
									new streamer_info[3];
									Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
									if((streamer_info[0] == _:AREA_TYPE_LABEL_EXT_PROP_DOOR || streamer_info[0] == _:AREA_TYPE_LABEL_INT_PROP_DOOR || streamer_info[0] == _:AREA_TYPE_EXT_PROPERTY_DOOR || streamer_info[0] == _:AREA_TYPE_INT_PROPERTY_DOOR) && streamer_info[1] == extra_id)
									{
										if(PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_CLOSED]) button_var_action[buttons++] = INV_BUTTON_TYPE_PDOOR_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_PDOOR_CLOSE;
									}
								}
							}
							button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
						}
					}
					case INV_ITEM_BUSINESS_KEY:
					{
						if(extra_id == -1)
						{
							button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
						}
						else
						{
							if(pLastAreaId[playerid] != INVALID_STREAMER_ID)
							{
								if(IsPlayerInDynamicArea(playerid, pLastAreaId[playerid]))
								{
									new streamer_info[3];
									Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
									if((streamer_info[0] == _:AREA_TYPE_BDOOR_EXT || streamer_info[0] == _:AREA_TYPE_LABEL_BDOOR_EXT || streamer_info[0] == _:AREA_TYPE_BDOOR_INT || streamer_info[0] == _:AREA_TYPE_LABEL_BDOOR_INT) && streamer_info[1] == extra_id)
									{
										if(BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_CLOSED]) button_var_action[buttons++] = INV_BUTTON_TYPE_BDOOR_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_BDOOR_CLOSE;
									}
								}
							}
							button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
						}
					}
				}
			}
			case INV_ITEM_TYPE_RENT_KEY:
			{
				switch(PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID])
				{
					case INV_ITEM_VEHICLE_RENT_KEY:
					{
						if(extra_id == INVALID_VEHICLE_INDEX)
						{
							button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
						}
						else
						{
							if(IsPlayerInVehicle(playerid, VehicleInfo[extra_id][vinfo_VEHICLE_ID]))
							{
								if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
								{
									if(VehicleModelHasDoors(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_DOORS]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_CLOSE;
									}
									if(VehicleModelHasEngine(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_ENGINE]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_STOP;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_START;
									}
								}
								else
								{
									if(VehicleModelHasDoors(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_DOORS]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_CLOSE;
									}
								}
								button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
								button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
								button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
							}
							else
							{
								if(GetPlayerCameraTargetVehicle(playerid) == VehicleInfo[extra_id][vinfo_VEHICLE_ID])
								{
									if(VehicleModelHasDoors(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_DOORS]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_CLOSE;
									}
								}
								button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
								button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
								button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
							}
						}
					}
					case INV_ITEM_PROPERTY_RENT_KEY:
					{
						if(extra_id == -1)
						{
							button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
						}
						else
						{
							if(pLastAreaId[playerid] != INVALID_STREAMER_ID)
							{
								if(IsPlayerInDynamicArea(playerid, pLastAreaId[playerid]))
								{
									new streamer_info[3];
									Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
									if((streamer_info[0] == _:AREA_TYPE_LABEL_EXT_PROP_DOOR || streamer_info[0] == _:AREA_TYPE_LABEL_INT_PROP_DOOR || streamer_info[0] == _:AREA_TYPE_EXT_PROPERTY_DOOR || streamer_info[0] == _:AREA_TYPE_INT_PROPERTY_DOOR) && streamer_info[1] == extra_id)
									{
										if(PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_CLOSED]) button_var_action[buttons++] = INV_BUTTON_TYPE_PDOOR_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_PDOOR_CLOSE;
									}
								}
							}
							button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
							button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
						}
					}
				}
			}
			case INV_ITEM_TYPE_MASTER_KEY:
			{
				switch(PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID])
				{
					case INV_ITEM_VEHICLE_MASTER_KEY:
					{
						if(extra_id == INVALID_VEHICLE_INDEX) button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
						else
						{
							if(IsPlayerInVehicle(playerid, VehicleInfo[extra_id][vinfo_VEHICLE_ID]))
							{
								if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
								{
									if(VehicleModelHasDoors(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_DOORS]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_CLOSE;
									}

									if(VehicleModelHasEngine(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_ENGINE]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_STOP;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_START;
									}
								}
								else
								{
									if(VehicleModelHasDoors(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_DOORS]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_CLOSE;
									}
								}
								button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
							}
							else
							{
								if(GetPlayerCameraTargetVehicle(playerid) == VehicleInfo[extra_id][vinfo_VEHICLE_ID])
								{
									if(VehicleModelHasDoors(VehicleInfo[extra_id][vinfo_MODELID]))
									{
										if(VehicleInfo[extra_id][vinfo_PARAMS_DOORS]) button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_VEHICLE_CLOSE;
									}
								}
								button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
							}
						}
					}
					case INV_ITEM_PROPERTY_MASTER_KEY:
					{
						if(extra_id == -1) button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
						else
						{
							if(pLastAreaId[playerid] != INVALID_STREAMER_ID)
							{
								if(IsPlayerInDynamicArea(playerid, pLastAreaId[playerid]))
								{
									new streamer_info[3];
									Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
									if((streamer_info[0] == _:AREA_TYPE_LABEL_EXT_PROP_DOOR || streamer_info[0] == _:AREA_TYPE_LABEL_INT_PROP_DOOR || streamer_info[0] == _:AREA_TYPE_EXT_PROPERTY_DOOR || streamer_info[0] == _:AREA_TYPE_INT_PROPERTY_DOOR) && streamer_info[1] == extra_id)
									{
										if(PropertyDoor[streamer_info[1]][streamer_info[2]][prop_door_CLOSED]) button_var_action[buttons++] = INV_BUTTON_TYPE_PDOOR_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_PDOOR_CLOSE;
									}
								}
							}
							button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
						}
					}
					case INV_ITEM_BUSINESS_MASTER_KEY:
					{
						if(extra_id == -1) button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
						else
						{
							if(pLastAreaId[playerid] != INVALID_STREAMER_ID)
							{
								if(IsPlayerInDynamicArea(playerid, pLastAreaId[playerid]))
								{
									new streamer_info[3];
									Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
									if((streamer_info[0] == _:AREA_TYPE_BDOOR_EXT || streamer_info[0] == _:AREA_TYPE_LABEL_BDOOR_EXT || streamer_info[0] == _:AREA_TYPE_BDOOR_INT || streamer_info[0] == _:AREA_TYPE_LABEL_BDOOR_INT) && streamer_info[1] == extra_id)
									{
										if(BusinessDoors[streamer_info[1]][streamer_info[2]][bdoor_CLOSED]) button_var_action[buttons++] = INV_BUTTON_TYPE_BDOOR_OPEN;
										else button_var_action[buttons++] = INV_BUTTON_TYPE_BDOOR_CLOSE;
									}
								}
							}
							button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
						}
					}
				}
			}
			case INV_ITEM_TYPE_LICENSE:
			{
				button_var_action[buttons++] = INV_BUTTON_TYPE_SHOW;
				button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
			}
			case INV_ITEM_TYPE_ID:
			{
				button_var_action[buttons++] = INV_BUTTON_TYPE_SHOW;
				button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
			}
			case INV_ITEM_TYPE_WEAPON:
			{
				new weapon_id = strval(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]);
				new weapon_index = GetPlayerWeaponIndexFromId(playerid, weapon_id);
				if(weapon_index != -1)
				{
					if(pWeapons[playerid][weapon_index][pweapon_CARRIED]) button_var_action[buttons++] = INV_BUTTON_WEAPON_CARRY_NO;
					else button_var_action[buttons++] = INV_BUTTON_WEAPON_CARRY_YES;
					button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
					button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
					button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
				}
			}
			case INV_ITEM_TYPE_TOY:
			{
				new toy_id = strval(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]);
				new toy_index = GetPlayerToyIndexFromId(playerid, toy_id);
				if(toy_index != -1)
				{
					if(IsModelidWatch(pToys[playerid][toy_index][ptoy_MODELID])) button_var_action[buttons++] = INV_BUTTON_WATCH_TIME;
					if(pToys[playerid][toy_index][ptoy_ATTACHED]) button_var_action[buttons++] = INV_BUTTON_TOY_REMOVE;
					else button_var_action[buttons++] = INV_BUTTON_TOY_ATTACH;
					button_var_action[buttons++] = INV_BUTTON_CONFIG_TOY;
					button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
					button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
					button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;

				}
			}
			case INV_ITEM_TYPE_PHONE:
			{
				if(PI[playerid][pi_PHONE_ON]) button_var_action[buttons++] = INV_BUTTON_TYPE_OPEN_PHONE;
				else button_var_action[buttons++] = INV_BUTTON_TURN_PHONE_ON;
				button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
			}
			case INV_ITEM_TYPE_GPS:
			{
				button_var_action[buttons++] = INV_BUTTON_TYPE_OPEN_GPS;
				button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
			}
			case INV_ITEM_TYPE_FOOD:
			{
				button_var_action[buttons++] = INV_BUTTON_FOOD_EAT;
				button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
			}
			case INV_ITEM_TYPE_DRINK:
			{
				button_var_action[buttons++] = INV_BUTTON_DRINK_DRINK;
				button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
			}
			case INV_ITEM_TYPE_CIGARETTE:
			{
				button_var_action[buttons++] = INV_BUTTON_TYPE_SMOKE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
			}
			case INV_ITEM_TYPE_BOOMBOX:
			{
				button_var_action[buttons++] = INV_BUTTON_USE_BOOMBOX;
				button_var_action[buttons++] = INV_BUTTON_TYPE_GIVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_MOVE;
				button_var_action[buttons++] = INV_BUTTON_TYPE_DELETE;
			}
		}

		//
		if(buttons > 0)
		{
			new Float:result_x,
				Float:real_INVENTORY_ITEM_SIZE_X,
				Float:real_INV_BUTTONS_BOX_SPACE,
				Float:real_INV_BUTTONS_BOX_SIZE_X
			;
			AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, INVENTORY_ITEM_SIZE_X, false, result_x, real_INVENTORY_ITEM_SIZE_X);
			AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, INV_BUTTONS_BOX_SPACE, false, result_x, real_INV_BUTTONS_BOX_SPACE);	
			AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, INV_BUTTONS_BOX_SIZE_X, false, result_x, real_INV_BUTTONS_BOX_SIZE_X);	
			
			new Float:box_pos_x,
				Float:box_pos_y,
				Float:box_size_y = (real_INV_BUTTONS_BOX_SPACE * 2) + (INV_BUTTONS_TEXT_SEPARATION * buttons);

			if(pInvTextDrawInverted[playerid][pInvSelected[playerid]][0]) box_pos_x = pInvTextDrawPosition[playerid][pInvSelected[playerid]][0] - real_INV_BUTTONS_BOX_SIZE_X;
			else box_pos_x = pInvTextDrawPosition[playerid][pInvSelected[playerid]][0] + real_INVENTORY_ITEM_SIZE_X;

			if(pInvTextDrawInverted[playerid][pInvSelected[playerid]][1]) box_pos_y = pInvTextDrawPosition[playerid][pInvSelected[playerid]][1] - box_size_y;
			else box_pos_y = pInvTextDrawPosition[playerid][pInvSelected[playerid]][1] + INVENTORY_ITEM_SIZE_Y;


			for(new i = 0; i != buttons; i ++)
			{
				if(i >= MAX_INV_BUTTONS) break;

				PTD_INV_BUTTONS[playerid][i] = CreatePlayerTextDraw(playerid, box_pos_x + real_INV_BUTTONS_BOX_SPACE, box_pos_y + (real_INV_BUTTONS_BOX_SPACE + (INV_BUTTONS_TEXT_SEPARATION * i)), "Button", true);
				PlayerTextDrawLetterSize(playerid, PTD_INV_BUTTONS[playerid][i], 0.196999, 0.994369);
				PlayerTextDrawTextSize(playerid, PTD_INV_BUTTONS[playerid][i], box_pos_x + real_INV_BUTTONS_BOX_SIZE_X, INV_BUTTONS_TEXT_SEPARATION - 2.0);
				PlayerTextDrawColor(playerid, PTD_INV_BUTTONS[playerid][i], -1);
				PlayerTextDrawSetShadow(playerid, PTD_INV_BUTTONS[playerid][i], 0);
				PlayerTextDrawFont(playerid, PTD_INV_BUTTONS[playerid][i], 1);
				PlayerTextDrawSetProportional(playerid, PTD_INV_BUTTONS[playerid][i], 1);
				PlayerTextDrawSetSelectable(playerid, PTD_INV_BUTTONS[playerid][i], true);
				SetPlayerTextDrawLayer(playerid, PTD_INV_BUTTONS[playerid][i], LAYER_INVENTORY);
				PlayerTextDrawShow(playerid, PTD_INV_BUTTONS[playerid][i]);
			}

			PTD_INV_BUTTONS_BOX[playerid] = CreatePlayerTextDraw(playerid, box_pos_x, box_pos_y, ""TEXTDRAW_CUSTOM_PATH"inv_buttons_box", true);
			PlayerTextDrawFont(playerid, PTD_INV_BUTTONS_BOX[playerid], 4);
			PlayerTextDrawSetSelectable(playerid, PTD_INV_BUTTONS_BOX[playerid], true);
			SetPlayerTextDrawLayer(playerid, PTD_INV_BUTTONS_BOX[playerid], LAYER_INVENTORY);
			PlayerTextDrawTextSize(playerid, PTD_INV_BUTTONS_BOX[playerid], real_INV_BUTTONS_BOX_SIZE_X, box_size_y);
			PlayerTextDrawShow(playerid, PTD_INV_BUTTONS_BOX[playerid]);
		}
		return buttons;
	}
	return 0;
}

DestroyPlayerInvButtons(playerid)
{
	if(PTD_INV_BUTTONS_BOX[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_INV_BUTTONS_BOX[playerid]);
		PTD_INV_BUTTONS_BOX[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}

	for(new i = 0; i != MAX_INV_BUTTONS; i ++)
	{
		if(PTD_INV_BUTTONS[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_INV_BUTTONS[playerid][i]);
			PTD_INV_BUTTONS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

LoadPlayerInvData(playerid)
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				new bool:isnull_params, id, position;
				cache_get_value_name_int(i, "id", id);
				cache_get_value_name_int(i, "position", position);
				if((position < 0 || position >= PLAYER_INV_MAX_SLOTS) || Iter_Contains(PINV[playerid], position))
				{
					position = Iter_Free(PINV[playerid]);
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET position = %d WHERE id = %d;", position, id);
					mysql_tquery(vcrp_db, QUERY_BUFFER);
				}
				PINV[playerid][position][pinv_ID] = id;
				cache_get_value_name_int(i, "item_id", PINV[playerid][position][pinv_ITEM_ID]);
				cache_get_value_name_int(i, "amount", PINV[playerid][position][pinv_AMOUNT]);
				cache_is_value_name_null(i, "params", isnull_params);
				if(!isnull_params) cache_get_value_name(i, "params", PINV[playerid][position][pinv_PARAMS], 128);
				Iter_Add(PINV[playerid], position);
			}
			CallRemoteFunction("OnPlayerInvDataLoaded", "i", playerid);
		}
	}

	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM player_inv WHERE player_id = '%d' LIMIT %d;", PI[playerid][pi_ID], PLAYER_INV_MAX_SLOTS);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	return 1;	
}

#define GetPlayerInvFreeItemSlot(%0) Iter_Free(PINV[%0])

AddPlayerInventoryItem(playerid, item_id, params[], amount = 1)
{
	if(IsValidItemId(item_id))
	{
		if(!(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_UNIQUE] && PlayerInvContainsItemType(playerid, INV_ITEMS_Info[item_id][inv_item_TYPE])))
		{
			/* amount check */
			if(amount < 1)
			return 0;

			if(!INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
			amount = 1;

			////////////////////////////
			if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MULTIPLIABLE] && PlayerInvContainsItem(playerid, item_id))
			{ //el objeto es multiplicable y tiene 1 o mas en su inv
				new index = GetPlayerInvIndexByItem(playerid, item_id, params);
				if(index == -1)
				{
					new inv_index = GetPlayerInvFreeItemSlot(playerid);
					if(inv_index != cellmin)
					{
						if(amount > INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MAX_MULTIPLIED])
						return 0;

						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_inv (player_id, item_id, amount, params, position) VALUES ('%d', '%d', %d, '%e', %d);", PI[playerid][pi_ID], item_id, amount, params, inv_index);
						mysql_tquery(vcrp_db, QUERY_BUFFER, "DB_OnPlayerInvItemAdded", "dddsd", playerid, inv_index, item_id, params, amount);
						return 1;
					}
				}
				else
				{
					new total_amount = PINV[playerid][index][pinv_AMOUNT] + amount;
					if(total_amount > INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MAX_MULTIPLIED])
					return 0;

					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET amount = %d WHERE id = '%d';", total_amount, PINV[playerid][index][pinv_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER, "DB_OnPlayerInvItemAdded", "dddsd", playerid, index, item_id, params, amount);
					return 1;
				}
			}
			else
			{ //no tiene el objeto (multiplicable o no)
				if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
				{
					if(amount > INV_ITEMS_TYPES_Info[INV_ITEMS_Info[item_id][inv_item_TYPE]][inv_item_type_MAX_MULTIPLIED])
					return 0;
				}
				
				new index = GetPlayerInvFreeItemSlot(playerid);
				if(index != cellmin)
				{
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_inv (player_id, item_id, amount, params, position) VALUES ('%d', '%d', %d, '%e', %d);", PI[playerid][pi_ID], item_id, amount, params, index);
					mysql_tquery(vcrp_db, QUERY_BUFFER, "DB_OnPlayerInvItemAdded", "dddsd", playerid, index, item_id, params, amount);
					return 1;
				}
			}
		}
	}
	return 0;
}

IsValidItemId(item_id)
{
	if(item_id <= 0 || item_id >= _:INV_ITEMS) return 0;
	return 1;
}

RemovePlayerInvetoryItem(playerid, index, bool:player_action = false, amount = 1)
{
	if(Iter_Contains(PINV[playerid], index))
	{
		if(INV_ITEMS_Info[ PINV[playerid][index][pinv_ITEM_ID] ][inv_item_TYPE] != _:INV_ITEM_TYPE_MASTER_KEY)
		{
			new inv_id = PINV[playerid][index][pinv_ID],
				itemid = PINV[playerid][index][pinv_ITEM_ID],
				params[128];

			format(params, sizeof params, "%s", PINV[playerid][index][pinv_PARAMS]);

			if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[ PINV[playerid][index][pinv_ITEM_ID] ][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
			{
				if(PINV[playerid][index][pinv_AMOUNT] > 1)
				{
					if(PINV[playerid][index][pinv_AMOUNT] - amount <= 0)
					{
						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_inv WHERE id = %d;", PINV[playerid][index][pinv_ID]);
						mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

						new tmp_PINV[enum_PINV];
						PINV[playerid][index] = tmp_PINV;
						Iter_Remove(PINV[playerid], index);
					}
					else
					{
						PINV[playerid][index][pinv_AMOUNT] -= amount;
						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET amount = %d WHERE id = %d;", PINV[playerid][index][pinv_AMOUNT], PINV[playerid][index][pinv_ID]);
						mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
					}
				}
				else
				{
					amount = 1;
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_inv WHERE id = %d;", PINV[playerid][index][pinv_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

					new tmp_PINV[enum_PINV];
					PINV[playerid][index] = tmp_PINV;
					Iter_Remove(PINV[playerid], index);
				}
			}
			else
			{
				amount = 1;
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_inv WHERE id = %d;", PINV[playerid][index][pinv_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

				new tmp_PINV[enum_PINV];
				PINV[playerid][index] = tmp_PINV;
				Iter_Remove(PINV[playerid], index);
			}
			//playerid, index, inv_id, itemid, params[], bool:player_action
			CallRemoteFunction("OnPlayerItemDeleted", "idddsbd", playerid, index, inv_id, itemid, params, player_action, amount);
			return 1;
		}
	}
	return 0;
}

GetPlayerInvIndexByItem(playerid, item_id, params[])
{
	foreach(new i : PINV[playerid])
	{
		if(PINV[playerid][i][pinv_ITEM_ID] == item_id && !strcmp(PINV[playerid][i][pinv_PARAMS], params))
		{
			return i;
		}
	}
	return -1;	
}

PlayerInvContainsItemType(playerid, type_id)
{
	foreach(new i : PINV[playerid])
	{
		if(INV_ITEMS_Info[ PINV[playerid][i][pinv_ITEM_ID] ][inv_item_TYPE] == type_id)
		{
			return 1;
		}
	}
	return 0;
}

PlayerInvContainsItem(playerid, item_id)
{
	foreach(new i : PINV[playerid])
	{
		if(PINV[playerid][i][pinv_ITEM_ID] == item_id)
		{
			return 1;
		}
	}
	return 0;
}

PlayerInvContainsItemEx(playerid, item_id1, item_id2, item_id3, params[])
{
	foreach(new i : PINV[playerid])
	{
		if((PINV[playerid][i][pinv_ITEM_ID] == item_id1 || PINV[playerid][i][pinv_ITEM_ID] == item_id2 || PINV[playerid][i][pinv_ITEM_ID] == item_id3) && !strcmp(PINV[playerid][i][pinv_PARAMS], params))
		{
			return 1;
		}
	}
	return 0;
}

InvButtonAction(playerid, INV_BUTTONS_TYPES:button_action, button_slot, extra_id = -1)
{
	switch(button_action)
	{
		case INV_BUTTON_USE_BOOMBOX:
		{
			new index = pInvSelected[playerid];
			CancelSelectTextDraw(playerid);
			CallRemoteFunction("OnPlayerRequestBoomboxCreation", "id", playerid, index);
		}
		case INV_BUTTON_WATCH_TIME:
		{
			CancelSelectTextDraw(playerid);
			CallRemoteFunction("OnPlayerCheckTime", "i", playerid);	
		}
		case INV_BUTTON_TYPE_SMOKE:
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
			RemovePlayerInvetoryItem(playerid, pInvSelected[playerid]);
			CancelSelectTextDraw(playerid);
		}
		case INV_BUTTON_FOOD_EAT:
		{
			if(pEatVomit[playerid] >= 3)
			{
				RemovePlayerAnimEnv(playerid);
				PI[playerid][pi_HUNGRY] += 25.0;
				if(PI[playerid][pi_HUNGRY] > 100.0) PI[playerid][pi_HUNGRY] = 100.0;
				pEatVomit[playerid] = 0;
				pLastVomit[playerid] = GetTickCount();

				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				SetPlayerAnimEnv(playerid, "FOOD", "EAT_Vomit_P", false, 18722, 2, 0.000000, 1.784000, -0.135000, 85.899986, 0.000000, 0.000000, .time = 6000, .animdelay = 3000, .soundid = 32201);
			}
			else
			{
				if(GetTickCount() - pLastEat[playerid] < 3000) Text_Send(playerid, $MESSAGE_ERROR_FOOD_LIMIT);
				else
				{
					if(GetTickCount() - pLastVomit[playerid] < 600000) Text_Send(playerid, $MESSAGE_ERROR_FOOD_VOMIT);
					else
					{
						new modelid = GetModelidFromInvItemId(PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID]);
						if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
						{
							switch(PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID])
							{
								case INV_ITEM_HAMBURGER: SetPlayerAnimEnv(playerid, "FOOD", "EAT_Burger", false, modelid, 6, 0.036999, 0.027999, -0.001000, -13.399999, 0.000000, 21.499998, 0.883999, 0.717000, 0.798000, .time = 3000);
								case INV_ITEM_HOTDOG: SetPlayerAnimEnv(playerid, "FOOD", "EAT_Burger", false, modelid, 6, 0.065999,0.032999,0.017000,-107.000000,164.400009,8.699995,0.669999,0.539000,0.778000, .time = 3000);
								case INV_ITEM_PIZZA: SetPlayerAnimEnv(playerid, "FOOD", "EAT_Pizza", false, modelid, 6, 0.007000,0.100000,0.107999,-80.499977,9.199999,25.299982,0.871000,0.838000,0.846000, .time = 3000);
							}
						}
						//
						CallRemoteFunction("OnPlayerEat", "id", playerid, PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID]);
						PI[playerid][pi_HUNGRY] -= float(strval(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]));
						if(PI[playerid][pi_HUNGRY] <= 0.0) PI[playerid][pi_HUNGRY] = 0.0;
						RemovePlayerInvetoryItem(playerid, pInvSelected[playerid]);
						if(!Iter_Contains(PINV[playerid], pInvSelected[playerid])) pInvSelected[playerid] = -1;
						UpdatePlayerInventoryTextdraws(playerid);

						if(GetTickCount() - pLastEat[playerid] < 10000) pEatVomit[playerid] ++;
						else pEatVomit[playerid] = 0;
						pLastEat[playerid] = GetTickCount();
					}
				}
			}
		}
		case INV_BUTTON_DRINK_DRINK:
		{
			if(GetTickCount() - pLastDrink[playerid] < 3000) Text_Send(playerid, $MESSAGE_ERROR_DRINK_LIMIT);
			else
			{
				if(PI[playerid][pi_THIRST] <= 0.0) Text_Send(playerid, $MESSAGE_ERROR_DRINK);
				else
				{
					new modelid = GetModelidFromInvItemId(PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID]);
					switch(PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID])
					{
						case INV_ITEM_BEER:
						{
							if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) SetPlayerAnimEnv(playerid, "VENDING", "VEND_Drink2_P", true, modelid, 5, 0.117999,0.051999,-0.029000,0.000000,173.299942,0.000000,0.736000,0.709000,0.849000, .time = 3000);
							SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 500);
						}
						case INV_ITEM_SODA:
						{
							if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) SetPlayerAnimEnv(playerid, "VENDING", "VEND_Drink2_P", true, modelid, 5, 0.110999,0.083000,-0.009000,0.000000,-172.000045,-123.199996,0.822000,0.810000,0.889000, .time = 3000);
						}
						case INV_ITEM_WATER:
						{
							if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) SetPlayerAnimEnv(playerid, "VENDING", "VEND_Drink2_P", true, modelid, 5, 0.123999,0.068999,-0.019000,0.000000,0.000000,0.000000,0.949000,0.840000,0.703000, .time = 3000);
						}
						case INV_ITEM_WHISKY:
						{
							if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) SetPlayerAnimEnv(playerid, "VENDING", "VEND_Drink2_P", true, modelid, 5, 0.140000,0.064999,-0.032999,0.000000,172.800125,0.000000,0.883000,0.862000,0.899000, .time = 3000);
							SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 1000);
						}

					}
					//
					CallRemoteFunction("OnPlayerDrink", "id", playerid, PINV[playerid][pInvSelected[playerid]][pinv_ITEM_ID]);
					PI[playerid][pi_THIRST] -= float(strval(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]));
					if(PI[playerid][pi_THIRST] <= 0.0) PI[playerid][pi_THIRST] = 0.0;
					RemovePlayerInvetoryItem(playerid, pInvSelected[playerid]);
					if(!Iter_Contains(PINV[playerid], pInvSelected[playerid])) pInvSelected[playerid] = -1;
					UpdatePlayerInventoryTextdraws(playerid);
					pLastDrink[playerid] = GetTickCount();
				}
			}
		}
		case INV_BUTTON_WEAPON_CARRY_YES:
		{
			new weapon_id = strval(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]);
			new weapon_index = GetPlayerWeaponIndexFromId(playerid, weapon_id);
			if(weapon_index != -1)
			{
				if(CountPlayerCarriedWeapons(playerid) >= MAX_PLAYER_WEAPONS_CARRIED) Text_Send(playerid, $MESSAGE_ERROR_WEAPON_MAX, MAX_PLAYER_WEAPONS_CARRIED);
				else
				{
					pWeapons[playerid][weapon_index][pweapon_CARRIED] = 1;
					GivePlayerWeapon(playerid, pWeapons[playerid][weapon_index][pweapon_WEAPONID], pWeapons[playerid][weapon_index][pweapon_AMMO]);
					SetPlayerArmedWeapon(playerid, pWeapons[playerid][weapon_index][pweapon_WEAPONID]);
					UpdatePlayerWeapon(playerid, weapon_index);

					pInvButtonAction[playerid][button_slot] = INV_BUTTON_WEAPON_CARRY_NO;
					FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
					CallRemoteFunction("OnPlayerCarryWeapon", "id", playerid, pWeapons[playerid][weapon_index][pweapon_WEAPONID]);
				}
			}	
		}
		case INV_BUTTON_WEAPON_CARRY_NO:
		{
			new weapon_id = strval(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]);
			new weapon_index = GetPlayerWeaponIndexFromId(playerid, weapon_id);
			if(weapon_index != -1)
			{
				pWeapons[playerid][weapon_index][pweapon_CARRIED] = 0;
				if(HasWeaponAmmo(pWeapons[playerid][weapon_index][pweapon_WEAPONID]))
				{
					new weaponid, ammo;
					GetPlayerWeaponData(playerid, GetWeaponSlot(pWeapons[playerid][weapon_index][pweapon_WEAPONID]), weaponid, ammo);
					if(weaponid == pWeapons[playerid][weapon_index][pweapon_WEAPONID])
					pWeapons[playerid][weapon_index][pweapon_AMMO] = ammo;
				}
				SetPlayerWeapons(playerid);
				UpdatePlayerWeapon(playerid, weapon_index);

				pInvButtonAction[playerid][button_slot] = INV_BUTTON_WEAPON_CARRY_YES;
				FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
				CallRemoteFunction("OnPlayerUncarryWeapon", "id", playerid, pWeapons[playerid][weapon_index][pweapon_WEAPONID]);
			}
		}
		case INV_BUTTON_TYPE_DELETE:
		{
			if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[ PINV[playerid][ pInvSelected[playerid] ][pinv_ITEM_ID] ][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
			{
				inline OnPlayerAmountDialog(pid2, dialogid2, response2, listitem2, string:inputtext2[])
				{
					#pragma unused pid2, dialogid2, listitem2
					if(response2)
					{
						new amount;
						if(!sscanf(inputtext2, "d", amount))
						{
							if(amount < 1 || amount > PINV[playerid][ pInvSelected[playerid] ][pinv_AMOUNT]) Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
							else
							{
								inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
								{
									#pragma unused pid, dialogid, listitem, inputtext
									if(response)
									{
										if(RemovePlayerInvetoryItem(playerid, pInvSelected[playerid], true, amount))
										{
											pInvSelected[playerid] = -1;
											UpdatePlayerInventoryTextdraws(playerid);
											Text_Send(playerid, $GAMETEXT_INFO_ITEM_DELETE);
										}
									}
								}
								Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_DELETE_ITEM_CAPTION, $DIALOG_DELETE_ITEM_BODY, $DIALOG_DELETE_ITEM_YES, $DIALOG_DELETE_ITEM_NO);
							}
						}
						else Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
					}
				}
				Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnPlayerAmountDialog, $DIALOG_DELETE_ITEM_AMOUNT_CAPTION, $DIALOG_DELETE_ITEM_AMOUNT_BODY, $DIALOG_DELETE_ITEM_AMOUNT_YES, $DIALOG_DELETE_ITEM_AMOUNT_NO, PINV[playerid][ pInvSelected[playerid] ][pinv_AMOUNT]);
			}
			else
			{
				inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
				{
					#pragma unused pid, dialogid, listitem, inputtext
					if(response)
					{
						if(RemovePlayerInvetoryItem(playerid, pInvSelected[playerid], true))
						{
							pInvSelected[playerid] = -1;
							UpdatePlayerInventoryTextdraws(playerid);
							Text_Send(playerid, $GAMETEXT_INFO_ITEM_DELETE);
						}
					}
				}
				Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_DELETE_ITEM_CAPTION, $DIALOG_DELETE_ITEM_BODY, $DIALOG_DELETE_ITEM_YES, $DIALOG_DELETE_ITEM_NO);
			}
		}
		case INV_BUTTON_TYPE_MOVE:
		{
			pInvMoving[playerid] = true;
			pInvMove_Index[playerid] = pInvSelected[playerid];
			DestroyPlayerInvButtons(playerid);
			Text_Send(playerid, $MESSAGE_INFO_MOVE);
		}
		case INV_BUTTON_TYPE_GIVE:
		{
			if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[ PINV[playerid][ pInvSelected[playerid] ][pinv_ITEM_ID] ][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
			{
				inline OnPlayerAmountDialog(pid2, dialogid2, response2, listitem2, string:inputtext2[])
				{
					#pragma unused pid2, dialogid2, listitem2
					if(response2)
					{
						new amount;
						if(!sscanf(inputtext2, "d", amount))
						{
							if(amount < 1 || amount > PINV[playerid][ pInvSelected[playerid] ][pinv_AMOUNT]) Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
							else
							{
								pInvGiveAmount[playerid] = amount;
								NearsPlayersDialog(playerid, NEAR_PLAYER_DIALOG_INV_GIVE);
							}
						}
						else Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
					}
				}
				Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnPlayerAmountDialog, $DIALOG_GIVE_ITEM_AMOUNT_CAPTION, $DIALOG_GIVE_ITEM_AMOUNT_BODY, $DIALOG_GIVE_ITEM_AMOUNT_YES, $DIALOG_GIVE_ITEM_AMOUNT_NO, PINV[playerid][ pInvSelected[playerid] ][pinv_AMOUNT]);
			}
			else
			{
				pInvGiveAmount[playerid] = 1;
				NearsPlayersDialog(playerid, NEAR_PLAYER_DIALOG_INV_GIVE);
			}
		}
		case INV_BUTTON_TYPE_SHOW: NearsPlayersDialog(playerid, NEAR_PLAYER_DIALOG_INV_SHOW, true);
		case INV_BUTTON_TOY_ATTACH:
		{
			new toy_id = strval(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]);
			new toy_index = GetPlayerToyIndexFromId(playerid, toy_id);
			if(toy_index != -1)
			{
				pToys[playerid][toy_index][ptoy_ATTACHED] = 1;
				SetPlayerToy(playerid, toy_index);
				UpdatePlayerToy(playerid, toy_index);

				pInvButtonAction[playerid][button_slot] = INV_BUTTON_TOY_REMOVE;
				FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
				CallRemoteFunction("OnPlayerAttachToy", "id", playerid, toy_index);
			}
		}
		case INV_BUTTON_TOY_REMOVE:
		{
			new toy_id = strval(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]);
			new toy_index = GetPlayerToyIndexFromId(playerid, toy_id);
			if(toy_index != -1)
			{
				pToys[playerid][toy_index][ptoy_ATTACHED] = 0;
				SetPlayerToy(playerid, toy_index);
				UpdatePlayerToy(playerid, toy_index);
				
				pInvButtonAction[playerid][button_slot] = INV_BUTTON_TOY_ATTACH;
				FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
				CallRemoteFunction("OnPlayerRemoveToy", "id", playerid, toy_index);
			}
		}
		case INV_BUTTON_CONFIG_TOY:
		{
			new toy_id = strval(PINV[playerid][pInvSelected[playerid]][pinv_PARAMS]);
			new toy_index = GetPlayerToyIndexFromId(playerid, toy_id);
			if(toy_index != -1)
			{
				if(pToys[playerid][toy_index][ptoy_ATTACHED])
				{
					CancelSelectTextDraw(playerid);
					CallRemoteFunction("OnPlayerRequestConfigToy", "id", playerid, toy_index);
				}
				else Text_Send(playerid, $MESSAGE_ERROR_TOY_NOT_ATTACHED);
			}
		}
		case INV_BUTTON_TYPE_VEHICLE_OPEN:
		{
			VehicleInfo[extra_id][vinfo_PARAMS_DOORS] = 0;
			SetVehicleParams(extra_id);
			pInvButtonAction[playerid][button_slot] = INV_BUTTON_TYPE_VEHICLE_CLOSE;
			FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
			Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_OPENED);
			CallRemoteFunction("OnPlayerOpenVehicle", "id", playerid, VehicleInfo[extra_id][vinfo_MODELID]);
		}
		case INV_BUTTON_TYPE_VEHICLE_CLOSE:
		{
			VehicleInfo[extra_id][vinfo_PARAMS_DOORS] = 1;
			SetVehicleParams(extra_id);

			pInvButtonAction[playerid][button_slot] = INV_BUTTON_TYPE_VEHICLE_OPEN;
			FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
			Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_CLOSED);
			CallRemoteFunction("OnPlayerCloseVehicle", "id", playerid, VehicleInfo[extra_id][vinfo_MODELID]);
		}
		case INV_BUTTON_TYPE_VEHICLE_START:
		{
			if(VehicleInfo[extra_id][vinfo_GAME_STATE] == VEHICLE_GAME_STATE_POUNDED)
			{
				inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
				{
					#pragma unused pid, dialogid, listitem, inputtext
					if(response)
					{
						if(VEHICLE_POUND_PRICE > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY, VEHICLE_POUND_PRICE);
						else
						{
							GivePlayerMoneyEx(playerid, -VEHICLE_POUND_PRICE, true);

							VehicleInfo[extra_id][vinfo_GAME_STATE] = VEHICLE_GAME_STATE_NORMAL;
							if(VehicleInfo[extra_id][vinfo_FUEL] <= 0.0) Text_Send(playerid, $MESSAGE_ERROR_NO_FUEL);
							else
							{
								VehicleInfo[extra_id][vinfo_PARAMS_ENGINE] = 1;
								SetVehicleParams(extra_id);

								pInvButtonAction[playerid][button_slot] = INV_BUTTON_TYPE_VEHICLE_STOP;
								FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
								Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_STARTED);
								CallRemoteFunction("OnPlayerStartVehicle", "id", playerid, VehicleInfo[extra_id][vinfo_MODELID]);
							}
						}
					}
				}
				Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_VEHICLE_POUND_CAPTION, $DIALOG_VEHICLE_POUND_BODY, $DIALOG_VEHICLE_POUND_YES, $DIALOG_VEHICLE_POUND_NO, VEHICLE_POUND_PRICE);
			}
			else
			{
				if(VehicleInfo[extra_id][vinfo_FUEL] <= 0.0) Text_Send(playerid, $MESSAGE_ERROR_NO_FUEL);
				else
				{
					VehicleInfo[extra_id][vinfo_PARAMS_ENGINE] = 1;
					SetVehicleParams(extra_id);

					pInvButtonAction[playerid][button_slot] = INV_BUTTON_TYPE_VEHICLE_STOP;
					FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
					Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_STARTED);
					CallRemoteFunction("OnPlayerStartVehicle", "id", playerid, VehicleInfo[extra_id][vinfo_MODELID]);
				}
			}
		}
		case INV_BUTTON_TYPE_VEHICLE_STOP:
		{
			VehicleInfo[extra_id][vinfo_PARAMS_ENGINE] = 0;
			SetVehicleParams(extra_id);

			pInvButtonAction[playerid][button_slot] = INV_BUTTON_TYPE_VEHICLE_START;
			FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
			Text_Send(playerid, $GAMETEXT_INFO_VEHICLE_STOPPED);
			CallRemoteFunction("OnPlayerStopVehicle", "id", playerid, VehicleInfo[extra_id][vinfo_MODELID]);
		}
		case INV_BUTTON_TYPE_PDOOR_OPEN:
		{
			new streamer_info[3];
			Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
			if(Iter_Contains(PropertyDoor[extra_id], streamer_info[2]))
			{
				PropertyDoor[extra_id][streamer_info[2]][prop_door_CLOSED] = false;
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties_doors SET closed = %d WHERE id = %d;", PropertyDoor[extra_id][streamer_info[2]][prop_door_CLOSED], PropertyDoor[extra_id][streamer_info[2]][prop_door_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);

				pInvButtonAction[playerid][button_slot] = INV_BUTTON_TYPE_PDOOR_CLOSE;
				FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
				Text_Send(playerid, $GAMETEXT_INFO_DOOR_OPENED);
				CallRemoteFunction("OnPlayerOpenProperty", "i", playerid);
			}
		}
		case INV_BUTTON_TYPE_PDOOR_CLOSE:
		{
			new streamer_info[3];
			Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
			if(Iter_Contains(PropertyDoor[extra_id], streamer_info[2]))
			{
				PropertyDoor[extra_id][streamer_info[2]][prop_door_CLOSED] = true;
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties_doors SET closed = %d WHERE id = %d;", PropertyDoor[extra_id][streamer_info[2]][prop_door_CLOSED], PropertyDoor[extra_id][streamer_info[2]][prop_door_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);

				pInvButtonAction[playerid][button_slot] = INV_BUTTON_TYPE_PDOOR_OPEN;
				FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
				Text_Send(playerid, $GAMETEXT_INFO_DOOR_CLOSED);
				CallRemoteFunction("OnPlayerCloseProperty", "i", playerid);
			}
		}
		case INV_BUTTON_TYPE_BDOOR_OPEN:
		{
			new streamer_info[3];
			Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
			if(Iter_Contains(BusinessDoors[extra_id], streamer_info[2]))
			{
				BusinessDoors[extra_id][streamer_info[2]][bdoor_CLOSED] = false;
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business_doors SET closed = %d WHERE id = %d;", BusinessDoors[extra_id][streamer_info[2]][bdoor_CLOSED], BusinessDoors[extra_id][streamer_info[2]][bdoor_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);

				pInvButtonAction[playerid][button_slot] = INV_BUTTON_TYPE_BDOOR_CLOSE;
				FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
				Text_Send(playerid, $GAMETEXT_INFO_DOOR_OPENED);
			}
		}
		case INV_BUTTON_TYPE_BDOOR_CLOSE:
		{
			new streamer_info[3];
			Streamer_GetArrayData(STREAMER_TYPE_AREA, pLastAreaId[playerid], E_STREAMER_EXTRA_ID, streamer_info);
			if(Iter_Contains(BusinessDoors[extra_id], streamer_info[2]))
			{
				BusinessDoors[extra_id][streamer_info[2]][bdoor_CLOSED] = true;
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business_doors SET closed = %d WHERE id = %d;", BusinessDoors[extra_id][streamer_info[2]][bdoor_CLOSED], BusinessDoors[extra_id][streamer_info[2]][bdoor_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);

				pInvButtonAction[playerid][button_slot] = INV_BUTTON_TYPE_BDOOR_OPEN;
				FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
				Text_Send(playerid, $GAMETEXT_INFO_DOOR_CLOSED);
			}
		}
		case INV_BUTTON_TYPE_OPEN_GPS:
		{
			HidePlayerInvetory(playerid);
			if(pCurrentZone[playerid] == INVALID_ZONE_ID && pRadarArea[playerid] == 0) Text_Send(playerid, $MESSAGE_ERROR_NO_SIGNAL);
			else ShowPlayerGps(playerid);
		}
		case INV_BUTTON_TYPE_OPEN_PHONE:
		{
			if(PI[playerid][pi_PHONE_NUMBER] != 0)
			{
				CancelSelectTextDraw(playerid);
				if(PI[playerid][pi_PHONE_ON]) ShowPlayerPhone(playerid);
				else ShowPlayerPhone(playerid, PHONE_PAGE_OFF);
			}
		}
		case INV_BUTTON_TURN_PHONE_ON:
		{
			PI[playerid][pi_PHONE_ON] = true;
			pInvButtonAction[playerid][button_slot] = INV_BUTTON_TYPE_OPEN_PHONE;
			FormatPlayerInvButtons(playerid, PTD_INV_BUTTONS[playerid], pInvButtonAction[playerid]);
		}
	}
	return 1;
}

GivePlayerInvItem(playerid, index, to_playerid, amount = 1)
{
	if(Iter_Contains(PINV[playerid], index))
	{
		if(!(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[ PINV[playerid][index][pinv_ITEM_ID] ][inv_item_TYPE]][inv_item_type_UNIQUE] && PlayerInvContainsItemType(to_playerid, INV_ITEMS_Info[ PINV[playerid][index][pinv_ITEM_ID] ][inv_item_TYPE])))
		{
			if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[ PINV[playerid][index][pinv_ITEM_ID] ][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
			{
				if(amount < 1 || amount > PINV[playerid][index][pinv_AMOUNT])
				return 0;

				//multiplicable
				new current_index = GetPlayerInvIndexByItem(to_playerid, PINV[playerid][index][pinv_ITEM_ID], PINV[playerid][index][pinv_PARAMS]);
				if(current_index == -1)
				{
					//to_playerid no tiene ninguno
					new newitem_index = GetPlayerInvFreeItemSlot(to_playerid);
					if(newitem_index != cellmin)
					{
						if(PINV[playerid][index][pinv_AMOUNT] == 1)
						{
							amount = 1;
							//a playerid solo le queda 1
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET amount = %d, position = %d, player_id = %d WHERE id = %d;", amount, newitem_index, PI[to_playerid][pi_ID], PINV[playerid][index][pinv_ID]);
							mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

							PINV[to_playerid][newitem_index][pinv_ID] = PINV[playerid][index][pinv_ID];
							PINV[to_playerid][newitem_index][pinv_ITEM_ID] = PINV[playerid][index][pinv_ITEM_ID];
							PINV[to_playerid][newitem_index][pinv_AMOUNT] = amount;
							format(PINV[to_playerid][newitem_index][pinv_PARAMS], 128, "%s", PINV[playerid][index][pinv_PARAMS]);
							Iter_Add(PINV[to_playerid], newitem_index);

							new tmp_PINV[enum_PINV];
							PINV[playerid][index] = tmp_PINV;
							Iter_Remove(PINV[playerid], index);
						}
						else
						{
							//a playerid le queda 2 o mas
							//to_playerid
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_inv (player_id, item_id, amount, params, position) VALUES ('%d', '%d', %d, '%e', %d);", PI[to_playerid][pi_ID], PINV[playerid][index][pinv_ITEM_ID], amount, PINV[playerid][index][pinv_PARAMS], newitem_index);
							mysql_tquery(vcrp_db, QUERY_BUFFER, "DB_OnPlayerInvItemAdded", "dddsd", to_playerid, newitem_index, PINV[playerid][index][pinv_ITEM_ID], PINV[playerid][index][pinv_PARAMS], amount);

							//playerid
							PINV[playerid][index][pinv_AMOUNT] -= amount;
							if(PINV[playerid][index][pinv_AMOUNT] <= 0)
							{
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_inv WHERE id = %d;", PINV[playerid][index][pinv_ID]);
								mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

								new tmp_PINV[enum_PINV];
								PINV[playerid][index] = tmp_PINV;
								Iter_Remove(PINV[playerid], index);
							}
							else
							{
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET amount = %d WHERE id = %d;", PINV[playerid][index][pinv_AMOUNT], PINV[playerid][index][pinv_ID]);
								mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
							}
						}
						return 1;
					}
				}
				else
				{
					new total_amount = amount + PINV[to_playerid][current_index][pinv_AMOUNT];
					if(total_amount > INV_ITEMS_TYPES_Info[INV_ITEMS_Info[ PINV[playerid][index][pinv_ITEM_ID] ][inv_item_TYPE]][inv_item_type_MAX_MULTIPLIED])
					return 0;

					//to_playerid tiene 1 o mas
					if(PINV[playerid][index][pinv_AMOUNT] == 1)
					{
						//a playerid solo le queda 1
						//to_playerid
						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET amount = %d WHERE id = '%d';", total_amount, PINV[to_playerid][current_index][pinv_ID]);
						mysql_tquery(vcrp_db, QUERY_BUFFER, "DB_OnPlayerInvItemAdded", "dddsd", to_playerid, current_index, PINV[to_playerid][current_index][pinv_ITEM_ID], PINV[to_playerid][current_index][pinv_PARAMS], amount);

						//playerid
						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_inv WHERE id = %d;", PINV[playerid][index][pinv_ID]);
						mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

						new tmp_PINV[enum_PINV];
						PINV[playerid][index] = tmp_PINV;
						Iter_Remove(PINV[playerid], index);
					}
					else
					{
						//a playerid solo le queda 2 o mas
						//to_playerid
						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET amount = %d WHERE id = '%d';", total_amount, PINV[to_playerid][current_index][pinv_ID]);
						mysql_tquery(vcrp_db, QUERY_BUFFER, "DB_OnPlayerInvItemAdded", "dddsd", to_playerid, current_index, PINV[to_playerid][current_index][pinv_ITEM_ID], PINV[to_playerid][current_index][pinv_PARAMS], amount);

						//playerid
						PINV[playerid][index][pinv_AMOUNT] -= amount;
						if(PINV[playerid][index][pinv_AMOUNT] <= 0)
						{
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_inv WHERE id = %d;", PINV[playerid][index][pinv_ID]);
							mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

							new tmp_PINV[enum_PINV];
							PINV[playerid][index] = tmp_PINV;
							Iter_Remove(PINV[playerid], index);
						}
						else
						{
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET amount = %d WHERE id = %d;", PINV[playerid][index][pinv_AMOUNT], PINV[playerid][index][pinv_ID]);
							mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
						}

					}
					return 1;
				}
			}
			else
			{
				amount = 1;
				new newitem_index = GetPlayerInvFreeItemSlot(to_playerid);
				if(newitem_index != cellmin)
				{
					new original_params[128], params[128];
					format(original_params, sizeof original_params, "%s", PINV[playerid][index][pinv_PARAMS]);
					format(params, sizeof params, "%s", original_params);

					switch(INV_ITEMS_Info[ PINV[playerid][index][pinv_ITEM_ID] ][inv_item_TYPE])
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

					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET position = %d, player_id = %d, params = '%e' WHERE id = %d;", newitem_index, PI[to_playerid][pi_ID], params, PINV[playerid][index][pinv_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");

					PINV[to_playerid][newitem_index][pinv_ID] = PINV[playerid][index][pinv_ID];
					PINV[to_playerid][newitem_index][pinv_ITEM_ID] = PINV[playerid][index][pinv_ITEM_ID];
					PINV[to_playerid][newitem_index][pinv_AMOUNT] = 1;
					format(PINV[to_playerid][newitem_index][pinv_PARAMS], 128, "%s", params);
					Iter_Add(PINV[to_playerid], newitem_index);

					new tmp_PINV[enum_PINV];
					PINV[playerid][index] = tmp_PINV;
					Iter_Remove(PINV[playerid], index);

					//callbacks
					CallRemoteFunction("OnPlayerItemDeleted", "idddsbd", playerid, index, PINV[to_playerid][newitem_index][pinv_ID], PINV[to_playerid][newitem_index][pinv_ITEM_ID], original_params, false, amount);
					CallRemoteFunction("OnPlayerItemAdded", "iddd", to_playerid, newitem_index, PINV[to_playerid][newitem_index][pinv_ITEM_ID], amount);
					return 1;
				}
			}
		}
	}
	return 0;
}

MoveInventoryItem(playerid, index, to_index)
{
	if(index == to_index || (index >= 0 && index < PLAYER_INV_MAX_SLOTS) && (to_index >= 0 && to_index < PLAYER_INV_MAX_SLOTS))
	{
		if(Iter_Contains(PINV[playerid], index))
		{
			if(Iter_Contains(PINV[playerid], to_index))
			{
				new tmp_PINV[enum_PINV];
				tmp_PINV = PINV[playerid][to_index];
				PINV[playerid][to_index] = PINV[playerid][index];
				PINV[playerid][index] = tmp_PINV;
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET position = %d WHERE id = %d;", to_index, PINV[playerid][to_index][pinv_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET position = %d WHERE id = %d;", index, PINV[playerid][index][pinv_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
			}
			else
			{
				new tmp_PINV[enum_PINV];
				PINV[playerid][to_index] = PINV[playerid][index];
				PINV[playerid][index] = tmp_PINV;
				Iter_Remove(PINV[playerid], index);
				Iter_Add(PINV[playerid], to_index);

				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET position = %d WHERE id = %d;", to_index, PINV[playerid][to_index][pinv_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
			}
			return 1;
		}
	}
	return 0;
}

FormatPlayerInventoryTextdraws(playerid, PlayerText:td1)
{
	PlayerTD_Text(playerid, td1, $TEXTDRAW_TITLE);
	return 1;
}

FormatPlayerInvMsgTextdraw(playerid, PlayerText:td, item_id, inv_params[] = "")
{
	if(item_id == -1) { PlayerTD_Text(playerid, td, $TEXTDRAW_INV_FREE_SLOT); }
	else
	{
		new td_str[64];
		format(td_str, sizeof td_str, "%s", GetItemName(playerid, item_id, inv_params));
		td_str[0] = toupper(td_str[0]);
		PlayerTextDrawSetString(playerid, td, td_str);
	}
	return 1;
}

FormatPlayerInvButtons(playerid, PlayerText:td_buttons[], INV_BUTTONS_TYPES:button_var_action[])
{
	for(new i = 0; i != MAX_INV_BUTTONS; i ++)
	{
		if(button_var_action[i] == INV_BUTTON_TYPE_NONE) continue;
		switch(button_var_action[i])
		{
			case INV_BUTTON_TYPE_GIVE: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_GIVE); }
			case INV_BUTTON_TYPE_MOVE: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_MOVE); }
			case INV_BUTTON_TYPE_DELETE: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_DELETE); }
			case INV_BUTTON_TYPE_VEHICLE_OPEN: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_VEHICLE_OPEN); }
			case INV_BUTTON_TYPE_PDOOR_OPEN: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_PDOOR_OPEN); }
			case INV_BUTTON_TYPE_BDOOR_OPEN: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_BDOOR_OPEN); }
			case INV_BUTTON_TYPE_VEHICLE_CLOSE: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_VEHICLE_CLOSE); }
			case INV_BUTTON_TYPE_PDOOR_CLOSE: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_PDOOR_CLOSE); }
			case INV_BUTTON_TYPE_BDOOR_CLOSE: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_BDOOR_CLOSE); }
			case INV_BUTTON_TYPE_VEHICLE_START: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_VEHICLE_START); }
			case INV_BUTTON_TYPE_VEHICLE_STOP: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_VEHICLE_STOP); }
			case INV_BUTTON_TYPE_SHOW: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_SHOW); }
			case INV_BUTTON_TURN_PHONE_ON: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TURN_PHONE_ON); }
			case INV_BUTTON_TOY_ATTACH: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TOY_ATTACH); }
			case INV_BUTTON_TOY_REMOVE: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TOY_REMOVE); }
			case INV_BUTTON_CONFIG_TOY: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_CONFIG_TOY); }
			case INV_BUTTON_WEAPON_CARRY_YES: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_WEAPON_CARRY_YES); }
			case INV_BUTTON_WEAPON_CARRY_NO: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_WEAPON_CARRY_NO); }
			case INV_BUTTON_TYPE_OPEN_GPS: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_OPEN_GPS); }
			case INV_BUTTON_TYPE_OPEN_PHONE: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_OPEN_PHONE); }
			case INV_BUTTON_FOOD_EAT: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_FOOD_EAT); }
			case INV_BUTTON_DRINK_DRINK: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_DRINK_DRINK); }
			case INV_BUTTON_TYPE_SMOKE: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_TYPE_SMOKE); }
			case INV_BUTTON_WATCH_TIME: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_WATCH_TIME); }
			case INV_BUTTON_USE_BOOMBOX: { PlayerTD_Text(playerid, td_buttons[i], $INV_BUTTON_USE_BOOMBOX); }
		}
	}
	return 1;
}

GetItemName(playerid, item_id, params[] = "")
{
	new item[64];
	switch(item_id)
	{
		case INV_ITEM_BANDANA: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_BANDANA);
		case INV_ITEM_BEER: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_BEER);
		case INV_ITEM_CAP: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_CAP);
		case INV_ITEM_CIGARETTE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_CIGARETTE);
		case INV_ITEM_GLASSES: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_GLASSES);
		case INV_ITEM_HELMET: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_HELMET);
		case INV_ITEM_HOTDOG: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_HOTDOG);
		case INV_ITEM_PROPERTY_KEY:
		{
			new id;
			sscanf(params, "d", id);
			Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_PROPERTY_KEY, id);
		}
		case INV_ITEM_PROPERTY_MASTER_KEY:
		{
			new id;
			sscanf(params, "d", id);
			Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_PROPERTY_MASTER_KEY, id);
		}
		case INV_ITEM_PROPERTY_RENT_KEY:
		{
			new id;
			sscanf(params, "d", id);
			Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_PROPERTY_RENT_KEY, id);
		}
		case INV_ITEM_MASK: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_MASK);
		case INV_ITEM_PHONE:
		{
			if(isnull(params)) Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_PHONE_NULL);
			else Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_PHONE, params);
		}
		case INV_ITEM_PIZZA: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_PIZZA);
		case INV_ITEM_SMASK: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_SMASK);
		case INV_ITEM_SKI_MASK: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_SKI_MASK);
		case INV_ITEM_SODA: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_SODA);
		case INV_ITEM_WATCH: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_WATCH);
		case INV_ITEM_WATER: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_WATER);
		case INV_ITEM_WHISKY: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_WHISKY);
		case INV_ITEM_HAMBURGER: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_HAMBURGER);
		case INV_ITEM_HAT: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_HAT);
		case INV_ITEM_BRASS_KNUCKLES: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_BRASS_KNUCKLES);
		case INV_ITEM_GOLF_CLUB: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_GOLF_CLUB);
		case INV_ITEM_NIGHTSTICK: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_NIGHTSTICK);
		case INV_ITEM_KNIFE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_KNIFE);
		case INV_ITEM_BASEBALL_BAT: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_BASEBALL_BAT);
		case INV_ITEM_SHOVEL: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_SHOVEL);
		case INV_ITEM_POOL_CUE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_POOL_CUE);
		case INV_ITEM_KATANA: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_KATANA);
		case INV_ITEM_CHAINSAW: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_CHAINSAW);
		case INV_ITEM_PURPLE_DILDO: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_PURPLE_DILDO);
		case INV_ITEM_DILDO: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_DILDO);
		case INV_ITEM_VIBRATOR: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_VIBRATOR);
		case INV_ITEM_SILVER_VIBRATOR: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_SILVER_VIBRATOR);
		case INV_ITEM_FLOWERS: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_FLOWERS);
		case INV_ITEM_CANE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_CANE);
		case INV_ITEM_GRENADE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_GRENADE);
		case INV_ITEM_TEAR_GAS: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_TEAR_GAS);
		case INV_ITEM_MOLOTOV_COCKTAIL: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_MOLOTOV_COCKTAIL);
		case INV_ITEM_COLT45: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_45COLT);
		case INV_ITEM_SILENCED_COLT45: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_SILENCED_45COLT);
		case INV_ITEM_DESERT_EAGLE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_DESERT_EAGLE);
		case INV_ITEM_SHOTGUN: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_SHOTGUN);
		case INV_ITEM_SAWNOFF_SHOTGUN: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_SAWNOFF_SHOTGUN);
		case INV_ITEM_COMBAT_SHOTGUN: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_COMBAT_SHOTGUN);
		case INV_ITEM_UZI: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_UZI);
		case INV_ITEM_MP5: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_MP5);
		case INV_ITEM_AK_47: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_AK_47);
		case INV_ITEM_M4: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_M4);
		case INV_ITEM_TEC_9: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_TEC_9);
		case INV_ITEM_COUNTRY_RIFLE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_COUNTRY_RIFLE);
		case INV_ITEM_SNIPER_RIFLE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_SNIPER_RIFLE);
		case INV_ITEM_RPG: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_RPG);
		case INV_ITEM_HS_ROCKET: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_HS_ROCKET);
		case INV_ITEM_FLAMETHROWER: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_FLAMETHROWER);
		case INV_ITEM_MINIGUN: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_MINIGUN);
		case INV_ITEM_SATCHEL_CHARGE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_SATCHEL_CHARGE);
		case INV_ITEM_DETONATOR: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_DETONATOR);
		case INV_ITEM_SPRAYCAN: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_SPRAYCAN);
		case INV_ITEM_FIRE_EXTINGUISHER: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_FIRE_EXTINGUISHER);
		case INV_ITEM_CAMERA: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_CAMERA);
		case INV_ITEM_PARACHUTE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_PARACHUTE);
		case INV_ITEM_VEHICLE_KEY:
		{
			new vid, modelid;
			sscanf(params, "p<,>dd", vid, modelid);
			Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_VEHICLE_KEY, GetVehicleNameByModelid(modelid), vid);
		}
		case INV_ITEM_VEHICLE_MASTER_KEY:
		{
			new vid, modelid;
			sscanf(params, "p<,>dd", vid, modelid);
			Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_VEHICLE_MASTER_KEY, GetVehicleNameByModelid(modelid), vid);
		}
		case INV_ITEM_VEHICLE_RENT_KEY:
		{
			new vid, modelid;
			sscanf(params, "p<,>dd", vid, modelid);
			Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_VEHICLE_RENT_KEY, GetVehicleNameByModelid(modelid), vid);
		}
		case INV_ITEM_BUSINESS_KEY:
		{
			new id;
			sscanf(params, "d", id);
			format(item, sizeof item, "business key (%d)", id);
			Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_BUSINESS_KEY, id);
		}
		case INV_ITEM_BUSINESS_MASTER_KEY:
		{
			new id;
			sscanf(params, "d", id);
			format(item, sizeof item, "business key (%d)", id);
			Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_BUSINESS_MASTER_KEY, id);
		}
		case INV_ITEM_DRIVER_LICENSE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_DRIVER_LICENSE);
		case INV_ITEM_CHARACTER_ID: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_CHARACTER_ID);
		case INV_ITEM_GPS: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_GPS);
		case INV_ITEM_GUN_LICENSE: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_GUN_LICENSE);
		case INV_ITEM_BOOMBOX: Text_Format_Dialog(item, sizeof item, PI[playerid][pi_LANG_ID], $INV_ITEM_BOOMBOX);
	}
	return item;
}