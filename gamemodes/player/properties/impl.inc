#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
	pPropertyTourTime[playerid] = 0;
	pLastPropertyTour[playerid] = 0;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(pPropertyTourTimer[playerid] != Timer:-1)
	{
		stop pPropertyTourTimer[playerid];
		pPropertyTourTimer[playerid] = Timer:-1;
	}
	Iter_Clear(PlayerProperties<playerid>);
	return 1;
}

hook OnPlayerLogin(playerid)
{
	foreach(new i : PropertyInfo)
	{
		if(PropertyInfo[i][property_ID_PLAYER] == PI[playerid][pi_ID])
		{
			Iter_Add(PlayerProperties<playerid>, i);
		}
	}
	return 1;
}

hook OnPlayerEnterProperty(playerid)
{
	if(!IsPropertyOccupied(PI[playerid][pi_WORLD_STATE_INDEX]))
	{
		if(pPropertyTourTimer[playerid] != Timer:-1)
		{
			stop pPropertyTourTimer[playerid];
			pPropertyTourTimer[playerid] = Timer:-1;
		}

		pPropertyTourTime[playerid] = PROPERTY_TOUR_TIME;
		pLastPropertyTour[playerid] = gettime();
		pPropertyTourTimer[playerid] = repeat OnPlayerPropertyTourUpdate(playerid);
	}
	return 1;
}

hook OnPlayerExitProperty(playerid)
{
	if(pPropertyTourTimer[playerid] != Timer:-1)
	{
		stop pPropertyTourTimer[playerid];
		pPropertyTourTimer[playerid] = Timer:-1;
		HidePlayerInfoMessage(playerid);
	}
	return 1;
}

timer OnPlayerPropertyTourUpdate[PROPERTY_TOUR_UPDATE_INTERVAL](playerid)
{
	if(PI[playerid][pi_WORLD_STATE] != PLAYER_WORLD_STATE_PROPERTY)
	{
		if(pPropertyTourTimer[playerid] != Timer:-1)
		{
			stop pPropertyTourTimer[playerid];
			pPropertyTourTimer[playerid] = Timer:-1;
		}
		HidePlayerInfoMessage(playerid);
	}
	else
	{
		pPropertyTourTime[playerid] --;
		if(pPropertyTourTime[playerid] <= 0)
		{
			if(pPropertyTourTimer[playerid] != Timer:-1)
			{
				stop pPropertyTourTimer[playerid];
				pPropertyTourTimer[playerid] = Timer:-1;
			}
			GetPlayerExteriorPos(playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], PI[playerid][pi_INTERIORID], PI[playerid][pi_WORLDID]);
			SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);

			SetPlayerPosEx(playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], PI[playerid][pi_INTERIORID], PI[playerid][pi_WORLDID], .offset = true);
			LoadScreenTimed(playerid);
			PlayerPropertyTourCancelMessage(playerid);
		}
		else PlayerPropertyTourMessage(playerid);
	}
	return 1;
}

hook OnPlGiveItemToPlayer(playerid, toplayerid, itemid, params[])
{
	if(itemid == _:INV_ITEM_PROPERTY_RENT_KEY)
	{
		new pid;
		if(!sscanf(params, "d", pid))
		{
			new pindex = GetPropertyIndexFromId(pid);
			if(pindex != -1)
			{
				if(PropertyInfo[pindex][property_ID_PLAYER])
				{
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties SET id_player = %d WHERE id = %d;", PI[toplayerid][pi_ID], PropertyInfo[pindex][property_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER);

					PropertyInfo[pindex][property_ID_PLAYER] = PI[toplayerid][pi_ID];
					format(PropertyInfo[pindex][property_PLAYER_NAME], 24, "%s", PI[toplayerid][pi_NAME]);
				}
			}
		}
	}
	return 1;
}

hook OnPlayerItemDeleted(playerid, index, inv_id, itemid, params[], bool:player_action, amount)
{
	if(itemid == _:INV_ITEM_PROPERTY_RENT_KEY)
	{
		new pid;
		if(!sscanf(params, "d", pid))
		{
			new pindex = GetPropertyIndexFromId(pid);
			if(pindex != -1)
			{
				if(PropertyInfo[pindex][property_ID_PLAYER])
				{
					mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE properties SET id_player = NULL WHERE id = %d;", PropertyInfo[pindex][property_ID]);
					mysql_tquery(vcrp_db, QUERY_BUFFER);

					PropertyInfo[pindex][property_ID_PLAYER] = 0;
					PropertyInfo[pindex][property_PLAYER_NAME][0] = EOS;

					DeletePropertyKeys(PropertyInfo[pindex][property_ID], false, pindex);
				}
			}
		}
	}
	return 1;
}