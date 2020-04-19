#include <YSI\y_hooks>

loadtext lang[gunsmith];

enum E_Valid_GunsmithKeys
{
	vgs_Key,
	vgs_KeyEmbedding[32]
};
new Valid_GunsmithKeys[][E_Valid_GunsmithKeys] =
{
	{KEY_CROUCH, "~k~~PED_DUCK~"},
	{KEY_FIRE, "~k~~PED_FIREWEAPON~"},
	{KEY_SPRINT, "~k~~PED_SPRINT~"},
	{KEY_SECONDARY_ATTACK, "~k~~VEHICLE_ENTER_EXIT~"},
	{KEY_JUMP, "~k~~PED_JUMPING~"},
	{KEY_WALK, "~k~~SNEAK_ABOUT~"},
	//{KEY_YES, "~k~~CONVERSATION_YES~"},
	//{KEY_NO, "~k~~CONVERSATION_NO~"},
	{KEY_CTRL_BACK, "~k~~GROUP_CONTROL_BWD~"}
};

new pGunsmithKey[MAX_PLAYERS];

forward OnPlayerRequestGsPoint(playerid, point_index);

enum E_GunSmith_Points
{
	Float:gspoint_POS[4],
	Float:gspoint_PLACE_POS[4],
	bool:gspoint_IN_USE,
	gspoint_AREAID
};
new GunSmith_Points[][E_GunSmith_Points] =
{
	{{2560.965820, -1295.886108, 1044.125000, 0.0}, {2559.082763, -1300.094848, 1044.125000, 180.0}, false, INVALID_STREAMER_ID},
	{{2556.874511, -1295.886230, 1044.125000, 0.0}, {2559.082763, -1300.094848, 1044.125000, 180.0}, false, INVALID_STREAMER_ID},
	{{2552.995849, -1295.886718, 1044.125000, 0.0}, {2551.079833, -1300.093994, 1044.125000, 180.0}, false, INVALID_STREAMER_ID},
	{{2548.964843, -1295.888549, 1044.125000, 0.0}, {2543.073730,-1300.094238, 1044.125000, 180.0}, false, INVALID_STREAMER_ID},
	{{2545.077148, -1295.887695, 1044.125000, 0.0}, {2551.079833, -1300.093994, 1044.125000, 180.0}, false, INVALID_STREAMER_ID},
	{{2540.889160, -1295.900512, 1044.125000, 0.0}, {2551.079833, -1300.093994, 1044.125000, 180.0}, false, INVALID_STREAMER_ID},
	{{2540.985107, -1290.976562, 1044.125000, 180.0}, {2543.143310, -1287.218750, 1044.125000, 0.0}, false, INVALID_STREAMER_ID},
	{{2545.183105, -1290.977172, 1044.125000, 180.0}, {2543.143310, -1287.218750, 1044.125000, 0.0}, false, INVALID_STREAMER_ID},
	{{2549.090576, -1290.977172, 1044.125000, 180.0}, {2551.120849, -1287.220214, 1044.125000, 0.0}, false, INVALID_STREAMER_ID},
	{{2553.152832, -1290.978515, 1044.125000, 180.0}, {2551.120849, -1287.220214, 1044.125000, 0.0}, false, INVALID_STREAMER_ID},
	{{2557.089599, -1290.978027, 1044.125000, 180.0}, {2559.123535, -1287.218383, 1044.125000, 0.0}, false, INVALID_STREAMER_ID},
	{{2560.991455, -1290.978149, 1044.125000, 180.0}, {2559.123535, -1287.218383, 1044.125000, 0.0}, false, INVALID_STREAMER_ID}
};
new Float:GunSmith_PiecesPoints[][] =
{
	{2564.255615, -1293.014770, 1044.125000}
};

new pCurrent_GsPoint[MAX_PLAYERS] = {-1, ...},
	bool:pGunsmithPieces[MAX_PLAYERS],
	pGunsmithCount[MAX_PLAYERS],
	pGunsmithCP[MAX_PLAYERS],

	pGunsmith_ProgressBar[MAX_PLAYERS] = {INVALID_PROGRESS_BAR_ID, ...},
	PlayerText:pGunsmith_Percentage_TD[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

hook OnScriptInit()
{
	new streamer_info[2];
	for(new i = 0; i < sizeof GunSmith_Points; i ++)
	{
		GunSmith_Points[i][gspoint_AREAID] = CreateDynamicCylinder(GunSmith_Points[i][gspoint_POS][0], GunSmith_Points[i][gspoint_POS][1], GunSmith_Points[i][gspoint_POS][2] - 1.0, GunSmith_Points[i][gspoint_POS][2] + 3.0, 1.0);
		streamer_info[0] = _:AREA_TYPE_GUNSMITH;
		streamer_info[1] = i;
		Streamer_SetArrayData(STREAMER_TYPE_AREA, GunSmith_Points[i][gspoint_AREAID], E_STREAMER_EXTRA_ID, streamer_info);
	}
	return 1;
}

hook OnPlayerRequestJob(playerid, job_index, job_point_index)
{
	if(Jobs[job_index][job_ID] == JOB_GUNSMITH)
	{
		if(pGunsmithCP[playerid] != INVALID_STREAMER_ID)
		{
			DestroyDynamicCP(pGunsmithCP[playerid]);
			pGunsmithCP[playerid] = INVALID_STREAMER_ID;
		}
		new index_gs = random(sizeof GunSmith_PiecesPoints);
		pGunsmithCP[playerid] = CreateDynamicCP(GunSmith_PiecesPoints[index_gs][0], GunSmith_PiecesPoints[index_gs][1], GunSmith_PiecesPoints[index_gs][2], 1.0, .playerid = playerid);
		Streamer_SetIntData(STREAMER_TYPE_CP, pGunsmithCP[playerid], E_STREAMER_EXTRA_ID, _:CHECKPOINT_TYPE_GUNSMITH_TAKE);
		pGunsmithCount[playerid] = 0;
	}
	return 1;
}

hook OnPlayerRequestFinJob(playerid, job_index, job_point_index)
{
	if(pCurrent_GsPoint[playerid] != -1)
	{
		GunSmith_Points[pCurrent_GsPoint[playerid]][gspoint_IN_USE] = false;
		pCurrent_GsPoint[playerid] = -1;
	}
	if(pGunsmithCP[playerid] != INVALID_STREAMER_ID)
	{
		DestroyDynamicCP(pGunsmithCP[playerid]);
		pGunsmithCP[playerid] = INVALID_STREAMER_ID;
	}
	if(pGunsmith_ProgressBar[playerid] != INVALID_PROGRESS_BAR_ID)
	{
		DestroyPlayerProgressBar(playerid, pGunsmith_ProgressBar[playerid]);
		pGunsmith_ProgressBar[playerid] = INVALID_PROGRESS_BAR_ID;
	}
	if(pGunsmith_Percentage_TD[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, pGunsmith_Percentage_TD[playerid]);
		pGunsmith_Percentage_TD[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
	pGunsmithPieces[playerid] = false;
	RemovePlayerAnimEnv(playerid);
	return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(pGunsmithCP[playerid] != INVALID_STREAMER_ID && checkpointid == pGunsmithCP[playerid])
	{	
		new type = Streamer_GetIntData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_EXTRA_ID);
		if(type == _:CHECKPOINT_TYPE_GUNSMITH_TAKE)
		{
			if(pGunsmithPieces[playerid]) Text_Send(playerid, $MESSAGE_ERROR_PIECES);
			else
			{
				pGunsmithPieces[playerid] = true;
				Text_Send(playerid, $MESSAGE_INFO_PIECES);
				SetPlayerAnimEnv(playerid, "", "", false, 3052, 6, 0.008999, 0.054999, -0.196000, -109.000030, -12.799996, -98.800056, 0.666999, 0.696000, 0.674999, SPECIAL_ACTION_CARRY);
				DestroyDynamicCP(pGunsmithCP[playerid]);
				pGunsmithCP[playerid] = INVALID_STREAMER_ID;
			}
		}
		else if(type == _:CHECKPOINT_TYPE_GUNSMITH_PLACE)
		{
			pGunsmithCount[playerid] ++;
			if(pGunsmithCount[playerid] >= 5)
			{
				CallRemoteFunction("OnPlayerCompleteJob", "iddf", playerid, pCurrentJobIndex[playerid][0], pCurrentJobIndex[playerid][1], 1.0);
				pGunsmithCount[playerid] = 0;
			}
			RemovePlayerAnimEnv(playerid);
			//
			DestroyDynamicCP(pGunsmithCP[playerid]);
			pGunsmithCP[playerid] = INVALID_STREAMER_ID;
			new index_gs = random(sizeof GunSmith_PiecesPoints);
			pGunsmithCP[playerid] = CreateDynamicCP(GunSmith_PiecesPoints[index_gs][0], GunSmith_PiecesPoints[index_gs][1], GunSmith_PiecesPoints[index_gs][2], 1.0, .playerid = playerid);
			Streamer_SetIntData(STREAMER_TYPE_CP, pGunsmithCP[playerid], E_STREAMER_EXTRA_ID, _:CHECKPOINT_TYPE_GUNSMITH_TAKE);
		}
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return 1;
}

public OnPlayerRequestGsPoint(playerid, point_index)
{
	if(pCurrent_GsPoint[playerid] == -1)
	{
		if(GetPlayerJobId(playerid) != JOB_GUNSMITH) Text_Send(playerid, $MESSAGE_ERROR_NO_JOB);
		else
		{
			if(GunSmith_Points[point_index][gspoint_IN_USE]) Text_Send(playerid, $MESSAGE_ERROR_GSPOINT_IN_USE);
			else
			{
				if(!pGunsmithPieces[playerid]) Text_Send(playerid, $MESSAGE_ERROR_NO_PIECES);
				else
				{
					pCurrent_GsPoint[playerid] = point_index;
					GunSmith_Points[pCurrent_GsPoint[playerid]][gspoint_IN_USE] = true;

					if(pGunsmith_ProgressBar[playerid] == INVALID_PROGRESS_BAR_ID) pGunsmith_ProgressBar[playerid] = CreatePlayerProgressBar(playerid, 280.0, 420.0, 80.0, 4.0, -1966081, -545062913);
					if(pGunsmith_Percentage_TD[playerid] == PlayerText:INVALID_TEXT_DRAW)
					{
						pGunsmith_Percentage_TD[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 408.000000, "0%");
						PlayerTextDrawLetterSize(playerid, pGunsmith_Percentage_TD[playerid], 0.207666, 0.977778);
						PlayerTextDrawAlignment(playerid, pGunsmith_Percentage_TD[playerid], 2);
						PlayerTextDrawColor(playerid, pGunsmith_Percentage_TD[playerid], -1);
						PlayerTextDrawSetShadow(playerid, pGunsmith_Percentage_TD[playerid], 0);
						PlayerTextDrawBackgroundColor(playerid, pGunsmith_Percentage_TD[playerid], 255);
						PlayerTextDrawFont(playerid, pGunsmith_Percentage_TD[playerid], 1);
						PlayerTextDrawSetProportional(playerid, pGunsmith_Percentage_TD[playerid], 1);
					}
					SetPlayerProgressBarValue(playerid, pGunsmith_ProgressBar[playerid], 0.0);
					PlayerTextDrawShow(playerid, pGunsmith_Percentage_TD[playerid]);
					ShowPlayerProgressBar(playerid, pGunsmith_ProgressBar[playerid]);
					HidePlayerInfoMessage(playerid);
					SetPlayerPos(playerid, GunSmith_Points[pCurrent_GsPoint[playerid]][gspoint_POS][0], GunSmith_Points[pCurrent_GsPoint[playerid]][gspoint_POS][1], GunSmith_Points[pCurrent_GsPoint[playerid]][gspoint_POS][2]);
					SetPlayerFacingAngle(playerid, GunSmith_Points[pCurrent_GsPoint[playerid]][gspoint_POS][3]);
					SetPlayerAnimEnv(playerid, "BASEBALL", "Bat_1", true, 18635, 6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, .animlockx = 1, .animlocky = 1);

					pGunsmithKey[playerid] = random(sizeof Valid_GunsmithKeys);
					ShowPlayerAuxTextDraw(playerid, GetLangAssemblerMessage(playerid, Valid_GunsmithKeys[pGunsmithKey[playerid]][vgs_KeyEmbedding]));
				}
			}
		}
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(pCurrent_GsPoint[playerid] != -1)
	{
		if(newkeys & Valid_GunsmithKeys[pGunsmithKey[playerid]][vgs_Key])
		{
			new Float:current_percentage = GetPlayerProgressBarValue(playerid, pGunsmith_ProgressBar[playerid]);
			if(current_percentage >= 100.0)
			{
				new old_index = pCurrent_GsPoint[playerid];
				if(pCurrent_GsPoint[playerid] != -1)
				{
					GunSmith_Points[pCurrent_GsPoint[playerid]][gspoint_IN_USE] = false;
					pCurrent_GsPoint[playerid] = -1;
				}
				if(pGunsmithCP[playerid] != INVALID_STREAMER_ID)
				{
					DestroyDynamicCP(pGunsmithCP[playerid]);
					pGunsmithCP[playerid] = INVALID_STREAMER_ID;
				}
				if(pGunsmith_ProgressBar[playerid] != INVALID_PROGRESS_BAR_ID)
				{
					DestroyPlayerProgressBar(playerid, pGunsmith_ProgressBar[playerid]);
					pGunsmith_ProgressBar[playerid] = INVALID_PROGRESS_BAR_ID;
				}
				if(pGunsmith_Percentage_TD[playerid] != PlayerText:INVALID_TEXT_DRAW)
				{
					PlayerTextDrawDestroy(playerid, pGunsmith_Percentage_TD[playerid]);
					pGunsmith_Percentage_TD[playerid] = PlayerText:INVALID_TEXT_DRAW;
				}
				pGunsmithPieces[playerid] = false;
				//ok
				HidePlayerAuxTextDraw(playerid);
				pGunsmithCP[playerid] = CreateDynamicCP(GunSmith_Points[old_index][gspoint_PLACE_POS][0], GunSmith_Points[old_index][gspoint_PLACE_POS][1], GunSmith_Points[old_index][gspoint_PLACE_POS][2], 1.0, .playerid = playerid);
				Streamer_SetIntData(STREAMER_TYPE_CP, pGunsmithCP[playerid], E_STREAMER_EXTRA_ID, _:CHECKPOINT_TYPE_GUNSMITH_PLACE);
				SetPlayerAnimEnv(playerid, "", "", false, 3052, 6, 0.008999, 0.054999, -0.196000, -109.000030, -12.799996, -98.800056, 0.666999, 0.696000, 0.674999, SPECIAL_ACTION_CARRY);
				Text_Send(playerid, $MESSAGE_INFO_PIECE_PLACE);
			}
			else
			{
				SetPlayerProgressBarValue(playerid, pGunsmith_ProgressBar[playerid], current_percentage + float(random(7)));
				ShowPlayerProgressBar(playerid, pGunsmith_ProgressBar[playerid]);
				new str[24];
				format(str, sizeof str, "%.0f%%", GetPlayerProgressBarValue(playerid, pGunsmith_ProgressBar[playerid]));
				PlayerTextDrawSetString(playerid, pGunsmith_Percentage_TD[playerid], str);
			}
		}
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return 1;
}

GetLangAssemblerMessage(playerid, key[])
{
	new td_str[64];
	Text_Format_TD(td_str, sizeof td_str, PI[playerid][pi_LANG_ID], $TEXTDRAW_KEY, key);
	format(td_str, sizeof td_str, "%s", td_str);
	return td_str;
}