UpdatePlayerVcMdlPreviewObject(playerid)
{
	if(current_mdlpreview_object[playerid] != INVALID_OBJECT_ID)
	{
		DestroyPlayerObject(playerid, current_mdlpreview_object[playerid]);
		current_mdlpreview_object[playerid] = INVALID_OBJECT_ID;
	}

	current_mdlpreview_object[playerid] = CreatePlayerObject(playerid, current_mdlpreview_mdl[playerid], mdlpreview_pos[0], mdlpreview_pos[1], mdlpreview_pos[2], 0.0, 0.0, 0.0, 1000.0);
	return 1;
}

UpdatePlayerVcMdlPreviewTds(playerid, modelid, type[])
{
	new td_str[12];
	format(td_str, sizeof td_str, "%d", modelid);
	PlayerTextDrawSetString(playerid, mdlpreview_ptd[playerid][0], td_str);
	PlayerTextDrawSetString(playerid, mdlpreview_ptd[playerid][1], type);
	return 1;
}

UpdateTotalNullModelidsTd()
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			new total, td_str[12];
			cache_get_value_index_int(0, 0, total);
			format(td_str, sizeof td_str, "%d", total);
			TextDrawSetString(mdlpreview_td[2], td_str);
		}
	}
	mysql_tquery_inline(vc_map_db, "SELECT COUNT(*) FROM models_type WHERE type IS NULL;", using inline OnQueryLoad, "");
	return 1;
}