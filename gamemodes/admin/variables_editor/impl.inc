#include <YSI\y_hooks>

YCMD:svariables(playerid, params[], help)
{
	inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, inputtext
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					inline OnPlayerEditDialog(ex_pid, ex_dialogid, ex_response, ex_listitem, string:ex_inputtext[])
					{
						#pragma unused ex_pid, ex_dialogid, ex_listitem
						if(ex_response)
						{
							new Float:value;
							if(sscanf(ex_inputtext, "f", value)) SendClientMessage(playerid, -1, "Wrong format!");
							else
							{
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE variables SET value = '%f' WHERE name = 'vehicle_depreciation';", value);
								mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
								vehicle_depreciation = value;

								new info_message[128];
								format(info_message, sizeof info_message, "vehicle_depreciation: %f", vehicle_depreciation);
								SendClientMessage(playerid, -1, info_message);
							}
						}
					}

					new edit_dialog_message[64];
					format(edit_dialog_message, sizeof edit_dialog_message, "current value: %f", vehicle_depreciation);
					Dialog_ShowCallback(playerid, using inline OnPlayerEditDialog, DIALOG_STYLE_INPUT, "vehicle_depreciation", edit_dialog_message, "Edit", "X");					
				}
				case 1:
				{
					inline OnPlayerEditDialog(ex_pid, ex_dialogid, ex_response, ex_listitem, string:ex_inputtext[])
					{
						#pragma unused ex_pid, ex_dialogid, ex_listitem
						if(ex_response)
						{
							new Float:value;
							if(sscanf(ex_inputtext, "f", value)) SendClientMessage(playerid, -1, "Wrong format!");
							else
							{
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE variables SET value = '%f' WHERE name = 'vehicle_depreciation_kms';", value);
								mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
								vehicle_depreciation_kms = value;
								
								new info_message[128];
								format(info_message, sizeof info_message, "vehicle_depreciation_kms: %f", vehicle_depreciation_kms);
								SendClientMessage(playerid, -1, info_message);
							}
						}
					}

					new edit_dialog_message[64];
					format(edit_dialog_message, sizeof edit_dialog_message, "current value: %f", vehicle_depreciation_kms);
					Dialog_ShowCallback(playerid, using inline OnPlayerEditDialog, DIALOG_STYLE_INPUT, "vehicle_depreciation_kms", edit_dialog_message, "Edit", "X");					
				}
				case 2:
				{
					inline OnPlayerEditDialog(ex_pid, ex_dialogid, ex_response, ex_listitem, string:ex_inputtext[])
					{
						#pragma unused ex_pid, ex_dialogid, ex_listitem
						if(ex_response)
						{
							new Float:value;
							if(sscanf(ex_inputtext, "f", value)) SendClientMessage(playerid, -1, "Wrong format!");
							else
							{
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE variables SET value = '%f' WHERE name = 'vehicle_depreciation_value';", value);
								mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
								vehicle_depreciation_value = value;
								
								new info_message[128];
								format(info_message, sizeof info_message, "vehicle_depreciation_value: %f", vehicle_depreciation_value);
								SendClientMessage(playerid, -1, info_message);
							}
						}
					}

					new edit_dialog_message[64];
					format(edit_dialog_message, sizeof edit_dialog_message, "current value: %f", vehicle_depreciation_value);
					Dialog_ShowCallback(playerid, using inline OnPlayerEditDialog, DIALOG_STYLE_INPUT, "vehicle_depreciation_value", edit_dialog_message, "Edit", "X");					
				}
				case 3:
				{
					inline OnPlayerEditDialog(ex_pid, ex_dialogid, ex_response, ex_listitem, string:ex_inputtext[])
					{
						#pragma unused ex_pid, ex_dialogid, ex_listitem
						if(ex_response)
						{
							new value;
							if(sscanf(ex_inputtext, "d", value)) SendClientMessage(playerid, -1, "Wrong format!");
							else
							{
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE variables SET value = '%d' WHERE name = 'vehicle_default_price';", value);
								mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
								vehicle_default_price = value;
								
								new info_message[128];
								format(info_message, sizeof info_message, "vehicle_default_price: %d", vehicle_default_price);
								SendClientMessage(playerid, -1, info_message);
							}
						}
					}

					new edit_dialog_message[64];
					format(edit_dialog_message, sizeof edit_dialog_message, "current value: %f", vehicle_default_price);
					Dialog_ShowCallback(playerid, using inline OnPlayerEditDialog, DIALOG_STYLE_INPUT, "vehicle_default_price", edit_dialog_message, "Edit", "X");					
				}
				case 4:
				{
					inline OnPlayerEditDialog(ex_pid, ex_dialogid, ex_response, ex_listitem, string:ex_inputtext[])
					{
						#pragma unused ex_pid, ex_dialogid, ex_listitem
						if(ex_response)
						{
							new value;
							if(sscanf(ex_inputtext, "d", value)) SendClientMessage(playerid, -1, "Wrong format!");
							else
							{
								mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "UPDATE variables SET value = '%d' WHERE name = 'oldvehicle_min_price';", value);
								mysql_tquery(vcrp_db, QUERY_BUFFER, "", "");
								oldvehicle_min_price = value;
								
								new info_message[128];
								format(info_message, sizeof info_message, "oldvehicle_min_price: %d", oldvehicle_min_price);
								SendClientMessage(playerid, -1, info_message);
							}
						}
					}

					new edit_dialog_message[64];
					format(edit_dialog_message, sizeof edit_dialog_message, "current value: %f", oldvehicle_min_price);
					Dialog_ShowCallback(playerid, using inline OnPlayerEditDialog, DIALOG_STYLE_INPUT, "oldvehicle_min_price", edit_dialog_message, "Edit", "X");					
				}
			}
		}
	}

	new dialog_message[256];
	format(dialog_message, sizeof dialog_message, 
		"\
			vehicle_depreciation: %f\n\
			vehicle_depreciation_kms: %f\n\
			vehicle_depreciation_value: %f\n\
			vehicle_default_price: %d\n\
			oldvehicle_min_price: %d\n\
		", vehicle_depreciation, vehicle_depreciation_kms, vehicle_depreciation_value, vehicle_default_price, oldvehicle_min_price
	);
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_LIST, "server variables", dialog_message, "Edit", "X");
	return 1;
}