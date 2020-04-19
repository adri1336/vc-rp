forward OnPlayerRequestJob(playerid, job_index, job_point_index);
forward OnPlayerCompleteJob(playerid, job_index, job_point_index, Float:pay_percentage);
forward OnPlayerRequestFinJob(playerid, job_index, job_point_index);

new pCurrentJobIndex[MAX_PLAYERS][2];

enum E_pJobs_Info
{
	pjob_LEVEL,
	pjob_EXP,
	pjob_JOBS
};
new pJobs_Info[MAX_PLAYERS][MAX_JOBS][E_pJobs_Info];

#include "player/jobs/jobs/taxi"
#include "player/jobs/jobs/truck"
#include "player/jobs/jobs/gunsmith"