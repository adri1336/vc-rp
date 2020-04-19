#define MAX_LOADED_ACTORS 500

enum E_ActorInfo
{
    actor_ID,
    actor_SKIN,
    Float:actor_X,
    Float:actor_Y,
    Float:actor_Z,
    Float:actor_ANGLE,
    actor_ANIMATION,
    actor_ANIMLIB[32],
    actor_ANIMNAME[32],
    actor_ANIM_LOOP,
    actor_LOCKX,
    actor_LOCKY,
    actor_FREEZE,
    actor_TIME,
    actor_CLERK,

    bool:actor_ENTRANCE,
    bool:actor_BUSINESS,
    bool:actor_PROPERTY,
    actor_EXTRA_INDEX,
    actor_ACTORID,
}
new ActorInfo[MAX_LOADED_ACTORS][E_ActorInfo],
    Iterator:ActorInfo<MAX_LOADED_ACTORS>;

forward OnActorLoaded(index);