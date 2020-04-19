#include <YSI\y_hooks>

loadtext lang[connection];

hook OnPlayerConnect(playerid)
{
	//
	GameTextForPlayer(playerid, "~p~VC-RP.es", 10000, 4);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	ResetPlayerMoney(playerid);
	HidePlayerDialog(playerid);
	CancelSelectTextDraw(playerid);
	SetPlayerTime(playerid, 12, 0);
	SetPlayerWeather(playerid, 0);
	SetPlayerScore(playerid, 0);
	ResetPlayerWeapons(playerid);
	SetPlayerColor(playerid, PLAYER_COLOR);
	CancelEdit(playerid);
	SetPlayerVirtualWorld(playerid, 0);
	EnablePlayerCameraTarget(playerid, true);
	//

	new tmp_name[24];
	GetPlayerName(playerid, tmp_name, 24);
	if(!IsValidRPName(tmp_name))
	{
		SetPlayerGameState(playerid, GAME_STATE_NONE); //esto hara que no siga con el proceso
		Text_Send(playerid, $MESSAGE_ERROR_WRONG_NAME_FORMAT);
		TimedKick(playerid);
	}

	pClassed[playerid] = false;
	pLoggedIn[playerid] = false;
	//TogglePlayerSpectating(playerid, true);
	PlayAudioStreamForPlayer(playerid, ""RADIO_URL"/vcrp.ogg");
	return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{
	if(GetPlayerGameState(playerid) == GAME_STATE_CONNECTED)
	{
		if(pClassed[playerid])
		{
			Kick(playerid);
		}
		else
		{
			pClassed[playerid] = true;
			PlayAudioStreamForPlayer(playerid, Intro_Audios[random(sizeof Intro_Audios)]);
			SetPlayerVirtualWorld(playerid, VC_WORLD);
			TogglePlayerSpectating(playerid, true);
		}
	}
	return 1;
}

hook OnPlayerRequestSpawn(playerid)
{
	Kick(playerid);
	return 1;
}

public OnAccountDataLoad(playerid)
{
	new camera = random(sizeof Intro_Cameras);
	InterpolateCameraPos(playerid, Intro_Cameras[camera][0], Intro_Cameras[camera][1], Intro_Cameras[camera][2], Intro_Cameras[camera][6], Intro_Cameras[camera][7], Intro_Cameras[camera][8], 10000, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, Intro_Cameras[camera][3], Intro_Cameras[camera][4], Intro_Cameras[camera][5], Intro_Cameras[camera][9], Intro_Cameras[camera][10], Intro_Cameras[camera][11], 10000, CAMERA_MOVE);
	CleanPlayerChat(playerid);
	SetRolePlayNames(playerid);
	SetSpawnInfo(playerid, NO_TEAM, GetPlayerClothingSkinModel(playerid), PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], 0, 0, 0, 0, 0, 0);
	GameTextForPlayer(playerid, " ", 1, 4);

	switch(orm_errno(PI[playerid][pi_ORM])) 
	{
		case ERROR_OK:
		{
			Langs_SetPlayerCode(playerid, PI[playerid][pi_LANG]);
			CallRemoteFunction("OnPlayerRequestLogin", "i", playerid);
		}
		case ERROR_NO_DATA: CallRemoteFunction("OnPlayerRequestRegister", "i", playerid);
	}
	orm_setkey(PI[playerid][pi_ORM], "id");
	return 1;
}

public OnPlayerLogin(playerid)
{
	SetPlayerColor(playerid, PLAYER_COLOR);
	CleanPlayerChat(playerid);
	pLoggedIn[playerid] = true;
	//
	if(strcmp(PI[playerid][pi_CONNECTION_IP], PI[playerid][pi_IP], false)) Text_Send(playerid, $MESSAGE_WARNING_IP);
	format(PI[playerid][pi_IP], 16, "%s", PI[playerid][pi_CONNECTION_IP]);
	//
	if(pNewUser[playerid]) Text_Send(playerid, $MESSAGE_INFO_SPAWN_NEW_USER, PI[playerid][pi_FIRST_NAME]);
	else Text_Send(playerid, $MESSAGE_INFO_SPAWN, PI[playerid][pi_FIRST_NAME], PI[playerid][pi_LAST_CONNECTION]);
	//fix indexs ids
	switch(PI[playerid][pi_WORLD_STATE])
	{
		case PLAYER_WORLD_STATE_ENTRANCE:
		{
			PI[playerid][pi_WORLD_STATE_INDEX] = GetEntranceIndexByEntranceDId(PI[playerid][pi_WORLD_STATE_ID]);
			if(PI[playerid][pi_WORLD_STATE_INDEX] == -1)
			{
				SetPlayerWorldDefaultInfo(playerid);
				Text_Send(playerid, $MESSAGE_ERROR_INDEX);
			}
		}
		case PLAYER_WORLD_STATE_PROPERTY:
		{
			PI[playerid][pi_WORLD_STATE_INDEX] = GetPropertyIndexFromId(PI[playerid][pi_WORLD_STATE_ID]);
			if(PI[playerid][pi_WORLD_STATE_INDEX] == -1)
			{
				SetPlayerWorldDefaultInfo(playerid);
				Text_Send(playerid, $MESSAGE_ERROR_INDEX);
			}
			else
			{
				PI[playerid][pi_WORLD_STATE_EXTRA_INDEX] = GetPropertyDoorIndexFromId(PI[playerid][pi_WORLD_STATE_INDEX], PI[playerid][pi_WORLD_STATE_EXTRA_ID]);
				if(PI[playerid][pi_WORLD_STATE_EXTRA_INDEX] == -1)
				{
					SetPlayerWorldDefaultInfo(playerid);
					Text_Send(playerid, $MESSAGE_ERROR_INDEX);
				}
			}
		}
		case PLAYER_WORLD_STATE_BUSINESS:
		{
			PI[playerid][pi_WORLD_STATE_INDEX] = GetBusinessIndexFromId(PI[playerid][pi_WORLD_STATE_ID]);
			if(PI[playerid][pi_WORLD_STATE_INDEX] == -1)
			{
				SetPlayerWorldDefaultInfo(playerid);
				Text_Send(playerid, $MESSAGE_ERROR_INDEX);
			}
			else
			{
				PI[playerid][pi_WORLD_STATE_EXTRA_INDEX] = GetBusinessDoorIndexFromId(PI[playerid][pi_WORLD_STATE_INDEX], PI[playerid][pi_WORLD_STATE_EXTRA_ID]);
				if(PI[playerid][pi_WORLD_STATE_EXTRA_INDEX] == -1)
				{
					SetPlayerWorldDefaultInfo(playerid);
					Text_Send(playerid, $MESSAGE_ERROR_INDEX);
				}
			}
		}
	}
	//
	PI[playerid][pi_CONNECTED] = true;
	PI[playerid][pi_PLAYERID] = playerid;


	//por si se cerro el server sin guardar
	if(PI[playerid][pi_WORLD_STATE] != PLAYER_WORLD_STATE_STREET)
	{
		new bool:act = true;
		if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_PROPERTY)
		{
			if(GetPropertyOwner(PI[playerid][pi_WORLD_STATE_INDEX]) == PI[playerid][pi_ID])
			act = false;
		}
		if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_BUSINESS)
		{
			if(GetBusinessOwner(PI[playerid][pi_WORLD_STATE_INDEX]) == PI[playerid][pi_ID])
			act = false;
		}
		if(act)
		{
			GetPlayerExteriorPos(playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], PI[playerid][pi_INTERIORID], PI[playerid][pi_WORLDID]);
			SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
		}
	}

	orm_update(PI[playerid][pi_ORM]);
	SetPlayerLanguageGroup(playerid);
	SetPlayerScore(playerid, PI[playerid][pi_LEVEL]);
	//para incs
	CallRemoteFunction("OnPlayerARLoad", "idd", playerid, PI[playerid][pi_AR_WIDTH], PI[playerid][pi_AR_HEIGHT]);
	return 1;
}