#include <YSI\y_hooks>

YCMD:aentrance(playerid, params[], help)
{
	new name[45];
	if(!sscanf(params, "s[45]", name))
	{
		inline OnEntranceInserted()
		{
			new msg[128];
			format(msg, sizeof msg, "Entrance added (ID: %d)", cache_insert_id());
			SendClientMessage(playerid, -1, msg);
		}
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO entrances (name) VALUES ('%e');", name);
		mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnEntranceInserted, "");
	}
	else SendClientMessage(playerid, -1, "Syntax: /aentrance <name>");
	return 1;
}

YCMD:adentrance(playerid, params[], help)
{
	new id_entrance, id_interior, time_open, time_close, mapicon_model, pickup_model;
	if(!sscanf(params, "dddddd", id_entrance, id_interior, time_open, time_close, mapicon_model, pickup_model))
	{
		inline OnQueryLoad()
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				if(rows)
				{
					new entrance_name[45];
					cache_get_value_index(0, 0, entrance_name);

					new interior_index = GetInteriorIndexByInteriorId(id_interior);
					if(interior_index == -1) SendClientMessage(playerid, -1, "Invalid interior ID!");
					else
					{
						new sub_ID = 0, sub_Index = -1, sub_Str[16] = "NULL";
						if(PI[playerid][pi_WORLD_STATE] == PLAYER_WORLD_STATE_ENTRANCE)
						{
							if(Entrances[ PI[playerid][pi_WORLD_STATE_INDEX] ][entrance_ID_ENTRANCE] != id_entrance) return SendClientMessage(playerid, -1, "cmd id_entrance != current id_entrance");
							sub_ID = Entrances[ PI[playerid][pi_WORLD_STATE_INDEX] ][entrance_ID_ENTRANCE];
							sub_Index = PI[playerid][pi_WORLD_STATE_INDEX];
							format(sub_Str, sizeof sub_Str, "%d", sub_ID);
						}

						new index = Iter_Free(Entrances);
						if(index != cellmin)
						{
							new Float:pos[4];
							GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
							GetPlayerFacingAngle(playerid, pos[3]);
							inline OnDoorEntranceInserted(string:entrancename[])
							{
								format(Entrances[index][entrance_NAME], 45, "%s", entrancename);
								Entrances[index][entrance_ID] = cache_insert_id();
								Entrances[index][entrance_ID_ENTRANCE] = id_entrance;
								Entrances[index][entrance_ID_INTERIOR] = id_interior;
								Entrances[index][entrance_X] = pos[0];
								Entrances[index][entrance_Y] = pos[1];
								Entrances[index][entrance_Z] = pos[2];
								Entrances[index][entrance_ANGLE] = pos[3];
								Entrances[index][entrance_TIME_OPEN] = time_open;
								Entrances[index][entrance_TIME_CLOSE] = time_close;
								Entrances[index][entrance_MAPICON_MODEL] = mapicon_model;
								Entrances[index][entrance_PICKUP_MODEL] = pickup_model;
								Entrances[index][entrance_SUB_ID] = sub_ID;
								Entrances[index][entrance_INTERIOR_INDEX] = interior_index;
								Entrances[index][entrance_SUB_ID_INDEX] = sub_Index;
								CallRemoteFunction("OnEntranceLoad", "d", index);
								CreateEntranceInfo(index, Entrances[index][entrance_SUB_ID_INDEX]);
								Iter_Add(Entrances, index);

								new msg[128];
								format(msg, sizeof msg, "Door entrance added (ID: %d)", Entrances[index][entrance_ID]);
								SendClientMessage(playerid, -1, msg);
							}
							mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, 
								"\
									INSERT INTO entrances_doors (id_entrance, id_interior, x, y, z, angle, time_open, time_close, mapicon_model, pickup_model, sub_id) \
									VALUES (%d, %d, %f, %f, %f, %f, %d, %d, %d, %d, %s);\
								",
									id_entrance, id_interior, pos[0], pos[1], pos[2], pos[3], time_open, time_close, mapicon_model, pickup_model, sub_Str
							);
							mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnDoorEntranceInserted, "s", entrance_name);
						}
						else SendClientMessage(playerid, -1, "Array full!");
					}
				}
				else SendClientMessage(playerid, -1, "Invalid entrance ID!");
			}
		}
		mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT name FROM entrances WHERE id = %d;", id_entrance);
		mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	}
	else SendClientMessage(playerid, -1, "Syntax: /adentrance <ID Entrance> <ID Interior> <time_open=0> <time_close=0> <mapicon_model=-1> <pickup_model=0>");
	return 1;
}

YCMD:identrances(playerid, params[], help)
{
	new dialog_message[256];
	format(dialog_message, sizeof dialog_message, 
		"Total: %d\nLimit: %d",
		Iter_Count(Entrances), MAX_ENTRANCES
	);

	inline OnPlayerDialog(pid, did, res, lis, string:inp)
	{
		#pragma unused pid, did, res, lis, inp
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "Entrances info", dialog_message, "X", "");
	return 1;
}

YCMD:identrance(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new index = GetEntranceIndexByEntranceDId(params[0]);
		if(index == -1) SendClientMessage(playerid, -1, "Invalid ID!");
		else
		{
			new dialog_message[256];
			format(dialog_message, sizeof dialog_message, 
				"ID Door: %d\nID Entrance (world): %d\nID Interior: %d\nSub ID:%d\nName: %s\nTime open: %d\nTime close: %d\nMapicon model: %d\nPickup model: %d",
				Entrances[index][entrance_ID], Entrances[index][entrance_ID_ENTRANCE], Entrances[index][entrance_ID_INTERIOR], Entrances[index][entrance_SUB_ID],
				Entrances[index][entrance_NAME], Entrances[index][entrance_TIME_OPEN], Entrances[index][entrance_TIME_CLOSE], Entrances[index][entrance_MAPICON_MODEL], Entrances[index][entrance_PICKUP_MODEL]
			);

			inline OnPlayerDialog(pid, did, res, lis, string:inp)
			{
				#pragma unused pid, did, res, lis, inp
			}
			Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "Entrance info", dialog_message, "X", "");
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /identrance <Door ID>");
	return 1;
}

YCMD:gdentrance(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new index = GetEntranceIndexByEntranceDId(params[0]);
		if(index == -1) SendClientMessage(playerid, -1, "Invalid ID!");
		else
		{
			new message[128];
			format(message, sizeof message, "ID Door: %d, ID Entrance (world): %d, ID Interior: %d, Name: %s, Sub_ID: %d", Entrances[ index ][entrance_ID], Entrances[ index ][entrance_ID_ENTRANCE], Entrances[ index ][entrance_ID_INTERIOR], Entrances[ index ][entrance_NAME], Entrances[ index ][entrance_SUB_ID]);
			SendClientMessage(playerid, -1, message);
			if(Entrances[ index ][entrance_SUB_ID_INDEX] == -1)
			{
				SetPlayerPosEx
				(
					playerid,
					Entrances[ index ][entrance_X],
					Entrances[ index ][entrance_Y],
					Entrances[ index ][entrance_Z],
					Entrances[ index ][entrance_ANGLE],
					0,
					VC_WORLD,
					false,
					true,
					true
				);
				SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
			}
			else
			{
				SetPlayerPosEx
				(
					playerid,
					Entrances[ index ][entrance_X],
					Entrances[ index ][entrance_Y],
					Entrances[ index ][entrance_Z],
					Entrances[ index ][entrance_ANGLE],
					Interiors[Entrances[ Entrances[ index ][entrance_SUB_ID_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID],
					Entrances[ Entrances[ index ][entrance_SUB_ID_INDEX] ][entrance_ID_ENTRANCE],
					false,
					true,
					true
				);
				SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_ENTRANCE, Entrances[ index ][entrance_SUB_ID_INDEX]);
			}
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /gotodentrance <Door ID>");
	return 1;
}

YCMD:dentrances(playerid, params[], help)
{
	pCurrentDialogPage[playerid] = 0;

	//
	new dialog_caption[64], count, dialog_str[64], dialog_message[64 * (DIALOG_PAGINATION_SIZE + DIALOG_PAGINATION_EXTRA_BUTTONS)];
	format(dialog_caption, sizeof dialog_caption, "Entrances (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Entrances)));
	foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
	{
		if(Iter_Contains(Entrances, x))
		{
			format(dialog_str, sizeof dialog_str, "%d. %s [%d]\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), Entrances[x][entrance_NAME], Entrances[x][entrance_ID]);
			strcat(dialog_message, dialog_str);
			pExtraButtons[playerid][count++] = x;
		}
	}
	pExtraButtons[playerid][count++] = DIALOG_PAGINATION_NEXT;
	strcat(dialog_message, "\tNext page\n");
	pExtraButtons[playerid][count++] = DIALOG_PAGINATION_PREVIOUS;
	strcat(dialog_message, "\tPrevious page\n");
	//

	inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, inputtext
		if(response)
		{
			switch(pExtraButtons[playerid][listitem])
			{
				case DIALOG_PAGINATION_NEXT:
				{
					pCurrentDialogPage[playerid] = GetNextDialogPage(pCurrentDialogPage[playerid], Iter_Count(Entrances));

					//
					dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
					format(dialog_caption, sizeof dialog_caption, "Entrances (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Entrances)));
					foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
					{
						if(Iter_Contains(Entrances, x))
						{
							format(dialog_str, sizeof dialog_str, "%d. %s [ID Entrance: %d ID Door: %d]\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), Entrances[x][entrance_NAME], Entrances[x][entrance_ID_ENTRANCE], Entrances[x][entrance_ID]);
							strcat(dialog_message, dialog_str);
							pExtraButtons[playerid][count++] = x;
						}
					}
					pExtraButtons[playerid][count++] = DIALOG_PAGINATION_NEXT;
					strcat(dialog_message, "\tNext page\n");
					pExtraButtons[playerid][count++] = DIALOG_PAGINATION_PREVIOUS;
					strcat(dialog_message, "\tPrevious page\n");
					//

					Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_LIST, dialog_caption, dialog_message, "Go", "X");
				}
				case DIALOG_PAGINATION_PREVIOUS:
				{
					pCurrentDialogPage[playerid] = GetPreviousDialogPage(pCurrentDialogPage[playerid], Iter_Count(Entrances));

					//
					dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
					format(dialog_caption, sizeof dialog_caption, "Entrances (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Entrances)));
					foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
					{
						if(Iter_Contains(Entrances, x))
						{
							format(dialog_str, sizeof dialog_str, "%d. %s [%d]\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), Entrances[x][entrance_NAME], Entrances[x][entrance_ID]);
							strcat(dialog_message, dialog_str);
							pExtraButtons[playerid][count++] = x;
						}
					}
					pExtraButtons[playerid][count++] = DIALOG_PAGINATION_NEXT;
					strcat(dialog_message, "\tNext page\n");
					pExtraButtons[playerid][count++] = DIALOG_PAGINATION_PREVIOUS;
					strcat(dialog_message, "\tPrevious page\n");
					//

					Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_LIST, dialog_caption, dialog_message, "Go", "X");
				}
				default:
				{
					new message[128];
					format(message, sizeof message, "ID Door: %d, ID Entrance (world): %d, ID Interior: %d, Name: %s, Sub_ID: %d", Entrances[ pExtraButtons[playerid][listitem] ][entrance_ID], Entrances[ pExtraButtons[playerid][listitem] ][entrance_ID_ENTRANCE], Entrances[ pExtraButtons[playerid][listitem] ][entrance_ID_INTERIOR], Entrances[ pExtraButtons[playerid][listitem] ][entrance_NAME], Entrances[ pExtraButtons[playerid][listitem] ][entrance_SUB_ID]);
					SendClientMessage(playerid, -1, message);
					if(Entrances[ pExtraButtons[playerid][listitem] ][entrance_SUB_ID_INDEX] == -1)
					{
						SetPlayerPosEx
						(
							playerid,
							Entrances[ pExtraButtons[playerid][listitem] ][entrance_X],
							Entrances[ pExtraButtons[playerid][listitem] ][entrance_Y],
							Entrances[ pExtraButtons[playerid][listitem] ][entrance_Z],
							Entrances[ pExtraButtons[playerid][listitem] ][entrance_ANGLE],
							0,
							VC_WORLD,
							false,
							true,
							true
						);
						SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_STREET);
					}
					else
					{
						SetPlayerPosEx
						(
							playerid,
							Entrances[ pExtraButtons[playerid][listitem] ][entrance_X],
							Entrances[ pExtraButtons[playerid][listitem] ][entrance_Y],
							Entrances[ pExtraButtons[playerid][listitem] ][entrance_Z],
							Entrances[ pExtraButtons[playerid][listitem] ][entrance_ANGLE],
							Interiors[Entrances[ Entrances[ pExtraButtons[playerid][listitem] ][entrance_SUB_ID_INDEX] ][entrance_INTERIOR_INDEX]][interior_INTERIORID],
							Entrances[ Entrances[ pExtraButtons[playerid][listitem] ][entrance_SUB_ID_INDEX] ][entrance_ID_ENTRANCE],
							false,
							true,
							true
						);
						SetPlayerWorldState(playerid, PLAYER_WORLD_STATE_ENTRANCE, Entrances[ pExtraButtons[playerid][listitem] ][entrance_SUB_ID_INDEX]);
					}
				}
			}
		}
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_LIST, dialog_caption, dialog_message, "Go", "X");
	return 1;
}

YCMD:ldentrances(playerid, params[], help)
{
	ToggleEntrancesInfoLabels(!entrancesInfoLabels);
	if(entrancesInfoLabels) SendClientMessage(playerid, -1, "Entrances info labels on!");
	else SendClientMessage(playerid, -1, "Entrances info labels off!");
	return 1;
}

YCMD:ddentrance(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new index = GetEntranceIndexByEntranceDId(params[0]);
		if(index == -1) SendClientMessage(playerid, -1, "Invalid ID!");
		else
		{
			DeleteDoorEntrance(index, true);
			SendClientMessage(playerid, -1, "Door entrance deleted!");
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /ddentrance <Door ID>");
	return 1;
}

YCMD:dentrance(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new index = GetEntranceIndexByEntranceId(params[0]);
		if(index == -1) SendClientMessage(playerid, -1, "Invalid ID!");
		else
		{
			DeleteEntrance(params[0], true);
			SendClientMessage(playerid, -1, "Entrance deleted!");
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /dentrance <ID Entrance>");
	return 1;
}