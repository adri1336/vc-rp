#include <YSI\y_hooks>

loadtext lang[intro];

hook OnScriptInit()
{
	Iter_Init(pCreditsObjects);
	return 1;
}

hook OnPlayerRegister(playerid)
{
	inline OnPlayerDialog(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, listitem, inputtext
		if(response)
		{
			HidePlayerMenu(playerid, false);
			HidePlayerAchievement(playerid);
			StartPlayerIntro(playerid);
		}
	}	
	Text_DialogBox(playerid, DIALOG_STYLE_MSGBOX, using inline OnPlayerDialog, $DIALOG_INTRO_INFO_CAPTION, $DIALOG_INTRO_INFO_BODY, $DIALOG_INTRO_INFO_YES, $DIALOG_INTRO_INFO_NO);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(pInIntro[playerid]) DestroyPlayerIntro(playerid);
	return 1;
}

timer OnPlayerRequestIntroNext[10000](playerid, bool:end)
{
	if(end)
	{
		DestroyPlayerIntro(playerid);
		HidePlayerScreenTD(playerid);
		ShowPlayerMenu(playerid);
		PlayAudioStreamForPlayer(playerid, Intro_Audios[random(sizeof Intro_Audios)]);

		new camera = random(sizeof Intro_Cameras);
		InterpolateCameraPos(playerid, Intro_Cameras[camera][0], Intro_Cameras[camera][1], Intro_Cameras[camera][2], Intro_Cameras[camera][6], Intro_Cameras[camera][7], Intro_Cameras[camera][8], 10000, CAMERA_MOVE);
		InterpolateCameraLookAt(playerid, Intro_Cameras[camera][3], Intro_Cameras[camera][4], Intro_Cameras[camera][5], Intro_Cameras[camera][9], Intro_Cameras[camera][10], Intro_Cameras[camera][11], 10000, CAMERA_MOVE);

		if(pIntroFinished[playerid])
		CallRemoteFunction("OnPlayerCompleteIntro", "i", playerid);

		CleanPlayerChat(playerid);
	}
	else
	{
		pIntroStep[playerid] ++;
		if(pIntroStep[playerid] >= sizeof Intro_Info)
		{
			if(pIntro_Timer[playerid] != Timer:-1)
			{
				stop pIntro_Timer[playerid];
				pIntro_Timer[playerid] = Timer:-1;
			}
			
			pIntroExiting[playerid] = true;
			pIntroFinished[playerid] = true;
			PlayerTextDrawHide(playerid, pIntro_PTD[playerid][2]);
			FadePlayerScreenTimed(playerid, 0x00, 0xFF, 1000, 0x000000, false);
		}
		else
		{
			SetPlayerIntroStep(playerid);
			if(pIntroStep[playerid] == sizeof Intro_Info - 1) CreatePlayerCreditsObjects(playerid, pIntroStep[playerid]);
		}
	}
	return 1;
}

hook OnFadeComplete(playerid, bool:in, color, fadeid)
{
	if(pInIntro[playerid] && pIntroExiting[playerid])
	{
		if(pIntro_Timer[playerid] != Timer:-1)
		{
			stop pIntro_Timer[playerid];
			pIntro_Timer[playerid] = Timer:-1;
		}
		pIntro_Timer[playerid] = defer OnPlayerRequestIntroNext[2000](playerid, true);
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(pInIntro[playerid] && !pIntroExiting[playerid])
	{
		if(newkeys & KEY_SPRINT)
		{
			if(pIntro_Timer[playerid] != Timer:-1)
			{
				stop pIntro_Timer[playerid];
				pIntro_Timer[playerid] = Timer:-1;
			}

			pIntroExiting[playerid] = true;
			StopAudioStreamForPlayer(playerid);
			PlayerTextDrawHide(playerid, pIntro_PTD[playerid][2]);
			FadePlayerScreenTimed(playerid, 0x00, 0xFF, 1000, 0x000000, false);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return 1;
}