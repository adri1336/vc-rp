forward OnVehiclesPricesLoad();

#define MAX_VEHICLE_MODELIDS 300

enum enum_Vehicle_Prices
{
	vehicle_price_MODELID,
	vehicle_price_PRICE,
	vehicle_price_LEVEL
};
new Vehicle_Prices[MAX_VEHICLE_MODELIDS][enum_Vehicle_Prices],
	Iterator:Vehicle_Prices<MAX_VEHICLE_MODELIDS>;