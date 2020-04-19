#include <YSI\y_hooks>

loadtext lang[admin_player];

hook OnPlayerLogin(playerid)
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			if(rows)
			{
				new id_history, bool:isnull_id_admin, id_admin, type, bool:isnull_reason, reason[256], date[24], bool:isnull_expire_date, expire_date[24],
					time_now[24], bool:isnull_time_diff_sec, time_diff_sec;
				cache_get_value_name_int(0, "id", id_history);
				cache_is_value_name_null(0, "id_admin", isnull_id_admin);
				if(!isnull_id_admin) cache_get_value_name_int(0, "id_admin", id_admin);
				cache_get_value_name_int(0, "type", type);
				cache_is_value_name_null(0, "reason", isnull_reason);
				if(!isnull_reason) cache_get_value_name(0, "reason", reason);
				cache_get_value_name(0, "date", date);
				cache_is_value_name_null(0, "expire_date", isnull_expire_date);
				if(!isnull_expire_date) cache_get_value_name(0, "expire_date", expire_date);
				cache_get_value_name(0, "time_now", time_now);
				cache_is_value_name_null(0, "time_diff_sec", isnull_time_diff_sec);
				if(!isnull_time_diff_sec) cache_get_value_name_int(0, "time_diff_sec", time_diff_sec);
				//ok
				switch(type)
				{
					case RESTRICTION_TYPE_PERM_BAN:
					{
						inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
						{
							#pragma unused pid, dialogid, response, listitem, inputtext
						}
						Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_INFO_PERM_BANNED_CAPTION, $DIALOG_INFO_PERM_BANNED_BODY, $DIALOG_INFO_PERM_BANNED_YES, "", id_history, reason, date);
						TimedKick(playerid);
					}
					case RESTRICTION_TYPE_TEMP_BAN:
					{
						if(time_diff_sec <= 0)
						{
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_admin_restrictions WHERE id_player = %d;", PI[playerid][pi_IP]);
							mysql_tquery(vcrp_db, QUERY_BUFFER);
							Text_Send(playerid, $MESSAGE_WARNING_UNBANNED);
						}
						else
						{
							inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
							{
								#pragma unused pid, dialogid, response, listitem, inputtext
							}
							Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_INFO_TEMP_BANNED_CAPTION, $DIALOG_INFO_TEMP_BANNED_BODY, $DIALOG_INFO_TEMP_BANNED_YES, "", id_history, reason, date, time_now, expire_date);
							TimedKick(playerid);
						}
					}
				}
			}
		}
	}
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT player_admin_history.*, NOW() AS time_now, TIMESTAMPDIFF(SECOND, NOW(), player_admin_history.expire_date) AS time_diff_sec FROM player_admin_restrictions INNER JOIN player_admin_history ON player_admin_history.id = player_admin_restrictions.id_history WHERE player_admin_restrictions.id_player = %d OR player_admin_restrictions.ip = '%s';", PI[playerid][pi_ID], PI[playerid][pi_IP]);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	return 1;
}

YCMD:report(playerid, params[], help)
{
	new to_playerid, reason[145];
	if(!sscanf(params, "us[145]", to_playerid, reason))
	{
		if(!IsPlayerConnected(to_playerid)) Text_Send(playerid, $MESSAGE_ERROR_PDISCONNECTED);
		else
		{
			foreach(new i : Player)
			{
				if(PI[i][pi_ADMIN_LEVEL])
				{
					Text_Send(i, $MESSAGE_WARNING_REPORT, PI[playerid][pi_NAME], playerid, PI[to_playerid][pi_NAME], to_playerid, reason);
				}
			}
			Text_Send(playerid, $MESSAGE_INFO_REPORT_SENT);
		}
	}
	else Text_Send(playerid, $MESSAGE_ERROR_SYNTAX_REPORT);
	return 1;
}

YCMD:setthirst(playerid, params[], help)
{
	new pid, Float:value;
	if(sscanf(params, "df", pid, value)) SendClientMessage(playerid, -1, "Syntax: /setthirst [playerid] [value]");
	else PI[pid][pi_THIRST] = value;
	return 1;
}

YCMD:sethungry(playerid, params[], help)
{
	new pid, Float:value;
	if(sscanf(params, "df", pid, value)) SendClientMessage(playerid, -1, "Syntax: /sethungry [playerid] [value]");
	else PI[pid][pi_HUNGRY] = value;
	return 1;
}

YCMD:sethealth(playerid, params[], help)
{
	new pid, Float:health;
	if(sscanf(params, "uf", pid, health)) return SendClientMessage(playerid, -1, "Syntax: /sethealth [id] [health]");
	SetPlayerHealthEx(pid, health);
	return 1;
}

YCMD:setarmour(playerid, params[], help)
{
	new pid, Float:armour;
	if(sscanf(params, "uf", pid, armour)) return SendClientMessage(playerid, -1, "Syntax: /setarmour [id] [armour]");
	SetPlayerArmourEx(pid, armour);
	return 1;
}

YCMD:setmoney(playerid, params[], help)
{
	if(sscanf(params, "ud", params[0], params[1])) return SendClientMessage(playerid, -1, "Syntax: /setmoney [playerid] [int]");
	
	PI[params[0]][pi_MONEY] = params[1];
	SetPlayerMoney(params[0]);
	return 1;
}

YCMD:givemoney(playerid, params[], help)
{
	if(sscanf(params, "ud", params[0], params[1])) return SendClientMessage(playerid, -1, "Syntax: /givemoney [playerid] [int]");
	GivePlayerMoneyEx(params[0], params[1]);
	return 1;
}

YCMD:setlevel(playerid, params[], help)
{
	if(sscanf(params, "ud", params[0], params[1])) return SendClientMessage(playerid, -1, "Syntax: /setlevel [playerid] [int]");
	PI[params[0]][pi_REPUTATION] = 1.0;
	PI[params[0]][pi_LEVEL] = params[1];
	orm_update(PI[params[0]][pi_ORM]);
	FormatPtaskInfoMessage(params[0], 0);
	SetPlayerScore(params[0], PI[params[0]][pi_LEVEL]);
	return 1;
}

YCMD:goto(playerid, params[], help)
{
	if(!sscanf(params, "u", params[0]))
	{
		new Float:pos[4];
		GetPlayerPos(params[0], pos[0], pos[1], pos[2]);
		GetPlayerFacingAngle(params[0], pos[3]);
		PI[playerid][pi_X] = pos[0];
		PI[playerid][pi_Y] = pos[1];
		PI[playerid][pi_Z] = pos[2];
		PI[playerid][pi_ANGLE] = pos[3];
		PI[playerid][pi_INTERIORID] = GetPlayerInterior(params[0]);
		PI[playerid][pi_WORLDID] = GetPlayerVirtualWorld(params[0]);
		SetPlayerWorldState(playerid, PI[params[0]][pi_WORLD_STATE], _:PI[params[0]][pi_WORLD_STATE_INDEX], PI[params[0]][pi_WORLD_STATE_EXTRA_INDEX]);
		SetPlayerPosEx(playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z], PI[playerid][pi_ANGLE], PI[playerid][pi_INTERIORID], PI[playerid][pi_WORLDID], false);	
	}
	else SendClientMessage(playerid, -1, "Syntax: /goto [playerid]");
	return 1;
}

YCMD:get(playerid, params[], help)
{
	if(!sscanf(params, "u", params[0]))
	{
		new Float:pos[4];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		GetPlayerFacingAngle(playerid, pos[3]);
		PI[params[0]][pi_X] = pos[0];
		PI[params[0]][pi_Y] = pos[1];
		PI[params[0]][pi_Z] = pos[2];
		PI[params[0]][pi_ANGLE] = pos[3];
		PI[params[0]][pi_INTERIORID] = GetPlayerInterior(playerid);
		PI[params[0]][pi_WORLDID] = GetPlayerVirtualWorld(playerid);
		SetPlayerWorldState(params[0], PI[playerid][pi_WORLD_STATE], _:PI[playerid][pi_WORLD_STATE_INDEX], PI[playerid][pi_WORLD_STATE_EXTRA_INDEX]);
		SetPlayerPosEx(params[0], PI[params[0]][pi_X], PI[params[0]][pi_Y], PI[params[0]][pi_Z], PI[params[0]][pi_ANGLE], PI[params[0]][pi_INTERIORID], PI[params[0]][pi_WORLDID], false);	
	}
	else SendClientMessage(playerid, -1, "Syntax: /get [playerid]");
	return 1;
}

YCMD:ban(playerid, params[], help)
{
	new to_playerid, reason[256];
	if(!sscanf(params, "us[256]", to_playerid, reason))
	{
		if(!IsPlayerConnected(to_playerid)) SendClientMessage(playerid, -1, "Error! player not connected.");
		else if(PI[playerid][pi_ID] == 0) SendClientMessage(playerid, -1, "Error! player not logged.");
		else
		{
			new date[24];
			getDateTime(date);
			inline OnQueryInserted(string:ban_reason[], string:ban_date[])
			{
				new id_history = cache_insert_id();
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_admin_restrictions (id_player, ip, id_history) VALUES (%d, '%s', %d);", PI[to_playerid][pi_ID], PI[to_playerid][pi_IP], id_history);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
				inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
				{
					#pragma unused pid, dialogid, response, listitem, inputtext
				}
				Text_DialogBox(to_playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_INFO_PERM_BANNED_CAPTION, $DIALOG_INFO_PERM_BANNED_BODY, $DIALOG_INFO_PERM_BANNED_YES, "", id_history, ban_reason, ban_date);
				CallRemoteFunction("OnPlayerGetAdminPunishment", "isids", to_playerid, PI[to_playerid][pi_NAME], playerid, PUNISHMENT_TYPE_PERM_BAN, ban_reason);
				TimedKick(to_playerid);
				SendClientMessage(playerid, -1, "Player banned!");
			}
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_admin_history (id_admin, id_player, type, reason, date) VALUES (%d, %d, %d, '%e', '%s');", PI[playerid][pi_ID], PI[to_playerid][pi_ID], RESTRICTION_TYPE_PERM_BAN, reason, date);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryInserted, "ss", reason, date);
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /ban [playerid] [reason]");
	return 1;
}

YCMD:kick(playerid, params[], help)
{
	new to_playerid, reason[256];
	if(!sscanf(params, "us[256]", to_playerid, reason))
	{
		if(!IsPlayerConnected(to_playerid)) SendClientMessage(playerid, -1, "Error! player not connected.");
		else if(PI[playerid][pi_ID] == 0) SendClientMessage(playerid, -1, "Error! player not logged.");
		else
		{
			new date[24];
			getDateTime(date);
			inline OnQueryInserted(string:kick_reason[])
			{
				Text_Send(to_playerid, $MESSAGE_WARNING_KICKED, kick_reason);
				CallRemoteFunction("OnPlayerGetAdminPunishment", "isids", to_playerid, PI[to_playerid][pi_NAME], playerid, PUNISHMENT_TYPE_KICK, kick_reason);
				TimedKick(to_playerid);
				SendClientMessage(playerid, -1, "Player kicked!");
			}
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_admin_history (id_admin, id_player, type, reason, date) VALUES (%d, %d, %d, '%e', '%e');", PI[playerid][pi_ID], PI[to_playerid][pi_ID], RESTRICTION_TYPE_KICK, reason, date);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryInserted, "s", reason);
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /kick [playerid] [reason]");
	return 1;
}

YCMD:tban(playerid, params[], help)
{
	new to_playerid, days, reason[256];
	if(!sscanf(params, "uds[256]", to_playerid, days, reason))
	{
		if(!IsPlayerConnected(to_playerid)) SendClientMessage(playerid, -1, "Error! player not connected.");
		else if(PI[playerid][pi_ID] == 0) SendClientMessage(playerid, -1, "Error! player not logged.");
		else
		{
			new date[24];
			getDateTime(date);
			inline OnQueryInserted(string:ban_reason[], string:ban_date[])
			{
				new id_history = cache_insert_id();
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_admin_restrictions (id_player, ip, id_history) VALUES (%d, '%s', %d);", PI[to_playerid][pi_ID], PI[to_playerid][pi_IP], id_history);
				mysql_tquery(vcrp_db, QUERY_BUFFER);
				inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
				{
					#pragma unused pid, dialogid, response, listitem, inputtext
				}
				Text_DialogBox(to_playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_INFO_TEMP_BANNED_CAPTION, $DIALOG_INFO_TEMP_BANNED_BODY, $DIALOG_INFO_TEMP_BANNED_YES, "", id_history, ban_reason, ban_date, ban_date, "0");
				Text_Send(to_playerid, $MESSAGE_WARNING_TEMP_BAN, days);
				CallRemoteFunction("OnPlayerGetAdminPunishment", "isids", to_playerid, PI[to_playerid][pi_NAME], playerid, PUNISHMENT_TYPE_TEMP_BAN, ban_reason);
				TimedKick(to_playerid);
				SendClientMessage(playerid, -1, "Player banned!");
			}
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_admin_history (id_admin, id_player, type, reason, date, expire_date) VALUES (%d, %d, %d, '%e', '%s', DATE_ADD(NOW(), INTERVAL %d DAY));", PI[playerid][pi_ID], PI[to_playerid][pi_ID], RESTRICTION_TYPE_TEMP_BAN, reason, date, days);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryInserted, "ss", reason, date);
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /tban [playerid] [reason]");
	return 1;
}

YCMD:unban(playerid, params[], help)
{
	new to_pid;
	if(!sscanf(params, "d", to_pid))
	{
		if(to_pid <= 0) SendClientMessage(playerid, -1, "Invalid ID!");
		else
		{
			inline OnQueryLoad()
			{
				new rows;
				if(cache_get_row_count(rows))
				{
					if(rows)
					{
						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "DELETE FROM player_admin_restrictions WHERE id_player = %d;", to_pid);
						mysql_tquery(vcrp_db, QUERY_BUFFER);
						SendClientMessage(playerid, -1, "Player unbanned!");
					}
					else SendClientMessage(playerid, -1, "Invalid ID or not banned!");
				}
			}
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM player_admin_restrictions WHERE id_player = %d;", to_pid);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad);
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /unban [PID]");
	return 1;
}

YCMD:settime(playerid, params[], help)
{
	new hour, minute;
	if(!sscanf(params, "dd", hour, minute))
	{
		SERVER_TIME[0] = hour;
		SERVER_TIME[1] = minute;
	}
	else SendClientMessage(playerid, -1, "Syntax: /settime [int] [int]");
	return 1;
}

YCMD:setweather(playerid, params[], help)
{
	new weatherid;
	if(!sscanf(params, "d", weatherid))
	{
		SERVER_WEATHER = weatherid;
		SetWeather(weatherid);
	}
	else SendClientMessage(playerid, -1, "Syntax: /settime [int]");
	return 1;
}

YCMD:con(playerid, params[], help)
{
	new stats[400+1];
	GetNetworkStats(stats, sizeof(stats));
	inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, response, listitem, inputtext
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "network stats", stats, "X", "");
	return 1;
}

YCMD:spec(playerid, params[], help)
{
	new to_playerid;
	if(!sscanf(params, "u", to_playerid))
	{
		if(!IsPlayerConnected(to_playerid)) SendClientMessage(playerid, -1, "Error! player not connected.");
		else
		{
			SavePlayerWorldInfo(playerid);
			TogglePlayerSpectating(playerid, true);
			SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(to_playerid));
			SetPlayerInterior(playerid, GetPlayerInterior(to_playerid));
			if(IsPlayerInAnyVehicle(to_playerid)) PlayerSpectateVehicle(playerid, GetPlayerVehicleID(to_playerid));
			else PlayerSpectatePlayer(playerid, to_playerid);
		}
	}
	else
	{
		LoadScreenTimed(playerid);
		TogglePlayerSpectating(playerid, false);
	}
	return 1;
}

YCMD:setalevel(playerid, params[], help)
{
	new to_playerid, level;
	if(!sscanf(params, "ud", to_playerid, level)) SetPlayerAdminLevel(to_playerid, level);
	else SendClientMessage(playerid, -1, "Syntax: /setalevel [playerid] [int]");
	return 1;
}

YCMD:getid(playerid, params[], help)
{
	new name[24];
	if(!sscanf(params, "s[24]", name))
	{
		inline OnQueryLoad()
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				if(rows)
				{
					new string[145];
					for(new i = 0; i < rows; i ++)
					{
						new pid, dname[24], connected, dplayerid;
						cache_get_value_name_int(i, "id", pid);
						cache_get_value_name(i, "name", dname);
						cache_get_value_name_int(i, "connected", connected);
						cache_get_value_name_int(i, "playerid", dplayerid);
						format(string, sizeof string, "PID: %d, Name: %s, Connected: %d, Playerid: %d", pid, dname, connected, dplayerid);
						SendClientMessage(playerid, -1, string);
					}
				}
				else SendClientMessage(playerid, -1, "no results");
			}
		}
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT id, name, connected, playerid FROM player WHERE name LIKE '%%%e%%';", name);
		mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad);
	}
	else SendClientMessage(playerid, -1, "Syntax: /getid [string]");
	return 1;
}

YCMD:getname(playerid, params[], help)
{
	new pid;
	if(!sscanf(params, "d", pid))
	{
		inline OnQueryLoad()
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				if(rows)
				{
					new string[145], dpid, dname[24], connected, dplayerid;
					cache_get_value_name_int(0, "id", dpid);
					cache_get_value_name(0, "name", dname);
					cache_get_value_name_int(0, "connected", connected);
					cache_get_value_name_int(0, "playerid", dplayerid);
					format(string, sizeof string, "PID: %d, Name: %s, Connected: %d, Playerid: %d", dpid, dname, connected, dplayerid);
					SendClientMessage(playerid, -1, string);
				}
				else SendClientMessage(playerid, -1, "no results");
			}
		}
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT id, name, connected, playerid FROM player WHERE id = %d;", pid);
		mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad);
	}
	else SendClientMessage(playerid, -1, "Syntax: /getname [int]");
	return 1;
}

YCMD:dban(playerid, params[], help)
{
	new to_pid, reason[256];
	if(!sscanf(params, "ds[256]", to_pid, reason))
	{
		inline OnQueryLoad(string:reason_pass[])
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				if(rows)
				{
					new dname[24], connected, ip[16];
					cache_get_value_name(0, "name", dname);
					cache_get_value_name_int(0, "connected", connected);
					cache_get_value_name(0, "ip", ip);
					if(connected) SendClientMessage(playerid, -1, "Player is connected, use /ban.");
					else
					{
						new date[24];
						getDateTime(date);
						inline OnQueryInserted(string:ban_ip[])
						{
							new id_history = cache_insert_id();
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_admin_restrictions (id_player, ip, id_history) VALUES (%d, '%s', %d);", to_pid, ban_ip, id_history);
							mysql_tquery(vcrp_db, QUERY_BUFFER);
							SendClientMessage(playerid, -1, "Player banned!");
						}
						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_admin_history (id_admin, id_player, type, reason, date) VALUES (%d, %d, %d, '%e', '%s');", PI[playerid][pi_ID], to_pid, RESTRICTION_TYPE_PERM_BAN, reason_pass, date);
						mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryInserted, "s", ip);
					}
				}
				else SendClientMessage(playerid, -1, "pid not found!");
			}
		}
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT name, connected, ip FROM player WHERE id = %d;", to_pid);
		mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "s", reason);
	}
	else SendClientMessage(playerid, -1, "Syntax: /dban [pid] [reason]");
	return 1;
}

YCMD:dtban(playerid, params[], help)
{
	new to_pid, days, reason[256];
	if(!sscanf(params, "dds[256]", to_pid, days, reason))
	{
		inline OnQueryLoad(string:reason_pass[])
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				if(rows)
				{
					new dname[24], connected, ip[16];
					cache_get_value_name(0, "name", dname);
					cache_get_value_name_int(0, "connected", connected);
					cache_get_value_name(0, "ip", ip);
					if(connected) SendClientMessage(playerid, -1, "Player is connected, use /ban.");
					else
					{
						new date[24];
						getDateTime(date);
						inline OnQueryInserted(string:ban_ip[])
						{
							new id_history = cache_insert_id();
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_admin_restrictions (id_player, ip, id_history) VALUES (%d, '%s', %d);", to_pid, ban_ip, id_history);
							mysql_tquery(vcrp_db, QUERY_BUFFER);
							SendClientMessage(playerid, -1, "Player banned!");
						}
						mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_admin_history (id_admin, id_player, type, reason, date, expire_date) VALUES (%d, %d, %d, '%e', '%s', DATE_ADD(NOW(), INTERVAL %d DAY));", PI[playerid][pi_ID], to_pid, RESTRICTION_TYPE_TEMP_BAN, reason_pass, date, days);
						mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryInserted, "s", ip);
					}
				}
				else SendClientMessage(playerid, -1, "pid not found!");
			}
		}
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT name, connected, ip FROM player WHERE id = %d;", to_pid);
		mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "s", reason);
	}
	else SendClientMessage(playerid, -1, "Syntax: /dban [pid] [reason]");
	return 1;
}

YCMD:asay(playerid, params[], help)
{
	new str[145];
	format(str, 145, "* Admin: %s", params);
	SendClientMessageToAll(0x2587CEFF, str);
	return 1;
}