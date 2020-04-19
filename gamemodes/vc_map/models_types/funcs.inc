GetVCModelTypeIndexById(id)
{
	foreach(new i : Vc_Models_Types)
	{
		if(Vc_Models_Types[i][vc_model_type_ID] == id)
		{
			return i;
		}
	}
	return -1;
}

SetVcModelTypeSsAndPriority(index, Float:ss, priority, bool:update = false)
{
	if(!Iter_Contains(Vc_Models_Types, index)) return 0;
	if(!Vc_Models_Types[index][vc_model_type_ID]) return 0;

	Vc_Models_Types[index][vc_model_type_STREAM_DISTANCE] = ss;
	Vc_Models_Types[index][vc_model_type_PRIORITY] = priority;

	if(update)
	{
		mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE models_types SET stream_distance = '%f', priority = '%d' WHERE id = '%d';", ss, priority, Vc_Models_Types[index][vc_model_type_ID]);
		mysql_tquery(vc_map_db, QUERY_BUFFER, "", "");
	}
	return 1;
}