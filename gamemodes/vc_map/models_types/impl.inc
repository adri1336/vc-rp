#include <YSI\y_hooks>

hook OnScriptInit()
{
	inline OnVCModelsTypesLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_VC_MODELS_TYPES)
				{
					printf("[WARNING]: Limite 'Vc_Models_Types' superado (%d)", MAX_VC_MODELS_TYPES);
					break;
				}

				cache_get_value_name_int(i, "id", Vc_Models_Types[i][vc_model_type_ID]);
				cache_get_value_name(i, "name", Vc_Models_Types[i][vc_model_type_NAME]);
				cache_get_value_float(i, "stream_distance", Vc_Models_Types[i][vc_model_type_STREAM_DISTANCE]);
				cache_get_value_name_int(i, "priority", Vc_Models_Types[i][vc_model_type_PRIORITY]);
				Iter_Add(Vc_Models_Types, i);
			}
			printf("[OK]: 'Vc_Models_Types' cargado (%d/%d)", Iter_Count(Vc_Models_Types), MAX_VC_MODELS_TYPES);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnVCModelsTypesLoad' (db error)");
		}
	}
	print("[INFO]: Cargando models_types VC...");
	mysql_tquery_inline(vc_map_db, "SELECT * FROM models_types;", using inline OnVCModelsTypesLoad, "");
	return 1;
}