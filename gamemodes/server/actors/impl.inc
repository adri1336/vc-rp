#include <YSI\y_hooks>

hook OnScriptInit()
{	
	inline OnActorsLoad()
	{
		new rows;
		if(cache_get_row_count(rows))
		{
			for(new i = 0; i != rows; i ++)
			{
				new index = Iter_Free(ActorInfo);
				if(index != cellmin)
				{
					new id, skin, Float:x, Float:y, Float:z, Float:angle, animation, animlib[24], animname[24], anim_loop, lockx, locky, freeze, time, clerk,
						bool:isnull_id_entrance, bool:isnull_id_business, bool:isnull_id_property, worldid = VC_WORLD;

					cache_get_value_name_int(i, "id", id);
					cache_get_value_name_int(i, "skin", skin);
					cache_get_value_name_float(i, "x", x);
					cache_get_value_name_float(i, "y", y);
					cache_get_value_name_float(i, "z", z);
					cache_get_value_name_float(i, "angle", angle);
					cache_get_value_name_int(i, "animation", animation);
					cache_get_value_name(i, "animlib", animlib, 24);
					cache_get_value_name(i, "animname", animname, 24);
					cache_get_value_name_int(i, "anim_loop", anim_loop);
					cache_get_value_name_int(i, "lockx", lockx);
					cache_get_value_name_int(i, "locky", locky);
					cache_get_value_name_int(i, "freeze", freeze);
					cache_get_value_name_int(i, "time", time);
					cache_get_value_name_int(i, "clerk", clerk);
					//worldid
					new extra_id, extra_index;
					cache_is_value_name_null(i, "id_entrance", isnull_id_entrance);
					cache_is_value_name_null(i, "id_business", isnull_id_business);
					cache_is_value_name_null(i, "id_property", isnull_id_property);
					if(!isnull_id_entrance)
					{
						cache_get_value_name_int(i, "id_entrance", extra_id);
						extra_index = GetEntranceIndexByEntranceId(extra_id);
						if(extra_index != -1)
						worldid = Entrances[extra_index][entrance_ID_ENTRANCE];
					}
					else if(!isnull_id_business)
					{
						cache_get_value_name_int(i, "id_business", extra_id);
						extra_index = GetBusinessIndexFromId(extra_id);
						if(extra_index != -1)
						worldid = BusinessData[extra_index][bdata_ID];
					}
					else if(!isnull_id_property)
					{
						cache_get_value_name_int(i, "id_property", extra_id);
						extra_index = GetPropertyIndexFromId(extra_id);
						if(extra_index != -1)
						worldid = PropertyInfo[extra_index][property_ID];
					}

					//actor
					new actorid = CreateDynamicActor(skin, x, y, z, angle, .worldid = worldid);
					Streamer_SetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_EXTRA_ID, _:ACTOR_TYPE_ACTOR);
					
					if(animation)
					ApplyDynamicActorAnimation(actorid, animlib, animname, 4.1, anim_loop, lockx, locky, freeze, time);

					//info
					ActorInfo[index][actor_ID] = id;
					ActorInfo[index][actor_SKIN] = skin;
					ActorInfo[index][actor_X] = x;
					ActorInfo[index][actor_Y] = y;
					ActorInfo[index][actor_Z] = z;
					ActorInfo[index][actor_ANGLE] = angle;
					ActorInfo[index][actor_ANIMATION] = animation;
					format(ActorInfo[index][actor_ANIMLIB], 32, "%s", animlib);
					format(ActorInfo[index][actor_ANIMNAME], 32, "%s", animname);
					ActorInfo[index][actor_ANIM_LOOP] = anim_loop;
					ActorInfo[index][actor_LOCKX] = lockx;
					ActorInfo[index][actor_LOCKY] = locky;
					ActorInfo[index][actor_FREEZE] = freeze;
					ActorInfo[index][actor_TIME] = time;
					ActorInfo[index][actor_CLERK] = clerk;
					ActorInfo[index][actor_ENTRANCE] = !isnull_id_entrance;
					ActorInfo[index][actor_BUSINESS] = !isnull_id_business;
					ActorInfo[index][actor_PROPERTY] = !isnull_id_property;
					ActorInfo[index][actor_EXTRA_INDEX] = extra_index;
					ActorInfo[index][actor_ACTORID] = actorid;
					Iter_Add(ActorInfo, index);
					CallRemoteFunction("OnActorLoaded", "i", index);
				}
			}
		}
	}
	mysql_tquery_inline(vcrp_db, "SELECT * FROM actors;", using inline OnActorsLoad, "");
	return 1;
}