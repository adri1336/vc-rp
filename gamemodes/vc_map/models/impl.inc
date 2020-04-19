#include <YSI\y_hooks>

hook OnScriptInit()
{
	inline OnViceCityCustomModelsLoad()
	{
		new rows, count;
		if(cache_get_row_count(rows))
		{
			new Vice_City_Dffpath[128], Vice_City_Txdpath[128];
			for(new i = 0; i != rows; i ++)
			{
				new flags, newmodelid, dffname[64], txdname[64], timeon, timeoff,
					bool:timeon_isnull, bool:timeoff_isnull;
				cache_get_value_name_int(i, "flags", flags);
				cache_get_value_name_int(i, "newmodelid", newmodelid);
				cache_get_value_name(i, "dffname", dffname);
				cache_get_value_name(i, "txdname", txdname);

				cache_is_value_name_null(i, "timeon", timeon_isnull);
				if(!timeon_isnull) cache_get_value_name_int(i, "timeon", timeon);
				cache_is_value_name_null(i, "timeoff", timeoff_isnull);
				if(!timeoff_isnull) cache_get_value_name_int(i, "timeoff", timeoff);

				format(Vice_City_Dffpath, 128, "%s%s", VICE_CITY_PATH, dffname);
				format(Vice_City_Txdpath, 128, "%s%s", VICE_CITY_PATH, txdname);
								
				AddVC2SASimpleObject(flags, newmodelid, Vice_City_Dffpath, Vice_City_Txdpath, timeon, timeoff);
				count ++;
			}
			printf("[OK]: VICE CITY CUSTOM MODELS cargado (%d de %d)", count, rows);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnViceCityCustomModelsLoad' (db error)");
		}
	}
	print("[INFO]: Cargando VICE CITY CUSTOM MODELS...");
	mysql_tquery_inline(vc_map_db, "SELECT * FROM models;", using inline OnViceCityCustomModelsLoad, "");
	return 1;
}