CreateJobPointInfo(index_job, index_point)
{
	//destroy (if exists)
	#if CUSTOM_PICKUPS == true
		if(Jobs_Points[index_job][index_point][job_point_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicObject(Jobs_Points[index_job][index_point][job_point_PICKUP_ID]);
			Jobs_Points[index_job][index_point][job_point_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#else
		if(Jobs_Points[index_job][index_point][job_point_PICKUP_ID] != INVALID_STREAMER_ID)
		{
			DestroyDynamicPickup(Jobs_Points[index_job][index_point][job_point_PICKUP_ID]);
			Jobs_Points[index_job][index_point][job_point_PICKUP_ID] = INVALID_STREAMER_ID;
		}
	#endif
	if(Jobs_Points[index_job][index_point][job_point_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(Jobs_Points[index_job][index_point][job_point_AREA_ID]);
		Jobs_Points[index_job][index_point][job_point_AREA_ID] = INVALID_STREAMER_ID;
	}
	if(Jobs_Points[index_job][index_point][job_point_LABEL_AREA_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicArea(Jobs_Points[index_job][index_point][job_point_LABEL_AREA_ID]);
		Jobs_Points[index_job][index_point][job_point_LABEL_AREA_ID] = INVALID_STREAMER_ID;
	}
	if(Jobs_Points[index_job][index_point][job_point_ACTOR_ID] != INVALID_STREAMER_ID)
	{
		DestroyDynamicActor(Jobs_Points[index_job][index_point][job_point_ACTOR_ID]);
		Jobs_Points[index_job][index_point][job_point_ACTOR_ID] = INVALID_STREAMER_ID;
	}
	Jobs_Points[index_job][index_point][job_point_ACTOR_TIMER] = Timer:-1;

	//create
	#if CUSTOM_PICKUPS == true
		if(Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] != -1) Jobs_Points[index_job][index_point][job_point_PICKUP_ID] = CreateDynamicObject(CUSTOM_PICKUP_MODELID, Jobs_Points[index_job][index_point][job_point_X], Jobs_Points[index_job][index_point][job_point_Y], Jobs_Points[index_job][index_point][job_point_Z], 0.0, 0.0, 0.0, .worldid = Entrances[ Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] ][entrance_ID_ENTRANCE], .interiorid = Interiors[Entrances[ Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] ][entrance_INTERIOR_INDEX]][interior_INTERIORID], .streamdistance = PICKUP_DISTANCE, .drawdistance = PICKUP_DISTANCE, .priority = 10);	
		else Jobs_Points[index_job][index_point][job_point_PICKUP_ID] = CreateDynamicObject(CUSTOM_PICKUP_MODELID, Jobs_Points[index_job][index_point][job_point_X], Jobs_Points[index_job][index_point][job_point_Y], Jobs_Points[index_job][index_point][job_point_Z], 0.0, 0.0, 0.0, VC_WORLD, 0, .streamdistance = PICKUP_DISTANCE, .drawdistance = PICKUP_DISTANCE, .priority = 10);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, Jobs_Points[index_job][index_point][job_point_PICKUP_ID], E_STREAMER_EXTRA_ID, _:OBJECT_TYPE_PICKUP_JOB_POINT);
	#else
		new pickup_model = 1314;
		if(Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] != -1) Jobs_Points[index_job][index_point][job_point_PICKUP_ID] = CreateDynamicPickup(pickup_model, 1, Jobs_Points[index_job][index_point][job_point_X], Jobs_Points[index_job][index_point][job_point_Y], Jobs_Points[index_job][index_point][job_point_Z], Entrances[ Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] ][entrance_ID_ENTRANCE], Interiors[Entrances[ Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] ][entrance_INTERIOR_INDEX]][interior_INTERIORID], .streamdistance = PICKUP_DISTANCE, .priority = 10);
		else Jobs_Points[index_job][index_point][job_point_PICKUP_ID] = CreateDynamicPickup(pickup_model, 1, Jobs_Points[index_job][index_point][job_point_X], Jobs_Points[index_job][index_point][job_point_Y], Jobs_Points[index_job][index_point][job_point_Z], VC_WORLD, 0, .streamdistance = PICKUP_DISTANCE, .priority = 10);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, Jobs_Points[index_job][index_point][job_point_PICKUP_ID], E_STREAMER_EXTRA_ID, _:PICKUP_TYPE_PICKUP_JOB_POINT);
	#endif

	new streamer_info[3];
	if(Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] != -1) Jobs_Points[index_job][index_point][job_point_AREA_ID] = CreateDynamicCylinder(Jobs_Points[index_job][index_point][job_point_X], Jobs_Points[index_job][index_point][job_point_Y], Jobs_Points[index_job][index_point][job_point_Z] - 1.0, Jobs_Points[index_job][index_point][job_point_Z] + 3.0, 1.0, Entrances[ Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] ][entrance_ID_ENTRANCE], Interiors[Entrances[ Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] ][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
	else Jobs_Points[index_job][index_point][job_point_AREA_ID] = CreateDynamicCylinder(Jobs_Points[index_job][index_point][job_point_X], Jobs_Points[index_job][index_point][job_point_Y], Jobs_Points[index_job][index_point][job_point_Z] - 1.0, Jobs_Points[index_job][index_point][job_point_Z] + 3.0, 1.0, VC_WORLD, 0);
	streamer_info[0] = _:AREA_TYPE_JOB_POINT;
	streamer_info[1] = index_job;
	streamer_info[2] = index_point;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, Jobs_Points[index_job][index_point][job_point_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);

	if(Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] != -1) Jobs_Points[index_job][index_point][job_point_LABEL_AREA_ID] = CreateDynamicCylinder(Jobs_Points[index_job][index_point][job_point_X], Jobs_Points[index_job][index_point][job_point_Y], Jobs_Points[index_job][index_point][job_point_Z] - PLAYER_LABEL_DISTANCE, Jobs_Points[index_job][index_point][job_point_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, Entrances[ Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] ][entrance_ID_ENTRANCE], Interiors[Entrances[ Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] ][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
	else Jobs_Points[index_job][index_point][job_point_LABEL_AREA_ID] = CreateDynamicCylinder(Jobs_Points[index_job][index_point][job_point_X], Jobs_Points[index_job][index_point][job_point_Y], Jobs_Points[index_job][index_point][job_point_Z] - PLAYER_LABEL_DISTANCE, Jobs_Points[index_job][index_point][job_point_Z] + PLAYER_LABEL_DISTANCE, PLAYER_LABEL_DISTANCE, VC_WORLD, 0);
	streamer_info[0] = _:AREA_TYPE_LABEL_JOB_POINT;
	streamer_info[1] = index_job;
	streamer_info[2] = index_point;
	Streamer_SetArrayData(STREAMER_TYPE_AREA, Jobs_Points[index_job][index_point][job_point_LABEL_AREA_ID], E_STREAMER_EXTRA_ID, streamer_info);

	if(Jobs_Points[index_job][index_point][job_point_ACTOR_SKIN] != -1)
	{
		new Float:actor_x, Float:actor_y;
		actor_x = Jobs_Points[index_job][index_point][job_point_X] - (1.0 * floatsin(-Jobs_Points[index_job][index_point][job_point_ANGLE], degrees));
		actor_y = Jobs_Points[index_job][index_point][job_point_Y] - (1.0 * floatcos(-Jobs_Points[index_job][index_point][job_point_ANGLE], degrees));
		if(Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] != -1) Jobs_Points[index_job][index_point][job_point_ACTOR_ID] = CreateDynamicActor(Jobs_Points[index_job][index_point][job_point_ACTOR_SKIN], actor_x, actor_y, Jobs_Points[index_job][index_point][job_point_Z], Jobs_Points[index_job][index_point][job_point_ANGLE], .worldid = Entrances[ Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] ][entrance_ID_ENTRANCE], .interiorid = Interiors[Entrances[ Jobs_Points[index_job][index_point][job_point_INDEX_ENTRANCE_DOOR] ][entrance_INTERIOR_INDEX]][interior_INTERIORID]);
		else Jobs_Points[index_job][index_point][job_point_ACTOR_ID] = CreateDynamicActor(Jobs_Points[index_job][index_point][job_point_ACTOR_SKIN], actor_x, actor_y, Jobs_Points[index_job][index_point][job_point_Z], Jobs_Points[index_job][index_point][job_point_ANGLE], .worldid = VC_WORLD, .interiorid = 0);
		Streamer_SetIntData(STREAMER_TYPE_ACTOR, Jobs_Points[index_job][index_point][job_point_ACTOR_ID], E_STREAMER_EXTRA_ID, _:ACTOR_TYPE_JOB_POINT);
		ApplyDynamicActorAnimation(Jobs_Points[index_job][index_point][job_point_ACTOR_ID], "COP_AMBIENT", "Coplook_loop", 4.1, true, 0, 0, 1, 0);
	}
	return 1;
}

GetJobIndexById(jobid)
{
	foreach(new i : Jobs)
	{
		if(Jobs[i][job_ID] == jobid)
		{
			return i;
		}
	}
	return -1;
}

SetJobPointActorTempAnim(job_index, job_point_index, animlib[], animname[])
{
	if(Jobs_Points[job_index][job_point_index][job_point_ACTOR_ID] != INVALID_STREAMER_ID)
	{
		if(Jobs_Points[job_index][job_point_index][job_point_ACTOR_TIMER] != Timer:-1)
		{
			stop Jobs_Points[job_index][job_point_index][job_point_ACTOR_TIMER];
			Jobs_Points[job_index][job_point_index][job_point_ACTOR_TIMER] = Timer:-1;
		}
		ApplyDynamicActorAnimation(Jobs_Points[job_index][job_point_index][job_point_ACTOR_ID], animlib, animname, 4.1, false, 0, 0, 1, 0);
		Jobs_Points[job_index][job_point_index][job_point_ACTOR_TIMER] = defer OnJobPointActorDefaultAnim(job_index, job_point_index);
		return 1;
	}
	return 0;
}