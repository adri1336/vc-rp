#include <YSI\y_hooks>

hook OnScriptInit()
{
	Iter_Init(PropertyDoor);
	return 1;
}

hook OnEntrancesLoad()
{
	inline OnPropertiesLoading()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_PROPERTIES)
				{
					printf("[WARNING]: Limite 'PropertyInfo' superado (%d)", MAX_PROPERTIES);
					break;
				}
				new bool:isnull_id_player, bool:isnull_rent_expire_date, bool:isnull_name;
				cache_get_value_name_int(i, "id", PropertyInfo[i][property_ID]);
				cache_get_value_name_int(i, "price", PropertyInfo[i][property_PRICE]);
				cache_get_value_name_int(i, "level", PropertyInfo[i][property_LEVEL]);
				cache_get_value_name_int(i, "rent", PropertyInfo[i][property_RENT]);
				cache_is_value_name_null(i, "rent_expire_date", isnull_rent_expire_date);
				if(!isnull_rent_expire_date) cache_get_value_name(i, "rent_expire_date", PropertyInfo[i][property_RENT_EXPIRE_DATE]);
				cache_is_value_name_null(i, "id_player", isnull_id_player);
				if(!isnull_id_player) cache_get_value_name_int(i, "id_player", PropertyInfo[i][property_ID_PLAYER]);
				cache_is_value_name_null(i, "name", isnull_name);
				if(!isnull_name) cache_get_value_name(i, "name", PropertyInfo[i][property_PLAYER_NAME]);
				Iter_Add(PropertyInfo, i);

				//door
				inline OnPropertyDoorsLoad()
				{
					if(cache_get_row_count(rows))
					{
						for(new x = 0; x != rows; x ++)
						{
							if(x >= MAX_PROPERTIES_DOORS)
							{
								printf("[WARNING]: Limite 'PropertyDoor' superado (max: %d, id_property: %d)", MAX_PROPERTIES_DOORS, PropertyInfo[i][property_ID]);
								break;
							}
							new bool:isnull_ext_entrance_door_id, bool:isnull_ext_sub_id;
							cache_get_value_name_int(x, "id", PropertyDoor[i][x][prop_door_ID]);
							cache_get_value_name_int(x, "id_property", PropertyDoor[i][x][prop_door_ID_PROPERTY]);
							cache_get_value_name_int(x, "closed", PropertyDoor[i][x][prop_door_CLOSED]);
							cache_get_value_name_float(x, "ext_x", PropertyDoor[i][x][prop_door_EXT_X]);
							cache_get_value_name_float(x, "ext_y", PropertyDoor[i][x][prop_door_EXT_Y]);
							cache_get_value_name_float(x, "ext_z", PropertyDoor[i][x][prop_door_EXT_Z]);
							cache_get_value_name_float(x, "ext_angle", PropertyDoor[i][x][prop_door_EXT_ANGLE]);
							cache_is_value_name_null(x, "ext_entrance_door_id", isnull_ext_entrance_door_id);
							if(!isnull_ext_entrance_door_id) cache_get_value_name_int(x, "ext_entrance_door_id", PropertyDoor[i][x][prop_door_EXT_ENTRANCE_DOOR_ID]);
							cache_is_value_name_null(x, "ext_sub_id", isnull_ext_sub_id);
							if(!isnull_ext_sub_id) cache_get_value_name_int(x, "ext_sub_id", PropertyDoor[i][x][prop_door_EXT_SUB_ID]);
							cache_get_value_name_int(x, "id_interior", PropertyDoor[i][x][prop_door_ID_INTERIOR]);
							PropertyDoor[i][x][prop_door_ID_INTERIOR_INDEX] = GetInteriorIndexByInteriorId(PropertyDoor[i][x][prop_door_ID_INTERIOR]);
							if(PropertyDoor[i][x][prop_door_ID_INTERIOR_INDEX] == -1)
							{
								printf("[ERROR]: Error al obtener índice de 'GetInteriorIndexByInteriorId' de 'OnPropertyDoorsLoad' (ID: %d)", PropertyDoor[i][x][prop_door_ID]);
								break;
							}

							if(PropertyDoor[i][x][prop_door_EXT_ENTRANCE_DOOR_ID]) PropertyDoor[i][x][prop_door_EXT_ENTR_DOOR_INDEX] = GetEntranceIndexByEntranceDId(PropertyDoor[i][x][prop_door_EXT_ENTRANCE_DOOR_ID]);
							else PropertyDoor[i][x][prop_door_EXT_ENTR_DOOR_INDEX] = -1;

							if(PropertyDoor[i][x][prop_door_EXT_SUB_ID]) PropertyDoor[i][x][prop_door_EXT_SUB_INDEX] = GetPropertyDoorIndexFromId(i, PropertyDoor[i][x][prop_door_EXT_SUB_ID]);
							else PropertyDoor[i][x][prop_door_EXT_SUB_INDEX] = -1;

							Iter_Add(PropertyDoor[i], x);
							CreatePropertyDoorInfo(i, x);
						}
					}
					else
					{
						printf("[ERROR]: No se pudo cargar en 'OnPropertyDoorsLoad' (db error, id_property: %d)", PropertyInfo[i][property_ID]);
					}
				}

				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM properties_doors WHERE id_property = %d;", PropertyInfo[i][property_ID]);
				mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnPropertyDoorsLoad, "");
			}
			CallRemoteFunction("OnPropertiesLoad", "");
			printf("[OK]: PropertyInfo cargado (%d de %d)", Iter_Count(PropertyInfo), rows);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnPropertiesLoading' (db error)");
		}
	}
	print("[INFO]: Cargando properties...");
	mysql_tquery_inline(vcrp_db, "SELECT properties.*, player.name FROM properties LEFT JOIN player ON properties.id_player = player.id;", using inline OnPropertiesLoading, "");
	return 1;
}

task OnRentPropertiesCheck[CHECK_RENT_PROPERTIES_INTERVAL]()
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				new pid;
				cache_get_value_index_int(i, 0, pid);
				new pindex = GetPropertyIndexFromId(pid);
				if(pindex != -1)
				{
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties SET id_player = NULL WHERE id = %d;", PropertyInfo[pindex][property_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER);

					PropertyInfo[pindex][property_ID_PLAYER] = 0;
					PropertyInfo[pindex][property_PLAYER_NAME][0] = EOS;

					DeletePropertyKeys(PropertyInfo[pindex][property_ID], true, pindex);
				}
			}
		}
	}
	mysql_tquery_inline(vcrp_db, "SELECT id FROM properties WHERE rent = 1 AND id_player IS NOT NULL AND NOW() > rent_expire_date;", using OnQueryLoad, "");
}