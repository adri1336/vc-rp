//business sales types
enum
{
	BUSINESS_SALE_TYPE_FOOD = 1,
	BUSINESS_SALE_TYPE_DRINK,
	BUSINESS_SALE_TYPE_CLOTHES,
	BUSINESS_SALE_TYPE_TOYS,
	BUSINESS_SALE_TYPE_ELECTRONICS,
	BUSINESS_SALE_TYPE_BAR,
	BUSINESS_SALE_TYPE_WEAPONS,
	BUSINESS_SALE_TYPE_AMMO,
	BUSINESS_SALE_TYPE_ALL, //todo lo que haya en la tienda
	BUSINESS_SALE_TYPE_HARDWARE,
	BUSINESS_SALE_TYPE_CIGARETTES,
	
	BUSINESS_SALE_TYPE_SIZE
};

//business sales points
#define MAX_BUSINESS_SALES_POINTS 100
enum E_BSales_Points
{
	bsale_point_ID,
	bsale_point_ID_TYPE,
	Float:bsale_point_X,
	Float:bsale_point_Y,
	Float:bsale_point_Z,
	bsale_point_ID_INTERIOR,

	//indexs
	bsale_point_INDEX_INTERIOR,

	//pickups
	bsale_point_PICKUP_ID,

	//areas
	bsale_point_AREA_ID,
	bsale_point_LABEL_AREA_ID
};
new BSales_Points[MAX_BUSINESS_SALES_POINTS][E_BSales_Points],
	Iterator:BSales_Points<MAX_BUSINESS_SALES_POINTS>;

//business products info
#define MAX_BUSINESS_PRODUCTS 100
enum E_BProducts_Info
{
	bproduct_info_ID,
	bproduct_info_ID_TYPE,
	bproduct_info_ID_INVITEM,
	bproduct_info_PARAMS[128],
	bproduct_info_PRICE,
	bproduct_info_LEVEL
};
new BProducts_Info[MAX_BUSINESS_PRODUCTS][E_BProducts_Info],
	Iterator:BProducts_Info<MAX_BUSINESS_PRODUCTS>;

//business types
enum
{
	BUSINESS_TYPE_GENERAL_STORE = 1,
	BUSINESS_TYPE_AMMUNATION,
	BUSINESS_TYPE_CLOTHING_STORE,
	BUSINESS_TYPE_RESTAURANT,
	BUSINESS_TYPE_BURGER,
	BUSINESS_TYPE_PIZZA,
	BUSINESS_TYPE_DISCO,
	BUSINESS_TYPE_BAR,
	BUSINESS_TYPE_ELECTRONICS,
	BUSINESS_TYPE_HARDWARE_STORE,

	BUSINESS_TYPE_SIZE
};

//business
#define MAX_BUSINESS 100
#define MAX_BUSINESS_ACTORS 50
#define MAX_DOORS_PER_BUSINESS 10
#define BUSINESS_DEFAULT_MONEY 10000
enum E_BusinessData
{
	bdata_ID,
	bdata_ID_TYPE,
	bdata_PRICE,
	bdata_LEVEL,
	bdata_MONEY,
	bdata_HOUR_OPEN,
	bdata_HOUR_CLOSE,
	bdata_ID_PLAYER,
	bdata_RADIO,
	bdata_PLAYER_NAME[24]
};
new BusinessData[MAX_BUSINESS][E_BusinessData],
	Iterator:BusinessData<MAX_BUSINESS>;


new BusinessActors[MAX_BUSINESS][MAX_BUSINESS_ACTORS],
	Iterator:BusinessActors[MAX_BUSINESS]<MAX_BUSINESS_ACTORS>;

//business doors
enum E_BusinessDoors
{
	bdoor_ID,	
	bdoor_ID_BUSINESS,	
	bdoor_CLOSED,	
	Float:bdoor_EXT_X,
	Float:bdoor_EXT_Y,
	Float:bdoor_EXT_Z,
	Float:bdoor_EXT_ANGLE,
	bdoor_EXT_ENTRANCE_DOOR_ID,
	bdoor_EXT_SUB_ID,
	bdoor_ID_INTERIOR,

	//indexs
	bdoor_INDEX_BUSINESS,
	bdoor_EXT_ENTRANCE_DOOR_INDEX,
	bdoor_EXT_SUB_INDEX,
	bdoor_INDEX_INTERIOR,

	//pickup/object pickup
	bdoor_EXT_PICKUP_ID,

	//areas
	bdoor_EXT_AREA_ID,
	bdoor_EXT_LABEL_AREA_ID,
	bdoor_INT_AREA_ID,
	bdoor_INT_LABEL_AREA_ID,

	//debug labels
	Text3D:bdoor_EXT_DEBUG_LABEL,
	Text3D:bdoor_INT_DEBUG_LABEL
};
new BusinessDoors[MAX_BUSINESS][MAX_DOORS_PER_BUSINESS][E_BusinessDoors],
	Iterator:BusinessDoors[MAX_BUSINESS]<MAX_DOORS_PER_BUSINESS>;

//business sales products
#define MAX_PRODUCTS_PER_BUSINESS 50
#define BUSINESS_DEFAULT_STOCK 100
#define MAX_PRODUCTS_STOCK 100000
enum E_BProducts
{
	bproduct_ID_PRODUCT,
	bproduct_ID_BUSINESS,
	bproduct_PRICE,
	bproduct_STOCK,

	//indexs
	bproduct_INDEX_PRODUCT
};
new BProducts[MAX_BUSINESS][MAX_PRODUCTS_PER_BUSINESS][E_BProducts],
	Iterator:BProducts[MAX_BUSINESS]<MAX_PRODUCTS_PER_BUSINESS>;

//business_types_stypes
enum E_BTypes_STypes
{
	btype_stype_ID_BUSINESS_TYPE,
	btype_stype_ID_BSALES_TYPE
};
new BTypes_STypes[BUSINESS_TYPE_SIZE * BUSINESS_SALE_TYPE_SIZE][E_BTypes_STypes],
	Iterator:BTypes_STypes<BUSINESS_TYPE_SIZE * BUSINESS_SALE_TYPE_SIZE>;