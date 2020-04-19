#define IsBusinessOccupied(%0) BusinessData[%0][bdata_ID_PLAYER]
#define GetBusinessOwner(%0) BusinessData[%0][bdata_ID_PLAYER]

CreateBusinessSalePointInfo(index)
{
	//destroy if exists
	#if CUSTOM_PICKUPS == true
		if(BSales_Points[index][bsale_point_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicObject(BSales_Points[index][bsale_point_PICKUP_ID]);
			BSales_Points[index][bsale_point_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#else
		if(BSales_Points[index][bsale_point_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicPickup(BSales_Points[index][bsale_point_PICKUP_ID]);
			BSales_Points[index][bsale_point_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#endif
	if(BSales_Points[index][bsale_point_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(BSales_Points[index][bsale_point_AREA_ID]);
		BSales_Points[index][bsale_point_AREA_ID] = INVALID_STREAMER_ID;
	}
	if(BSales_Points[index][bsale_point_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(BSales_Points[index][bsale_point_LABEL_AREA_ID]);
		BSales_Points[index][bsale_point_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}

	//create
	#if CUSTOM_PICKUPS == true
		BSales_Points[index][bsale_point_PICKUP_ID] = CreateDynamicObject(CUSTOM_PICKUP_MODELID, BSales_Points[index][bsale_point_X], BSales_Points[index][bsale_point_Y], BSales_Points[index][bsale_point_Z], 0.0, 0.0, 0.0, .worldid = -1, .interiorid = Interiors[ BSales_Points[index][bsale_point_INDEX_INTERIOR] ][interior_INTERIORID], .streamdistance = PICKUP_DISTANCE, .drawdistance = PICKUP_DISTANCE, .priority = 10);	
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, BSales_Points[index][bsale_point_PICKUP_ID], E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_PICKUP_BSALE_POINT);
	#else
		new pickup_model = 1274;
		BSales_Points[index][bsale_point_PICKUP_ID] = CreateDynamicPickup(pickup_model, 1, BSales_Points[index][bsale_point_X], BSales_Points[index][bsale_point_Y], BSales_Points[index][bsale_point_Z], -1, Interiors[ BSales_Points[index][bsale_point_INDEX_INTERIOR] ][interior_INTERIORID], .streamdistance = PICKUP_DISTANCE, .priority = 10);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, BSales_Points[index][bsale_point_PICKUP_ID], E_STREAMER_EXTRA_ID, _:PICKUP_TYPE_PICKUP_BSALE_POINT);
	#endif

	new streamer_info[2];
	BSales_Points[index][bsale_point_AREA_ID] = CreateDynamicCylinder(BSales_Points[index][bsale_point_X], BSales_Points[index][bsale_point_Y], BSales_Points[index][bsale_point_Z] - 1.0, BSales_Points[index][bsale_point_Z] + 3.0, 1.0, -1, Interiors[ BSales_Points[index][bsale_point_INDEX_INTERIOR] ][interior_INTERIORID]);
	streamer_info[0] = _:AREA_TYPE_BSALE_POINT;
	streamer_info[1] = index;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, BSales_Points[index][bsale_point_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);

	BSales_Points[index][bsale_point_LABEL_AREA_ID] = CreateDynamicCylinder(BSales_Points[index][bsale_point_X], BSales_Points[index][bsale_point_Y], BSales_Points[index][bsale_point_Z] - PLAYER_LABEL_DISTANCE, BSales_Points[index][bsale_point_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, -1, Interiors[ BSales_Points[index][bsale_point_INDEX_INTERIOR] ][interior_INTERIORID]);
	streamer_info[0] = _:AREA_TYPE_LABEL_BSALE_POINT;
	streamer_info[1] = index;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, BSales_Points[index][bsale_point_LABEL_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);
}

GetBusinessIndexFromId(id)
{
	foreach(new i : BusinessData)
	{
		if(BusinessData[i][bdata_ID] == id)
		{
			return i;
		}
	}
	return -1;
}

GetBusinessDoorIndexFromId(index_business, id)
{
	foreach(new i : BusinessDoors[index_business])
	{
		if(BusinessDoors[index_business][i][bdoor_ID] == id)
		{
			return i;
		}
	}
	return -1;
}

CreateBusinessDoorInfo(index_business, index_door)
{
	//destroy if exists
	#if CUSTOM_PICKUPS == true
		if(BusinessDoors[index_business][index_door][bdoor_EXT_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicObject(BusinessDoors[index_business][index_door][bdoor_EXT_PICKUP_ID]);
			BusinessDoors[index_business][index_door][bdoor_EXT_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#else
		if(BusinessDoors[index_business][index_door][bdoor_EXT_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicPickup(BusinessDoors[index_business][index_door][bdoor_EXT_PICKUP_ID]);
			BusinessDoors[index_business][index_door][bdoor_EXT_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#endif
	if(BusinessDoors[index_business][index_door][bdoor_EXT_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(BusinessDoors[index_business][index_door][bdoor_EXT_AREA_ID]);
		BusinessDoors[index_business][index_door][bdoor_EXT_AREA_ID] = INVALID_STREAMER_ID;
	}
	if(BusinessDoors[index_business][index_door][bdoor_EXT_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(BusinessDoors[index_business][index_door][bdoor_EXT_LABEL_AREA_ID]);
		BusinessDoors[index_business][index_door][bdoor_EXT_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}
	if(BusinessDoors[index_business][index_door][bdoor_INT_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(BusinessDoors[index_business][index_door][bdoor_INT_AREA_ID]);
		BusinessDoors[index_business][index_door][bdoor_INT_AREA_ID] = INVALID_STREAMER_ID;
	}
	if(BusinessDoors[index_business][index_door][bdoor_INT_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(BusinessDoors[index_business][index_door][bdoor_INT_LABEL_AREA_ID]);
		BusinessDoors[index_business][index_door][bdoor_INT_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}

	//create
	new ext_worldid = VC_WORLD,
		ext_interiorid = 0,
		int_worldid = BusinessDoors[index_business][index_door][bdoor_ID_BUSINESS],
		int_interiorid = Interiors[ BusinessDoors[index_business][index_door][bdoor_INDEX_INTERIOR] ][interior_INTERIORID];

	if(BusinessDoors[index_business][index_door][bdoor_EXT_ENTRANCE_DOOR_INDEX] != -1)
	{
		ext_worldid = Entrances[ BusinessDoors[index_business][index_door][bdoor_EXT_ENTRANCE_DOOR_INDEX] ][entrance_ID_ENTRANCE];
		ext_interiorid = Interiors[Entrances[ BusinessDoors[index_business][index_door][bdoor_EXT_ENTRANCE_DOOR_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID];
	}
	else if(BusinessDoors[index_business][index_door][bdoor_EXT_SUB_INDEX] != -1)
	{
		ext_worldid = BusinessDoors[index_business][index_door][bdoor_ID_BUSINESS];
		ext_interiorid = Interiors[ BusinessDoors[index_business][ BusinessDoors[index_business][index_door][bdoor_EXT_SUB_INDEX] ][bdoor_INDEX_INTERIOR] ][interior_INTERIORID];
	}

	#if CUSTOM_PICKUPS == true
		BusinessDoors[index_business][index_door][bdoor_EXT_PICKUP_ID] = CreateDynamicObject(CUSTOM_PICKUP_MODELID, BusinessDoors[index_business][index_door][bdoor_EXT_X], BusinessDoors[index_business][index_door][bdoor_EXT_Y], BusinessDoors[index_business][index_door][bdoor_EXT_Z], 0.0, 0.0, 0.0, .worldid = ext_worldid, .interiorid = ext_interiorid, .streamdistance = PICKUP_DISTANCE, .drawdistance = PICKUP_DISTANCE, .priority = 10);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, BusinessDoors[index_business][index_door][bdoor_EXT_PICKUP_ID], E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_PICKUP_BDOOR);
	#else
		new pickup_model = 1318;
		BusinessDoors[index_business][index_door][bdoor_EXT_PICKUP_ID] = CreateDynamicPickup(pickup_model, 1, BusinessDoors[index_business][index_door][bdoor_EXT_X], BusinessDoors[index_business][index_door][bdoor_EXT_Y], BusinessDoors[index_business][index_door][bdoor_EXT_Z], ext_worldid, ext_interiorid, .streamdistance = PICKUP_DISTANCE, .priority = 10);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, BusinessDoors[index_business][index_door][bdoor_EXT_PICKUP_ID], E_STREAMER_EXTRA_ID, _:PICKUP_TYPE_PICKUP_BDOOR);
	#endif

	new streamer_info[3];
	BusinessDoors[index_business][index_door][bdoor_EXT_AREA_ID] = CreateDynamicCylinder(BusinessDoors[index_business][index_door][bdoor_EXT_X], BusinessDoors[index_business][index_door][bdoor_EXT_Y], BusinessDoors[index_business][index_door][bdoor_EXT_Z] - 1.0, BusinessDoors[index_business][index_door][bdoor_EXT_Z] + 3.0, 1.0, ext_worldid, ext_interiorid);
	streamer_info[0] = _:AREA_TYPE_BDOOR_EXT;
	streamer_info[1] = index_business;
	streamer_info[2] = index_door;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, BusinessDoors[index_business][index_door][bdoor_EXT_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);

	BusinessDoors[index_business][index_door][bdoor_EXT_LABEL_AREA_ID] = CreateDynamicCylinder(BusinessDoors[index_business][index_door][bdoor_EXT_X], BusinessDoors[index_business][index_door][bdoor_EXT_Y], BusinessDoors[index_business][index_door][bdoor_EXT_Z] - PLAYER_LABEL_DISTANCE, BusinessDoors[index_business][index_door][bdoor_EXT_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, ext_worldid, ext_interiorid);
	streamer_info[0] = _:AREA_TYPE_LABEL_BDOOR_EXT;
	streamer_info[1] = index_business;
	streamer_info[2] = index_door;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, BusinessDoors[index_business][index_door][bdoor_EXT_LABEL_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);

	BusinessDoors[index_business][index_door][bdoor_INT_AREA_ID] = CreateDynamicCylinder(Interiors[ BusinessDoors[index_business][index_door][bdoor_INDEX_INTERIOR] ][interior_X], Interiors[ BusinessDoors[index_business][index_door][bdoor_INDEX_INTERIOR] ][interior_Y], Interiors[ BusinessDoors[index_business][index_door][bdoor_INDEX_INTERIOR] ][interior_Z] - 1.0, Interiors[ BusinessDoors[index_business][index_door][bdoor_INDEX_INTERIOR] ][interior_Z] + 3.0, 1.0, int_worldid, int_interiorid);
	streamer_info[0] = _:AREA_TYPE_BDOOR_INT;
	streamer_info[1] = index_business;
	streamer_info[2] = index_door;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, BusinessDoors[index_business][index_door][bdoor_INT_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);

	BusinessDoors[index_business][index_door][bdoor_INT_LABEL_AREA_ID] = CreateDynamicCylinder(Interiors[ BusinessDoors[index_business][index_door][bdoor_INDEX_INTERIOR] ][interior_X], Interiors[ BusinessDoors[index_business][index_door][bdoor_INDEX_INTERIOR] ][interior_Y], Interiors[ BusinessDoors[index_business][index_door][bdoor_INDEX_INTERIOR] ][interior_Z] - PLAYER_LABEL_DISTANCE, Interiors[ BusinessDoors[index_business][index_door][bdoor_INDEX_INTERIOR] ][interior_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, int_worldid, int_interiorid);
	streamer_info[0] = _:AREA_TYPE_LABEL_BDOOR_INT;
	streamer_info[1] = index_business;
	streamer_info[2] = index_door;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, BusinessDoors[index_business][index_door][bdoor_INT_LABEL_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);
}

GetProductInfoIndexById(id)
{
	foreach(new i : BProducts_Info)
	{
		if(BProducts_Info[i][bproduct_info_ID] == id)
		{
			return i;
		}
	}
	return -1;
}

GetBusinessProductIndexById(index_business, id_product)
{
	foreach(new i : BProducts[index_business])
	{
		if(BProducts[index_business][i][bproduct_ID_PRODUCT] == id_product)
		{
			return i;
		}
	}
	return -1;
}

ResetBusinessProducts(index_business)
{
	//reset
	new tmp_BProducts[E_BProducts];
	foreach(new i : BProducts[index_business])
	{
		BProducts[index_business][i] = tmp_BProducts;
	}
	Iter_Clear(BProducts[index_business]);

	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM business_sales_products WHERE id_business = %d;", BusinessData[index_business][bdata_ID]);
	mysql_tquery(vcrp_db, QUERY_BUFFER);
	//copy
	new index_product;
	foreach(new i : BProducts_Info)
	{
		foreach(new j : BTypes_STypes)
		{
			if(BTypes_STypes[j][btype_stype_ID_BUSINESS_TYPE] == BusinessData[index_business][bdata_ID_TYPE])
			{
				if(BProducts_Info[i][bproduct_info_ID_TYPE] == BTypes_STypes[j][btype_stype_ID_BSALES_TYPE])
				{
					if(index_product >= MAX_PRODUCTS_PER_BUSINESS)
					{
						break;
					}
					BProducts[index_business][index_product][bproduct_ID_PRODUCT] = BProducts_Info[i][bproduct_info_ID];
					BProducts[index_business][index_product][bproduct_ID_BUSINESS] = BusinessData[index_business][bdata_ID];
					BProducts[index_business][index_product][bproduct_PRICE] = BProducts_Info[i][bproduct_info_PRICE];
					BProducts[index_business][index_product][bproduct_STOCK] = BUSINESS_DEFAULT_STOCK;
					BProducts[index_business][index_product][bproduct_INDEX_PRODUCT] = i;
					Iter_Add(BProducts[index_business], index_product);
					
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO business_sales_products VALUES (%d, %d, %d, %d);", BProducts[index_business][index_product][bproduct_ID_PRODUCT], BProducts[index_business][index_product][bproduct_ID_BUSINESS], BProducts[index_business][index_product][bproduct_PRICE], BProducts[index_business][index_product][bproduct_STOCK]);
					mysql_tquery(vcrp_db, QUERY_BUFFER);
					index_product ++;
				}
			}
		}
	}
	return 1;
}

CountBusinessProducts(index_business, product_types = BUSINESS_SALE_TYPE_ALL)
{
	new c;
	if(product_types == BUSINESS_SALE_TYPE_ALL)
	{
		c = Iter_Count(BProducts[index_business]);
	}
	else
	{
		foreach(new i : BProducts[index_business])
		{
			if(BProducts_Info[ BProducts[index_business][i][bproduct_INDEX_PRODUCT] ][bproduct_info_ID_TYPE] == product_types)
			{
				c ++;
			}
		}
	}
	return c;
}

SellBusinessProductInfo(index_business, index_product, playerid = INVALID_PLAYER_ID, amount = 1)
{
	BProducts[index_business][index_product][bproduct_STOCK] -= amount;
	if(BProducts[index_business][index_product][bproduct_STOCK] < 0) BProducts[index_business][index_product][bproduct_STOCK] = 0;
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business_sales_products SET stock = %d WHERE id_product = %d AND id_business = %d;", BProducts[index_business][index_product][bproduct_STOCK], BProducts[index_business][index_product][bproduct_ID_PRODUCT], BProducts[index_business][index_product][bproduct_ID_BUSINESS]);
	mysql_tquery(vcrp_db, QUERY_BUFFER);

	BusinessData[index_business][bdata_MONEY] += BProducts[index_business][index_product][bproduct_PRICE] * amount;
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business SET money = %d WHERE id = %d;", BusinessData[index_business][bdata_MONEY], BusinessData[index_business][bdata_ID]);
	mysql_tquery(vcrp_db, QUERY_BUFFER);

	if(playerid == INVALID_PLAYER_ID)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO business_sales (id_business, id_player, id_product, price, amount, sale_date) VALUES (%d, NULL, %d, %d, %d, %s);", BusinessData[index_business][bdata_ID], BProducts[index_business][index_product][bproduct_ID_PRODUCT], BProducts[index_business][index_product][bproduct_PRICE], amount, getDateTimeDB());
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}
	else
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO business_sales (id_business, id_player, id_product, price, amount, sale_date) VALUES (%d, %d, %d, %d, %d, %s);", BusinessData[index_business][bdata_ID], PI[playerid][pi_ID], BProducts[index_business][index_product][bproduct_ID_PRODUCT], BProducts[index_business][index_product][bproduct_PRICE], amount, getDateTimeDB());
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}
	return 1;
}

UpdateBusinessData(index_business)
{
	new str_id_player[24];
	if(BusinessData[index_business][bdata_ID_PLAYER] == 0) str_id_player = "NULL";
	else format(str_id_player, sizeof str_id_player, "%d", BusinessData[index_business][bdata_ID_PLAYER]);

	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE business SET id_type = %d, price = %d, level = %d, money = %d, hour_open = %d, hour_close = %d, id_player = %s, radio = %d WHERE id = %d;",
			BusinessData[index_business][bdata_ID_TYPE], BusinessData[index_business][bdata_PRICE], BusinessData[index_business][bdata_LEVEL], BusinessData[index_business][bdata_MONEY],
			BusinessData[index_business][bdata_HOUR_OPEN], BusinessData[index_business][bdata_HOUR_CLOSE], str_id_player, BusinessData[index_business][bdata_RADIO], BusinessData[index_business][bdata_ID]);
	mysql_tquery(vcrp_db, QUERY_BUFFER);
	return 1;
}

CountBusiness(option = 0)
{
	switch(option)
	{
		case 0: return Iter_Count(BusinessData);
		case 1: //libres
		{
			new c;
			foreach(new i : BusinessData)
			{
				if(!IsBusinessOccupied(i))
				{
					c ++;
				}
			}
			return c;
		}
		case 2: //ocupadas
		{
			new c;
			foreach(new i : BusinessData)
			{
				if(IsBusinessOccupied(i))
				{
					c ++;
				}
			}
			return c;
		}
		case 3: //sin puerta
		{
			new c;
			foreach(new i : BusinessData)
			{
				if(Iter_Count(BusinessDoors[i]) == 0)
				{
					c ++;
				}
			}
			return c;
		}
	}
	return 0;
}

DeleteBusinessKeys(id, bindex = -1)
{
	new params[24];
	format(params, sizeof params, "%d", id);

	//player
	foreach(new i : Player)
	{
		if(bindex != -1)
		{
			if(Iter_Contains(PlayerBusiness<i>, bindex))
			Iter_Remove(PlayerBusiness<i>, bindex);
		}
		foreach(new x : PINV[i])
		{
			if(PINV[i][x][pinv_ITEM_ID] == _:INV_ITEM_BUSINESS_KEY || PINV[i][x][pinv_ITEM_ID] == _:INV_ITEM_BUSINESS_MASTER_KEY)
			{
				if(!strcmp(PINV[i][x][pinv_PARAMS], params))
				{
					new tmp_PINV[enum_PINV], prev;
					PINV[i][x] = tmp_PINV;

					Iter_SafeRemove(PINV[i], x, prev); 
					x = prev;
				}
			}
		}
	}

	//db
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_inv WHERE (item_id = %d OR item_id = %d) AND params = '%e';", _:INV_ITEM_BUSINESS_KEY, _:INV_ITEM_BUSINESS_MASTER_KEY, params);
	mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
	return 1;
}

DeleteBusinessDoor(business_index, door_index, bool:db = false, bool:iter_remove = true)
{
	if(db)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM business_doors WHERE id = %d;", BusinessDoors[business_index][door_index][bdoor_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}

	#if CUSTOM_PICKUPS == true
		if(BusinessDoors[business_index][door_index][bdoor_EXT_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicObject(BusinessDoors[business_index][door_index][bdoor_EXT_PICKUP_ID]);
			BusinessDoors[business_index][door_index][bdoor_EXT_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#else
		if(BusinessDoors[business_index][door_index][bdoor_EXT_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicPickup(BusinessDoors[business_index][door_index][bdoor_EXT_PICKUP_ID]);
			BusinessDoors[business_index][door_index][bdoor_EXT_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#endif

	if(BusinessDoors[business_index][door_index][bdoor_EXT_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(BusinessDoors[business_index][door_index][bdoor_EXT_AREA_ID]);
		BusinessDoors[business_index][door_index][bdoor_EXT_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(BusinessDoors[business_index][door_index][bdoor_EXT_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(BusinessDoors[business_index][door_index][bdoor_EXT_LABEL_AREA_ID]);
		BusinessDoors[business_index][door_index][bdoor_EXT_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(BusinessDoors[business_index][door_index][bdoor_INT_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(BusinessDoors[business_index][door_index][bdoor_INT_AREA_ID]);
		BusinessDoors[business_index][door_index][bdoor_INT_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(BusinessDoors[business_index][door_index][bdoor_INT_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(BusinessDoors[business_index][door_index][bdoor_INT_LABEL_AREA_ID]);
		BusinessDoors[business_index][door_index][bdoor_INT_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}

	if(BusinessDoors[business_index][door_index][bdoor_EXT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
	{
		DestroyDynamic3DTextLabel(BusinessDoors[business_index][door_index][bdoor_EXT_DEBUG_LABEL]);
		BusinessDoors[business_index][door_index][bdoor_EXT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
	}

	if(BusinessDoors[business_index][door_index][bdoor_INT_DEBUG_LABEL] != Text3D:INVALID_STREAMER_ID)
	{
		DestroyDynamic3DTextLabel(BusinessDoors[business_index][door_index][bdoor_INT_DEBUG_LABEL]);
		BusinessDoors[business_index][door_index][bdoor_INT_DEBUG_LABEL] = Text3D:INVALID_STREAMER_ID;
	}
	
	new tmp_BusinessDoors[E_BusinessDoors];
	BusinessDoors[business_index][door_index] = tmp_BusinessDoors;
	if(iter_remove) Iter_Remove(BusinessDoors[business_index], door_index);
	return 1;
}