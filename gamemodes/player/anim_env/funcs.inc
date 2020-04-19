#define RemovePlayerAnimEnvObject(%0) RemovePlayerAttachedObject(%0,ATTACHED_OBJECT_ANIM_SLOT)

RemovePlayerAnimEnv(playerid, bool:clearanims = true)
{
	if(pAnimEnv_Timer[playerid] != Timer:-1)
	{
		stop pAnimEnv_Timer[playerid];
		pAnimEnv_Timer[playerid] = Timer:-1;
	}
	if(pAnimEnv_Delay_Timer[playerid] != Timer:-1)
	{
		stop pAnimEnv_Delay_Timer[playerid];
		pAnimEnv_Delay_Timer[playerid] = Timer:-1;
	}
	pAnimEnv[playerid] = false;
	RemovePlayerAnimEnvObject(playerid);
	if(clearanims)
	{
		ClearAnimations(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	}
	return 1;
}

SetPlayerAnimEnv(playerid, animlib[], animname[], bool:animloop, modelid = 0, bone = 0, Float:x = 0.0, Float:y = 0.0, Float:z = 0.0, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, Float:sx = 1.0, Float:sy = 1.0, Float:sz = 1.0, specialaction = 0, time = 0, animdelay = 0, soundid = 0, animlockx = 0, animlocky = 0)
{
	if(pAnimEnv_Timer[playerid] != Timer:-1)
	{
		stop pAnimEnv_Timer[playerid];
		pAnimEnv_Timer[playerid] = Timer:-1;
	}
	if(pAnimEnv_Delay_Timer[playerid] != Timer:-1)
	{
		stop pAnimEnv_Delay_Timer[playerid];
		pAnimEnv_Delay_Timer[playerid] = Timer:-1;
	}
	ClearAnimations(playerid);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	RemovePlayerAnimEnvObject(playerid);
	if(specialaction) SetPlayerSpecialAction(playerid, specialaction);
	else ApplyAnimation(playerid, animlib, animname, 4.1, animloop, animlockx, animlocky, 1, 0, 1);

	if(animdelay == 0)
	{
		if(modelid != 0) SetPlayerAttachedObject(playerid, ATTACHED_OBJECT_ANIM_SLOT, modelid, bone, x, y, z, rx, ry, rz, sx, sy, sz);
		if(soundid != 0) PlayerPlaySound(playerid, soundid, 0.0, 0.0, 0.0);
	}
	else pAnimEnv_Delay_Timer[playerid] = defer OnPlayerAnimDelayed[animdelay](playerid, modelid, bone, x, y, z, rx, ry, rz, sx, sy, sz, soundid);

	pAnimEnv[playerid] = true;
	if(time > 0) pAnimEnv_Timer[playerid] = defer OnPlayerAnimStopTimer[time](playerid);
	return 1;
}