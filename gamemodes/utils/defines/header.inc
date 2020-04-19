// HOLDING(keys)
#define HOLDING(%0) \
	((newkeys & (%0)) == (%0))

// PRESSED(keys)
#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

// PRESSING(keyVariable, keys)
#define PRESSING(%0,%1) \
	(%0 & (%1))

// RELEASED(keys)
#define RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

#define ACTION_DISTANCE 15.0
#define SPECIAL_ACTION_PISSING 68

#define HidePlayerDialog(%1)		ShowPlayerDialog(%1, -1, 0, " ", " ", " ", " ")

//
#define ADMIN_LEVEL_NONE			0
#define ADMIN_LEVEL_MODERATOR		1
#define ADMIN_LEVEL_ADMINISTRATOR	2
#define ADMIN_LEVEL_DEVELOPER		3
#define MAX_ADMIN_LEVELS			4
//

#define VC_WORLD 0
#define CUSTOM_PICKUPS true
#define CUSTOM_PICKUP_MODELID 19135
#define PICKUP_DISTANCE 50.0
#define ACTION_KEY KEY_YES
#define ACTION_KEY_STR "~k~~CONVERSATION_YES~"
#define SECONDARY_ACTION_KEY KEY_CTRL_BACK
#define SECONDARY_ACTION_KEY_STR "~k~~GROUP_CONTROL_BWD~"