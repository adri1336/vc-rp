loadtext lang[jobs];

GetPlayerJobId(playerid)
{
	if(pCurrentJobIndex[playerid][0] != -1 && pCurrentJobIndex[playerid][1] != -1)
	{
		return Jobs[ pCurrentJobIndex[playerid][0] ][job_ID];
	}
	return 0;
}

GetPlayerJobPointId(playerid)
{
	if(pCurrentJobIndex[playerid][0] != -1 && pCurrentJobIndex[playerid][1] != -1)
	{
		return Jobs_Points[ pCurrentJobIndex[playerid][0] ][ pCurrentJobIndex[playerid][1] ][job_point_ID];
	}
	return 0;
}

IsPlayerInAnyJob(playerid)
{
	if(pCurrentJobIndex[playerid][0] != -1 && pCurrentJobIndex[playerid][1] != -1)
	{
		return true;
	}
	return false;
}

SavePlayerJobInfo(playerid, job_index)
{
	mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "INSERT INTO player_jobs_info VALUES (%d, %d, %d, %d, %d) ON DUPLICATE KEY UPDATE level = %d, exp = %d, jobs = %d;", PI[playerid][pi_ID], Jobs[job_index][job_ID], pJobs_Info[playerid][job_index][pjob_LEVEL], pJobs_Info[playerid][job_index][pjob_EXP], pJobs_Info[playerid][job_index][pjob_JOBS], pJobs_Info[playerid][job_index][pjob_LEVEL], pJobs_Info[playerid][job_index][pjob_EXP], pJobs_Info[playerid][job_index][pjob_JOBS]);
	mysql_tquery(vcrp_db, QUERY_BUFFER);
	return 1;
}

GetJobName(playerid, jobid)
{
	new name[64];
	switch(jobid)
	{
		case JOB_TAXI: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $JOB_TAXI);
		case JOB_TRUCKER: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $JOB_TRUCKER);
		case JOB_GUNSMITH: Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $JOB_GUNSMITH);
	}
	return name;
}

FormatJobLevelUpMessage(playerid, id_job, level)
{
	new str[64];
	Text_Format_TD(str, sizeof str, PI[playerid][pi_LANG_ID], $TEXTDRAW_JOB_LEVEL_UP, GetJobName(playerid, id_job), level);
	ShowPlayerInfoMessage(playerid, str, 5);
	return 1;
}

GetPJobsDialogHeader(playerid)
{
	new name[128];
	Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $DIALOG_HEADER);
	return name;
}

GetPJobsDialogCaption(playerid)
{
	new name[32];
	Text_Format_Dialog(name, sizeof name, PI[playerid][pi_LANG_ID], $DIALOG_CAPTION);
	return name;
}