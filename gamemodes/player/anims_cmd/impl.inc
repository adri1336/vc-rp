#include <YSI\y_hooks>

loadtext lang[anims_cmd];

YCMD:anim(playerid, params[], help)
{
    new index;
    if(!sscanf(params, "d", index))
    {
        if(index < 0 || index >= sizeof CommandAnimations) Text_Send(playerid, $MESSAGE_INVALID_INDEX, sizeof CommandAnimations - 1);
        else
        {
            if(index == 0)
            {
                ClearAnimations(playerid, 1);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            }
            else
            {
                if(CommandAnimations[index][anim_SPECIAL_ACTION] != SPECIAL_ACTION_NONE)
                {
                    ClearAnimations(playerid, 1);
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                    SetPlayerSpecialAction(playerid, CommandAnimations[index][anim_SPECIAL_ACTION]);
                }
                else
                {
                    ClearAnimations(playerid, 1);
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

                    if(!sscanf(params, "dd", params[0], params[1])) ApplyAnimation(playerid, CommandAnimations[index][anim_LIB], CommandAnimations[index][anim_NAME], CommandAnimations[index][anim_FDELTA], params[1], CommandAnimations[index][anim_LOCKX], CommandAnimations[index][anim_LOCKY], CommandAnimations[index][anim_FREEZE], CommandAnimations[index][anim_TIME], CommandAnimations[index][anim_FORCESYNC]);
                    else ApplyAnimation(playerid, CommandAnimations[index][anim_LIB], CommandAnimations[index][anim_NAME], CommandAnimations[index][anim_FDELTA], CommandAnimations[index][anim_LOOP], CommandAnimations[index][anim_LOCKX], CommandAnimations[index][anim_LOCKY], CommandAnimations[index][anim_FREEZE], CommandAnimations[index][anim_TIME], CommandAnimations[index][anim_FORCESYNC]);
                }
            }
        }
    }
    else Text_Send(playerid, $MESSAGE_ERROR_SYNTAX, sizeof CommandAnimations - 1);
    return 1;
}