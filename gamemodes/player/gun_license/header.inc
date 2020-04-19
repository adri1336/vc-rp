forward OnPlayerGunLicenseTestDialog(playerid, dialogid, response, listitem, inputtext[]);
forward OnPlayerRequestGunLicense(playerid);
forward OnPlayerGetGunLicen(playerid);

new pGunLicensePoints[MAX_PLAYERS],
	pGunLicenseQuestion[MAX_PLAYERS],
	pGunLicenseValidQuestion[MAX_PLAYERS],
	Timer:pGunLicenseTimer[MAX_PLAYERS] = {Timer:-1, ...};