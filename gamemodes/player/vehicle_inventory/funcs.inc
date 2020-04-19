loadtext lang[vinv];

ShowVehicleInventoryForPlayer(vehindex, playerid, areaid)
{
	pVInv[playerid] = true;
	pVInvMoving[playerid] = false;
	pVInvSelected[playerid] = -1;
	pVInvVehIndex[playerid] = vehindex;
	pVInvArea[playerid] = areaid;

	CreatePlayerVInvetoryTextdraws(playerid);
	PlayerTD_Text(playerid, pVInvTd_BASE[playerid][2], $TEXTDRAW_TITLE);
	PlayerTD_Text(playerid, pVInvTd_BASE[playerid][3], $TEXTDRAW_ADD_BUTTON);
	UpdateVInventoryTdsForPlayer(vehindex, playerid);
	DisablePlayerLayers(playerid, LAYER_INVENTORY, true, LAYER_RADAR);
	ShowPlayerVInventoryTextdraws(playerid);
	SelectTextDraw(playerid, 0xFFFFFFFF);

	CallRemoteFunction("OnPlayerOpenVehicleInventory", "id", playerid, vehindex);
	return 1;
}

CreatePlayerVInvetoryTextdraws(playerid)
{
	//calc
	new Float:result_x,
		Float:real_INVENTORY_ITEM_SIZE_X,
		Float:real_INVENTORY_PADDING
	;
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, INVENTORY_ITEM_SIZE_X, false, result_x, real_INVENTORY_ITEM_SIZE_X);
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, VINV_TD_PADDING, false, result_x, real_INVENTORY_PADDING);

	//base calc
	new Float:current_y,
		Float:base_x,
		Float:base_y,
		Float:base_size_x = real_INVENTORY_PADDING,
		Float:base_size_y = (real_INVENTORY_PADDING + VINV_TD_TEXT_OFFSET_Y + real_INVENTORY_PADDING) + (real_INVENTORY_PADDING + VINV_TD_TEXT2_OFFSET_Y + real_INVENTORY_PADDING) + ((MAX_VEHICLE_INVENTORY_SLOTS / VINV_TD_ITEMS_PER_ROW) * (INVENTORY_ITEM_SIZE_Y + real_INVENTORY_PADDING));


	//+ boton añadir
	base_size_y += VINV_TD_TEXT2_OFFSET_Y + real_INVENTORY_PADDING;

	for(new i = 0; i < VINV_TD_ITEMS_PER_ROW; i ++)
	{
		base_size_x += real_INVENTORY_ITEM_SIZE_X + real_INVENTORY_PADDING;
	}
	base_x = 320.0 - (base_size_x / 2.0);
	base_y = 224.0 - (base_size_y / 2.0);
	current_y = base_y;

	//base tds
	pVInvTd_BASE[playerid][0] = CreatePlayerTextDraw(playerid, base_x, base_y, "LD_SPAC:white");
	PlayerTextDrawColor(playerid, pVInvTd_BASE[playerid][0], 909588720);
	PlayerTextDrawFont(playerid, pVInvTd_BASE[playerid][0], 4);
	PlayerTextDrawTextSize(playerid, pVInvTd_BASE[playerid][0], base_size_x, base_size_y);
	SetPlayerTextDrawLayer(playerid, pVInvTd_BASE[playerid][0], LAYER_INVENTORY);

	pVInvTd_BASE[playerid][1] = CreatePlayerTextDraw(playerid, base_x, base_y + (real_INVENTORY_PADDING + VINV_TD_TEXT_OFFSET_Y + real_INVENTORY_PADDING), "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, pVInvTd_BASE[playerid][1], base_size_x, base_size_y - (real_INVENTORY_PADDING + VINV_TD_TEXT_OFFSET_Y + real_INVENTORY_PADDING));
	PlayerTextDrawColor(playerid, pVInvTd_BASE[playerid][1], 690563839);
	PlayerTextDrawFont(playerid, pVInvTd_BASE[playerid][1], 4);
	SetPlayerTextDrawLayer(playerid, pVInvTd_BASE[playerid][1], LAYER_INVENTORY);

	current_y += real_INVENTORY_PADDING;
	pVInvTd_BASE[playerid][2] = CreatePlayerTextDraw(playerid, 320.0, current_y, "TEXT");
	PlayerTextDrawLetterSize(playerid, pVInvTd_BASE[playerid][2], 0.262665, VINV_TD_TEXT_OFFSET_Y / 10.0);
	PlayerTextDrawTextSize(playerid, pVInvTd_BASE[playerid][2], 0.000000, base_size_x);
	PlayerTextDrawAlignment(playerid, pVInvTd_BASE[playerid][2], 2);
	PlayerTextDrawColor(playerid, pVInvTd_BASE[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, pVInvTd_BASE[playerid][2], 0);
	PlayerTextDrawFont(playerid, pVInvTd_BASE[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, pVInvTd_BASE[playerid][2], 1);
	SetPlayerTextDrawLayer(playerid, pVInvTd_BASE[playerid][2], LAYER_INVENTORY);
	current_y += VINV_TD_TEXT_OFFSET_Y + real_INVENTORY_PADDING;

	//items tds
	new items_x, row,
		Float:item_x = base_x + real_INVENTORY_PADDING,
		Float:item_y = base_y + (real_INVENTORY_PADDING + VINV_TD_TEXT_OFFSET_Y + real_INVENTORY_PADDING) + (real_INVENTORY_PADDING + VINV_TD_TEXT2_OFFSET_Y + real_INVENTORY_PADDING);

	new mid_column = floatround(floatdiv(VINV_TD_ITEMS_PER_ROW, 2), floatround_ceil),
		mid_row = floatround(floatdiv(floatdiv(MAX_VEHICLE_INVENTORY_SLOTS, VINV_TD_ITEMS_PER_ROW), 2), floatround_ceil);

	for(new i = 0; i < MAX_VEHICLE_INVENTORY_SLOTS; i ++)
	{
		pVInvTd_ITEMS_BOX[playerid][i] = CreatePlayerTextDraw(playerid, item_x, item_y, ""TEXTDRAW_CUSTOM_PATH"inv_box_null");
		PlayerTextDrawTextSize(playerid, pVInvTd_ITEMS_BOX[playerid][i], real_INVENTORY_ITEM_SIZE_X, INVENTORY_ITEM_SIZE_Y);
		PlayerTextDrawSetSelectable(playerid, pVInvTd_ITEMS_BOX[playerid][i], true);
		PlayerTextDrawFont(playerid, pVInvTd_ITEMS_BOX[playerid][i], 4);
		SetPlayerTextDrawLayer(playerid, pVInvTd_ITEMS_BOX[playerid][i], LAYER_INVENTORY);

		pVInvTd_ITEMS[playerid][i] = CreatePlayerTextDraw(playerid, item_x, item_y, ""TEXTDRAW_CUSTOM_PATH"icon_undefinied");
		PlayerTextDrawTextSize(playerid, pVInvTd_ITEMS[playerid][i], real_INVENTORY_ITEM_SIZE_X, INVENTORY_ITEM_SIZE_Y);
		PlayerTextDrawFont(playerid, pVInvTd_ITEMS[playerid][i], 4);
		SetPlayerTextDrawLayer(playerid, pVInvTd_ITEMS[playerid][i], LAYER_INVENTORY);

		pVInvTd_ITEMS_AMOUNT[playerid][i] = CreatePlayerTextDraw(playerid, item_x + (real_INVENTORY_ITEM_SIZE_X - real_INVENTORY_PADDING), item_y + (INVENTORY_ITEM_SIZE_Y - real_INVENTORY_PADDING - 6.45925), "0");
		PlayerTextDrawLetterSize(playerid, pVInvTd_ITEMS_AMOUNT[playerid][i], 0.130331, 0.645925);
		PlayerTextDrawAlignment(playerid, pVInvTd_ITEMS_AMOUNT[playerid][i], 3);
		PlayerTextDrawSetShadow(playerid, pVInvTd_ITEMS_AMOUNT[playerid][i], 0);
		PlayerTextDrawFont(playerid, pVInvTd_ITEMS_AMOUNT[playerid][i], 1);
		PlayerTextDrawSetProportional(playerid, pVInvTd_ITEMS_AMOUNT[playerid][i], 1);
		SetPlayerTextDrawLayer(playerid, pVInvTd_ITEMS_AMOUNT[playerid][i], LAYER_INVENTORY);


		//positions info
		pVInvTextDrawPosition[playerid][i][0] = item_x;
		pVInvTextDrawPosition[playerid][i][1] = item_y;

		if(items_x + 1 >= mid_column) pVInvTextDrawInverted[playerid][i][0] = true;
		else pVInvTextDrawInverted[playerid][i][0] = false;

		if(row >= mid_row) pVInvTextDrawInverted[playerid][i][1] = true;
		else pVInvTextDrawInverted[playerid][i][1] = false;


		//check
		item_x += real_INVENTORY_PADDING + real_INVENTORY_ITEM_SIZE_X;
		items_x ++;
		if(items_x == VINV_TD_ITEMS_PER_ROW)
		{
			items_x = 0;
			row ++;
			item_x = base_x + real_INVENTORY_PADDING;
			item_y += INVENTORY_ITEM_SIZE_Y + real_INVENTORY_PADDING;
		}
	}

	//msg
	pVInvTd_INFO_MESSAGE[playerid] = CreatePlayerTextDraw(playerid, 320.0, base_y + (real_INVENTORY_PADDING + VINV_TD_TEXT_OFFSET_Y + real_INVENTORY_PADDING + real_INVENTORY_PADDING), "_"); //msg info
	PlayerTextDrawLetterSize(playerid, pVInvTd_INFO_MESSAGE[playerid], 0.196999, VINV_TD_TEXT2_OFFSET_Y / 10.0);
	PlayerTextDrawTextSize(playerid, pVInvTd_INFO_MESSAGE[playerid], 0.000000, base_size_x);
	PlayerTextDrawAlignment(playerid, pVInvTd_INFO_MESSAGE[playerid], 2);
	PlayerTextDrawColor(playerid, pVInvTd_INFO_MESSAGE[playerid], -1);
	PlayerTextDrawSetShadow(playerid, pVInvTd_INFO_MESSAGE[playerid], 0);
	PlayerTextDrawFont(playerid, pVInvTd_INFO_MESSAGE[playerid], 1);
	PlayerTextDrawSetProportional(playerid, pVInvTd_INFO_MESSAGE[playerid], 1);
	SetPlayerTextDrawLayer(playerid, pVInvTd_INFO_MESSAGE[playerid], LAYER_INVENTORY);

	//+Add
	pVInvTd_BASE[playerid][3] = CreatePlayerTextDraw(playerid, (320.0 + (base_size_x / 2.0)) - (real_INVENTORY_PADDING * 2.0), item_y, "+ Add");
	PlayerTextDrawLetterSize(playerid, pVInvTd_BASE[playerid][3], 0.196999, VINV_TD_TEXT2_OFFSET_Y / 10.0);
	PlayerTextDrawTextSize(playerid, pVInvTd_BASE[playerid][3], ((320.0 + (base_size_x / 2.0)) - real_INVENTORY_PADDING) + (base_size_x / 2.0), VINV_TD_TEXT2_OFFSET_Y);
	PlayerTextDrawAlignment(playerid, pVInvTd_BASE[playerid][3], 3);
	PlayerTextDrawColor(playerid, pVInvTd_BASE[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, pVInvTd_BASE[playerid][3], 0);
	PlayerTextDrawFont(playerid, pVInvTd_BASE[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, pVInvTd_BASE[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, pVInvTd_BASE[playerid][3], true);
	SetPlayerTextDrawLayer(playerid, pVInvTd_BASE[playerid][3], LAYER_INVENTORY);
	return 1;
}

ShowPlayerVInventoryTextdraws(playerid)
{
	PlayerTextDrawShow(playerid, pVInvTd_BASE[playerid][0]);
	PlayerTextDrawShow(playerid, pVInvTd_BASE[playerid][1]);
	PlayerTextDrawShow(playerid, pVInvTd_BASE[playerid][2]);
	PlayerTextDrawShow(playerid, pVInvTd_BASE[playerid][3]);
	for(new i = 0; i < MAX_VEHICLE_INVENTORY_SLOTS; i ++)
	{
		PlayerTextDrawShow(playerid, pVInvTd_ITEMS_BOX[playerid][i]);
	}
	PlayerTextDrawShow(playerid, pVInvTd_INFO_MESSAGE[playerid]);
	return 1;
}

DestroyPlayerVInventory(playerid)
{
	new vehindex = pVInvVehIndex[playerid];
	pVInv[playerid] = false;
	pVInvMoving[playerid] = false;
	pVInvSelected[playerid] = -1;
	pVInvVehIndex[playerid] = INVALID_VEHICLE_INDEX;
	pVInvArea[playerid] = INVALID_STREAMER_ID;
	if(pVInvTd_BASE[playerid][0] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, pVInvTd_BASE[playerid][0]);
		pVInvTd_BASE[playerid][0] = PlayerText:INVALID_TEXT_DRAW;
	}	
	if(pVInvTd_BASE[playerid][1] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, pVInvTd_BASE[playerid][1]);
		pVInvTd_BASE[playerid][1] = PlayerText:INVALID_TEXT_DRAW;
	}
	if(pVInvTd_BASE[playerid][2] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, pVInvTd_BASE[playerid][2]);
		pVInvTd_BASE[playerid][2] = PlayerText:INVALID_TEXT_DRAW;
	}
	if(pVInvTd_BASE[playerid][3] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, pVInvTd_BASE[playerid][3]);
		pVInvTd_BASE[playerid][3] = PlayerText:INVALID_TEXT_DRAW;
	}

	for(new i = 0; i != MAX_VEHICLE_INVENTORY_SLOTS; i ++)
	{
		if(pVInvTd_ITEMS_BOX[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pVInvTd_ITEMS_BOX[playerid][i]);
			pVInvTd_ITEMS_BOX[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		if(pVInvTd_ITEMS[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pVInvTd_ITEMS[playerid][i]);
			pVInvTd_ITEMS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
		if(pVInvTd_ITEMS_AMOUNT[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pVInvTd_ITEMS_AMOUNT[playerid][i]);
			pVInvTd_ITEMS_AMOUNT[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}

	if(pVInvTd_INFO_MESSAGE[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, pVInvTd_INFO_MESSAGE[playerid]);
		pVInvTd_INFO_MESSAGE[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
	DestroyPlayerVInvButtons(playerid);
	EnablePlayerLayers(playerid);
	CallRemoteFunction("OnPlayerCloseVehicleInventory", "id", playerid, vehindex);
	return 1;
}

DestroyPlayerVInvButtons(playerid)
{
	if(pVInvTd_BUTTONS_BOX[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, pVInvTd_BUTTONS_BOX[playerid]);
		pVInvTd_BUTTONS_BOX[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}

	for(new i = 0; i != MAX_INV_BUTTONS; i ++)
	{
		if(pVInvTd_BUTTONS[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pVInvTd_BUTTONS[playerid][i]);
			pVInvTd_BUTTONS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}

UpdateVInventoryTdsForPlayer(vehindex, playerid)
{
	PlayerTextDrawSetString(playerid, pVInvTd_INFO_MESSAGE[playerid], "_");

	for(new i = 0; i != MAX_VEHICLE_INVENTORY_SLOTS; i ++)
	{
		if(Iter_Contains(VehicleInventory[vehindex], i)) PlayerTextDrawSetString(playerid, pVInvTd_ITEMS_BOX[playerid][i], ""TEXTDRAW_CUSTOM_PATH"inv_box_item");
		else PlayerTextDrawSetString(playerid, pVInvTd_ITEMS_BOX[playerid][i], ""TEXTDRAW_CUSTOM_PATH"inv_box_null");

		PlayerTextDrawSetString(playerid, pVInvTd_ITEMS[playerid][i], ""TEXTDRAW_CUSTOM_PATH"icon_undefinied");
		PlayerTextDrawHide(playerid, pVInvTd_ITEMS[playerid][i]);

		PlayerTextDrawSetString(playerid, pVInvTd_ITEMS_AMOUNT[playerid][i], "0");
		PlayerTextDrawHide(playerid, pVInvTd_ITEMS_AMOUNT[playerid][i]);
	}

	if(pVInvSelected[playerid] != -1)
	{
		PlayerTextDrawSetString(playerid, pVInvTd_ITEMS_BOX[playerid][pVInvSelected[playerid]], ""TEXTDRAW_CUSTOM_PATH"inv_box_selected");

		if(Iter_Contains(VehicleInventory[vehindex], pVInvSelected[playerid]))
		{
			FormatVInvMsgTextdraw(playerid, pVInvTd_INFO_MESSAGE[playerid], VehicleInventory[vehindex][ pVInvSelected[playerid] ][vinv_ITEM_ID], VehicleInventory[vehindex][ pVInvSelected[playerid] ][vinv_PARAMS]);

			CreateVInvButtons(playerid);
			FormatPlayerVInvButtons(playerid, pVInvTd_BUTTONS[playerid]);
		}
		else
		{
			FormatVInvMsgTextdraw(playerid, pVInvTd_INFO_MESSAGE[playerid], -1);
			DestroyPlayerVInvButtons(playerid);
		}
	}
	else DestroyPlayerVInvButtons(playerid);

	foreach(new i : VehicleInventory[vehindex])
	{
		new string[128];
		format(string, sizeof string, ""TEXTDRAW_CUSTOM_PATH"%s", INV_ITEMS_Info[ VehicleInventory[vehindex][i][vinv_ITEM_ID] ][inv_item_ICON_NAME]);
		PlayerTextDrawSetString(playerid, pVInvTd_ITEMS[playerid][i], string);
		PlayerTextDrawShow(playerid, pVInvTd_ITEMS[playerid][i]);

		if(pVInvSelected[playerid] == -1 || i == pVInvSelected[playerid] || !Iter_Contains(VehicleInventory[vehindex], pVInvSelected[playerid])) //para que no se sobrepongan los numeros a los botones
		{
			if(INV_ITEMS_TYPES_Info[ INV_ITEMS_Info[ VehicleInventory[vehindex][i][vinv_ITEM_ID] ][inv_item_TYPE] ][inv_item_type_MULTIPLIABLE])
			{
				format(string, sizeof string, "%d", VehicleInventory[vehindex][i][vinv_AMOUNT]);
				PlayerTextDrawSetString(playerid, pVInvTd_ITEMS_AMOUNT[playerid][i], string);
				PlayerTextDrawShow(playerid, pVInvTd_ITEMS_AMOUNT[playerid][i]);			
			}
		}
	}
	return 1;
}

FormatVInvMsgTextdraw(playerid, PlayerText:td, item_id, inv_params[] = "")
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

CreateVInvButtons(playerid)
{
	if(pVInvSelected[playerid] != -1)
	{
		DestroyPlayerVInvButtons(playerid);

		new Float:pos_x = pVInvTextDrawPosition[playerid][ pVInvSelected[playerid] ][0],
			Float:pos_y = pVInvTextDrawPosition[playerid][ pVInvSelected[playerid] ][1];

		new Float:result_x,
			Float:real_INV_BUTTONS_BOX_SIZE_X,
			Float:real_INVENTORY_PADDING,
			Float:real_INVENTORY_ITEM_SIZE_X,
			Float:box_size_y;

		AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, VINV_BUTTONS_BOX_SIZE_X, false, result_x, real_INV_BUTTONS_BOX_SIZE_X);
		AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, VINV_TD_PADDING, false, result_x, real_INVENTORY_PADDING);
		AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, INVENTORY_ITEM_SIZE_X, false, result_x, real_INVENTORY_ITEM_SIZE_X);

		box_size_y = real_INVENTORY_PADDING + (VINV_TD_TEXT2_OFFSET_Y * MAX_VINV_BUTTONS) + real_INVENTORY_PADDING;

		if(pVInvTextDrawInverted[playerid][ pVInvSelected[playerid] ][0]) pos_x -= real_INV_BUTTONS_BOX_SIZE_X;
		else pos_x += real_INVENTORY_ITEM_SIZE_X;

		if(pVInvTextDrawInverted[playerid][ pVInvSelected[playerid] ][1]) pos_y -= box_size_y;
		else pos_y += INVENTORY_ITEM_SIZE_Y;

		new Float:current_y = pos_y + real_INVENTORY_PADDING;
		for(new i = 0; i < MAX_VINV_BUTTONS; i ++)
		{
			pVInvTd_BUTTONS[playerid][i] = CreatePlayerTextDraw(playerid, pos_x + (real_INVENTORY_PADDING * 2.0), current_y, "Button", true);
			PlayerTextDrawLetterSize(playerid, pVInvTd_BUTTONS[playerid][i], 0.196999, VINV_TD_TEXT2_OFFSET_Y / 10.0);
			PlayerTextDrawTextSize(playerid, pVInvTd_BUTTONS[playerid][i], pos_x + real_INV_BUTTONS_BOX_SIZE_X, VINV_TD_TEXT2_OFFSET_Y - 0.15);
			PlayerTextDrawColor(playerid, pVInvTd_BUTTONS[playerid][i], -1);
			PlayerTextDrawSetShadow(playerid, pVInvTd_BUTTONS[playerid][i], 0);
			PlayerTextDrawFont(playerid, pVInvTd_BUTTONS[playerid][i], 1);
			PlayerTextDrawSetProportional(playerid, pVInvTd_BUTTONS[playerid][i], 1);
			PlayerTextDrawSetSelectable(playerid, pVInvTd_BUTTONS[playerid][i], true);
			SetPlayerTextDrawLayer(playerid, pVInvTd_BUTTONS[playerid][i], LAYER_INVENTORY);
			PlayerTextDrawShow(playerid, pVInvTd_BUTTONS[playerid][i]);
			current_y += VINV_TD_TEXT2_OFFSET_Y;
		}

		pVInvTd_BUTTONS_BOX[playerid] = CreatePlayerTextDraw(playerid, pos_x, pos_y, ""TEXTDRAW_CUSTOM_PATH"inv_buttons_box", true);
		PlayerTextDrawFont(playerid, pVInvTd_BUTTONS_BOX[playerid], 4);
		PlayerTextDrawSetSelectable(playerid, pVInvTd_BUTTONS_BOX[playerid], true);
		SetPlayerTextDrawLayer(playerid, pVInvTd_BUTTONS_BOX[playerid], LAYER_INVENTORY);
		PlayerTextDrawTextSize(playerid, pVInvTd_BUTTONS_BOX[playerid], real_INV_BUTTONS_BOX_SIZE_X, box_size_y);
		PlayerTextDrawShow(playerid, pVInvTd_BUTTONS_BOX[playerid]);
		return 1;
	}
	return 0;
}

FormatPlayerVInvButtons(playerid, PlayerText:td_buttons[])
{
	PlayerTD_Text(playerid, td_buttons[0], $VINV_BUTTON_TAKE);
	PlayerTD_Text(playerid, td_buttons[1], $VINV_BUTTON_MOVE);
	PlayerTD_Text(playerid, td_buttons[2], $VINV_BUTTON_DELETE);
	return 1;
}

VInvButtonAction(playerid, button)
{
	switch(button)
	{
		case VINV_BUTTON_TAKE:
		{
			if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[ VehicleInventory[ pVInvVehIndex[playerid] ][ pVInvSelected[playerid] ][vinv_ITEM_ID] ][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
			{
				inline OnPlayerAmountDialog(pid2, dialogid2, response2, listitem2, string:inputtext2[])
				{
					#pragma unused pid2, dialogid2, listitem2
					if(response2)
					{
						new amount;
						if(!sscanf(inputtext2, "d", amount))
						{
							if(amount < 1 || amount > VehicleInventory[ pVInvVehIndex[playerid] ][ pVInvSelected[playerid] ][vinv_AMOUNT]) Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
							else
							{
								if(AddPlayerInventoryItem(playerid, VehicleInventory[ pVInvVehIndex[playerid] ][ pVInvSelected[playerid] ][vinv_ITEM_ID], VehicleInventory[ pVInvVehIndex[playerid] ][ pVInvSelected[playerid] ][vinv_PARAMS], amount))
								{
									RemoveVehicleInvetoryItem(pVInvVehIndex[playerid], pVInvSelected[playerid], amount);
									CancelSelectTextDraw(playerid);
									Text_Send(playerid, $GAMETEXT_INFO_TAKEN);
								}
								else Text_Send(playerid, $MESSAGE_ERROR_INV);
							}
						}
						else Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
					}
				}
				Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnPlayerAmountDialog, $DIALOG_MOVE_ITEM_TO_INV_CAPTION, $DIALOG_MOVE_ITEM_TO_INV_BODY, $DIALOG_MOVE_ITEM_TO_INV_YES, $DIALOG_MOVE_ITEM_TO_INV_NO, VehicleInventory[ pVInvVehIndex[playerid] ][ pVInvSelected[playerid] ][vinv_AMOUNT]);
			}
			else
			{
				if(AddPlayerInventoryItem(playerid, VehicleInventory[ pVInvVehIndex[playerid] ][ pVInvSelected[playerid] ][vinv_ITEM_ID], VehicleInventory[ pVInvVehIndex[playerid] ][ pVInvSelected[playerid] ][vinv_PARAMS]))
				{
					RemoveVehicleInvetoryItem(pVInvVehIndex[playerid], pVInvSelected[playerid]);
					CancelSelectTextDraw(playerid);
					Text_Send(playerid, $GAMETEXT_INFO_TAKEN);
				}
				else Text_Send(playerid, $MESSAGE_ERROR_INV);
			}
		}
		case VINV_BUTTON_MOVE:
		{
			pVInvMoving[playerid] = true;
			pVInvMove_Index[playerid] = pVInvSelected[playerid];
			DestroyPlayerVInvButtons(playerid);
			Text_Send(playerid, $MESSAGE_INFO_MOVE);
		}
		case VINV_BUTTON_DELETE:
		{
			if(INV_ITEMS_TYPES_Info[INV_ITEMS_Info[ VehicleInventory[ pVInvVehIndex[playerid] ][ pVInvSelected[playerid] ][vinv_ITEM_ID] ][inv_item_TYPE]][inv_item_type_MULTIPLIABLE])
			{
				inline OnPlayerAmountDialog(pid2, dialogid2, response2, listitem2, string:inputtext2[])
				{
					#pragma unused pid2, dialogid2, listitem2
					if(response2)
					{
						new amount;
						if(!sscanf(inputtext2, "d", amount))
						{
							if(amount < 1 || amount > VehicleInventory[ pVInvVehIndex[playerid] ][ pVInvSelected[playerid] ][vinv_AMOUNT]) Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
							else
							{
								inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
								{
									#pragma unused pid, dialogid, listitem, inputtext
									if(response)
									{
										if(RemoveVehicleInvetoryItem(pVInvVehIndex[playerid], pVInvSelected[playerid], amount))
										{
											pVInvSelected[playerid] = -1;
											UpdateVInventoryTdsForPlayer(pVInvVehIndex[playerid], playerid);
											Text_Send(playerid, $GAMETEXT_INFO_DELETED);
										}
									}
								}
								Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_DELETE_ITEM_CAPTION, $DIALOG_DELETE_ITEM_BODY, $DIALOG_DELETE_ITEM_YES, $DIALOG_DELETE_ITEM_NO);
							}
						}
						else Text_Send(playerid, $MESSAGE_ERROR_INVALID_AMOUNT);
					}
				}
				Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnPlayerAmountDialog, $DIALOG_DELETE_ITEM_AMOUNT_CAPTION, $DIALOG_DELETE_ITEM_AMOUNT_BODY, $DIALOG_DELETE_ITEM_AMOUNT_YES, $DIALOG_DELETE_ITEM_AMOUNT_NO, VehicleInventory[ pVInvVehIndex[playerid] ][ pVInvSelected[playerid] ][vinv_AMOUNT]);
			}
			else
			{
				inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
				{
					#pragma unused pid, dialogid, listitem, inputtext
					if(response)
					{
						if(RemoveVehicleInvetoryItem(pVInvVehIndex[playerid], pVInvSelected[playerid]))
						{
							pVInvSelected[playerid] = -1;
							UpdateVInventoryTdsForPlayer(pVInvVehIndex[playerid], playerid);
							Text_Send(playerid, $GAMETEXT_INFO_DELETED);
						}
					}
				}
				Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_DELETE_ITEM_CAPTION, $DIALOG_DELETE_ITEM_BODY, $DIALOG_DELETE_ITEM_YES, $DIALOG_DELETE_ITEM_NO);
			}
		}
	}
	return 1;
}

UpdateVInventoryInvTd(playerid)
{
	if(pInvetory[playerid])
	{
		PlayerTD_Text(playerid, pVInvTd_BASE[playerid][3], $TEXTDRAW_CLOSE_INV);
	}
	else
	{
		PlayerTD_Text(playerid, pVInvTd_BASE[playerid][3], $TEXTDRAW_ADD_BUTTON);
	}
	return 1;
}