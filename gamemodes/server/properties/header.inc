#define PROPERTY_RENT_MIN_DAYS 1
#define PROPERTY_RENT_MAX_DAYS 10

#define MAX_PROPERTIES 1000
#define MAX_PROPERTIES_DOORS 3

#define CHECK_RENT_PROPERTIES_INTERVAL 600000

enum enum_PropertyInfo
{
	property_ID,
	property_PRICE,
	property_LEVEL,
	property_RENT,
	property_RENT_EXPIRE_DATE[24],
	property_ID_PLAYER,

	property_PLAYER_NAME[24]
};
new PropertyInfo[MAX_PROPERTIES][enum_PropertyInfo],
	Iterator:PropertyInfo<MAX_PROPERTIES>;

enum enum_PropertyDoor
{
	prop_door_ID,
	prop_door_ID_PROPERTY,
	prop_door_CLOSED,
	Float:prop_door_EXT_X,
	Float:prop_door_EXT_Y,
	Float:prop_door_EXT_Z,
	Float:prop_door_EXT_ANGLE,
	prop_door_EXT_ENTRANCE_DOOR_ID,
	prop_door_EXT_SUB_ID,
	prop_door_ID_INTERIOR,
	prop_door_ID_INTERIOR_INDEX,
	//
	prop_door_EXT_ENTR_DOOR_INDEX,
	prop_door_EXT_SUB_INDEX,

	prop_door_EXT_PICKUP_ID,
	prop_door_EXT_AREA_ID,
	prop_door_EXT_LABEL_AREA_ID,

	prop_door_INT_AREA_ID,
	prop_door_INT_LABEL_AREA_ID,

	//
	Text3D:prop_door_EXT_DEBUG_LABEL,
	Text3D:prop_door_INT_DEBUG_LABEL
};
new PropertyDoor[MAX_PROPERTIES][MAX_PROPERTIES_DOORS][enum_PropertyDoor],
	Iterator:PropertyDoor[MAX_PROPERTIES]<MAX_PROPERTIES_DOORS>;