#include <YSI\y_hooks>

hook OnScriptInit()
{
	inline OnInteriorsLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_INTERIORS)
				{
					printf("[WARNING]: Limite 'Interiors' superado (%d)", MAX_INTERIORS);
					break;
				}

				cache_get_value_name_int(i, "id", Interiors[i][interior_ID]);
				cache_get_value_name(i, "name", Interiors[i][interior_NAME], 45);
				cache_get_value_name_int(i, "interiorid", Interiors[i][interior_INTERIORID]);
				cache_get_value_name_float(i, "x", Interiors[i][interior_X]);
				cache_get_value_name_float(i, "y", Interiors[i][interior_Y]);
				cache_get_value_name_float(i, "z", Interiors[i][interior_Z]);
				cache_get_value_name_float(i, "angle", Interiors[i][interior_ANGLE]);
				Iter_Add(Interiors, i);
			}
			printf("[OK]: Interiors cargado (%d de %d)", Iter_Count(Interiors), rows);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnInteriorsLoad' (db error)");
		}
	}
	print("[INFO]: Cargando Interiors...");
	mysql_tquery_inline(vcrp_db, "SELECT * FROM interiors;", using inline OnInteriorsLoad, "");
	return 1;
}