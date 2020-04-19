loadtext lang[business];

CountPlayerBusiness(playerid)
{
	new c;
	foreach(new i : PlayerBusiness<playerid>)
	{
		c ++;
	}
	return c;
}

GetPlayerDialogBusinessInfo(playerid, index_business, type, dialog[], dialog_size = sizeof dialog)
{
	dialog[0] = EOS;
	//dialog pagination
	pDialogPagination_FirstIndex[playerid] = -1;
	if(pDialogPagination_LastIndex[playerid] == -1)
	{
		foreach(new i : BProducts[index_business])
		{
			if(BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_ID_TYPE] == type)
			{
				pDialogPagination_FirstIndex[playerid] = i;
				break;
			}
		}
	}
	else
	{
		new next_index = Iter_Next(BProducts[index_business], pDialogPagination_LastIndex[playerid]);
		if(next_index == Iter_End(BProducts[index_business]))
		{
			foreach(new i : BProducts[index_business])
			{
				if(BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_ID_TYPE] == type)
				{
					pDialogPagination_FirstIndex[playerid] = i;
					break;
				}
			}
		}
		else
		{
			for(new i = next_index; i != Iter_End(BProducts[index_business]); i = Iter_Next(BProducts[index_business], i))
			{
				if(BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_ID_TYPE] == type)
				{
					pDialogPagination_FirstIndex[playerid] = i;
					break;
				}
			}
			if(pDialogPagination_FirstIndex[playerid] == -1)
			{
				foreach(new i : BProducts[index_business])
				{
					if(BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_ID_TYPE] == type)
					{
						pDialogPagination_FirstIndex[playerid] = i;
						break;
					}
				}
			}
		}
	}

	if(pDialogPagination_FirstIndex[playerid] != -1)
	{
		//dialog
		new line_str[128], count = 0;
		strcat(dialog, GetProductsDialogTitle(playerid), dialog_size);
		for(new i = pDialogPagination_FirstIndex[playerid]; i != Iter_End(BProducts[index_business]); i = Iter_Next(BProducts[index_business], i))
		{
			if(BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_ID_TYPE] == type)
			{
				if(count >= DIALOG_PAGINATION_SIZE)
				{
					break;
				}
				else
				{
					new product_name[64], required_level = BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_LEVEL];
					format(product_name, sizeof product_name, "%s", GetBusinessProductName(playerid, BProducts[index_business][i][bproduct_INDEX_PRODUCT]));
					format(line_str, sizeof line_str, "{FFFFFF}%c%s\t{3ebf13}%d$\t%s\t{%06x}%d\n", toupper(product_name[0]), product_name[1], BProducts[index_business][i][bproduct_PRICE], GetFormattedBProductStock(playerid, BProducts[index_business][i][bproduct_STOCK]), required_level > PI[playerid][pi_LEVEL] ? 0xd30000 : 0x3ebf13, required_level);
					strcat(dialog, line_str, dialog_size);
					pExtraButtons[playerid][count++] = i;
					pDialogPagination_LastIndex[playerid] = i;
				}
			}	
		}
		pExtraButtons[playerid][count++] = DIALOG_PAGINATION_NEXT;
		strcat(dialog, GetProductsDialogNextPage(playerid), dialog_size);
	}
	return 1;
}

ShowBProducts(playerid)
{
	for(new i = 0; i < sizeof pBProducts_Order[]; i ++)
	pBProducts_Order[playerid][i] = false;
	//
	pBProducts_IndexBusiness[playerid] = PI[playerid][pi_WORLD_STATE_INDEX];
	pCurrentDialogPage[playerid] = 0;
	CreateBProductsTds(playerid);
	FormatBProductsTds(playerid);
	UpdateBusinessProductsTds(playerid);
	ShowBProductsTds(playerid);
	DisablePlayerLayers(playerid, LAYER_BUSINESS_DIALOG);
	pBProducts_Enabled[playerid] = true;
	SelectTextDraw(playerid, 0xCCCCCCFF);
	return 1;
}

ShowBProductsTds(playerid)
{
	for(new i = 0; i < sizeof pBProducts_Base_PTD[]; i ++)
	{
		if(pBProducts_Base_PTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawShow(playerid, pBProducts_Base_PTD[playerid][i]);
	}
	for(new i = 0; i < sizeof pBProducts_Products_PTD[]; i ++)
	{
		for(new j = 0; j < sizeof pBProducts_Products_PTD[][]; j ++)
		{
			if(pBProducts_Products_PTD[playerid][i][j] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawShow(playerid, pBProducts_Products_PTD[playerid][i][j]);
		}
	}
	return 1;
}

DestroyBProducts(playerid)
{
	pBProducts_Enabled[playerid] = false;
	//pBProducts_IndexBusiness[playerid] = -1;
	for(new i = 0; i < sizeof pBProducts_Base_PTD[]; i ++)
	{
		if(pBProducts_Base_PTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, pBProducts_Base_PTD[playerid][i]);
			pBProducts_Base_PTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	for(new i = 0; i < sizeof pBProducts_Products_PTD[]; i ++)
	{
		for(new j = 0; j < sizeof pBProducts_Products_PTD[][]; j ++)
		{
			if(pBProducts_Products_PTD[playerid][i][j] != PlayerText:INVALID_TEXT_DRAW)
			{
				PlayerTextDrawDestroy(playerid, pBProducts_Products_PTD[playerid][i][j]);
				pBProducts_Products_PTD[playerid][i][j] = PlayerText:INVALID_TEXT_DRAW;
			}
		}
	}
	EnablePlayerLayers(playerid);
	return 1;
}

CreateBProductsTds(playerid)
{
	new	Float:current_y, Float:padding, Float:unused,
		Float:base_box_pos_x, Float:base_box_pos_y,
		Float:base_box_size_x, Float:base_box_size_y,
		Float:baseInfo_box_size_y;

	//calc padding converted
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], 0.0, BPRODUCTS_TD_PADDING, false, unused, padding);

	//calc base size y
	base_box_size_y = padding + BPRODUCTS_TD_TEXT_OFFSET_Y + padding + BPRODUCTS_TD_TEXT_OFFSET_Y + padding;
	for(new i = 0; i < BPRODUCTS_TD_PRODUCTS; i ++)
	{
		base_box_size_y += BPRODUCTS_TD_TEXT_OFFSET_Y;
		baseInfo_box_size_y += BPRODUCTS_TD_TEXT_OFFSET_Y;
	}
	base_box_size_y += padding + BPRODUCTS_TD_TEXT_OFFSET_Y + padding;

	//calc base y
	base_box_pos_y = BPRODUCTS_TD_Y - (base_box_size_y / 2.0);
	current_y = base_box_pos_y;

	//tds
	AR_Calc(PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT], BPRODUCTS_TD_X, BPRODUCTS_TD_SIZE_X, true, base_box_pos_x, base_box_size_x);
	pBProducts_Base_PTD[playerid][0] = CreatePlayerTextDraw(playerid, base_box_pos_x, base_box_pos_y,  "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, pBProducts_Base_PTD[playerid][0], base_box_size_x, base_box_size_y);
	PlayerTextDrawAlignment(playerid, pBProducts_Base_PTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, pBProducts_Base_PTD[playerid][0], 240);
	PlayerTextDrawSetShadow(playerid, pBProducts_Base_PTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, pBProducts_Base_PTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, pBProducts_Base_PTD[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, pBProducts_Base_PTD[playerid][0], 0);
	SetPlayerTextDrawLayer(playerid, pBProducts_Base_PTD[playerid][0], LAYER_BUSINESS_DIALOG);

	current_y += padding;
	pBProducts_Base_PTD[playerid][1] = CreatePlayerTextDraw(playerid, BPRODUCTS_TD_X, current_y, "~y~PRODUCTOS");
	PlayerTextDrawLetterSize(playerid, pBProducts_Base_PTD[playerid][1], 0.208249, 1.112592);
	PlayerTextDrawAlignment(playerid, pBProducts_Base_PTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, pBProducts_Base_PTD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, pBProducts_Base_PTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, pBProducts_Base_PTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, pBProducts_Base_PTD[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, pBProducts_Base_PTD[playerid][1], 1);
	SetPlayerTextDrawLayer(playerid, pBProducts_Base_PTD[playerid][1], LAYER_BUSINESS_DIALOG);
	current_y += BPRODUCTS_TD_TEXT_OFFSET_Y + padding;

	new Float:order_size_x = (base_box_size_x - padding) / 5.0, //5 objetos
		Float:order_current_x = (base_box_pos_x + padding) + (order_size_x / 2.0);
	pBProducts_Column_Size_X[playerid] = order_size_x;
	pBProducts_Base_PTD[playerid][2] = CreatePlayerTextDraw(playerid, order_current_x, current_y, "~u~_ID");
	PlayerTextDrawLetterSize(playerid, pBProducts_Base_PTD[playerid][2], 0.228665, 1.039999);
	PlayerTextDrawAlignment(playerid, pBProducts_Base_PTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, pBProducts_Base_PTD[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, pBProducts_Base_PTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, pBProducts_Base_PTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, pBProducts_Base_PTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, pBProducts_Base_PTD[playerid][2], 1);
	PlayerTextDrawTextSize(playerid, pBProducts_Base_PTD[playerid][2], BPRODUCTS_TD_TEXT_OFFSET_Y, order_size_x);
	PlayerTextDrawSetSelectable(playerid, pBProducts_Base_PTD[playerid][2], true);
	SetPlayerTextDrawLayer(playerid, pBProducts_Base_PTD[playerid][2], LAYER_BUSINESS_DIALOG);
	order_current_x += order_size_x;

	pBProducts_Base_PTD[playerid][3] = CreatePlayerTextDraw(playerid, order_current_x, current_y, "Producto");
	PlayerTextDrawLetterSize(playerid, pBProducts_Base_PTD[playerid][3], 0.228665, 1.039999);
	PlayerTextDrawAlignment(playerid, pBProducts_Base_PTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, pBProducts_Base_PTD[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, pBProducts_Base_PTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, pBProducts_Base_PTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, pBProducts_Base_PTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, pBProducts_Base_PTD[playerid][3], 1);
	PlayerTextDrawTextSize(playerid, pBProducts_Base_PTD[playerid][3], BPRODUCTS_TD_TEXT_OFFSET_Y, order_size_x);
	PlayerTextDrawSetSelectable(playerid, pBProducts_Base_PTD[playerid][3], false);
	SetPlayerTextDrawLayer(playerid, pBProducts_Base_PTD[playerid][3], LAYER_BUSINESS_DIALOG);
	order_current_x += order_size_x;

	pBProducts_Base_PTD[playerid][4] = CreatePlayerTextDraw(playerid, order_current_x, current_y, "~u~_Precio");
	PlayerTextDrawLetterSize(playerid, pBProducts_Base_PTD[playerid][4], 0.228665, 1.039999);
	PlayerTextDrawAlignment(playerid, pBProducts_Base_PTD[playerid][4], 2);
	PlayerTextDrawColor(playerid, pBProducts_Base_PTD[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, pBProducts_Base_PTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, pBProducts_Base_PTD[playerid][4], 255);
	PlayerTextDrawFont(playerid, pBProducts_Base_PTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, pBProducts_Base_PTD[playerid][4], 1);
	PlayerTextDrawTextSize(playerid, pBProducts_Base_PTD[playerid][4], BPRODUCTS_TD_TEXT_OFFSET_Y, order_size_x);
	PlayerTextDrawSetSelectable(playerid, pBProducts_Base_PTD[playerid][4], true);
	SetPlayerTextDrawLayer(playerid, pBProducts_Base_PTD[playerid][4], LAYER_BUSINESS_DIALOG);
	order_current_x += order_size_x;

	pBProducts_Base_PTD[playerid][5] = CreatePlayerTextDraw(playerid, order_current_x, current_y, "~u~_Stock");
	PlayerTextDrawLetterSize(playerid, pBProducts_Base_PTD[playerid][5], 0.228665, 1.039999);
	PlayerTextDrawAlignment(playerid, pBProducts_Base_PTD[playerid][5], 2);
	PlayerTextDrawColor(playerid, pBProducts_Base_PTD[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, pBProducts_Base_PTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, pBProducts_Base_PTD[playerid][5], 255);
	PlayerTextDrawFont(playerid, pBProducts_Base_PTD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, pBProducts_Base_PTD[playerid][5], 1);
	PlayerTextDrawTextSize(playerid, pBProducts_Base_PTD[playerid][5], BPRODUCTS_TD_TEXT_OFFSET_Y, order_size_x);
	PlayerTextDrawSetSelectable(playerid, pBProducts_Base_PTD[playerid][5], true);
	SetPlayerTextDrawLayer(playerid, pBProducts_Base_PTD[playerid][5], LAYER_BUSINESS_DIALOG);
	order_current_x += order_size_x;

	pBProducts_Base_PTD[playerid][6] = CreatePlayerTextDraw(playerid, order_current_x, current_y, "~u~_Ventas");
	PlayerTextDrawLetterSize(playerid, pBProducts_Base_PTD[playerid][6], 0.228665, 1.039999);
	PlayerTextDrawAlignment(playerid, pBProducts_Base_PTD[playerid][6], 2);
	PlayerTextDrawColor(playerid, pBProducts_Base_PTD[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, pBProducts_Base_PTD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, pBProducts_Base_PTD[playerid][6], 255);
	PlayerTextDrawFont(playerid, pBProducts_Base_PTD[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, pBProducts_Base_PTD[playerid][6], 1);
	PlayerTextDrawTextSize(playerid, pBProducts_Base_PTD[playerid][6], BPRODUCTS_TD_TEXT_OFFSET_Y, order_size_x);
	PlayerTextDrawSetSelectable(playerid, pBProducts_Base_PTD[playerid][6], true);
	SetPlayerTextDrawLayer(playerid, pBProducts_Base_PTD[playerid][6], LAYER_BUSINESS_DIALOG);
	current_y += BPRODUCTS_TD_TEXT_OFFSET_Y + padding;

	pBProducts_Base_PTD[playerid][7] = CreatePlayerTextDraw(playerid, base_box_pos_x + padding, current_y, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, pBProducts_Base_PTD[playerid][7], base_box_size_x - (padding * 2.0), baseInfo_box_size_y);
	PlayerTextDrawAlignment(playerid, pBProducts_Base_PTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, pBProducts_Base_PTD[playerid][7], 1181645055);
	PlayerTextDrawSetShadow(playerid, pBProducts_Base_PTD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, pBProducts_Base_PTD[playerid][7], 255);
	PlayerTextDrawFont(playerid, pBProducts_Base_PTD[playerid][7], 4);
	PlayerTextDrawSetProportional(playerid, pBProducts_Base_PTD[playerid][7], 0);
	SetPlayerTextDrawLayer(playerid, pBProducts_Base_PTD[playerid][7], LAYER_BUSINESS_DIALOG);
	
	//products
	for(new i = 0; i < sizeof pBProducts_Products_PTD[]; i ++)
	{
		pBProducts_Products_PTD[playerid][i][0] = CreatePlayerTextDraw(playerid, base_box_pos_x + padding, current_y, "LD_SPAC:white");
		PlayerTextDrawTextSize(playerid, pBProducts_Products_PTD[playerid][i][0], base_box_size_x - (padding * 2.0), BPRODUCTS_TD_TEXT_OFFSET_Y);
		PlayerTextDrawAlignment(playerid, pBProducts_Products_PTD[playerid][i][0], 1);
		PlayerTextDrawColor(playerid, pBProducts_Products_PTD[playerid][i][0], 0x00000000);
		PlayerTextDrawSetShadow(playerid, pBProducts_Products_PTD[playerid][i][0], 0);
		PlayerTextDrawBackgroundColor(playerid, pBProducts_Products_PTD[playerid][i][0], 255);
		PlayerTextDrawFont(playerid, pBProducts_Products_PTD[playerid][i][0], 4);
		PlayerTextDrawSetProportional(playerid, pBProducts_Products_PTD[playerid][i][0], 0);
		PlayerTextDrawSetSelectable(playerid, pBProducts_Products_PTD[playerid][i][0], false);
		SetPlayerTextDrawLayer(playerid, pBProducts_Products_PTD[playerid][i][0], LAYER_BUSINESS_DIALOG);
		order_current_x = (base_box_pos_x + padding) + (order_size_x / 2.0);
		for(new j = 1; j < sizeof pBProducts_Products_PTD[][]; j ++)
		{
			pBProducts_Products_PTD[playerid][i][j] = CreatePlayerTextDraw(playerid, order_current_x, current_y, "_");
			PlayerTextDrawLetterSize(playerid, pBProducts_Products_PTD[playerid][i][j], 0.228665, 1.039999);
			PlayerTextDrawAlignment(playerid, pBProducts_Products_PTD[playerid][i][j], 2);
			PlayerTextDrawColor(playerid, pBProducts_Products_PTD[playerid][i][j], -1);
			PlayerTextDrawSetShadow(playerid, pBProducts_Products_PTD[playerid][i][j], 0);
			PlayerTextDrawBackgroundColor(playerid, pBProducts_Products_PTD[playerid][i][j], 255);
			PlayerTextDrawFont(playerid, pBProducts_Products_PTD[playerid][i][j], 1);
			PlayerTextDrawSetProportional(playerid, pBProducts_Products_PTD[playerid][i][j], 1);
			PlayerTextDrawTextSize(playerid, pBProducts_Products_PTD[playerid][i][j], BPRODUCTS_TD_TEXT_OFFSET_Y, order_size_x);
			SetPlayerTextDrawLayer(playerid, pBProducts_Products_PTD[playerid][i][j], LAYER_BUSINESS_DIALOG);
			order_current_x += order_size_x;
		}
		current_y += BPRODUCTS_TD_TEXT_OFFSET_Y;
	}
	current_y += /*baseInfo_box_size_y +*/ padding;
	//products

	pBProducts_Base_PTD[playerid][8] = CreatePlayerTextDraw(playerid, base_box_pos_x + padding, current_y, "+_Anadir_producto");
	PlayerTextDrawLetterSize(playerid, pBProducts_Base_PTD[playerid][8], 0.228665, 1.039999);
	PlayerTextDrawTextSize(playerid, pBProducts_Base_PTD[playerid][8], (base_box_pos_x + padding) + 70.0, BPRODUCTS_TD_TEXT_OFFSET_Y);
	PlayerTextDrawAlignment(playerid, pBProducts_Base_PTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, pBProducts_Base_PTD[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, pBProducts_Base_PTD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, pBProducts_Base_PTD[playerid][8], 255);
	PlayerTextDrawFont(playerid, pBProducts_Base_PTD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, pBProducts_Base_PTD[playerid][8], 1);
	PlayerTextDrawSetSelectable(playerid, pBProducts_Base_PTD[playerid][8], true);
	SetPlayerTextDrawLayer(playerid, pBProducts_Base_PTD[playerid][8], LAYER_BUSINESS_DIALOG);

	pBProducts_Base_PTD[playerid][9] = CreatePlayerTextDraw(playerid, BPRODUCTS_TD_X, current_y, "1/1");
	PlayerTextDrawLetterSize(playerid, pBProducts_Base_PTD[playerid][9], 0.228665, 1.039999);
	PlayerTextDrawTextSize(playerid, pBProducts_Base_PTD[playerid][9], BPRODUCTS_TD_TEXT_OFFSET_Y, 10.0);
	PlayerTextDrawAlignment(playerid, pBProducts_Base_PTD[playerid][9], 2);
	PlayerTextDrawColor(playerid, pBProducts_Base_PTD[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, pBProducts_Base_PTD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, pBProducts_Base_PTD[playerid][9], 255);
	PlayerTextDrawFont(playerid, pBProducts_Base_PTD[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, pBProducts_Base_PTD[playerid][9], 1);
	PlayerTextDrawSetSelectable(playerid, pBProducts_Base_PTD[playerid][9], true);
	SetPlayerTextDrawLayer(playerid, pBProducts_Base_PTD[playerid][9], LAYER_BUSINESS_DIALOG);
	return 1;
}

UpdateBusinessProductsTds(playerid, order_sql[] = "id_product ASC")
{
	new total_pages = GetDialogPages(Iter_Count(BProducts[pBProducts_IndexBusiness[playerid]]), BPRODUCTS_TD_PRODUCTS),
		td_str[24];

	//pages
	format(td_str, sizeof td_str, "%d/%d", pCurrentDialogPage[playerid] + 1, total_pages);
	PlayerTextDrawSetString(playerid, pBProducts_Base_PTD[playerid][9], td_str);

	//products
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i < rows; i ++)
			{
				new	td_str2[64], index_product = -1,
					bool:is_null_sales,
					id_product, price, p_stock, sales;

				cache_get_value_index_int(i, 0, id_product);
				cache_get_value_index_int(i, 1, price);
				cache_get_value_index_int(i, 2, p_stock);
				cache_is_value_index_null(i, 3, is_null_sales);
				if(!is_null_sales) cache_get_value_index_int(i, 3, sales);
				//tds
				PlayerTextDrawSetSelectable(playerid, pBProducts_Products_PTD[playerid][i][0], true);
				PlayerTextDrawShow(playerid, pBProducts_Products_PTD[playerid][i][0]);
				format(td_str2, sizeof td_str2, "%d", id_product);
				PlayerTextDrawSetString(playerid, pBProducts_Products_PTD[playerid][i][1], td_str2);
				format(td_str2, sizeof td_str2, "%d$", price);
				PlayerTextDrawSetString(playerid, pBProducts_Products_PTD[playerid][i][3], td_str2);
				format(td_str2, sizeof td_str2, "%d", p_stock);
				PlayerTextDrawSetString(playerid, pBProducts_Products_PTD[playerid][i][4], td_str2);
				format(td_str2, sizeof td_str2, "%d", sales);
				PlayerTextDrawSetString(playerid, pBProducts_Products_PTD[playerid][i][5], td_str2);
				//name
				index_product = GetBusinessProductIndexById(pBProducts_IndexBusiness[playerid], id_product);
				if(index_product != -1)
				{
					pExtraButtons[playerid][i] = index_product;
					format(td_str2, sizeof td_str2, "%s", GetBusinessProductName(playerid, BProducts[pBProducts_IndexBusiness[playerid]][index_product][bproduct_INDEX_PRODUCT]));
					format(td_str2, sizeof td_str2, "%c%s", toupper(td_str2[0]), td_str2[1]);
					PlayerTextDrawSetString(playerid, pBProducts_Products_PTD[playerid][i][2], td_str2);

					new Float:letter_x = GetTdTextFontX(1, td_str2, true, 0.0, pBProducts_Column_Size_X[playerid]);
					if(letter_x > 0.228665) letter_x = 0.228665;
					PlayerTextDrawLetterSize(playerid, pBProducts_Products_PTD[playerid][i][2], letter_x, 1.039999);
					PlayerTextDrawShow(playerid, pBProducts_Products_PTD[playerid][i][2]);
				}
				else
				{
					pExtraButtons[playerid][i] = -1;
					PlayerTextDrawSetString(playerid, pBProducts_Products_PTD[playerid][i][2], "-");
				}
			}
			for(new i = rows; i < BPRODUCTS_TD_PRODUCTS; i ++) //reset
			{
				pExtraButtons[playerid][i] = -1;
				PlayerTextDrawSetSelectable(playerid, pBProducts_Products_PTD[playerid][i][0], false);
				PlayerTextDrawShow(playerid, pBProducts_Products_PTD[playerid][i][0]);
				for(new j = 1; j < sizeof pBProducts_Products_PTD[][]; j ++)
				PlayerTextDrawSetString(playerid, pBProducts_Products_PTD[playerid][i][j], "_");
			}
		}
	}
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER,
		"SELECT \
			business_sales_products.id_product, \
			business_sales_products.price, \
			business_sales_products.stock, \
			(SELECT SUM(business_sales.amount) FROM business_sales WHERE business_sales.id_product = business_sales_products.id_product AND business_sales.id_business = business_sales_products.id_business) AS sales \
		FROM business_sales_products \
		WHERE business_sales_products.id_business = %d \
		ORDER BY %s LIMIT %d, %d;", BusinessData[pBProducts_IndexBusiness[playerid]][bdata_ID], order_sql, BPRODUCTS_TD_PRODUCTS * pCurrentDialogPage[playerid], BPRODUCTS_TD_PRODUCTS);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	return 1;
}

GetBusinessTypeNameFromId(playerid, id)
{
	new name[32];
	switch(id)
	{
		case BUSINESS_TYPE_GENERAL_STORE: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_TYPE_GENERAL_STORE);
		case BUSINESS_TYPE_AMMUNATION: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_TYPE_AMMUNATION);
		case BUSINESS_TYPE_CLOTHING_STORE: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_TYPE_CLOTHING_STORE);
		case BUSINESS_TYPE_RESTAURANT: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_TYPE_RESTAURANT);
		case BUSINESS_TYPE_BURGER: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_TYPE_BURGER);
		case BUSINESS_TYPE_PIZZA: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_TYPE_PIZZA);
		case BUSINESS_TYPE_DISCO: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_TYPE_DISCO);
		case BUSINESS_TYPE_BAR: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_TYPE_BAR);
		case BUSINESS_TYPE_ELECTRONICS: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_TYPE_ELECTRONICS);
		case BUSINESS_TYPE_HARDWARE_STORE: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_TYPE_HARDWARE_STORE);
	}
	return name;
}

GetBusinessSaleTypeNameFromId(playerid, id)
{
	new name[32];
	switch(id)
	{
		case BUSINESS_SALE_TYPE_FOOD: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_FOOD);
		case BUSINESS_SALE_TYPE_DRINK: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_DRINK);
		case BUSINESS_SALE_TYPE_CLOTHES: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_CLOTHES);
		case BUSINESS_SALE_TYPE_TOYS: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_TOYS);
		case BUSINESS_SALE_TYPE_ELECTRONICS: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_ELECTRONICS);
		case BUSINESS_SALE_TYPE_BAR: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_BAR);
		case BUSINESS_SALE_TYPE_WEAPONS: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_WEAPONS);
		case BUSINESS_SALE_TYPE_AMMO: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_AMMO);
		case BUSINESS_SALE_TYPE_ALL: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_ALL);
		case BUSINESS_SALE_TYPE_HARDWARE: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_HARDWARE);
		case BUSINESS_SALE_TYPE_CIGARETTES: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_CIGARETTES);
	}
	return name;
}

GetBusinessProductName(playerid, bproductinfo_index)
{
	new name[64];
	if(BProducts_Info[bproductinfo_index][bproduct_info_ID_INVITEM] != 0)
	{
		format(name, sizeof name, "%s", GetItemName(playerid, BProducts_Info[bproductinfo_index][bproduct_info_ID_INVITEM]));
	}
	else
	{
		switch(BProducts_Info[bproductinfo_index][bproduct_info_ID_TYPE])
		{
			case BUSINESS_SALE_TYPE_CLOTHES: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_SALE_TYPE_CLOTHES);
			default:
			{
				switch(BProducts_Info[bproductinfo_index][bproduct_info_ID])
				{
					case 48: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_PRODUCT_WINE);
					case 49: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_PRODUCT_SPRUNK);
					case 53: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_PRODUCT_DUPLICATE_KEYS);
					case 54: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $BUSINESS_PRODUCT_NORMAL_AMMO);
				}
			}
		}
	}
	return name;
}

GetProductsDialogTitle(playerid)
{
	new name[32];
	Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $DIALOG_BUSINESS_CATALOG_HEADER);
	return name;
}

GetProductsDialogCaption(playerid)
{
	new name[32];
	Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $DIALOG_BUSINESS_CATALOG_CAPTION);
	return name;
}

GetFormattedBProductStock(playerid, amount)
{
	new str_stock[32];
	format(str_stock, sizeof str_stock, "%d", amount);
	if(amount <= 0)
	Text_Format_Dialog(str_stock, sizeof str_stock, PI[playerid][pi_LANG_ID], $DIALOG_BUSINESS_CATALOG_NO_STOCK);
	
	//color
	if(amount >= 20) strins(str_stock, "{3ebf13}", 0);
	else if(amount >= 1) strins(str_stock, "{ecf22b}", 0);
	else strins(str_stock, "{d30000}", 0);
	return str_stock;
}

GetProductsDialogNextPage(playerid)
{
	new name[32];	
	Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $DIALOG_BUSINESS_CATALOG_NEXT_PAGE);
	return name;
}

FormatBProductsTds(playerid)
{
	PlayerTD_Text(playerid, pBProducts_Base_PTD[playerid][1], $TEXTDRAW_BCATALOG_TITLE);
	if(pBProducts_Order[playerid][0]) { PlayerTD_Text(playerid, pBProducts_Base_PTD[playerid][2], $TEXTDRAW_BCATALOG_ID_DOWN); }
	else { PlayerTD_Text(playerid, pBProducts_Base_PTD[playerid][2], $TEXTDRAW_BCATALOG_ID_UP); }
	PlayerTD_Text(playerid, pBProducts_Base_PTD[playerid][3], $TEXTDRAW_BCATALOG_PRODUCT);
	if(pBProducts_Order[playerid][2]) { PlayerTD_Text(playerid, pBProducts_Base_PTD[playerid][4], $TEXTDRAW_BCATALOG_PRICE_DOWN); }
	else { PlayerTD_Text(playerid, pBProducts_Base_PTD[playerid][4], $TEXTDRAW_BCATALOG_PRICE_UP); }
	if(pBProducts_Order[playerid][3]) { PlayerTD_Text(playerid, pBProducts_Base_PTD[playerid][5], $TEXTDRAW_BCATALOG_STOCK_DOWN); }
	else { PlayerTD_Text(playerid, pBProducts_Base_PTD[playerid][5], $TEXTDRAW_BCATALOG_STOCK_UP); }
	if(pBProducts_Order[playerid][4]) { PlayerTD_Text(playerid, pBProducts_Base_PTD[playerid][6], $TEXTDRAW_BCATALOG_SALES_DOWN); }
	else { PlayerTD_Text(playerid, pBProducts_Base_PTD[playerid][6], $TEXTDRAW_BCATALOG_SALES_UP); }
	PlayerTD_Text(playerid, pBProducts_Base_PTD[playerid][8], $TEXTDRAW_BCATALOG_ADD_PRODUCT);
	return 1;
}