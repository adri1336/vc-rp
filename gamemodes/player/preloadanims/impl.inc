#include <YSI\y_hooks>

hook OnPlayerFirstSpawn(playerid, bool:new_user)
{
	for(new i = 0, j = sizeof s_AnimationLibraries; i != j; i++)
	{
		ApplyAnimation(playerid, s_AnimationLibraries[i], "null", 0.0, 0, 0, 0, 0, 0);
	}
	return 1;
}