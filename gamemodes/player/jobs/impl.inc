#include <YSI\y_hooks>

loadtext lang[jobs];

hook OnPlayerConnect(playerid)
{
	pCurrentJobIndex[playerid][0] = -1;
	pCurrentJobIndex[playerid][1] = -1;

	for(new i = 0; i < MAX_JOBS; i ++)
	{
		pJobs_Info[playerid][i][pjob_LEVEL] = 1;
		pJobs_Info[playerid][i][pjob_EXP] = 1;
		pJobs_Info[playerid][i][pjob_JOBS] = 0;
	}
	return 1;
}

hook OnPlayerLogin(playerid)
{
	inline OnQueryLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i < rows; i ++)
			{
				new id_job;
				cache_get_value_name_int(i, "id_job", id_job);
				new index_job = GetJobIndexById(id_job);
				if(index_job != -1)
				{
					cache_get_value_name_int(i, "level", pJobs_Info[playerid][index_job][pjob_LEVEL]);
					cache_get_value_name_int(i, "exp", pJobs_Info[playerid][index_job][pjob_EXP]);
					cache_get_value_name_int(i, "jobs", pJobs_Info[playerid][index_job][pjob_JOBS]);
				}
			}
		}
	}
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM player_jobs_info WHERE id_player = %d;", PI[playerid][pi_ID]);
	mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnQueryLoad, "");
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(IsPlayerInAnyJob(playerid)) CallRemoteFunction("OnPlayerRequestFinJob", "idd", playerid, pCurrentJobIndex[playerid][0], pCurrentJobIndex[playerid][1]);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(IsPlayerInAnyJob(playerid)) CallRemoteFunction("OnPlayerRequestFinJob", "idd", playerid, pCurrentJobIndex[playerid][0], pCurrentJobIndex[playerid][1]);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_SPECTATING)
	{
		if(IsPlayerInAnyJob(playerid)) CallRemoteFunction("OnPlayerRequestFinJob", "idd", playerid, pCurrentJobIndex[playerid][0], pCurrentJobIndex[playerid][1]);
	}
	return 1;
}

public OnPlayerRequestJob(playerid, job_index, job_point_index)
{
	if(pCurrentJobIndex[playerid][0] == job_index && pCurrentJobIndex[playerid][1] == job_point_index) CallRemoteFunction("OnPlayerRequestFinJob", "idd", playerid, job_index, job_point_index);
	else if(IsPlayerInAnyJob(playerid)) Text_Send(playerid, $MESSAGE_ERROR_ALREADY_IN_JOB, GetJobName(playerid, Jobs[ pCurrentJobIndex[playerid][0] ][job_ID]));
	else
	{
		if(PI[playerid][pi_LEVEL] >= Jobs[job_index][job_MIN_LEVEL])
		{
			if(pJobs_Info[playerid][job_index][pjob_LEVEL] >= Jobs_Points[job_index][job_point_index][job_point_MIN_JOB_LEVEL])
			{
				switch(Jobs[job_index][job_ID])
				{
					case JOB_TAXI, JOB_TRUCKER:
					{
						if(!PlayerInvContainsItem(playerid, _:INV_ITEM_DRIVER_LICENSE))
						{
							Text_Send(playerid, $MESSAGE_ERROR_DRIVER_LICENSE);
							SetJobPointActorTempAnim(job_index, job_point_index, "GANGS", "Invite_No");
							return 0;
						}
					}
				}
				//si
				pCurrentJobIndex[playerid][0] = job_index;
				pCurrentJobIndex[playerid][1] = job_point_index;
				Text_Send(playerid, $MESSAGE_INFO_JOB_STARTED);
				Text_Send(playerid, $GAMETEXT_INFO_JOB_STARTED);
				SetJobPointActorTempAnim(job_index, job_point_index, "GANGS", "Invite_Yes");

				//vehs
				foreach(new i : VehicleInfo)
				{
					if(VehicleInfo[i][vinfo_TYPE] == VEHICLE_TYPE_JOB && VehicleInfo[i][vinfo_ID_JOB_POINT] == GetPlayerJobPointId(playerid))
					{
						Iter_Add(PlayerVehicles[playerid], i);
					}
				}
			}
			else
			{
				Text_Send(playerid, $MESSAGE_ERROR_JOB_LEVEL, Jobs_Points[job_index][job_point_index][job_point_MIN_JOB_LEVEL]);
				SetJobPointActorTempAnim(job_index, job_point_index, "GANGS", "Invite_No");
			}
		}
		else
		{
			Text_Send(playerid, $MESSAGE_ERROR_LEVEL, Jobs[job_index][job_MIN_LEVEL]);
			SetJobPointActorTempAnim(job_index, job_point_index, "GANGS", "Invite_No");
		}
	}
	return 1;
}

public OnPlayerRequestFinJob(playerid, job_index, job_point_index)
{
	if(GetPlayerGameState(playerid) == GAME_STATE_SPAWNED)
	Text_Send(playerid, $GAMETEXT_INFO_JOB_FINISHED);
	
	//vehs
	foreach(new i : VehicleInfo)
	{
		if(VehicleInfo[i][vinfo_TYPE] == VEHICLE_TYPE_JOB && VehicleInfo[i][vinfo_ID_JOB_POINT] == GetPlayerJobPointId(playerid))
		{
			Iter_Remove(PlayerVehicles[playerid], i);
		}
	}

	pCurrentJobIndex[playerid][0] = -1;
	pCurrentJobIndex[playerid][1] = -1;
	return 1;
}

public OnPlayerCompleteJob(playerid, job_index, job_point_index, Float:pay_percentage)
{
	//pjob info
	if(Jobs[job_index][job_EXP_PER_JOB] > 0 && Jobs[job_index][job_EXP_FOR_NEXT_LEVEL] > 0)
	{
		pJobs_Info[playerid][job_index][pjob_EXP] += Jobs[job_index][job_EXP_PER_JOB];
		if(pJobs_Info[playerid][job_index][pjob_EXP] >= (Jobs[job_index][job_EXP_FOR_NEXT_LEVEL] * pJobs_Info[playerid][job_index][pjob_LEVEL]))
		{
			pJobs_Info[playerid][job_index][pjob_LEVEL] ++;
			pJobs_Info[playerid][job_index][pjob_EXP] = 1;	
			FormatJobLevelUpMessage(playerid, Jobs[job_index][job_ID], pJobs_Info[playerid][job_index][pjob_LEVEL]);
		}
	}
	pJobs_Info[playerid][job_index][pjob_JOBS] ++;
	SavePlayerJobInfo(playerid, job_index);

	//pjob payment
	new extra_percentage = (100 + Jobs[job_index][job_PERCENTAGE_PAYMENT_LEVEL] * (pJobs_Info[playerid][job_index][pjob_LEVEL] - 1));
	new base_payment = floatround(floatdiv(floatmul(float(Jobs_Points[job_index][job_point_index][job_point_BASE_PAYMENT]), float(extra_percentage)), 100.0));
	new payment = floatround(floatmul(float(base_payment), pay_percentage));
	if(payment > Jobs[job_index][job_MAX_PAYMENT]) payment = Jobs[job_index][job_MAX_PAYMENT];
	
	GivePlayerMoneyEx(playerid, payment);
	return 1;
}

YCMD:jobs(playerid, params[], help)
{
	new line_str[128], dialog[128 * (MAX_JOBS + 1)];
	format(dialog, sizeof dialog, "%s", GetPJobsDialogHeader(playerid));
	foreach(new i : Jobs)
	{
		format(line_str, sizeof line_str, "%s\t%d\t%d/%d\t%d\n", GetJobName(playerid, Jobs[i][job_ID]), pJobs_Info[playerid][i][pjob_LEVEL], pJobs_Info[playerid][i][pjob_EXP], (Jobs[i][job_EXP_FOR_NEXT_LEVEL] * pJobs_Info[playerid][i][pjob_LEVEL]), pJobs_Info[playerid][i][pjob_JOBS]);
		strcat(dialog, line_str);
	}
	inline OnPlayerDialog(pid, did, res, lis, string:inp[])
	{
		#pragma unused pid, did, res, lis, inp
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_TABLIST_HEADERS, GetPJobsDialogCaption(playerid), dialog, "X", "");
	return 1;
}