GetModelidFromInvItemId(itemid)
{
	switch(itemid)
	{
		case INV_ITEM_BEER: return 1486;
		case INV_ITEM_CIGARETTE: return 19625;
		case INV_ITEM_HOTDOG: return 19346;
		case INV_ITEM_PIZZA: return 2881;
		case INV_ITEM_SODA: return 2601;
		case INV_ITEM_WATER: return 1666;
		case INV_ITEM_WHISKY: return 2958;
		case INV_ITEM_HAMBURGER: return 2703;
	}
	return 0;
}

IsItemTypeDynamic(type) //puede salir del inv (intercambio maletero armarios)
{
	switch(type)
	{
		case INV_ITEM_TYPE_KEY, INV_ITEM_TYPE_DRINK, INV_ITEM_TYPE_FOOD, INV_ITEM_TYPE_CIGARETTE, INV_ITEM_TYPE_BOOMBOX, INV_ITEM_TYPE_WEAPON, INV_ITEM_TYPE_TOY:
		{
			return true;
		}
	}
	return false;
}