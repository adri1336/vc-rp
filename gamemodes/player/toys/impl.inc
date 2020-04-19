#include <YSI\y_hooks>

loadtext lang[toys];

hook OnScriptInit()
{
	Iter_Init(pToys);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	for(new i = 0; i < MAX_PLAYER_ATTACHED_OBJECTS; i ++)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid, i)) RemovePlayerAttachedObject(playerid, i);
	}
	for(new i = 0; i < MAX_PLAYER_TOYS; i ++)
	{
		for(new j = 0; j < MAX_CLOTHING_CLOTHES_PER_CHAR; j ++)
		{
			pToys_Clothes[playerid][i][j][ptoy_clothe_X] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_Y] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_Z] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_RX] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_RY] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_RZ] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_SX] = 1.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_SY] = 1.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_SZ] = 1.0;
		}
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	new tmp_pToys[E_pToys];
	foreach(new i : pToys[playerid])
	{
		pToys[playerid][i] = tmp_pToys;
		if(IsPlayerAttachedObjectSlotUsed(playerid, i)) RemovePlayerAttachedObject(playerid, i);
	}
	Iter_Clear(pToys[playerid]);
	return 1;
}

hook OnPlayerClothesLoaded(playerid)
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_PLAYER_TOYS)
				{
					printf("[ERROR]: Límite rebasado en pToys en OnPlayerClothesLoaded (pid: %d)", PI[playerid][pi_ID]);
					break;
				}
				cache_get_value_name_int(i, "id", pToys[playerid][i][ptoy_ID]);
				cache_get_value_name_int(i, "inv_itemid", pToys[playerid][i][ptoy_INV_ITEMID]);
				cache_get_value_name_int(i, "attached", pToys[playerid][i][ptoy_ATTACHED]);
				cache_get_value_name_int(i, "modelid", pToys[playerid][i][ptoy_MODELID]);
				cache_get_value_name_int(i, "bone", pToys[playerid][i][ptoy_BONE]);
				cache_get_value_name_float(i, "x", pToys[playerid][i][ptoy_X]);
				cache_get_value_name_float(i, "y", pToys[playerid][i][ptoy_Y]);
				cache_get_value_name_float(i, "z", pToys[playerid][i][ptoy_Z]);
				cache_get_value_name_float(i, "rx", pToys[playerid][i][ptoy_RX]);
				cache_get_value_name_float(i, "ry", pToys[playerid][i][ptoy_RY]);
				cache_get_value_name_float(i, "rz", pToys[playerid][i][ptoy_RZ]);
				cache_get_value_name_float(i, "sx", pToys[playerid][i][ptoy_SX]);
				cache_get_value_name_float(i, "sy", pToys[playerid][i][ptoy_SY]);
				cache_get_value_name_float(i, "sz", pToys[playerid][i][ptoy_SZ]);
				cache_get_value_name_int(i, "color1", pToys[playerid][i][ptoy_COLOR1]);
				cache_get_value_name_int(i, "color2", pToys[playerid][i][ptoy_COLOR2]);
				Iter_Add(pToys[playerid], i);

				//clothes
				inline in_OnQueryLoad()
				{
					new irows;
					if(cache_get_row_count(irows))
					{
						for(new j = 0; j < irows; j ++)
						{
							new CLOTHES_TYPES:id_clothe;
							cache_get_value_name_int(j, "id_clothe", _:id_clothe);
							new index_clothe = GetPlayerClotheIndexById(playerid, id_clothe);
							if(index_clothe != -1)
							{
								cache_get_value_name_float(j, "x", pToys_Clothes[playerid][i][index_clothe][ptoy_clothe_X]);
								cache_get_value_name_float(j, "y", pToys_Clothes[playerid][i][index_clothe][ptoy_clothe_Y]);
								cache_get_value_name_float(j, "z", pToys_Clothes[playerid][i][index_clothe][ptoy_clothe_Z]);
								cache_get_value_name_float(j, "rx", pToys_Clothes[playerid][i][index_clothe][ptoy_clothe_RX]);
								cache_get_value_name_float(j, "ry", pToys_Clothes[playerid][i][index_clothe][ptoy_clothe_RY]);
								cache_get_value_name_float(j, "rz", pToys_Clothes[playerid][i][index_clothe][ptoy_clothe_RZ]);
								cache_get_value_name_float(j, "sx", pToys_Clothes[playerid][i][index_clothe][ptoy_clothe_SX]);
								cache_get_value_name_float(j, "sy", pToys_Clothes[playerid][i][index_clothe][ptoy_clothe_SY]);
								cache_get_value_name_float(j, "sz", pToys_Clothes[playerid][i][index_clothe][ptoy_clothe_SZ]);
							}
						}
					}
				}
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM player_toys_clothes WHERE id_toy = %d;", pToys[playerid][i][ptoy_ID]);
				mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline in_OnQueryLoad, "");
			}
		}
	}
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM player_toys WHERE id_player = %d;", PI[playerid][pi_ID]);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	CancelEdit(playerid);
	RemovePlayerToys(playerid);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	SetPlayerToys(playerid);
	return 1;
}

hook OnPlayerItemAdded(playerid, index, item_id, amount)
{
	if(INV_ITEMS_Info[item_id][inv_item_TYPE] == _:INV_ITEM_TYPE_TOY)
	{
		new tindex = Iter_Free(pToys[playerid]);
		if(tindex != cellmin)
		{
			new modelid, color1, color2;
			sscanf(PINV[playerid][index][pinv_PARAMS], "p<,>ddd", modelid, color1, color2);

			inline OnQueryLoad()
			{
				pToys[playerid][tindex][ptoy_ID] = cache_insert_id();
				pToys[playerid][tindex][ptoy_INV_ITEMID] = item_id;
				pToys[playerid][tindex][ptoy_ATTACHED] = 0;
				pToys[playerid][tindex][ptoy_MODELID] = modelid;
				pToys[playerid][tindex][ptoy_BONE] = 1;
				pToys[playerid][tindex][ptoy_X] = 0.0;
				pToys[playerid][tindex][ptoy_Y] = 0.0;
				pToys[playerid][tindex][ptoy_Z] = 0.0;
				pToys[playerid][tindex][ptoy_RX] = 0.0;
				pToys[playerid][tindex][ptoy_RY] = 0.0;
				pToys[playerid][tindex][ptoy_RZ] = 0.0;
				pToys[playerid][tindex][ptoy_SX] = 1.0;
				pToys[playerid][tindex][ptoy_SY] = 1.0;
				pToys[playerid][tindex][ptoy_SZ] = 1.0;
				pToys[playerid][tindex][ptoy_COLOR1] = color1;
				pToys[playerid][tindex][ptoy_COLOR2] = color2;
				Iter_Add(pToys[playerid], tindex);

				format(PINV[playerid][index][pinv_PARAMS], 128, "%d", pToys[playerid][tindex][ptoy_ID]);
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET params = '%e' WHERE id = %d;", PINV[playerid][index][pinv_PARAMS], PINV[playerid][index][pinv_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
			}
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_toys (id_player, inv_itemid, modelid, color1, color2) VALUES (%d, %d, %d, %d, %d);", PI[playerid][pi_ID], item_id, modelid, color1, color2);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
		}
	}
	return 1;
}

hook OnPlayerItemDeleted(playerid, index, inv_id, itemid, params[], bool:player_action, amount)
{
	if(INV_ITEMS_Info[itemid][inv_item_TYPE] == _:INV_ITEM_TYPE_TOY)
	{
		new toy_id = strval(params);
		new toy_index = GetPlayerToyIndexFromId(playerid, toy_id);
		if(toy_index != -1)
		{
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_toys WHERE id = %d;", pToys[playerid][toy_index][ptoy_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);

			new tmp_pToys[E_pToys];
			pToys[playerid][toy_index] = tmp_pToys;
			if(IsPlayerAttachedObjectSlotUsed(playerid, toy_index)) RemovePlayerAttachedObject(playerid, toy_index);
			Iter_Remove(pToys[playerid], toy_index);
		}
	}
	return 1;
}

public OnPlayerRequestConfigToy(playerid, index)
{
	inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, listitem, inputtext
		if(response)
		{
			new line_str[32], dialog[512];
			for(new i = 0; i < 18; i ++)
			{
				format(line_str, sizeof line_str, "%s", GetPlayerBonePartName(playerid, i + 1));
				format(line_str, sizeof line_str, "%c%s\n", toupper(line_str[0]), line_str[1]);
				strcat(dialog, line_str);
			}

			inline in_OnPlayerDialog(in_pid, did, res, lis, string:inp)
			{
				#pragma unused in_pid, did, res, inp
				pToys[playerid][index][ptoy_BONE] = lis + 1;
				SetPlayerToy(playerid, index);
				UpdatePlayerToy(playerid, index);
				EditAttachedObject(playerid, index);		
			}
			Dialog_ShowCallback(playerid, using inline in_OnPlayerDialog, DIALOG_STYLE_LIST, " - ", dialog, ">>", "X");
		}
		else EditAttachedObject(playerid, index);
	}
	Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_CONFIG_TOY_CAPTION, $DIALOG_CONFIG_TOY_BODY, $DIALOG_CONFIG_TOY_YES, $DIALOG_CONFIG_TOY_NO, GetPlayerBonePartName(playerid, pToys[playerid][index][ptoy_BONE]));
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	if(response)
	{
		if(fScaleX >= 1.5 || fScaleY >= 1.5 || fScaleZ >= 1.5)
		{
			Text_Send(playerid, $MESSAGE_ERROR_TOY_TOO_BIG);
			SetPlayerToy(playerid, index);
		}
		else
		{
			if(!IsPlayerUsingClothe(playerid))
			{
				pToys[playerid][index][ptoy_X] = fOffsetX;
				pToys[playerid][index][ptoy_Y] = fOffsetY;
				pToys[playerid][index][ptoy_Z] = fOffsetZ;
				pToys[playerid][index][ptoy_RX] = fRotX;
				pToys[playerid][index][ptoy_RY] = fRotY;
				pToys[playerid][index][ptoy_RZ] = fRotZ;
				pToys[playerid][index][ptoy_SX] = fScaleX;
				pToys[playerid][index][ptoy_SY] = fScaleY;
				pToys[playerid][index][ptoy_SZ] = fScaleZ;
				UpdatePlayerToy(playerid, index);
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
					pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_X] = fOffsetX;
					pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_Y] = fOffsetY;
					pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_Z] = fOffsetZ;
					pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RX] = fRotX;
					pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RY] = fRotY;
					pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_RZ] = fRotZ;
					pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SX] = fScaleX;
					pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SY] = fScaleY;
					pToys_Clothes[playerid][index][toy_clothe_index][ptoy_clothe_SZ] = fScaleZ;
					UpdatePlayerToyClothe(playerid, index, toy_clothe_index);
				}
			}
		}
	}
	else SetPlayerToy(playerid, index);
	return 1;
}

YCMD:toys(playerid, params[], help)
{
	new	attached_toys_dialog[90 * MAX_PLAYER_TOYS],
		toys_dialog[90 * MAX_PLAYER_TOYS],
		list;

	//carried weapons
	pExtraButtons[playerid][list++] = -1;
	foreach(new i : pToys[playerid])
	{
		if(pToys[playerid][i][ptoy_ATTACHED])
		{
			new toy_name[64];
			format(toy_name, sizeof toy_name, "%s\n", GetItemName(playerid, pToys[playerid][i][ptoy_INV_ITEMID]));
			format(toy_name, sizeof toy_name, "%c%s", toupper(toy_name[0]), toy_name[1]);
			strcat(attached_toys_dialog, toy_name);
			pExtraButtons[playerid][list++] = i;
		}
	}
	strcat(attached_toys_dialog, "{FFCCFF}");

	//weapons
	pExtraButtons[playerid][list++] = -1;
	foreach(new i : pToys[playerid])
	{
		if(!pToys[playerid][i][ptoy_ATTACHED])
		{
			new toy_name[64];
			format(toy_name, sizeof toy_name, "%s\n", GetItemName(playerid, pToys[playerid][i][ptoy_INV_ITEMID]));
			format(toy_name, sizeof toy_name, "%c%s", toupper(toy_name[0]), toy_name[1]);
			strcat(toys_dialog, toy_name);
			pExtraButtons[playerid][list++] = i;
		}
	}

	//dialog
	inline OnPlayerDialog(pid, did, res, lis, string:inp)
	{
		#pragma unused pid, did, inp
		if(res)
		{
			new toy_index = pExtraButtons[playerid][lis];
			if(toy_index != -1)
			{
				if(Iter_Contains(pToys[playerid], toy_index))
				{
					inline in_OnPlayerDialog(in_pid, in_did, in_res, in_lis, string:in_inp)
					{
						#pragma unused in_pid, in_did, in_lis, in_inp
						if(in_res)
						{
							switch(in_lis)
							{
								case 0: //colocar/guardar
								{
									if(pToys[playerid][toy_index][ptoy_ATTACHED]) //guardar
									{
										pToys[playerid][toy_index][ptoy_ATTACHED] = 0;
										SetPlayerToy(playerid, toy_index);
										UpdatePlayerToy(playerid, toy_index);
										CallRemoteFunction("OnPlayerRemoveToy", "id", playerid, toy_index);
									}
									else
									{
										pToys[playerid][toy_index][ptoy_ATTACHED] = 1;
										SetPlayerToy(playerid, toy_index);
										UpdatePlayerToy(playerid, toy_index);
										CallRemoteFunction("OnPlayerAttachToy", "id", playerid, toy_index);
									}
								}
								case 1: //eliminar
								{
									if(pToys[playerid][toy_index][ptoy_ATTACHED]) //editar
									{
										CallRemoteFunction("OnPlayerRequestConfigToy", "id", playerid, toy_index);
									}
									else
									{
										new inv_params[128], itemid = pToys[playerid][toy_index][ptoy_INV_ITEMID];
										format(inv_params, sizeof inv_params, "%d", pToys[playerid][toy_index][ptoy_ID]);
										new inv_index = GetPlayerInvIndexByItem(playerid, itemid, inv_params);
										if(inv_index != -1)
										RemovePlayerInvetoryItem(playerid, inv_index, true);
									}
								}
								case 2: //eliminar
								{
									new inv_params[128], itemid = pToys[playerid][toy_index][ptoy_INV_ITEMID];
									format(inv_params, sizeof inv_params, "%d", pToys[playerid][toy_index][ptoy_ID]);
									new inv_index = GetPlayerInvIndexByItem(playerid, itemid, inv_params);
									if(inv_index != -1)
									RemovePlayerInvetoryItem(playerid, inv_index, true);
								}
							}
						}
					}
					if(pToys[playerid][toy_index][ptoy_ATTACHED]) Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline in_OnPlayerDialog, $DIALOG_TOY_ATTACHED_CAPTION, $DIALOG_TOY_ATTACHED_BODY, $DIALOG_TOY_ATTACHED_YES, $DIALOG_TOY_ATTACHED_NO);
					else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline in_OnPlayerDialog, $DIALOG_TOY_CAPTION, $DIALOG_TOY_BODY, $DIALOG_TOY_YES, $DIALOG_TOY_NO);
				}
			}
		}
	}
	Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline OnPlayerDialog, $DIALOG_TOYS_CAPTION, $DIALOG_TOYS_BODY, $DIALOG_TOYS_YES, $DIALOG_TOYS_NO, attached_toys_dialog, toys_dialog);
	return 1;
}

hook OnPlayerClothesChange(playerid, index)
{	
	SetPlayerToys(playerid);
	return 1;
}

hook OnPlayerRemoveClothes(playerid, index, CLOTHES_TYPES:id_clothe)
{
	foreach(new i : pToys[playerid])
	{
		pToys_Clothes[playerid][i][index][ptoy_clothe_X] = 0.0;
		pToys_Clothes[playerid][i][index][ptoy_clothe_Y] = 0.0;
		pToys_Clothes[playerid][i][index][ptoy_clothe_Z] = 0.0;
		pToys_Clothes[playerid][i][index][ptoy_clothe_RX] = 0.0;
		pToys_Clothes[playerid][i][index][ptoy_clothe_RY] = 0.0;
		pToys_Clothes[playerid][i][index][ptoy_clothe_RZ] = 0.0;
		pToys_Clothes[playerid][i][index][ptoy_clothe_SX] = 1.0;
		pToys_Clothes[playerid][i][index][ptoy_clothe_SY] = 1.0;
		pToys_Clothes[playerid][i][index][ptoy_clothe_SZ] = 1.0;
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_toys_clothes WHERE id_toy = %d AND id_clothe = %d;", pToys[playerid][i][ptoy_ID], _:id_clothe);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}
	return 1;
}

hook OnPlayerCharacterChange(playerid)
{
	foreach(new i : pToys[playerid])
	{
		for(new j = 0; j < MAX_CLOTHING_CLOTHES_PER_CHAR; j ++)
		{
			pToys_Clothes[playerid][i][j][ptoy_clothe_X] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_Y] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_Z] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_RX] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_RY] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_RZ] = 0.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_SX] = 1.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_SY] = 1.0;
			pToys_Clothes[playerid][i][j][ptoy_clothe_SZ] = 1.0;
		}
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_toys_clothes WHERE id_toy = %d;", pToys[playerid][i][ptoy_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
	}
	return 1;
}

YCMD:time(playerid, params[], help)
{
	if(HasPlayerWatch(playerid)) CallRemoteFunction("OnPlayerCheckTime", "i", playerid);
	else Text_Send(playerid, $MESSAGE_ERROR_NO_WATCH);
	return 1;
}