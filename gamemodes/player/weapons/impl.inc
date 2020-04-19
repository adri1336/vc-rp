#include <YSI\y_hooks>

loadtext lang[weapons];

hook OnScriptInit()
{
	Iter_Init(pWeapons);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	ResetPlayerWeapons(playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	new tmp_pWeapons[E_pWeapons];
	foreach(new i : pWeapons[playerid])
	{
		if(pWeapons[playerid][i][pweapon_CARRIED])
		{
			if(HasWeaponAmmo(pWeapons[playerid][i][pweapon_WEAPONID]))
			{
				new weaponid, ammo;
				GetPlayerWeaponData(playerid, GetWeaponSlot(pWeapons[playerid][i][pweapon_WEAPONID]), weaponid, ammo);
				if(weaponid == pWeapons[playerid][i][pweapon_WEAPONID])
				pWeapons[playerid][i][pweapon_AMMO] = ammo;
				UpdatePlayerWeapon(playerid, i);
			}
		}
		pWeapons[playerid][i] = tmp_pWeapons;
	}
	Iter_Clear(pWeapons[playerid]);
	return 1;
}

hook OnPlayerLogin(playerid)
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				if(i >= MAX_PLAYER_WEAPONS)
				{
					printf("[ERROR]: Límite rebasado en pWeapons en OnPlayerLogin (pid: %d)", PI[playerid][pi_ID]);
					break;
				}
				cache_get_value_name_int(i, "id", pWeapons[playerid][i][pweapon_ID]);
				cache_get_value_name_int(i, "carried", pWeapons[playerid][i][pweapon_CARRIED]);
				cache_get_value_name_int(i, "weaponid", pWeapons[playerid][i][pweapon_WEAPONID]);
				cache_get_value_name_int(i, "ammo", pWeapons[playerid][i][pweapon_AMMO]);
				Iter_Add(pWeapons[playerid], i);
			}
		}
	}
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM player_weapons WHERE id_player = %d;", PI[playerid][pi_ID]);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	ResetPlayerWeapons(playerid);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	SetPlayerWeaponsSkillLevels(playerid);
	SetPlayerWeapons(playerid);
	return 1;
}

hook OnPlayerItemAdded(playerid, index, item_id, amount)
{
	if(INV_ITEMS_Info[item_id][inv_item_TYPE] == _:INV_ITEM_TYPE_WEAPON)
	{
		new tindex = Iter_Free(pWeapons[playerid]);
		if(tindex != cellmin)
		{
			new weaponid, ammo;
			sscanf(PINV[playerid][index][pinv_PARAMS], "p<,>dd", weaponid, ammo);
			if(ammo == 0) ammo = DEFAULT_WEAPON_AMMO;
			
			inline OnQueryLoad()
			{
				pWeapons[playerid][tindex][pweapon_ID] = cache_insert_id();
				pWeapons[playerid][tindex][pweapon_CARRIED] = 0;
				pWeapons[playerid][tindex][pweapon_WEAPONID] = weaponid;
				pWeapons[playerid][tindex][pweapon_AMMO] = ammo;
				Iter_Add(pWeapons[playerid], tindex);

				format(PINV[playerid][index][pinv_PARAMS], 128, "%d", pWeapons[playerid][tindex][pweapon_ID]);
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_inv SET params = '%e' WHERE id = %d;", PINV[playerid][index][pinv_PARAMS], PINV[playerid][index][pinv_ID]);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
			}
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_weapons (id_player, weaponid, ammo) VALUES (%d, %d, %d);", PI[playerid][pi_ID], weaponid, ammo);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
		}
	}
	return 1;
}

hook OnPlayerItemDeleted(playerid, index, inv_id, itemid, params[], bool:player_action, amount)
{
	if(INV_ITEMS_Info[itemid][inv_item_TYPE] == _:INV_ITEM_TYPE_WEAPON)
	{
		new weapon_id = strval(params);
		new weapon_index = GetPlayerWeaponIndexFromId(playerid, weapon_id);
		if(weapon_index != -1)
		{
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_weapons WHERE id = %d;", pWeapons[playerid][weapon_index][pweapon_ID]);
			mysql_tquery(vcrp_db, QUERY_BUFFER);

			new tmp_pWeapons[E_pWeapons];
			pWeapons[playerid][weapon_index] = tmp_pWeapons;
			Iter_Remove(pWeapons[playerid], weapon_index);
			SetPlayerWeapons(playerid);
		}
	}
	return 1;
}

YCMD:weapons(playerid, params[], help)
{
	new	line_str[90],
		carried_weapons_dialog[90 * MAX_PLAYER_WEAPONS_CARRIED],
		weapons_dialog[90 * MAX_PLAYER_WEAPONS],
		list;

	//carried weapons
	pExtraButtons[playerid][list++] = -1;
	foreach(new i : pWeapons[playerid])
	{
		if(pWeapons[playerid][i][pweapon_CARRIED])
		{
			new weapon_name[64];
			format(weapon_name, sizeof weapon_name, "%s", GetItemName(playerid, GetInvItemIdFromWeaponID(pWeapons[playerid][i][pweapon_WEAPONID])));
			if(HasWeaponAmmo(pWeapons[playerid][i][pweapon_WEAPONID])) format(line_str, sizeof line_str, "%c%s\t%d\n", toupper(weapon_name[0]), weapon_name[1], pWeapons[playerid][i][pweapon_AMMO]);
			else format(line_str, sizeof line_str, "%c%s\t-\n", toupper(weapon_name[0]), weapon_name[1]);
			strcat(carried_weapons_dialog, line_str);
			pExtraButtons[playerid][list++] = i;
		}
	}
	strcat(carried_weapons_dialog, "{FFCCFF}");

	//weapons
	pExtraButtons[playerid][list++] = -1;
	foreach(new i : pWeapons[playerid])
	{
		if(!pWeapons[playerid][i][pweapon_CARRIED])
		{
			new weapon_name[64];
			format(weapon_name, sizeof weapon_name, "%s", GetItemName(playerid, GetInvItemIdFromWeaponID(pWeapons[playerid][i][pweapon_WEAPONID])));
			if(HasWeaponAmmo(pWeapons[playerid][i][pweapon_WEAPONID])) format(line_str, sizeof line_str, "%c%s\t%d\n", toupper(weapon_name[0]), weapon_name[1], pWeapons[playerid][i][pweapon_AMMO]);
			else format(line_str, sizeof line_str, "%c%s\t-\n", toupper(weapon_name[0]), weapon_name[1]);
			strcat(weapons_dialog, line_str);
			pExtraButtons[playerid][list++] = i;
		}
	}

	//dialog
	inline OnPlayerDialog(pid, did, res, lis, string:inp)
	{
		#pragma unused pid, did, inp
		if(res)
		{
			new weapon_index = pExtraButtons[playerid][lis];
			if(weapon_index != -1)
			{
				if(Iter_Contains(pWeapons[playerid], weapon_index))
				{
					inline in_OnPlayerDialog(in_pid, in_did, in_res, in_lis, string:in_inp)
					{
						#pragma unused in_pid, in_did, in_lis, in_inp
						if(in_res)
						{
							switch(in_lis)
							{
								case 0: //sacar/guardar
								{
									if(pWeapons[playerid][weapon_index][pweapon_CARRIED]) //guardar
									{
										pWeapons[playerid][weapon_index][pweapon_CARRIED] = 0;
										if(HasWeaponAmmo(pWeapons[playerid][weapon_index][pweapon_WEAPONID]))
										{
											new weaponid, ammo;
											GetPlayerWeaponData(playerid, GetWeaponSlot(pWeapons[playerid][weapon_index][pweapon_WEAPONID]), weaponid, ammo);
											if(weaponid == pWeapons[playerid][weapon_index][pweapon_WEAPONID])
											pWeapons[playerid][weapon_index][pweapon_AMMO] = ammo;
										}
										SetPlayerWeapons(playerid);
										UpdatePlayerWeapon(playerid, weapon_index);
										CallRemoteFunction("OnPlayerUncarryWeapon", "id", playerid, pWeapons[playerid][weapon_index][pweapon_WEAPONID]);
									}
									else
									{
										if(CountPlayerCarriedWeapons(playerid) >= MAX_PLAYER_WEAPONS_CARRIED) Text_Send(playerid, $MESSAGE_ERROR_WEAPON_MAX, MAX_PLAYER_WEAPONS_CARRIED);
										else
										{
											pWeapons[playerid][weapon_index][pweapon_CARRIED] = 1;
											GivePlayerWeapon(playerid, pWeapons[playerid][weapon_index][pweapon_WEAPONID], pWeapons[playerid][weapon_index][pweapon_AMMO]);
											SetPlayerArmedWeapon(playerid, pWeapons[playerid][weapon_index][pweapon_WEAPONID]);
											UpdatePlayerWeapon(playerid, weapon_index);
											CallRemoteFunction("OnPlayerCarryWeapon", "id", playerid, pWeapons[playerid][weapon_index][pweapon_WEAPONID]);
										}
									}
								}
								case 1: //eliminar
								{
									new inv_params[128], itemid = GetInvItemIdFromWeaponID(pWeapons[playerid][weapon_index][pweapon_WEAPONID]);
									format(inv_params, sizeof inv_params, "%d", pWeapons[playerid][weapon_index][pweapon_ID]);
									
									new inv_index = GetPlayerInvIndexByItem(playerid, itemid, inv_params);
									if(inv_index != -1)
									RemovePlayerInvetoryItem(playerid, inv_index, true);
								}
							}
						}
					}
					if(pWeapons[playerid][weapon_index][pweapon_CARRIED]) Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline in_OnPlayerDialog, $DIALOG_WEAPON_CARRIED_CAPTION, $DIALOG_WEAPON_CARRIED_BODY, $DIALOG_WEAPON_CARRIED_YES, $DIALOG_WEAPON_CARRIED_NO);
					else Text_DialogBox(playerid, DIALOG_STYLE_LIST, using inline in_OnPlayerDialog, $DIALOG_WEAPON_CAPTION, $DIALOG_WEAPON_BODY, $DIALOG_WEAPON_YES, $DIALOG_WEAPON_NO);
				}
			}
		}
	}
	Text_DialogBox(playerid, DIALOG_STYLE_TABLIST_HEADERS, using inline OnPlayerDialog, $DIALOG_WEAPONS_CAPTION, $DIALOG_WEAPONS_BODY, $DIALOG_WEAPONS_YES, $DIALOG_WEAPONS_NO, carried_weapons_dialog, weapons_dialog);
	return 1;
}