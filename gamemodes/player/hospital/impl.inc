#include <YSI\y_hooks>

loadtext lang[hospital];

hook OnPlayerConnect(playerid)
{
	pSpawnInHospital[playerid] = false;
	pInHospitalBed[playerid] = false;
	pHospitalBedIndex[playerid] = 0;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	CancelPlayerHospitalBed(playerid);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	CancelPlayerHospitalBed(playerid);

	new hospital_index = GetNearestHospitalForPlayer(playerid);

	PI[playerid][pi_ARMOUR] = 0.0;
	PI[playerid][pi_HEALTH] = 20.0;
	PI[playerid][pi_X] = Interiors[Entrances[HospitalsEntrances[hospital_index]][entrance_INTERIOR_INDEX]][interior_X];
	PI[playerid][pi_Y] = Interiors[Entrances[HospitalsEntrances[hospital_index]][entrance_INTERIOR_INDEX]][interior_Y];
	PI[playerid][pi_Z] = Interiors[Entrances[HospitalsEntrances[hospital_index]][entrance_INTERIOR_INDEX]][interior_Z];
	PI[playerid][pi_ANGLE] = Interiors[Entrances[HospitalsEntrances[hospital_index]][entrance_INTERIOR_INDEX]][interior_ANGLE];
	PI[playerid][pi_INTERIORID] = Interiors[Entrances[HospitalsEntrances[hospital_index]][entrance_INTERIOR_INDEX]][interior_INTERIORID];
	PI[playerid][pi_WORLDID] = Entrances[HospitalsEntrances[hospital_index]][entrance_ID_ENTRANCE];

	//fix
	PI[playerid][pi_X] += (1.5 * floatsin(-PI[playerid][pi_ANGLE], degrees));
	PI[playerid][pi_Y] += (1.5 * floatcos(-PI[playerid][pi_ANGLE], degrees));
	PI[playerid][pi_X] += (1.5 * floatsin(-(PI[playerid][pi_ANGLE] + 90.0), degrees));
	PI[playerid][pi_Y] += (1.5 * floatcos(-(PI[playerid][pi_ANGLE] + 90.0), degrees));

	SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_ENTRANCE, HospitalsEntrances[hospital_index]);
	SetSpawnInfo(playerid, NO_TEAM, GetPlayerClothingSkinModel(playerid), PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], 0, 0, 0, 0, 0, 0);

	FadePlayerScreenTimed(playerid, 0x00, 0xFF, 700);
	pSpawnInHospital[playerid] = true;
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(pSpawnInHospital[playerid])
	{
		pSpawnInHospital[playerid] = false;
		Streamer_Update(playerid);
		FadePlayerScreenTimed(playerid, 0xFF, 0x00, 2000);
		CleanPlayerChat(playerid);

		new cost = minrand(50, 80);
		if(cost > PI[playerid][pi_MONEY]) cost = 0;
		GivePlayerMoneyEx(playerid, -cost);

		if(cost) Text_Send(playerid, $MESSAGE_INFO_HOSPITAL_MONEY, cost);
		else Text_Send(playerid, $MESSAGE_INFO_HOSPITAL);
		Text_Send(playerid, $MESSAGE_INFO_HOSPITAL_BED);
	}
	return 1;
}

public OnPlayerRequestHospitalBed(playerid, index)
{
	if(pInHospitalBed[playerid]) return 0;

	if(Hospital_Beds[index][hbed_IN_USE]) Text_Send(playerid, $MESSAGE_ERROR_BED_IN_USE);
	else
	{
		if(PI[playerid][pi_HEALTH] > 70.0) Text_Send(playerid, $MESSAGE_ERROR_GOOD_HEALTH);
		else
		{
			Hospital_Beds[index][hbed_IN_USE] = true;
			pInHospitalBed[playerid] = true;
			pHospitalBedIndex[playerid] = index;
			HidePlayerInfoMessage(playerid);
			SetPlayerInBed(playerid, index);
			Text_Send(playerid, $MESSAGE_INFO_BED);
			hopitalbed_timer[playerid] = repeat HospitalBedUp(playerid);
			CallRemoteFunction("OnPlayerHospitalBed", "i", playerid);
		}
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(GetPlayerGameState(playerid) == GAME_STATE_SPAWNED && pInHospitalBed[playerid])
	{
		if(PRESSED(KEY_SECONDARY_ATTACK)) CancelPlayerHospitalBed(playerid);
	}
	return 1;
}

timer HospitalBedUp[5000](playerid)
{
	GivePlayerHealth(playerid, 1.0);

	if(PI[playerid][pi_HEALTH] >= 100.0)
	{
		CancelPlayerHospitalBed(playerid);
		Text_Send(playerid, $GAMETEXT_INFO_CURED);
		PI[playerid][pi_HEALTH] = 100.0;
		SetPlayerHealthEx(playerid, PI[playerid][pi_HEALTH]);
	}
	else
	{
		if(GetPlayerDistanceFromPoint(playerid, Hospital_Beds[pHospitalBedIndex[playerid]][hbed_X], Hospital_Beds[pHospitalBedIndex[playerid]][hbed_Y], Hospital_Beds[pHospitalBedIndex[playerid]][hbed_Z]) > 1.0)
		{
			Text_Send(playerid, $MESSAGE_INFO_BED_DISTANCE);
			SetPlayerInBed(playerid, pHospitalBedIndex[playerid]);
		}
		GameTextForPlayer(playerid, "~g~+1 hp", 1500, 4);
	}	
}