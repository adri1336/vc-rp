GetInvItemIdFromWeaponID(weaponid)
{
	switch(weaponid)
	{
		case 1: return _:INV_ITEM_BRASS_KNUCKLES;
		case 2: return _:INV_ITEM_GOLF_CLUB;
		case 3: return _:INV_ITEM_NIGHTSTICK;
		case 4: return _:INV_ITEM_KNIFE;
		case 5: return _:INV_ITEM_BASEBALL_BAT;
		case 6: return _:INV_ITEM_SHOVEL;
		case 7: return _:INV_ITEM_POOL_CUE;
		case 8: return _:INV_ITEM_KATANA;
		case 9: return _:INV_ITEM_CHAINSAW;
		case 10: return _:INV_ITEM_PURPLE_DILDO;
		case 11: return _:INV_ITEM_DILDO;
		case 12: return _:INV_ITEM_VIBRATOR;
		case 13: return _:INV_ITEM_SILVER_VIBRATOR;
		case 14: return _:INV_ITEM_FLOWERS;
		case 15: return _:INV_ITEM_CANE;
		case 16: return _:INV_ITEM_GRENADE;
		case 17: return _:INV_ITEM_TEAR_GAS;
		case 18: return _:INV_ITEM_MOLOTOV_COCKTAIL;
		case 22: return _:INV_ITEM_COLT45;
		case 23: return _:INV_ITEM_SILENCED_COLT45;
		case 24: return _:INV_ITEM_DESERT_EAGLE;
		case 25: return _:INV_ITEM_SHOTGUN;
		case 26: return _:INV_ITEM_SAWNOFF_SHOTGUN;
		case 27: return _:INV_ITEM_COMBAT_SHOTGUN;
		case 28: return _:INV_ITEM_UZI;
		case 29: return _:INV_ITEM_MP5;
		case 30: return _:INV_ITEM_AK_47;
		case 31: return _:INV_ITEM_M4;
		case 32: return _:INV_ITEM_TEC_9;
		case 33: return _:INV_ITEM_COUNTRY_RIFLE;
		case 34: return _:INV_ITEM_SNIPER_RIFLE;
		case 35: return _:INV_ITEM_RPG;
		case 36: return _:INV_ITEM_HS_ROCKET;
		case 37: return _:INV_ITEM_FLAMETHROWER;
		case 38: return _:INV_ITEM_MINIGUN;
		case 39: return _:INV_ITEM_SATCHEL_CHARGE;
		case 40: return _:INV_ITEM_DETONATOR;
		case 41: return _:INV_ITEM_SPRAYCAN;
		case 42: return _:INV_ITEM_FIRE_EXTINGUISHER;
		case 43: return _:INV_ITEM_CAMERA;
		case 46: return _:INV_ITEM_PARACHUTE;
	}
	return 0;
}

SetPlayerWeapons(playerid)
{
	ResetPlayerWeapons(playerid);
	foreach(new i : pWeapons[playerid])
	{
		if(pWeapons[playerid][i][pweapon_CARRIED])
		GivePlayerWeapon(playerid, pWeapons[playerid][i][pweapon_WEAPONID], pWeapons[playerid][i][pweapon_AMMO]);
	}
	return 1;
}

UpdatePlayerWeapon(playerid, index)
{
	if(Iter_Contains(pWeapons[playerid], index))
	{
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE player_weapons SET carried = %d, weaponid = %d, ammo = %d WHERE id = %d;", pWeapons[playerid][index][pweapon_CARRIED], pWeapons[playerid][index][pweapon_WEAPONID], pWeapons[playerid][index][pweapon_AMMO], pWeapons[playerid][index][pweapon_ID]);
		mysql_tquery(vcrp_db, QUERY_BUFFER);
		return 1;
	}
	return 0;
}

GetPlayerWeaponIndexFromId(playerid, weapon_id)
{
	foreach(new i : pWeapons[playerid])
	{
		if(pWeapons[playerid][i][pweapon_ID] == weapon_id)
		{
			return i;
		}
	}
	return -1;
}

CountPlayerCarriedWeapons(playerid)
{
	new weapons[13][2], count;
	for (new i = 0; i <= 12; i++)
	{
		GetPlayerWeaponData(playerid, i, weapons[i][0], weapons[i][1]);
		if(weapons[i][0] != 0 && weapons[i][1] > 0) count ++;
	}
	return count;
}

SetPlayerWeaponsSkillLevels(playerid)
{
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 0);
	return 1;
}