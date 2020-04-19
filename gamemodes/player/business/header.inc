#define MAX_PLAYER_BUSINESS 3
#define BPRODUCT_PRICE_MUL 0.75
#define BPRODUCT_PRICE_MAX_MUL 3.0

#define BPRODUCTS_TD_X 320.0
#define BPRODUCTS_TD_Y 224.0//140.0
#define BPRODUCTS_TD_SIZE_X 280.0
#define BPRODUCTS_TD_PRODUCTS 10
#define BPRODUCTS_TD_PADDING 2.0
#define BPRODUCTS_TD_TEXT_OFFSET_Y 10.0

new Iterator:PlayerBusiness<MAX_PLAYERS, MAX_BUSINESS>,
	pBusinessTmpMenu[MAX_PLAYERS] = INVALID_MENU_ID,
	
	pBusinessTmpProductIndex[MAX_PLAYERS][MAX_BUSINESS_PRODUCTS] = {{-1, ...}, ...},
	bool:pBusinessTmpMenu_Clothes[MAX_PLAYERS] = {false, ...},
	bool:pBusinessTmpMenu_Toys[MAX_PLAYERS] = {false, ...},

	//productos admininstracion
	bool:pBProducts_Enabled[MAX_PLAYERS],
	bool:pBProducts_Order[MAX_PLAYERS][5], //false ASC, true DESC
	pBProducts_IndexBusiness[MAX_PLAYERS] = {-1, ...},
	Float:pBProducts_Column_Size_X[MAX_PLAYERS],
	PlayerText:pBProducts_Base_PTD[MAX_PLAYERS][10] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	PlayerText:pBProducts_Products_PTD[MAX_PLAYERS][BPRODUCTS_TD_PRODUCTS][6];

forward OnPlayerRequestBSPoint(playerid, bsale_type, index_business);