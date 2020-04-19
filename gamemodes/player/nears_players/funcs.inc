loadtext lang[nears_players];

NearsPlayersDialog(playerid, id, bool:player = false)
{
	SavePlayerWorldInfo(playerid);

	new dialog_message[45 * MAX_NEARS_PLAYERS_DIALOG], line_str[45], count;

	if(player)
	{
		format(line_str, sizeof line_str, "- %s (%s, %d)\n", GetPlayerMeMessage(playerid), PI[playerid][pi_RP_NAME], playerid);
		strcat(dialog_message, line_str);

		pNearsPlayersId[playerid][count][0] = playerid;
		pNearsPlayersId[playerid][count][1] = PI[playerid][pi_ID];
		count ++;
	}
	foreach(new i : Player)
	{
		if(i == playerid) continue;
		if(IsPlayerNearPlayer(playerid, i, false))
		{
			if(count >= MAX_NEARS_PLAYERS_DIALOG) break;

			format(line_str, sizeof line_str, "- %s (%d)\n", PI[i][pi_RP_NAME], i);
			strcat(dialog_message, line_str);

			pNearsPlayersId[playerid][count][0] = i;
			pNearsPlayersId[playerid][count][1] = PI[i][pi_ID];
			count ++;
		}
	}
	
	if(isnull(dialog_message))
	{
		Text_Send(playerid, $MESSAGE_ERROR_NO_NEAR_PLAYERS);
		return 0;
	}
	else
	{
		inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
		{
			#pragma unused pid, dialogid, inputtext
			if(response)
			{
				//check
				if(!IsPlayerConnected(pNearsPlayersId[playerid][listitem][0])) return Text_Send(playerid, $MESSAGE_ERROR_SELECTED_PLAYER_GONE);
				if(pNearsPlayersId[playerid][listitem][1] != PI[ pNearsPlayersId[playerid][listitem][0] ][pi_ID]) return Text_Send(playerid, $MESSAGE_ERROR_SELECTED_PLAYER_GONE);

				//world info check
				if(!IsPlayerNearPlayer(playerid, pNearsPlayersId[playerid][listitem][0])) Text_Send(playerid, $MESSAGE_ERROR_SELECTED_PLAYER_GONE);
				else CallRemoteFunction("OnSelectNearPlayer", "idi", playerid, id, pNearsPlayersId[playerid][listitem][0]);
			}
		}
		Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_LIST, GetNearPlayersCaption(playerid), dialog_message, ">>", "X");
		return 1;
	}
}

IsPlayerNearPlayer(playerid, to_playerid, bool:update = true)
{
	if(update) SavePlayerWorldInfo(playerid);

	if(GetPlayerGameState(to_playerid) == GAME_STATE_SPAWNED)
	{
		if(GetPlayerDistanceFromPoint(to_playerid, PI[playerid][pi_X], PI[playerid][pi_Y], PI[playerid][pi_Z]) <= NEARS_PLAYERS_VALID_DISTANCE && GetPlayerInterior(to_playerid) == PI[playerid][pi_INTERIORID] && GetPlayerVirtualWorld(to_playerid) == PI[playerid][pi_WORLDID])
		{
			return true;
		}
	}
	return false;
}

GetNearPlayersCaption(playerid)
{
	new caption[32];
	Text_Format_Dialog(caption, sizeof caption, PI[playerid][pi_LANG_ID], $DIALOG_CAPTION);
	return caption;
}

GetPlayerMeMessage(playerid)
{
	new caption[24];
	Text_Format_Dialog(caption, sizeof caption, PI[playerid][pi_LANG_ID], $DIALOG_ME);
	return caption;
}