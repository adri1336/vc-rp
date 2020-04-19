#include <YSI\y_hooks>

hook OnScriptInit()
{
	Iter_Init(BusinessActors);
	Iter_Init(BusinessDoors);
	Iter_Init(BProducts_Info);
	Iter_Init(BProducts);

	//load business sales points
	inline OnBusinessSalesPointsLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_BUSINESS_SALES_POINTS)
				{
					print("Limite rebasado para 'BSales_Points' en 'OnBusinessSalesPointsLoad'.");
					break;
				}

				cache_get_value_name_int(i, "id", BSales_Points[i][bsale_point_ID]);
				cache_get_value_name_int(i, "id_type", BSales_Points[i][bsale_point_ID_TYPE]);
				cache_get_value_name_float(i, "x", BSales_Points[i][bsale_point_X]);
				cache_get_value_name_float(i, "y", BSales_Points[i][bsale_point_Y]);
				cache_get_value_name_float(i, "z", BSales_Points[i][bsale_point_Z]);
				cache_get_value_name_int(i, "id_interior", BSales_Points[i][bsale_point_ID_INTERIOR]);
				BSales_Points[i][bsale_point_INDEX_INTERIOR] = GetInteriorIndexByInteriorId(BSales_Points[i][bsale_point_ID_INTERIOR]);
				if(BSales_Points[i][bsale_point_INDEX_INTERIOR] == -1)
				{
					printf("Error al obtener indice de 'GetInteriorIndexByInteriorId' en 'OnBusinessSalesPointsLoad' (ID: %d)", BSales_Points[i][bsale_point_INDEX_INTERIOR]);
					break;
				}
				Iter_Add(BSales_Points, i);
				CreateBusinessSalePointInfo(i);
			}
			printf("[OK]: business sales points (%d/%d)", Iter_Count(BSales_Points), rows);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnBusinessSalesPointsLoad' (db error)");
		}
	}
	print("[INFO]: Cargando business sales points...");
	mysql_tquery_inline(vcrp_db, "SELECT * FROM business_sales_points;", using inline OnBusinessSalesPointsLoad, "");

	//load business products info
	inline OnBProductsInfoLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_BUSINESS_PRODUCTS)
				{
					print("Limite rebasado para 'BProducts_Info' en 'OnBProductsInfoLoad'.");
					break;
				}
				cache_get_value_name_int(i, "id", BProducts_Info[i][bproduct_info_ID]);
				cache_get_value_name_int(i, "id_type", BProducts_Info[i][bproduct_info_ID_TYPE]);
				new bool:isnull_id_invitem;
				cache_is_value_name_null(i, "id_invitem", isnull_id_invitem);
				if(!isnull_id_invitem) cache_get_value_name_int(i, "id_invitem", BProducts_Info[i][bproduct_info_ID_INVITEM]);
				cache_get_value_name(i, "params", BProducts_Info[i][bproduct_info_PARAMS]);
				cache_get_value_name_int(i, "price", BProducts_Info[i][bproduct_info_PRICE]);
				cache_get_value_name_int(i, "level", BProducts_Info[i][bproduct_info_LEVEL]);
				Iter_Add(BProducts_Info, i);
			}
			printf("[OK]: business products info (%d/%d)", Iter_Count(BProducts_Info), rows);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnBProductsInfoLoad' (db error)");
		}
	}
	print("[INFO]: Cargando business products info...");
	mysql_tquery_inline(vcrp_db, "SELECT * FROM business_sales_products_info;", using inline OnBProductsInfoLoad, "");

	//load business_types_stypes
	inline OnBTypesSTypesLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= sizeof BTypes_STypes)
				{
					print("Limite rebasado para 'BTypes_STypes' en 'OnBTypesSTypesLoad'.");
					break;
				}
				cache_get_value_name_int(i, "id_business_type", BTypes_STypes[i][btype_stype_ID_BUSINESS_TYPE]);
				cache_get_value_name_int(i, "id_business_sales_type", BTypes_STypes[i][btype_stype_ID_BSALES_TYPE]);
				Iter_Add(BTypes_STypes, i);
			}
			printf("[OK]: business types stypes (%d/%d)", Iter_Count(BTypes_STypes), rows);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnBTypesSTypesLoad' (db error)");
		}
	}
	print("[INFO]: Cargando business types stypes...");
	mysql_tquery_inline(vcrp_db, "SELECT * FROM business_types_stypes;", using inline OnBTypesSTypesLoad, "");	
	
	//load business
	inline OnBusinessDataLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_BUSINESS)
				{
					print("Limite rebasado para 'BusinessData' en 'OnBusinessDataLoad'.");
					break;
				}
				cache_get_value_name_int(i, "id", BusinessData[i][bdata_ID]);
				cache_get_value_name_int(i, "id_type", BusinessData[i][bdata_ID_TYPE]);
				cache_get_value_name_int(i, "price", BusinessData[i][bdata_PRICE]);
				cache_get_value_name_int(i, "level", BusinessData[i][bdata_LEVEL]);
				cache_get_value_name_int(i, "money", BusinessData[i][bdata_MONEY]);
				cache_get_value_name_int(i, "hour_open", BusinessData[i][bdata_HOUR_OPEN]);
				cache_get_value_name_int(i, "hour_close", BusinessData[i][bdata_HOUR_CLOSE]);
				new bool:isnull_id_player;
				cache_is_value_name_null(i, "id_player", isnull_id_player);
				if(!isnull_id_player) cache_get_value_name_int(i, "id_player", BusinessData[i][bdata_ID_PLAYER]);
				cache_get_value_name_int(i, "radio", BusinessData[i][bdata_RADIO]);
				new bool:isnull_name;
				cache_is_value_name_null(i, "name", isnull_name);
				if(!isnull_name) cache_get_value_name(i, "name", BusinessData[i][bdata_PLAYER_NAME]);
				else BusinessData[i][bdata_PLAYER_NAME][0] = EOS;
				Iter_Add(BusinessData, i);
				//door
				inline OnBusinessDoorLoad()
				{
					new x_rows;
					if(cache_get_row_count(x_rows))
					{
						for(new j = 0; j != x_rows; j ++)
						{
							if(j >= MAX_DOORS_PER_BUSINESS)
							{
								printf("Limite rebasado para 'BusinessDoors' en 'OnBusinessDoorLoad' (ID: %d).", BusinessData[i][bdata_ID]);
								break;
							}
							//data
							cache_get_value_name_int(j, "id", BusinessDoors[i][j][bdoor_ID]);
							cache_get_value_name_int(j, "id_business", BusinessDoors[i][j][bdoor_ID_BUSINESS]);
							cache_get_value_name_int(j, "closed", BusinessDoors[i][j][bdoor_CLOSED]);
							cache_get_value_name_float(j, "ext_x", BusinessDoors[i][j][bdoor_EXT_X]);
							cache_get_value_name_float(j, "ext_y", BusinessDoors[i][j][bdoor_EXT_Y]);
							cache_get_value_name_float(j, "ext_z", BusinessDoors[i][j][bdoor_EXT_Z]);
							cache_get_value_name_float(j, "ext_angle", BusinessDoors[i][j][bdoor_EXT_ANGLE]);
							new bool:isnull_ext_entrance_door_id, bool:isnull_ext_sub_id;
							cache_is_value_name_null(j, "ext_entrance_door_id", isnull_ext_entrance_door_id);
							if(!isnull_ext_entrance_door_id) cache_get_value_name_int(j, "ext_entrance_door_id", BusinessDoors[i][j][bdoor_EXT_ENTRANCE_DOOR_ID]);
							cache_is_value_name_null(j, "ext_sub_id", isnull_ext_sub_id);
							if(!isnull_ext_sub_id) cache_get_value_name_int(j, "ext_sub_id", BusinessDoors[i][j][bdoor_EXT_SUB_ID]);
							cache_get_value_name_int(j, "id_interior", BusinessDoors[i][j][bdoor_ID_INTERIOR]);
							//indexs
							BusinessDoors[i][j][bdoor_EXT_ENTRANCE_DOOR_INDEX] = -1;
							BusinessDoors[i][j][bdoor_EXT_SUB_INDEX] = -1;
							BusinessDoors[i][j][bdoor_INDEX_INTERIOR] = -1;
							BusinessDoors[i][j][bdoor_INDEX_BUSINESS] = i;
							if(BusinessDoors[i][j][bdoor_EXT_ENTRANCE_DOOR_ID] > 0)
							{
								BusinessDoors[i][j][bdoor_EXT_ENTRANCE_DOOR_INDEX] = GetEntranceIndexByEntranceDId(BusinessDoors[i][j][bdoor_EXT_ENTRANCE_DOOR_ID]);
								if(BusinessDoors[i][j][bdoor_EXT_ENTRANCE_DOOR_INDEX] == -1)
								{
									printf("Error al obtener indice de 'GetEntranceIndexByEntranceDId' en 'OnBusinessDoorLoad' (ID: %d)", BusinessDoors[i][j][bdoor_EXT_ENTRANCE_DOOR_ID]);
									break;
								}
							}
							if(BusinessDoors[i][j][bdoor_EXT_SUB_ID] > 0)
							{
								BusinessDoors[i][j][bdoor_EXT_SUB_INDEX] = GetBusinessDoorIndexFromId(i, BusinessDoors[i][j][bdoor_EXT_SUB_ID]);
								if(BusinessDoors[i][j][bdoor_EXT_SUB_INDEX] == -1)
								{
									printf("Error al obtener indice de 'GetBusinessDoorIndexFromId' en 'OnBusinessDoorLoad' (ID: %d)", BusinessDoors[i][j][bdoor_EXT_SUB_ID]);
									break;
								}
							}
							BusinessDoors[i][j][bdoor_INDEX_INTERIOR] = GetInteriorIndexByInteriorId(BusinessDoors[i][j][bdoor_ID_INTERIOR]);
							if(BusinessDoors[i][j][bdoor_INDEX_INTERIOR] == -1)
							{
								printf("Error al obtener indice de 'GetInteriorIndexByInteriorId' en 'OnBusinessDoorLoad' (ID: %d)", BusinessDoors[i][j][bdoor_ID_INTERIOR]);
								break;
							}
							Iter_Add(BusinessDoors[i], j);
							CreateBusinessDoorInfo(i, j);
						}
					}
				}
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM business_doors WHERE id_business = %d;", BusinessData[i][bdata_ID]);
				mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnBusinessDoorLoad, "");
				//products
				if(IsBusinessOccupied(i))
				{
					inline OnBusinessProductsLoad()
					{
						new x_rows;
						if(cache_get_row_count(x_rows))
						{
							for(new j = 0; j != x_rows; j ++)
							{
								if(j >= MAX_PRODUCTS_PER_BUSINESS)
								{
									printf("Limite rebasado para 'BProducts' en 'OnBusinessProductsLoad' (ID: %d).", BusinessData[i][bdata_ID]);
									break;
								}
								//data
								cache_get_value_name_int(j, "id_product", BProducts[i][j][bproduct_ID_PRODUCT]);
								cache_get_value_name_int(j, "id_business", BProducts[i][j][bproduct_ID_BUSINESS]);
								cache_get_value_name_int(j, "price", BProducts[i][j][bproduct_PRICE]);
								cache_get_value_name_int(j, "stock", BProducts[i][j][bproduct_STOCK]);
								BProducts[i][j][bproduct_INDEX_PRODUCT] = GetProductInfoIndexById(BProducts[i][j][bproduct_ID_PRODUCT]);
								if(BProducts[i][j][bproduct_INDEX_PRODUCT] == -1)
								{
									printf("Error al obtener indice de 'GetProductInfoIndexById' en 'OnBusinessProductsLoad' (ID: %d)", BProducts[i][j][bproduct_ID_PRODUCT]);
									break;
								}
								Iter_Add(BProducts[i], j);
							}
						}
					}
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM business_sales_products WHERE id_business = %d;", BusinessData[i][bdata_ID]);
					mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnBusinessProductsLoad, "");
				}
				else ResetBusinessProducts(i);
			}
			printf("[OK]: business cargado (%d/%d)", Iter_Count(BusinessData), rows);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnBusinessDataLoad' (db error)");
		}	
	}
	print("[INFO]: Cargando business...");
	mysql_tquery_inline(vcrp_db, "SELECT business.*, player.name FROM business LEFT JOIN player ON business.id_player = player.id;", using inline OnBusinessDataLoad, "");
	return 1;
}

hook OnActorLoaded(index)
{
	if(ActorInfo[index][actor_BUSINESS])
	{
		new business_index = ActorInfo[index][actor_EXTRA_INDEX];
		new actor_index = Iter_Free(BusinessActors[business_index]);
		if(actor_index != cellmin)
		{
			BusinessActors[business_index][actor_index] = index;
			Iter_Add(BusinessActors[business_index], actor_index);
		}
	}
	return 1;
}