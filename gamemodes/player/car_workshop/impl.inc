#include <YSI\y_hooks>

loadtext lang[car_workshop];

public OnPlayerRequestCarWorkShop(playerid)
{
	if(GetPlayerVehicleIndex(playerid) == INVALID_VEHICLE_INDEX || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) Text_Send(playerid, $MESSAGE_ERROR_NO_VEHICLE);
	else
	{
		new index = GetPlayerVehicleIndex(playerid);
		if(!HasPlayerAccessToVehicle(playerid, index)) Text_Send(playerid, $MESSAGE_ERROR_VEH_ACCESS);
		else if(VehicleInfo[index][vinfo_PARAMS_ENGINE]) Text_Send(playerid, $MESSAGE_ERROR_ENGINE);
		else
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
							if(CAR_WORKSHOP_REPAIR_PRICE > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
							else
							{
								VehicleInfo[index][vinfo_HEALTH] = 1000.0;
								RepairVehicle(VehicleInfo[index][vinfo_VEHICLE_ID]);
								GivePlayerMoneyEx(playerid, -CAR_WORKSHOP_REPAIR_PRICE);
								Text_Send(playerid, $GAMETEXT_INFO_WORK_DONE);
							}
						}
						case 1:
						{
							inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
							{
								#pragma unused in_pid, in_dialogid, in_inputtext
								if(in_response)
								{
									switch(in_listitem)
									{
										case 0:
										{
											if(CAR_WORKSHOP_PAINT1_PRICE > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
											else
											{
												new line_str[15], dialog[15 * (sizeof(VEHICLE_COLORS) + 1) ];
												for(new i = 0; i < sizeof VEHICLE_COLORS; i ++)
												{
													format(line_str, sizeof(line_str), "{%06x}%d\n", VEHICLE_COLORS[i] >>> 8, i);
													strcat(dialog, line_str);
												}
												inline in2_OnPlayerDialog(in2_pid, in2_dialogid, in2_response, in2_listitem, string:in2_inputtext[])
												{
													#pragma unused in2_pid, in2_dialogid, in2_inputtext
													if(in2_response)
													{
														VehicleInfo[index][vinfo_COLOR1] = in2_listitem;
														ChangeVehicleColor(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_COLOR1], VehicleInfo[index][vinfo_COLOR2]);
														GivePlayerMoneyEx(playerid, -CAR_WORKSHOP_PAINT1_PRICE);
														Text_Send(playerid, $GAMETEXT_INFO_WORK_DONE);
													}
												}

												new dialog_caption[64];
												Text_Format_Dialog(dialog_caption, sizeof dialog_caption, PI[playerid][pi_LANG_ID], $DIALOG_PAINT_COLORS_CAPTION);
												Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_LIST, dialog_caption, dialog, ">>", "X");
											}
										}
										case 1:
										{
											if(CAR_WORKSHOP_PAINT2_PRICE > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
											else
											{
												new line_str[15], dialog[15 * (sizeof(VEHICLE_COLORS) + 1) ];
												for(new i = 0; i < sizeof VEHICLE_COLORS; i ++)
												{
													format(line_str, sizeof(line_str), "{%06x}%d\n", VEHICLE_COLORS[i] >>> 8, i);
													strcat(dialog, line_str);
												}
												inline in2_OnPlayerDialog(in2_pid, in2_dialogid, in2_response, in2_listitem, string:in2_inputtext[])
												{
													#pragma unused in2_pid, in2_dialogid, in2_inputtext
													if(in2_response)
													{
														VehicleInfo[index][vinfo_COLOR2] = in2_listitem;
														ChangeVehicleColor(VehicleInfo[index][vinfo_VEHICLE_ID], VehicleInfo[index][vinfo_COLOR1], VehicleInfo[index][vinfo_COLOR2]);
														GivePlayerMoneyEx(playerid, -CAR_WORKSHOP_PAINT2_PRICE);
														Text_Send(playerid, $GAMETEXT_INFO_WORK_DONE);
													}
												}

												new dialog_caption[64];
												Text_Format_Dialog(dialog_caption, sizeof dialog_caption, PI[playerid][pi_LANG_ID], $DIALOG_PAINT_COLORS_CAPTION);
												Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_LIST, dialog_caption, dialog, ">>", "X");
											}
										}
									}
								}
							}
							Text_DialogBox(playerid, DIALOG_STYLE_TABLIST, using inline in_OnPlayerDialog, $DIALOG_CAR_PAINT_CAPTION, $DIALOG_CAR_PAINT_BODY, $DIALOG_CAR_PAINT_YES, $DIALOG_CAR_PAINT_NO, CAR_WORKSHOP_PAINT1_PRICE, CAR_WORKSHOP_PAINT2_PRICE);
						}
						case 2:
						{
							if(!IsVehModelTuneable(VehicleInfo[index][vinfo_MODELID])) Text_Send(playerid, $MESSAGE_ERROR_TUNING);
							else
							{
								new types[MAX_COMPONENTS_TYPES], total;
								GetVehModelComponentTypes(VehicleInfo[index][vinfo_MODELID], types, total);
								if(total <= 0) Text_Send(playerid, $MESSAGE_ERROR_TUNING);
								else
								{
									new dialog[512];
									for(new i = 0; i < total; i ++)
									format(dialog, sizeof dialog, "%s%s\n", dialog, GetComponentPartName(playerid, types[i]));

									inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
									{
										#pragma unused in_pid, in_dialogid, in_inputtext
										if(in_response)
										{
											new components[MAX_VEHICLE_COMPONENTS], total_components;
											GetVehModelComponentsInType(VehicleInfo[index][vinfo_MODELID], types[in_listitem], components, total_components);
											if(total_components <= 0) Text_Send(playerid, $MESSAGE_ERROR_TUNING);
											else
											{
												dialog = "";
												for(new i = 0; i < total_components; i ++)
												format(dialog, sizeof dialog, "%s%s\t%d$\n", dialog, ComponentInfo[ components[i] - 1000 ][component_NAME], ComponentInfo[ components[i] - 1000 ][component_PRICE]);

												inline in2_OnPlayerDialog(in2_pid, in2_dialogid, in2_response, in2_listitem, string:in2_inputtext[])
												{
													#pragma unused in2_pid, in2_dialogid, in2_inputtext
													if(in2_response)
													{
														if(ComponentInfo[ components[in2_listitem] - 1000 ][component_PRICE] > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
														else
														{
															AddVehicleMod(VehicleInfo[index][vinfo_VEHICLE_ID], components[in2_listitem]);
															UpdateVehicleModifications(index);
															GivePlayerMoneyEx(playerid, -ComponentInfo[ components[in2_listitem] - 1000 ][component_PRICE]);
															Text_Send(playerid, $GAMETEXT_INFO_WORK_DONE);
														}
													}
												}
												Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_TABLIST, GetComponentPartName(playerid, types[in_listitem]), dialog, ">>", "X");
											}
										}
									}
									Dialog_ShowCallback(playerid, using inline in_OnPlayerDialog, DIALOG_STYLE_LIST, "Tuning", dialog, ">>", "X");
								}
							}
						}
						case 3: //eliminar componente
						{
							new components[MAX_VEHICLE_COMPONENTS], total_components;
							GetVehComponents(VehicleInfo[index][vinfo_VEHICLE_ID], components, total_components);
							if(total_components == 0) Text_Send(playerid, $MESSAGE_ERROR_NO_COMPONENTS);
							else
							{
								new dialog[512];
								for(new i = 0; i < total_components; i ++)
								{
									new component_type = GetVehComponentType(components[i]);
									format(dialog, sizeof dialog, "%s%s %s\n", dialog, GetComponentPartName(playerid, component_type, false), ComponentInfo[ components[i] - 1000 ][component_NAME]);
								}

								inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
								{
									#pragma unused in_pid, in_dialogid, in_inputtext
									if(in_response)
									{
										if(CAR_WORKSHOP_REMOVE_MOD_PRICE > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
										else
										{
											RemoveVehicleMod(VehicleInfo[index][vinfo_VEHICLE_ID], components[in_listitem]);
											UpdateVehicleModifications(index);
											GivePlayerMoneyEx(playerid, -CAR_WORKSHOP_REMOVE_MOD_PRICE);
											Text_Send(playerid, $GAMETEXT_INFO_WORK_DONE);
										}
									}
								}

								new dialog_caption[64];
								Text_Format_Dialog(dialog_caption, sizeof dialog_caption, PI[playerid][pi_LANG_ID], $DIALOG_REMOVE_COMPONENT_CAPTION);
								Dialog_ShowCallback(playerid, using inline in_OnPlayerDialog, DIALOG_STYLE_LIST, dialog_caption, dialog, ">>", "X");
							}
						}
						case 4: //paintjob
						{
							new paintjobs[MAX_VEHICLE_PAINTJOBS], total;
							GetVehModelPaintjobs(VehicleInfo[index][vinfo_MODELID], paintjobs, total);
							if(total == 0) Text_Send(playerid, $MESSAGE_ERROR_PAINTJOB);
							else
							{
								new dialog[512], delete_paintjob_str[64];
								Text_Format_Dialog(delete_paintjob_str, sizeof delete_paintjob_str, PI[playerid][pi_LANG_ID], $DIALOG_DELETE_PAINTJOB);
								format(dialog, sizeof dialog, "{FF0000}%s\n", delete_paintjob_str);
								
								for(new i = 0; i < total; i ++)
								format(dialog, sizeof dialog, "%sPaintjob #%d\n", dialog, i);

								inline in_OnPlayerDialog(in_pid, in_dialogid, in_response, in_listitem, string:in_inputtext[])
								{
									#pragma unused in_pid, in_dialogid, in_inputtext
									if(in_response)
									{
										if(CAR_WORKSHOP_PAINTJOB_PRICE > PI[playerid][pi_MONEY]) Text_Send(playerid, $MESSAGE_ERROR_NO_MONEY);
										else
										{
											new paintjobid;
											if(in_listitem == 0) paintjobid = INVALID_PAINTJOB_ID;
											else paintjobid = in_listitem - 1;

											ChangeVehiclePaintjob(VehicleInfo[index][vinfo_VEHICLE_ID], paintjobid);
											VehicleInfo[index][vinfo_PAINTJOB] = paintjobid;
											GivePlayerMoneyEx(playerid, -CAR_WORKSHOP_PAINTJOB_PRICE);
											Text_Send(playerid, $GAMETEXT_INFO_WORK_DONE);
										}
									}
								}

								new dialog_caption[64];
								Text_Format_Dialog(dialog_caption, sizeof dialog_caption, PI[playerid][pi_LANG_ID], $DIALOG_PAINTJOBS_CAPTION);
								Dialog_ShowCallback(playerid, using inline in_OnPlayerDialog, DIALOG_STYLE_LIST, dialog_caption, dialog, ">>", "X");
							}
						}
					}
				}
			}
			if(VehicleInfo[index][vinfo_ID_PLAYER] == PI[playerid][pi_ID]) Text_DialogBox(playerid, DIALOG_STYLE_TABLIST, using inline OnPlayerDialog, $DIALOG_CAR_WORKSHOP_CAPTION, $DIALOG_CAR_WORKSHOP_OWNER_BODY, $DIALOG_CAR_WORKSHOP_YES, $DIALOG_CAR_WORKSHOP_NO, CAR_WORKSHOP_REPAIR_PRICE, CAR_WORKSHOP_REMOVE_MOD_PRICE, CAR_WORKSHOP_PAINTJOB_PRICE);
			else Text_DialogBox(playerid, DIALOG_STYLE_TABLIST, using inline OnPlayerDialog, $DIALOG_CAR_WORKSHOP_CAPTION, $DIALOG_CAR_WORKSHOP_BODY, $DIALOG_CAR_WORKSHOP_YES, $DIALOG_CAR_WORKSHOP_NO, CAR_WORKSHOP_REPAIR_PRICE, CAR_WORKSHOP_REMOVE_MOD_PRICE, CAR_WORKSHOP_PAINTJOB_PRICE);
		}
	}
	return 1;
}