#include <YSI\y_hooks>

public OnPlayerFirstSpawn(playerid, bool:new_user)
{
	/*if(new_user)
	{
		if(pNewuserCP[playerid] != INVALID_STREAMER_ID)
		{
			DestroyDynamicCP(pNewuserCP[playerid]);
			pNewuserCP[playerid] = INVALID_STREAMER_ID;
		}
		pNewuserCP[playerid] = CreateDynamicCP(Interest_Points[0][0], Interest_Points[0][1], Interest_Points[0][2], 1.0, .playerid = playerid);
		Streamer_SetIntData(STREAMER_TYPE_CP, pNewuserCP[playerid], E_STREAMER_EXTRA_ID, _:CHECKPOINT_TYPE_NEWUSER);
	}*/
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(pNewuserCP[playerid] != INVALID_STREAMER_ID)
	{
		DestroyDynamicCP(pNewuserCP[playerid]);
		pNewuserCP[playerid] = INVALID_STREAMER_ID;
	}
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	SetPlayerPosEx(playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], PI[playerid][pi_INTERIORID], PI[playerid][pi_WORLDID]);
	SetPlayerTime(playerid, SERVER_TIME[0], SERVER_TIME[1]);
	SetPlayerWeather(playerid, SERVER_WEATHER);
	SetPlayerHealthEx(playerid, PI[playerid][pi_HEALTH]);
	SetPlayerArmourEx(playerid, PI[playerid][pi_ARMOUR]);
	SetPlayerMoney(playerid);
	StopAudioStreamForPlayer(playerid);
	SetPlayerSkin(playerid, GetPlayerClothingSkinModel(playerid));
	//PlayerPlaySound(playerid, 1, 0.0, 0.0, 0.0); //desactiva sonido de las olas pero no va puto kalcor
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(pNewuserCP[playerid] != INVALID_STREAMER_ID && checkpointid == pNewuserCP[playerid])
	{	
		new type = Streamer_GetIntData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_EXTRA_ID);
		if(type == _:CHECKPOINT_TYPE_NEWUSER)
		{
			DestroyDynamicCP(pNewuserCP[playerid]);
			pNewuserCP[playerid] = INVALID_STREAMER_ID;
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return 1;
}