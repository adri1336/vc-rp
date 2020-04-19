stock IsValidGpsCatId(cat_id)
{
	foreach(new i : GPS_Cat)
	{
		if(GPS_Cat[i][gps_cat_ID] == cat_id)
		{
			return 1;
		}
	}
	return 0;
}

stock IsValidGpsSiteId(site_id)
{
	foreach(new i : GPS_Cat)
	{
		foreach(new j : GPS_Sites[i])
		{
			if(GPS_Sites[i][j][gps_site_ID] == site_id)
			{
				return 1;
			}
		}
	}
	return 0;
}

stock GetGpsCatIndexById(cat_id)
{
	foreach(new i : GPS_Cat)
	{
		if(GPS_Cat[i][gps_cat_ID] == cat_id)
		{
			return i;
		}
	}
	return -1;	
}

stock DeleteGpsCatIndex(cat_index, bool:update = false)
{
	if(update)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM gps_cat WHERE id = %d;", GPS_Cat[cat_index][gps_cat_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}
	Iter_Clear(GPS_Sites[cat_index]);
	Iter_Remove(GPS_Cat, cat_index);
	return 1;
}

stock DeleteGpsSiteId(site_id, bool:update = false)
{
	foreach(new i : GPS_Cat)
	{
		foreach(new j : GPS_Sites[i])
		{
			if(GPS_Sites[i][j][gps_site_ID] == site_id)
			{
				if(update)
				{
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM gps_sites WHERE id = %d;", GPS_Sites[i][j][gps_site_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER);
				}
				new prev;
				Iter_SafeRemove(GPS_Sites[i], j, prev); 
				j = prev;
				return 1;
			}
		}
	}
	return 0;
}