#include <YSI\y_hooks>

hook OnScriptInit()
{
	Iter_Init(Jobs_Points);
	//
	inline OnJobsLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				new bool:isnull_NAME, bool:isnull_ICON, bool:isnull_MAPICON;
				cache_get_value_name_int(i, "id", Jobs[i][job_ID]);
				cache_is_value_name_null(i, "name", isnull_NAME);
				if(!isnull_NAME) cache_get_value_name(i, "name", Jobs[i][job_NAME]);
				cache_is_value_name_null(i, "name", isnull_ICON);
				if(!isnull_ICON) cache_get_value_name(i, "icon", Jobs[i][job_ICON]);
				cache_is_value_name_null(i, "mapicon", isnull_MAPICON);
				if(!isnull_MAPICON) cache_get_value_name_int(i, "mapicon", Jobs[i][job_MAPICON]);
				cache_get_value_name_int(i, "min_level", Jobs[i][job_MIN_LEVEL]);
				cache_get_value_name_int(i, "max_payment", Jobs[i][job_MAX_PAYMENT]);
				cache_get_value_name_int(i, "exp_per_job", Jobs[i][job_EXP_PER_JOB]);
				cache_get_value_name_int(i, "exp_for_next_level", Jobs[i][job_EXP_FOR_NEXT_LEVEL]);
				cache_get_value_name_int(i, "percentage_payment_level", Jobs[i][job_PERCENTAGE_PAYMENT_LEVEL]);
				Iter_Add(Jobs, i);
				//points
				inline OnJobPointsLoad()
				{
					new in_rows;
					if(cache_get_row_count(in_rows))
					{
						for(new x = 0; x != in_rows; x ++)
						{
							new bool:isnull_ACTOR_SKIN, bool:isnull_ID_ENTRANCE_DOOR;
							cache_get_value_name_int(x, "id", Jobs_Points[i][x][job_point_ID]);
							cache_get_value_name_int(x, "id_job", Jobs_Points[i][x][job_point_ID_JOB]);
							cache_get_value_name_int(x, "min_job_level", Jobs_Points[i][x][job_point_MIN_JOB_LEVEL]);
							cache_is_value_name_null(x, "actor_skin", isnull_ACTOR_SKIN);
							if(!isnull_ACTOR_SKIN) cache_get_value_name_int(x, "actor_skin", Jobs_Points[i][x][job_point_ACTOR_SKIN]);
							else Jobs_Points[i][x][job_point_ACTOR_SKIN] = -1;
							cache_get_value_name_float(x, "x", Jobs_Points[i][x][job_point_X]);
							cache_get_value_name_float(x, "y", Jobs_Points[i][x][job_point_Y]);
							cache_get_value_name_float(x, "z", Jobs_Points[i][x][job_point_Z]);
							cache_get_value_name_float(x, "angle", Jobs_Points[i][x][job_point_ANGLE]);
							cache_get_value_name_int(x, "base_payment", Jobs_Points[i][x][job_point_BASE_PAYMENT]);
							cache_is_value_name_null(x, "id_entrance_door", isnull_ID_ENTRANCE_DOOR);
							if(!isnull_ID_ENTRANCE_DOOR)
							{
								cache_get_value_name_int(x, "id_entrance_door", Jobs_Points[i][x][job_point_ID_ENTRANCE_DOOR]);
								Jobs_Points[i][x][job_point_INDEX_ENTRANCE_DOOR] = GetEntranceIndexByEntranceDId(Jobs_Points[i][x][job_point_ID_ENTRANCE_DOOR]);
							}
							else Jobs_Points[i][x][job_point_INDEX_ENTRANCE_DOOR] = -1;
							Iter_Add(Jobs_Points[i], x);
							CreateJobPointInfo(i, x);
						}
					}
				}
				mysql_format(vcrp_db, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM jobs_points WHERE id_job = %d LIMIT "#MAX_JOBS_POINTS";", Jobs[i][job_ID]);
				mysql_tquery_inline(vcrp_db, QUERY_BUFFER, using inline OnJobPointsLoad, "");
			}
		}
	}
	printf("[INFO]: Cargando trabajos...");
	mysql_tquery_inline(vcrp_db, "SELECT * FROM jobs LIMIT "#MAX_JOBS";", using inline OnJobsLoad, "");
	return 1;
}

timer OnJobPointActorDefaultAnim[3000](job_index, job_point_index)
{
	Jobs_Points[job_index][job_point_index][job_point_ACTOR_TIMER] = Timer:-1;
	ApplyDynamicActorAnimation(Jobs_Points[job_index][job_point_index][job_point_ACTOR_ID], "COP_AMBIENT", "Coplook_loop", 4.1, true, 0, 0, 1, 0);
	return 1;
}