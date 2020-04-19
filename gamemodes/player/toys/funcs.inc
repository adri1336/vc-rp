loadtext lang[toys];

RemovePlayerToys(playerid)
{
	for(new i = 0; i < MAX_PLAYER_TOYS; i ++)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid, i)) RemovePlayerAttachedObject(playerid, i);
	}
	return 1;
}

SetPlayerToys(playerid)
{
	foreach(new i : pToys[playerid])
	{
		SetPlayerToy(playerid, i);
	}
	return 1;
}

SetPlayerToy(playerid, index)
{
	if(Iter_Contains(pToys[playerid], index))
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid, index))
		RemovePlayerAttachedObject(playerid, index);

		if(pToys[playerid][index][ptoy_ATTACHED])
		{
			if(!IsPlayerUsingClothe(playerid))
			{
				SetPlayerAttachedObject
				(
					playerid,
					index,
					pToys[playerid][index][ptoy_MODELID],
					pToys[playerid][index][ptoy_BONE],
					pToys[playerid][index][ptoy_X],
					pToys[playerid][index][ptoy_Y],
					pToys[playerid][index][ptoy_Z],
					pToys[playerid][index][ptoy_RX],
					pToys[playerid][index][ptoy_RY],
					pToys[playerid][index][ptoy_RZ],
					pToys[playerid][index][ptoy_SX],
					pToys[playerid][index][ptoy_SY],
					pToys[playerid][index][ptoy_SZ],
					pToys[playerid][index][ptoy_COLOR1],
					pToys[playerid][index][ptoy_COLOR2]
				);
			}
			else
			{
				new
					id_character, CLOTHES_TYPES:id_clothe,
					toy_clothe_index = -1;
				GetPlayerClothingInfo(playerid, id_character, id_clothe);
				toy_clothe_index = GetPlayerClotheIndexById(playerid, id_clothe);
				if(toy_clothe_index != -1)
				{
					SetPlayerAttachedObject
					(
						playerid,
						index,
						pToys[playerid][index][ptoy_MODELID],
						pToys[playerid][index][ptoy_BONE],
						pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_X],
						pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_Y],
						pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_Z],
						pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RX],
						pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RY],
						pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RZ],
						pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SX],
						pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SY],
						pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SZ],
						pToys[playerid][index][ptoy_COLOR1],
						pToys[playerid][index][ptoy_COLOR2]
					);
				}
			}
		}
		return 1;
	}
	return 0;
}

UpdatePlayerToy(playerid, index)
{
	if(Iter_Contains(pToys[playerid], index))
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_toys SET inv_itemid = %d, attached = %d, modelid = %d, bone = %d, x = %f, y = %f, z = %f, rx = %f, ry = %f, rz = %f, sx = %f, sy = %f, sz = %f, color1 = %d, color2 = %d WHERE id = %d;", pToys[playerid][index][ptoy_INV_ITEMID], pToys[playerid][index][ptoy_ATTACHED], pToys[playerid][index][ptoy_MODELID], pToys[playerid][index][ptoy_BONE], pToys[playerid][index][ptoy_X], pToys[playerid][index][ptoy_Y], pToys[playerid][index][ptoy_Z], pToys[playerid][index][ptoy_RX], pToys[playerid][index][ptoy_RY], pToys[playerid][index][ptoy_RZ], pToys[playerid][index][ptoy_SX], pToys[playerid][index][ptoy_SY], pToys[playerid][index][ptoy_SZ], pToys[playerid][index][ptoy_COLOR1], pToys[playerid][index][ptoy_COLOR2], pToys[playerid][index][ptoy_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
		return 1;
	}
	return 0;
}

UpdatePlayerToyClothe(playerid, index, toy_clothe_index)
{
	if(Iter_Contains(pToys[playerid], index))
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER,
			"\
				INSERT INTO player_toys_clothes (id_toy, id_clothe, x, y, z, rx, ry, rz, sx, sy, sz) VALUES (%d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f) \
				ON DUPLICATE KEY UPDATE x = %f, y = %f, z = %f, rx = %f, ry = %f, rz = %f, sx = %f, sy = %f, sz = %f;\
			",
				pToys[playerid][index][ptoy_ID], _:pClothes[playerid][toy_clothe_index],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_X],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_Y],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_Z],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RX],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RY],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RZ],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SX],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SY],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SZ],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_X],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_Y],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_Z],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RX],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RY],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RZ],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SX],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SY],
				pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SZ]
		);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
		return 1;
	}
	return 0;
}

GetPlayerToyIndexFromId(playerid, toy_id)
{
	foreach(new i : pToys[playerid])
	{
		if(pToys[playerid][i][ptoy_ID] == toy_id)
		{
			return i;
		}
	}
	return -1;
}

GetPlayerToyIndexFromModelid(playerid, modelid)
{
	foreach(new i : pToys[playerid])
	{
		if(pToys[playerid][i][ptoy_MODELID] == modelid)
		{
			return i;
		}
	}
	return -1;
}

IsModelidWatch(modelid)
{
	if(modelid >= 19039 && modelid <= 19053)
	{
		return true;
	}
	return false;
}

HasPlayerWatch(playerid)
{
	foreach(new i : pToys[playerid])
	{
		if(IsModelidWatch(pToys[playerid][i][ptoy_MODELID]))
		{
			return true;
		}
	}
	return false;
}

GetPlayerBonePartName(playerid, bone)
{
	new string[64];
	switch(bone)
	{
		case 1: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_1_BONE);
		case 2: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_2_BONE);
		case 3: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_3_BONE);
		case 4: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_4_BONE);
		case 5: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_5_BONE);
		case 6: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_6_BONE);
		case 7: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_7_BONE);
		case 8: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_8_BONE);
		case 9: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_9_BONE);
		case 10: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_10_BONE);
		case 11: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_11_BONE);
		case 12: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_12_BONE);
		case 13: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_13_BONE);
		case 14: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_14_BONE);
		case 15: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_15_BONE);
		case 16: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_16_BONE);
		case 17: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_17_BONE);
		case 18: Text_Format_Dialog(string, sizeof string, PI[playerid][pi_LANG_ID], $TOY_18_BONE);
	}
	return string;
}

GetToysMenuTitle(playerid)
{
	new title[32];
	Text_Format_TD(title, sizeof title, PI[playerid][pi_LANG_ID], $TEXTDRAW_TOYS_TITLE);
	return title;
}