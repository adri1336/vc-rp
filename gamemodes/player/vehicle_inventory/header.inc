#define VINV_TD_PADDING 2.0
#define VINV_TD_TEXT_OFFSET_Y 13.45484
#define VINV_TD_TEXT2_OFFSET_Y 9.94369
#define VINV_TD_ITEMS_PER_ROW 5
#define VINV_BUTTONS_BOX_SIZE_X 50.0

new bool:pVInv[MAX_PLAYERS],
	bool:pVInvMoving[MAX_PLAYERS],
	pVInvMove_Index[MAX_PLAYERS] = {-1, ...},
	pVInvSelected[MAX_PLAYERS] = {-1, ...},
	pVInvArea[MAX_PLAYERS] = {INVALID_STREAMER_ID, ...},
	pVInvVehIndex[MAX_PLAYERS] = {INVALID_VEHICLE_INDEX, ...},

	Float:pVInvTextDrawPosition[MAX_PLAYERS][MAX_VEHICLE_INVENTORY_SLOTS][2],
	bool:pVInvTextDrawInverted[MAX_PLAYERS][MAX_VEHICLE_INVENTORY_SLOTS][2];

new PlayerText:pVInvTd_BASE[MAX_PLAYERS][4] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},

	PlayerText:pVInvTd_ITEMS_BOX[MAX_PLAYERS][MAX_VEHICLE_INVENTORY_SLOTS] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PlayerText:pVInvTd_ITEMS[MAX_PLAYERS][MAX_VEHICLE_INVENTORY_SLOTS] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PlayerText:pVInvTd_ITEMS_AMOUNT[MAX_PLAYERS][MAX_VEHICLE_INVENTORY_SLOTS] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},

	PlayerText:pVInvTd_INFO_MESSAGE[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
	PlayerText:pVInvTd_BUTTONS_BOX[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
	PlayerText:pVInvTd_BUTTONS[MAX_PLAYERS][MAX_INV_BUTTONS] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...};

forward OnPlayerOpenVehicleInventory(playerid, vehindex);
forward OnPlayerCloseVehicleInventory(playerid, vehindex);