#define MAX_ENTRANCES 100
enum enum_Entrances
{
	entrance_ID,
	entrance_ID_ENTRANCE,
	entrance_RADIO,
	entrance_AUDIO[128],
	entrance_ID_INTERIOR,
	entrance_NAME[45],
	Float:entrance_X,
	Float:entrance_Y,
	Float:entrance_Z,
	Float:entrance_ANGLE,
	entrance_TIME_OPEN,
	entrance_TIME_CLOSE,
	entrance_MAPICON_MODEL,
	entrance_PICKUP_MODEL,
	entrance_SUB_ID,
	
	entrance_INTERIOR_INDEX,
	entrance_SUB_ID_INDEX,

	entrance_MAPICON_ID,
	entrance_PICKUP_ID,
	entrance_AREA_ID,
	entrance_LABEL_AREA_ID,

	entrance_INT_AREA_ID,
	entrance_INT_LABEL_AREA_ID,

	Text3D:entrance_EXT_DEBUG_LABEL,
	Text3D:entrance_INT_DEBUG_LABEL
};
new Entrances[MAX_ENTRANCES][enum_Entrances],
	Iterator:Entrances<MAX_ENTRANCES>;

forward OnEntranceLoad(index);
forward OnEntrancesLoad();