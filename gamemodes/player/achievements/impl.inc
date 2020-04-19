#include <YSI\y_hooks>

hook OnScriptInit()
{
	Iter_Init(pAchievements);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	new tmp_pAchievements[enum_pAchievements];
	foreach(new i : pAchievements[playerid])
	{
		pAchievements[playerid][i] = tmp_pAchievements;
	}
	for(new i, j = sizeof PTD_pAchievement[]; i != j; i++)
	{
		if(PTD_pAchievement[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_pAchievement[playerid][i]);
			PTD_pAchievement[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	if(PTD_pAchievement_Timer[playerid] != Timer:-1)
	{
		stop PTD_pAchievement_Timer[playerid];
		PTD_pAchievement_Timer[playerid] = Timer:-1;
	}
	Iter_Clear(pAchievements[playerid]);
	return 1;
}

hook OnPlayerLogin(playerid)
{
	LoadPlayerAchievements(playerid);
	return 1;
}

timer HidePlayerAchievement_Timer[5000](playerid)
{
	PTD_pAchievement_Timer[playerid] = Timer:-1;
	HidePlayerAchievement(playerid);
}

//prizes:
hook OnPlayerRegister(playerid)
{
	AddPlayerAchievement(playerid, ACHIEVEMENT_NEW_USER);
	return 1;
}

hook OnPlayerRentVehicle(playerid, vehindex)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_RENT_CAR))
	AddPlayerAchievement(playerid, ACHIEVEMENT_RENT_CAR);
	return 1;
}

hook OnPlayerPurchaseCar(playerid)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_PURCHASE_CAR))
	AddPlayerAchievement(playerid, ACHIEVEMENT_PURCHASE_CAR);
	return 1;
}

hook OnPlayerPurchaseUsedCar(playerid)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_PURCHASE_USED_CAR))
	AddPlayerAchievement(playerid, ACHIEVEMENT_PURCHASE_USED_CAR);
	return 1;
}

hook OnPlayerGetDriverLicen(playerid)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_DRIVER_LICENSE))
	AddPlayerAchievement(playerid, ACHIEVEMENT_DRIVER_LICENSE);
	return 1;
}

hook OnPlayerHospitalBed(playerid)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_HOSPITAL_BED))
	AddPlayerAchievement(playerid, ACHIEVEMENT_HOSPITAL_BED);
	return 1;
}

hook OnPlayerAtmWithdraw(playerid)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_USE_ATM))
	AddPlayerAchievement(playerid, ACHIEVEMENT_USE_ATM);
	return 1;
}

hook OnPlayerAtmDeposit(playerid)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_USE_ATM))
	AddPlayerAchievement(playerid, ACHIEVEMENT_USE_ATM);
	return 1;
}

hook OnPlayerPurchaseProp(playerid)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_PURCHASE_PROPERTY))
	AddPlayerAchievement(playerid, ACHIEVEMENT_PURCHASE_PROPERTY);
	return 1;
}

hook OnPlayerRentProp(playerid)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_RENT_PROPERTY))
	AddPlayerAchievement(playerid, ACHIEVEMENT_RENT_PROPERTY);
	return 1;
}

hook OnPlayerPurchaseBizz(playerid)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_PURCHASE_BUSINESS))
	AddPlayerAchievement(playerid, ACHIEVEMENT_PURCHASE_BUSINESS);
	return 1;
}

hook OnPlayerGetGunLicen(playerid)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_GUN_LICENSE))
	AddPlayerAchievement(playerid, ACHIEVEMENT_GUN_LICENSE);
	return 1;
}

hook OnPlayerCompleteIntro(playerid)
{
	if(!PlayerAchievementsContainsId(playerid, ACHIEVEMENT_INTRO))
	AddPlayerAchievement(playerid, ACHIEVEMENT_INTRO);
	return 1;
}

YCMD:achievements(playerid, params[], help)
{
	new line_str[145], dialog[145 * MAX_ACHIEVEMENTS];
	foreach(new i : pAchievements[playerid])
	{
		new achievement[128];
		format(achievement, sizeof achievement, "%s", GetAchievementName(playerid, pAchievements[playerid][i][pAch_ID], false));
		format(line_str, sizeof line_str, "- %c%s (%s)\n", toupper(achievement[0]), achievement[1], pAchievements[playerid][i][pAch_DATE]);
		strcat(dialog, line_str);
	}

	inline OnPlayerDialog(pid, did, res, lis, string:inp)
	{
		#pragma unused pid, did, res, lis, inp
	}
	Dialog_ShowCallback(playerid, using inline OnPlayerDialog, DIALOG_STYLE_MSGBOX, " - ", dialog, "X", "");
	return 1;
}