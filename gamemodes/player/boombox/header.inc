forward OnPlayerRequestBoomboxCreation(playerid, inv_index);
forward OnPlayerRequestBoomboxConfig(playerid, index);

#define MAX_BOOMBOXS 100
enum E_Boombox
{
    boombox_URL[256],
    boombox_PLAYING[128],
    boombox_ACCOUNT_ID,
    boombox_MODELID,

    boombox_OBJECTID,
    boombox_PLAY_AREAID,
    boombox_LABEL_AREAID,
    boombox_AREAID,
    Timer:boombox_DESTROY_TIMER,

    Float:boombox_X,
    Float:boombox_Y,
    Float:boombox_Z,
    Float:boombox_RX,
    Float:boombox_RY,
    Float:boombox_RZ,
    Float:boombox_DISTANCE,
    boombox_INTERIORID,
    boombox_WORLDID
};
new Boombox[MAX_BOOMBOXS][E_Boombox],
    Iterator:Boombox<MAX_BOOMBOXS>;

#define BOOMBOX_OFFSET_DISTANCE 5.0
#define MIN_DISTANCE_BETWEEN_BOOMBOXS 10.0
#define DEFAULT_BOOMBOX_DISTANCE 15.0
#define DISCONNECTED_PLAYER_BOOMBOX_TIME 300000 //destruir a los 5 minutos de desconectarse
#define INVALID_BOOMBOX_ID -1
#define IsValidBoombox(%0) Iter_Contains(Boombox,%0)