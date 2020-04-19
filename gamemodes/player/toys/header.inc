#define MAX_PLAYER_TOYS 5

enum E_pToys
{
	ptoy_ID,
	ptoy_INV_ITEMID,
	ptoy_ATTACHED,
	ptoy_MODELID,
	ptoy_BONE,
	Float:ptoy_X,
	Float:ptoy_Y,
	Float:ptoy_Z,
	Float:ptoy_RX,
	Float:ptoy_RY,
	Float:ptoy_RZ,
	Float:ptoy_SX,
	Float:ptoy_SY,
	Float:ptoy_SZ,
	ptoy_COLOR1,
	ptoy_COLOR2
};
new	pToys[MAX_PLAYERS][MAX_PLAYER_TOYS][E_pToys],
	Iterator:pToys[MAX_PLAYERS]<MAX_PLAYER_TOYS>;

enum E_pToys_Clothes
{
	Float:ptoy_clothe_X,
	Float:ptoy_clothe_Y,
	Float:ptoy_clothe_Z,
	Float:ptoy_clothe_RX,
	Float:ptoy_clothe_RY,
	Float:ptoy_clothe_RZ,
	Float:ptoy_clothe_SX,
	Float:ptoy_clothe_SY,
	Float:ptoy_clothe_SZ
};
new pToys_Clothes[MAX_PLAYERS][MAX_PLAYER_TOYS][MAX_CLOTHING_CLOTHES_PER_CHAR][E_pToys_Clothes];

forward OnPlayerRequestConfigToy(playerid, index);
forward OnPlayerAttachToy(playerid, toy_index);
forward OnPlayerRemoveToy(playerid, toy_index);
forward OnPlayerCheckTime(playerid);