#define MAX_VINV_BUTTONS 3
enum
{
	VINV_BUTTON_TAKE,
	VINV_BUTTON_MOVE,
	VINV_BUTTON_DELETE
}

#define MAX_VEHICLE_INVENTORY_SLOTS 20
enum E_VehicleInventory
{
	vinv_ID,
	vinv_ITEM_ID,
	vinv_AMOUNT,
	vinv_PARAMS[128]
};
new VehicleInventory[MAX_VEHICLES][MAX_VEHICLE_INVENTORY_SLOTS][E_VehicleInventory],
	Iterator:VehicleInventory[MAX_VEHICLES]<MAX_VEHICLE_INVENTORY_SLOTS>;

new vInvArea[MAX_VEHICLES] = {INVALID_STREAMER_ID, ...},
	bool:vInvInUse[MAX_VEHICLES];

forward OnVehicleInvItemAdded(vehindex, index, amount);
forward OnVehicleInvItemDBAdded(vehindex, index, item_id, params[], amount);