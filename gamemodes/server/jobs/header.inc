//ids
enum
{
	JOB_TAXI = 1,
	JOB_TRUCKER,
	JOB_GUNSMITH
};

enum
{
	JOB_POINT_TAXI = 1,
	JOB_POINT_TRUCKER_1,
	JOB_POINT_TRUCKER_2,
	JOB_POINT_GUNSMITH
};

#define MAX_JOBS 5
enum E_Jobs
{
	job_ID,
	job_NAME[32],
	job_ICON[32],
	job_MAPICON,
	job_MIN_LEVEL,
	job_MAX_PAYMENT,
	job_EXP_PER_JOB,
	job_EXP_FOR_NEXT_LEVEL,
	job_PERCENTAGE_PAYMENT_LEVEL
};
new Jobs[MAX_JOBS][E_Jobs],
	Iterator:Jobs<MAX_JOBS>;

#define MAX_JOBS_POINTS 5
enum E_Jobs_Points
{
	//db
	job_point_ID,
	job_point_ID_JOB,
	job_point_MIN_JOB_LEVEL,
	job_point_ACTOR_SKIN,
	Float:job_point_X,
	Float:job_point_Y,
	Float:job_point_Z,
	Float:job_point_ANGLE,
	job_point_BASE_PAYMENT,
	job_point_ID_ENTRANCE_DOOR,

	//otro
	job_point_INDEX_ENTRANCE_DOOR,
	job_point_PICKUP_ID,
	job_point_AREA_ID,
	job_point_LABEL_AREA_ID,
	job_point_ACTOR_ID,
	Timer:job_point_ACTOR_TIMER
};
new Jobs_Points[MAX_JOBS][MAX_JOBS_POINTS][E_Jobs_Points],
	Iterator:Jobs_Points[MAX_JOBS]<MAX_JOBS_POINTS>;