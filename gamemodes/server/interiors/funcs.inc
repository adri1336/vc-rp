stock GetInteriorIndexByInteriorId(id)
{
	foreach(new i : Interiors)
	{
		if(Interiors[i][interior_ID] == id)
		{
			return i;
		}
	}
	return -1;
}

stock IsValidInteriorIndex(index)
{
	if(Iter_Contains(Interiors, index))
	{
		return 1;
	}
	return 0;
}

DeleteInterior(index, bool:db = false)
{
	if(db)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM interiors WHERE id = %d;", Interiors[index][interior_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}

	//label
	if(Interiors[index][interior_INFO_LABEL] != Text3D:INVALID_STREAMER_ID)
	{
		DestroyDynamic3DTextLabel(Interiors[index][interior_INFO_LABEL]);
		Interiors[index][interior_INFO_LABEL] = Text3D:INVALID_STREAMER_ID;
	}
	//var
	new tmp_Interiors[enum_Interiors];
	Interiors[index] = tmp_Interiors;
	//array
	Iter_Remove(Interiors, index);
	return 1;
}