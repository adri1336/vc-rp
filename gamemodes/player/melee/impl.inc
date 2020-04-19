#include <YSI\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(GetPlayerGameState(playerid) == GAME_STATE_SPAWNED && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if((newkeys & KEY_FIRE) || ((PRESSED(KEY_HANDBRAKE)) && (newkeys & KEY_SECONDARY_ATTACK)))
        {
            new tc = GetTickCount();
            if(tc - pLastHit[playerid] > 200)
            {
                new target_player = GetPlayerCameraTargetPlayer(playerid);
                if(target_player != INVALID_PLAYER_ID && GetPlayerState(target_player) == PLAYER_STATE_ONFOOT)
                {
                    new Float:x, Float:y, Float:z;
                    GetPlayerPos(playerid, x, y, z);
                    if(IsPlayerInRangeOfPoint(target_player, MELEE_RANGE_SIZE, x, y, z))
                    {
                        GivePlayerHealth(target_player, -1.32);
                        ApplyAnimation(target_player, "ped", "HitA_1", 4.1, 0, 0, 0, 0, 0, 1);
                        pLastHit[playerid] = tc;
                    }
                }
            }
        }
	}
	return 1;
} 