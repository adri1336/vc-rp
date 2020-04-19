#define INVENTORY_COLUMNS 5
#define INVENTORY_POS_X 538.0
#define INVENTORY_POS_Y 228.0
#define INVENTORY_ITEM_SIZE_X 30.0
#define INVENTORY_ITEM_SIZE_Y 30.0
#define INVENTORY_ITEM_SPACE 2.0
#define INVENTORY_TEXT_SIZE_Y 14.0
#define INVENTORY_MESSAGE_SPACE 15.0
#define INVENTORY_MESSAGE_OFFSET 17.0
#define INV_TD_AMOUNT_OFFSET_X 29.0
#define INV_TD_AMOUNT_OFFSET_Y 23.0
#define INV_BUTTONS_TEXT_SEPARATION 10.0
#define INV_BUTTONS_BOX_SPACE 4.0
#define INV_BUTTONS_BOX_SIZE_X 50.0
#define MAX_INV_BUTTONS 5

#define PLAYER_INV_MAX_SLOTS 25

new PlayerText:PTD_INV_BASE[MAX_PLAYERS][3] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},

	PlayerText:PTD_INV_ITEMS_BOX[MAX_PLAYERS][PLAYER_INV_MAX_SLOTS] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PlayerText:PTD_INV_ITEMS[MAX_PLAYERS][PLAYER_INV_MAX_SLOTS] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PlayerText:PTD_INV_ITEMS_AMOUNT[MAX_PLAYERS][PLAYER_INV_MAX_SLOTS] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},

	PlayerText:PTD_INV_INFO_MESSAGE[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
	PlayerText:PTD_INV_BUTTONS_BOX[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
	PlayerText:PTD_INV_BUTTONS[MAX_PLAYERS][MAX_INV_BUTTONS] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...};


enum enum_PINV
{
	pinv_ID,
	pinv_ITEM_ID,
	pinv_AMOUNT,
	pinv_PARAMS[128]
};

new PINV[MAX_PLAYERS][PLAYER_INV_MAX_SLOTS][enum_PINV],
	Iterator:PINV[MAX_PLAYERS]<PLAYER_INV_MAX_SLOTS>,
	bool:pInvetory[MAX_PLAYERS],
	pInvSelected[MAX_PLAYERS],
	pInvExtraId[MAX_PLAYERS],
	Float:pInvTextDrawPosition[MAX_PLAYERS][PLAYER_INV_MAX_SLOTS][2],
	bool:pInvTextDrawInverted[MAX_PLAYERS][PLAYER_INV_MAX_SLOTS][2],
	INV_BUTTONS_TYPES:pInvButtonAction[MAX_PLAYERS][MAX_INV_BUTTONS] = {{INV_BUTTON_TYPE_NONE, ...}, ...},
	bool:pInvDisableInv[MAX_PLAYERS],
	bool:pInvMoving[MAX_PLAYERS],
	pInvMove_Index[MAX_PLAYERS] = {-1, ...},
	pInvGivePlayerid[MAX_PLAYERS],
	pInvGiveAmount[MAX_PLAYERS],

	pLastDrink[MAX_PLAYERS],
	pLastEat[MAX_PLAYERS],
	pEatVomit[MAX_PLAYERS],
	pLastVomit[MAX_PLAYERS];

forward DB_OnPlayerInvItemAdded(playerid, index, item_id, params[], amount);
forward OnPlayerItemAdded(playerid, index, item_id, amount);
forward OnPlayerItemDeleted(playerid, index, inv_id, itemid, params[], bool:player_action, amount);
forward OnPlayerOpenInventory(playerid);
forward OnPlayerCloseInventory(playerid);
forward OnPlayerInvDataLoaded(playerid);