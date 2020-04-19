#include <YSI\y_hooks>

hook OnPlayerRequestClass(playerid, classid)
{
	if(GetPlayerGameState(playerid) == GAME_STATE_CONNECTED)
	{
		GetPlayerName(playerid, PI[playerid][pi_NAME], 24);
		GetPlayerIp(playerid, PI[playerid][pi_CONNECTION_IP], 16);
		GetPlayerIp(playerid, PI[playerid][pi_IP], 16);
		PI[playerid][pi_CONNECTED] = true;
		PI[playerid][pi_PLAYERID] = playerid;
		PI[playerid][pi_X] = New_User_Pos[0];
		PI[playerid][pi_Y] = New_User_Pos[1];
		PI[playerid][pi_Z] = New_User_Pos[2];
		PI[playerid][pi_ANGLE] = New_User_Pos[3];
		PI[playerid][pi_HEALTH] = 100.0;
		PI[playerid][pi_LEVEL] = 1;
		PI[playerid][pi_REPUTATION] = 1.0;
		PI[playerid][pi_WORLD_STATE] = PLAYER_WORLD_STATE_STREET;
		PI[playerid][pi_WORLD_STATE_INDEX] = -1;
		PI[playerid][pi_WORLD_STATE_EXTRA_INDEX] = -1;
		PI[playerid][pi_WORLDID] = VC_WORLD;
		PI[playerid][pi_MONEY] = minrand(1000, 2000);
		PI[playerid][pi_BANK_MONEY] = minrand(1000, 2000);
		PI[playerid][pi_AR_WIDTH] = DEFAULT_AR_WIDTH;
		PI[playerid][pi_AR_HEIGHT] = DEFAULT_AR_HEIGHT;
		PI[playerid][pi_GPS_MINIMAP] = false;
		PI[playerid][pi_GPS_LOCATION] = true;
		PI[playerid][pi_GPS_ROUTE] = true;
		PI[playerid][pi_GPS_OBJECTIVES] = true;
		PI[playerid][pi_GPS_PROPERTIES] = true;
		PI[playerid][pi_GPS_BUSINESS] = true;
		PI[playerid][pi_GPS_VEHICLES] = true;
		PI[playerid][pi_PHONE_ON] = true;
		PI[playerid][pi_CLOTHING_CHARACTER] = 1;
		PI[playerid][pi_CLOTHING_CLOTHE] = CLOTHE_TYPE_DEFAULT;
		PI[playerid][pi_HELP_CHANNEL] = 1;
		PI[playerid][pi_ADMIN_MESSAGES] = 1;
		PI[playerid][pi_TUTORIAL] = TutorialFlags:0;
		PI[playerid][pi_LANG_ID] = Language:0;

		PI[playerid][pi_ORM] = orm_create("player", vcrp_db);
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_ID], "id");
		orm_addvar_string(PI[playerid][pi_ORM], PI[playerid][pi_NAME], 24, "name");
		orm_addvar_string(PI[playerid][pi_ORM], PI[playerid][pi_SALT], 16, "salt");
		orm_addvar_string(PI[playerid][pi_ORM], PI[playerid][pi_PASSWD], 65, "passwd");
		orm_addvar_string(PI[playerid][pi_ORM], PI[playerid][pi_IP], 16, "ip");
		orm_addvar_string(PI[playerid][pi_ORM], PI[playerid][pi_REGISTER_DATE], 24, "register_date");
		orm_addvar_string(PI[playerid][pi_ORM], PI[playerid][pi_LAST_CONNECTION], 24, "last_connection");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_TIME_PLAYING], "time_playing");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_MONEY], "money");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_LEVEL], "level");
		orm_addvar_float(PI[playerid][pi_ORM], PI[playerid][pi_REPUTATION], "reputation");
		orm_addvar_string(PI[playerid][pi_ORM], PI[playerid][pi_LANG], 3, "lang");
		orm_addvar_string(PI[playerid][pi_ORM], PI[playerid][pi_EMAIL], 64, "email");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_CONNECTED], "connected");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_PLAYERID], "playerid");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_ADMIN_LEVEL], "admin_level");
		orm_addvar_float(PI[playerid][pi_ORM], PI[playerid][pi_X], "x");
		orm_addvar_float(PI[playerid][pi_ORM], PI[playerid][pi_Y], "y");
		orm_addvar_float(PI[playerid][pi_ORM], PI[playerid][pi_Z], "z");
		orm_addvar_float(PI[playerid][pi_ORM], PI[playerid][pi_ANGLE], "angle");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_INTERIORID], "interiorid");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_WORLDID], "worldid");
		orm_addvar_float(PI[playerid][pi_ORM], PI[playerid][pi_HEALTH], "health");
		orm_addvar_float(PI[playerid][pi_ORM], PI[playerid][pi_ARMOUR], "armour");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_GENDER], "gender");
		orm_addvar_float(PI[playerid][pi_ORM], PI[playerid][pi_HUNGRY], "hungry");
		orm_addvar_float(PI[playerid][pi_ORM], PI[playerid][pi_THIRST], "thirst");
		orm_addvar_int(PI[playerid][pi_ORM], _:PI[playerid][pi_WORLD_STATE], "world_state");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_WORLD_STATE_INDEX], "world_state_index");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_WORLD_STATE_EXTRA_INDEX], "world_state_extra_index");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_WORLD_STATE_ID], "world_state_id");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_WORLD_STATE_EXTRA_ID], "world_state_extra_id");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_BANK_MONEY], "bank_money");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_KILLS], "kills");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_DEATHS], "deaths");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_AR_WIDTH], "ar_width");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_AR_HEIGHT], "ar_height");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_GPS_MINIMAP], "gps_minimap");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_GPS_LOCATION], "gps_location");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_GPS_ROUTE], "gps_route");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_GPS_OBJECTIVES], "gps_objectives");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_GPS_PROPERTIES], "gps_properties");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_GPS_BUSINESS], "gps_business");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_GPS_VEHICLES], "gps_vehicles");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_PHONE_NUMBER], "phone_number");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_PHONE_ON], "phone_on");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_CLOTHING_CHARACTER], "clothing_character");
		orm_addvar_int(PI[playerid][pi_ORM], _:PI[playerid][pi_CLOTHING_CLOTHE], "clothing_clothe");
		orm_addvar_string(PI[playerid][pi_ORM], PI[playerid][pi_LAST_CHARACTER_CHANGE], 24, "last_character_change");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_HELP_CHANNEL], "help_channel");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_ADMIN_MESSAGES], "admin_messages");
		orm_addvar_int(PI[playerid][pi_ORM], _:PI[playerid][pi_TUTORIAL], "tutorial");
		orm_addvar_int(PI[playerid][pi_ORM], PI[playerid][pi_MPH], "mph");
		orm_setkey(PI[playerid][pi_ORM], "name");
		orm_select(PI[playerid][pi_ORM], "OnAccountDataLoad", "d", playerid);
	}
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(IsPlayerConnected(killerid)) PI[killerid][pi_KILLS] ++;
	PI[playerid][pi_DEATHS] ++;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(!pLoggedIn[playerid]) return 1;
	//set
	PI[playerid][pi_CONNECTED] = false;
	PI[playerid][pi_PLAYERID] = 0;
	getDateTime(PI[playerid][pi_LAST_CONNECTION]);

	//save if exists
	if(PI[playerid][pi_ID])
	{
		if(GetPlayerGameState(playerid) == GAME_STATE_SPAWNED || GetPlayerGameState(playerid) == GAME_STATE_DEAD)
		{
			SavePlayerWorldInfo_DB(playerid);
		}
		orm_update(PI[playerid][pi_ORM]);
	}

	//
	Disconnect_Message(playerid, reason, PI[playerid][pi_RP_NAME]);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	//reset all
	new tmp_PI[enum_PI];
	PI[playerid] = tmp_PI;
	return 1;
}