#include <YSI\y_hooks>

#define VC_MODEL_PREVIEW
loadtext lang[vc_mdlpreview];

hook OnScriptInit()
{
	mdlpreview_td[0] = TextDrawCreate(320.000000, 355.000000, "box");
	TextDrawLetterSize(mdlpreview_td[0], 0.000000, 6.233332);
	TextDrawTextSize(mdlpreview_td[0], 0.000000, 150.000000);
	TextDrawAlignment(mdlpreview_td[0], 2);
	TextDrawColor(mdlpreview_td[0], -1);
	TextDrawUseBox(mdlpreview_td[0], 1);
	TextDrawBoxColor(mdlpreview_td[0], 255);
	TextDrawSetShadow(mdlpreview_td[0], 0);
	TextDrawBackgroundColor(mdlpreview_td[0], 255);
	TextDrawFont(mdlpreview_td[0], 1);
	TextDrawSetProportional(mdlpreview_td[0], 1);

	mdlpreview_td[1] = TextDrawCreate(245.000000, 355.000000, "Current_Modelid:~n~Current_Modelid_Type:~n~Total_null_modelids:");
	TextDrawLetterSize(mdlpreview_td[1], 0.263666, 1.251555);
	TextDrawAlignment(mdlpreview_td[1], 1);
	TextDrawColor(mdlpreview_td[1], -1);
	TextDrawSetShadow(mdlpreview_td[1], 0);
	TextDrawBackgroundColor(mdlpreview_td[1], 255);
	TextDrawFont(mdlpreview_td[1], 1);
	TextDrawSetProportional(mdlpreview_td[1], 1);

	mdlpreview_td[2] = TextDrawCreate(395.000000, 377.000000, "0"); //total null modelids
	TextDrawLetterSize(mdlpreview_td[2], 0.263666, 1.251555);
	TextDrawAlignment(mdlpreview_td[2], 3);
	TextDrawColor(mdlpreview_td[2], -1);
	TextDrawSetShadow(mdlpreview_td[2], 0);
	TextDrawBackgroundColor(mdlpreview_td[2], 255);
	TextDrawFont(mdlpreview_td[2], 1);
	TextDrawSetProportional(mdlpreview_td[2], 1);

	mdlpreview_td[3] = TextDrawCreate(370.000000, 395.000000, ">>");
	TextDrawLetterSize(mdlpreview_td[3], 0.263666, 1.251555);
	TextDrawTextSize(mdlpreview_td[3], 10.000000, 47.000000);
	TextDrawAlignment(mdlpreview_td[3], 2);
	TextDrawColor(mdlpreview_td[3], -1);
	TextDrawUseBox(mdlpreview_td[3], 1);
	TextDrawBoxColor(mdlpreview_td[3], -1263225601);
	TextDrawSetShadow(mdlpreview_td[3], 0);
	TextDrawBackgroundColor(mdlpreview_td[3], 255);
	TextDrawFont(mdlpreview_td[3], 1);
	TextDrawSetProportional(mdlpreview_td[3], 1);
	TextDrawSetSelectable(mdlpreview_td[3], true);

	mdlpreview_td[4] = TextDrawCreate(270.000000, 395.000000, "<<");
	TextDrawLetterSize(mdlpreview_td[4], 0.263666, 1.251555);
	TextDrawTextSize(mdlpreview_td[4], 10.000000, 47.000000);
	TextDrawAlignment(mdlpreview_td[4], 2);
	TextDrawColor(mdlpreview_td[4], -1);
	TextDrawUseBox(mdlpreview_td[4], 1);
	TextDrawBoxColor(mdlpreview_td[4], -1263225601);
	TextDrawSetShadow(mdlpreview_td[4], 0);
	TextDrawBackgroundColor(mdlpreview_td[4], 255);
	TextDrawFont(mdlpreview_td[4], 1);
	TextDrawSetProportional(mdlpreview_td[4], 1);
	TextDrawSetSelectable(mdlpreview_td[4], true);

	mdlpreview_td[5] = TextDrawCreate(320.000000, 395.000000, "filter");
	TextDrawLetterSize(mdlpreview_td[5], 0.263666, 1.251555);
	TextDrawTextSize(mdlpreview_td[5], 10.000000, 35.000000);
	TextDrawAlignment(mdlpreview_td[5], 2);
	TextDrawColor(mdlpreview_td[5], -1);
	TextDrawUseBox(mdlpreview_td[5], 1);
	TextDrawBoxColor(mdlpreview_td[5], -1263225601);
	TextDrawSetShadow(mdlpreview_td[5], 0);
	TextDrawBackgroundColor(mdlpreview_td[5], 255);
	TextDrawFont(mdlpreview_td[5], 1);
	TextDrawSetProportional(mdlpreview_td[5], 1);
	TextDrawSetSelectable(mdlpreview_td[5], true);
	return 1;
}

hook OnScriptExit()
{
	TextDrawDestroy(mdlpreview_td[0]);
	TextDrawDestroy(mdlpreview_td[1]);
	TextDrawDestroy(mdlpreview_td[2]);
	TextDrawDestroy(mdlpreview_td[3]);
	TextDrawDestroy(mdlpreview_td[4]);
	TextDrawDestroy(mdlpreview_td[5]);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	mdlpreview_ptd[playerid][0] = CreatePlayerTextDraw(playerid, 395.000000, 355.000000, "0");
	PlayerTextDrawLetterSize(playerid, mdlpreview_ptd[playerid][0], 0.263666, 1.251555);
	PlayerTextDrawTextSize(playerid, mdlpreview_ptd[playerid][0], 440.0, 9.0);
	PlayerTextDrawAlignment(playerid, mdlpreview_ptd[playerid][0], 3);
	PlayerTextDrawColor(playerid, mdlpreview_ptd[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, mdlpreview_ptd[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, mdlpreview_ptd[playerid][0], 255);
	PlayerTextDrawFont(playerid, mdlpreview_ptd[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, mdlpreview_ptd[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, mdlpreview_ptd[playerid][0], true);

	mdlpreview_ptd[playerid][1] = CreatePlayerTextDraw(playerid, 395.000000, 366.000000, "null");
	PlayerTextDrawLetterSize(playerid, mdlpreview_ptd[playerid][1], 0.263666, 1.251555);
	PlayerTextDrawTextSize(playerid, mdlpreview_ptd[playerid][1], 440.0, 9.0);
	PlayerTextDrawAlignment(playerid, mdlpreview_ptd[playerid][1], 3);
	PlayerTextDrawColor(playerid, mdlpreview_ptd[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, mdlpreview_ptd[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, mdlpreview_ptd[playerid][1], 255);
	PlayerTextDrawFont(playerid, mdlpreview_ptd[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, mdlpreview_ptd[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, mdlpreview_ptd[playerid][1], true);

	current_mdlpreview_mdl[playerid] = 0;
	current_mdlpreview_object[playerid] = INVALID_OBJECT_ID;
	mdlpreview_filter[playerid] = false;
	return 1;
}

hook OnPlayerDisconnect(playerid)
{
	PlayerTextDrawDestroy(playerid, mdlpreview_ptd[playerid][0]);
	PlayerTextDrawDestroy(playerid, mdlpreview_ptd[playerid][1]);
	if(current_mdlpreview_object[playerid] != INVALID_OBJECT_ID)
	{
		DestroyPlayerObject(playerid, current_mdlpreview_object[playerid]);
		current_mdlpreview_object[playerid] = INVALID_OBJECT_ID;
	}
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(current_mdlpreview_mdl[playerid] != 0)
	{
		if(clickedid == Text:INVALID_TEXT_DRAW)
		{
			return 1;
		}
		else if(clickedid == mdlpreview_td[3]) //>>
		{
			inline OnQueryLoad()
			{
				new rows;
				if(cache_get_row_count(rows))
				{
					if(rows)
					{
						new model_type, model_type_index;
						cache_get_value_name_int(0, "modelid", current_mdlpreview_mdl[playerid]);
						cache_get_value_name_int(0, "type", model_type);

						model_type_index = GetVCModelTypeIndexById(model_type);
						if(model_type_index == -1) UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], "null");
						else UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], Vc_Models_Types[model_type_index][vc_model_type_NAME]);

						UpdatePlayerVcMdlPreviewObject(playerid);
					}
					else
					{
						inline in_OnQueryLoad()
						{
							new in_rows;
							if(cache_get_row_count(in_rows))
							{
								if(in_rows)
								{
									new model_type, model_type_index;
									cache_get_value_name_int(0, "modelid", current_mdlpreview_mdl[playerid]);
									cache_get_value_name_int(0, "type", model_type);

									model_type_index = GetVCModelTypeIndexById(model_type);
									if(model_type_index == -1) UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], "null");
									else UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], Vc_Models_Types[model_type_index][vc_model_type_NAME]);

									UpdatePlayerVcMdlPreviewObject(playerid);
								}
							}
							else Text_Send(playerid, $MESSAGE_ERROR_DB_ERROR);
						}
						if(mdlpreview_filter[playerid]) mysql_tquery_inline(vc_map_db, "SELECT * FROM models_type WHERE type IS NULL ORDER BY modelid ASC LIMIT 1;", using inline in_OnQueryLoad, "");
						else mysql_tquery_inline(vc_map_db, "SELECT * FROM models_type ORDER BY modelid ASC LIMIT 1;", using inline in_OnQueryLoad, "");
					}
				}
				else Text_Send(playerid, $MESSAGE_ERROR_DB_ERROR);
			}

			if(mdlpreview_filter[playerid]) mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM models_type WHERE modelid > '%d' AND type IS NULL ORDER BY modelid ASC LIMIT 1;", current_mdlpreview_mdl[playerid]);
			else mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM models_type WHERE modelid > '%d' ORDER BY modelid ASC LIMIT 1;", current_mdlpreview_mdl[playerid]);
			mysql_tquery_inline(vc_map_db, QUERY_BUFFER, using inline OnQueryLoad, "");
			return 1;
		}
		else if(clickedid == mdlpreview_td[4]) //<<
		{
			inline OnQueryLoad()
			{
				new rows;
				if(cache_get_row_count(rows))
				{
					if(rows)
					{
						new model_type, model_type_index;
						cache_get_value_name_int(0, "modelid", current_mdlpreview_mdl[playerid]);
						cache_get_value_name_int(0, "type", model_type);

						model_type_index = GetVCModelTypeIndexById(model_type);
						if(model_type_index == -1) UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], "null");
						else UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], Vc_Models_Types[model_type_index][vc_model_type_NAME]);

						UpdatePlayerVcMdlPreviewObject(playerid);
					}
					else
					{
						inline in_OnQueryLoad()
						{
							new in_rows;
							if(cache_get_row_count(in_rows))
							{
								if(in_rows)
								{
									new model_type, model_type_index;
									cache_get_value_name_int(0, "modelid", current_mdlpreview_mdl[playerid]);
									cache_get_value_name_int(0, "type", model_type);

									model_type_index = GetVCModelTypeIndexById(model_type);
									if(model_type_index == -1) UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], "null");
									else UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], Vc_Models_Types[model_type_index][vc_model_type_NAME]);

									UpdatePlayerVcMdlPreviewObject(playerid);
								}
							}
							else Text_Send(playerid, $MESSAGE_ERROR_DB_ERROR);
						}
						if(mdlpreview_filter[playerid]) mysql_tquery_inline(vc_map_db, "SELECT * FROM models_type WHERE type IS NULL ORDER BY modelid DESC LIMIT 1;", using inline in_OnQueryLoad, "");
						else mysql_tquery_inline(vc_map_db, "SELECT * FROM models_type ORDER BY modelid DESC LIMIT 1;", using inline in_OnQueryLoad, "");
					}
				}
				else Text_Send(playerid, $MESSAGE_ERROR_DB_ERROR);
			}

			if(mdlpreview_filter[playerid]) mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM models_type WHERE modelid < '%d' AND type IS NULL ORDER BY modelid DESC LIMIT 1;", current_mdlpreview_mdl[playerid]);
			else mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM models_type WHERE modelid < '%d' ORDER BY modelid DESC LIMIT 1;", current_mdlpreview_mdl[playerid]);
			mysql_tquery_inline(vc_map_db, QUERY_BUFFER, using inline OnQueryLoad, "");
			return 1;
		}
		else if(clickedid == mdlpreview_td[5]) //<<
		{
			if(mdlpreview_filter[playerid])
			{
				Text_Send(playerid, $MESSAGE_INFO_FILTER_OFF);
				mdlpreview_filter[playerid] = false;
			}
			else
			{
				Text_Send(playerid, $MESSAGE_INFO_FILTER_ON);
				mdlpreview_filter[playerid] = true;
			}
			return 1;
		}
	}
	return 0;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
	if(current_mdlpreview_mdl[playerid] != 0)
	{
		if(playertextid == mdlpreview_ptd[playerid][0]) //id
		{
			inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
			{
				#pragma unused pid, dialogid, listitem
				if(response)
				{
					if(sscanf(inputtext, "d", inputtext[0])) return Text_Send(playerid, $MESSAGE_ERROR_WRONG_MODELID_FORMAT);

					inline OnQueryLoad()
					{
						new rows;
						if(cache_get_row_count(rows))
						{
							if(rows)
							{
								new model_type, model_type_index;
								cache_get_value_name_int(0, "modelid", current_mdlpreview_mdl[playerid]);
								cache_get_value_name_int(0, "type", model_type);

								model_type_index = GetVCModelTypeIndexById(model_type);
								if(model_type_index == -1) UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], "null");
								else UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], Vc_Models_Types[model_type_index][vc_model_type_NAME]);

								UpdatePlayerVcMdlPreviewObject(playerid);
							}
							else Text_Send(playerid, $MESSAGE_ERROR_NO_MODELID_FOUND);
						}
						else Text_Send(playerid, $MESSAGE_ERROR_DB_ERROR);
					}

					mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM models_type WHERE modelid = '%d';", inputtext[0]);
					mysql_tquery_inline(vc_map_db, QUERY_BUFFER, using inline OnQueryLoad, "");
				}
			}
			Text_DialogBox(playerid, DIALOG_STYLE_INPUT, using inline OnPlayerDialog, $DIALOG_MODELID_CAPTION, $DIALOG_MODELID_BODY, $DIALOG_MODELID_YES, $DIALOG_MODELID_NO);
			return 1;
		}
		else if(playertextid == mdlpreview_ptd[playerid][1]) //types
		{
			inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
			{
				#pragma unused pid, dialogid, inputtext
				if(response)
				{
					if(listitem == 0)
					{
						if(SaveVcEditorChanges)
						{
							mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE models_type SET type = NULL WHERE modelid = '%d';", current_mdlpreview_mdl[playerid]);
							mysql_tquery(vc_map_db, QUERY_BUFFER, "OnTotalNullModelidsTdUpdate", "");
						}

						SetVcModelidObjectType(current_mdlpreview_mdl[playerid], -1);
						UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], "null");
					}
					else
					{
						listitem --;

						if(SaveVcEditorChanges)
						{
							mysql_format(vc_map_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE models_type SET type = '%d' WHERE modelid = '%d';", Vc_Models_Types[listitem][vc_model_type_ID], current_mdlpreview_mdl[playerid]);
							mysql_tquery(vc_map_db, QUERY_BUFFER, "OnTotalNullModelidsTdUpdate", "");
						}

						SetVcModelidObjectType(current_mdlpreview_mdl[playerid], listitem);
						UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], Vc_Models_Types[listitem][vc_model_type_ID]);
					}
				}
			}

			new dialog[450], line_str[45];
			dialog = "Type\tStreamDistance\nnull\t300.00\n";
			foreach(new i : Vc_Models_Types)
			{
				format(line_str, sizeof line_str, "%s\t%.2f\n", Vc_Models_Types[i][vc_model_type_NAME], Vc_Models_Types[i][vc_model_type_STREAM_DISTANCE]);
				strcat(dialog, line_str);
			}
			Text_DialogBox(playerid, DIALOG_STYLE_TABLIST_HEADERS, using inline OnPlayerDialog, $DIALOG_OBJECT_TYPE_CAPTION, $DIALOG_OBJECT_TYPE_BODY, $DIALOG_OBJECT_TYPE_YES, $DIALOG_OBJECT_TYPE_NO, dialog);
			return 1;
		}
	}
	return 0;
}

public OnTotalNullModelidsTdUpdate()
{
	UpdateTotalNullModelidsTd();
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_FIRE && current_mdlpreview_mdl[playerid] != 0)
	{
		SelectTextDraw(playerid, 0xFFCCFFFF);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return 1;
}

YCMD:gotomdlpreview(playerid, params[], help)
{
	SetPlayerPos(playerid, mdlpreview_pos[0], mdlpreview_pos[1], mdlpreview_pos[2]);
	return 1;
}

YCMD:mdlpreview(playerid, params[], help)
{
	if(current_mdlpreview_mdl[playerid] == 0)
	{
		inline OnQueryLoad()
		{
			new rows;
			if(cache_get_row_count(rows))
			{
				new model_type, model_type_index;
				cache_get_value_name_int(0, "modelid", current_mdlpreview_mdl[playerid]);
				cache_get_value_name_int(0, "type", model_type);

				model_type_index = GetVCModelTypeIndexById(model_type);
				if(model_type_index == -1) UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], "null");
				else UpdatePlayerVcMdlPreviewTds(playerid, current_mdlpreview_mdl[playerid], Vc_Models_Types[model_type_index][vc_model_type_NAME]);

				UpdatePlayerVcMdlPreviewObject(playerid);

				TextDrawShowForPlayer(playerid, mdlpreview_td[0]);
				TextDrawShowForPlayer(playerid, mdlpreview_td[1]);
				TextDrawShowForPlayer(playerid, mdlpreview_td[2]);
				TextDrawShowForPlayer(playerid, mdlpreview_td[3]);
				TextDrawShowForPlayer(playerid, mdlpreview_td[4]);
				TextDrawShowForPlayer(playerid, mdlpreview_td[5]);
				PlayerTextDrawShow(playerid, mdlpreview_ptd[playerid][0]);
				PlayerTextDrawShow(playerid, mdlpreview_ptd[playerid][1]);
				SelectTextDraw(playerid, 0xFFCCFFFF);
				Text_Send(playerid, $MESSAGE_INFO_QUIT);
			}
			else Text_Send(playerid, $MESSAGE_ERROR_DB_ERROR);
		}

		UpdateTotalNullModelidsTd();
		mysql_tquery_inline(vc_map_db, "SELECT * FROM models_type ORDER BY modelid ASC LIMIT 1;", using inline OnQueryLoad, "");
	}
	else
	{
		if(current_mdlpreview_object[playerid] != INVALID_OBJECT_ID)
		{
			DestroyPlayerObject(playerid, current_mdlpreview_object[playerid]);
			current_mdlpreview_object[playerid] = INVALID_OBJECT_ID;
		}

		TextDrawHideForPlayer(playerid, mdlpreview_td[0]);
		TextDrawHideForPlayer(playerid, mdlpreview_td[1]);
		TextDrawHideForPlayer(playerid, mdlpreview_td[2]);
		TextDrawHideForPlayer(playerid, mdlpreview_td[3]);
		TextDrawHideForPlayer(playerid, mdlpreview_td[4]);
		TextDrawHideForPlayer(playerid, mdlpreview_td[5]);
		PlayerTextDrawHide(playerid, mdlpreview_ptd[playerid][0]);
		PlayerTextDrawHide(playerid, mdlpreview_ptd[playerid][1]);
		CancelSelectTextDraw(playerid);

		current_mdlpreview_mdl[playerid] = 0;
	}
	return 1;
}