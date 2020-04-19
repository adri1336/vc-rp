#include <YSI\y_hooks>

public OnPlayerRequestEnvArea(playerid, type)
{
	switch(type)
	{
		case ENV_AREA_TYPE_DANCE:
		{
			new rand = minrand(SPECIAL_ACTION_DANCE1, SPECIAL_ACTION_DANCE4);
			SetPlayerSpecialAction(playerid, rand);
		}
		case ENV_AREA_TYPE_BED: ApplyAnimation(playerid, "INT_HOUSE", "BED_Loop_L", 4.1, 0, 0, 0, 0, 0, 1);
		case ENV_AREA_TYPE_SEAT: ApplyAnimation(playerid, "PED", "SEAT_idle", 4.1, 0, 0, 0, 0, 0, 1);
		case ENV_AREA_TYPE_PROSTITUTE_MONEY:
		{
			if(PI[playerid][pi_MONEY] >= PAYSTRIP_PRICE)
			{
				ApplyAnimation(playerid, "STRIP", RandomPayStripAnimations[random(sizeof(RandomPayStripAnimations))], 4.1, 0, 0, 0, 0, 0, 1);
				GivePlayerMoneyEx(playerid, -PAYSTRIP_PRICE);
			}
		}
	}
	return 1;
}