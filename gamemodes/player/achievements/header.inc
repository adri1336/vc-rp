#define ACHIEVEMENT_TD_BG_SIZEX 100.0
#define ACHIEVEMENT_TD_SIZE 35.0
#define ACHIEVEMENT_SOUND_ID 31205

enum enum_pAchievements
{
	ACHIEVEMENTS:pAch_ID,
	pAch_DATE[24]
};
new pAchievements[MAX_PLAYERS][MAX_ACHIEVEMENTS][enum_pAchievements],
	Iterator:pAchievements[MAX_PLAYERS]<MAX_ACHIEVEMENTS>,

	PlayerText:PTD_pAchievement[MAX_PLAYERS][4] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
	Timer:PTD_pAchievement_Timer[MAX_PLAYERS] = {Timer:-1, ...};

//prizes:
forward OnPlayerRentVehicle(playerid, vehindex);
forward OnPlayerPurchaseCar(playerid);
forward OnPlayerPurchaseUsedCar(playerid);
forward OnPlayerGetDriverLicen(playerid);
forward OnPlayerPurchaseProp(playerid);
forward OnPlayerRentProp(playerid);
forward OnPlayerPurchaseBizz(playerid);