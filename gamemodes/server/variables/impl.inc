#include <YSI\y_hooks>

hook OnScriptInit()
{
	inline OnVariablesLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				new variable_name[32];
				cache_get_value_name(i, "name", variable_name);

				if(!strcmp(variable_name, "vehicle_depreciation")) cache_get_value_float(i, "value", vehicle_depreciation);
				else if(!strcmp(variable_name, "vehicle_depreciation_kms")) cache_get_value_float(i, "value", vehicle_depreciation_kms);
				else if(!strcmp(variable_name, "vehicle_depreciation_value")) cache_get_value_float(i, "value", vehicle_depreciation_value);
				else if(!strcmp(variable_name, "vehicle_default_price")) cache_get_value_int(i, "value", vehicle_default_price);
				else if(!strcmp(variable_name, "property_depreciation")) cache_get_value_float(i, "value", property_depreciation);
				else if(!strcmp(variable_name, "business_depreciation")) cache_get_value_float(i, "value", business_depreciation);
			}
		}
		else
		{
			print("[ERROR]: No se pudo cargar en 'OnVariablesLoad' (db error)");
		}
	}
	print("[INFO]: Cargando variables...");
	mysql_tquery_inline(vcrp_db, "SELECT * FROM variables;", using inline OnVariablesLoad, "");
	return 1;
}