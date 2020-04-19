#include <YSI\y_hooks>

hook OnScriptInit()
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				new id_type, area_type[24], Float:x, Float:y, Float:z, Float:size, Float:max_x, Float:max_y,
					bool:isnull_max_x, bool:isnull_max_y;

				cache_get_value_name_int(i, "id_type", id_type);
				cache_get_value_name(i, "area_type", area_type);
				cache_get_value_name_float(i, "x", x);
				cache_get_value_name_float(i, "y", y);
				cache_get_value_name_float(i, "z", z);
				cache_get_value_name_float(i, "size", size);
				cache_is_value_name_null(i, "max_x", isnull_max_x);
				if(!isnull_max_x) cache_get_value_name_float(i, "max_x", max_x);
				cache_is_value_name_null(i, "max_y", isnull_max_y);
				if(!isnull_max_x) cache_get_value_name_float(i, "max_y", max_y);
				//area
				new streamer_info[2], areaid;
				if(!strcmp(area_type, "cylinder")) areaid = CreateDynamicCylinder(x, y, z - size, z + size, size);
				else if(!strcmp(area_type, "cuboid")) areaid = CreateDynamicCuboid(x, y, z - size, max_x, max_y, z + size);
				if(areaid != INVALID_STREAMER_ID)
				{
					streamer_info[0] = _:AREA_TYPE_ENV_AREA;
					streamer_info[1] = id_type;
					Streamer_SetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, streamer_info);
				}
			}
		}
	}
	mysql_tquery_inline(vcrp_db, "SELECT * FROM env_areas;", using inline OnQueryLoad, "");
	return 1;
}