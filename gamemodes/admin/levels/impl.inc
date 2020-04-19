#include <YSI\y_hooks>

hook OnScriptInit()
{
	for (new i = 1; i < MAX_ADMIN_LEVELS; i ++)
	{
		Admin_Groups[i] = Group_Create();
		if (i > 1) Group_AddChild(Admin_Groups[i], Admin_Groups[i - 1]);
	}

	CallRemoteFunction("OnAdminGroupsCreated", "");
	return 1;
}

hook OnPlayerLogin(playerid)
{
	if(PI[playerid][pi_ADMIN_LEVEL] > 0)
	{
		SetPlayerAdminLevel(playerid, PI[playerid][pi_ADMIN_LEVEL], false);
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	for (new i = 1; i < MAX_ADMIN_LEVELS; i ++) Group_SetPlayer(Admin_Groups[i], playerid, false);
	return 1;
}