#include <YSI\y_hooks>

hook OnScriptInit()
{
	inline OnEntrancesLoading()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_ENTRANCES)
				{
					printf("[WARNING]: Limite 'Entrances' superado (%d)", MAX_ENTRANCES);
					break;
				}
				new bool:isnull_audio;
				cache_get_value_name(i, "name", Entrances[i][entrance_NAME], 45);
				cache_get_value_name_int(i, "radio", Entrances[i][entrance_RADIO]);
				cache_is_value_name_null(i, "audio", isnull_audio);
				if(!isnull_audio) cache_get_value_name(i, "audio", Entrances[i][entrance_AUDIO], 128);
				cache_get_value_name_int(i, "id", Entrances[i][entrance_ID]);
				cache_get_value_name_int(i, "id_entrance", Entrances[i][entrance_ID_ENTRANCE]);
				cache_get_value_name_int(i, "id_interior", Entrances[i][entrance_ID_INTERIOR]);
				cache_get_value_name_float(i, "x", Entrances[i][entrance_X]);
				cache_get_value_name_float(i, "y", Entrances[i][entrance_Y]);
				cache_get_value_name_float(i, "z", Entrances[i][entrance_Z]);
				cache_get_value_name_float(i, "angle", Entrances[i][entrance_ANGLE]);
				cache_get_value_name_int(i, "time_open", Entrances[i][entrance_TIME_OPEN]);
				cache_get_value_name_int(i, "time_close", Entrances[i][entrance_TIME_CLOSE]);
				cache_get_value_name_int(i, "mapicon_model", Entrances[i][entrance_MAPICON_MODEL]);
				cache_get_value_name_int(i, "pickup_model", Entrances[i][entrance_PICKUP_MODEL]);

				Entrances[i][entrance_SUB_ID] = 0;
				Entrances[i][entrance_SUB_ID_INDEX] = -1;
				new bool:entrance_sub_id_isnull;
				cache_is_value_name_null(i, "sub_id", entrance_sub_id_isnull);
				if(!entrance_sub_id_isnull) cache_get_value_name_int(i, "sub_id", Entrances[i][entrance_SUB_ID]);

				Entrances[i][entrance_INTERIOR_INDEX] = GetInteriorIndexByInteriorId(Entrances[i][entrance_ID_INTERIOR]);
				if(Entrances[i][entrance_INTERIOR_INDEX] == -1)
				{
					printf("[ERROR]: Error al intentar obtener índice de 'GetInteriorIndexByDoorId' en 'OnEntrancesLoading', EntranceID: %d, InteriorID: %d.\n", Entrances[i][entrance_ID], Entrances[i][entrance_ID_INTERIOR]);
					continue;
				}

				if(Entrances[i][entrance_SUB_ID] != 0)
				{
					Entrances[i][entrance_SUB_ID_INDEX] = GetInteriorIndexByInteriorId(Entrances[i][entrance_SUB_ID]);
					if(Entrances[i][entrance_SUB_ID_INDEX] == -1)
					{
						printf("[ERROR]: Error al intentar obtener índice de 'GetInteriorIndexByDoorId' en 'OnEntrancesLoading', EntranceID: %d, Sub_ID: %d.\n", Entrances[i][entrance_ID], Entrances[i][entrance_SUB_ID]);
						continue;
					}
				}

				CallRemoteFunction("OnEntranceLoad", "d", i);
				CreateEntranceInfo(i, Entrances[i][entrance_SUB_ID_INDEX]);
				Iter_Add(Entrances, i);
			}
			CallRemoteFunction("OnEntrancesLoad", "");
			printf("[OK]: Entrances cargado (%d de %d)", Iter_Count(Entrances), rows);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnEntrancesLoading' (db error)");
		}
	}
	print("[INFO]: Cargando Entrances...");
	mysql_tquery_inline(vcrp_db, "SELECT entrances.name, entrances.radio, entrances.audio, entrances_doors.* FROM entrances_doors LEFT JOIN entrances ON entrances_doors.id_entrance = entrances.id;", using inline OnEntrancesLoading, "");
	return 1;
}