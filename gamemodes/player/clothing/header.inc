#define CHARACTER_CHANGE_PRICE 10000
#define MIN_DAYS_BETWEEN_CHAR_CHANGE 14
forward OnPlayerCharacterChange(playerid);
forward OnPlayerClothesLoaded(playerid);
forward OnPlayerRequestCharacterChange(playerid);
forward OnPlayerClothesChange(playerid, index);
forward OnPlayerRemoveClothes(playerid, index, CLOTHES_TYPES:id_clothe);
forward OnPlayerGetClothes(playerid);

new CLOTHES_TYPES:pClothes[MAX_PLAYERS][MAX_CLOTHING_CLOTHES_PER_CHAR],
	Iterator:pClothes[MAX_PLAYERS]<MAX_CLOTHING_CLOTHES_PER_CHAR>,
	pClothesMenu[MAX_PLAYERS] = INVALID_MENU_ID,
	pClothesInfo[MAX_PLAYERS][2];