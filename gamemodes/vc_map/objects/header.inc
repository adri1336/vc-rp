new bool:vcObjects_Debug;
#define DEBUG_LABEL_STREAM_DISTANCE 100.0
#define DEFAULT_VC_STREAM_DISTANCE 300.0
#define MAX_VC_OBJECTS 8000

enum enum_Vc_Objects
{
	vc_ID,
	vc_OBJECTID,
	vc_MODELID,
	Float:vc_X,
	Float:vc_Y,
	Float:vc_Z,
	Float:vc_RX,
	Float:vc_RY,
	Float:vc_RZ,
	vc_INTERIORID,
	vc_WORLDID,
	vc_OBJECT_TYPE,
	vc_OBJECT_TYPE_INDEX,
	Text3D:vc_OBJECT_LABEL
};
new Vc_Objects[MAX_VC_OBJECTS][enum_Vc_Objects];
new Iterator:Vc_Objects<MAX_VC_OBJECTS>;

forward OnPlayerViceCityObjectAdding(playerid, modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, world, interior);