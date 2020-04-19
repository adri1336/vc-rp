#include <YSI\y_hooks>

hook OnScriptInit()
{
	inline OnViceCityObjectsLoad()
	{
		new rows, objects;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(objects >= MAX_VC_OBJECTS)
				{
					printf("[WARNING]: Limite 'Vc_Objects' superado (%d)", MAX_VC_OBJECTS);
					break;
				}

				new id, modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, world, interior, type, bool:type_isnull;
				cache_get_value_name_int(i, "id", id);
				cache_get_value_name_int(i, "modelid", modelid);
				cache_get_value_name_float(i, "x", x);
				cache_get_value_name_float(i, "y", y);
				cache_get_value_name_float(i, "z", z);
				cache_get_value_name_float(i, "rx", rx);
				cache_get_value_name_float(i, "ry", ry);
				cache_get_value_name_float(i, "rz", rz);
				cache_get_value_name_int(i, "world", world);
				cache_get_value_name_int(i, "interior", interior);
				cache_is_value_name_null(i, "type", type_isnull);
				if(!type_isnull) cache_get_value_name_int(i, "type", type);
				//
				CreateVCObject(id, modelid, x, y, z, rx, ry, rz, world, interior, type, i);
				objects ++;
			}
			printf("[OK]: VICE CITY OBJECTS cargado (%d de %d objetos, MAX: %d)", objects, rows, MAX_VC_OBJECTS);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnViceCityObjectsLoad' (db error)");
		}
	}
	print("[INFO]: Cargando VICE CITY OBJECTS...");
	mysql_tquery_inline(vc_map_db, "SELECT objects.*, models_type.type FROM objects INNER JOIN models_type on objects.modelid = models_type.modelid WHERE objects.enabled = '1';", using inline OnViceCityObjectsLoad, "");
	return 1;
}

public OnPlayerViceCityObjectAdding(playerid, modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, world, interior)
{
	new index = Iter_Free(Vc_Objects);
	CreateVCObject(cache_insert_id(), modelid, x, y, z, rx, ry, rz, world, interior, 0, index);
	CallRemoteFunction("OnPlayerViceCityObjectAdded", "id", playerid, index);

	//
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			if(rows)
			{
				new bool:is_null;
				cache_is_value_name_null(0, "type", is_null);

				if(!is_null)
				{
					new type, type_index = -1;
					cache_get_value_name_int(0, "type", type);
					type_index = GetVCModelTypeIndexById(type);
					if(type_index != -1) SetVcObjectModelType(index, type_index);
				}
			}
			else
			{
				mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO models_type (modelid) VALUES ('%d');", modelid);
				mysql_tquery(vc_map_db, QUERY_BUFFER, "", "");
			}
		}
	}

	mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM models_type WHERE modelid = '%d';", modelid);
	mysql_tquery_inline(vc_map_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	return 1;
}