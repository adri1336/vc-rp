// Players Move Speed
#define MOVE_SPEED              100.0
#define ACCEL_RATE              0.03

// Players Mode
#define CAMERA_MODE_NONE    	0
#define CAMERA_MODE_FLY     	1

// Key state definitions
#define MOVE_FORWARD    		1
#define MOVE_BACK       		2
#define MOVE_LEFT       		3
#define MOVE_RIGHT      		4
#define MOVE_FORWARD_LEFT       5
#define MOVE_FORWARD_RIGHT      6
#define MOVE_BACK_LEFT          7
#define MOVE_BACK_RIGHT         8
#define MOVE_UP                 9
#define MOVE_DOWN               10

// Enumeration for storing data about the player
enum noclipenum
{
	cameramode,
	flyobject,
	mode,
	lrold,
	udold,
	lastmove,
	Float:accelmul
}
new noclipdata[MAX_PLAYERS][noclipenum];