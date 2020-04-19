#include <YSI\y_hooks>

hook OnScriptInit()
{
	Iter_Init(GPS_Sites);
	inline OnGpsCategoriesLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_GPS_CATEGORIES)
				{
					printf("[WARNING]: Limite en 'GPS_Cat' superado (%d)", MAX_GPS_CATEGORIES);
					break;
				}
				cache_get_value_name_int(i, "id", GPS_Cat[i][gps_cat_ID]);
				cache_get_value_name(i, "name", GPS_Cat[i][gps_cat_NAME], 24);
				cache_get_value_name(i, "icon", GPS_Cat[i][gps_cat_ICON], 32);
				//load sites
				inline OnGpsCategorySitesLoad()
				{
					new rows2;
					if(cache_get_row_count(rows2))
					{
						for(new j = 0; j < rows2; j ++)
						{
							if(j >= MAX_GPS_SITES_PER_CATEGORY)
							{
								printf("[WARNING]: Limite en 'GPS_Sites' superado (%d)", MAX_GPS_SITES_PER_CATEGORY);
								break;
							}
							cache_get_value_name_int(j, "id", GPS_Sites[i][j][gps_site_ID]);
							cache_get_value_name_float(j, "x", GPS_Sites[i][j][gps_site_X]);
							cache_get_value_name_float(j, "y", GPS_Sites[i][j][gps_site_Y]);
							cache_get_value_name_float(j, "z", GPS_Sites[i][j][gps_site_Z]);
							cache_get_value_name_int(j, "cat_id", GPS_Sites[i][j][gps_site_CAT_ID]);
							new bool:isnull_icon;
							cache_is_value_name_null(j, "icon", isnull_icon);
							if(!isnull_icon) cache_get_value_name(j, "icon", GPS_Sites[i][j][gps_site_ICON]);
							Iter_Add(GPS_Sites[i], j);
						}
					}
				}
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM gps_sites WHERE cat_id = %d;", GPS_Cat[i][gps_cat_ID]);
				mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnGpsCategorySitesLoad, "");
				//fin
				Iter_Add(GPS_Cat, i);
			}
			printf("[OK]: Gps_cat cargado (%d)", Iter_Count(GPS_Cat), rows);
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnGpsCategoriesLoad' (db error)");
		}
	}
	print("[INFO]: Cargando Gps_cat...");
	mysql_tquery_inline(vcrp_db, "SELECT * FROM gps_cat;", using inline OnGpsCategoriesLoad, "");
	return 1;
}