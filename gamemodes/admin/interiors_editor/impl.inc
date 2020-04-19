#include <YSI\y_hooks>

YCMD:iinteriors(playerid, params[], help)
{
	new dialog_message[256];
	format(dialog_message, sizeof dialog_message, 
		"Total: %d\nLimit: %d",
		Iter_Count(Interiors), MAX_INTERIORS
	);

	inline OnPlayerDialog(pid, did, res, lis, string:inp)
	{
		#pragma unused pid, did, res, lis, inp
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "Interiors info", dialog_message, "X", "");
	return 1;
}

YCMD:iinterior(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new index = GetInteriorIndexByInteriorId(params[0]);
		if(index == -1) SendClientMessage(playerid, -1, "Invalid ID!");
		else
		{
			new dialog_message[256];
			format(dialog_message, sizeof dialog_message, 
				"ID: %d\nName: %s\nInteriorID: %d",
				Interiors[index][interior_ID], Interiors[index][interior_NAME], Interiors[index][interior_INTERIORID]
			);

			inline OnPlayerDialog(pid, did, res, lis, string:inp)
			{
				#pragma unused pid, did, res, lis, inp
			}
			Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, "Interior info", dialog_message, "X", "");
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /iinterior <ID>");
	return 1;
}

YCMD:ginterior(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new index = GetInteriorIndexByInteriorId(params[0]);
		if(index == -1) SendClientMessage(playerid, -1, "Invalid ID!");
		else
		{
			SetPlayerPosEx
			(
				playerid,
				Interiors[index][interior_X],
				Interiors[index][interior_Y],
				Interiors[index][interior_Z],
				Interiors[index][interior_ANGLE],
				Interiors[index][interior_INTERIORID]
			);
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /ginterior <ID>");
	return 1;
}

YCMD:linteriors(playerid, params[], help)
{
	ToggleInteriorsInfoLabels(!interiorsInfoLabels);
	if(interiorsInfoLabels) SendClientMessage(playerid, -1, "Interiors info labels on!");
	else SendClientMessage(playerid, -1, "Interiors info labels off!");
	return 1;
}

YCMD:ainterior(playerid, params[], help)
{
	new name[45];
	if(!sscanf(params, "s[45]", name))
	{
		new index = Iter_Free(Interiors);
		if(index != cellmin)
		{
			new interiorid, Float:pos[3], Float:angle;
			interiorid = GetPlayerInterior(playerid);
			GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
			GetPlayerFacingAngle(playerid, angle);
			inline OnInteriorInserted(string:interiorname[])
			{
				Interiors[index][interior_ID] = cache_insert_id();
				format(Interiors[index][interior_NAME], 45, "%s", interiorname);
				Interiors[index][interior_X] = pos[0];
				Interiors[index][interior_Y] = pos[1];
				Interiors[index][interior_Z] = pos[2];
				Interiors[index][interior_ANGLE] = angle;
				Interiors[index][interior_INTERIORID] = interiorid;
				Iter_Add(Interiors, index);

				new msg[128];
				format(msg, sizeof msg, "Interior added (ID: %d)", Interiors[index][interior_ID]);
				SendClientMessage(playerid, -1, msg);
			}
			mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO interiors (name, interiorid, x, y, z, angle) VALUES ('%e', %d, %f, %f, %f, %f);", name, interiorid, pos[0], pos[1], pos[2], angle);
			mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnInteriorInserted, "s", name);
		}
		else SendClientMessage(playerid, -1, "Array full!");
	}
	else SendClientMessage(playerid, -1, "Syntax: /ainterior <name>");
	return 1;
}

YCMD:dinterior(playerid, params[], help)
{
	if(!sscanf(params, "d", params[0]))
	{
		new index = GetInteriorIndexByInteriorId(params[0]);
		if(index == -1) SendClientMessage(playerid, -1, "Invalid ID!");
		else
		{
			DeleteInterior(index, true);
			SendClientMessage(playerid, -1, "Interior deleted!");
		}
	}
	else SendClientMessage(playerid, -1, "Syntax: /dinterior <ID>");
	return 1;
}

YCMD:interiors(playerid, params[], help)
{
	pCurrentDialogPage[playerid] = 0;

	//
	new dialog_caption[64], count, dialog_str[64], dialog_message[64 * (DIALOG_PAGINATION_SIZE + DIALOG_PAGINATION_EXTRA_BUTTONS)]; 
	format(dialog_caption, sizeof dialog_caption, "Interiors (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Interiors)));
	foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
	{
		if(Iter_Contains(Interiors, x))
		{
			format(dialog_str, sizeof dialog_str, "%d. %s [%d]\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), Interiors[x][interior_NAME], Interiors[x][interior_ID]);
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
					pCurrentDialogPage[playerid] = GetNextDialogPage(pCurrentDialogPage[playerid], Iter_Count(Interiors));

					//
					dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
					format(dialog_caption, sizeof dialog_caption, "Interiors (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Interiors)));
					foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
					{
						if(Iter_Contains(Interiors, x))
						{
							format(dialog_str, sizeof dialog_str, "%d. %s [%d]\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), Interiors[x][interior_NAME], Interiors[x][interior_ID]);
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
					pCurrentDialogPage[playerid] = GetPreviousDialogPage(pCurrentDialogPage[playerid], Iter_Count(Interiors));

					//
					dialog_caption[0] = EOS, count = 0, dialog_str[0] = EOS, dialog_message[0] = EOS;
					format(dialog_caption, sizeof dialog_caption, "Interiors (%d/%d)", pCurrentDialogPage[playerid] + 1, GetDialogPages(Iter_Count(Interiors)));
					foreach(new x : Range(DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid], (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]) + DIALOG_PAGINATION_SIZE))
					{
						if(Iter_Contains(Interiors, x))
						{
							format(dialog_str, sizeof dialog_str, "%d. %s [%d]\n", (count + 1) + (DIALOG_PAGINATION_SIZE * pCurrentDialogPage[playerid]), Interiors[x][interior_NAME], Interiors[x][interior_ID]);
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
					format(message, sizeof message, "ID: %d, Name: %s, InteriorID: %d", Interiors[ pExtraButtons[playerid][listitem] ][interior_ID], Interiors[ pExtraButtons[playerid][listitem] ][interior_NAME], Interiors[ pExtraButtons[playerid][listitem] ][interior_INTERIORID]);
					SendClientMessage(playerid, -1, message);
					SetPlayerPosEx
					(
						playerid,
						Interiors[ pExtraButtons[playerid][listitem] ][interior_X],
						Interiors[ pExtraButtons[playerid][listitem] ][interior_Y],
						Interiors[ pExtraButtons[playerid][listitem] ][interior_Z],
						Interiors[ pExtraButtons[playerid][listitem] ][interior_ANGLE],
						Interiors[ pExtraButtons[playerid][listitem] ][interior_INTERIORID]
					);
				}
			}
		}
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_LIST, dialog_caption, dialog_message, "Go", "X");
	return 1;
}