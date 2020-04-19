#include <YSI\y_hooks>

hook OnScriptInit()
{
	inline OnInvItemsTypesLoad()
	{
		new rows, count;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				new id;
				cache_get_value_name_int(i, "id", id);
				
				if(id < 1 || id >= _:INV_ITEMS_TYPES)
				{
					printf("[ERROR]: OnInvItemsTypesLoad, id fuera de límites (id: %d, array: %d).", id, _:INV_ITEMS_TYPES);
					break;
				}

				INV_ITEMS_TYPES_Info[id][inv_item_type_MULTIPLIABLE] = 0;
				INV_ITEMS_TYPES_Info[id][inv_item_type_MAX_MULTIPLIED] = 0;
				INV_ITEMS_TYPES_Info[id][inv_item_type_UNIQUE] = 0;
				cache_get_value_name_int(i, "multipliable", INV_ITEMS_TYPES_Info[id][inv_item_type_MULTIPLIABLE]);
				cache_get_value_name_int(i, "max_multiplied", INV_ITEMS_TYPES_Info[id][inv_item_type_MAX_MULTIPLIED]);
				cache_get_value_name_int(i, "inv_unique", INV_ITEMS_TYPES_Info[id][inv_item_type_UNIQUE]);

				count ++;
			}
			printf("[OK]: INV_ITEMS_TYPES cargado (%d de %d)", count, rows);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnInvItemsTypesLoad' (db error)");
		}
	}
	print("[INFO]: Cargando INV_ITEMS_TYPES...");
	mysql_tquery_inline(vcrp_db, "SELECT * FROM inv_items_types;", using inline OnInvItemsTypesLoad, "");
	
	//
	inline OnInvItemsLoad()
	{
		new rows, count;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				new id;
				cache_get_value_name_int(i, "id", id);
				
				if(id < 1 || id >= _:INV_ITEMS)
				{
					printf("[ERROR]: OnInvItemsLoad, id fuera de límites (id: %d, array: %d).", id, _:INV_ITEMS);
					break;
				}

				INV_ITEMS_Info[id][inv_item_TYPE] = 0;
				INV_ITEMS_Info[id][inv_item_ICON_NAME][0] = EOS;
				cache_get_value_name_int(i, "type", INV_ITEMS_Info[id][inv_item_TYPE]);
				cache_get_value_name(i, "icon_name", INV_ITEMS_Info[id][inv_item_ICON_NAME], 32);

				count ++;
			}
			printf("[OK]: INV_ITEMS cargado (%d de %d)", count, rows);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnInvItemsLoad' (db error)");
		}
	}
	print("[INFO]: Cargando INV_ITEMS...");
	mysql_tquery_inline(vcrp_db, "SELECT * FROM inv_items;", using inline OnInvItemsLoad, "");
	return 1;
}