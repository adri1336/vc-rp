#include <YSI\y_hooks>

YCMD:ac(playerid, params[], help)
{
	new line_str[128], dialog_message[128 * _:CHEATS];
	for(new i = 1; i < _:CHEATS; i ++)
	{
		format(line_str, sizeof line_str, "[%d] %s\t%d:%d:%d\t%d\n", AcInfo[i][ac_ENABLED], GetCheatName(i), AcInfo[i][ac_DETECTIONS], AcInfo[i][ac_IN_SECONDS], AcInfo[i][ac_MIN_SECONDS], AcInfo[i][ac_KICK]);
		strcat(dialog_message, line_str);
	}
	inline OnPlayerDialog(pid, did, res, lis, string:inp[])
	{
		#pragma unused pid, did, inp
		if(res)
		{
			new cheatid = lis + 1,
				in_dialog_message[128];
			format(in_dialog_message, sizeof in_dialog_message, "Enabled\t%d\nDetections\t%d\nIn_Seconds\t%d\nMin_Seconds\t%d\nKick\t%d", AcInfo[cheatid][ac_ENABLED], AcInfo[cheatid][ac_DETECTIONS], AcInfo[cheatid][ac_IN_SECONDS], AcInfo[cheatid][ac_MIN_SECONDS], AcInfo[cheatid][ac_KICK]);
			inline in_OnPlayerDialog(in_pid, in_did, in_res, in_lis, string:in_inp[])
			{
				#pragma unused in_pid, in_did, in_inp
				if(in_res)
				{
					switch(in_lis)
					{
						case 0:
						{
							AcInfo[cheatid][ac_ENABLED] = !AcInfo[cheatid][ac_ENABLED];
							ac_UpdateCheatDB(cheatid);
						}
						case 1:
						{
							inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
							{
								#pragma unused in2_pid, in2_did, in2_lis
								if(in2_res)
								{
									new value;
									if(!sscanf(in2_inp, "d", value))
									{
										AcInfo[cheatid][ac_DETECTIONS] = value;
										ac_UpdateCheatDB(cheatid);
									}
									else SendClientMessage(playerid, -1, "Error!");
								}
							}
							Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "Detections", "integer", ">", "X");				
						}
						case 2:
						{
							inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
							{
								#pragma unused in2_pid, in2_did, in2_lis
								if(in2_res)
								{
									new value;
									if(!sscanf(in2_inp, "d", value))
									{
										AcInfo[cheatid][ac_IN_SECONDS] = value;
										ac_UpdateCheatDB(cheatid);
									}
									else SendClientMessage(playerid, -1, "Error!");
								}
							}
							Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "In_Seconds", "integer", ">", "X");				
						}
						case 3:
						{
							inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
							{
								#pragma unused in2_pid, in2_did, in2_lis
								if(in2_res)
								{
									new value;
									if(!sscanf(in2_inp, "d", value))
									{
										AcInfo[cheatid][ac_MIN_SECONDS] = value;
										ac_UpdateCheatDB(cheatid);
									}
									else SendClientMessage(playerid, -1, "Error!");
								}
							}
							Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "Min_Seconds", "integer", ">", "X");				
						}
						case 4:
						{
							AcInfo[cheatid][ac_KICK] = !AcInfo[cheatid][ac_KICK];
							ac_UpdateCheatDB(cheatid);
						}
					}
				}
			}
			Dialog_ShowCallback(playerid, using inline in_OnPlayerDialog, DIALOG_STYLE_TABLIST, GetCheatName(cheatid), in_dialog_message, ">", "X");
		}
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, "Anticheats", dialog_message, ">", "X");
	return 1;
}

YCMD:acvars(playerid, params[], help)
{
	new dialog_message[256];
	format(dialog_message, sizeof dialog_message, 
		"\
			ac_Teleport_Distance\t%f\n\
			ac_Position_Distance_Foot\t%f\n\
			ac_Position_Distance_Vehicle\t%f\n\
			ac_Position_Distance_Vehicle_mS\t%f\n\
			ac_PlayerSpeed_MaxValue\t%d\n\
			ac_VehicleSpeed_MaxValue\t%d\n\
			ac_VehicleSpeed_Offset_MaxValue\t%d\n\
			ac_Default_Protection_Seconds\t%d\n\
			ac_Default_Flooder_MaxInterval\t%d\
		",
			ac_Teleport_Distance, ac_Position_Distance_Foot, ac_Position_Distance_Vehicle, ac_Position_Distance_Vehicle_mS,
			ac_PlayerSpeed_MaxValue, ac_VehicleSpeed_MaxValue, ac_VehicleSpeed_Offset_MaxValue, ac_Default_Protection_Seconds,
			ac_Default_Flooder_MaxInterval
		);
	inline OnPlayerDialog(pid, did, res, lis, string:inp[])
	{
		#pragma unused pid, did, inp
		if(res)
		{
			switch(lis)
			{
				case 0:
				{
					inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
					{
						#pragma unused in2_pid, in2_did, in2_lis
						if(in2_res)
						{
							new Float:value;
							if(!sscanf(in2_inp, "f", value))
							{
								ac_Teleport_Distance = value;
								ac_UpdateVariablesDB();
							}
							else SendClientMessage(playerid, -1, "Error!");
						}
					}
					Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "ac_Teleport_Distance", "float", ">", "X");
				}
				case 1:
				{
					inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
					{
						#pragma unused in2_pid, in2_did, in2_lis
						if(in2_res)
						{
							new Float:value;
							if(!sscanf(in2_inp, "f", value))
							{
								ac_Position_Distance_Foot = value;
								ac_UpdateVariablesDB();
							}
							else SendClientMessage(playerid, -1, "Error!");
						}
					}
					Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "ac_Position_Distance_Foot", "float", ">", "X");
				}
				case 2:
				{
					inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
					{
						#pragma unused in2_pid, in2_did, in2_lis
						if(in2_res)
						{
							new Float:value;
							if(!sscanf(in2_inp, "f", value))
							{
								ac_Position_Distance_Vehicle = value;
								ac_UpdateVariablesDB();
							}
							else SendClientMessage(playerid, -1, "Error!");
						}
					}
					Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "ac_Position_Distance_Vehicle", "float", ">", "X");
				}
				case 3:
				{
					inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
					{
						#pragma unused in2_pid, in2_did, in2_lis
						if(in2_res)
						{
							new Float:value;
							if(!sscanf(in2_inp, "f", value))
							{
								ac_Position_Distance_Vehicle_mS = value;
								ac_UpdateVariablesDB();
							}
							else SendClientMessage(playerid, -1, "Error!");
						}
					}
					Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "ac_Position_Distance_Vehicle_mS", "float", ">", "X");
				}
				case 4:
				{
					inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
					{
						#pragma unused in2_pid, in2_did, in2_lis
						if(in2_res)
						{
							new value;
							if(!sscanf(in2_inp, "d", value))
							{
								ac_PlayerSpeed_MaxValue = value;
								ac_UpdateVariablesDB();
							}
							else SendClientMessage(playerid, -1, "Error!");
						}
					}
					Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "ac_PlayerSpeed_MaxValue", "float", ">", "X");
				}
				case 5:
				{
					inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
					{
						#pragma unused in2_pid, in2_did, in2_lis
						if(in2_res)
						{
							new value;
							if(!sscanf(in2_inp, "d", value))
							{
								ac_VehicleSpeed_MaxValue = value;
								ac_UpdateVariablesDB();
							}
							else SendClientMessage(playerid, -1, "Error!");
						}
					}
					Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "ac_VehicleSpeed_MaxValue", "float", ">", "X");
				}
				case 6:
				{
					inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
					{
						#pragma unused in2_pid, in2_did, in2_lis
						if(in2_res)
						{
							new value;
							if(!sscanf(in2_inp, "d", value))
							{
								ac_VehicleSpeed_Offset_MaxValue = value;
								ac_UpdateVariablesDB();
							}
							else SendClientMessage(playerid, -1, "Error!");
						}
					}
					Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "ac_VehicleSpeed_Offset_MaxValue", "float", ">", "X");
				}
				case 7:
				{
					inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
					{
						#pragma unused in2_pid, in2_did, in2_lis
						if(in2_res)
						{
							new value;
							if(!sscanf(in2_inp, "d", value))
							{
								ac_Default_Protection_Seconds = value;
								ac_UpdateVariablesDB();
							}
							else SendClientMessage(playerid, -1, "Error!");
						}
					}
					Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "ac_Default_Protection_Seconds", "float", ">", "X");
				}
				case 8:
				{
					inline in2_OnPlayerDialog(in2_pid, in2_did, in2_res, in2_lis, string:in2_inp[])
					{
						#pragma unused in2_pid, in2_did, in2_lis
						if(in2_res)
						{
							new value;
							if(!sscanf(in2_inp, "d", value))
							{
								ac_Default_Flooder_MaxInterval = value;
								ac_UpdateVariablesDB();
							}
							else SendClientMessage(playerid, -1, "Error!");
						}
					}
					Dialog_ShowCallback(playerid, using inline in2_OnPlayerDialog, DIALOG_STYLE_INPUT, "ac_Default_Flooder_MaxInterval", "float", ">", "X");
				}
			}
		}
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST, "Anticheats variables", dialog_message, ">", "X");
	return 1;
}