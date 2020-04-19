#include <YSI\y_hooks>

YCMD:igpscats(playerid, params[], help)
{
	new string[145];
	format(string, sizeof string, "Gps cats: %d, max: %d", Iter_Count(GPS_Cat), MAX_GPS_CATEGORIES);
	SendClientMessage(playerid, -1, string);
	return 1;
}

YCMD:gpscats(playerid, params[], help)
{
	new string[145];
	foreach(new i : GPS_Cat)
	{
		format(string, sizeof string, "GPS Cat ID: %d, Name: %s, Icon: %s", GPS_Cat[i][gps_cat_ID], GPS_Cat[i][gps_cat_NAME], GPS_Cat[i][gps_cat_ICON]);
		SendClientMessage(playerid, -1, string);
	}
	return 1;
}

YCMD:igpssites(playerid, params[], help)
{
	new gps_cat;
	if(!sscanf(params, "d", gps_cat))
	{
		new gps_cat_index = GetGpsCatIndexById(gps_cat);
		if(gps_cat_index != -1)
		{
			new string[145];
			format(string, sizeof string, "Gps sites: %d, max: %d", Iter_Count(GPS_Sites[gps_cat_index]), MAX_GPS_SITES_PER_CATEGORY);
			SendClientMessage(playerid, -1, string);
		}
		else SendClientMessage(playerid, -1, "Invalid ID!");
	}
	else SendClientMessage(playerid, -1, "Syntax: /gpssites <ID>");
	return 1;
}

YCMD:gpssites(playerid, params[], help)
{
	new gps_cat;
	if(!sscanf(params, "d", gps_cat))
	{
		new gps_cat_index = GetGpsCatIndexById(gps_cat);
		if(gps_cat_index != -1)
		{
			new string[145];
			foreach(new i : GPS_Sites[gps_cat_index])
			{
				format(string, sizeof string, "ID: %d, X: %f, Y: %f, Z: %f", GPS_Sites[gps_cat_index][i][gps_site_ID], GPS_Sites[gps_cat_index][i][gps_site_X], GPS_Sites[gps_cat_index][i][gps_site_Y], GPS_Sites[gps_cat_index][i][gps_site_Z]);
				SendClientMessage(playerid, -1, string);
			}
		}
		else SendClientMessage(playerid, -1, "Invalid ID!");
	}
	else SendClientMessage(playerid, -1, "Syntax: /gpssites <ID>");
	return 1;
}

YCMD:ggpssite(playerid, params[], help)
{
	new site_id;
	if(!sscanf(params, "d", site_id))
	{
		foreach(new i : GPS_Cat)
		{
			foreach(new j : GPS_Sites[i])
			{
				if(GPS_Sites[i][j][gps_site_ID] == site_id)
				{
					PI[playerid][pi_X] = GPS_Sites[i][j][gps_site_X];
					PI[playerid][pi_Y] = GPS_Sites[i][j][gps_site_Y];
					PI[playerid][pi_Z] = GPS_Sites[i][j][gps_site_Z];
					PI[playerid][pi_ANGLE] = 0.0;
					PI[playerid][pi_INTERIORID] = 0;
					PI[playerid][pi_WORLDID] = VC_WORLD;
					SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
					SetPlayerPosEx(playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], PI[playerid][pi_INTERIORID], PI[playerid][pi_WORLDID], true);
					return 1;
				}
			}
		}
		SendClientMessage(playerid, -1, "Invalid ID!");
	}
	else SendClientMessage(playerid, -1, "Syntax: /ggpssite <ID>");
	return 1;
}

YCMD:agpscat(playerid, params[], help)
{
	new name[24], icon[32];
	if(!sscanf(params, "s[24]s[32]", name, icon))
	{
		new index = Iter_Free(GPS_Cat);
		if(index == cellmin) SendClientMessage(playerid, -1, "Array full!");
		else
		{
			inline OnGpsCatInserted(string:cat_name[], string:cat_icon[])
			{
				GPS_Cat[index][gps_cat_ID] = cache_insert_id();
				format(GPS_Cat[index][gps_cat_NAME], 24, "%s", cat_name);
				format(GPS_Cat[index][gps_cat_ICON], 32, "%s", cat_icon);
				Iter_Add(GPS_Cat, index);

				new msg[128];
				format(msg, sizeof msg, "GPS Cat added (ID: %d)", GPS_Cat[index][gps_cat_ID]);
				SendClientMessage(playerid, -1, msg);
			}
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO gps_cat (name, icon) VALUES ('%e', '%e');", name, icon);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnGpsCatInserted, "ss", name, icon);
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /agpscat <name> <icon>");
	return 1;
}

YCMD:dgpscat(playerid, params[], help)
{
	new gps_cat;
	if(!sscanf(params, "d", gps_cat))
	{
		new gps_cat_index = GetGpsCatIndexById(gps_cat);
		if(gps_cat_index != -1)
		{
			DeleteGpsCatIndex(gps_cat_index, true);
			SendClientMessage(playerid, -1, "GPS Cat deleted!");
		}
		else SendClientMessage(playerid, -1, "Invalid ID!");
	}
	else SendClientMessage(playerid, -1, "Syntax: /dgpscat <ID>");
	return 1;
}

YCMD:agpssite(playerid, params[], help)
{
	new gps_cat;
	if(!sscanf(params, "d", gps_cat))
	{
		new gps_cat_index = GetGpsCatIndexById(gps_cat);
		if(gps_cat_index != -1)
		{
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
			new index = Iter_Free(GPS_Sites[gps_cat_index]);
			if(index == cellmin) SendClientMessage(playerid, -1, "Array full!");
			else
			{
				inline OnGpsSiteInserted()
				{
					GPS_Sites[gps_cat_index][index][gps_site_ID] = cache_insert_id();
					GPS_Sites[gps_cat_index][index][gps_site_X] = x;
					GPS_Sites[gps_cat_index][index][gps_site_Y] = y;
					GPS_Sites[gps_cat_index][index][gps_site_Z] = z;
					GPS_Sites[gps_cat_index][index][gps_site_CAT_ID] = gps_cat;
					Iter_Add(GPS_Sites[gps_cat_index], index);

					new msg[128];
					format(msg, sizeof msg, "GPS Site added (ID: %d)", GPS_Sites[gps_cat_index][index][gps_site_ID]);
					SendClientMessage(playerid, -1, msg);
				}
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO gps_sites (x, y, z, cat_id) VALUES (%f, %f, %f, %d);", x, y, z, gps_cat);
				mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnGpsSiteInserted, "");
			}
		}
		else SendClientMessage(playerid, -1, "Invalid ID!");
	}
	else SendClientMessage(playerid, -1, "Syntax: /dgpscat <ID>");
	return 1;
}

YCMD:dgpssite(playerid, params[], help)
{
	new site_id;
	if(!sscanf(params, "d", site_id))
	{
		if(DeleteGpsSiteId(site_id, true)) SendClientMessage(playerid, -1, "GPS Site deleted!");
		else SendClientMessage(playerid, -1, "Invalid ID!");
	}
	else SendClientMessage(playerid, -1, "Syntax: /dgpssite <ID>");
	return 1;
}