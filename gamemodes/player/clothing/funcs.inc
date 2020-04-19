loadtext lang[clothing];

GetPlayerClotheIndexById(playerid, CLOTHES_TYPES:clotheid)
{
	foreach(new i : pClothes[playerid])
	{
		if(pClothes[playerid][i] == clotheid)
		{
			return i;
		}
	}
	return -1;
}

AddPlayerClothe(playerid, CLOTHES_TYPES:clotheid)
{
	new index = Iter_Free(pClothes[playerid]);
	if(index != cellmin)
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_clothes (id_player, id_clothe) VALUES (%d, %d);", PI[playerid][pi_ID], _:clotheid);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
		pClothes[playerid][index] = clotheid;
		Iter_Add(pClothes[playerid], index);
		CallRemoteFunction("OnPlayerGetClothes", "i", playerid);
		return 1;
	}
	return 0;
}

DeletePlayerClothe(playerid, CLOTHES_TYPES:clotheid, bool:update = true)
{
	new index = -1;
	foreach(new i : pClothes[playerid])
	{
		if(pClothes[playerid][i] == clotheid)
		index = i;
	}

	if(index != -1)
	{
		pClothes[playerid][index] = CLOTHES_TYPES:0;
		Iter_Remove(pClothes[playerid], index);

		if(update)
		{
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_clothes WHERE id_player = %d AND id_clothe = %d;", PI[playerid][pi_ID], _:clotheid);
			mysql_tquery(vcrp_db, QUERY_BUFFER);
		}
		return 1;
	}
	return 0;
}

GetCharacterMenuTitle(playerid)
{
	new title[32];
	Text_Format_TD(title, sizeof title, PI[playerid][pi_LANG_ID], $TEXTDRAW_CHARACTER_MENU_TITLE);
	return title;
}

GetClotheMenuTitle(playerid)
{
	new title[32];
	Text_Format_TD(title, sizeof title, PI[playerid][pi_LANG_ID], $TEXTDRAW_CLOTHES_MENU_TITLE);
	return title;
}